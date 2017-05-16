//
// Created by robso on 5/16/2017.
//

#ifndef TRABALHO2_PLANE_H
#define TRABALHO2_PLANE_H


#include <GL/glut.h>
#include "Shoot.h"
#include "Shooter.h"

enum {right_direction, left_direction};

class Plane : Shooter {
public:
    Plane(GLfloat x, GLfloat y);
    void draw();
    void move(int direction);
    Shoot* shoot();
    void shoot_done();

    GLfloat get_x();
    GLfloat get_y();

private:
    GLfloat x_pos, y_pos;
    int life;
    bool has_shooted;
    GLfloat red, green, blue;
};


#endif //TRABALHO2_PLANE_H
