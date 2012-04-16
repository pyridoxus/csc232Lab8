/*
 * DataReader.h
 *
 *  Created on: Apr 15, 2012
 *      Author: pyridoxus
 */

#ifndef DATAREADER_H_
#define DATAREADER_H_
#include <string>
#include <fstream>
#include <iostream>
#include <stdlib.h>

using namespace std;

namespace DataFileReader
{

	class DataReader
	{
		public:
			DataReader(string fileName);
			DataReader(char *fileName);
			virtual ~DataReader();

		private:
			unsigned int dx, dy, dz;		// Dimensions of data file
			unsigned int dSize;				// Size of data element
			long int geoSize;			// Size of geometry array
			float *geometry;	// Array of geometry from file
			void constructor(const char *fileName);
			bool getDimensions(string *header);	// Return false if not proper format
	};

} /* namespace DataFileReader */
#endif /* DATAREADER_H_ */
