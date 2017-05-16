//
// Created by robso on 5/15/2017.
//

#include "enemy.h"
#include "shoot.h"

enemy::enemy(GLfloat x, GLfloat y) {
    this->x_pos = x;
    this->y_pos = y;
}

void enemy::move() {
    this->y_pos++;
}

shoot enemy::shoot() {
    shoot sht = new shoot(this->x_pos, this->y_pos);
    sht->set_color(this->red, this->green, this->blue);
    return sht;
}