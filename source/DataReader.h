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
#include <float.h>
#include <vector>

namespace DataFileReader
{

	struct Color
	{
			float r;
			float g;
			float b;
			float a;
	};

	class DataReader
	{
		public:
			DataReader(std::string dataFileName, std::string colorFileName);
			DataReader(char *dataFileName, char *colorFileName);
			virtual ~DataReader();

		private:
			unsigned int dx, dy, dz;		// Dimensions of data file
			unsigned int dSize;				// Size of data element
			long int geoSize;			// Size of geometry array
			float minG, maxG;			// Geometry extremes
			float *geometry;	// Array of geometry from file
			std::vector<Color> colors;
			void dataConstructor(const char *dataFileName);
			void colorConstructor(const char *colorFileName);
			bool getDimensions(std::string *header);	// Return false if not proper format
			void buildInterpolate(void);				// Build the interpolation table
	};

} /* namespace DataFileReader */
#endif /* DATAREADER_H_ */
