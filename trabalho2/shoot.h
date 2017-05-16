//
// Created by robso on 5/15/2017.
//

#ifndef TRABALHO2_SHOOT_H
#define TRABALHO2_SHOOT_H

#include <GL/gl.h>

class shoot {
public:
    shoot(GLfloat x_pos, GLfloat y_pos);
    void set_color(GLfloat red, GLfloat green, GLfloat blue);

private:
    GLfloat x_pos, y_pos;

protected:
    GLfloat red, green, blue;
};


#endif //TRABALHO2_SHOOT_H
