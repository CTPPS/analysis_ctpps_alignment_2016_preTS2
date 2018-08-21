import root;
import pad_layout;

string topDir = "../../data/";

include "../fills_samples.asy";
InitDataSets();

//----------------------------------------------------------------------------------------------------

string sample_labels[];
pen sample_pens[];
sample_labels.push("ZeroBias"); sample_pens.push(blue);
sample_labels.push("DoubleEG"); sample_pens.push(red);
sample_labels.push("SingleMuon"); sample_pens.push(heavygreen);

real sfa = 0.3;

int rp_ids[];
string rps[], rp_labels[];
real rp_y_min[], rp_y_max[];
rp_ids.push(3); rps.push("L_1_F"); rp_labels.push("L-210-fr-hr"); rp_y_min.push(-0.05); rp_y_max.push(-0.00);
rp_ids.push(2); rps.push("L_1_N"); rp_labels.push("L-210-nr-hr"); rp_y_min.push(-0.07); rp_y_max.push(-0.02);
rp_ids.push(102); rps.push("R_1_N"); rp_labels.push("R-210-nr-hr"); rp_y_min.push(-0.04); rp_y_max.push(+0.01);
rp_ids.push(103); rps.push("R_1_F"); rp_labels.push("R-210-fr-hr"); rp_y_min.push(-0.04); rp_y_max.push(+0.01);

xSizeDef = 20cm;

yTicksDef = RightTicks(0.01, 0.005);

//----------------------------------------------------------------------------------------------------

string TickLabels(real x)
{
	if (x >=0 && x < fill_data.length)
	{
		return format("%i", fill_data[(int) x].fill);
	} else {
		return "";
	}
}

xTicksDef = LeftTicks(rotate(90)*Label(""), TickLabels, Step=1, step=0);

//----------------------------------------------------------------------------------------------------

NewPad(false, 1, 1);

AddToLegend("with margin", mSq+false+3pt+black);
AddToLegend("without margin", mCi+true+3pt+black);

for (int sai : sample_labels.keys)
{
	AddToLegend(sample_labels[sai], sample_pens[sai]);
}

AttachLegend();

//----------------------------------------------------------------------------------------------------

for (int rpi : rps.keys)
{
	write(rps[rpi]);

	//if (rpi == 2)
		NewRow();

	NewPad("fill", "slope$\ung{rad}$");

	for (int fdi : fill_data.keys)
	{
		write(format("    %i", fill_data[fdi].fill));

		int fill = fill_data[fdi].fill; 
		int rp_id = rp_ids[rpi];

		for (int dsi : fill_data[fdi].datasets.keys)
		{
			string dataset = fill_data[fdi].datasets[dsi].tag;

			write("        " + dataset);
	
			mark m = (fill_data[fdi].datasets[dsi].margin) ? mSq+4pt+false : mCi+3pt;

			for (int sai : sample_labels.keys)
			{
				string f = topDir + dataset + "/" + sample_labels[sai] + "/y_alignment.root";

				RootObject obj = RootGetObject(f, rps[rpi] + "/p_y_vs_x|ff", error = false);
		
				if (!obj.valid)
					continue;
		
				real x = fdi;

				real y = obj.rExec("GetParameter", 1);
				real y_unc = obj.rExec("GetParError", 1);

				pen p = sample_pens[sai];

				{
					draw((x, y), m + p);
					draw((x, y-y_unc)--(x, y+y_unc), p);
				}
			}
		}
	}

	limits((-1, rp_y_min[rpi]), (fill_data.length, rp_y_max[rpi]), Crop);

	AttachLegend("{\SetFontSizesXX " + rp_labels[rpi] + "}");
}

//----------------------------------------------------------------------------------------------------

GShipout(hSkip=5mm, vSkip=1mm);
