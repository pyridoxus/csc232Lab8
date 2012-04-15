/*
 * DataReader.cpp
 *
 *  Created on: Apr 15, 2012
 *      Author: pyridoxus
 */

#include "DataReader.h"

namespace DataFileReader
{

	DataReader::DataReader(string fileName)
	{
		constructor(fileName.c_str());
	}

	DataReader::DataReader(char *fileName)
	{
		constructor(fileName);
	}

	DataReader::~DataReader()
		{
			// TODO Auto-generated destructor stub
		}

	void DataReader::constructor(const char *fileName)
	{
		fstream in;
		char s[256];
		in.open( fileName, ios::in | ios::binary );
		if (in.is_open())
		{
		  cout << "File " << fileName << " successfully opened." << endl;
			while(!in.eof())
			{
				in.getline(s,255);
				cout << s << endl;
			}
			in.close();
		}
		else
		{
		  cout << "Error opening file " << fileName << endl;
		}
	}

} /* namespace DataFileReader */
