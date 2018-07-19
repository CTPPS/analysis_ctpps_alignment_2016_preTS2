struct FillInfo
{
	unsigned int fillNumber;
	bool margin;
	unsigned int runMin, runMax;
	string alignmentTag;

	FillInfo(unsigned int _fn=0, bool _m=false, unsigned int _rmin=0, unsigned int _rmax=0, const string &at="") :
		fillNumber(_fn), margin(_m), runMin(_rmin), runMax(_rmax), alignmentTag(at)
	{
	}
};

//----------------------------------------------------------------------------------------------------

struct FillInfoCollection : public vector<FillInfo> 
{
	FillInfo FindByFill(unsigned int fill, bool margin) const
	{
		for (const auto it : *this)
		{
			if (it.fillNumber == fill && it.margin == margin)
				return it;
		}

		printf("ERROR in FillInfoCollection::FindByFill > fill %u not found in the collection.\n", fill);
		exit(1);

		return FillInfo();
	}

	FillInfo FindByRun(unsigned int run) const
	{
		for (const auto it : *this)
		{
			if (it.runMin <= run && it.runMax >= run)
				return it;
		}

		printf("ERROR in FillInfoCollection::FindByRun > run %u not found in the collection.\n", run);
		exit(1);

		return FillInfo();
	}
};

//----------------------------------------------------------------------------------------------------

FillInfoCollection fillInfoCollection;

//----------------------------------------------------------------------------------------------------

void InitFillInfoCollection()
{
	fillInfoCollection.push_back(FillInfo(4947, true, 273725, 273730, "period1_physics_margin/fill_4947/2017_01_17"));
	fillInfoCollection.push_back(FillInfo(4953, true, 274094, 274094, "period1_physics_margin/fill_4953/2017_01_17"));
	fillInfoCollection.push_back(FillInfo(4961, true, 274198, 274200, "period1_physics_margin/fill_4961/2017_01_17"));
	fillInfoCollection.push_back(FillInfo(4964, true, 274240, 274241, "period1_physics_margin/fill_4964/2017_01_17"));
	fillInfoCollection.push_back(FillInfo(4964, false, 274244, 274244, "period1_physics/fill_4964/2017_01_17"));
	fillInfoCollection.push_back(FillInfo(4976, true, 274282, 274286, "period1_physics_margin/fill_4976/2017_01_17"));
	fillInfoCollection.push_back(FillInfo(4985, false, 274387, 274388, "period1_physics/fill_4985/2017_01_17"));
	fillInfoCollection.push_back(FillInfo(4988, false, 274420, 274422, "period1_physics/fill_4988/2017_01_17"));
	fillInfoCollection.push_back(FillInfo(4990, false, 274440, 274443, "period1_physics/fill_4990/2017_01_17"));
	fillInfoCollection.push_back(FillInfo(5005, false, 274954, 274959, "period1_physics/fill_5005/2017_01_17"));
	fillInfoCollection.push_back(FillInfo(5013, false, 274966, 274971, "period1_physics/fill_5013/2017_01_17"));
	fillInfoCollection.push_back(FillInfo(5017, false, 274998, 275001, "period1_physics/fill_5017/2017_01_17"));
	fillInfoCollection.push_back(FillInfo(5020, false, 275059, 275074, "period1_physics/fill_5020/2017_01_17"));
	fillInfoCollection.push_back(FillInfo(5021, false, 275124, 275125, "period1_physics/fill_5021/2017_01_17"));
	fillInfoCollection.push_back(FillInfo(5024, false, 275282, 275293, "period1_physics/fill_5024/2017_01_17"));
	fillInfoCollection.push_back(FillInfo(5026, false, 275309, 275311, "period1_physics/fill_5026/2017_01_17"));
	fillInfoCollection.push_back(FillInfo(5027, false, 275319, 275338, "period1_physics/fill_5027/2017_01_17"));
	fillInfoCollection.push_back(FillInfo(5028, false, 275344, 275345, "period1_physics/fill_5028/2017_01_17"));
	fillInfoCollection.push_back(FillInfo(5029, false, 275370, 275371, "period1_physics/fill_5029/2017_01_17"));
	fillInfoCollection.push_back(FillInfo(5030, false, 275375, 275376, "period1_physics/fill_5030/2017_01_17"));
	fillInfoCollection.push_back(FillInfo(5038, false, 275656, 275659, "period1_physics/fill_5038/2017_01_17"));
	fillInfoCollection.push_back(FillInfo(5043, false, 275757, 275783, "period1_physics/fill_5043/2017_01_17"));
	fillInfoCollection.push_back(FillInfo(5045, false, 275828, 275847, "period1_physics/fill_5045/2017_01_17"));
	fillInfoCollection.push_back(FillInfo(5048, false, 275886, 275890, "period1_physics/fill_5048/2017_01_17"));
	fillInfoCollection.push_back(FillInfo(5052, false, 275911, 275931, "period1_physics/fill_5052/2017_01_17"));

	fillInfoCollection.push_back(FillInfo(5261, false, 279760, 279767, "period1_physics/fill_5261/2017_01_17"));
	fillInfoCollection.push_back(FillInfo(5264, false, 279794, 279794, "period1_physics/fill_5264/2017_01_17"));
	fillInfoCollection.push_back(FillInfo(5265, false, 279823, 279823, "period1_physics/fill_5265/2017_01_17"));
	fillInfoCollection.push_back(FillInfo(5266, false, 279841, 279841, "period1_physics/fill_5266/2017_01_17"));
	fillInfoCollection.push_back(FillInfo(5267, false, 279844, 279865, "period1_physics/fill_5267/2017_01_17"));
	fillInfoCollection.push_back(FillInfo(5274, false, 279931, 279931, "period1_physics/fill_5274/2017_01_17"));
	fillInfoCollection.push_back(FillInfo(5275, false, 279966, 279966, "period1_physics/fill_5275/2017_01_17"));
	fillInfoCollection.push_back(FillInfo(5276, false, 279975, 279975, "period1_physics/fill_5276/2017_01_17"));
	fillInfoCollection.push_back(FillInfo(5277, false, 279993, 280024, "period1_physics/fill_5277/2017_01_17"));
	fillInfoCollection.push_back(FillInfo(5279, false, 280187, 280194, "period1_physics/fill_5279/2017_01_17"));
	fillInfoCollection.push_back(FillInfo(5287, false, 280327, 280364, "period1_physics/fill_5287/2017_01_17"));
	fillInfoCollection.push_back(FillInfo(5288, false, 280383, 280385, "period1_physics/fill_5288/2017_01_17"));
}
