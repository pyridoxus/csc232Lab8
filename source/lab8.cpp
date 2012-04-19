/*
 * lab8.cpp
 *
 *  Created on: Apr 15, 2012
 *      Author: cmcculloch1
 */


#include "lab8.h"

int main( int argc, char *argv[] )
{
	char temp[256];
	string dataFileName(getcwd(temp, 255));
	string colorFileName(getcwd(temp, 255));
	dataFileName.append("/data/Elevation.bin");
	colorFileName.append("/data/rainbow.pal");

//	cout << dataFileName << endl;
//	cout << colorFileName << endl;
//	cout << "Setting up data reader" << endl;
	dr = new DataReader(dataFileName, colorFileName);
//	cout << "Building texture" << endl;
	texels = buildTexture();	// texels allocated here
//	cout << "Everything appears to work" << endl;
	setup(argc, argv);
	free(texels);
	free(dr);
	return 0;
}

GLubyte *buildTexture(void)
{
	unsigned int i, j;
	Color c;
	texels = new GLubyte[ dr->getGeoSize() ];	// texels is global

	cout.precision(6);
	// For each data value
	for( j = 0, i = 0; i < dr->getGeoSize() >> 2; ++i, j+=4 )
		{
			c = dr->at(i);
			// Assign data in r,g,b texture memory
			texels[j+0] = (GLubyte)(c.r * 256);
			texels[j+1] = (GLubyte)(c.g * 256);
			texels[j+2] = (GLubyte)(c.b * 256);
			texels[j+3] = 255;
//			cout << c.r << ", " << c.g << ", " << c.b << ", " << c.a << endl;
		}

	return texels;
}

void setup(int argc, char *argv[])
{
	char temp[256];
	string vertFileName(getcwd(temp, 255));
	string fragFileName(getcwd(temp, 255));
	vertFileName.append("/source/sample2d.vert");
	fragFileName.append("/source/sample2d.frag");

	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
	glutInitWindowSize( 400, 300 );
	glutCreateWindow( "Craig McCulloch's Lab 8" );

	// Resolves which OpenGL extensions are supported by hardware
	if( glewInit() != GLEW_OK )    {
		cerr << "Error reported by glewInit" << endl;
		exit(1);
	}

	// Orthographic projection
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluOrtho2D( 0.0, float(dr->getX()-1), 0.0, float(dr->getY()-1) );
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	// Specify 2D RGBA texture
	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
	glGenTextures( 1, &texName );
	glBindTexture( GL_TEXTURE_2D, texName );
	glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, dr->getX(), dr->getY(), 0, GL_RGBA,
			GL_UNSIGNED_BYTE, texels );

	// Create shader program
	shaderProgram1 = CreateProgram( vertFileName.c_str(), fragFileName.c_str() );

	// Locate address of shader sampler variable
	TexUnitLocation = glGetUniformLocation( shaderProgram1, "TexUnit" );

	// Assign sampler variable value texture unit 0
	glUniform1i( TexUnitLocation, TexUnit );

	// Callbacks
	glutDisplayFunc( myDraw );

	// Main loop
	glutMainLoop();

}

// Display callback
void myDraw(void)
{
  // Clear the screen
  glClearColor( 0.0, 0.0, 0.0, 1.0);
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  // Apply shader program
  glUseProgram( shaderProgram1 );

//  glColor3f(1.0, 0.5, 0.25);
//  cout << dr->getX() << endl;
//  cout << dr->getY() << endl;
  // Draw polygon with data dimensions
  glBegin( GL_POLYGON );
  glTexCoord3f( 0.0, 0.0, 0.0 );
  glVertex3f( 0.0, 0.0, 0.0 );
  glTexCoord3f( 1.0, 0.0, 0.0 );
  glVertex3f( dr->getX()-1, 0.0, 0.0 );
  glTexCoord3f( 1.0, 1.0, 0.0 );
  glVertex3f( dr->getX()-1, dr->getY()-1, 0.0 );
  glTexCoord3f( 0.0, 1.0, 0.0 );
  glVertex3f( 0.0, dr->getY()-1, 0.0 );
  glEnd();

  // Swap buffers
  glutSwapBuffers();
}
