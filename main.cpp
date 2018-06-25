#include <windows.h>
#include <GL/glut.h>
#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int altura = 600, largura = 400;
int tab[3][3];
int turno, j1, j2;
bool acabou, flag = true;
int vencedor;
const int VAZIO = 0, X = 1, O = 2;
GLfloat fAspect;

void AlteraTamanhoJanela(int x, int y);
int Vencedor();
bool Empate();
void DesenhaString(void *fonte, const char s[], float x, float y);
void Clique(int botao, int estado, int x, int y);
void GerarCampo();
void Inicializa();
void GerarCirculo(float cx, float cy, float r, int num_segmentos);
void GerarX(int i, int j);
void GerarXO();
void DesenhaJ1eJ2();
void Desenha();
void NovoJogo(unsigned char tecla, int x, int y);

int main(){
    PlaySound("C:\\Users\\Joao Marcos\\Desktop\\Jogo_da_velha\\musica.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
    Inicializa();

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(550, 100);
	glutInitWindowSize(largura, altura);
	glutCreateWindow("Jogo da Velha");
	glutReshapeFunc(AlteraTamanhoJanela);
	glutDisplayFunc(Desenha);
	glutKeyboardFunc(NovoJogo);
    glutMouseFunc(Clique);
    glutIdleFunc(Desenha);
	glutMainLoop();

	return 0;
}

int Vencedor(){
    int largura = 400;
    int altura = 400;
    int tam = 3;

    ///primeira linha
    if  (tab[0][0] != VAZIO && tab[0][0] == tab[0][1] && tab[0][1] == tab[0][2]){
        glBegin(GL_QUADS);
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex2f(0,(altura / 6) - tam);
            glVertex2f(0, (altura / 6) + tam);
            glVertex2f(largura,(altura / 6) + tam);
            glVertex2f(largura,(altura / 6) - tam);
        glEnd();
        glFlush();
        return turno;
    }

    ///segunda linha
    else if (tab[1][0] != VAZIO && tab[1][0] == tab[1][1] && tab[1][1] == tab[1][2]){
        glBegin(GL_QUADS);
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex2f(0, ((altura / 6) * 3) - tam);
            glVertex2f(0, ((altura / 6) * 3) + tam);
            glVertex2f(largura, ((altura / 6) * 3) + tam);
            glVertex2f(largura, ((altura / 6) * 3) - tam);
        glEnd();
        glFlush();
        return turno;
    }

    ///terceira linha
    else if (tab[2][0] != VAZIO && tab[2][0] == tab[2][1] && tab[2][1] == tab[2][2]){
        glBegin(GL_QUADS);
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex2f(0, ((altura / 6) * 5) - tam);
            glVertex2f(0, ((altura / 6) * 5) + tam);
            glVertex2f(largura, ((altura / 6) * 5) + tam);
            glVertex2f(largura, ((altura / 6) * 5) - tam);
        glEnd();
        glFlush();
        return turno;
    }

    ///primeira coluna
    else if (tab[0][0] != VAZIO && tab[0][0] == tab[1][0] && tab[1][0] == tab[2][0]){
        glBegin(GL_QUADS);
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex2f((largura / 6) - tam, 0);
            glVertex2f((largura / 6) + tam, 0);
            glVertex2f((largura / 6) + tam, altura);
            glVertex2f((largura / 6) - tam, altura);
        glEnd();
        glFlush();
        return turno;
    }

    ///segunda coluna
    else if (tab[0][1] != VAZIO && tab[0][1] == tab[1][1] && tab[1][1] == tab[2][1]){
        glBegin(GL_QUADS);
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex2f(((largura / 6) * 3) - tam, altura);
            glVertex2f(((largura / 6) * 3) + tam, altura);
            glVertex2f(((largura / 6) * 3) + tam, 0);
            glVertex2f(((largura / 6) * 3) - tam, 0);
        glEnd();
        glFlush();
        return turno;
    }

    ///terceira coluna
    else if (tab[0][2] != VAZIO && tab[0][2] == tab[1][2] && tab[1][2] == tab[2][2]){
        glBegin(GL_QUADS);
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex2f(((largura / 6) * 5) - tam, altura);
            glVertex2f(((largura / 6) * 5) + tam, altura);
            glVertex2f(((largura / 6) * 5) + tam, 0);
            glVertex2f(((largura / 6) * 5) - tam, 0);
        glEnd();
        glFlush();
        return turno;
    }

    ///diagonal principal
    else if (tab[0][0] != VAZIO && tab[0][0] == tab[1][1] && tab[1][1] == tab[2][2]){
        glBegin(GL_QUADS);
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex2f(0, 0 + tam);
            glVertex2f(largura - tam, altura);
            glVertex2f(largura, altura - tam);
             glVertex2f(0 + tam, 0);
        glEnd();
        glFlush();
        return turno;
    }

    ///diagonal secundaria
    else if (tab[0][2] != VAZIO && tab[0][2] == tab[1][1] && tab[1][1] == tab[2][0]){
        glBegin(GL_QUADS);
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex2f(largura - tam, 0);
            glVertex2f(0, altura - tam);
            glVertex2f(0 + tam, altura);
            glVertex2f(largura, 0 + tam);
        glEnd();
        glFlush();
        return turno;
    }
    return 0;
}

bool Empate(){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(tab[i][j] == 0)
                return false;
        }
    }
    return true;
}

void DesenhaString(void *fonte, const char s[], float x, float y){
    glRasterPos2f(x, y);
	for(unsigned int i = 0; i < strlen(s); i++){
		glutBitmapCharacter(fonte, s[i]);
	}
}

void Clique(int botao, int estado, int x, int y){
    int a = 25, b = 133;
    if(acabou == false && botao == GLUT_LEFT_BUTTON && estado == GLUT_DOWN){
        if(turno == X){
            if(tab[(y - a) / b][x / b] == 0){
                tab[(y - a) / b][x / b] = X;
                turno = O;

            }
        }
        else if(turno == O){
            if(tab[(y - a) / b][x / b] == 0){
                tab[(y - a) / b][x / b] = O;
                turno = X;
            }
        }
    }
}

void GerarCampo(){
    int largura = 400;
    int altura = 400;

    glBegin(GL_LINES);
    glColor3f(1.0f, 1.0f, 1.0f);

    glVertex2f(largura / 3, 0);
	glVertex2f(largura / 3, altura);

	glVertex2f((largura / 3) * 2, altura);
	glVertex2f((largura / 3) * 2, 0);

	glVertex2f(0, altura / 3);
	glVertex2f(largura, altura / 3);

	glVertex2f(0, (altura / 3) * 2);
	glVertex2f(largura, (altura / 3) * 2);

	glEnd();
}

void Inicializa(){
    turno = X;
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            tab[i][j] = VAZIO;
        }
    }
}

void AlteraTamanhoJanela(int x, int y){
    glViewport(0, 0, x, y);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, x, y, 0, 0, 1);
	glMatrixMode(GL_MODELVIEW);
	/// Para não poder redimensionar a janela
	glutReshapeWindow(largura, altura);
}

void GerarCirculo(float cx, float cy, float r, int num_segmentos){
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < num_segmentos; i++){
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segmentos);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

void GerarX(int i, int j){
    int a = 133;
    glBegin(GL_LINES);
        glVertex2f(25  + j * a, 25  + i * a);
        glVertex2f(108 + j * a, 108 + i * a);
        glVertex2f(25  + j * a, 108 + i * a);
        glVertex2f(108 + j * a, 25  + i * a);
    glEnd();
}

void GerarXO(){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(tab[i][j] == 1){
                GerarX(i, j);
            }
            else if(tab[i][j] == 2){
                GerarCirculo(66 + j * 133, 66 + i * 133, 40, 20);
            }
        }
    }
}

void DesenhaJ1eJ2(){
    DesenhaString(GLUT_BITMAP_TIMES_ROMAN_24, "J1", 50, 460);
    std::ostringstream ostr;
    ostr << j1;
    std::string s = ostr.str();
    DesenhaString(GLUT_BITMAP_TIMES_ROMAN_24, s.c_str(), 50, 480);

    DesenhaString(GLUT_BITMAP_TIMES_ROMAN_24, "J2", 330, 460);
    ostr.str(std::string());
    ostr.clear();
    ostr << j2;
    s = ostr.str();
    DesenhaString(GLUT_BITMAP_TIMES_ROMAN_24, s.c_str(), 330, 480);
}

void Desenha(){
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0, 0, 0, 1);
	glColor3f(1, 1, 1);
	if(turno == X){
		DesenhaString(GLUT_BITMAP_TIMES_ROMAN_24, "Turno do jogador 1", 105, 490);
	}
	else {
		DesenhaString(GLUT_BITMAP_TIMES_ROMAN_24, "Turno do jogador 2", 105, 490);
	}

    GerarCampo();
    GerarXO();

    DesenhaJ1eJ2();

    vencedor = Vencedor();

    if(flag == true){
        if(vencedor == X){
            j2++;
            flag = false;
        }
        else if(vencedor == O){
            j1++;
            flag = false;
        }

    }

    if(vencedor){
        if(turno == X){
            acabou = true;
        }
        else {
            acabou = true;
        }
    }
    else if(Empate()){
        acabou = true;
    }

    if(acabou == true){
        glColor3f(0, 0, 0);
        DesenhaString(GLUT_BITMAP_TIMES_ROMAN_24, "Turno do jogador 1", 105, 490);
        DesenhaString(GLUT_BITMAP_TIMES_ROMAN_24, "Turno do jogador 2", 105, 490);
        glColor3f(1.0f, 1.0f, 1.0f);
        DesenhaString(GLUT_BITMAP_TIMES_ROMAN_24, "Game Over", 146, 470);
		if(vencedor == VAZIO){
			DesenhaString(GLUT_BITMAP_TIMES_ROMAN_24, "Empate", 165, 495);
		}
		else if(vencedor == O){
			DesenhaString(GLUT_BITMAP_TIMES_ROMAN_24, "Jogador 1 ganhou", 115, 495);
		}
		else if(vencedor == X){
			DesenhaString(GLUT_BITMAP_TIMES_ROMAN_24, "Jogador 2 ganhou", 115, 495);
		}
		DesenhaString(GLUT_BITMAP_TIMES_ROMAN_24, "Deseja continuar? (S/N)", 90, 520);
    }

    glutSwapBuffers();
}

void NovoJogo(unsigned char tecla, int x, int y){
    if(acabou == true){
        if(tecla == 'S' || tecla == 's'){
            acabou = false;
            flag = true;
            Inicializa();
        }
        else if(tecla == 'N' || tecla == 'n'){
            exit(0);
        }
    }
}
