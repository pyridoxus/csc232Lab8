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
		free(this->geometry);
	}

	void DataReader::constructor(const char *fileName)
	{
		fstream in;
		char temp[256];
		string header[4];
		int i = 0;
		this->dSize = this->dx = this->dy = this->dz = 0;
		in.open( fileName, ios::in | ios::binary );
		if (in.is_open())
		{
		  cout << "File " << fileName << " successfully opened." << endl;
		  for(int a = 0; a < 4; a ++)
		  {
				in.getline(temp, 256);
				header[a].append(temp);
				cout << header[a] << header[a].length() << endl;
		  }
		  if(this->getDimensions(header))
		  {
		  	if(this->dSize == sizeof(float))
		  	{
		  		this->geometry = (float *)malloc(this->geoSize);
					in.read((char *)this->geometry, this->geoSize);
					for(i = 0; i < this->geoSize >> 2; i++)
					{
						cout << "Item: " << i << " = " << geometry[i] << endl;
					}
		  	}
		  	else cout << "Data is not the size of a float" << endl;
		  }
			in.close();
		}
		else
		{
		  cout << "Error opening file " << fileName << endl;
		}
	}

	bool DataReader::getDimensions(string *header)
	{
		unsigned int loc, prevLoc, i;
		string temp[6];
		// Check that the file is the correct type...
		if(header[0].compare("DL Data Format") != 0) return false;
		if(header[1].compare(0, 10, "Dimensions") != 0) return false;
		if(header[2].compare(0, 11, "Type Binary") != 0) return false;
		if(header[3].compare(0, 12, "Grid Uniform") != 0) return false;

		i = prevLoc = 0;
		loc = header[1].find_first_of(" ");
		while((loc != string::npos) && (i < 6))
		{
			temp[i] = header[1].substr(prevLoc, loc - prevLoc);
			prevLoc = loc + 1;
			loc = header[1].find_first_of(" ", prevLoc);
			i++;
		}
		this->dx = atoi(temp[1].c_str());
		this->dy = atoi(temp[2].c_str());
		this->dz = atoi(temp[3].c_str());
		this->dSize = atoi(header[2].substr(header[2].size() - 1).c_str());
		if(this->dSize == sizeof(float))
		{
			this->geoSize = this->dx * this->dy * this->dz * this->dSize;
		}
		else return false;
		return true;
	}
} /* namespace DataFileReader */
