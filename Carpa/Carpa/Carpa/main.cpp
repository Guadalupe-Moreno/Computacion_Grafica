/*
Modelo:
	Emplenado texturisado y figuras 3D, modelar una carpa de circo 
*/
#include <stdlib.h>
#include <GL/glut.h>
#include <windows.h>
#include "figuras.h"
#include "Textura_negro.c"
#include "Textura_CI.c"
#include "Textura_CS.c"

//variables para acumular traslación con teclas w,s (en z) a,d (en x) e,c (en y)
float transZ = -5.0f;
float transX = 0.0f;
float transY = 0.0f;

//variables para acumular rotación con flechas de dirección
float angleX = 0.0f;
float angleY = 0.0f;

//identificadores de textura
GLuint idTextura_negro;
GLuint idTextura_CI;
GLuint idTextura_CS;

struct timeval strart;
DWORD dwFrames = 0;
DWORD dwCurrentTime = 0;
DWORD dwLastUpdateTime = 0;
DWORD dwElapsedTime = 0;

int giraRotaTorso = 0.0f;
int giraRotaP1 = 0.0f;

//función para inicializar estados de gl
void inicializar(void)
{
	glClearColor(0.831, 0.949, 0.988, 1);
	glClearDepth(1.0f);									// Configuramos Depth Buffer
	glEnable(GL_DEPTH_TEST);							// Habilitamos Depth Testing
	glDepthFunc(GL_LEQUAL);								// Tipo de Depth Testing a realizar
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	
	//cargaa textura negro
	glGenTextures(1, &idTextura_negro);
	glBindTexture(GL_TEXTURE_2D, idTextura_negro);

	gluBuild2DMipmaps(GL_TEXTURE_2D,
		Textura_negro.bytes_per_pixel, Textura_negro.width,
		Textura_negro.height, GL_RGB, GL_UNSIGNED_BYTE,
		Textura_negro.pixel_data);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// En caso de no querer repetir las texturas, comentar estas
	// dos líneas
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	glEnable(GL_TEXTURE_2D);

	//cargaa textura carpa_inf
	glGenTextures(1, &idTextura_CI);
	glBindTexture(GL_TEXTURE_2D, idTextura_CI);

	gluBuild2DMipmaps(GL_TEXTURE_2D,
		Textura_CI.bytes_per_pixel, Textura_CI.width,
		Textura_CI.height, GL_RGB, GL_UNSIGNED_BYTE,
		Textura_CI.pixel_data);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// En caso de no querer repetir las texturas, comentar estas
	// dos líneas
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	glEnable(GL_TEXTURE_2D);

	//cargaa textura carpa_sup
	glGenTextures(1, &idTextura_CS);
	glBindTexture(GL_TEXTURE_2D, idTextura_CS);

	gluBuild2DMipmaps(GL_TEXTURE_2D,
		Textura_CS.bytes_per_pixel, Textura_CS.width,
		Textura_CS.height, GL_RGB, GL_UNSIGNED_BYTE,
		Textura_CS.pixel_data);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// En caso de no querer repetir las texturas, comentar estas
	// dos líneas
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	glEnable(GL_TEXTURE_2D);

}

void anima(void) {
	// Calculate the number of frames per one second:
	//dwFrames++;
	dwCurrentTime = GetTickCount(); // Even better to use timeGetTime()
	dwElapsedTime = dwCurrentTime - dwLastUpdateTime;

	if (dwElapsedTime >= 30) {
		giraRotaTorso = (giraRotaTorso - 1) % 360;
		giraRotaP1 = (giraRotaP1 - 1) % 360;

		dwLastUpdateTime = dwCurrentTime;
	}

	glutPostRedisplay();
}

void dibujar(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Limpiamos pantalla y Depth Buffer

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	//se debe recorrer hacia z negativo xq la cara de enfrente está mi espalda
	//si no lo recorro lo suficiente las caras de los lados se verán largas
	glTranslatef(transX, transY, transZ);
	glRotatef(angleY, 0.0, 1.0, 0.0);	 //gira sobre y sentido horario
	glRotatef(angleX, 1.0, 0.0, 0.0);	 //gira sobre x sentido antihorario

	//dibujar cuerpo
	//dibujar base
	glPushMatrix();
		glTranslatef(0.0f, -0.5f, 0.0f);
		cilindro(1.5, 1.5, 50, idTextura_CI);
	glPopMatrix();

	//dibujar cono superior
	glPushMatrix();
		glTranslatef(0.0f, 1.0f, 0.0f);
		cono(1, 2.0, 50, idTextura_CI);
	glPopMatrix();

	//dibujar banderin
	//palo
	glPushMatrix();
		glTranslatef(0.0f, 1.75f, 0.0f);
		cilindro(0.1, 1.0, 50, idTextura_negro);
	glPopMatrix();
	//bandera
	glPushMatrix();
		glTranslatef(0.5f, 2.5f, 0.0f);
		glScalef(1, 0.5, 0.1);
		prisma2(idTextura_CS, idTextura_CS);
	glPopMatrix();

	glFlush();

}

void remodelar(int width, int height)   // Creamos funcion Reshape
{
	if (height == 0)										// Prevenir division entre cero
	{
		height = 1;
	}

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);						// Seleccionamos Projection Matrix
	glLoadIdentity();

	// Tipo de Vista
	//glFrustum(-5, 5, -5, 5, 0.1, 50.0);
	glFrustum(-0.1, 0.1, -0.1, 0.1, 0.1, 50.0);
	

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


int main(int argc, char* argv[])
{
	//inicializa GLUT con el sistema de ventanas pasando los argumentos del main
	glutInit(&argc, argv);
	//Buffer simple para dibujar
	//Colores RGB y alpha
	//Buffer de profundidad
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE | GLUT_DEPTH);
	//Define ventana de 500 pixeles de ancho por 500 de alto
	glutInitWindowSize(600, 600);
	//Posiciona la ventana de izquierda a derecha 50 pixeles y de arriba a abajo 25
	glutInitWindowPosition(400, 100);
	//Crea y abre la ventana y recibe el nombre que va en su barra de título
	glutCreateWindow(argv[1]);
	//Llamada a función propia para inicializar estados de opengl
	inicializar();
	//Llamada a la función a ser dibujada y redibujada
	glutDisplayFunc(dibujar);
	glutReshapeFunc(remodelar);
	//Lamada a función que maneja eventos del teclado
	glutKeyboardFunc(teclado);
	glutSpecialFunc(teclasFlechas);
	glutIdleFunc(anima);
	//Llamada a función que cede el control a GLUT y procesa eventos de ventana, ratón
	glutMainLoop();

	//termina la ejecución devolviendo cero
	return 0;
}