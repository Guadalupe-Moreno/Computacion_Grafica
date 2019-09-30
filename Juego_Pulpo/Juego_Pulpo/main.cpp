/*
Modelo:
	Emplenado texturisado y figuras 3D, modelar un pokemon pulpo
*/
#include <stdlib.h>
#include <GL/glut.h>
#include <windows.h>
#include "figuras.h"
#include "Textura_piel.c"
#include "Textura_bola.c"
#include "Textura_blanco.c"
#include "Textura_negro.c"
#include "Textura_piso.c"
#include "Textura_P1.c"
#include "Textura_P2.c"
#include "Textura_P3.c"
#include "Textura_P4.c"
#include "Textura_P5.c"
#include "Textura_P6.c"

//variables para acumular traslación con teclas w,s (en z) a,d (en x) e,c (en y)
float transZ = -5.0f;
float transX = 0.0f;
float transY = 0.0f;

//variables para acumular rotación con flechas de dirección
float angleX = 0.0f;
float angleY = 0.0f;

//identificadores de textura
GLuint idTextura_piel;
GLuint idTextura_bola;
GLuint idTextura_blanco;
GLuint idTextura_negro;
GLuint idTextura_piso;
GLuint idTextura_P1;
GLuint idTextura_P2;
GLuint idTextura_P3;
GLuint idTextura_P4;
GLuint idTextura_P5;
GLuint idTextura_P6;

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

	//cargaa textura piel
	glGenTextures(1, &idTextura_piel);
	glBindTexture(GL_TEXTURE_2D, idTextura_piel);

	gluBuild2DMipmaps(GL_TEXTURE_2D,
		Textura_piel.bytes_per_pixel, Textura_piel.width,
		Textura_piel.height, GL_RGB, GL_UNSIGNED_BYTE,
		Textura_piel.pixel_data);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// En caso de no querer repetir las texturas, comentar estas
	// dos líneas
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	glEnable(GL_TEXTURE_2D);

	//cargaa textura bola
	glGenTextures(1, &idTextura_bola);
	glBindTexture(GL_TEXTURE_2D, idTextura_bola);

	gluBuild2DMipmaps(GL_TEXTURE_2D,
		Textura_bola.bytes_per_pixel, Textura_bola.width,
		Textura_bola.height, GL_RGB, GL_UNSIGNED_BYTE,
		Textura_bola.pixel_data);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// En caso de no querer repetir las texturas, comentar estas
	// dos líneas
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	glEnable(GL_TEXTURE_2D);

	//cargaa textura blanco
	glGenTextures(1, &idTextura_blanco);
	glBindTexture(GL_TEXTURE_2D, idTextura_blanco);

	gluBuild2DMipmaps(GL_TEXTURE_2D,
		Textura_blanco.bytes_per_pixel, Textura_blanco.width,
		Textura_blanco.height, GL_RGB, GL_UNSIGNED_BYTE,
		Textura_blanco.pixel_data);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// En caso de no querer repetir las texturas, comentar estas
	// dos líneas
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	glEnable(GL_TEXTURE_2D);

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

	//cargaa textura piso
	glGenTextures(1, &idTextura_piso);
	glBindTexture(GL_TEXTURE_2D, idTextura_piso);

	gluBuild2DMipmaps(GL_TEXTURE_2D,
		Textura_piso.bytes_per_pixel, Textura_piso.width,
		Textura_piso.height, GL_RGB, GL_UNSIGNED_BYTE,
		Textura_piso.pixel_data);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// En caso de no querer repetir las texturas, comentar estas
	// dos líneas
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	glEnable(GL_TEXTURE_2D);

	//cargaa textura pokebola 1
	glGenTextures(1, &idTextura_P1);
	glBindTexture(GL_TEXTURE_2D, idTextura_P1);

	gluBuild2DMipmaps(GL_TEXTURE_2D,
		Textura_P1.bytes_per_pixel, Textura_P1.width,
		Textura_P1.height, GL_RGB, GL_UNSIGNED_BYTE,
		Textura_P1.pixel_data);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// En caso de no querer repetir las texturas, comentar estas
	// dos líneas
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	glEnable(GL_TEXTURE_2D);

	//cargaa textura pokebola 2
	glGenTextures(1, &idTextura_P2);
	glBindTexture(GL_TEXTURE_2D, idTextura_P2);

	gluBuild2DMipmaps(GL_TEXTURE_2D,
		Textura_P2.bytes_per_pixel, Textura_P2.width,
		Textura_P2.height, GL_RGB, GL_UNSIGNED_BYTE,
		Textura_P2.pixel_data);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// En caso de no querer repetir las texturas, comentar estas
	// dos líneas
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	glEnable(GL_TEXTURE_2D);

	//cargaa textura pokebola 3
	glGenTextures(1, &idTextura_P3);
	glBindTexture(GL_TEXTURE_2D, idTextura_P3);

	gluBuild2DMipmaps(GL_TEXTURE_2D,
		Textura_P3.bytes_per_pixel, Textura_P3.width,
		Textura_P3.height, GL_RGB, GL_UNSIGNED_BYTE,
		Textura_P3.pixel_data);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// En caso de no querer repetir las texturas, comentar estas
	// dos líneas
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	glEnable(GL_TEXTURE_2D);

	//cargaa textura pokebola 4
	glGenTextures(1, &idTextura_P4);
	glBindTexture(GL_TEXTURE_2D, idTextura_P4);

	gluBuild2DMipmaps(GL_TEXTURE_2D,
		Textura_P4.bytes_per_pixel, Textura_P4.width,
		Textura_P4.height, GL_RGB, GL_UNSIGNED_BYTE,
		Textura_P4.pixel_data);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// En caso de no querer repetir las texturas, comentar estas
	// dos líneas
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	glEnable(GL_TEXTURE_2D);

	//cargaa textura pokebola 5
	glGenTextures(1, &idTextura_P5);
	glBindTexture(GL_TEXTURE_2D, idTextura_P5);

	gluBuild2DMipmaps(GL_TEXTURE_2D,
		Textura_P5.bytes_per_pixel, Textura_P5.width,
		Textura_P5.height, GL_RGB, GL_UNSIGNED_BYTE,
		Textura_P5.pixel_data);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// En caso de no querer repetir las texturas, comentar estas
	// dos líneas
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	glEnable(GL_TEXTURE_2D);

	//cargaa textura pokebola 6
	glGenTextures(1, &idTextura_P6);
	glBindTexture(GL_TEXTURE_2D, idTextura_P6);

	gluBuild2DMipmaps(GL_TEXTURE_2D,
		Textura_P6.bytes_per_pixel, Textura_P6.width,
		Textura_P6.height, GL_RGB, GL_UNSIGNED_BYTE,
		Textura_P6.pixel_data);

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
	glTranslatef(0.0f, -2.5f, 0.0f);
	cilindro(0.75, 1.5, 50, idTextura_piel);
		glPushMatrix();
		glLoadIdentity();
		glTranslatef(transX, transY, transZ);
		glRotatef(angleY, 0.0, 1.0, 0.0);
		glRotatef(angleX, 1.0, 0.0, 0.0);
			glTranslatef(0.0f, -2.5f, 0.0f);
			glScalef(2, 0.5, 2);
			prisma2(idTextura_piso, idTextura_piso);
		glPopMatrix();
		glPushMatrix();
		glLoadIdentity();
		glTranslatef(transX, transY, transZ);
		glRotatef(angleY, 0.0, 1.0, 0.0);
		glRotatef(angleX, 1.0, 0.0, 0.0);
			glTranslatef(0.0f, -3.0f, 0.0f);
			glScalef(3, 0.5, 3);
			prisma2(idTextura_piso, idTextura_piso);
		glPopMatrix();
		glPushMatrix();
		glLoadIdentity();
		glTranslatef(transX, transY, transZ);
		glRotatef(angleY, 0.0, 1.0, 0.0);
		glRotatef(angleX, 1.0, 0.0, 0.0);
			glTranslatef(0.0f, -3.5f, 0.0f);
			glScalef(4, 0.5, 4);
			prisma2(idTextura_piso, idTextura_piso);
		glPopMatrix();
	glPopMatrix();

	//dibujar bola inferior
	glPushMatrix();
	glTranslatef(0.0f, 0.5f, 0.0f);
	glRotatef(giraRotaTorso, 0.0, 1.0, 0.0); //el torso jira sobre su propio eje
	esfera(2.0, 50, 50, idTextura_piel);

		//tentaculo derecho

		glPushMatrix();
			glTranslatef(1.75f, 0.0f, 0.0f);
			esfera(0.5, 50, 50, idTextura_bola);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(1.5f, -0.5f, 0.0f);
			glRotatef(240.0f, 0.0, 0.0, 1.0);
			cilindro(0.75, 1.0, 50, idTextura_piel);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0f, -0.5f, 0.0f);
			glTranslatef(4.5f, -0.5f, 0.0f);
			glRotatef(90.0f, 0.0, 0.0, 1.0);
			cilindro(0.70, 2.0, 50, idTextura_piel);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0f, -0.5f, 0.0f);
			glTranslatef(2.5f, -0.5f, 0.0f);
			esfera(0.75, 50, 50, idTextura_bola);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0f, -0.5f, 0.0f);
			glTranslatef(4.5f, -0.5f, 0.0f);
			esfera(0.75, 50, 50, idTextura_bola);
			glPushMatrix();
				glTranslatef(0.0f, -0.1f, 0.0f);
				glRotatef(315.0f, 0.0, 0.0, 1.0);
				cilindro(0.60, 1.0, 50, idTextura_piel);
			glPopMatrix();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0f, -0.5f, 0.0f);
			glTranslatef(5.0f, 0.5f, 0.0f);
			glRotatef(giraRotaP1, 1.0, 0.0, 0.0); //el asiento jira sobre su propio eje
			esfera(1.0, 50, 50, idTextura_P1);
		glPopMatrix();

		
		//tentaculo atras derecho

		glPushMatrix();
			glTranslatef(1.0f, 0.0f, -1.5f);
			esfera(0.5, 50, 50, idTextura_bola);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(1.0f, -1.0f, -2.0f);
			glRotatef(330.0f, 0.0, 1.0, 0.0);
			glRotatef(55.0f, 1.0, 0.0, 0.0);
			cilindro(0.75, 1.0, 50, idTextura_piel);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0f, -0.5f, 0.0f);
			glTranslatef(1.0f, -0.60f, -2.2f);
			esfera(0.80, 50, 50, idTextura_bola);
			glPushMatrix();
				glTranslatef(1.0f, -0.1f, -2.0f);
				glRotatef(330.0f, 0.0, 1.0, 0.0);
				glRotatef(90.0f, 1.0, 0.0, 0.0);
				cilindro(0.70, 2.0, 50, idTextura_piel);
			glPopMatrix();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0f, -0.5f, 0.0f);
		glTranslatef(1.9f, -0.70f, -4.0f);
		esfera(0.75, 50, 50, idTextura_bola);
			glPushMatrix();
				glTranslatef(0.0f, 0.1f, 0.0f);
				glRotatef(330.0f, 0.0, 1.0, 0.0);
				glRotatef(315.0f, 1.0, 0.0, 0.0);
				cilindro(0.60, 1.0, 50, idTextura_piel);
			glPopMatrix();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0f, -0.5f, 0.0f);
			glTranslatef(2.5f, 0.70f, -5.0f);
			glRotatef(giraRotaP1, 1.0, 0.0, 0.0); //el asiento jira sobre su propio eje
			esfera(1.0, 50, 50, idTextura_P2);
		glPopMatrix();

		//tentaculo atras izquierdo

		glPushMatrix();
			glTranslatef(-1.0f, 0.0f, -1.5f);
			esfera(0.5, 50, 50, idTextura_bola);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-1.0f, -1.0f, -2.0f);
			glRotatef(30.0f, 0.0, 1.0, 0.0);
			glRotatef(55.0f, 1.0, 0.0, 0.0);
			cilindro(0.75, 1.0, 50, idTextura_piel);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0f, -0.5f, 0.0f);
			glTranslatef(-1.0f, -0.60f, -2.2f);
			esfera(0.80, 50, 50, idTextura_bola);
			glPushMatrix();
				glTranslatef(-1.0f, -0.1f, -2.0f);
				glRotatef(30.0f, 0.0, 1.0, 0.0);
				glRotatef(90.0f, 1.0, 0.0, 0.0);
				cilindro(0.70, 2.0, 50, idTextura_piel);
			glPopMatrix();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0f, -0.5f, 0.0f);
			glTranslatef(-1.9f, -0.70f, -4.0f);
			esfera(0.75, 50, 50, idTextura_bola);
			glPushMatrix();
				glTranslatef(0.0f, 0.1f, 0.0f);
				glRotatef(30.0f, 0.0, 1.0, 0.0);
				glRotatef(315.0f, 1.0, 0.0, 0.0);
				cilindro(0.60, 1.0, 50, idTextura_piel);
			glPopMatrix();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0f, -0.5f, 0.0f);
			glTranslatef(-2.5f, 0.70f, -5.0f);
			glRotatef(giraRotaP1, 1.0, 0.0, 0.0); //el asiento jira sobre su propio eje
			esfera(1.0, 50, 50, idTextura_P3);
		glPopMatrix();

		//tentaculo izquierdo

		glPushMatrix();
			glTranslatef(-1.75f, 0.0f, 0.0f);
			esfera(0.5, 50, 50, idTextura_bola);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-1.5f, -0.5f, 0.0f);
			glRotatef(120.0f, 0.0, 0.0, 1.0);
			cilindro(0.75, 1.0, 50, idTextura_piel);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0f, -0.5f, 0.0f);
			glTranslatef(-2.5f, -0.5f, 0.0f);
			esfera(0.75, 50, 50, idTextura_bola);
			glRotatef(90.0f, 0.0, 0.0, 1.0);
			cilindro(0.70, 2.0, 50, idTextura_piel);
		glPopMatrix();
							
		glPushMatrix();
		glTranslatef(0.0f, -0.5f, 0.0f);
			glTranslatef(-4.5f, -0.5f, 0.0f);
			esfera(0.75, 50, 50, idTextura_bola);
			glPushMatrix();
				glTranslatef(0.0f, 0.1f, 0.0f);
				glRotatef(45.0f, 0.0, 0.0, 1.0);
				cilindro(0.60, 1.0, 50, idTextura_piel);
			glPopMatrix();
		glPopMatrix();
							
		glPushMatrix();
		glTranslatef(0.0f, -0.5f, 0.0f);
			glTranslatef(-5.3f, 0.85f, 0.0f);
			glRotatef(giraRotaP1, 1.0, 0.0, 0.0); //el asiento jira sobre su propio eje
			esfera(1.0, 50, 50, idTextura_P4);
		glPopMatrix();

		//tentaculo enfrente izquierdo

		glPushMatrix();
			glTranslatef(-0.95f, 0.0f, 1.5f);
			esfera(0.5, 50, 50, idTextura_bola);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-0.7f, -0.5f, 1.5f);
			glRotatef(330.0f, 0.0, 1.0, 0.0);
			glRotatef(120.0f, 1.0, 0.0, 0.0);
			cilindro(0.75, 1.0, 50, idTextura_piel);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0f, -0.5f, 0.0f);
			glTranslatef(1.2f, -0.5f, 2.2f);
			esfera(0.80, 50, 50, idTextura_bola);
			glPushMatrix();
				glTranslatef(0.0f, -0.1f, 0.0f);
				glRotatef(30.0f, 0.0, 1.0, 0.0);
				glRotatef(90.0f, 1.0, 0.0, 0.0);
				cilindro(0.70, 2.0, 50, idTextura_piel);
			glPopMatrix();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0f, -0.5f, 0.0f);
			glTranslatef(-2.35f, -0.5f, 4.25f);
			esfera(0.75, 50, 50, idTextura_bola);
			glPushMatrix();
				glTranslatef(0.0f, -0.1f, 0.0f);
				glRotatef(330.0f, 0.0, 1.0, 0.0);
				glRotatef(45.0f, 1.0, 0.0, 0.0);
				cilindro(0.60, 1.0, 50, idTextura_piel);
			glPopMatrix();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0f, -0.5f, 0.0f);
			glTranslatef(-2.50f, 0.5f, 4.7f);
			glRotatef(giraRotaP1, 1.0, 0.0, 0.0); //el asiento jira sobre su propio eje
			esfera(1.0, 50, 50, idTextura_P5);
		glPopMatrix();

		//tentaculo enfrente derecho

		glPushMatrix();
			glTranslatef(0.95f, 0.0f, 1.5f);
			esfera(0.5, 50, 50, idTextura_bola);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.7f, -0.5f, 1.5f);
			glRotatef(30.0f, 0.0, 1.0, 0.0);
			glRotatef(120.0f, 1.0, 0.0, 0.0);
			cilindro(0.75, 1.0, 50, idTextura_piel);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0f, -0.5f, 0.0f);
			glTranslatef(-1.2f, -0.5f, 2.2f);
			esfera(0.80, 50, 50, idTextura_bola);
			glPushMatrix();
				glTranslatef(0.0f, -0.1f, 0.0f);
				glRotatef(330.0f, 0.0, 1.0, 0.0);
				glRotatef(90.0f, 1.0, 0.0, 0.0);
				cilindro(0.70, 2.0, 50, idTextura_piel);
			glPopMatrix();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0f, -0.5f, 0.0f);
			glTranslatef(2.35f, -0.5f, 4.25f);
			esfera(0.75, 50, 50, idTextura_bola);
			glPushMatrix();
				glTranslatef(0.0f, -0.1f, 0.0f);
				glRotatef(30.0f, 0.0, 1.0, 0.0);
				glRotatef(45.0f, 1.0, 0.0, 0.0);
				cilindro(0.60, 1.0, 50, idTextura_piel);
			glPopMatrix();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0f, -0.5f, 0.0f);
			glTranslatef(2.50f, 0.5f, 4.7f);
			glRotatef(giraRotaP1, 1.0, 0.0, 0.0); //el asiento jira sobre su propio eje
			esfera(1.0, 50, 50, idTextura_P6);
		glPopMatrix();

	glPopMatrix();

	//dibujar bola superior
	glPushMatrix();
	glTranslatef(0.0f, 1.5f, 0.0f);
	esfera(2.0, 50, 50, idTextura_piel);
	glPopMatrix();

	//dibujar manchas amarillas
	glPushMatrix();
	glTranslatef(0.0f, 3.25f, 0.0f);
	esfera(0.5, 50, 50, idTextura_bola);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 3.0f, 1.0f);
	esfera(0.5, 50, 50, idTextura_bola);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 3.0f, -1.0f);
	esfera(0.5, 50, 50, idTextura_bola);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 2.25f, -1.5f);
	esfera(0.5, 50, 50, idTextura_bola);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 1.5f, -1.7f);
	esfera(0.5, 50, 50, idTextura_bola);
	glPopMatrix();


	//dibujar cara
	//nariz
	glPushMatrix();
	glTranslatef(0.0f, 2.0f, 1.5f); 
	glRotatef(90.0f, 1.0, 0.0, 0.0);
	cono(1.5, 0.75, 10, idTextura_piel);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0.0f, 2.0f, 2.0f); 
	glRotatef(90.0f, 1.0, 0.0, 0.0);
	cilindro(0.5, 1.0, 50, idTextura_piel);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 2.0f, 2.75f);
	esfera(0.3, 50, 50, idTextura_negro);
	glPopMatrix();

	//ojo izquierdo
	glPushMatrix();
	glTranslatef(-0.5f, 2.25f, 1.0f);
	esfera(0.75, 50, 50, idTextura_blanco);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.5f, 2.5f, 1.5f);
	esfera(0.25, 50, 50, idTextura_negro);
	glPopMatrix();

	//ojo derecho
	glPushMatrix();
	glTranslatef(0.5f, 2.25f, 1.0f);
	esfera(0.75, 50, 50, idTextura_blanco);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.5f, 2.5f, 1.5f);
	esfera(0.25, 50, 50, idTextura_negro);
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