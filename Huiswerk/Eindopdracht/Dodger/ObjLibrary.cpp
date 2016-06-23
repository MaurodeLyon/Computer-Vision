#include "stdafx.h"
#include "ObjLibrary.h"


std::vector<pair<string, ObjModel*>> objectLibrary;

void ObjLibrary::loadObjects()
{
	string objectName;
	ifstream ObjectFile;

	ObjectFile.open("res/models/obj_LIST.txt");	//open the .txt with object names
	while (!ObjectFile.eof())					//while not at end of file
	{
		getline(ObjectFile, objectName);		//get the line from file and parse it to objectName
		initObject(objectName);					//add object to objectLibrary
	}
	ObjectFile.close();							//close the file
}

void ObjLibrary::initObject(string file)
{
	objectLibrary.push_back(pair<string, ObjModel*>(file, new ObjModel("res/models/" + file + ".obj")));	//add object to object library
	cout << "res/models/" + file + ".obj Loaded into the objectLibrary" << endl;
}
