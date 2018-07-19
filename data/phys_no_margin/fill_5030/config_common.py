import sys
import os
import FWCore.ParameterSet.Config as cms

sys.path.append(os.path.relpath("../../../../"))

from config_base import config

#config.sector_45.cut_h_apply = True
config.sector_45.cut_h_a = -1.020
config.sector_45.cut_h_c = -0.915
config.sector_45.cut_h_si = 0.200

#config.sector_45.cut_v_apply = False
config.sector_45.cut_v_a = -1.159
config.sector_45.cut_v_c = 0.500
config.sector_45.cut_v_si = 0.150

#config.sector_56.cut_h_apply = True
config.sector_56.cut_h_a = -0.990
config.sector_56.cut_h_c = 0.714
config.sector_56.cut_h_si = 0.200

#config.sector_56.cut_v_apply = False
config.sector_56.cut_v_a = -1.143
config.sector_56.cut_v_c = 0.038
config.sector_56.cut_v_si = 0.150

config.matching.rp_L_1_F.x_min = 12.70
config.matching.rp_L_1_F.x_max = 16.50
config.matching.rp_L_1_N.x_min = 11.60
config.matching.rp_L_1_N.x_max = 14.50
config.matching.rp_R_1_N.x_min = 10.70
config.matching.rp_R_1_N.x_max = 15.50
config.matching.rp_R_1_F.x_min = 10.00
config.matching.rp_R_1_F.x_max = 14.50

config.alignment_y.rp_L_1_F.x_min = 8.50
config.alignment_y.rp_L_1_F.x_max = 12.00
config.alignment_y.rp_L_1_N.x_min = 8.50
config.alignment_y.rp_L_1_N.x_max = 12.00
config.alignment_y.rp_R_1_N.x_min = 5.00
config.alignment_y.rp_R_1_N.x_max = 11.00
config.alignment_y.rp_R_1_F.x_min = 4.00
config.alignment_y.rp_R_1_F.x_max = 11.00

config.rel_alignment_x.rp_L_1_F.x_min = 8.50
config.rel_alignment_x.rp_L_1_F.x_max = -1.00
config.rel_alignment_x.rp_L_1_N.x_min = 8.50
config.rel_alignment_x.rp_L_1_N.x_max = -1.00
config.rel_alignment_x.rp_R_1_N.x_min = 6.00
config.rel_alignment_x.rp_R_1_N.x_max = 6.80
config.rel_alignment_x.rp_R_1_F.x_min = 6.00
config.rel_alignment_x.rp_R_1_F.x_max = 6.80
