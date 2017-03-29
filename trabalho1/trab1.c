#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include <GL/freeglut.h>

GLfloat R = 0.0f, G = 0.0f, B = 0.0f;

GLuint background_texture;

GLuint loadBMP(const char * imagepath) 
{
	// Data read from the header of the BMP file
	
	// Each BMP file begins by a 54-bytes header
	unsigned char header[54];
	
	// Position in the file where the actual data begins
	unsigned int dataPos;
	unsigned int width, height;
	
	// = width*height*3
	unsigned int imageSize;

	// Actual RGB data
	unsigned char * data;

	// Open the file
	FILE * file = fopen(imagepath,"rb");
	if (!file) {
		printf("%s: Background image could not be opened\n", imagepath); 
		exit(1);
	}
	
	// If not 54 bytes read -> problem
	if ( fread(header, 1, 54, file) != 54 ) {
		printf("%s: Not a correct BMP file\n", imagepath);
		exit(1);
	}

	if ( header[0]!='B' || header[1]!='M' ){
		printf("%s: Not a correct BMP file\n", imagepath);
		exit(1);
	}

	// Read ints from the byte array
	dataPos    = *(int*)&(header[0x0A]);
	imageSize  = *(int*)&(header[0x22]);
	width      = *(int*)&(header[0x12]);
	height     = *(int*)&(header[0x16]);
	
	// Some BMP files are misformatted, guess missing information
	if (imageSize == 0) {
		// 3 : one byte for each Red, Green and Blue component
		imageSize = width*height*3; 
	}
	if (dataPos == 0) {
		// The BMP header is done that way
		dataPos = 54; 
	}

	// Create a buffer
	data = new unsigned char [imageSize];
	
	// Read the actual data from the file into the buffer
	fread(data, 1, imageSize, file);
	
	// Everything is in memory now, the file can be closed
	fclose(file);

	// Create one OpenGL texture
	GLuint textureID;
	glGenTextures(1, &textureID);
	
	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Give the image to OpenGL
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
	
	//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
	//gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);

	delete data;
	return textureID;
}

GLfloat sorteia_cor() 
{
	return (rand()*1.0f) / (RAND_MAX*1.0f);
}

void desenha(void) 
{
	/* Colorir o fundo da cena de branco */
	//glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	//glClear(GL_COLOR_BUFFER_BIT);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	/*
	glColor3f(R, G, B);
	glBegin(GL_QUADS);
		glVertex2f(100.0f, -100.0f);
		glVertex2f(100.0f, 100.0f);
		glVertex2f(300.0f, 100.0f);
		glVertex2f(300.0f, -100.0f);
	glEnd();
	*/

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, background_texture);
	glColor4f(1.0, 1.0, 1.0, 1.0); // reset gl color
	glBegin( GL_QUADS );
	glTexCoord2d(0.0,0.0); glVertex3d(100.0f, -100.0f, -1.0);
	glTexCoord2d(0.0,1.0); glVertex3d(100.0f, 100.0f, -1.0);
	glTexCoord2d(1.0,1.0); glVertex3d(300.0f, 100.0f, -1.0);
	glTexCoord2d(1.0,0.0); glVertex3d(300.0f, -100.0f, -1.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glFlush();
}

//		Eventos 
void on_mouseClick(int botao_clicado, int estado_do_click, int x_mouse_position, int y_mouse_position) {
	
	if(estado_do_click == GLUT_UP) {
		if(botao_clicado == GLUT_LEFT_BUTTON) {
			R = 0.0f;
			G = 0.0f;
			B = 0.0f;
		}

		if(botao_clicado == GLUT_RIGHT_BUTTON) {
			R = sorteia_cor();
			G = sorteia_cor();
			B = sorteia_cor();
		}
	}

	// Força a glut redesenhar a cena após a atualização.
	glutPostRedisplay();
}

int main(int argc, char* argv[])
{
	srand(time(NULL));

	glutInit(&argc, argv); // Inicia uma instância da glut
	//glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Define o modo de display do buffer
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600); // Define o tamanho em pixels da janela
	glutCreateWindow("Exemplo OpenGL"); // Define o título da janela
	glutDisplayFunc(desenha); // Estabelece que a função de rendering é a função "desenha(.)"

	glutMouseFunc(on_mouseClick); // Evento de click do mouse

	gluOrtho2D(0, 400, -150, 150); // Define o plano ortogonal em que a cena será construída

	background_texture = loadBMP("./data/xp.bmp");

	glutMainLoop(); // Inicia as operações conforme as especificações anteriores
}
