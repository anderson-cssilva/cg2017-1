#include <iostream>
#include <GL/glut.h>
#include <stdlib.h>
#include <vector>
#include <math.h>


using namespace std;

	// Pontos/Vetores no R^3.
	struct GLPoint{
		GLfloat x;
		GLfloat y;
		GLfloat z;
	//	GLPoint(void){}
	//	GLPoint(GLfloat _x, GLfloat _y, GLfloat _z): x(_x), y(_y), z(_z) {}
	};
	
	// Estrutura de pontos com seus respecrivos
	//vetores normais.
	struct GLCell{
		GLPoint ponto;
		GLPoint vetor_normal;
	};
	


class Rendering{
	
	private:
		
	//Tamanho da "malha".
	int N;
	GLfloat R;
	
	//Dimensões do domínio.
	GLfloat x_min, x_max, y_min, y_max;
	GLfloat h_x, h_y;
	
	//"Malha": Conjunto dos pontos com seus respectivos vetores
	//normais de uma dada superfície.
	vector<vector<GLCell> > mesh;
	
	//Calcula o produto vetorial de dois vetores vet_a e vet_b.
	GLPoint produto_vetorial(GLPoint vet_a, GLPoint vet_b){
		GLPoint result;
		
		result.x = vet_a.y*vet_b.z - vet_b.y*vet_a.z;
		result.y = vet_a.z*vet_b.x - vet_b.z*vet_a.x;
		result.z = vet_a.x*vet_b.y - vet_b.x*vet_a.y;
		
		return result;
	}
	
	//Calcula a normalização euclidiana de um dado vetor v.
	GLPoint normalize(GLPoint v){
		GLPoint v_norm;
		GLfloat norma = sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
		
		v_norm.x = v.x/norma;
		v_norm.y = v.y/norma;
		v_norm.z = v.z/norma;
		
		return v_norm;
	}
	
	//Função z = f(x,y).
	GLfloat f(GLfloat x, GLfloat y){
		
		return 10*exp((-x*x-y*y)/300);
		
	}
	
	//Calcula os pontos da malha (sem as respectivas normais).
	void calc_mesh_points(void){
		GLfloat x, y, z, theta, phi;
		
		for(int i = 0; i < N+2; i++)
			for(int j = 0; j < N+2; j++){
				
				theta = x_min + (j)*h_x;
				phi = y_min + (i)*h_y;
				
				x = R*sin(phi)*cos(theta);
				z = R*sin(phi)*sin(theta);
				y = R*cos(phi);
				
				this->mesh[i][j].ponto.x = x;
				this->mesh[i][j].ponto.y = y;
				this->mesh[i][j].ponto.z = z;
			}		
	}
	
	//Adiciona os vetores normais à malha.
	void add_normais(void){
		//Pontos de controle.
		GLPoint P1, P2, P3;
		//v1 = P2-P1, v2 = P3-P1; (Vetores)
		GLPoint v1, v2;
		//Vetor normal no ponto.
		GLPoint vet_normal;
		
		
		for(int i = 1; i < (N+2)-1; i++)
			for(int j = 1; j < (N+2)-1; j++){
				P1 = mesh[i][j].ponto;
				P2 = mesh[i][j+1].ponto;
				P3 = mesh[i+1][j].ponto;
				
				//Cálculo de v1:
				v1.x = P2.x-P1.x;
				v1.y = P2.y-P1.y;
				v1.z = P2.z-P1.z;
				
				//Cálculo de v2:
				v2.x = -P3.x+P1.x;
				v2.y = -P3.y+P1.y;
				v2.z = -P3.z+P1.z;
				
				//Cálculo do vetor normal:
				vet_normal = normalize(produto_vetorial(v1, v2));
				
				mesh[i][j].vetor_normal.x = vet_normal.x;
				mesh[i][j].vetor_normal.y = vet_normal.y;
				mesh[i][j].vetor_normal.z = vet_normal.z;
			}
	}
		
		
	public:
	Rendering(int N, GLfloat x_min, GLfloat x_max, GLfloat y_min, GLfloat y_max, GLfloat R){
		this->N = N;
		
		//theta define o plano xy
		this->x_min = x_min; // theta_0 = 0
		this->x_max = x_max; // theta_f = 2pi
		
		// phi define o plano yz
		this->y_min = y_min; // phi_0 = 0
		this->y_max = y_max; // phi_f = pi
		
		//Definição dos passos.
		this->h_x = (x_max - x_min)/(1.0*N);
		this->h_y = (y_max - y_min)/(1.0*N);
		
		this->R = R;
		
		//Inicializa a malha de tamanho N+2xN+2.
		this->mesh.resize(N+2);
		for ( int i = 0 ; i < N+2 ; i++ )
  			 this->mesh[i].resize(N+2);
		
	}
	
	vector<vector<GLCell> > getMesh(){
		calc_mesh_points();
		add_normais();
		
		return this->mesh;
	}
	
};
