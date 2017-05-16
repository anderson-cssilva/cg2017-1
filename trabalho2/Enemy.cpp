//
// Created by robso on 5/15/2017.
//

#include "Enemy.h"

Enemy *enemy;

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

void move_enemy(int step) {
    enemy->move(step);
    glutPostRedisplay();
    glutTimerFunc(10, move_enemy, step);
}

void Enemy::start() {
    enemy = this;
    move_enemy(1);
}

void Enemy::move(int step) {
    this->y_pos -= (2.0 * step * 0.5) / 100;
}

Shoot *Enemy::shoot() {
    Shoot *sht = new Shoot(this->x_pos, this->y_pos, 1);
    sht->set_color(this->red, this->green, this->blue);
    sht->draw();
    return sht;
}