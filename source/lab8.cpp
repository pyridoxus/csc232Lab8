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
	char fileName[] = "../data/buckyballs.bin";

	dr = new DataReader(fileName);
	return 0;
}

