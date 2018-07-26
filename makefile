all: distributions match y_alignment rot_z_alignment copy_alignment

distributions: distributions.cc config.h stat.h fill_info.h
	g++ `root-config --libs` -lMinuit `root-config --cflags` \
		-g -O3 --std=c++14 -Wall -Wextra -Wno-attributes\
		-I$(CMSSW_RELEASE_BASE)/src \
		-L$(CMSSW_RELEASE_BASE)/lib/slc6_amd64_gcc630 \
		-lDataFormatsFWLite -lDataFormatsCommon -lDataFormatsCTPPSDetId -lFWCoreParameterSet -lFWCorePythonParameterSet \
			distributions.cc -o distributions

match: match.cc config.h stat.h alignment_classes.h
	g++ `root-config --libs` -lMinuit `root-config --cflags` \
		-g -O3 --std=c++14 -Wall -Wextra -Wno-attributes\
		-I$(CMSSW_RELEASE_BASE)/src \
		-L$(CMSSW_RELEASE_BASE)/lib/slc6_amd64_gcc630 \
		-lDataFormatsFWLite -lDataFormatsCommon -lDataFormatsCTPPSDetId -lFWCoreParameterSet -lFWCorePythonParameterSet \
			match.cc -o match

y_alignment: y_alignment.cc config.h stat.h alignment_classes.h
	g++ `root-config --libs` -lMinuit `root-config --cflags` \
		-g -O3 --std=c++14 -Wall -Wextra -Wno-attributes\
		-I$(CMSSW_RELEASE_BASE)/src \
		-L$(CMSSW_RELEASE_BASE)/lib/slc6_amd64_gcc630 \
		-lDataFormatsFWLite -lDataFormatsCommon -lDataFormatsCTPPSDetId -lFWCoreParameterSet -lFWCorePythonParameterSet \
			y_alignment.cc -o y_alignment

rot_z_alignment: rot_z_alignment.cc config.h stat.h alignment_classes.h
	g++ `root-config --libs` -lMinuit `root-config --cflags` \
		-g -O3 --std=c++14 -Wall -Wextra -Wno-attributes\
		-I$(CMSSW_RELEASE_BASE)/src \
		-L$(CMSSW_RELEASE_BASE)/lib/slc6_amd64_gcc630 \
		-lDataFormatsFWLite -lDataFormatsCommon -lDataFormatsCTPPSDetId -lFWCoreParameterSet -lFWCorePythonParameterSet \
			rot_z_alignment.cc -o rot_z_alignment

copy_alignment: copy_alignment.cc config.h alignment_classes.h
	g++ `root-config --libs` -lMinuit `root-config --cflags` \
		-g -O3 --std=c++14 -Wall -Wextra -Wno-attributes\
		-I$(CMSSW_RELEASE_BASE)/src \
		-L$(CMSSW_RELEASE_BASE)/lib/slc6_amd64_gcc630 \
		-lDataFormatsFWLite -lDataFormatsCommon -lDataFormatsCTPPSDetId -lFWCoreParameterSet -lFWCorePythonParameterSet \
			copy_alignment.cc -o copy_alignment
