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

//	cout << dataFileName << endl;
//	cout << colorFileName << endl;
	cout << "Setting up data reader" << endl;
	dr = new DataReader(dataFileName, colorFileName);
	cout << "Building texture" << endl;
	texels = buildTexture(dr);	// texels allocated here
	cout << "Everything appears to work" << endl;
	free(texels);
	free(dr);
	return 0;
}

GLubyte *buildTexture(DataReader *dr)
{
	unsigned int i, j;
	Color c;
	texels = new GLubyte[ dr->getGeoSize() ];	// texels is global

	// For each data value
	for( j = 0, i = 0; i < dr->getGeoSize() >> 2; ++i, j+=4 )
		{
			c = dr->at(i);
			// Assign data in r,g,b texture memory
			texels[j+0] = c.r;
			texels[j+1] = c.g;
			texels[j+2] = c.b;
			texels[j+3] = c.a;
		}

	return texels;
}

//// 2D Data sampling with GLSL
//int dims[2];                      // data dimensions
//GLuint texName;                   // texture name
//GLuint shaderProgram1;            // shader program handle
//GLint TexUnit = 0;                // texture unit shader attribute
//GLint TexUnitLocation;            // texture unit shader attribute location
//
//
//// Callback function
//void myDraw();
//
//void main( int argc, char **argv )
//{
//  // Two-dimensional dataset (checkerboard pattern)
//  dims[0] = 64;
//  dims[1] = 64;
//  int size = dims[0] * dims[1];
//  float *data = new float[ size ];
//  register int i,j,k;
//  for( k = 0, i = 0; i < dims[0]; i++ )
//    for( j = 0; j < dims[1]; j++, ++k )
//       data[k] = float((((i&0x8)==0)^((j&0x8)==0)));
//
//  // Allocate memory for 2D texture
//  //   size of data * 4 for r,g,b,a components
//  // Initialize window system
//  glutInit( &argc, argv );
//  glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
//  glutInitWindowSize( 400, 300 );
//  glutCreateWindow( "Sample 2d" );
//
//  // Resolves which OpenGL extensions are supported by hardware
//  if( glewInit() != GLEW_OK )    {
//    cerr << "Error reported by glewInit" << endl;
//    exit(1);
//  }
//
//  // Orthographic projection
//  glMatrixMode( GL_PROJECTION );
//  glLoadIdentity();
//  gluOrtho2D( 0.0, float(dims[0]-1), 0.0, float(dims[1]-1) );
//  glMatrixMode( GL_MODELVIEW );
//  glLoadIdentity();
//
//  // Specify 2D RGBA texture
//  glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
//  glGenTextures( 1, &texName );
//  glBindTexture( GL_TEXTURE_2D, texName );
//  glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE );
//  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
//  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
//  glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, dims[0], dims[1], 0, GL_RGBA, GL_UNSIGNED_BYTE, texels );
//
//  // Free texture memory
//  delete[] texels;
//
//  // Create shader program
//  shaderProgram1 = CreateProgram( "sample2d.vert", "sample2d.frag" );
//
//  // Locate address of shader sampler variable
//  TexUnitLocation = glGetUniformLocation( shaderProgram1, "TexUnit" );
//
//  // Assign sampler variable value texture unit 0
//  glUniform1i( TexUnitLocation, TexUnit );
//
//  // Callbacks
//  glutDisplayFunc( myDraw );
//
//  // Main loop
//  glutMainLoop();
//}
//
//// Display callback
//void myDraw()
//{
//  // Clear the screen
//  glClearColor( 0.0, 0.0, 0.0, 1.0);
//  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
//
//  // Apply shader program
//  glUseProgram( shaderProgram1 );
//
//  // Draw polygon with data dimensions
//  glBegin( GL_POLYGON );
//  glTexCoord3f( 0.0, 0.0, 0.0 );
//  glVertex3f( 0.0, 0.0, 0.0 );
//  glTexCoord3f( 1.0, 0.0, 0.0 );
//  glVertex3f( dims[0]-1, 0.0, 0.0 );
//  glTexCoord3f( 1.0, 1.0, 0.0 );
//  glVertex3f( dims[0]-1, dims[1]-1, 0.0 );
//  glTexCoord3f( 0.0, 1.0, 0.0 );
//  glVertex3f( 0.0, dims[1]-1, 0.0 );
//  glEnd();
//
//  // Swap buffers
//  glutSwapBuffers();
//}
//
//
//sample2d.vert
//void main()
//{
//       // Output texture coordinates
//       gl_TexCoord[0]  = gl_MultiTexCoord0;
//
//       // Position in clip space
//       gl_Position   = gl_ModelViewProjectionMatrix * gl_Vertex;
//}
//
//sample2d.frag
//uniform sampler2D TexUnit;
//
//void main()
//{
//       // Texel color
//       vec3 tColor = vec3(texture2D( TexUnit, vec2(gl_TexCoord[0].st) ).rgb);
//
//       // Result
//       gl_FragColor = vec4( tColor, 1.0 );
//}
