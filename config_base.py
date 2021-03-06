import FWCore.ParameterSet.Config as cms

config = cms.PSet(
    fill = cms.uint32(0),
    dataset = cms.string(""),
    rps_have_margin = cms.bool(False),

    alignment_corrections = cms.PSet(
      rp_L_1_F = cms.PSet(
        de_x = cms.double(0.)
      ),
      rp_L_1_N = cms.PSet(
        de_x = cms.double(0.)
      ),
      rp_R_1_N = cms.PSet(
        de_x = cms.double(0.)
      ),
      rp_R_1_F = cms.PSet(
        de_x = cms.double(0.)
      )
    ),

    aligned = cms.bool(False),

    n_si = cms.double(4.),

    sector_45 = cms.PSet(
	  cut_h_apply = cms.bool(True),
	  cut_h_a = cms.double(-1),
	  cut_h_c = cms.double(-38.55),
	  cut_h_si = cms.double(0.2),

	  cut_v_apply = cms.bool(False),
	  cut_v_a = cms.double(-1.07),
	  cut_v_c = cms.double(1.63),
	  cut_v_si = cms.double(0.15)
    ),

    sector_56 = cms.PSet(
	  cut_h_apply = cms.bool(True),
	  cut_h_a = cms.double(-1),
	  cut_h_c = cms.double(-39.26),
	  cut_h_si = cms.double(0.2),

	  cut_v_apply = cms.bool(False),
	  cut_v_a = cms.double(-1.07),
	  cut_v_c = cms.double(1.49),
	  cut_v_si = cms.double(0.15)
    ),

    matching = cms.PSet(
      reference_datasets = cms.vstring("default"),

      rp_L_1_F = cms.PSet(
        x_min = cms.double(0.),
        x_max = cms.double(0.),
        sh_min = cms.double(-4.5),
        sh_max = cms.double(-3.3)
      ),
      rp_L_1_N = cms.PSet(
        x_min = cms.double(0.),
        x_max = cms.double(0.),
        sh_min = cms.double(-3.7),
        sh_max = cms.double(-0.8)
      ),
      rp_R_1_N = cms.PSet(
        x_min = cms.double(0.),
        x_max = cms.double(0.),
        sh_min = cms.double(-4.3),
        sh_max = cms.double(-2.8)
      ),
      rp_R_1_F = cms.PSet(
        x_min = cms.double(0.),
        x_max = cms.double(0.),
        sh_min = cms.double(-4.2),
        sh_max = cms.double(-2.5)
      )
    ),

    alignment_y = cms.PSet(
      rp_L_1_F = cms.PSet(
        x_min = cms.double(46.5),
        x_max = cms.double(57.),
      ),
      rp_L_1_N = cms.PSet(
        x_min = cms.double(8.),
        x_max = cms.double(18.),
      ),
      rp_R_1_N = cms.PSet(
        x_min = cms.double(7.5),
        x_max = cms.double(18.),
      ),
      rp_R_1_F = cms.PSet(
        x_min = cms.double(47.),
        x_max = cms.double(57.),
      )
    ),

    rel_alignment_x = cms.PSet(
      rp_L_1_F = cms.PSet(
        x_min = cms.double(46.5),
        x_max = cms.double(57.),
      ),
      rp_L_1_N = cms.PSet(
        x_min = cms.double(8.),
        x_max = cms.double(18.),
      ),
      rp_R_1_N = cms.PSet(
        x_min = cms.double(7.5),
        x_max = cms.double(18.),
      ),
      rp_R_1_F = cms.PSet(
        x_min = cms.double(47.),
        x_max = cms.double(57.),
      )
    ),
)
