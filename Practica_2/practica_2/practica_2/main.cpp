#include<GL/glut.h>

void dibujar(void) {
	glClearColor(0.219, 0.941, 0.890, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	//define el tipo de proyeccion e informacion relatica a la camara
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); //cargamos matriz identidad

	//proyeccion ortografica dentro del cubo indicado
	glOrtho(-5, 50, -5, 50, -1, 1);

	//define la colocacion de los objetos en la escena y el punto de vista
	glMatrixMode(GL_MODELVIEW);

	glLineWidth(3.0);//grosor de la linea en pixeles
	glColor3f(1.0, 0.0, 0.0);//el color de toda la figura

	//Corazon unicolor
	/*glBegin(GL_TRIANGLES);
		glVertex3f(4, 1, 0);
		glVertex3f(7, 4, 0);
		glVertex3f(1, 4, 0);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3f(1, 4, 0);
		glVertex3f(7, 4, 0);
		glVertex3f(7, 5, 0);
		glVertex3f(1, 5, 0);


		glVertex3f(1, 5, 0);
		glVertex3f(4, 5, 0);
		glVertex3f(3, 6, 0);
		glVertex3f(2, 6, 0);


		glVertex3f(4, 5, 0);
		glVertex3f(7, 5, 0);
		glVertex3f(6, 6, 0);
		glVertex3f(5, 6, 0);

	glEnd();*/

	//Corazon degradado
	glBegin(GL_QUADS);
	glColor3f(0.870, 0.050, 0.078);//el color de toda la figura
	glVertex3f(1, 20, 0);
	glVertex3f(2, 19, 0);
	glVertex3f(2, 22, 0);
	glVertex3f(1, 21, 0);

	glColor3f(0.941, 0.156, 0.184);//el color de toda la figura
	glVertex3f(2, 19, 0);
	glVertex3f(3, 18, 0);
	glVertex3f(3, 22, 0);
	glVertex3f(2, 22, 0);

	glColor3f(0.949, 0.450, 0.466);//el color de toda la figura
	glVertex3f(3, 18, 0);
	glVertex3f(4, 17, 0);
	glVertex3f(4, 21, 0);
	glVertex3f(3, 22, 0);

	glColor3f(0.972, 0.545, 0.560);//el color de toda la figura
	glVertex3f(4, 17, 0);
	glVertex3f(5, 18, 0);
	glVertex3f(5, 22, 0);
	glVertex3f(4, 21, 0);

	glColor3f(0.984, 0.635, 0.647);//el color de toda la figura
	glVertex3f(5, 18, 0);
	glVertex3f(6, 19, 0);
	glVertex3f(6, 22, 0);
	glVertex3f(5, 22, 0);

	glColor3f(0.992, 0.768, 0.776);//el color de toda la figura
	glVertex3f(6, 19, 0);
	glVertex3f(7, 20, 0);
	glVertex3f(7, 21, 0);
	glVertex3f(6, 22, 0);

	glEnd();

	//C uniculor
	/*glBegin(GL_QUADS);
		glVertex3f(1, 1, 0);
		glVertex3f(6, 1, 0);
		glVertex3f(6, 3, 0);
		glVertex3f(3, 3, 0);


		glVertex3f(1, 1, 0);
		glVertex3f(3, 3, 0);
		glVertex3f(3, 7, 0);
		glVertex3f(1, 9, 0);


		glVertex3f(3, 7, 0);
		glVertex3f(6, 7, 0);
		glVertex3f(6, 9, 0);
		glVertex3f(1, 9, 0);

	glEnd();*/

	//C colores
	/*glBegin(GL_QUADS);
	glColor3f(0.772, 0.125, 0.725);//el color de toda la figura
		glVertex3f(1, 1, 0);
		glVertex3f(6, 1, 0);
		glVertex3f(6, 3, 0);
		glVertex3f(3, 3, 0);

	glColor3f(0.125, 0.184, 0.772);//el color de toda la figura
		glVertex3f(1, 1, 0);
		glVertex3f(3, 3, 0);
		glVertex3f(3, 7, 0);
		glVertex3f(1, 9, 0);

	glColor3f(0.180, 0.917, 0.290);//el color de toda la figura
		glVertex3f(3, 7, 0);
		glVertex3f(6, 7, 0);
		glVertex3f(6, 9, 0);
		glVertex3f(1, 9, 0);

	glEnd();*/

	//FLOR
	glBegin(GL_LINES);
	glLineWidth(3.0);
	glColor3f(0.180, 0.917, 0.290);//el color de toda la figura
	glVertex3f(4, 7, 0);
	glVertex3f(4, 11, 0);

	glVertex3f(4, 8, 0);
	glVertex3f(5, 10, 0);
	glVertex3f(4, 9, 0);

	glVertex3f(3, 11, 0);
	glVertex3f(4, 9, 0);
	glVertex3f(4, 10, 0);

	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0, 0.266, 0.921);//el color de toda la figura
	glVertex3f(4, 11, 0);
	glVertex3f(3, 12, 0);
	glVertex3f(3, 14, 0);
	glVertex3f(4, 13, 0);
	glVertex3f(5, 14, 0);
	glVertex3f(5, 12, 0);

	glEnd();

	//G uniculor
	glBegin(GL_QUADS);
	glColor3f(0.019, 0.094, 0.282);//el color de toda la figura
	glVertex3f(2, 26, 0);
	glVertex3f(3, 25, 0);
	glVertex3f(3, 30, 0);
	glVertex3f(2, 29, 0);


	glVertex3f(3, 25, 0);
	glVertex3f(6, 25, 0);
	glVertex3f(6, 26, 0);
	glVertex3f(3, 26, 0);


	glVertex3f(5, 26, 0);
	glVertex3f(6, 26, 0);
	glVertex3f(6, 28, 0);
	glVertex3f(5, 28, 0);


	glVertex3f(4, 27, 0);
	glVertex3f(5, 27, 0);
	glVertex3f(5, 28, 0);
	glVertex3f(4, 28, 0);


	glVertex3f(3, 29, 0);
	glVertex3f(5, 29, 0);
	glVertex3f(5, 30, 0);
	glVertex3f(3, 30, 0);

	glEnd();

	//M uniculor
	glBegin(GL_QUADS);
	glColor3f(0.019, 0.094, 0.282);//el color de toda la figura
	glVertex3f(2, 0, 0);
	glVertex3f(3, 0, 0);
	glVertex3f(3, 4, 0);
	glVertex3f(2, 4, 0);


	glVertex3f(3, 3, 0);
	glVertex3f(4, 2, 0);
	glVertex3f(4, 3, 0);
	glVertex3f(3, 4, 0);


	glVertex3f(4, 2, 0);
	glVertex3f(5, 3, 0);
	glVertex3f(5, 4, 0);
	glVertex3f(4, 3, 0);


	glVertex3f(5, 0, 0);
	glVertex3f(6, 0, 0);
	glVertex3f(6, 4, 0);
	glVertex3f(5, 4, 0);

	glEnd();

	glFlush();
}
int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(500, 250);
	glutInitWindowPosition(50, 25);
	glutCreateWindow(argv[1]);
	glutDisplayFunc(dibujar);
	glutMainLoop();

	return 0;
}