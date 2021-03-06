#ifndef _config_h_
#define _config_h_

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/PythonParameterSet/interface/MakeParameterSets.h"

#include <vector>
#include <string>

using namespace std;

//----------------------------------------------------------------------------------------------------

struct SelectionRange
{
	double x_min;
	double x_max;

	SelectionRange(double _xmi=0., double _xma=0.) : x_min(_xmi), x_max(_xma)
	{
	}
};

//----------------------------------------------------------------------------------------------------

struct SectorConfig
{
	bool cut_h_apply;
	double cut_h_a, cut_h_c, cut_h_si;

	bool cut_v_apply;
	double cut_v_a, cut_v_c, cut_v_si;
};

//----------------------------------------------------------------------------------------------------

struct Config
{
	unsigned int fill;
	string dataset;
	bool rps_have_margin;

	map<unsigned int, string> rp_tags;

	vector<string> input_files;

	map<unsigned int, double> alignment_corrections_x;

	bool aligned;

	double n_si;

	SectorConfig sectorConfig45, sectorConfig56;

	vector<string> matching_reference_datasets;

	map<unsigned int, SelectionRange> matching_ranges;
	map<unsigned int, SelectionRange> matching_shift_ranges;

	map<unsigned int, SelectionRange> alignment_y_ranges;

	map<unsigned int, SelectionRange> rel_alignment_x_ranges;

	int LoadFrom(const string &f);

	void Print(bool print_input_files=false) const;
};

//----------------------------------------------------------------------------------------------------

int Config::LoadFrom(const string &f_in)
{
	rp_tags = {
		{ 3, "L_1_F" },
		{ 2, "L_1_N" },
		{ 102, "R_1_N" },
		{ 103, "R_1_F" }
	};

	const edm::ParameterSet& config = edm::readPSetsFrom(f_in)->getParameter<edm::ParameterSet>("config");

	fill = config.getParameter<unsigned int>("fill");
	dataset = config.getParameter<string>("dataset");
	rps_have_margin = config.getParameter<bool>("rps_have_margin");

	input_files = config.getParameter<vector<string>>("input_files");

	const auto &acc = config.getParameter<edm::ParameterSet>("alignment_corrections");
	for (const auto &p : rp_tags)
	{
		const auto &ps = acc.getParameter<edm::ParameterSet>("rp_" + p.second);
		alignment_corrections_x[p.first] = ps.getParameter<double>("de_x");
	}

	aligned = config.getParameter<bool>("aligned");

	n_si = config.getParameter<double>("n_si");

	{
		const auto &sps = config.getParameter<edm::ParameterSet>("sector_45");

		sectorConfig45.cut_h_apply = sps.getParameter<bool>("cut_h_apply");
		sectorConfig45.cut_h_a = sps.getParameter<double>("cut_h_a");
		sectorConfig45.cut_h_c = sps.getParameter<double>("cut_h_c");
		sectorConfig45.cut_h_si = sps.getParameter<double>("cut_h_si");

		sectorConfig45.cut_v_apply = sps.getParameter<bool>("cut_v_apply");
		sectorConfig45.cut_v_a = sps.getParameter<double>("cut_v_a");
		sectorConfig45.cut_v_c = sps.getParameter<double>("cut_v_c");
		sectorConfig45.cut_v_si = sps.getParameter<double>("cut_v_si");
	}

	{
		const auto &sps = config.getParameter<edm::ParameterSet>("sector_56");

		sectorConfig56.cut_h_apply = sps.getParameter<bool>("cut_h_apply");
		sectorConfig56.cut_h_a = sps.getParameter<double>("cut_h_a");
		sectorConfig56.cut_h_c = sps.getParameter<double>("cut_h_c");
		sectorConfig56.cut_h_si = sps.getParameter<double>("cut_h_si");

		sectorConfig56.cut_v_apply = sps.getParameter<bool>("cut_v_apply");
		sectorConfig56.cut_v_a = sps.getParameter<double>("cut_v_a");
		sectorConfig56.cut_v_c = sps.getParameter<double>("cut_v_c");
		sectorConfig56.cut_v_si = sps.getParameter<double>("cut_v_si");
	}

	const auto &c_m1d = config.getParameter<edm::ParameterSet>("matching");
	matching_reference_datasets = c_m1d.getParameter<vector<string>>("reference_datasets");

	for (const auto &p : rp_tags)
	{
		const auto &ps = c_m1d.getParameter<edm::ParameterSet>("rp_" + p.second);
		matching_ranges[p.first] = SelectionRange(ps.getParameter<double>("x_min"), ps.getParameter<double>("x_max"));
		matching_shift_ranges[p.first] = SelectionRange(ps.getParameter<double>("sh_min"), ps.getParameter<double>("sh_max"));
	}

	const auto &c_ay = config.getParameter<edm::ParameterSet>("alignment_y");
	for (const auto &p : rp_tags)
	{
		const auto &ps = c_ay.getParameter<edm::ParameterSet>("rp_" + p.second);
		alignment_y_ranges[p.first] = SelectionRange(ps.getParameter<double>("x_min"), ps.getParameter<double>("x_max"));
	}

	const auto &c_rax = config.getParameter<edm::ParameterSet>("rel_alignment_x");
	for (const auto &p : rp_tags)
	{
		const auto &ps = c_rax.getParameter<edm::ParameterSet>("rp_" + p.second);
		rel_alignment_x_ranges[p.first] = SelectionRange(ps.getParameter<double>("x_min"), ps.getParameter<double>("x_max"));
	}

	return 0;
}

//----------------------------------------------------------------------------------------------------

void Config::Print(bool print_input_files) const
{
	if (print_input_files)
	{
		printf("* input files\n");
		for (const auto &f : input_files)
			printf("    %s\n", f.c_str());
		printf("\n");
	}

	printf("* general info\n");
	printf("    fill = %u\n", fill);
	printf("    dataset = %s\n", dataset.c_str());
	printf("    rps_have_margin = %i\n", rps_have_margin);

	printf("\n");
	printf("* dataset already aligned\n");
	printf("    aligned = %u\n", aligned);

	printf("\n");
	printf("* alignment parameters\n");
	for (const auto &p : alignment_corrections_x)
		printf("    RP %u: de_x = %.3f mm\n", p.first, p.second);

	printf("\n");
	printf("* cuts\n");
	printf("    n_si = %.3f\n", n_si);

	printf("\n");
	printf("* sector 45\n");
	printf("    cut_h: apply = %u, a = %.3f, c = %.3f, si = %.3f\n", sectorConfig45.cut_h_apply, sectorConfig45.cut_h_a, sectorConfig45.cut_h_c, sectorConfig45.cut_h_si);
	printf("    cut_v: apply = %u, a = %.3f, c = %.3f, si = %.3f\n", sectorConfig45.cut_v_apply, sectorConfig45.cut_v_a, sectorConfig45.cut_v_c, sectorConfig45.cut_v_si);
	printf("* sector 56\n");
	printf("    cut_h: apply = %u, a = %.3f, c = %.3f, si = %.3f\n", sectorConfig56.cut_h_apply, sectorConfig56.cut_h_a, sectorConfig56.cut_h_c, sectorConfig56.cut_h_si);
	printf("    cut_v: apply = %u, a = %.3f, c = %.3f, si = %.3f\n", sectorConfig56.cut_v_apply, sectorConfig56.cut_v_a, sectorConfig56.cut_v_c, sectorConfig56.cut_v_si);

	printf("\n");
	printf("* matching\n");
	printf("    reference datasets (%lu):\n", matching_reference_datasets.size());
	for (const auto &ds : matching_reference_datasets)
		printf("        %s\n", ds.c_str());
	for (const auto &p : matching_ranges)
	{
		const auto it_sh = matching_shift_ranges.find(p.first);
		printf("    RP %u: x_min = %.3f, x_max = %.3f, sh_min = %.3f, sh_max = %.3f\n",
			p.first, p.second.x_min, p.second.x_max, it_sh->second.x_min, it_sh->second.x_max);
	}

	printf("\n* alignment_y\n");
	for (const auto &p : alignment_y_ranges)
		printf("    RP %u: x_min = %.3f, x_max = %.3f\n", p.first, p.second.x_min, p.second.x_max);

	printf("\n* rel_alignment_x\n");
	for (const auto &p : rel_alignment_x_ranges)
		printf("    RP %u: x_min = %.3f, x_max = %.3f\n", p.first, p.second.x_min, p.second.x_max);
}

//----------------------------------------------------------------------------------------------------

Config cfg;

#endif
