//
// Created by robso on 5/15/2017.
//

#ifndef TRABALHO2_ENEMY_H
#define TRABALHO2_ENEMY_H

#include <GL/glut.h>
#include "Shoot.h"

class Enemy {
public:
    Enemy(GLfloat x, GLfloat y);
    virtual void draw() = 0;
    void start();
    void move(int step);
    Shoot* shoot();

    GLfloat get_x();
    GLfloat get_y();

protected:
    GLfloat x_pos, y_pos;
    bool active;
    GLfloat red, green, blue;
	bool shoot_active;
};


#endif //TRABALHO2_ENEMY_H
