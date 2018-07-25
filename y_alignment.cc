#include "config.h"
#include "stat.h"
#include "alignment_classes.h"
#include "fill_info.h"

#include "TFile.h"
#include "TH1D.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TProfile.h"

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

	// get input
	TFile *f_in = new TFile("distributions.root");

	// ouput file
	TFile *f_out = new TFile("y_alignment.root", "recreate");

	// get fill info
	InitFillInfoCollection();
	const auto &fillInfo = fillInfoCollection.FindByFill(cfg.fill, cfg.rps_have_margin);

	//  load alignment
	AlignmentResultsCollection alignmentCollection;
	alignmentCollection.Load("../../../../global_alignment/data/collect_alignments_2017_01_17.out");
	printf("* global alignment tag: %s\n", fillInfo.alignmentTag.c_str());
	const auto alignments = alignmentCollection.find(fillInfo.alignmentTag)->second;

	// prepare results
	AlignmentResultsCollection results;

	TF1 *ff = new TF1("ff", "[0] + [1]*x");

	// processing
	for (const auto &rpd : rpData)
	{
		printf("* %s\n", rpd.name.c_str());

		TDirectory *rp_dir = f_out->mkdir(rpd.name.c_str());
		gDirectory = rp_dir;
		
		TProfile *p_y_vs_x = (TProfile *) f_in->Get((rpd.sectorName + "/profiles/" + rpd.name + "/h_mean").c_str());

		if (p_y_vs_x == NULL)
		{
			printf("    cannot load data, skipping\n");
			continue;
		}

		const auto ait = alignments.find(rpd.id);
		const double sh_x = ait->second.sh_x;
		const double x_min = cfg.alignment_y_ranges[rpd.id].x_min - sh_x;
		const double x_max = cfg.alignment_y_ranges[rpd.id].x_max - sh_x;

		printf("    x_min = %.3f, x_max = %.3f\n", x_min, x_max);

		ff->SetParameters(0., 0.);
		p_y_vs_x->Fit(ff, "Q", "", x_min, x_max);

		p_y_vs_x->Write("p_y_vs_x");

		const double a = ff->GetParameter(1), a_unc = ff->GetParError(1);
		const double b = ff->Eval(-sh_x), b_unc = sqrt(pow(a_unc * sh_x, 2.) + pow(ff->GetParError(0), 2.));

		TGraph *g_results = new TGraph();
		g_results->SetPoint(0, sh_x, 0.);
		g_results->SetPoint(1, a, a_unc);
		g_results->SetPoint(2, b, b_unc);
		g_results->Write("g_results");

		results["y_alignment"][rpd.id] = AlignmentResult(0., 0., b, b_unc, 0., 0.);
	}

	// write results
	results.Write("y_alignment.out");

	// clean up
	delete f_out;
	return 0;
}
