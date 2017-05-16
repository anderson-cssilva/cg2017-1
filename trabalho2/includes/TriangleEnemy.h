//
// Created by robso on 5/15/2017.
//

#ifndef TRABALHO2_RECTANGLEENEMY_H
#define TRABALHO2_RECTANGLEENEMY_H


#include "Enemy.h"

/* Esta classe é uma implementação de Enemy que representa um inimigo
 * em formato triangular.
 */
class TriangleEnemy : Enemy {
        public:
        TriangleEnemy(GLfloat x, GLfloat y);
        void draw();

    };


#endif //TRABALHO2_RECTANGLEENEMY_H
