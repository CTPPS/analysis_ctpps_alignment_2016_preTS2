#include "config.h"
#include "alignment_classes.h"

#include "TFile.h"
#include "TGraph.h"

#include <vector>
#include <string>

using namespace std;

//----------------------------------------------------------------------------------------------------

int main()
{
	// load config
	if (cfg.LoadFrom("config.py") != 0)
	{
		printf("ERROR: cannot load config.\n");
		return 1;
	}

	printf("-------------------- config ----------------------\n");
	cfg.Print(false);
	printf("--------------------------------------------------\n");

	// list of RPs and their settings
	struct RPData
	{
		string name;
		unsigned int id;
		string sectorName;
	};

	vector<RPData> rpData = {
		{ "L_1_F", 3,   "sector 45" },
		{ "L_1_N", 2,   "sector 45" },
		{ "R_1_N", 102, "sector 56" },
		{ "R_1_F", 103, "sector 56" }
	};

	// prepare input
	TFile *f_in = TFile::Open("../../../../global_alignment/tilt_fit.root");

	// prepare results
	AlignmentResultsCollection results;

	// processing
	for (const auto &rpd : rpData)
	{
		printf("* %s\n", rpd.name.c_str());

		TGraph *g_tilt_vs_fill_smooth = (TGraph *) f_in->Get((rpd.name + "/g_tilt_vs_fill_smooth").c_str());

		double tilt = 0.;
		double tilt_unc = 0.;

		if (rpd.id == 2)
		{
			tilt = g_tilt_vs_fill_smooth->Eval(cfg.fill) + 0.03;
			tilt_unc = 0.005;
		}

		results["rot_z_alignment"][rpd.id] = AlignmentResult(0., 0., 0., 0., tilt, tilt_unc);
	}

	// write results
	FILE *f_results = fopen("rot_z_alignment.out", "w"); 
	results.Write(f_results);
	fclose(f_results);

	// clean up
	delete f_in;
	return 0;
}
