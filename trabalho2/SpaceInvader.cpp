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
#include <time.h>

using namespace std;

// Declara��o de vari�veis globais
std::vector<Enemy *> invasors;
Plane *plane = new Plane(0.0f, -0.82f);

void move_enemy(int step) {
    for (int i = 0; i < invasors.size(); ++i)
        invasors.at(i)->move(step);
    //glutPostRedisplay();
    glutTimerFunc(10, move_enemy, step);
}

void DesenhaTiros() {
    Shoot::draw_shoots();
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
    DesenhaInvasores();

    // Desenha o jatinho.
    glLoadIdentity();
    glTranslatef(plane->get_x(), 0.0f, 0.0f);
    plane->draw();

    // Desenha o missel
    DesenhaTiros();

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

    //glutPostRedisplay();
}

// Fun��o callback chamada para gerenciar eventos de teclas
void Teclado(unsigned char key, int x, int y) {

    if (key == 27)
        exit(0);

    if (key == 32 && !plane->has_shot())
        plane->shoot();
}

void TirosInvasors(int step) {
	srand(time(NULL));

	int i;
	while(true) {
		i = rand()%invasors.size();
		if(invasors.at(i)->is_active() && !invasors.at(i)->has_shot())
			break;
	}
	invasors.at(i)->shoot();

	//glutPostRedisplay();
	glutTimerFunc(2000, TirosInvasors, step);
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

            GLfloat x = (j + 1) * 0.15f - 0.9f;
            GLfloat y = (i + 1) * 0.15f + 0.2f;

            cout << "ANTES - ("<< x << ", " << y << ")"<< endl;

            if (i == 0)
                enemy = (Enemy *) new SquareEnemy(x, y);
            else if (i < 3)
                enemy = (Enemy *) new CircleEnemy(x, y);
            else
                enemy = (Enemy *) new TriangleEnemy(x, y);

            invasors.push_back(enemy);
        }
    }

	// Chama pela primeira vez a fun��o de atirar dos invasores
	TirosInvasors(1);
}

void redesenha(int step) {
	glutPostRedisplay();
	glutTimerFunc(10, redesenha, 1);
}

// Programa Principal 
int main(int argc, char *argv[]) {
    glutInit(&argc, argv); // Inicia uma inst�ncia da glut
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(5, 5);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Desenho de um prot�tipo de jatinho do Space Invaders!");

	glutTimerFunc(10, redesenha, 1);

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
