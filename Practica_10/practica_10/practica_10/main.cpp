/*
Practica_10:
	*/


#include <stdlib.h>
#include <string.h>
// al incluir a glut. h incluye a gl.h a  glu.h
#include <GL/glut.h>

#include "texture.h"
#include "figuras.h"
#include "Camera.h"
#include "cmodel/CModel.h"

//variables para acumular traslaciÃ³n con teclas w,s (en z) a,d (en x) e,c (en y)
float transZ = -10.0f;
float transX = 0.0f;
float transY = 0.0f;

//variables para acumular rotaciÃ³n con flechas de direcciÃ³n
float angleX = 0.0f;
float angleY = 0.0f;

//Solo para Visual Studio 2015 o mayor
#if (_MSC_VER >= 1900)
#   pragma comment( lib, "legacy_stdio_definitions.lib" )
#endif

CCamera objCamera;
GLfloat g_lookupdown = 0.0f;    // Look Position In The Z-Axis (NEW) 

long int font = (long int)GLUT_BITMAP_HELVETICA_18;

GLfloat Diffuse[] = { 0.5f, 27.0f, -5.0f, 0.0f };			// Light Position
GLfloat Position2[] = { 0.0f, 0.0f, -5.0f, 1.0f };			// Light Position

GLfloat m_dif1[] = { 0.0, 0.5f, 0.5f, 1.0f };				// Diffuse Light Values
GLfloat Specular[] = { 1.0, 1.0, 1.0, 1.0 };				// Specular Light Values
GLfloat Position[] = { 0.0f, 0.2f, 1.0f, 1.0f };				// Diffuse Light Values
GLfloat m_spec1[] = { 0.0, 0.0, 0.0, 1.0 };				// Specular Light Values
GLfloat m_amb1[] = { 0.0, 0.0, 0.0, 1.0 };				// Ambiental Light Values
GLfloat m_s1[] = { 18 };

CTexture text1;
CTexture text2;
CTexture text3;	//Flecha
CTexture text4;	//Pavimento
CTexture text5;	//Pasto01
CTexture text6;	//Casa01

CFiguras fig1;
CFiguras fig2;
CFiguras fig3;
CFiguras fig4;	//Pasto01
CFiguras fig5;	//Casa01
CFiguras fig6;

CFiguras fig7; //Para el monito

			   //Figuras de 3D Studio
CModel kit;
CModel llanta;

//Animación del coche
float movKit = 0.0;
bool g_fanimacion = false;

float giro = 0.0f;

bool avanza = true;

//función para inicializar estados de gl
void inicializar(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Negro de fondo	

	glEnable(GL_TEXTURE_2D);

	glShadeModel(GL_SMOOTH);
	glLightfv(GL_LIGHT1, GL_POSITION, Position);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Diffuse);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_COLOR_MATERIAL);

	glClearDepth(1.0f);									// Configuramos Depth Buffer
	glEnable(GL_DEPTH_TEST);							// Habilitamos Depth Testing
	glDepthFunc(GL_LEQUAL);								// Tipo de Depth Testing a realizar
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);

	/* setup blending */
	glEnable(GL_BLEND);			// Turn Blending On

	text1.LoadBMP("01.bmp");
	text1.BuildGLTexture();
	text1.ReleaseImage();

	text2.LoadBMP("logopumas.bmp");
	text2.BuildGLTexture();
	text2.ReleaseImage();

	text3.LoadTGA("city/arrow.tga");
	text3.BuildGLTexture();
	text3.ReleaseImage();

	text4.LoadTGA("city/pavimento.tga");
	text4.BuildGLTexture();
	text4.ReleaseImage();

	text5.LoadTGA("city/pasto01.tga");
	text5.BuildGLTexture();
	text5.ReleaseImage();

	text6.LoadTGA("city/casa01.tga");
	text6.BuildGLTexture();
	text6.ReleaseImage();

	//Carga de Figuras
	kit._3dsLoad("modelos/kitt.3ds");
	//kit.VertexNormals();

	llanta._3dsLoad("modelos/k_rueda.3ds");

	objCamera.Position_Camera(10, 2.5f, 13, 10, 2.5f, 10, 0, 1.0, 0);
}

void dibujar(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Limpiamos pantalla y Depth Buffer

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();

	glRotatef(g_lookupdown, 1.0f, 0, 0);

	gluLookAt(objCamera.mPos.x, objCamera.mPos.y, objCamera.mPos.z,
		objCamera.mView.x, objCamera.mView.y, objCamera.mView.z,
		objCamera.mUp.x, objCamera.mUp.y, objCamera.mUp.z);


	glPushMatrix();
	glPushMatrix(); //Creamos cielo
	glDisable(GL_LIGHTING);
	glTranslatef(0, 60, 0);
	fig1.skybox(130.0, 130.0, 130.0, text1.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	//Para que el coche conserve sus colores
	glDisable(GL_COLOR_MATERIAL);
	glRotatef(90, 0, 1, 0);
	glScalef(0.3, 0.3, 0.3);

	glTranslatef(0, 4, movKit);
	//Pongo aquí la carroceria del carro
	kit.GLrender(NULL, _SHADED, 1.0);  //_WIRED O _POINTS

	glPushMatrix();
	glTranslatef(-6.0, -1.0, 7.5);
	glRotatef(giro, 1.0, 0.0, 0.0);
	//glRotatef(rota_llanta, 0.0, 0.0, 1.0);
	llanta.GLrender(NULL, _SHADED, 1.0); //llanta delantera derecha 
	glPopMatrix();

	glPushMatrix();
	glTranslatef(6.0, -1.0, 7.5);
	glRotatef(180, 0.0, 1.0, 0.0);
	glRotatef(-giro, 1.0, 0.0, 0.0);
	//glRotatef(rota_llanta, 0.0, 0.0, 1.0);
	llanta.GLrender(NULL, _SHADED, 1.0); //llanta delantera izq
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-6.0, -1.0, -9.5);
	glRotatef(giro, 1.0, 0.0, 0.0);
	//glRotatef(rota_llanta, 0.0, 0.0, 1.0);
	llanta.GLrender(NULL, _SHADED, 1.0); //llanta atras derecha 
	glPopMatrix();

	glPushMatrix();
	glTranslatef(6.0, -1.0, -9.5);
	glRotatef(180, 0.0, 1.0, 0.0);
	glRotatef(-giro, 1.0, 0.0, 0.0);
	//glRotatef(rota_llanta, 0.0, 0.0, 1.0);
	llanta.GLrender(NULL, _SHADED, 1.0); //llanta atras izq 
	glPopMatrix();

	glPopMatrix();

	//Para que el comando glColor funcione con iluminacion
	glEnable(GL_COLOR_MATERIAL);

	glPushMatrix(); //Flecha
	glScalef(7, 0.1, 7);
	glDisable(GL_LIGHTING);
	fig3.prisma_anun(text3.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //Camino1
	glTranslatef(23.5, 0.0, 0.0);
	glScalef(40, 0.1, 7);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text4.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //Camino2
	glTranslatef(-23.5, 0.0, 0.0);
	glScalef(40, 0.1, 7);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text4.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //Pasto
	glTranslatef(0.0, 0.0, -4.0);
	glScalef(87, 0.1, 1);
	glDisable(GL_LIGHTING);
	fig4.prisma2(text5.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //Pasto
	glTranslatef(0.0, 0.0, 4.0);
	glScalef(87, 0.1, 1);
	glDisable(GL_LIGHTING);
	fig4.prisma2(text5.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //Casa01
	glTranslatef(0.0, 3.0, 7.0);
	glRotatef(90, 1, 0, 0);
	glRotatef(180, 0, 0, 1);
	glScalef(6, 5.0, 6);
	glDisable(GL_LIGHTING);
	fig5.prisma2(text6.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //Casa01
	glTranslatef(0.0, 3.0, -7.0);
	glRotatef(90, 1, 0, 0);
	glScalef(6, 5.0, 6);
	glDisable(GL_LIGHTING);
	fig5.prisma2(text6.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glColor3f(1.0, 1.0, 1.0);

	glPopMatrix();
	glPopMatrix();

	glFlush();
}

void animacion() {

	fig3.text_izq -= 0.001;
	fig3.text_der -= 0.001;
	if (fig3.text_izq < -1)
		fig3.text_izq = 0;
	if (fig3.text_der < 0)
		fig3.text_der = 1;

	if (g_fanimacion) {
		if (avanza) {
			giro += 1;
			movKit += 0.1;
			if (movKit > 50)
				avanza = false;
		}
		else {
			giro -= 1;
			movKit -= 0.1;
			if (movKit < 0)
				avanza = true;
		}
	}


	glutPostRedisplay();
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
	glFrustum(-0.1, 0.1, -0.1, 0.1, 0.1, 200.0);

	glutPostRedisplay();
}

void teclado(unsigned char key, int x, int y)
{
	switch (key) {
	case 'w':   case 'W':
		objCamera.Move_Camera(CAMERASPEED + 0.2);
		break;
	case 's': 	case 'S':
		objCamera.Move_Camera(-(CAMERASPEED + 0.2));
		break;
	case 'a':	case 'A':
		objCamera.Strafe_Camera(-(CAMERASPEED + 0.4));
		break;
	case 'd':	case 'D':
		objCamera.Strafe_Camera(CAMERASPEED + 0.4);
		break;
		//teclas para animación
	case ' ': //poner algo en movimiento
		g_fanimacion ^= true; //Activamos/desactivamos la nimacion
		movKit = 0.0f;
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
	case GLUT_KEY_UP:     // Presionamos tecla ARRIBA...
		g_lookupdown -= 1.0f;
		break;
	case GLUT_KEY_DOWN:               // Presionamos tecla ABAJO...
		g_lookupdown += 1.0f;
		break;
	case GLUT_KEY_LEFT:
		objCamera.Rotate_View(-CAMERASPEED);
		break;
	case GLUT_KEY_RIGHT:
		objCamera.Rotate_View(CAMERASPEED);
		break;
	case GLUT_KEY_PAGE_UP:
		objCamera.UpDown_Camera(CAMERASPEED);
		break;
	case GLUT_KEY_PAGE_DOWN:
		objCamera.UpDown_Camera(-CAMERASPEED);
		break;
	default:
		break;
	}
	glutPostRedisplay();
}


int main(int argc, char *argv[]){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(400, 100);
	glutCreateWindow(argv[1]);
	inicializar();
	glutDisplayFunc(dibujar);
	glutReshapeFunc(remodelar);
	glutKeyboardFunc(teclado);
	glutSpecialFunc(teclasFlechas);
	glutIdleFunc(animacion);
	glutMainLoop();

	return 0;
}