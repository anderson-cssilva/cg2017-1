/*
 * In order to build this, used examples available in mycourses.
 */

//#include <GL/glut.h>
#include <GL/freeglut.h>
#include <math.h>
#include <stdio.h>	/* getch */

const float DEG2RAD = 3.14159f/180;
float xguy = 2.0;

/*
 * Draw background elements in the scene.
 */
void background()
{
	/* blue background */
	glClearColor(0.2f, 0.6f, 0.9f, 0.0f);			
  	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* grass */
	glColor3f(0.48, 0.98f, 0.0f);
	glBegin(GL_QUADS);
		glVertex3f(-2.5, -2.3, 0);
		glVertex3f(-2.5, -2, 0);
		glVertex3f(2.5, -2, 0);
		glVertex3f(2.5, -2.3, 0);
	glEnd();

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
		glBegin(GL_LINES);
			float degInRad = i*DEG2RAD;
			glVertex3f(1.8, 1.8, .0);
			glVertex3f(1.8 + cos(degInRad) * radius, 1.8 + sin(degInRad) * radius, .0);
		glEnd();
		flag = !flag;
	}
}

/*
 * Draw foreground elements in the scene.
 */
void foreground(void)
{
	if(xguy < -0.25) 
		xguy = 2.0;

	/* House body */
	glColor3f(0.85f, 0.64f, 0.12f);
	glBegin(GL_QUADS);
		glVertex3f(-1.5, -2, 0);
		glVertex3f(-1.5, .3, 0);
		glVertex3f(-.3, .3, 0);
		glVertex3f(-.3, -2, 0);
	glEnd();

	/* House roof */
	glColor3f(0.6f, 0.5f, 0.2f);
	glBegin(GL_TRIANGLE_FAN);
		glVertex3f(-1.5, .3, 0);
		glVertex3f(-0.9, .8, 0);
		glVertex3f(-.3, .3, 0);
	glEnd();

	/* House door */
	glColor3f(0.4f, 0.2f, 0.0f);
	glBegin(GL_QUADS);
		glVertex3f(-0.8, -1.962, 0.1);
		glVertex3f(-0.8, -1.1, 0.1);
		glVertex3f(-.5, -1.1, 0.1);
		glVertex3f(-.5, -1.962, 0.1);
	glEnd();

	/* House chamney */
	glColor3f(0.4f, 0.2f, 0.0f);
	glBegin(GL_QUADS);
		glVertex3f(-1.3, .3, 0);
		glVertex3f(-1.3, .8, 0);
		glVertex3f(-1.1, .8, 0);
		glVertex3f(-1.1, .3, 0);
	glEnd();

	/* guy's body */
	glPushMatrix();
	glColor3f(.0, .0, .0);
	glTranslatef(xguy, -1.74, 0.);
	glRotatef(0, 0, 0, 1);
	glRectf(-0.012f, 0.23f, 0.012f, -0.23f);
	glPopMatrix();

	/* guy's right leg */
	glPushMatrix();
	glColor3f(.0, .0, .0);
	glTranslatef(0.045 + xguy, -1.95, 0.);
	glRotatef(30, 0, 0, 1);
	glRectf(-0.012f, 0.08f, 0.012f, -0.08f);
	glPopMatrix();

	/* guy's left leg */
	glPushMatrix();
	glColor3f(.0, .0, .0);
	glTranslatef(-0.045+ xguy, -1.95, 0.);
	glRotatef(330, 0, 0, 1);
	glRectf(-0.012f, 0.08f, 0.012f, -0.08f);
	glPopMatrix();

	/* guy's right arm */
	glPushMatrix();
	glColor3f(.0, .0, .0);
	glTranslatef(0.045+ xguy, -1.66, 0.);
	glRotatef(120, 0, 0, 1);
	glRectf(-0.012f, 0.08f, 0.012f, -0.08f);
	glPopMatrix();

	/* guy's left arm */
	glPushMatrix();
	glColor3f(.0, .0, .0);
	glTranslatef(-0.045+ xguy, -1.66, 0.);
	glRotatef(240, 0, 0, 1);
	glRectf(-0.012f, 0.08f, 0.012f, -0.08f);
	glPopMatrix();

	/* guy's head */
	glBegin(GL_TRIANGLE_FAN);
	   for (int i = 0; i < 360; i++) {
		  float degInRad = i*DEG2RAD;
		  glVertex3f(cos(degInRad) * 0.1+ xguy, sin(degInRad) * 0.1 - 1.5, .0);
	   }
	glEnd();
	glColor3f(0.2f, 0.6f, 0.9f);			
	glBegin(GL_TRIANGLE_FAN);
	   for (int i = 0; i < 360; i++) {
		  float degInRad = i*DEG2RAD;
		  glVertex3f(cos(degInRad) * 0.08+ xguy, sin(degInRad) * 0.08 - 1.5, 0.008);
	   }
	glEnd();

	/* guy's mouth */
	glColor3f(0., 0., 0.);			
	glBegin(GL_LINE_LOOP);
	   	for (int i = 225; i < 315; i++) {
			float degInRad = i*DEG2RAD;
			glVertex3f(cos(degInRad) * 0.04+ xguy, sin(degInRad) * 0.04 - 1.5, 0.01);
	   	}
	glEnd();

	/* guy's end */
	glBegin(GL_POINTS);
		glVertex3f(-0.02+ xguy, -1.47, 0.01);
		glVertex3f(0.02+ xguy, -1.47, 0.01);
	glEnd();

	xguy -= 0.1;
}

void draw(void)
{
	background();
	foreground();
	glutSwapBuffers();
}

void init(void)
{
 	/* Use depth buffering for hidden surface elimination. */
	glEnable(GL_DEPTH_TEST);

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
}

void keyboard(unsigned char key, int x, int y) {
	if( key == 'q' || key == 'Q' )
		exit(0);
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
		int time = 75000000;
		while(time) {
			time--;
		}
	}
	return 0;
}
