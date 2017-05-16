//
// Created by robso on 5/15/2017.
//

#ifndef TRABALHO2_SHOOT_H
#define TRABALHO2_SHOOT_H

#include <GL/gl.h>
#include "Shooter.h"

enum {up_direction, down_direction};

class Shoot {
public:
    Shoot(Shooter *shooter, GLfloat x_pos, GLfloat y_pos, int direction);
    void set_color(GLfloat red, GLfloat green, GLfloat blue);
    void draw();
    void move(int step);
    void start();
    GLfloat get_x();
    GLfloat get_y();

    static void draw_shoots();

private:
    GLfloat x_pos, y_pos;
    int direction;
    Shooter *shooter;

    bool unavailable();

protected:
    GLfloat red, green, blue;
};


#endif //TRABALHO2_SHOOT_H
