//
// Created by robso on 5/15/2017.
//

#ifndef TRABALHO2_ENEMY_H
#define TRABALHO2_ENEMY_H

#include <GL/glut.h>
#include "Shoot.h"
#include "Shooter.h"
#include <vector>

class Enemy : Shooter {
public:
    Enemy(GLfloat x, GLfloat y);
    virtual void draw() = 0;
    void move(int step);
    Shoot* shoot();
    void shoot_done();

    GLfloat get_x();
    GLfloat get_y();

	bool is_active();
	bool has_shot();

protected:
    GLfloat x_pos, y_pos;
    bool active;
    GLfloat red, green, blue;
    Shoot* my_shoot;
};

#endif //TRABALHO2_ENEMY_H
