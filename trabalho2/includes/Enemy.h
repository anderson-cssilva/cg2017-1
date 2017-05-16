//
// Created by robso on 5/15/2017.
//

#ifndef TRABALHO2_ENEMY_H
#define TRABALHO2_ENEMY_H

#include <GL/glut.h>
#include "Shoot.h"
#include "Shooter.h"
#include <vector>

/* Esta classe abstrata provê a representação de um inimigo, o qual
 * o usuário utilizará como personagem chave no jogo.
 *
 * Ela é uma subclasse de Shooter, pois performa tiros para
 * derrotar o usuário.
 */
class Enemy : Shooter {
public:
    Enemy(GLfloat x, GLfloat y);
	// métodos responsáveis pelo desenho e movimentação do jato
	virtual void draw() = 0;
    void move(int step);

	// métodos responsáveis pelo controle do tiro
    Shoot* shoot();
    void hit_target();
	bool has_shot();
	bool is_active();

	// métodos get
    GLfloat get_x();
    GLfloat get_y();

protected:
    GLfloat x_pos, y_pos;
    bool active;
    GLfloat red, green, blue;
    Shoot* my_shoot;
};

#endif //TRABALHO2_ENEMY_H
