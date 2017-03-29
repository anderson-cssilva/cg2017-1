/*
 * In order to build this, used examples available in mycourses.
 */

//#include <GL/glut.h>
#include <GL/freeglut.h>
#include <math.h>
#include <stdio.h>	/* getch */


/* cg stuff */
#include <Cg/cg.h>
#include <Cg/cgGL.h>		// we will be using CG with OpenGL

CGcontext	Cg_context;		// Cg context (container)
CGprofile	Cg_vprofile;	// Cg vertex profile
CGprofile	Cg_fprofile;	// Cg fragment profile
CGprogram	Cg_vprogram;	// Cg vertex program
CGprogram	Cg_fprogram;	// Cg fragment program
CGparameter Cg_par;			// Cg program parameter
CGparameter Cg_par_trans;	// Cg program parameter (matrix used for transformation)
CGparameter Cg_par_gap;		// Cg program parameter (gap between parallel textures)
CGparameter Cg_par_counter;	// Cg program parameter (counter)
GLfloat		Gap = 0.1f;		// gap between our parallel textures
GLfloat		counter = 0.0f;	// value that always increments for trigonomic functions of Cg progrms

bool		Cg_v = false;	// Cg vertex program enabled
bool		Cg_f = false;	// Cg fragment program enabled

GLuint loadBMP(const char * imagepath) 
{
	// Data read from the header of the BMP file
	unsigned char header[54]; // Each BMP file begins by a 54-bytes header
	unsigned int dataPos;     // Position in the file where the actual data begins
	unsigned int width, height;
	unsigned int imageSize;   // = width*height*3
	// Actual RGB data
	unsigned char * data;

	// Open the file
	FILE * file = fopen(imagepath,"rb");
	if (!file) {
		printf("%s: Image could not be opened\n", imagepath); 
		exit(1);
	}

	if ( fread(header, 1, 54, file) != 54 ) {  // If not 54 bytes read : problem
		printf("%s: Not a correct BMP file\n", imagepath);
		exit(1);
	}

	if ( header[0]!='B' || header[1]!='M' ){
		printf("%s: Not a correct BMP file\n", imagepath);
		exit(1);
	}

	// Read ints from the byte array
	dataPos    = *(int*)&(header[0x0A]);
	imageSize  = *(int*)&(header[0x22]);
	width      = *(int*)&(header[0x12]);
	height     = *(int*)&(header[0x16]);
	
	// Some BMP files are misformatted, guess missing information
	if (imageSize == 0)
		imageSize = width*height*3; // 3 : one byte for each Red, Green and Blue component
	if (dataPos == 0)
		dataPos = 54; // The BMP header is done that way

	// Create a buffer
	data = new unsigned char [imageSize];
	
	// Read the actual data from the file into the buffer
	fread(data,1,imageSize,file);
	
	//Everything is in memory now, the file can be closed
	fclose(file);

	// Create one OpenGL texture
	GLuint textureID;
	glGenTextures(1, &textureID);
	
	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, textureID);
	// Give the image to OpenGL
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
	
	//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
	//gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);

	delete data;
	return textureID;
}


bool CheckCgError(const char *situation)
{
	CGerror error;
	const char *string = cgGetLastErrorString(&error);

	if (error != CG_NO_ERROR) {
		printf("CG Error: %s - %s\n", situation, string);
		return false;
	}
	return true;
}

/*
 * Draw background elements in the scene.
 */
GLuint back_tex;
GLuint house_tex;
GLuint roof_tex;
GLuint chi_tex;
GLuint door_tex;
GLuint man_tex;
GLuint smoke_tex;

const float DEG2RAD = 3.14159f/180;
float xguy = 2.0;
float guy_scale = 0.0;
float ypos_smoke = 0.0;

void background()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer

	/* sun */
	glColor3f(1., 1., 0.0f);
	glBegin(GL_TRIANGLE_FAN);
	   for (int i = 0; i < 360; i++) {
		  float degInRad = i*DEG2RAD;
		  glVertex3f(1.8 + cos(degInRad) * 0.2, 1.8 + sin(degInRad) * 0.2, .0);
	   }
	glEnd();

   /* sun rays */
	int flag = 0;
	float radius;
	for(float i = 0.; i < 360.; i+= 51.42/2.0) {
		if(!flag) radius = 0.28;
		else radius = 0.35;
		glColor3f(1., 1., 0.0f);
		glBegin(GL_LINES);
			float degInRad = i*DEG2RAD;
			glVertex3f(1.8, 1.8, .0);
			glVertex3f(1.8 + cos(degInRad) * radius, 1.8 + sin(degInRad) * radius, 0.);
		glEnd();
		flag = !flag;
	}
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, back_tex);
	glColor4f(1.0, 1.0, 1.0, 1.0); // reset gl color
	glBegin( GL_QUADS );
	glTexCoord2d(0.0,0.0); glVertex3d(-2.7, -2.6, -1.);
	glTexCoord2d(0.0,1.0); glVertex3d(-2.7, +2.6, -1.);
	glTexCoord2d(1.0,1.0); glVertex3d(+2.7, +2.6, -1.);
	glTexCoord2d(1.0,0.0); glVertex3d(+2.7, -2.6, -1.);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

/* Draws the house */
void house() 
{
	/* house body */
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, house_tex);
	glColor4f(1.0, 1.0, 1.0, 1.0);
	glBegin( GL_QUADS );
	glTexCoord2d(0.0,0.0); glVertex3d(-1.5, -2., 0.);
	glTexCoord2d(0.0,1.0); glVertex3d(-1.5, .3, 0.);
	glTexCoord2d(1.0,1.0); glVertex3d(-.3, .3, 0.);
	glTexCoord2d(1.0,0.0); glVertex3d(-.3, -2, 0.);
	glEnd();

	/* house roof */
	glBindTexture(GL_TEXTURE_2D, roof_tex);
	glColor4f(1.0, 1.0, 1.0, 1.0); // reset gl color
	glBegin(GL_TRIANGLE_FAN);
	glTexCoord2d(0.0,0.0); glVertex3d(-1.5, .3, 0.);
	glTexCoord2d(0.0,1.0); glVertex3d(-0.9, .8, 0.);
	glTexCoord2d(1.0,0.0); glVertex3d(-.3, .3, 0.);
	glEnd();

	/* House door */
	glBindTexture(GL_TEXTURE_2D, door_tex);
	glColor4f(1.0, 1.0, 1.0, 1.0); // reset gl color
	glBegin( GL_QUADS );
	glTexCoord2d(0.0,0.0); glVertex3f(-0.8, -1.962, 0.1);
	glTexCoord2d(0.0,1.0); glVertex3f(-0.8, -1.1, 0.1);
	glTexCoord2d(1.0,1.0); glVertex3f(-.5, -1.1, 0.1);
	glTexCoord2d(1.0,0.0); glVertex3f(-.5, -1.962, 0.1);
	glEnd();

	/* chimney */
	glBindTexture(GL_TEXTURE_2D, chi_tex);
	glColor4f(1.0, 1.0, 1.0, 1.0); // reset gl color
	glBegin( GL_QUADS );
	glTexCoord2d(0.0,0.0); glVertex3f(-1.3, .3, -0.01);
	glTexCoord2d(0.0,1.0); glVertex3f(-1.3, .8, -0.01);
	glTexCoord2d(1.0,1.0); glVertex3f(-1.1, .8, -0.01);
	glTexCoord2d(1.0,0.0); glVertex3f(-1.1, .3, -0.01);
	glEnd();

	/* smoke */
	if(ypos_smoke > 1.2)
		ypos_smoke = 0.;

	glBindTexture(GL_TEXTURE_2D, smoke_tex);
	glColor4f(1.0, 1.0, 1.0, 1.0); // reset gl color
	glBegin( GL_QUADS );
	glTexCoord2d(0.0,0.0); glVertex3f(-1.15, .8 + ypos_smoke, -0.01);
	glTexCoord2d(0.0,1.0); glVertex3f(-1.15, 1. + ypos_smoke, -0.01);
	glTexCoord2d(1.0,1.0); glVertex3f(-1.12, 1. + ypos_smoke, -0.01);
	glTexCoord2d(1.0,0.0); glVertex3f(-1.12, .8 + ypos_smoke, -0.01);
	glEnd();

	glColor4f(1.0, 1.0, 1.0, 1.0); // reset gl color
	glBegin( GL_QUADS );
	glTexCoord2d(0.0,0.0); glVertex3f(-1.21, .7 + ypos_smoke, -0.01);
	glTexCoord2d(0.0,1.0); glVertex3f(-1.21, .9 + ypos_smoke, -0.01);
	glTexCoord2d(1.0,1.0); glVertex3f(-1.18, .9 + ypos_smoke, -0.01);
	glTexCoord2d(1.0,0.0); glVertex3f(-1.18, .7 + ypos_smoke, -0.01);
	glEnd();

	glColor4f(1.0, 1.0, 1.0, 1.0); // reset gl color
	glBegin( GL_QUADS );
	glTexCoord2d(0.0,0.0); glVertex3f(-1.27, .8 + ypos_smoke, -0.01);
	glTexCoord2d(0.0,1.0); glVertex3f(-1.27, .99 + ypos_smoke, -0.01);
	glTexCoord2d(1.0,1.0); glVertex3f(-1.24, .99 + ypos_smoke, -0.01);
	glTexCoord2d(1.0,0.0); glVertex3f(-1.24, .8 + ypos_smoke, -0.01);
	glEnd();

	ypos_smoke += 0.01;

	glDisable(GL_TEXTURE_2D);
}

/* Draws the guy */
void guy()
{
	if(xguy < -0.21) {
		xguy = 2.0;
		guy_scale = 0;
	}

	if(guy_scale > 0.38)
		guy_scale = 0.38;

	glDepthMask(GL_FALSE);
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, man_tex);
	glColor4f(1.0, 1.0, 1.0, 1.0); // reset gl color

	glBegin(GL_QUADS);
	glTexCoord2d(0.0,0.0); glVertex3f(xguy-0.1, -2.0, 0.01);
	glTexCoord2d(0.0,1.0); glVertex3f(xguy-0.1, -1.5+guy_scale, 0.01);
	glTexCoord2d(1.0,1.0); glVertex3f(xguy+0.1, -1.5+guy_scale, 0.01);
	glTexCoord2d(1.0,0.0); glVertex3f(xguy+0.1, -2.0, 0.01);
	glEnd();

	glDepthMask(GL_TRUE);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

	xguy -= 0.007;
	guy_scale += 0.00125;
}

/*
 * Draw foreground elements in the scene.
 */
void foreground(void)
{
	house();
	guy();
}

void draw(void)
{
	/* CG stuff */
	cgGLSetStateMatrixParameter(Cg_par_trans, CG_GL_MODELVIEW_PROJECTION_MATRIX, CG_GL_MATRIX_IDENTITY);
	if(!CheckCgError("vertex program modelViewProj setting"))
		return;

	Gap += 0.01f;
	if (Gap > 1.0f)
		Gap -= 1.0f;

	cgSetParameter2f(Cg_par_gap, Gap, 0);
	if(!CheckCgError("vertex gap parameter setting"))
		return ;

	counter += 0.1f;
	cgGLSetParameter1f(Cg_par_counter, counter);
	if(!CheckCgError("fragment counter parameter setting"))
		return ;

	cgUpdateProgramParameters(Cg_vprogram);
	cgUpdateProgramParameters(Cg_fprogram);

	
	/* draw */
	background();
	foreground();

	glutSwapBuffers();
}

void init(void)
{
	back_tex = loadBMP("./data/xp.bmp");
	house_tex = loadBMP("./data/brick.bmp");
	roof_tex = loadBMP("./data/brickDark.bmp");
	chi_tex = loadBMP("./data/chi.bmp");
	door_tex = loadBMP("./data/door.bmp");
	man_tex = loadBMP("./data/man.bmp");
	smoke_tex = loadBMP("./data/grey.bmp");

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup

	 	/* Use depth buffering for hidden surface elimination. */
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	/* Setup the view of the cube. */
	glMatrixMode(GL_PROJECTION);
	gluPerspective( /* field of view in degree */ 40.0,
    /* aspect ratio */ 1.0,
    /* Z near */ 1.0, /* Z far */ 10.0);

	glMatrixMode(GL_MODELVIEW);
	gluLookAt(0.0, 0.0, 5.0,  /* eye is at (0,0,5) */
    	0.0, 0.0, 0.0,      /* center is at (0,0,0) */
    	0.0, 1.0, 0.0);      /* up is in positive Y direction */

	/* Adjust cube position to be asthetic angle. */
	glTranslatef(0.0, 0.0, -1.0);
	glRotatef(0, 1.0, 0.0, 0.0);
	glRotatef(0, 0.0, 0.0, 1.0);

	/* cg stuff */

	Cg_context = cgCreateContext();
	if(!CheckCgError("context creation"))
		return;
	cgGLSetDebugMode(CG_FALSE);
	cgSetParameterSettingMode(Cg_context, CG_DEFERRED_PARAMETER_SETTING);

	// load vertex Cg program

	Cg_vprofile = cgGLGetLatestProfile(CG_GL_VERTEX);
	cgGLSetOptimalOptions(Cg_vprofile);
	if(!CheckCgError("vertex profile selection"))
		return;
	Cg_vprogram = cgCreateProgramFromFile(Cg_context, CG_SOURCE, "vertex.cg", Cg_vprofile, "vertex_main", NULL);
	if(!CheckCgError("vertex program creation from file"))
		return;
	cgGLLoadProgram(Cg_vprogram);
	if(!CheckCgError("vertex program loading"))
		return;

	// retrieve handles of vertex uniform variables

	Cg_par_gap = cgGetNamedParameter(Cg_vprogram, "Gap");
	if(!CheckCgError("vertex gap parameter retrieving"))
		return;
	cgSetParameter2f(Cg_par_gap, Gap, 0);
	if(!CheckCgError("vertex gap parameter setting"))
		return;

	Cg_par_trans = cgGetNamedParameter(Cg_vprogram, "modelViewProj");
	if(!CheckCgError("vertex modelViewProj parameter retrieving"))
		return;

	// load fragment Cg program

	Cg_fprofile = cgGLGetLatestProfile(CG_GL_FRAGMENT);
	cgGLSetOptimalOptions(Cg_fprofile);
	if(!CheckCgError("fragment profile selection"))
		return;
	Cg_fprogram = cgCreateProgramFromFile(Cg_context, CG_SOURCE, "fragment.cg", Cg_fprofile, "fragment_main", NULL);
	if(!CheckCgError("fragment program creation from file"))
		return;
	cgGLLoadProgram(Cg_fprogram);
	if(!CheckCgError("fragment program loading"))
		return;

	// retrieve handles of fragment uniform variables

	Cg_par = cgGetNamedParameter(Cg_fprogram, "decal");
	if(!CheckCgError("fragment decal parameter retrieving"))
		return;
	cgGLSetTextureParameter(Cg_par, 0);
	if(!CheckCgError("fragment decal parameter setting"))
		return;
	Cg_par_counter = cgGetNamedParameter(Cg_fprogram, "counter");
	if(!CheckCgError("fragment counter parameter retrieving"))
		return;
	cgGLSetParameter1f(Cg_par_counter, counter);
	if(!CheckCgError("fragment counter parameter setting"))
		return;

	//cgGLBindProgram(Cg_vprogram);
	if(!CheckCgError("vertex program binding"))
		return ;

	//cgGLEnableProfile(Cg_vprofile);
	if(!CheckCgError("vertex profile enabling"))
		return ;
	Cg_v = true;

	//cgGLBindProgram(Cg_fprogram);
	if(!CheckCgError("fragment program binding"))
		return ;

	//cgGLEnableProfile(Cg_fprofile);
	if(!CheckCgError("fragment profile enabling"))
		return ;
	Cg_f = true;
}

void keyboard(unsigned char key, int x, int y) {
	if( key == 'q' || key == 'Q' ) {
		cgDestroyProgram(Cg_vprogram);
		cgDestroyProgram(Cg_fprogram);
		cgDestroyContext(Cg_context);
		exit(0);
	}
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
	glutCreateWindow("Assignment 3 - Part2 - Home Scene");
	glutDisplayFunc(draw);
	glutKeyboardFunc(keyboard);
	init();

	while(1) {
		glutMainLoopEvent();
		glutPostRedisplay();
	}

	return 0;
}
