/*
Practica_3:
	Dibujo basico empleando un cubo y aplicando transformaciones basicas
*/
#include"stdlib.h"
#include<GL/glut.h>

//funcion para inicialisar estados de gl
void inicializar() {
	glClearColor(0.219, 0.941, 0.890, 1);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void prisma() {
	GLfloat vertice[8][3] = {
		{0.5, -0.5, 0.5},
		{-0.5, -0.5, 0.5},
		{-0.5, -0.5, -0.5},
		{0.5, -0.5, -0.5},
		{0.5, 0.5, 0.5},
		{0.5, 0.5, -0.5},
		{-0.5, 0.5, -0.5},
		{-0.5, 0.5, 0.5},
	};

	glBegin(GL_POLYGON);  //ENFRENTE
	glColor3f(0.196, 0.266, 0.862);
	glVertex3fv(vertice[0]);
	glVertex3fv(vertice[4]);
	glVertex3fv(vertice[7]);
	glVertex3fv(vertice[1]);
	glEnd();

	glBegin(GL_POLYGON); //DERECHA
	glVertex3fv(vertice[0]);
	glVertex3fv(vertice[3]);
	glVertex3fv(vertice[5]);
	glVertex3fv(vertice[4]);
	glEnd();

	glBegin(GL_POLYGON); //ATRAS
	glVertex3fv(vertice[6]);
	glVertex3fv(vertice[5]);
	glVertex3fv(vertice[3]);
	glVertex3fv(vertice[2]);
	glEnd();

	glBegin(GL_POLYGON);  //Izquierda
	glVertex3fv(vertice[1]);
	glVertex3fv(vertice[7]);
	glVertex3fv(vertice[6]);
	glVertex3fv(vertice[2]);
	glEnd();

	glBegin(GL_POLYGON); //DABAJO
	glVertex3fv(vertice[0]);
	glVertex3fv(vertice[1]);
	glVertex3fv(vertice[2]);
	glVertex3fv(vertice[3]);
	glEnd();

	glBegin(GL_POLYGON); //ATRRIBA
	glVertex3fv(vertice[4]);
	glVertex3fv(vertice[5]);
	glVertex3fv(vertice[6]);
	glVertex3fv(vertice[7]);
	glEnd();
}

void dibujar() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0.0f, 0.0f, -5.0f);

	glRotatef(-35.0, 0.0, 1.0, 0.0); //girar sobre y sentido horario
	glRotatef(-15.0, 0.0, 0.0, 1.0); //girar sobre z sentido horario
	glRotatef(15.0, 1.0, 0.0, 0.0); //girar sobre x sentido antihorario
	prisma();
	glTranslatef(0.0f, 0.0f, -1.0f);
	prisma();

	glTranslatef(2.0f, 0.0f, 0.0f);
	prisma();
	glTranslatef(0.0f, 0.0f, 1.0f);
	prisma();

	glLoadIdentity();
	glTranslatef(0.0f, 2.0f, -5.0f);
	glRotatef(-35.0, 0.0, 1.0, 0.0); //girar sobre y sentido horario
	glRotatef(-15.0, 0.0, 0.0, 1.0); //girar sobre z sentido horario
	glRotatef(15.0, 1.0, 0.0, 0.0); //girar sobre x sentido antihorario
	prisma();
	glTranslatef(0.0f, 0.0f, -1.0f);
	prisma();

	glTranslatef(2.0f, 0.0f, 0.0f);
	prisma();
	glTranslatef(0.0f, 0.0f, 1.0f);
	prisma();

	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -6.0f);
	glRotatef(-35.0, 0.0, 1.0, 0.0); //girar sobre y sentido horario
	glRotatef(-15.0, 0.0, 0.0, 1.0); //girar sobre z sentido horario
	glRotatef(15.0, 1.0, 0.0, 0.0); //girar sobre x sentido antihorario

	glTranslatef(0.5f, 0.0f, -1.0f);
	prisma();
	glTranslatef(2.0f, 0.0f, 0.0f);
	prisma();

	glTranslatef(0.0f, 1.0f, 0.0f);
	prisma();
	glTranslatef(-1.0f, 0.0f, 0.0f);
	prisma();
	glTranslatef(-1.0f, 0.0f, 0.0f);
	prisma();

	glTranslatef(0.0f, 1.0f, 0.0f);
	prisma();
	glTranslatef(1.0f, 0.0f, 0.0f);
	prisma();
	glTranslatef(1.0f, 0.0f, 0.0f);
	prisma();

	glTranslatef(-1.0f, 1.0f, 0.0f);
	prisma();

	glFlush();
}

void remodelar(int width, int height) {
	if (height == 0) {
		height = 1;
	}
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//Tipo de vista
	//glOrtho(-5, 5, -5, 5, 0.1, 20);

	glFrustum(-5, 5, -5, 5, 3.0, 20.0);
	glutPostRedisplay();
}

void teclado(unsigned char key, int x, int y) {
	if (key == 27)
		exit(0);

	glutPostRedisplay();
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(400, 250);
	glutCreateWindow(argv[1]);
	inicializar();
	glutDisplayFunc(dibujar);
	glutReshapeFunc(remodelar);
	glutKeyboardFunc(teclado);
	//glut SpacialFunc();
	glutMainLoop();

	return 0;
}