/*
Practica_6:
	Sistema solar
*/
#include <stdlib.h>
#include <GL/glut.h>
#include <windows.h>

float transZ = -10.0f;
float transX = 0.0f;
float transY = 0.0f;

float angleX = 0.0f;
float angleY = 0.0f;

struct timeval strart;
DWORD dwFrames = 0;
DWORD dwCurrentTime = 0;
DWORD dwLastUpdateTime = 0;
DWORD dwElapsedTime = 0;

int giraRotaLuisMi = 0.0f;
int giraRotaMercuri = 0.0f;
int giraRotaVenus = 0.0f;
int giraRotaTierra = 0.0f;
int giraRotaLuna = 0.0f;
int giraRotaMarte = 0.0f;

int giraTraslaMercurio = 0.0f;
int giraTraslaVenus = 0.0f;
int giraTraslaTierra = 0.0f;
int giraTraslaLuna = 0.0f;
int giraTraslaMarte = 0.0f;

float sol[3] = { 1.0, 1.0, 0.0 };
float mercurio[3] = { 0.956, 0.003, 0.239 };
float venus[3] = { 0.019, 0.486, 0.882 };
float tierra[3] = { 0.541, 0.462, 0.039 };
float luna[3] = { 0.556, 0.823, 0.796 };
float marte[3] = { 0.039, 0.247, 0.541 };

void inicializar(void) {
	glClearColor(0.831, 0.949, 0.988, 1);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void anima(void){
	// Calculate the number of frames per one second:
	//dwFrames++;
	dwCurrentTime = GetTickCount(); // Even better to use timeGetTime()
	dwElapsedTime = dwCurrentTime - dwLastUpdateTime;

	if (dwElapsedTime >= 30){
		giraRotaLuisMi = (giraRotaLuisMi - 1) % 360;
		giraRotaMercuri = (giraRotaMercuri - 1) % 360;
		giraTraslaMercurio = (giraTraslaMercurio - 3) % 360;
		giraRotaVenus = (giraRotaVenus - 1) % 360;
		giraTraslaVenus = (giraTraslaVenus - 1) % 360;
		giraRotaTierra = (giraRotaTierra - 1) % 360;
		giraTraslaTierra = (giraTraslaTierra - 1) % 360;
		giraRotaLuna = (giraRotaLuna - 1) % 360;
		giraTraslaLuna = (giraTraslaLuna - 1) % 360;
		giraRotaMarte = (giraRotaMarte - 1) % 360;
		giraTraslaMarte = (giraTraslaMarte - 1) % 360;

		dwLastUpdateTime = dwCurrentTime;
	}

	glutPostRedisplay();
}

void dibujar(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(transX, transY, transZ);
	glRotatef(angleY, 0.0, 1.0, 0.0);
	glRotatef(angleX, 1.0, 0.0, 0.0);

	// dibuja sol
	glColor3fv( sol );
	glPushMatrix();
		glRotatef(giraRotaLuisMi, 0.0, 1.0, 0.0); //el sol jira sobre su propio eje
		glutWireSphere(1.5, 30, 30);
	glPopMatrix();

	//dibuja mercurio
	glColor3fv(mercurio);
	glPushMatrix();
		glRotatef(giraTraslaMercurio,0.0, 1.0, 0.0); //movimiento de traslacion 
	
		glPushMatrix();
			glTranslatef(3.0, 0.0, 0.0);
			glRotatef(giraRotaMercuri, 0.0, 1.0, 0.0); //movimiento de rotacion
			glutWireSphere(0.3, 30, 30);
		glPopMatrix();
	glPopMatrix();

	//dibuja venus
	glColor3fv(venus);
	glPushMatrix();
		glRotatef(giraTraslaVenus,0.0, 1.0, 0.0); //movimiento de traslacion 
	
		glPushMatrix();
			glTranslatef(4.5, 0.0, 0.0);
			glRotatef(giraRotaVenus, 0.0, 1.0, 0.0); //movimiento de rotacion
			glutWireSphere(0.4, 30, 30);
		glPopMatrix();
	glPopMatrix();

	//dibujar tierra
	glColor3fv(tierra);
	glPushMatrix();
		glRotatef(giraTraslaTierra, 0.0, 1.0, 0.0); //movimiento de traslacion 

		glPushMatrix();
			glTranslatef(5.5, 0.0, 0.0);
			glRotatef(giraRotaTierra, 0.0, 1.0, 0.0); //movimiento de rotacion
			glutWireSphere(0.5, 30, 30);
			//dibujar luna
				glPushMatrix();
				glColor3fv(luna);
					glRotatef(giraTraslaLuna, 0.0, 1.0, 0.0); //movimiento de traslacion 
					glTranslatef(1.0, 0.0, 0.0);
					glRotatef(giraRotaLuna, 0.0, 1.0, 0.0); //movimiento de rotacion
					glutWireSphere(0.2, 30, 30);
				glPopMatrix();
		glPopMatrix();
	glPopMatrix();

	//dibuja marte
	glColor3fv(marte);
	glPushMatrix();
		glRotatef(giraTraslaMarte,0.0, 1.0, 0.0); //movimiento de traslacion 
	
		glPushMatrix();
			glTranslatef(8.5, 0.0, 0.0);
			glRotatef(giraRotaMarte, 0.0, 1.0, 0.0); //movimiento de rotacion
			glutWireSphere(0.3, 30, 30);
		glPopMatrix();
	glPopMatrix();


	glutSwapBuffers();
}

void remodelar(int width, int heigth){
	if (heigth == 0){
		heigth = 1;
	}
	glViewport(0, 0, width, heigth);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glFrustum(-5, 5, -5, 5, 4, 20.0);
	glutPostRedisplay();
}

void teclado(unsigned char key, int x, int y)
{
	switch (key) {
	case 'w': case 'W':  //acerca al objeto con traslación en z pos
		transZ += 0.2f;
		break;

	case 's': case 'S':  //aleja al objeto con traslación en z neg
		transZ -= 0.2f;
		break;

	case 'a': case 'A':  //traslada objeto hacia la derecha en x pos
		transX += 0.2f;
		break;

	case 'd': case 'D':  //traslada objeto hacia la izquierda en x neg
		transX -= 0.2f;
		break;

	case 'e': case 'E':  //traslada objeto hacia arriba en y pos
		transY += 0.2f;
		break;

	case 'c': case 'C':  //traslada objeto hacia abajo en y neg
		transY -= 0.2f;
		break;


	case 27:  //Si presiona tecla ESC (ASCII 27) sale
		exit(0);
		break;

	default:  //Si es cualquier otra tecla no hace nada
		break;
	}

	glutPostRedisplay();
}


void teclasFlechas(int tecla, int x, int y)  // Funcion para manejo de teclas especiales (arrow keys)
{
	switch (tecla) {
	case GLUT_KEY_UP:  //gira sobre x sentido antihorario, valor positivo
		angleX += 2.0f;
		break;
	case GLUT_KEY_DOWN:  //gira sobre x sentido horario, valor negativo
		angleX -= 2.0f;
		break;
	case GLUT_KEY_LEFT:  //gira sobre y sentido antihorario, valor positivo
		angleY += 2.0f;
		break;
	case GLUT_KEY_RIGHT:  //gira sobre y sentido horario, valor negativo
		angleY -= 2.0f;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 250);
	glutInitWindowPosition(50, 25);
	glutCreateWindow(argv[1]);
	inicializar();
	glutDisplayFunc(dibujar);
	glutReshapeFunc(remodelar);
	glutKeyboardFunc(teclado);
	glutSpecialFunc(teclasFlechas);
	glutIdleFunc(anima);
	glutMainLoop();

	return 0;
}