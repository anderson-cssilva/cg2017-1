//
// Created by robso on 5/16/2017.
//

#ifndef TRABALHO2_PLANE_H
#define TRABALHO2_PLANE_H

#include <GL/glut.h>
#include "Shoot.h"
#include "Shooter.h"

enum {right_direction, left_direction};

/* Esta classe provê a representação de um Jatinho, o qual
 * o usuário utilizará como personagem chave no jogo.
 *
 * Ela é uma subclasse de Shooter, pois performa tiros para
 * derrotar os inimigos invasores.
 */
class Plane : Shooter {
public:
    Plane(GLfloat x, GLfloat y);
	// métodos responsáveis pelo desenho e movimentação do jato 
    void draw();
    void move(int direction);

	// métodos responsáveis pelo controle do tiro
	Shoot* shoot();
	bool has_shot();
	void hit_target();

	// métodos get
	GLfloat get_x();
	GLfloat get_y();

private:
    GLfloat x_pos, y_pos;
    Shoot* my_shoot;
    GLfloat red, green, blue;
	int life;
};


#endif //TRABALHO2_PLANE_H
