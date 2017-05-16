/*
* Para compilar: g++ SpaceInvader.cpp -o Space -lglut -lGLU -lGL -lm
*
* Computa��o Gr�fica
* Trabalho 2
*
* membros:
*	Anderson Caio Santos Silva
*	Luana Okino Sawada
*	Robson Marques Pessoa
*/

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <GL/glut.h>
#include "includes/Enemy.h"
#include "includes/SquareEnemy.h"
#include "includes/CircleEnemy.h"
#include "includes/TriangleEnemy.h"
#include "includes/Plane.h"

#include <iostream>
using namespace std;

// Declara��o de vari�veis globais
std::vector<Enemy *> invasors;
Plane *plane = new Plane(0.0f, 0.0f);

void DesenhaTiro() {
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

void move_enemy(int step) {
    for (int i=0; i< invasors.size(); ++i)
        invasors.at(i)->move(step);
    glutPostRedisplay();
    glutTimerFunc(10, move_enemy, step);
}

void DesenhaInvasores() {
    for (int i = 0; i < invasors.size(); ++i)
        invasors.at(i)->draw();
    move_enemy(1);
}

// Fun��o callback de redesenho da janela de visualiza��o
void Desenha(void) {
    // Muda para o sistema de coordenadas do modelo
    glMatrixMode(GL_MODELVIEW);
    // Inicializa a matriz de transforma��o corrente
    glLoadIdentity();

    // Limpa a janela de visualiza��o com a cor
    // de fundo definida previamente
    glClear(GL_COLOR_BUFFER_BIT);

    // Desenha os invasores
    glTranslatef(0.0f, -0.8f, 0.0f);    // Tras o conjunto para bottom da tela
    glScalef(0.1f, 0.1f, 0.0f); 		// Reduz 90% o tamanho do conjunto
    DesenhaInvasores();

    // Desenha o jatinho.
    glLoadIdentity();
    glTranslatef(plane->get_x(), 0.0f, 0.0f);
    glTranslatef(0.0f, -0.8f, 0.0f);
    glScalef(0.1f, 0.1f, 0.0f);
    plane->draw();

	// Desenha o missel
	//
	// se o missel ainda n�o foi disparado, desenhar no topo do avi�o
	// ou seja, translada como a posi��o X do avi�o
	if(	!plane->is_shoot_active()) {
		DesenhaTiro();
	}
	// missel t� em movimento, n�o transforma sua coordenada X com a pos do avi�o
	else {
		cout << plane->get_shoot()->get_x() << ", " <<  plane->get_shoot()->get_y() << endl;

    	glLoadIdentity();
    	glTranslatef(plane->get_shoot()->get_x(), plane->get_shoot()->get_y(), 0.0f);
		glTranslatef(0.0f, -0.8f, 0.0f);
		glScalef(0.1f, 0.1f, 0.0f);

		DesenhaTiro();
	}

    // Executa os comandos OpenGL
    glFlush();
}

// Fun��o callback chamada quando o tamanho da janela � alterado 
void AlteraTamanhoJanela(GLsizei w, GLsizei h) {
    GLsizei largura, altura;

    // Evita a divisao por zero
    if (h == 0) h = 1;

    // Atualiza as vari�veis
    largura = w;
    altura = h;

    // Especifica as dimens�es da Viewport
    glViewport(0, 0, largura, altura);

    // Inicializa o sistema de coordenadas
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Estabelece a janela de sele��o (esquerda, direita, inferior,
    // superior) mantendo a propor��o com a janela de visualiza��o
    if (largura <= altura) {
        gluOrtho2D(-1.0f, 1.0f, -1.0f * altura / largura, 1.0f * altura / largura);
        //win = 1.0f;
    } else {
        gluOrtho2D(-1.0f * largura / altura, 1.0f * largura / altura, -1.0f, 1.0f);
        //	win = 1.0f*largura/altura;
    }
}

// Fun��o callback chamada para gerenciar eventos de teclas especiais(F1,PgDn,...)
void TeclasEspeciais(int key, int x, int y) {

    // Move a base
    if (key == GLUT_KEY_LEFT) {
        plane->move(left_direction);
    }
    if (key == GLUT_KEY_RIGHT) {
        plane->move(right_direction);
    }

    glutPostRedisplay();
}

// Fun��o callback chamada para gerenciar eventos de teclas
void Teclado(unsigned char key, int x, int y) {

    if (key == 27)
        exit(0);

    if (key == 32 && !plane->is_shoot_active()) {
		plane->shoot()->start();
    }
}

// Fun��o respons�vel por inicializar par�metros e vari�veis
void Inicializa(void) {
    // Define a cor de fundo da janela de visualiza��o como branca
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    gluOrtho2D(-1.0f, 1.0f, -1.0f, 1.0f);
    glViewport(0, 0, 500, 500);

    // Inicializa os tipos dos invasores
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 10; j++) {
            Enemy *enemy;

            GLfloat x = (j + 1) * 500 + 1000;
            GLfloat y = i * 525 + 5000;

            // TODO convert to normal coordinates
            // Esses valores s�o uns aleat�rios a�
            x = 0.0025 * x - 10;
            y = 0.0025 * y - 1;

            if (i == 0)
                enemy = (Enemy *) new SquareEnemy(x, y);
            else if (i < 3)
                enemy = (Enemy *) new CircleEnemy(x, y);
            else
                enemy = (Enemy *) new TriangleEnemy(x, y);

            invasors.push_back(enemy);
        }
    }
}

// Programa Principal 
int main(int argc, char *argv[]) {
    glutInit(&argc, argv); // Inicia uma inst�ncia da glut
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(5, 5);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Desenho de um prot�tipo de jatinho do Space Invaders!");

    // Registra a fun��o callback de redesenho da janela de visualiza��o
    glutDisplayFunc(Desenha);

    // Registra a fun��o callback de redimensionamento da janela de visualiza��o
    glutReshapeFunc(AlteraTamanhoJanela);

    // Registra a fun��o callback para tratamento das teclas especiais
    glutSpecialFunc(TeclasEspeciais);

    // Registra a fun��o callback para tratamento das teclas ASCII
    glutKeyboardFunc(Teclado);

    // Chama a fun��o respons�vel por fazer as inicializa��es
    Inicializa();

    // Inicia o processamento e aguarda intera��es do usu�rio
    glutMainLoop();

    return 0;
}
