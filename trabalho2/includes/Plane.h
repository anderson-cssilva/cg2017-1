//
// Created by robso on 5/16/2017.
//

#ifndef TRABALHO2_PLANE_H
#define TRABALHO2_PLANE_H


#include <GL/glut.h>
#include "Shoot.h"

enum {right_direction, left_direction};

class Plane {
public:
    Plane(GLfloat x, GLfloat y);
    void draw();
    void move(int direction);
    Shoot* shoot();

    GLfloat get_x();
    GLfloat get_y();

private:
    GLfloat x_pos, y_pos;
    int life;
    GLfloat red, green, blue;
};


#endif //TRABALHO2_PLANE_H
