//
// Created by robso on 5/15/2017.
//

#include <math.h>
#include "CircleEnemy.h"

CircleEnemy::CircleEnemy(GLfloat x, GLfloat y) : Enemy(x, y) {
    this->red = 1.0f;
    this->green = 0.5f;
    this->blue = 0.5f;
}

void CircleEnemy::draw() {
    glColor3f(this->red, this->green, this->blue);
    glLineWidth(2);
    glBegin(GL_LINE_LOOP);

    int segments = 100;
    for(int i = 0; i < segments; i++)
    {
        float theta = 2.0f * 3.1415926f * float(i) / float(segments);//get the current angle

        float x = cosf(theta) / 2;//calculate the x component
        float y = sinf(theta) / 2;//calculate the y component

        glVertex2f(x + this->x_pos, y + this->y_pos);//output vertex
    }

    glEnd();

    this->start();
}
