all: collect_alignments tilt_fit

collect_alignments: collect_alignments.cc ../alignment_classes.h
	g++ -O3 -g -Wall -Wextra --std=c++11\
		`root-config --libs` `root-config --cflags` \
		-I"$(CMSSW_RELEASE_BASE)/src" \
		-L"$(CMSSW_RELEASE_BASE)/lib/slc6_amd64_gcc630" \
		-lDataFormatsFWLite \
		-lDataFormatsCommon \
		collect_alignments.cc -o collect_alignments

tilt_fit: tilt_fit.cc ../alignment_classes.h
	g++ `root-config --libs` `root-config --cflags` -O3 -g -Wall -Wextra --std=c++14\
		tilt_fit.cc -o tilt_fit
