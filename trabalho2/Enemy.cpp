//
// Created by robso on 5/15/2017.
//

#include "Enemy.h"

Enemy::Enemy(GLfloat x, GLfloat y) {
    this->x_pos = x;
    this->y_pos = y;
    this->active = true;
}

GLfloat Enemy::get_x() {
    return this->x_pos;
}

GLfloat Enemy::get_y() {
    return this->y_pos;
}

void Enemy::move(int step) {
    this->y_pos -= (2.0 * step) / 500000;
}

Shoot *Enemy::shoot() {
    Shoot *sht = new Shoot(this->x_pos, this->y_pos, down_direction);
    sht->set_color(this->red, this->green, this->blue);
    sht->draw();
    return sht;
}