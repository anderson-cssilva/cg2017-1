//
// Created by robso on 5/15/2017.
//

#include "../includes/SquareEnemy.h"

SquareEnemy::SquareEnemy(GLfloat x, GLfloat y) : Enemy(x, y) {
    this->red = 0.5f;
    this->green = 1.0f;
    this->blue = 0.5f;
}

void SquareEnemy::draw() {
    glColor3f(this->red, this->green, this->blue);
    glLineWidth(2);
    glBegin(GL_QUADS);
    glVertex2f(this->x_pos - 0.5, this->y_pos - 0.5);
    glVertex2f(this->x_pos - 0.5, this->y_pos + 0.5);
    glVertex2f(this->x_pos + 0.5, this->y_pos + 0.5);
    glVertex2f(this->x_pos + 0.5, this->y_pos - 0.5);
    glEnd();
}
