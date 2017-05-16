/*
* Para compilar: g++ SpaceInvader.cpp -o Space -lglut -lGLU -lGL -lm
*
* Computação Gráfica
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
#include "Enemy.h"
#include "SquareEnemy.h"
#include "CircleEnemy.h"
#include "TriangleEnemy.h"

// Declaração de variáveis globais
GLfloat missel1_y = 0;
GLfloat aviao_x = 0, missel1_tx = 0;
bool missel1_moving = false;
int msec_missel1 = 0;

std::vector<Enemy *> invasors;


void move_missel1(int passo) {
    missel1_y += (2.0 * passo) / 100;
    glutPostRedisplay();

    glutTimerFunc(10, move_missel1, passo);
}


// Função para desenhar a base do objeto           
void DesenhaAviao() {

    glColor3f(1.0f, 0.0f, 1.0f);
    glLineWidth(2);
//x vai de -1 ate 1, y vai de -1 ate 0.1
    glBegin(GL_QUADS);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(1.0f, -0.5f);
    glVertex2f(-1.0f, -0.5f);
    glVertex2f(-1.0f, -1.0f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(0.8f, -0.5f);
    glVertex2f(0.8f, -0.4f);
    glVertex2f(-0.8f, -0.4f);
    glVertex2f(-0.8f, -0.5f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(0.25f, -0.4f);
    glVertex2f(0.25f, -0.1f);
    glVertex2f(-0.25f, -0.1f);
    glVertex2f(-0.25f, -0.4f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(0.1f, -0.1f);
    glVertex2f(0.1f, 0.1f);
    glVertex2f(-0.1f, 0.1f);
    glVertex2f(-0.1f, -0.1f);
    glEnd();
}

void DesenhaMisseis() {
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(2);
    glBegin(GL_POLYGON);
    glVertex2f(0.1f, -0.1f);
    glVertex2f(0.1f, 0.1f);
    glVertex2f(0.0f, 0.2f);
    glVertex2f(-0.1f, 0.1f);
    glVertex2f(-0.1f, -0.1f);
    glEnd();
}

void DesenhaInvasores() {
    for (int i = 0; i < invasors.size(); ++i)
        invasors.at(i)->draw();
}

// Função callback de redesenho da janela de visualização
void Desenha(void) {
    // Muda para o sistema de coordenadas do modelo
    glMatrixMode(GL_MODELVIEW);
    // Inicializa a matriz de transformação corrente
    glLoadIdentity();

    // Limpa a janela de visualização com a cor
    // de fundo definida previamente
    glClear(GL_COLOR_BUFFER_BIT);

    glTranslatef(aviao_x, 0.0f, 0.0f);
    glTranslatef(0.0f, -0.8f, 0.0f);    // Tras o conjunto do jato e misseis para bottom da tela
    glScalef(0.1, 0.1f, 0.0f); // Reduz 90% o tamanho do conjunto
    glPushMatrix();

    if (missel1_moving) {
        glTranslatef(-aviao_x, 0.0f, 0.0f);
        glTranslatef(missel1_tx, 0.0f, 0.0f);
    }
    //Míssel 1.
    glTranslatef(0.0f, missel1_y, 0.0f);
    DesenhaMisseis();

    glPopMatrix(); //Pro jatinho nao sair junto com o missel 1.
    // Desenha o jatinho.
    DesenhaAviao();

    // Desenha os invasores
    DesenhaInvasores();


    printf("Aviao (%f, y)\n", aviao_x);
    printf("Invasor (%f, %f)\n", invasors.at(0)->get_x(), invasors.at(0)->get_y());
    // Executa os comandos OpenGL
    glFlush();
}

// Função callback chamada quando o tamanho da janela é alterado 
void AlteraTamanhoJanela(GLsizei w, GLsizei h) {
    GLsizei largura, altura;

    // Evita a divisao por zero
    if (h == 0) h = 1;

    // Atualiza as variáveis
    largura = w;
    altura = h;

    // Especifica as dimensões da Viewport
    glViewport(0, 0, largura, altura);

    // Inicializa o sistema de coordenadas
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Estabelece a janela de seleção (esquerda, direita, inferior,
    // superior) mantendo a proporção com a janela de visualização
    if (largura <= altura) {
        gluOrtho2D(-1.0f, 1.0f, -1.0f * altura / largura, 1.0f * altura / largura);
        //win = 1.0f;
    } else {
        gluOrtho2D(-1.0f * largura / altura, 1.0f * largura / altura, -1.0f, 1.0f);
        //	win = 1.0f*largura/altura;
    }
}

// Função callback chamada para gerenciar eventos de teclas especiais(F1,PgDn,...)
void TeclasEspeciais(int key, int x, int y) {
    // Move a base
    if (key == GLUT_KEY_LEFT) {
        aviao_x -= 0.05;
        if (aviao_x < -0.9f) // Trava o aviao a esquerda da tela
            aviao_x = -0.9f;
    }
    if (key == GLUT_KEY_RIGHT) {
        aviao_x += 0.05;
        if (aviao_x > 0.9f) // Trava o aviao a direita da tela
            aviao_x = 0.9f;
    }

    glutPostRedisplay();
}

// Função callback chamada para gerenciar eventos de teclas
void Teclado(unsigned char key, int x, int y) {
    if (key == 27)
        exit(0);

    if (key == 32) {
        missel1_moving = true;
        missel1_tx = aviao_x;
        glutTimerFunc(10, move_missel1, 1);
    }
}

// Função responsável por inicializar parâmetros e variáveis
void Inicializa(void) {
    // Define a cor de fundo da janela de visualização como branca
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
            // Esses valores são uns aleatórios aí
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
    glutInit(&argc, argv); // Inicia uma instância da glut
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(5, 5);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Desenho de um protótipo de jatinho do Space Invaders!");

    // Registra a função callback de redesenho da janela de visualização
    glutDisplayFunc(Desenha);

    // Registra a função callback de redimensionamento da janela de visualização
    glutReshapeFunc(AlteraTamanhoJanela);

    // Registra a função callback para tratamento das teclas especiais
    glutSpecialFunc(TeclasEspeciais);

    // Registra a função callback para tratamento das teclas ASCII
    glutKeyboardFunc(Teclado);

    // Chama a função responsável por fazer as inicializações
    Inicializa();

    glutTimerFunc(0, move_missel1, 0); // Timer para mover o missel 1

    // Inicia o processamento e aguarda interações do usuário
    glutMainLoop();

    return 0;
}
