#include <GL/freeglut.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>

using namespace std;

struct BULLET {
	GLfloat x, y;
	bool active;
};

struct AIRSHIP {
	GLfloat x, y;
	bool active;
	BULLET bullet;

	// for base player's airship
	int life_count;
};

// base player's airship
AIRSHIP base;

// airship enemies invaders
AIRSHIP invaders[5][10];

/* Draw the player's airship at the bottom of the screen */
void drawBase()
{ 
    glBegin(GL_QUADS);
    glVertex2f(base.x - 50.0f, base.y - 25.0f);
    glVertex2f(base.x - 50.0f, base.y + 25.0f);
    glVertex2f(base.x + 50.0f, base.y + 25.0f);
    glVertex2f(base.x + 50.0f, base.y - 25.0f);
    glEnd();
}

/* Draw a bullet */
void drawBullet(BULLET b)
{
	if(!b.active) return;

    glBegin(GL_QUADS);
    glVertex2f(b.x - 5.0f, b.y - 10.0f);
    glVertex2f(b.x - 5.0f, b.y + 10.0f);
    glVertex2f(b.x + 5.0f, b.y + 10.0f);
    glVertex2f(b.x + 5.0f, b.y - 10.0f);
    glEnd();
}

void drawSquareInvader(GLfloat x, GLfloat y)
{
	glColor3f(0.0f, 0.0f, 255.0f);
	glBegin(GL_QUADS);
	glVertex2f(x - 25.0f, y - 25.0f);
	glVertex2f(x - 25.0f, y + 25.0f);
	glVertex2f(x + 25.0f, y + 25.0f);
	glVertex2f(x + 25.0f, y - 25.0f);
	glEnd();
}

void drawTriangleInvader(GLfloat x, GLfloat y)
{
	glColor3f(0.0f, 255.0f, 0.0f);
	glBegin(GL_TRIANGLES);
	glVertex2f(x - 25.0f, y - 25.0f);
	glVertex2f(x, y + 25.0f);
	glVertex2f(x + 25.0f, y - 25.0f);
	glEnd();
}

void drawCircleInvader(GLfloat x_pos, GLfloat y_pos)
{
	glColor3f(255.0f, 0.0f, 0.0f);

	GLfloat N = 100.0f, r = 25.0f, LIM = 2.0f*3.14159265f, h = LIM / N, theta;
    glLineWidth(2);
    glBegin(GL_TRIANGLE_FAN);
    for (theta = 0.0f; theta <= LIM; theta += h) {
        glVertex2f(x_pos + r*cos(theta), y_pos + r*sin(theta));
    }
    glEnd();
}

/* Draw all active invaders */
void drawInvaders()
{
	for(int i = 0; i < 5; i++) {
		for(int j = 0; j < 10; j++) {
			if(invaders[i][j].active) {
				if(i == 0)
					drawTriangleInvader(invaders[i][j].x, invaders[i][j].y);
				else if(i < 3)
					drawCircleInvader(invaders[i][j].x, invaders[i][j].y);
				else
					drawSquareInvader(invaders[i][j].x, invaders[i][j].y);
			
				if(invaders[i][j].bullet.active) {
					drawBullet(invaders[i][j].bullet);
				}
			}
		}
	}
}

/* General drawing function */
void draw(void) 
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

	// draw the player's base airship (changes its color based on number of lives)
	if(base.life_count == 3)
		glColor3f(255.0f, 0.0f, 255.0f);
	else if(base.life_count == 2)
		glColor3f(0.0f, 255.0f, 0.0f);
	else 
		glColor3f(255.0f, 0.0f, 0.0f);
	drawBase();

	// draw player's bullet
	drawBullet(base.bullet);

	// draw Invaders
	drawInvaders();

    glFlush();
}

void moveBaseBullet(int step)
{
	if(!base.bullet.active) return;

	base.bullet.y += 5.0 * step;

	// check if this bullet is colliding some other object
	for(int i = 0; i < 5 && base.bullet.active; i++) {
		for(int j = 0; j < 10 && base.bullet.active; j++) {

			// touching a invader's bullet (both will get destroyed)
			if(invaders[i][j].bullet.active) {
				GLfloat x = invaders[i][j].bullet.x;
				GLfloat y = invaders[i][j].bullet.y;

				if(base.bullet.x >= x - 5.0f && base.bullet.x <= x + 5.0f &&
					base.bullet.y >= y - 10.0f && base.bullet.y <= y + 10.0f) {
					invaders[i][j].bullet.active = false;
					base.bullet.active = false;
					// because the bullet was destroyed it can't collide anymore
					continue; 
				}
			}

			// killing an invader
			if(invaders[i][j].active) {
				GLfloat x = invaders[i][j].x;
				GLfloat y = invaders[i][j].y;

				if(base.bullet.x >= x - 25.0f && base.bullet.x <= x + 25.0f && 
					base.bullet.y >= y - 25.0f && base.bullet.y <= y + 25.0f) {
						invaders[i][j].active = false;
						base.bullet.active = false;
				}

			}
		}
	}

	if( base.bullet.y > 950)
		base.bullet.active = false;

	glutTimerFunc(10, moveBaseBullet, 1);
}


/* Move all invaders down closer to the bottom */
void moveInvaders(int step)
{
	for(int i = 0; i < 5; i++) {
		for(int j = 0; j < 10; j++) {
			invaders[i][j].y -= 0.1 * step;

			// if the bullet is active, we have to move it as well
			if(invaders[i][j].active && invaders[i][j].bullet.active) {
				invaders[i][j].bullet.y -= 5.0 * step;

				// Check if the bullet has decreased player's life
				GLfloat bx = invaders[i][j].bullet.x;
				GLfloat by = invaders[i][j].bullet.y;

				if(bx >= base.x - 50.0f && bx <= base.x + 50.0f &&
					by >= base.y - 25.0f && by <= base.y + 25.0f) {
						invaders[i][j].bullet.active = false;

						base.life_count--;
				}
				if(invaders[i][j].bullet.y <= base.y)
					invaders[i][j].bullet.active = false;
			}
		}
	}
	glutTimerFunc(10, moveInvaders, 1);
}

void gameOver()
{
	exit(0);
}

void checkGameOver(int step)
{

	// 1: invader touch base
	for(int i = 0; i < 5; i++) {
		for(int j = 0; j < 10; j++) {
			if(!invaders[i][j].active) continue;

			if(invaders[i][j].y - 25.0f <= base.y + 25.0f ) {
				gameOver();
			}
		}
	}

	// 2: base airship has destroyed all invaders
	int sum = 0;
	for(int i = 0; i < 5; i++) {
		for(int j = 0; j < 10; j++) {
			sum += !invaders[i][j].active;
		}
	}
	if(sum == 50)
		gameOver();

	// 3: base airship has been shot 3 times
	if(base.life_count <= 0) 
		gameOver();

	glutTimerFunc(10, checkGameOver, 1);
}

/* Each second generates a random bottom invader to shoot */
void shootInvaders(int step)
{
	srand(time(NULL));

	int j = rand()%10;
	for(int i = 4; i >= 0; i--) {
		if(invaders[i][j].bullet.active) break;

		if(invaders[i][j].active && !invaders[i][j].bullet.active) {
			invaders[i][j].bullet.active = true;
			invaders[i][j].bullet.x = invaders[i][j].x;
			invaders[i][j].bullet.y = invaders[i][j].y;
			break;
		}
	}

	glutTimerFunc(1000, shootInvaders, 1);
}

/* Moves the player's base airship to the left and right */
void specialKeys(int key, int x, int y)
{
    if (key == GLUT_KEY_LEFT) {
        base.x -= 20.0f;
		if(base.x < 50.0f)
			base.x = 50.0f;
    }
	else if (key == GLUT_KEY_RIGHT) {
        base.x += 20.0f;
		if(base.x > 950.0f)
			base.x = 950.0f;
    }
}

/* Treats ESC(27) for game exit and SPACE(32) for shooting */
void keyboard(unsigned char key, int x, int y)
{
    if (key == 27) {
        exit(0);
	}
	else if (key == 32 && !base.bullet.active) {
		base.bullet.active = true;
		base.bullet.x = base.x;
		base.bullet.y = base.y + 25.0f;

		moveBaseBullet(1);
	}
}

/* Global redraw function to synchronize the animation */
void redraw(int step)
{
	glutPostRedisplay();
	glutTimerFunc(10, redraw, 1);
}

/* Initialize necessary variables and functions */
void localInit() 
{
	// base airship position
	base.x = 500.0f, base.y = 50.0f;

	// base airship bullet control
	base.bullet.active = false;

	// life counter
	base.life_count = 3;

	for(int i = 0; i < 5; i++) {
		for(int j = 0; j < 10; j++) {
			invaders[i][j].x = j * 75.0f + 150.0f;
			invaders[i][j].y = 1000 - (i * 75.0f + 50.0f);

			invaders[i][j].active = true;
			invaders[i][j].bullet.active = false;
		}
	}
	
	glutTimerFunc(10, redraw, 1);
	glutTimerFunc(10, moveInvaders, 1);
	glutTimerFunc(100, shootInvaders, 1);
	glutTimerFunc(10, checkGameOver, 1);
}

int main(int argc, char *argv[]) 
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(5, 5);
    glutInitWindowSize(600, 600);
    glutCreateWindow("CG - T2");

	// for RIGHT, LEFT moving 
    glutSpecialFunc(specialKeys);

	// for space shooting and ESC exiting
    glutKeyboardFunc(keyboard);

    glutDisplayFunc(draw);
    gluOrtho2D(0, 1000, 0, 1000);

	localInit();
    glutMainLoop();
}
