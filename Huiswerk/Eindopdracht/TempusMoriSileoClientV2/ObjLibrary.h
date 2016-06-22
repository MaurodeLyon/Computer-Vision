#pragma once
#include <string>
#include <vector> 
#include "ObjModel.h"
using namespace std;
class ObjLibrary
{
public:
	ObjLibrary(){};
	~ObjLibrary(){};
	void initObject(std::string);
	void loadObjects();
};

