/*
 * lab8.cpp
 *
 *  Created on: Apr 15, 2012
 *      Author: cmcculloch1
 */


#include "lab8.h"

int main( int argc, char *argv[] )
{
	DataReader *dr;
	char temp[256];
	string dataFileName(getcwd(temp, 255));
	string colorFileName(getcwd(temp, 255));
	dataFileName.append("/data/Elevation.bin");
	colorFileName.append("/data/livingston.pal");

	cout << dataFileName << endl;
	cout << colorFileName << endl;
	dr = new DataReader(dataFileName, colorFileName);
	free(dr);
	return 0;
}

