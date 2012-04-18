#ifndef LAB8_H_
#define LAB8_H_

using namespace std;
#include "DataReader.h"
using namespace DataFileReader;
#include "GLSL.h"

#define MAX_STR                   256

GLubyte *texels;
GLubyte *buildTexture(DataReader *dr);
#endif
