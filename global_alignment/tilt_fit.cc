#include "TFile.h"
#include "TGraphErrors.h"
#include "TF1.h"

#include <vector>
#include <string>

using namespace std;

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

	vector<string> input_streams = {
		"DoubleEG",
		"SingleMuon",
	};

	vector<string> rps = {
		"L_1_F",
		"L_1_N",
		"R_1_N",
		"R_1_F",
	};

	// prepare output
	TFile *f_out = TFile::Open("tilt_fit.root", "recreate");

	// prepare fit function
	TF1 *ff = new TF1("ff", "[0]");

	// process each input directory
	for (const auto &rp : rps)
	{
		TGraphErrors *g_tilt_vs_fill = new TGraphErrors();

		for (const auto &dir : input_dirs)
		{
			const unsigned int fill = atoi(dir.substr(dir.find("fill_")+5).c_str());

			for (const auto &stream : input_streams)
			{
				TFile *f_in = TFile::Open(("../data/" + dir + "/" + stream + "/y_alignment.root").c_str());
				TGraph *g_results = (TGraph *) f_in->Get((rp + "/g_results").c_str());

				const double tilt = g_results->GetX()[1];
				const double tilt_unc = g_results->GetY()[1];

				int idx = g_tilt_vs_fill->GetN();
				g_tilt_vs_fill->SetPoint(idx, fill, tilt);
				g_tilt_vs_fill->SetPointError(idx, 0., tilt_unc);

				delete f_in;
			}
		}

		// make fit
		ff->SetParameter(0, 0.);
		g_tilt_vs_fill->Fit(ff, "Q");

		// save output
		gDirectory = f_out->mkdir(rp.c_str());
		g_tilt_vs_fill->Write("g_tilt_vs_fill");

		if (rp == "L_1_N")
		{
			TGraph *g_tilt_vs_fill_smooth = new TGraph();
			g_tilt_vs_fill_smooth->SetLineColor(2);
			g_tilt_vs_fill_smooth->SetPoint(0, 4930, -0.0525);
			g_tilt_vs_fill_smooth->SetPoint(1, 5000, -0.0525);
			g_tilt_vs_fill_smooth->SetPoint(2, 5004, -0.066);
			g_tilt_vs_fill_smooth->SetPoint(3, 5032, -0.040);
			g_tilt_vs_fill_smooth->SetPoint(4, 5054, -0.035);
			g_tilt_vs_fill_smooth->SetPoint(5, 5260, -0.04);
			g_tilt_vs_fill_smooth->SetPoint(6, 5290, -0.0315);
			g_tilt_vs_fill_smooth->Write("g_tilt_vs_fill_smooth");
		}
	}

	// clean up
	delete f_out;

	return 0;
}
