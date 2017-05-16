//
// Created by robso on 5/15/2017.
//

#ifndef TRABALHO2_ENEMY_H
#define TRABALHO2_ENEMY_H

#include <GL/glut.h>
#include "shoot.h"

class enemy {
public:
    enemy(GLfloat x, GLfloat y);
    virtual void draw() = 0;
    void move();
    shoot shoot();

private:
    GLfloat x_pos, y_pos;

protected:
    GLfloat red, green, blue;

};


#endif //TRABALHO2_ENEMY_H
