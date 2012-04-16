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
	dr = new DataReader(dataFileName, colorFileName);
	free(dr);
	return 0;
}

//// 2D Data sampling with GLSL
//
//#include <iostream>
//#include <fstream>
//using namespace std;
//#include <GL/glew.h>
//#include <GL/glut.h>
//
//#define MAX_STR                   256
//
//int dims[2];                      // data dimensions
//GLuint texName;                   // texture name
//GLuint shaderProgram1;            // shader program handle
//GLint TexUnit = 0;                // texture unit shader attribute
//GLint TexUnitLocation;            // texture unit shader attribute location
//
//// GLSL API functions
//GLuint CreateProgram( string, string );
//GLuint CreateShader( GLenum, string );
//void CheckGlErrors( const char * );
//int LinkProgram( GLuint );
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
//  GLubyte *texels = new GLubyte[ size*4 ];
//
//  // For each data value
//  for( j = 0, i = 0; i < size; ++i, j+=4 )
//    {
//      // Convert data range to unsigned bytes (0 to 255)
//      GLubyte c = GLubyte( data[i] * 255.0 );
//      c = c < 0 ? 0 : c;
//      c = c > 255 ? 255 : c;
//
//      // Assign data in r,g,b texture memory (alpha constant)
//      texels[j+0] = GLubyte( c );
//      texels[j+1] = GLubyte( c );
//      texels[j+2] = GLubyte( c );
//      texels[j+3] = 255;
//    }
//
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
//// Function to create shader program
//GLuint CreateProgram( string vertfname, string fragfname )
//{
//  // Create vertex and fragment shaders
//  GLuint vertShader = CreateShader( GL_VERTEX_SHADER,   vertfname );
//  GLuint fragShader = CreateShader( GL_FRAGMENT_SHADER, fragfname );
//
//  // Attach shaders to shader program
//  GLuint program = glCreateProgram();
//  glAttachShader( program, vertShader );
//  glAttachShader( program, fragShader );
//
//  // Link shader program
//  LinkProgram( program );
//
//  // Return handle to program
//  return program;
//}
//
//// Function to create shader object
//GLuint CreateShader( GLenum type, string fname )
//{
//  // Create shader object
//  GLuint shader = glCreateShader( type );
//
//  // Read shader source file
//  ifstream is;
//       is.open( fname.c_str(), ios::in | ios::binary );
//  long begin = is.tellg();              // size of file plus a byte for null termination
//  is.seekg( 0, ios::end );
//  long end = is.tellg();
//       int bsize = end-begin+1;
//  is.seekg( 0, ios::beg );
//  char *str = new char[ bsize ];        // allocate read all bytes in file
//  is.read( str, bsize-1 );
//       str[ bsize-1] = '\0';
//       is.close();
//
//  // Load shader source into shader object
//  glShaderSource( shader, 1, (const GLchar **)&str, NULL );
//  if( str ) delete[] str;
//
//  // Compile shader object and check for errors
//  glCompileShader( shader );
//  CheckGlErrors( "Compile Shader:");
//  int status, infoLogLen;
//  glGetShaderiv( shader, GL_COMPILE_STATUS, &status );
//  if( !status )
//    {
//      cerr << "Shader compilation error: " << fname.c_str() << endl;
//      glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &infoLogLen );
//      if( infoLogLen > 0)
//        {
//          GLchar *infoLog = new GLchar[infoLogLen+1];
//          glGetShaderInfoLog( shader, infoLogLen, NULL, infoLog);
//          infoLog[infoLogLen] = '\0';
//          cerr << infoLog << endl;
//          delete[] infoLog;
//        }
//      glDeleteShader( shader );
//      exit(1);
//    }
//  CheckGlErrors("LoadShader:Compile 2");
//
//  // Return handle to shader object
//  return shader;
//}
//
//// Check OpenGL errors (from Graphics Shaders textbook)
//void CheckGlErrors( const char* caller )
//{
//  unsigned int gle = glGetError();
//
//  if( gle != GL_NO_ERROR )
//    {
//      fprintf( stderr, "GL Error discovered from caller %s: ", caller );
//      switch (gle)
//        {
//        case GL_INVALID_ENUM:
//          fprintf( stderr, "Invalid enum.\n" );
//          break;
//        case GL_INVALID_VALUE:
//          fprintf( stderr, "Invalid value.\n" );
//          break;
//        case GL_INVALID_OPERATION:
//          fprintf( stderr, "Invalid Operation.\n" );
//          break;
//        case GL_STACK_OVERFLOW:
//          fprintf( stderr, "Stack overflow.\n" );
//          break;
//        case GL_STACK_UNDERFLOW:
//          fprintf(stderr, "Stack underflow.\n" );
//          break;
//        case GL_OUT_OF_MEMORY:
//          fprintf( stderr, "Out of memory.\n" );
//          break;
//        }
//      return;
//    }
//}
//
//// Link shader program (from Graphics Shaders textbook)
//int LinkProgram( GLuint program )
//{
//  glLinkProgram( program );
//  CheckGlErrors("LoadShader:Link 1");
//
//  GLchar* infoLog;
//  GLint infoLogLen;
//  GLint linkStatus;
//  glGetProgramiv( program, GL_LINK_STATUS, &linkStatus );
//  CheckGlErrors("LoadShader:Link 2");
//
//  if( linkStatus == 0 )
//    {
//      glGetProgramiv( program, GL_INFO_LOG_LENGTH, &infoLogLen );
//      cerr << "Failed to link program -- Info Log Length = " << infoLogLen << endl;
//      if( infoLogLen > 0 )
//        {
//          infoLog = new GLchar[infoLogLen+1];
//          glGetProgramInfoLog( program, infoLogLen, NULL, infoLog );
//          infoLog[infoLogLen] = '\0';
//          cerr << "Info Log: " << infoLog << endl;
//          delete[] infoLog;
//        }
//      glDeleteProgram( program );
//      return 0;
//    }
//  return 1;
//};
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
