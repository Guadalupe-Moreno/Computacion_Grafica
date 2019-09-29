/*
Practica_1:
	Creacion de una ventana 
*/
#include<GL/glut.h>

void dibujar(void) {
	glClearColor(0.219, 0.941, 0.890, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}
int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 250);
	glutInitWindowPosition(50, 25);
	glutCreateWindow(argv[1]);
	glutDisplayFunc(dibujar);
	glutMainLoop();

	return 0;
}