//
// Created by robso on 5/15/2017.
//

#include "Shoot.h"
#include <GL/glut.h>
#include <cstdio>

Shoot *shoot;

Shoot::Shoot(GLfloat x_pos, GLfloat y_pos, int direction) {
    this->x_pos = x_pos;
    this->y_pos = y_pos;
    this->direction = direction;
}

void Shoot::set_color(GLfloat red, GLfloat green, GLfloat blue) {
    this->red = red;
    this->green = green;
    this->blue = blue;
}

void move_shoot(int step) {
    shoot->move(step);
    glutPostRedisplay();
    glutTimerFunc(10, move_shoot, step);
}

void Shoot::move(int step) {
    if (up_direction)
        this->y_pos -= (2.0 * step) / 100;
    else if (down_direction)
        this->y_pos += (2.0 * step) / 100;
}

void Shoot::draw() {
    glColor3f(this->red, this->green, this->blue);
    glLineWidth(2);

    glTranslatef(this->x_pos, 0, 0.0f);
    glTranslatef(0, this->y_pos, 0.0f);

    glBegin(GL_POLYGON);
    glVertex2f(0.1f, -0.1f);
    glVertex2f(0.1f, 0.1f);
    glVertex2f(0.0f, 0.2f);
    glVertex2f(-0.1f, 0.1f);
    glVertex2f(-0.1f, -0.1f);
    glEnd();

    printf("(x, y) = (%f, %f)\n", this->x_pos, this->y_pos);
}

void Shoot::start() {
    shoot = this;
    move_shoot(2);
}

GLfloat Shoot::get_x() {
    return this->x_pos;
}

GLfloat Shoot::get_y() {
    return this->y_pos;
}