/*
* Computa��o Gr�fica
* Trabalho 1
*
* membros:
*	Anderson Caio Santos Silva
*	Luana Okino Sawada
*	Robson Marques Pessoa
*/

#include <GL/freeglut.h>

/* 
 * Posi��o do topo da haste do cata vento.
 * � o centro do conjunto de tri�ngulos que formam a h�lice.
 */
GLfloat xpos = 300.0f, ypos = 250.0f;

/* Angulo para movimento da h�lice */
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

    /* Desenha c�u azul*/
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
    /* Iniciar as transforma��es 2D */
    glLoadIdentity();

    /* Faz a rota��o de todas as h�lices com theta graus */
    glTranslatef(xpos, ypos, 0.0f);
    glRotatef(theta, 0.0f, 0.0f, 1.0f);
    glTranslatef(-xpos, -ypos, 0.0f);
}

void desenhaHelices() {
    /* Desenha H�lices 1 - fucsia */
    glColor3f(1.0f, 0.0f, 0.5f);
    glBegin(GL_TRIANGLES);
    glVertex2f(xpos, ypos);
    glVertex2f(xpos + 50.0f, ypos + 15.0f);
    glVertex2f(xpos + 50.0f, ypos - 15.0f);
    glEnd();

    /* Desenha H�lices 2 - blue */
    glColor3f(0.3f, 0.77f, 0.84f);
    glBegin(GL_TRIANGLES);
    glVertex2f(xpos, ypos);
    glVertex2f(xpos - 50.0f, ypos + 15.0f);
    glVertex2f(xpos - 50.0f, ypos - 15.0f);
    glEnd();

    /* Desenha H�lices 3 - verde */
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(xpos, ypos);
    glVertex2f(xpos - 15.0f, ypos - 50.0f);
    glVertex2f(xpos + 15.0f, ypos - 50.0f);
    glEnd();

    /* Desenha H�lices 4 - amarela */
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

    /* Iniciar as transforma��es 2D */
    /* Inicia-se a matriz de transforma��es da openGL */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    /* Desenha o fundo da tela */
    desenhaFundo();

    /* Desenha a primeira parte do cata-vento, a Haste, que � fixa */
    desenhaHaste();

    /* Aplica as tranforma��es necess�rias para o movimento das h�lices */
    aplicaTransformacoes();

    /* Desenha os tri�ngulos que representam as h�lices */
    desenhaHelices();

    glFlush();
}

/* Evento de click no mouse */
void on_mouseClick(int botao_clicado, int estado_do_click,
                   int x_mouse_position, int y_mouse_position) {

    if (estado_do_click == GLUT_UP) {
    	/* Se o click for com o bot�o esquerdo do mouse
    	 ent�o gira todas as h�lices para o sentido anti-hor�rio com thera graus*/
        if (botao_clicado == GLUT_LEFT_BUTTON) {
            theta += 36.0f;
        }
        
        /* Se o click for com o bot�o direito do mouse
         ent�o gira todas as h�lices para o sentido hor�rio com thera graus */
        if (botao_clicado == GLUT_RIGHT_BUTTON) {
            theta -= 36.0f;
        }
    }

    /* For�a a glut redesenhar a cena ap�s a atualiza��o. */
    glutPostRedisplay();
}

int main(int argc, char *argv[]) {
    /* Inicia uma inst�ncia da glut */
    glutInit(&argc, argv);

    /* Define o modo de display do buffer */
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    /* Define o tamanho em pixels da janela */
    glutInitWindowSize(600, 600);

    /* Define o t�tulo da janela */
    glutCreateWindow("Computa��o Gr�fica - Trabalho 1");

    /* Estabelece que a fun��o de rendering � a fun��o "desenha(.)" */
    glutDisplayFunc(desenha);

    /* Tratamento de eventios de click do mouse */
    glutMouseFunc(on_mouseClick);

    /* Especifica��es de observa��o de cena */
    glMatrixMode(GL_PROJECTION);

    /* Define o plano ortogonal em que a cena ser� constru�da */
    gluOrtho2D(0, 400, 0, 400);

    /* Inicia as opera��es conforme as especifica��es anteriores */
    glutMainLoop();
}
