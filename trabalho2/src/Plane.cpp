//
// Created by robso on 5/16/2017.
//
#include "../includes/Plane.h"

Plane::Plane(GLfloat x, GLfloat y) {
    this->x_pos = x;
    this->y_pos = y;
    this->life = 3;
    this->red = 1.0f;
    this->green = 0.0f;
    this->blue = 1.0f;
    this->my_shoot = NULL;
}

void Plane::draw() {
    glColor3f(this->red, this->green, this->blue);
    glLineWidth(2);
    //x vai de -1 ate 1, y vai de -1 ate 0.1

    glBegin(GL_QUADS);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(1.0f, -0.5f);
    glVertex2f(-1.0f, -0.5f);
    glVertex2f(-1.0f, -1.0f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(0.8f, -0.5f);
    glVertex2f(0.8f, -0.4f);
    glVertex2f(-0.8f, -0.4f);
    glVertex2f(-0.8f, -0.5f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(0.25f, -0.4f);
    glVertex2f(0.25f, -0.1f);
    glVertex2f(-0.25f, -0.1f);
    glVertex2f(-0.25f, -0.4f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(0.1f, -0.1f);
    glVertex2f(0.1f, 0.1f);
    glVertex2f(-0.1f, 0.1f);
    glVertex2f(-0.1f, -0.1f);
    glEnd();

    if (!this->has_shot()) {
        glColor3f(0, 0, 0);
        glLineWidth(2);

        glBegin(GL_POLYGON);
        glVertex2f(0.1f, -0.1f);
        glVertex2f(0.1f, 0.1f);
        glVertex2f(0.0f, 0.2f);
        glVertex2f(-0.1f, 0.1f);
        glVertex2f(-0.1f, -0.1f);
        glEnd();
    }
}

void Plane::move(int direction) {

    if (direction == left_direction) {
        this->x_pos -= 0.05;
        if (this->x_pos < -0.9f) // Trava o aviao a esquerda da tela
            this->x_pos = -0.9f;
    }else if (direction == right_direction) {
        this->x_pos += 0.05;
        if (this->x_pos > 0.9f) // Trava o aviao a direita da tela
            this->x_pos = 0.9f;
    }
}

Shoot* Plane::shoot() {
    if (this->my_shoot == NULL) {
        Shoot *sht = new Shoot(this, this->x_pos, this->y_pos, up_direction);
        sht->set_color(0.0f, 0.0f, 0.0f);
        this->my_shoot = sht;
        this->my_shoot->start();
    }

    return this->my_shoot;
}

GLfloat Plane::get_x() {
    return this->x_pos;
}

GLfloat Plane::get_y() {
    return this->y_pos;
}

void Plane::hit_target() {
    delete this->my_shoot;
    this->my_shoot = NULL;
}

bool Plane::has_shot() {
	return this->my_shoot != NULL;
}
