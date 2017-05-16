//
// Created by robso on 5/15/2017.
//

#include "../includes/TriangleEnemy.h"

TriangleEnemy::TriangleEnemy(GLfloat x, GLfloat y) : Enemy(x, y) {
    this->red = 0.5f;
    this->green = 0.5f;
    this->blue = 1.0f;
}

void TriangleEnemy::draw() {
    glColor3f(this->red, this->green, this->blue);
    glLineWidth(2);
//x vai de -1 ate 1, y vai de -1 ate 0.1
    glBegin(GL_TRIANGLES);
    glVertex2f(this->x_pos, this->y_pos - 0.05f);
    glVertex2f(this->x_pos - 0.025f, this->y_pos + 0.05f);
    glVertex2f(this->x_pos + 0.025f, this->y_pos + 0.05f);
    glEnd();
}