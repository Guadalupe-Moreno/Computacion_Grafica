/*
Practica_4:
	Dibujo con transformaciones basicas
*/
#include <GL/glut.h>

float transZ = -10.0f;
float transX = 0.0f;
float transY = 0.0f;

float angleX = 0.0f;
float angleY = 0.0f;

float cabello[3] = { 0.007,0.011,0.031 };
float traje[3] = { 0.423, 0.462, 0.498 };
float botas[3] = { 0.0,0.0,0.0 };
float capa[3] = { 0.113, 0.278, 0.427 };
float cinturon[3] = { 0.949,0.788,0.109 };
float piel[3] = { 0.925,0.756,0.396 };


void inicializar(void)
{
	glClearColor(0.219, 0.941, 0.890, 1);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

//función para dibujar un cubo a partir de polígonos
void prisma(void)
{
	GLfloat vertice[8][3] = {
	 { 0.5 ,-0.5, 0.5 },    //Coordenadas Vértice 0 V0
	{ -0.5 ,-0.5, 0.5 },    //Coordenadas Vértice 1 V1
	{ -0.5 ,-0.5, -0.5 },    //Coordenadas Vértice 2 V2
	{ 0.5 ,-0.5, -0.5 },    //Coordenadas Vértice 3 V3
	{ 0.5 ,0.5, 0.5 },    //Coordenadas Vértice 4 V4
	{ 0.5 ,0.5, -0.5 },    //Coordenadas Vértice 5 V5
	{ -0.5 ,0.5, -0.5 },    //Coordenadas Vértice 6 V6
	{ -0.5 ,0.5, 0.5 },    //Coordenadas Vértice 7 V7
	};

	glBegin(GL_POLYGON); //Enfrente
	glColor3fv(traje);
	glVertex3fv(vertice[0]);
	glVertex3fv(vertice[4]);
	glVertex3fv(vertice[7]);
	glVertex3fv(vertice[1]);
	glEnd();

	glBegin(GL_POLYGON); //Derecha
	glColor3fv(capa);
	glVertex3fv(vertice[0]);
	glVertex3fv(vertice[3]);
	glVertex3fv(vertice[5]);
	glVertex3fv(vertice[4]);
	glEnd();

	glBegin(GL_POLYGON); //Atrás
	glColor3fv(cinturon);
	glVertex3fv(vertice[6]);
	glVertex3fv(vertice[5]);
	glVertex3fv(vertice[3]);
	glVertex3fv(vertice[2]);
	glEnd();

	glBegin(GL_POLYGON);  //Izquierda
	glColor3fv(botas);
	glVertex3fv(vertice[1]);
	glVertex3fv(vertice[7]);
	glVertex3fv(vertice[6]);
	glVertex3fv(vertice[2]);
	glEnd();

	glBegin(GL_POLYGON);  //Abajo
	glColor3fv(piel);
	glVertex3fv(vertice[0]);
	glVertex3fv(vertice[1]);
	glVertex3fv(vertice[2]);
	glVertex3fv(vertice[3]);
	glEnd();

	glBegin(GL_POLYGON);  //Arriba
	glColor3fv(cabello);
	glVertex3fv(vertice[4]);
	glVertex3fv(vertice[5]);
	glVertex3fv(vertice[6]);
	glVertex3fv(vertice[7]);
	glEnd();
}


void dibujar(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);


	glLoadIdentity();

	glTranslatef(transX, transY, transZ);
	glRotatef(angleY, 0.0, 1.0, 0.0);
	glRotatef(angleX, 1.0, 0.0, 0.0);

	//Calzon
	glScalef(6.0, 2.0, 1.0);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	prisma();

	glLoadIdentity();
	glTranslatef(transX, transY, transZ);
	glRotatef(angleY, 0.0, 1.0, 0.0);
	glRotatef(angleX, 1.0, 0.0, 0.0);

	//Pierna Derecha
	glTranslatef(-1.75f, -4.0f, 0.0f);
	glScalef(2.5, 6.0, 1.0);
	prisma();

	glLoadIdentity();
	glTranslatef(transX, transY, transZ);
	glRotatef(angleY, 0.0, 1.0, 0.0);
	glRotatef(angleX, 1.0, 0.0, 0.0);

	//Pierna Izquierda
	glTranslatef(1.75f, -4.0f, 0.0f);
	glScalef(2.5, 6.0, 1.0);
	prisma();

	glLoadIdentity();
	glTranslatef(transX, transY, transZ);
	glRotatef(angleY, 0.0, 1.0, 0.0);
	glRotatef(angleX, 1.0, 0.0, 0.0);

	//Bota derecha
	glTranslatef(1.75f, -9.5f, 0.0f);
	glScalef(2.5, 5.0, 1.0);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	prisma();

	glLoadIdentity();

	glTranslatef(transX, transY, transZ);
	glRotatef(angleY, 0.0, 1.0, 0.0);
	glRotatef(angleX, 1.0, 0.0, 0.0);

	//Bota Izquierda
	glTranslatef(-1.75f, -9.5f, 0.0f);
	glScalef(2.5, 5.0, 1.0);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	prisma();

	glLoadIdentity();
	glTranslatef(transX, transY, transZ);
	glRotatef(angleY, 0.0, 1.0, 0.0);
	glRotatef(angleX, 1.0, 0.0, 0.0);

	//Cinturon
	glTranslatef(0.0f, 1.5f, 0.0f);
	glScalef(5.5, 1.0, 1.0);
	glRotatef(180.0, 0.0, 1.0, 0.0);
	prisma();

	glLoadIdentity();
	glTranslatef(transX, transY, transZ);
	glRotatef(angleY, 0.0, 1.0, 0.0);
	glRotatef(angleX, 1.0, 0.0, 0.0);

	//Torso
	glTranslatef(0.0f, 5.0f, 0.0f);
	glScalef(5.5, 7.0, 1.0);
	prisma();

	glLoadIdentity();
	glTranslatef(transX, transY, transZ);
	glRotatef(angleY, 0.0, 1.0, 0.0);
	glRotatef(angleX, 1.0, 0.0, 0.0);

	//Cuello
	glTranslatef(0.0f, 9.0f, 0.0f);
	glScalef(2.0, 1.5, 1.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	prisma();

	glLoadIdentity();
	glTranslatef(transX, transY, transZ);
	glRotatef(angleY, 0.0, 1.0, 0.0);
	glRotatef(angleX, 1.0, 0.0, 0.0);

	//Cara
	glTranslatef(0.0f, 11.7f, 0.0f);
	glScalef(3.5, 4.0, 1.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	prisma();

	glLoadIdentity();
	glTranslatef(transX, transY, transZ);
	glRotatef(angleY, 0.0, 1.0, 0.0);
	glRotatef(angleX, 1.0, 0.0, 0.0);

	//Hombros
	glTranslatef(0.0f, 8.0f, 0.0f);
	glScalef(9.2, 1.75, 1.0);
	prisma();

	glLoadIdentity();
	glTranslatef(transX, transY, transZ);
	glRotatef(angleY, 0.0, 1.0, 0.0);
	glRotatef(angleX, 1.0, 0.0, 0.0);

	//Brazo izquierdo
	glTranslatef(3.95f, 4.89f, 0.0f);
	glScalef(1.6, 8.0, 1.0);
	prisma();

	glLoadIdentity();
	glTranslatef(transX, transY, transZ);
	glRotatef(angleY, 0.0, 1.0, 0.0);
	glRotatef(angleX, 1.0, 0.0, 0.0);

	//Brazo derecho
	glTranslatef(-3.95f, 4.89f, 0.0f);
	glScalef(1.6, 8.0, 1.0);
	prisma();

	glLoadIdentity();
	glTranslatef(transX, transY, transZ);
	glRotatef(angleY, 0.0, 1.0, 0.0);
	glRotatef(angleX, 1.0, 0.0, 0.0);

	//Capa
	glTranslatef(0.0f, 1.93f, -0.1f);
	glScalef(11.0, 14.0, 1.0);
	glRotatef(-90.0, 0.0, 1.0, 0.0);
	prisma();

	glLoadIdentity();
	glTranslatef(transX, transY, transZ);
	glRotatef(angleY, 0.0, 1.0, 0.0);
	glRotatef(angleX, 1.0, 0.0, 0.0);

	//Mano Derecha
	glTranslatef(-3.95f, -0.1f, 0.0f);
	glScalef(1.6, 2.0, 1.0);
	glRotatef(270.0, 1.0, 0.0, 0.0);
	prisma();

	glLoadIdentity();
	glTranslatef(transX, transY, transZ);
	glRotatef(angleY, 0.0, 1.0, 0.0);
	glRotatef(angleX, 1.0, 0.0, 0.0);

	//Mano Izquierda
	glTranslatef(3.95f, -0.1f, 0.0f);
	glScalef(1.6, 2.0, 1.0);
	glRotatef(270.0, 1.0, 0.0, 0.0);
	prisma();

	glLoadIdentity();
	glTranslatef(transX, transY, transZ);
	glRotatef(angleY, 0.0, 1.0, 0.0);
	glRotatef(angleX, 1.0, 0.0, 0.0);

	//Logo
	glTranslatef(0.0f, 6.5f, 0.0f);
	glScalef(3.5, 1.5, 1.0);
	glRotatef(180.0, 0.0, 1.0, 0.0);
	prisma();

	glLoadIdentity();
	glTranslatef(transX, transY, transZ);
	glRotatef(angleY, 0.0, 1.0, 0.0);
	glRotatef(angleX, 1.0, 0.0, 0.0);

	glTranslatef(0.0f, 6.5f, 0.0f);
	glScalef(2.5, 0.7, 1.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	prisma();

	glLoadIdentity();
	glTranslatef(transX, transY, transZ);
	glRotatef(angleY, 0.0, 1.0, 0.0);
	glRotatef(angleX, 1.0, 0.0, 0.0);

	//Boca
	glTranslatef(0.0f, 10.7f, 0.0f);
	glScalef(2.6, 1.3, 1.0);
	glRotatef(270.0, 1.0, 0.0, 0.0);
	prisma();

	glLoadIdentity();
	glTranslatef(transX, transY, transZ);
	glRotatef(angleY, 0.0, 1.0, 0.0);
	glRotatef(angleX, 1.0, 0.0, 0.0);

	//Ojo Izquierdo
	glTranslatef(0.7f, 12.2f, 0.0f);
	glScalef(1.0, 0.3, 1.0);
	glRotatef(270.0, 1.0, 0.0, 0.0);
	prisma();

	glLoadIdentity();
	glTranslatef(transX, transY, transZ);
	glRotatef(angleY, 0.0, 1.0, 0.0);
	glRotatef(angleX, 1.0, 0.0, 0.0);

	//Ojo Dedrecho
	glTranslatef(-0.7f, 12.2f, 0.0f);
	glScalef(1.0, 0.3, 1.0);
	glRotatef(270.0, 1.0, 0.0, 0.0);
	prisma();

	glLoadIdentity();
	glTranslatef(transX, transY, transZ);
	glRotatef(angleY, 0.0, 1.0, 0.0);
	glRotatef(angleX, 1.0, 0.0, 0.0);

	//Cuerno Izquierdo
	glTranslatef(-1.5f, 14.4f, 0.0f);
	glScalef(0.5, 1.5, 1.0);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	prisma();

	glLoadIdentity();
	glTranslatef(transX, transY, transZ);
	glRotatef(angleY, 0.0, 1.0, 0.0);
	glRotatef(angleX, 1.0, 0.0, 0.0);

	//Cuerno Derecho
	glTranslatef(1.5f, 14.4f, 0.0f);
	glScalef(0.5, 1.5, 1.0);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	prisma();

	glFlush();
}

void remodelar(int width, int height)
{
	if (height == 0)
	{
		height = 1;
	}
	glViewport(0, 0, width, height);    //definir ventana (ancho, altura)
	glMatrixMode(GL_PROJECTION);        // guarda vista de como se ve la camara
	glLoadIdentity();

	glFrustum(-10, 10, -10, 10, 4.0, 20.0);
	glutPostRedisplay();
}

void teclado(unsigned char key, int x, int y)
{
	switch (key)
	{
	case'w':case'W':  //acerca al objeto con traslación en Z pos
		transZ += 0.2f;
		break;

	case's':case'S':  //aleja al objeto con traslación en Z neg
		transZ -= 0.2f;
		break;

	case'a':case'A':  //traslada al objeto hacia la derecha en X pos
		transX += 0.2f;
		break;

	case'd':case'D':  //traslada al objeto hacia la izquierda en X neg
		transX -= 0.2f;
		break;

	case'q':case'Q':  //traslada al objeto hacia arriba en Y pos
		transY += 0.2f;
		break;

	case'e':case'E':  //traslada al objeto hacia abajo en Y neg
		transY -= 0.2f;
		break;

	case 27:    //Si presiona la tecla ESC(ASCII 27) sale
		exit(0);
		break;

	default:    //Si es cualquier otra tecla no hace nada
		break;
	}
	glutPostRedisplay();
}

void teclasFlechas(int tecla, int x, int y)
{
	switch (tecla) {
	case GLUT_KEY_UP:
		angleX += 2.0f;
		break;
	case GLUT_KEY_DOWN:
		angleX -= 2.0f;
		break;
	case GLUT_KEY_LEFT:
		angleY += 2.0f;
		break;
	case GLUT_KEY_RIGHT:
		angleY -= 2.0f;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}


int main(int argc, char* argv[]){
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE | GLUT_DEPTH);  
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(500, 250);

	glutCreateWindow(argv[1]);
	inicializar();
	glutDisplayFunc(dibujar);
	glutReshapeFunc(remodelar);
	glutKeyboardFunc(teclado);
	glutSpecialFunc(teclasFlechas);
	glutMainLoop();

	return 0;
}
