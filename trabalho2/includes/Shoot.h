//
// Created by robso on 5/15/2017.
//

#ifndef TRABALHO2_SHOOT_H
#define TRABALHO2_SHOOT_H

#include <GL/gl.h>
#include "Shooter.h"

enum {up_direction = 1, down_direction = -1};

/* Esta classe provê a representação de um tiro, utilizada
 * por qualquer classe Shooter (com a habilidade de atirar).
 */
class Shoot {
public:
    Shoot(Shooter *shooter, GLfloat x_pos, GLfloat y_pos, int direction);

    // métodos responsáveis pelo controle do desenho e da movimentação do objeto
    void set_color(GLfloat red, GLfloat green, GLfloat blue);
    void draw();
    void move(int step);
    void start();

    // métodos get
    GLfloat get_x();
    GLfloat get_y();

    // método estático para desenhar todos os objetos Shoot do jogo
    static void draw_shoots();

private:
    GLfloat x_pos, y_pos;
    int direction;
    Shooter *shooter;

    // método para verificação da disponibilidade do tiro (se ainda encontra-se em jogo)
    bool unavailable();

protected:
    GLfloat red, green, blue;
};


#endif //TRABALHO2_SHOOT_H
