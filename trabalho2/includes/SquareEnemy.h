//
// Created by robso on 5/15/2017.
//

#ifndef TRABALHO2_SQUAREENEMY_H
#define TRABALHO2_SQUAREENEMY_H


#include "Enemy.h"

/* Esta classe é uma implementação de Enemy que representa um inimigo
 * em formato quadrado.
 */
class SquareEnemy : Enemy {
public:
    SquareEnemy(GLfloat x, GLfloat y);
    void draw();

};


#endif //TRABALHO2_SQUAREENEMY_H
