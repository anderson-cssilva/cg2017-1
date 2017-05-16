//
// Created by robso on 5/15/2017.
//

#include "../includes/Enemy.h"
#include <iostream>
using namespace std;

Enemy::Enemy(GLfloat x, GLfloat y) {
    this->x_pos = x;
    this->y_pos = y;
    this->active = true;
	this->my_shoot = NULL;
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

Shoot* Enemy::shoot() {
    if (this->my_shoot == NULL) {
		cout << "invasor shoot building\n";
        Shoot *sht = new Shoot(this, this->x_pos, this->y_pos, down_direction);
        //sht->set_color(this->red, this->green, this->blue);
        sht->set_color(1, 0, 1);
        this->my_shoot = sht;
        this->my_shoot->start();
    }

    return this->my_shoot;
}
void Enemy::hit_target() {
    delete this->my_shoot;
    this->my_shoot = NULL;
}

bool Enemy::is_active() {
	return this->active;
}

bool Enemy::has_shot() {
	return this->my_shoot != NULL;
}
