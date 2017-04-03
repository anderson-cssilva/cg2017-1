/*
* Computação Gráfica
* Trabalho 1
*
* membros:
*	Anderson Caio Santos Silva
*	Luana Okino Sawada
*	Robson Marques Pessoa
*/

#include <GL/freeglut.h>

/* 
 * Posição do topo da haste do cata vento.
 * É o centro do conjunto de triângulos que formam a hélice.
 */
GLfloat xpos = 300.0f, ypos = 250.0f;

/* Angulo para movimento da hélice */
GLfloat theta = 0.0f;

void desenhaFundo() {
    /* Desenha grama verde */
    glColor3f(0.12f, 0.75f, 0.14f);
    glBegin(GL_QUADS);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.0f, 150.0f);
    glVertex2f(400.0f, 150.0f);
    glVertex2f(400.0f, 0.0f);
    glEnd();

    /* Desenha céu azul*/
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(0.0f, 150.0f);
    glVertex2f(0.0f, 400.0f);
    glVertex2f(400.0f, 400.0f);
    glVertex2f(400.0f, 150.0f);
    glEnd();
}

void desenhaHaste() {
    /* Desenha haste preta */
    glColor3f(.0f, .0f, .0f);
    glBegin(GL_QUADS);
    glVertex2f(299.0f, 100.0f); /* botton-left */
    glVertex2f(299.0f, 250.0f); /* upper -left */
    glVertex2f(301.0f, 250.0f); /* upper-right */
    glVertex2f(301.0f, 100.0f); /* botton-right */
    glEnd();
}

void aplicaTransformacoes() {
    /* Iniciar as transformações 2D */
    glLoadIdentity();

    /* Faz a rotação de todas as hélices com theta graus */
    glTranslatef(xpos, ypos, 0.0f);
    glRotatef(theta, 0.0f, 0.0f, 1.0f);
    glTranslatef(-xpos, -ypos, 0.0f);
}

void desenhaHelices() {
    /* Desenha Hélices 1 - fucsia */
    glColor3f(1.0f, 0.0f, 0.5f);
    glBegin(GL_TRIANGLES);
    glVertex2f(xpos, ypos);
    glVertex2f(xpos + 50.0f, ypos + 15.0f);
    glVertex2f(xpos + 50.0f, ypos - 15.0f);
    glEnd();

    /* Desenha Hélices 2 - blue */
    glColor3f(0.3f, 0.77f, 0.84f);
    glBegin(GL_TRIANGLES);
    glVertex2f(xpos, ypos);
    glVertex2f(xpos - 50.0f, ypos + 15.0f);
    glVertex2f(xpos - 50.0f, ypos - 15.0f);
    glEnd();

    /* Desenha Hélices 3 - verde */
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(xpos, ypos);
    glVertex2f(xpos - 15.0f, ypos - 50.0f);
    glVertex2f(xpos + 15.0f, ypos - 50.0f);
    glEnd();

    /* Desenha Hélices 4 - amarela */
    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(xpos, ypos);
    glVertex2f(xpos - 15.0f, ypos + 50.0f);
    glVertex2f(xpos + 15.0f, ypos + 50.0f);
    glEnd();
}

void desenha(void) {
    /* Colorir o fundo da cena de branco */
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    /* Iniciar as transformações 2D */
    /* Inicia-se a matriz de transformações da openGL */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    /* Desenha o fundo da tela */
    desenhaFundo();

    /* Desenha a primeira parte do cata-vento, a Haste, que é fixa */
    desenhaHaste();

    /* Aplica as tranformações necessárias para o movimento das hélices */
    aplicaTransformacoes();

    /* Desenha os triângulos que representam as hélices */
    desenhaHelices();

    glFlush();
}

/* Evento de click no mouse */
void on_mouseClick(int botao_clicado, int estado_do_click,
                   int x_mouse_position, int y_mouse_position) {

    if (estado_do_click == GLUT_UP) {
    	/* Se o click for com o botão esquerdo do mouse
    	 então gira todas as hélices para o sentido anti-horário com thera graus*/
        if (botao_clicado == GLUT_LEFT_BUTTON) {
            theta += 36.0f;
        }
        
        /* Se o click for com o botão direito do mouse
         então gira todas as hélices para o sentido horário com thera graus */
        if (botao_clicado == GLUT_RIGHT_BUTTON) {
            theta -= 36.0f;
        }
    }

    /* Força a glut redesenhar a cena após a atualização. */
    glutPostRedisplay();
}

int main(int argc, char *argv[]) {
    /* Inicia uma instância da glut */
    glutInit(&argc, argv);

    /* Define o modo de display do buffer */
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    /* Define o tamanho em pixels da janela */
    glutInitWindowSize(600, 600);

    /* Define o título da janela */
    glutCreateWindow("Computação Gráfica - Trabalho 1");

    /* Estabelece que a função de rendering é a função "desenha(.)" */
    glutDisplayFunc(desenha);

    /* Tratamento de eventios de click do mouse */
    glutMouseFunc(on_mouseClick);

    /* Especificações de observação de cena */
    glMatrixMode(GL_PROJECTION);

    /* Define o plano ortogonal em que a cena será construída */
    gluOrtho2D(0, 400, 0, 400);

    /* Inicia as operações conforme as especificações anteriores */
    glutMainLoop();
}
