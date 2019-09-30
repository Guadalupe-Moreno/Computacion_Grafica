/*
Practica_9:
	Emplenado texturisado y figuras 3D, modelar un esenario en la playa
*/
#include <GL/glut.h>
#include "figuras.h"
#include "Textura_arena.c"
#include "Textura_mar.c"
#include "Textura_piso.c"
#include "Textura_PA.c"
#include "Textura_tela.c"
#include "Textura_TA.c"
#include "Textura_coco.c"
#include "Textura_pelota.c"

//variables para acumular traslación con teclas w,s (en z) a,d (en x) e,c (en y)
float transZ = -5.0f;
float transX = 0.0f;
float transY = -5.0f;

//variables para acumular rotación con flechas de dirección
float angleX = 0.0f;
float angleY = 0.0f;

//identificadores de textura
GLuint idTextura_arena;
GLuint idTextura_mar;
GLuint idTextura_piso;
GLuint idTextura_PA;
GLuint idTextura_tela;
GLuint idTextura_TA;
GLuint idTextura_coco;
GLuint idTextura_pelota;

//función para inicializar estados de gl
void inicializar(void)
{
	glClearColor(0.831, 0.949, 0.988, 1);
	glClearDepth(1.0f);									// Configuramos Depth Buffer
	glEnable(GL_DEPTH_TEST);							// Habilitamos Depth Testing
	glDepthFunc(GL_LEQUAL);								// Tipo de Depth Testing a realizar
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	//cargaa textura arena
	glGenTextures(1, &idTextura_arena);
	glBindTexture(GL_TEXTURE_2D, idTextura_arena);

	gluBuild2DMipmaps(GL_TEXTURE_2D,
		Textura_arena.bytes_per_pixel, Textura_arena.width,
		Textura_arena.height, GL_RGB, GL_UNSIGNED_BYTE,
		Textura_arena.pixel_data);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// En caso de no querer repetir las texturas, comentar estas
	// dos líneas
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	glEnable(GL_TEXTURE_2D);

	//cargaa textura mar
	glGenTextures(1, &idTextura_mar);
	glBindTexture(GL_TEXTURE_2D, idTextura_mar);

	gluBuild2DMipmaps(GL_TEXTURE_2D,
		Textura_mar.bytes_per_pixel, Textura_mar.width,
		Textura_mar.height, GL_RGB, GL_UNSIGNED_BYTE,
		Textura_mar.pixel_data);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// En caso de no querer repetir las texturas, comentar estas
	// dos líneas
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	glEnable(GL_TEXTURE_2D);

	//cargaa textura piso de madera
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

	//cargaa textura cemento
	glGenTextures(1, &idTextura_PA);
	glBindTexture(GL_TEXTURE_2D, idTextura_PA);

	gluBuild2DMipmaps(GL_TEXTURE_2D,
		Textura_PA.bytes_per_pixel, Textura_PA.width,
		Textura_PA.height, GL_RGB, GL_UNSIGNED_BYTE,
		Textura_PA.pixel_data);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// En caso de no querer repetir las texturas, comentar estas
	// dos líneas
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	glEnable(GL_TEXTURE_2D);

	//cargaa textura tela roja
	glGenTextures(1, &idTextura_tela);
	glBindTexture(GL_TEXTURE_2D, idTextura_tela);

	gluBuild2DMipmaps(GL_TEXTURE_2D,
		Textura_tela.bytes_per_pixel, Textura_tela.width,
		Textura_tela.height, GL_RGB, GL_UNSIGNED_BYTE,
		Textura_tela.pixel_data);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// En caso de no querer repetir las texturas, comentar estas
	// dos líneas
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	glEnable(GL_TEXTURE_2D);

	//cargaa textura tela azul
	glGenTextures(1, &idTextura_TA);
	glBindTexture(GL_TEXTURE_2D, idTextura_TA);

	gluBuild2DMipmaps(GL_TEXTURE_2D,
		Textura_TA.bytes_per_pixel, Textura_TA.width,
		Textura_TA.height, GL_RGB, GL_UNSIGNED_BYTE,
		Textura_TA.pixel_data);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// En caso de no querer repetir las texturas, comentar estas
	// dos líneas
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	glEnable(GL_TEXTURE_2D);

	//cargaa textura coco
	glGenTextures(1, &idTextura_coco);
	glBindTexture(GL_TEXTURE_2D, idTextura_coco);

	gluBuild2DMipmaps(GL_TEXTURE_2D,
		Textura_coco.bytes_per_pixel, Textura_coco.width,
		Textura_coco.height, GL_RGB, GL_UNSIGNED_BYTE,
		Textura_coco.pixel_data);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// En caso de no querer repetir las texturas, comentar estas
	// dos líneas
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	glEnable(GL_TEXTURE_2D);

	//cargaa textura pelota
	glGenTextures(1, &idTextura_pelota);
	glBindTexture(GL_TEXTURE_2D, idTextura_pelota);

	gluBuild2DMipmaps(GL_TEXTURE_2D,
		Textura_pelota.bytes_per_pixel, Textura_pelota.width,
		Textura_pelota.height, GL_RGB, GL_UNSIGNED_BYTE,
		Textura_pelota.pixel_data);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// En caso de no querer repetir las texturas, comentar estas
	// dos líneas
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	glEnable(GL_TEXTURE_2D);

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

										 //dibujar
	//esfera(2.0, 50, 50, idTextura_mar);

	glPushMatrix();
		glScalef(10,1,1);
		prisma2(idTextura_mar, idTextura_mar);
	
		glTranslatef(0.0f, 0.0f, -1.5f);
		glScalef(1, 1, 2);
		prisma2(idTextura_arena, idTextura_arena);

		glTranslatef(0.0f, 0.0f, -2.0f);
		glScalef(1, 1, 3);
		prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();
	
	//Mesa
	//pata izquierda atras
	glPushMatrix();
		glTranslatef(-1.0f, 0.5f, -1.5f);
		glScalef(0.25, 0.5, 0.25);
		prisma2(idTextura_PA, idTextura_PA);
	glPopMatrix();
	//pata derecha atras
	glPushMatrix();
		glTranslatef(1.0f, 0.5f, -1.5f);
		glScalef(0.25, 0.5, 0.25);
		prisma2(idTextura_PA, idTextura_PA);
	glPopMatrix();
	//pata izquierda enfrente
	glPushMatrix();
		glTranslatef(-1.0f, 0.5f, -1.0f);
		glScalef(0.25, 0.5, 0.25);
		prisma2(idTextura_PA, idTextura_PA);
	glPopMatrix();
	//pata derecha enfrente
	glPushMatrix();
		glTranslatef(1.0f, 0.5f, -1.0f);
		glScalef(0.25, 0.5, 0.25);
		prisma2(idTextura_PA, idTextura_PA);
	glPopMatrix();
	//tabla
	glPushMatrix();
		glTranslatef(0.0f, 0.75f, -1.25f);
		glScalef(2, 0.25, 0.75);
		prisma2(idTextura_PA, idTextura_PA);
	glPopMatrix();

	//sombriya
	//palo
	glPushMatrix();
		glTranslatef(-1.5f, 0.5f, -1.25f);
		glScalef(0.20, 2, 0.20);
		prisma2(idTextura_PA, idTextura_PA);
	glPopMatrix();
	//tela
	glPushMatrix();
		glTranslatef(-1.5f, 1.5f, -1.25f);
		cono(0.5, 1, 10, idTextura_tela);
	glPopMatrix();
	//tualla
	glPushMatrix();
		glTranslatef(-2.0f, 0.5f, -1.25f);
		glScalef(0.5, 0.1, 1);
		prisma2(idTextura_TA, idTextura_TA);
	glPopMatrix();

	//coco
	glPushMatrix();
		glTranslatef(0.0f, 1.0f, -1.25f);
		esfera(0.1, 50, 50, idTextura_coco);
	glPopMatrix();

	//pelota
	glPushMatrix();
		glTranslatef(2.0f, 0.75f, -1.25f);
		esfera(0.3, 50, 50, idTextura_pelota);
	glPopMatrix();

	//Hotel
	//en medio
	glPushMatrix();
		glTranslatef(0.0f, 0.75f, -6.0f);
		cilindro(2.5, 5.5, 50, idTextura_pelota);
	glPopMatrix();
	//cistado izquierdo
	glPushMatrix();
		glTranslatef(-2.5f, 0.75f, -6.0f);
		cilindro(1.5, 5.0, 50, idTextura_pelota);
	glPopMatrix();
	//costado derecho
	glPushMatrix();
		glTranslatef(2.5f, 0.75f, -6.0f);
		cilindro(1.5, 5.0, 50, idTextura_pelota);
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
	glFrustum (-5, 5, -5, 5, 4, 20.0);
	//glFrustum(-0.1, 0.1, -0.1, 0.1, 0.1, 50.0);

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

	//Llamada a función que cede el control a GLUT y procesa eventos de ventana, ratón
	glutMainLoop();

	//termina la ejecución devolviendo cero
	return 0;
}
