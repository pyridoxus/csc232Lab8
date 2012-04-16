/*
 * DataReader.cpp
 *
 *  Created on: Apr 15, 2012
 *      Author: pyridoxus
 */

#include "DataReader.h"
using namespace std;

namespace DataFileReader
{

	DataReader::DataReader(string dataFileName, string colorFileName)
	{
		dataConstructor(dataFileName.c_str());
		colorConstructor(colorFileName.c_str());
	}

	DataReader::DataReader(char *dataFileName, char *colorFileName)
	{
		dataConstructor(dataFileName);
		colorConstructor(colorFileName);
	}

	DataReader::~DataReader()
	{
		free(this->geometry);
	}

	void DataReader::dataConstructor(const char *dataFileName)
	{
		fstream in;
		char temp[256];
		string header[4];
		this->dSize = this->dx = this->dy = this->dz = 0;
		in.open( dataFileName, ios::in | ios::binary );
		if (in.is_open())
		{
//		  cout << "File " << dataFileName << " successfully opened." << endl;
		  for(int a = 0; a < 4; a ++)
		  {
				in.getline(temp, 256);
				header[a].append(temp);
//				cout << header[a] << header[a].length() << endl;
		  }
		  if(this->getDimensions(header))
		  {
				this->geometry = (float *)malloc(this->geoSize);
				in.read((char *)this->geometry, this->geoSize);
				buildInterpolate();		  }
			in.close();
		}
		else
		{
		  cout << "Error opening file " << dataFileName << endl;
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

	void DataReader::buildInterpolate(void)
	{
		this->maxG = FLT_MIN;
		this->minG = FLT_MAX;
		for(int i = 0; i < this->geoSize >> 2; i++)
		{
			this->geometry[i] < this->minG ? this->minG = this->geometry[i] : 0;
			this->geometry[i] > this->maxG ? this->maxG = this->geometry[i] : 0;
		}
//		cout << "Min: " << this->minG << endl;
//		cout << "Max: " << this->maxG << endl;
		//(inVal – inMin) / (inMax – inMin) = (outVal – outMin) / (outMax – outMin)
		return;
	}

	void DataReader::colorConstructor(const char *colorFileName)
	{
		fstream in;
		char temp[256];
		string s;
		string t[4];
		unsigned int i, loc, prevLoc;
		DataFileReader::Color c;
		in.open( colorFileName, ios::in | ios::binary );
		if(in.is_open())
		{
			while(!in.eof())
			{
				in.getline(temp, 256);
				s.assign(temp);
				i = prevLoc = 0;
				loc = s.find_first_of(" ");
				while((loc != string::npos) && (i < 4))
				{
					t[i] = s.substr(prevLoc, loc - prevLoc);
					prevLoc = loc + 1;
					loc = s.find_first_of(" ", prevLoc);
					i++;
				}
				c.r = atof(t[0].c_str());
				c.g = atof(t[1].c_str());
				c.b = atof(t[2].c_str());
				c.a = atof(t[3].c_str());
				this->colors.push_back(c);
			}
			in.close();
		}
//		cout.precision(6);
//		for(unsigned int d = 0; d < this->colors.size(); d++)
//		{
//			cout << this->colors[d].r << " ";
//			cout << this->colors[d].g << " ";
//			cout << this->colors[d].b << " ";
//			cout << this->colors[d].a << " " << endl;
//		}
		return;
	}

} /* namespace DataFileReader */
