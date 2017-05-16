//
// Created by robso on 5/15/2017.
//

#include "../includes/Shoot.h"
#include <GL/glut.h>
#include <cstdio>
#include <vector>

std::vector<Shoot*> active_shoots;

Shoot::Shoot(Shooter *shooter, GLfloat x_pos, GLfloat y_pos, int direction) {
    this->x_pos = x_pos;
    this->y_pos = y_pos;
    this->direction = direction;
    this->shooter = shooter;
}

void Shoot::set_color(GLfloat red, GLfloat green, GLfloat blue) {
    this->red = red;
    this->green = green;
    this->blue = blue;
}

bool Shoot::unavailable() {
    // Out of y bounds
    if (this->y_pos >= 20.0f)
        return true;
    return false;
}

void move_shoot(int step) {
    for (int i=0; i < active_shoots.size(); ++i)
        active_shoots.at(i)->move(step);
    glutPostRedisplay();
    glutTimerFunc(10, move_shoot, step);
}

void Shoot::move(int step) {
    if (up_direction)
        this->y_pos -= (2.0 * step) / 100;
    else if (down_direction)
        this->y_pos += (2.0 * step) / 100;

    if (unavailable()) {
        shooter->shoot_done();
    }
}

void Shoot::draw() {
    glPushMatrix();

    glColor3f(this->red, this->green, this->blue);
    glLineWidth(2);

    glTranslatef(this->x_pos, this->y_pos, 0.0f);

    glBegin(GL_POLYGON);
    glVertex2f(0.1f, -0.1f);
    glVertex2f(0.1f, 0.1f);
    glVertex2f(0.0f, 0.2f);
    glVertex2f(-0.1f, 0.1f);
    glVertex2f(-0.1f, -0.1f);
    glEnd();

    glPopMatrix(); //Pro jatinho nao sair junto com o missel 1.
}

void Shoot::start() {
    active_shoots.push_back((Shoot *&&) this);
    move_shoot(2);
}

GLfloat Shoot::get_x() {
    return this->x_pos;
}

GLfloat Shoot::get_y() {
    return this->y_pos;
}