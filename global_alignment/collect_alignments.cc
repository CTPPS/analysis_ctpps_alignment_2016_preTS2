#include "../alignment_classes.h"

using namespace std;

//----------------------------------------------------------------------------------------------------

struct AlignmentInput
{
	string file;
	string tag;
	vector<string> streams;

	vector<AlignmentResults> collection;

	AlignmentInput(const string &_f, const string &_t, const vector<string> _s) : file(_f), tag(_t), streams(_s)
	{
	}

	void Load(const string &dir, bool &error)
	{
		collection.clear();

		if (file == "none")
			return;

		for (const auto &stream : streams)
		{
			AlignmentResultsCollection arc;
			string fn = "../data/" + dir + "/" + stream + "/" + file;
			int res = arc.Load(fn);
			if (res != 0)
			{
				printf("ERROR: can't load alignment results from file '%s'.\n", fn.c_str());
				collection.clear();
				error = true;
				return;
			}

			const auto it = arc.find(tag);
			if (it == arc.end())
			{
				printf("ERROR: can't load tag '%s' from file '%s'.\n", tag.c_str(), fn.c_str());
				collection.clear();
				error = true;
				return;
			}

			collection.emplace_back(it->second);
		}
	}

	set<unsigned int> GetRPs() const
	{
		set<unsigned int> rps;

		if (file == "none")
			return rps;

		for (unsigned int i = 0; i < streams.size(); ++i)
		{
			for (const auto &r : collection[i])
				rps.insert(r.first);
		}

		return rps;
	}

	AlignmentResult GetMeanAlignment(unsigned int rpId, bool &error) const
	{
		AlignmentResult mean;

		if (file == "none")
			return mean;

		for (unsigned int i = 0; i < streams.size(); ++i)
		{
			const auto it = collection[i].find(rpId);
			if (it == collection[i].end())
			{
				printf("ERROR: can't get RP '%u' from file '%s' and stream '%s'.\n", rpId, file.c_str(), streams[i].c_str());
				error = true;
				return mean;
			}

			mean.sh_x += it->second.sh_x;
			mean.sh_y += it->second.sh_x;
			mean.rot_z += it->second.sh_x;
		}
		
		mean.sh_x /= streams.size();
		mean.sh_y /= streams.size();
		mean.rot_z /= streams.size();

		return mean;
	}
};

//----------------------------------------------------------------------------------------------------

int main()
{
	// define datasets
	vector<string> input_dirs = {
		"phys_margin/fill_4947",
		"phys_margin/fill_4953",
		"phys_margin/fill_4961",
		"phys_margin/fill_4964",
		"phys_margin/fill_4976",

		"phys_no_margin/fill_4964",
		"phys_no_margin/fill_4985",
		"phys_no_margin/fill_4988",
		"phys_no_margin/fill_4990",
		"phys_no_margin/fill_5005",
		"phys_no_margin/fill_5013",
		"phys_no_margin/fill_5017",
		"phys_no_margin/fill_5020",
		"phys_no_margin/fill_5021",
		"phys_no_margin/fill_5024",
		"phys_no_margin/fill_5026",
		"phys_no_margin/fill_5027",
		"phys_no_margin/fill_5028",
		"phys_no_margin/fill_5029",
		"phys_no_margin/fill_5030",
		"phys_no_margin/fill_5038",
		"phys_no_margin/fill_5043",
		"phys_no_margin/fill_5045",
		"phys_no_margin/fill_5048",
		"phys_no_margin/fill_5052",
		"phys_no_margin/fill_5261",
		"phys_no_margin/fill_5264",
		"phys_no_margin/fill_5265",
		"phys_no_margin/fill_5266",
		"phys_no_margin/fill_5267",
		"phys_no_margin/fill_5274",
		"phys_no_margin/fill_5275",
		"phys_no_margin/fill_5276",
		"phys_no_margin/fill_5277",
		"phys_no_margin/fill_5279",
		"phys_no_margin/fill_5287",
		"phys_no_margin/fill_5288",
	};

	// define input
	AlignmentInput input_sh_x("copy_alignment.out", "copy_alignment", {"DoubleEG"});
	AlignmentInput input_sh_y("y_alignment.out", "y_alignment", {"DoubleEG", "SingleMuon"});
	AlignmentInput input_rot_z("rot_z_alignment.out", "rot_z_alignment", {"DoubleEG"});

	//const string output_tag = "_2018_07_16";
	const string output_tag = "_new";
	
	// collection
	AlignmentResultsCollection output;

	// process each input directory
	for (const auto dir : input_dirs)
	{
		// load alignment
		bool error = false;
		input_sh_x.Load(dir, error);
		input_sh_y.Load(dir, error);
		input_rot_z.Load(dir, error);

		if (error)
			continue;

		// get list of RPs
		set<unsigned int> rpIds;

		for (const auto rp : input_sh_x.GetRPs())
			rpIds.insert(rp);

		for (const auto rp : input_sh_y.GetRPs())
			rpIds.insert(rp);

		for (const auto rp : input_rot_z.GetRPs())
			rpIds.insert(rp);

		// combine horizontal and verctical alignment
		AlignmentResults ars_combined;

		for (unsigned int rpId : rpIds)
		{
			error = false;
			const AlignmentResult &ar_sh_x = input_sh_x.GetMeanAlignment(rpId, error);
			const AlignmentResult &ar_sh_y = input_sh_x.GetMeanAlignment(rpId, error);
			const AlignmentResult &ar_rot_z = input_sh_x.GetMeanAlignment(rpId, error);

			if (error)
				continue;

			double x_corr = 0.;
			/*
			if (rpId == 2) x_corr = +0.019;
			if (rpId == 3) x_corr = -0.019;
			if (rpId == 102) x_corr = +0.045;
			if (rpId == 103) x_corr = -0.045;
			*/

			ars_combined[rpId] = AlignmentResult(ar_sh_x.sh_x + x_corr, 150E-3, ar_sh_y.sh_y, 100E-3, ar_rot_z.rot_z, ar_rot_z.rot_z_unc);
		}

		output[dir] = ars_combined;
	}

	output.Write("collect_alignments" + output_tag + ".out");

	return 0;
}
