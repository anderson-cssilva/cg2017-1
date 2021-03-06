//
// Created by robso on 5/15/2017.
//

#include "../includes/Shoot.h"
#include <GL/glut.h>
#include <vector>
#include <algorithm>

#include <iostream>
using namespace std;

std::vector<Shoot *> active_shoots;

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
    if (up_direction && this->y_pos >= 0.95f)
        return true;
	else if(down_direction && this->y_pos <= -1.0)
		return true;

    return false;
}

void move_shoot(int step) {
    if (!active_shoots.empty()) {
        for (int i = 0; i < active_shoots.size(); ++i)
            active_shoots.at(i)->move(step);
        //glutPostRedisplay();
        glutTimerFunc(10, move_shoot, step);
    }
}

void Shoot::move(int step) {
	cout << "shoot: " << this << " move --> (" << this->x_pos << ", " << this->y_pos << ")\n";

    if (this->direction == up_direction)
        this->y_pos += (2.0 * step) / 100;
    else if (this->direction == down_direction)
        this->y_pos -= (2.0 * step) / 100;

    if (unavailable()) {
        auto it = std::find(active_shoots.begin(), active_shoots.end(), this);
        if(it != active_shoots.end())
            active_shoots.erase(it);
        shooter->hit_target();
    }
}

void Shoot::draw() {
    glPushMatrix();

    glLoadIdentity();
    glTranslatef(this->x_pos, this->y_pos, 0.0f);

    glColor3f(this->red, this->green, this->blue);
    glLineWidth(2);

    glBegin(GL_POLYGON);
    glVertex2f(0.01f, -0.01f);
    glVertex2f(0.01f, 0.01f);
    glVertex2f(0.0f, 0.02f);
    glVertex2f(-0.01f, 0.01f);
    glVertex2f(-0.01f, -0.01f);
    glEnd();

    glPopMatrix(); //Pro jatinho nao sair junto com o missel 1.
}

void Shoot::start() {
	cout << "shoot: " << this << " starting\n";
    active_shoots.push_back((Shoot *&&) this);
    move_shoot(2);
}

void Shoot::draw_shoots() {
    for (int i = 0; i < active_shoots.size(); ++i)
        active_shoots.at(i)->draw();
}

GLfloat Shoot::get_x() {
    return this->x_pos;
}

GLfloat Shoot::get_y() {
    return this->y_pos;
}
