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

	// get fill info
	InitFillInfoCollection();
	const auto &fillInfo = fillInfoCollection.FindByFill(cfg.fill, cfg.rps_have_margin);

	//  load alignment
	AlignmentResultsCollection alignmentCollection;
	alignmentCollection.Load("../../../../global_alignment/data/collect_alignments_2018_07_17.out");
	printf("* global alignment tag: %s\n", fillInfo.alignmentTag.c_str());
	const auto alignments = alignmentCollection.find(fillInfo.alignmentTag)->second;

	// write results
	AlignmentResultsCollection output;
	output["copy_alignment"] = alignments;
	output.Write("copy_alignment.out");

	// clean up
	return 0;
}
