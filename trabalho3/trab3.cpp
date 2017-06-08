#include <GL/freeglut.h>
#include <stdlib.h>
#include <math.h>

#include "bibutil.h"

//angle of rotation
float xpos = 0, ypos = 0, zpos = 0, xrot = 0, yrot = 0, angle = 0.0;

float cRadius = 10.0f; // our radius distance from our character

float lastx, lasty;

//positions of the cubes
float positionz[10];
float positiony[10];
float positionx[10];

// Apontador para objeto
OBJ *objeto;

void figurespositions(void) { //set the positions of the figures

	for (int i = 0; i<10; i++)
	{
		positionz[i] = rand() % 5 + 1;
		positiony[i] = rand() % 5 + 1;
		positionx[i] = rand() % 5 + 1;
	}
}

//draw the cube -x,-y,-z
void cube(void) {
	for (int i = 0; i<10 - 1; i++)
	{
		glPushMatrix();
		glTranslated(-positionx[i + 1] * 10, -positiony[i + 1] * 10, -positionz[i + 1] * 10); //translate the cube
		glutSolidCube(2); //draw the cube
		glPopMatrix();
	}
}

//draw the sphere -x,-y,z
void sphere(void) {
	for (int i = 0; i<10 - 1; i++)
	{
    	glPushMatrix();
        glTranslated(-positionx[i + 1] * 10, -positiony[i + 1] * 10, positionz[i + 1] * 10);
        glutSolidSphere(1,50,50);
    	glPopMatrix(); 
	}
}

//draw the cone -x,y,-z
void cone(void) {
	for (int i = 0; i<10 - 1; i++)
	{
    	glPushMatrix();
        glTranslated(-positionx[i + 1] * 10,  positiony[i + 1] * 10, -positionz[i + 1] * 10);
        glRotated(65, -1.0, 0.0, 0.0);
        glutSolidCone(1, 2, 50, 50);
    	glPopMatrix(); 
	}
}

//draw the torus x,-y,-z
void torus(void) {
	for (int i = 0; i<10 - 1; i++)
	{
    	glPushMatrix();
        glTranslated(positionx[i + 1] * 10,  -positiony[i + 1] * 10, -positionz[i + 1] * 10);
        glRotated(-10, 1.0, 0.0, 0.0);
        glutSolidTorus(0.4, 0.8, 10, 50);
    	glPopMatrix(); 
	}
}

//draw the dodecahedron x,y,-z
void dodecahedron(void) {
	for (int i = 0; i<10 - 1; i++)
	{
    	glPushMatrix();
        glTranslated(positionx[i + 1] * 10,  positiony[i + 1] * 10, -positionz[i + 1] * 10);
        glutSolidDodecahedron();
    	glPopMatrix(); 
	}
}

//draw the octahedron -x,y,z
void octahedron(void) {
	for (int i = 0; i<10 - 1; i++)
	{
    	glPushMatrix();
        glTranslated(-positionx[i + 1] * 10,  positiony[i + 1] * 10, positionz[i + 1] * 10);
        glutSolidOctahedron();
    	glPopMatrix(); 
	}
}

//draw the tetrahedron x,-y,z
void tetrahedron(void) {
	for (int i = 0; i<10 - 1; i++)
	{
    	glPushMatrix();
        glTranslated(positionx[i + 1] * 10,  -positiony[i + 1] * 10, positionz[i + 1] * 10);
        glutSolidTetrahedron();
    	glPopMatrix(); 
	}
}

//draw the icosahedron x,y,z
void icosahedron(void) {
	for (int i = 0; i<10 - 1; i++)
	{
    	glPushMatrix();
        glTranslated(positionx[i + 1] * 10,  positiony[i + 1] * 10, positionz[i + 1] * 10);
        glutSolidIcosahedron();
    	glPopMatrix(); 
	}
}

void init(void) {
	figurespositions();
}

void enable(void) {
	glEnable(GL_DEPTH_TEST); //enable the depth testing
	glEnable(GL_LIGHTING); //enable the lighting
	glEnable(GL_LIGHT0); //enable LIGHT0, our Diffuse Light
	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH); //set the shader to smooth shader

	objeto = CarregaObjeto("monkey.obj",true);
    printf("Objeto carregado!");
}

void display(void) {
	glClearColor(0.0, 0.0, 0.0, 1.0); //clear the screen to 	black
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//clear the color buffer and the depth buffer
	enable();

	glLoadIdentity();

	glTranslatef(0.0f, 0.0f, -cRadius);
	glRotatef(xrot, 1.0, 0.0, 0.0);
	glColor3f(1.0f, 0.0f, 0.0f);
	//glutSolidCube(2); //Our character to follow

	glPushMatrix();
	//glLoadIdentity();
	DesenhaObjeto(objeto);
	glPopMatrix();

	glRotatef(yrot, 0.0, 1.0, 0.0);  //rotate our camera on the y - axis(up and down)
	glTranslated(-xpos, -ypos, -zpos); //translate the screento the position of our camera
	
	glColor3f(1.0f, 0.498f, 0.0f);
	cube(); //call the cube drawing function
	
	glColor3f(1.0f, 1.0f, 0.0f);
	sphere(); //call the sphere drawing function
	
	glColor3f(0.0f, 1.0f, 0.0f);
	cone(); //call the cone drawing function

	glColor3f(0.0f, 0.0f, 1.0f);
	torus(); //call the torus drawing function

	glColor3f(0.4f, 0.11f, 0.49f);
	dodecahedron(); //call the dodecahedron drawing function

	glColor3f(0.85f, 0.15f, 0.2f);
	octahedron(); //call the octahedron drawing function

	glColor3f(1.0f, 1.0f, 1.0f);
	tetrahedron(); //call the tetrahedron drawing function

	glColor3f(0.0f, 1.0f, 1.0f);
	icosahedron(); //call the icosahedron drawing function

	glutSwapBuffers(); //swap the buffers
	angle++; //increase the angle
}

void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h); //set the viewport	to the current window specifications
	glMatrixMode(GL_PROJECTION); //set the matrix to projection

	glLoadIdentity();
	gluPerspective(60, (GLfloat)w / (GLfloat)h, 0.1, 100.0); //set the perspective (angle of sight, width, height, , depth)
	glMatrixMode(GL_MODELVIEW); //set the matrix back to model

}

void keyboard(unsigned char key, int x, int y) {
	if (key == 'q')
	{
		xrot += 1;
		if (xrot >360) xrot -= 360;
	}

	if (key == 'z')
	{
		xrot -= 1;
		if (xrot < -360) xrot += 360;
	}

	if (key == 'w')
	{
		float xrotrad, yrotrad;
		yrotrad = (yrot / 180 * 3.141592654f);
		xrotrad = (xrot / 180 * 3.141592654f);
		xpos += float(sin(yrotrad));
		zpos -= float(cos(yrotrad));
		ypos -= float(sin(xrotrad));
	}

	if (key == 's')
	{
		float xrotrad, yrotrad;
		yrotrad = (yrot / 180 * 3.141592654f);
		xrotrad = (xrot / 180 * 3.141592654f);
		xpos -= float(sin(yrotrad));
		zpos += float(cos(yrotrad));
		ypos += float(sin(xrotrad));
	}

	if (key == 'd')
	{
		float yrotrad;
		yrotrad = (yrot / 180 * 3.141592654f);
		xpos += float(cos(yrotrad)) * 0.2;
		zpos += float(sin(yrotrad)) * 0.2;
	}

	if (key == 'a')
	{
		float yrotrad;
		yrotrad = (yrot / 180 * 3.141592654f);
		xpos -= float(cos(yrotrad)) * 0.2;
		zpos -= float(sin(yrotrad)) * 0.2;
	}

	if (key == 27)
	{
		// Libera memória e finaliza programa
		LiberaObjeto(objeto);

		exit(0);
	}
}

void mouseMovement(int x, int y) {
	int diffx = x - lastx; //check the difference between the 	current x and the last x position
	int diffy = y - lasty; //check the difference between the 	current y and the last y position
	lastx = x; //set lastx to the current x position
	lasty = y; //set lasty to the current y position
	xrot += (float)diffy; //set the xrot to xrot with the addition	of the difference in the y position
	yrot += (float)diffx;    //set the xrot to yrot with the addition	of the difference in the x position
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Trabalho 3");
	init();
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(reshape);

	glutPassiveMotionFunc(mouseMovement); //check for mouse	movement

	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}