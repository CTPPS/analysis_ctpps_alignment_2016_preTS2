import sys
import os
import FWCore.ParameterSet.Config as cms

sys.path.append(os.path.relpath("../../../../"))

from config_base import config

#config.sector_45.cut_h_apply = True
config.sector_45.cut_h_a = -0.999
config.sector_45.cut_h_c = 0.046
config.sector_45.cut_h_si = 0.200

#config.sector_45.cut_v_apply = False
config.sector_45.cut_v_a = -1.170
config.sector_45.cut_v_c = -0.077
config.sector_45.cut_v_si = 0.150

#config.sector_56.cut_h_apply = True
config.sector_56.cut_h_a = -0.963
config.sector_56.cut_h_c = 0.095
config.sector_56.cut_h_si = 0.200

#config.sector_56.cut_v_apply = False
config.sector_56.cut_v_a = -1.139
config.sector_56.cut_v_c = 0.400
config.sector_56.cut_v_si = 0.150

config.matching.rp_L_1_F.x_min = 3.50
config.matching.rp_L_1_F.x_max = 11.00
config.matching.rp_L_1_N.x_min = 3.70
config.matching.rp_L_1_N.x_max = 10.50
config.matching.rp_R_1_N.x_min = 2.00
config.matching.rp_R_1_N.x_max = 10.00
config.matching.rp_R_1_F.x_min = 2.00
config.matching.rp_R_1_F.x_max = 10.00

config.alignment_y.rp_L_1_F.x_min = 0.00
config.alignment_y.rp_L_1_F.x_max = 0.00
config.alignment_y.rp_L_1_N.x_min = 0.00
config.alignment_y.rp_L_1_N.x_max = 0.00
config.alignment_y.rp_R_1_N.x_min = 0.00
config.alignment_y.rp_R_1_N.x_max = 0.00
config.alignment_y.rp_R_1_F.x_min = 0.00
config.alignment_y.rp_R_1_F.x_max = 0.00

config.rel_alignment_x.rp_L_1_F.x_min = 0.00
config.rel_alignment_x.rp_L_1_F.x_max = 0.00
config.rel_alignment_x.rp_L_1_N.x_min = 0.00
config.rel_alignment_x.rp_L_1_N.x_max = 0.00
config.rel_alignment_x.rp_R_1_N.x_min = 0.00
config.rel_alignment_x.rp_R_1_N.x_max = 0.00
config.rel_alignment_x.rp_R_1_F.x_min = 0.00
config.rel_alignment_x.rp_R_1_F.x_max = 0.00
