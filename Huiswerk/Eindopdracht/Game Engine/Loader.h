#pragma once
class Loader
{
public:
	Loader();
	~Loader();
private:
	std::vector<int*> vaos;
	std::vector<int*> vbos;
	RawModel loadToVao(float[]);
	int createVAO();
	void storeDataInAttributeList(int, float[]);
};

