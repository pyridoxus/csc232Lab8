/*
 * lab8.cpp
 *
 *  Created on: Apr 15, 2012
 *      Author: cmcculloch1
 */


#include "lab8.h"
using namespace DataFileReader;

int main( int argc, char *argv[] )
{
	DataReader *dr;
	char temp[256];
	string fileName(getcwd(temp, 255));
	fileName.append("/data/Elevation.bin");

	cout << fileName << endl;
	dr = new DataReader(fileName);
	free(dr);
	return 0;
}

