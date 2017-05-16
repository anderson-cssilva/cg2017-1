//
// Created by robso on 5/15/2017.
//

#ifndef TRABALHO2_CIRCLEENEMY_H
#define TRABALHO2_CIRCLEENEMY_H


#include "Enemy.h"

/* Esta classe é uma implementação de Enemy que representa um inimigo
 * em formato de círculo.
 */
class CircleEnemy : Enemy {
public:
    CircleEnemy(GLfloat x, GLfloat y);
    void draw();

};


#endif //TRABALHO2_CIRCLEENEMY_H
