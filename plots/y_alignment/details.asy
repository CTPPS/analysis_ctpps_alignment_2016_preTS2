import root;
import pad_layout;

string topDir = "../../data/";

int rp_ids[];
string rps[], rp_labels[];
real rp_x_min[], rp_x_max[], rp_y_cen[];
rp_ids.push(3); rps.push("L_1_F"); rp_labels.push("L-210-fr-hr"); rp_x_min.push(-3.65); rp_x_max.push(-4.17); rp_y_cen.push(-0.75);
rp_ids.push(2); rps.push("L_1_N"); rp_labels.push("L-210-nr-hr"); rp_x_min.push(-1.15); rp_x_max.push(-0.00); rp_y_cen.push(-0.4);
rp_ids.push(102); rps.push("R_1_N"); rp_labels.push("R-210-nr-hr"); rp_x_min.push(-3.32); rp_x_max.push(-3.93); rp_y_cen.push(-0.4);
rp_ids.push(103); rps.push("R_1_F"); rp_labels.push("R-210-fr-hr"); rp_x_min.push(-2.96); rp_x_max.push(-3.57); rp_y_cen.push(-0.6);

xSizeDef = 9cm;

xTicksDef = LeftTicks(1., 0.5);
yTicksDef = RightTicks(0.1, 0.05);

string datasets[] = {
	"phys_margin/fill_4947/DoubleEG",
	"phys_no_margin/fill_5005/DoubleEG",
	"phys_no_margin/fill_5038/DoubleEG",

	"phys_no_margin/fill_5261/DoubleEG",
	"phys_no_margin/fill_5275/DoubleEG",
	"phys_no_margin/fill_5287/DoubleEG",
	"phys_no_margin/fill_5288/DoubleEG",
};

string datasets[] = {
	"phys_no_margin/fill_5024/DoubleEG",
	"phys_no_margin/fill_5026/DoubleEG",
	"phys_no_margin/fill_5038/DoubleEG",
	"phys_no_margin/fill_5045/DoubleEG",
	"phys_no_margin/fill_5261/DoubleEG",
};

//----------------------------------------------------------------------------------------------------

for (int dsi : datasets.keys)
{
	string dataset = datasets[dsi];
	
	NewRow();

	NewPadLabel(replace(dataset, "_", "\_"));


	for (int rpi : rps.keys)
	{
		NewPad("$x\ung{mm}$", "mean of $y\ung{mm}$");
	
		RootObject profile = RootGetObject(topDir + dataset + "/y_alignment.root", rps[rpi] + "/p_y_vs_x");
		RootObject fit = RootGetObject(topDir + dataset + "/y_alignment.root", rps[rpi] + "/p_y_vs_x|ff", error=true);
		RootObject results = RootGetObject(topDir + dataset + "/y_alignment.root", rps[rpi] + "/g_results");

		if (!fit.valid)
			continue;

		draw(profile, "eb,d0", red);

		TF1_x_min = -inf;
		TF1_x_max = +inf;
		draw(fit, "def", blue+2pt);

		TF1_x_min = 0;
		TF1_x_max = 13;
		draw(fit, "def", blue+dashed);

		//real y_cen = rp_y_cen[rpi];
		real y_cen = fit.rExec("Eval", 8.);

		real ax[] = {0.};
		real ay[] = {0.};
		results.vExec("GetPoint", 0, ax, ay); real sh_x = ax[0];
		results.vExec("GetPoint", 1, ax, ay); real a = ax[0], a_unc = ay[0];
		results.vExec("GetPoint", 2, ax, ay); real b = ax[0], b_unc = ay[0];

		draw((-sh_x, b), mCi+3pt+magenta);
	
		limits((2, y_cen - 0.5), (18, y_cen + 0.5), Crop);

		yaxis(XEquals(-sh_x, false), heavygreen);
	
		AttachLegend(rp_labels[rpi]);
	}
}
