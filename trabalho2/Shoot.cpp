//
// Created by robso on 5/15/2017.
//

#include "Shoot.h"

Shoot::Shoot(GLfloat x_pos, GLfloat y_pos, int direction) {
    this->x_pos = x_pos;
    this->y_pos = y_pos;
    this->direction = direction;
}

void Shoot::set_color(GLfloat red, GLfloat green, GLfloat blue) {
    this->red = red;
    this->green = green;
    this->blue = blue;
}

void Shoot::draw() {

}
