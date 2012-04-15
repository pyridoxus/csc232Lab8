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
			void constructor(const char *fileName);
	};

} /* namespace DataFileReader */
#endif /* DATAREADER_H_ */
