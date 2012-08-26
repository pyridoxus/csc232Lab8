//This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.
#ifndef LAB8_H_
#define LAB8_H_

using namespace std;
#include "DataReader.h"
using namespace DataFileReader;
#include "GLSL.h"

#define MAX_STR                   256
GLuint texName;                   // texture name
GLuint shaderProgram1;            // shader program handle
GLint TexUnit = 0;                // texture unit shader attribute
GLint TexUnitLocation;            // texture unit shader attribute location
GLubyte *texels;
DataReader *dr;

GLubyte *buildTexture();
// Callback function
void myDraw(void);

void setup(int argc, char *argv[]);

#endif
