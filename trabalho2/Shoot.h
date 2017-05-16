//
// Created by robso on 5/15/2017.
//

#ifndef TRABALHO2_SHOOT_H
#define TRABALHO2_SHOOT_H

#include <GL/gl.h>

class Shoot {
public:
    Shoot(GLfloat x_pos, GLfloat y_pos, int direction);
    void set_color(GLfloat red, GLfloat green, GLfloat blue);
    void draw();

private:
    GLfloat x_pos, y_pos;
    int direction;

protected:
    GLfloat red, green, blue;
};


#endif //TRABALHO2_SHOOT_H
