/*
* Computação Gráfica
* Trabalho 1
*
* membros:
*	Anderson Caio Santos Silva
*	Luana Okino Sawada
*	Robson Marques Pessoa
*
* To compile and execute:
* make; make run
*/

#include <GL/freeglut.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>

using namespace std;

//size of the screen
int xwin = 600;
int ywin = 600;

//ortho2D
int xview = 1000;
int yview = 1000;

struct BULLET {
	GLfloat x, y;
	bool active;
};

struct AIRSHIP {
	GLfloat x, y;
	bool active;
	BULLET bullet;
	// for ivaders direction R=0, L=1
	int direction;
	bool down;
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
    glVertex2f(base.x - 5.0f, base.y + 10.0f);
    glVertex2f(base.x - 5.0f, base.y + 20.0f);
    glVertex2f(base.x + 5.0f, base.y + 20.0f);
    glVertex2f(base.x + 5.0f, base.y + 10.0f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(base.x - 10.0f, base.y);
    glVertex2f(base.x - 10.0f, base.y + 10.0f);
    glVertex2f(base.x + 10.0f, base.y + 10.0f);
    glVertex2f(base.x + 10.0f, base.y);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(base.x - 45.0f, base.y - 5.0f);
    glVertex2f(base.x - 45.0f, base.y);
    glVertex2f(base.x + 45.0f, base.y);
    glVertex2f(base.x + 45.0f, base.y - 5.0f);
    glEnd();

	glBegin(GL_QUADS);
    glVertex2f(base.x - 50.0f, base.y - 35.0f);
    glVertex2f(base.x - 50.0f, base.y - 5.0f);
    glVertex2f(base.x + 50.0f, base.y - 5.0f);
    glVertex2f(base.x + 50.0f, base.y - 35.0f);
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

void drawTriangleInvader(GLfloat x, GLfloat y, GLfloat life)
{
	glColor3f( (4-life)/(life+4)*1.0f, 1.0f,  (4-life)/(life+4)*1.0f);
	glBegin(GL_TRIANGLES);
	glVertex2f(x - 25.0f, y - 25.0f);
	glVertex2f(x, y + 25.0f);
	glVertex2f(x + 25.0f, y - 25.0f);
	glEnd();
}

void drawCircleInvader(GLfloat x_pos, GLfloat y_pos, GLfloat life)
{
	glColor3f(1.0f, (3-life)/(life+3)*1.0f, (3-life)/(life+3)*1.0f);

	GLfloat N = 100.0f, r = 25.0f, LIM = 2.0f*3.14159265f, h = LIM / N, theta;
    glLineWidth(2);
    glBegin(GL_TRIANGLE_FAN);
    for (theta = 0.0f; theta <= LIM; theta += h) {
        glVertex2f(x_pos + r*cos(theta), y_pos + r*sin(theta));
    }
    glEnd();
}

void drawSquareInvader(GLfloat x, GLfloat y)
{
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);
	glVertex2f(x - 25.0f, y - 25.0f);
	glVertex2f(x - 25.0f, y + 25.0f);
	glVertex2f(x + 25.0f, y + 25.0f);
	glVertex2f(x + 25.0f, y - 25.0f);
	glEnd();
}

/* Draw all active invaders */
void drawInvaders()
{
	for(int i = 0; i < 5; i++) {
		for(int j = 0; j < 10; j++) {
			if(invaders[i][j].active) {
				if(i == 0)
					drawTriangleInvader(invaders[i][j].x, invaders[i][j].y, invaders[i][j].life_count);
				else if(i < 3)
					drawCircleInvader(invaders[i][j].x, invaders[i][j].y, invaders[i][j].life_count);
				else
					drawSquareInvader(invaders[i][j].x, invaders[i][j].y);
			}

			if(invaders[i][j].bullet.active) {
				drawBullet(invaders[i][j].bullet);
			}
		}
	}
}
							

/* General drawing function */
void draw(void) 
{
    glClearColor(0.95, 0.95f, 0.95f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

	// draw base with different levels of gray according to number of lives
	glColor3f(0.75f / (1.0*base.life_count), 0.75f / (1.0*base.life_count), 0.75f / (1.0*base.life_count));

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

	base.bullet.y += 5*step;

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
						invaders[i][j].life_count--;
						base.bullet.active = false;

						if (invaders[i][j].life_count == 0)
							invaders[i][j].active = false;
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
	// moving invaders to the left and right
	if (invaders[0][0].down){
		// go down if it was going to the right
		if (invaders[0][9].direction == 0){
			for(int i = 0; i < 5; i++) {
				for(int j = 0; j < 10; j++) {
					invaders[i][j].y -= 25;
					invaders[i][j].direction = 1;
					invaders[i][j].down = false;
				}
			}
		}
		// go down if it was going to the left
		else if (invaders[0][0].direction == 1){
			for(int i = 0; i < 5; i++) {
				for(int j = 0; j < 10; j++) {
					invaders[i][j].y -= 25;
					invaders[i][j].direction = 0;
					invaders[i][j].down = false;
				}
			}
		}
		if (step < 4)
			step++;
		else
			step = 4;
	}

	if (!invaders[0][0].down){
		// check the invader from the right side
		if (invaders[0][9].direction == 0)
		{
			if (invaders[0][9].x < 1000-25){
				for(int i = 0; i < 5; i++) {
					for(int j = 0; j < 10; j++) {
						invaders[i][j].x += 0.5*(step+1)/2.0;
					}
				}
			}		
			//if hit the border then go down
			else {
				for(int i = 0; i < 5; i++) {
					for(int j = 0; j < 10; j++) {
						invaders[i][j].down = true; // go down
					}
				}
			}
		}
		// check the invader from the left side
		else if (invaders[0][0].direction == 1)
		{
			if (invaders[0][0].x > 25){
				for(int i = 0; i < 5; i++) {
					for(int j = 0; j < 10; j++) {
						invaders[i][j].x -= 0.5*(step+1)/2.0;
					}
				}
			}		
			//if hit the border then go down
			else {
				for(int i = 0; i < 5; i++) {
					for(int j = 0; j < 10; j++) {
						invaders[i][j].down = true; // go down
					}
				}
			}
		}
	}

	// collision
	for(int i = 0; i < 5; i++) {
		for(int j = 0; j < 10; j++) {

			// if the bullet is active, we have to move it as well
			if(invaders[i][j].bullet.active) {
				invaders[i][j].bullet.y -= (step+1)/0.5;

				// Check if the bullet has decreased player's life
				GLfloat bx = invaders[i][j].bullet.x;
				GLfloat by = invaders[i][j].bullet.y;

				if(bx >= base.x - 50.0f && bx <= base.x + 50.0f &&
					by >= base.y - 35.0f && by <= base.y + 20.0f) {
						invaders[i][j].bullet.active = false;
						base.life_count--;
				}

				// has reached the bottom 
				if(invaders[i][j].bullet.y <= base.y-35)
					invaders[i][j].bullet.active = false;
			}
		}
	}

	glutTimerFunc(10, moveInvaders, step);
}

void gameOver()
{
	/* TODO
	 * Create a restart option?
	 * Send the player a message?
	 * 		YOU LOST - GAME OVER
	 * 		YOU WIN - NEXT PHASE
	 * Go to a harder phase if it's a win??
	 * 		increase speed of invaders movement
	 * 		invaders starting from a lower Y position
	 * 		increase number of lifes necessary to kill a invader
	 */
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
/* TODO
 * 	Try different timers and different approaches for random generation of 
 * 	coordinates. Maybe give more probability to the area the base is in.
 */
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
/* TODO
 * 	Differentiate when a key is pressed down and when it keeps being pressed.
 * 	This will allow the base airship to move independently of the bullets
 */
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
			invaders[i][j].direction = 0;
			invaders[i][j].down = false;

			if (i == 0)
				invaders[i][j].life_count = 3;
			else if(i < 3)
				invaders[i][j].life_count = 2;
			else
				invaders[i][j].life_count = 1;
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
    glutInitWindowSize(xwin, ywin);
    glutCreateWindow("CG - T2");

	// for RIGHT, LEFT moving 
    glutSpecialFunc(specialKeys);

	// for space shooting and ESC exiting
    glutKeyboardFunc(keyboard);

    glutDisplayFunc(draw);
	/* TODO
	 * 	Maybe it'll be necessary to keep these values as initial and change it
	 * 	if the window is resized. In that case, we'll need to replace the usages 
	 * 	of fixed values considering the variables with current sizes
	 */
    gluOrtho2D(0, xview, 0, yview);

	localInit();
    glutMainLoop();
}
