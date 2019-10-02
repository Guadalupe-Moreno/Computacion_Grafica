/*
Practica_5:
	Creacion de un brazo con movimiento
*/

#include <GL/glut.h>

float transZ = -5.0f;
float transX = 0.0f;
float angleX = 0.0f;
float angleY = 0.0f;
int screenW = 0.0;
int screenH = 0.0;
float angCodo = 0.0f;
float angMuñeca = 0.0f;
float angF1 = 0.0f;
float angDindice = 0.0f;
float angDmedio = 0.0f;
float angDanular = 0.0f;
float angDmeñique = 0.0f;



GLfloat Position[] = { 0.0f, 3.0f, 0.0f, 1.0f };			// Light Position
GLfloat Position2[] = { 0.0f, 0.0f, -5.0f, 1.0f };			// Light Position


void InitGL(void)     // Inicializamos parametros
{

	glShadeModel(GL_SMOOTH);							// Habilitamos Smooth Shading
	glClearColor(0.219, 0.941, 0.890, 1);				// Negro de fondo
	glClearDepth(1.0f);									// Configuramos Depth Buffer
	glEnable(GL_DEPTH_TEST);							// Habilitamos Depth Testing

	//Configuracion luz
	glLightfv(GL_LIGHT0, GL_POSITION, Position);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, Position2);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);


	glDepthFunc(GL_LEQUAL);								// Tipo de Depth Testing a realizar
	glEnable(GL_COLOR_MATERIAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void prisma(void)
{
	GLfloat vertice[8][3] = {
				{0.5 ,-0.5, 0.5},    //Coordenadas Vértice 0 V0
				{-0.5 ,-0.5, 0.5},    //Coordenadas Vértice 1 V1
				{-0.5 ,-0.5, -0.5},    //Coordenadas Vértice 2 V2
				{0.5 ,-0.5, -0.5},    //Coordenadas Vértice 3 V3
				{0.5 ,0.5, 0.5},    //Coordenadas Vértice 4 V4
				{0.5 ,0.5, -0.5},    //Coordenadas Vértice 5 V5
				{-0.5 ,0.5, -0.5},    //Coordenadas Vértice 6 V6
				{-0.5 ,0.5, 0.5},    //Coordenadas Vértice 7 V7
	};

	glBegin(GL_POLYGON);	//Front
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3fv(vertice[0]);
	glVertex3fv(vertice[4]);
	glVertex3fv(vertice[7]);
	glVertex3fv(vertice[1]);
	glEnd();

	glBegin(GL_POLYGON);	//Right
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3fv(vertice[0]);
	glVertex3fv(vertice[3]);
	glVertex3fv(vertice[5]);
	glVertex3fv(vertice[4]);
	glEnd();

	glBegin(GL_POLYGON);	//Back
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3fv(vertice[6]);
	glVertex3fv(vertice[5]);
	glVertex3fv(vertice[3]);
	glVertex3fv(vertice[2]);
	glEnd();

	glBegin(GL_POLYGON);  //Left
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3fv(vertice[1]);
	glVertex3fv(vertice[7]);
	glVertex3fv(vertice[6]);
	glVertex3fv(vertice[2]);
	glEnd();

	glBegin(GL_POLYGON);  //Bottom
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3fv(vertice[0]);
	glVertex3fv(vertice[1]);
	glVertex3fv(vertice[2]);
	glVertex3fv(vertice[3]);
	glEnd();

	glBegin(GL_POLYGON);  //Top
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3fv(vertice[4]);
	glVertex3fv(vertice[5]);
	glVertex3fv(vertice[6]);
	glVertex3fv(vertice[7]);
	glEnd();
}

void display(void)   // Creamos la funcion donde se dibuja
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Limiamos pantalla y Depth Buffer
	//glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(transX, 0.0f, transZ);
	glRotatef(angleY, 0.0, 1.0, 0.0);
	glRotatef(angleX, 1.0, 0.0, 0.0);
	glPushMatrix();//inicio

	//Brazo
	glPushMatrix();//inicio Brazo

		//Hombro
		glPushMatrix();//inicio Hombro
			glColor3f(1.0f, 1.0f, 0.0f);
			glScalef(1.0F, 1.0F, 1.0F);
			prisma();
		glPopMatrix();//termino Hombro

		glTranslatef(1.5f, 0.0f, 0.0f);

		//Bicep
		glPushMatrix();//inicio Bicep
			glColor3f(0.0f, 1.0f, 0.0f);
			glScalef(2.0F, 1.0F, 1.0F);
			prisma();
		glPopMatrix();//termino Bicep

			glTranslatef(1.0f, 0.0f, 0.0f);
			glRotatef(angCodo, 0.0f, 1.0f, 0.0f);
			glTranslatef(1.0f, 0.0f, 0.0f);

		//Antebrazo
		glPushMatrix();//inicio Antebrazo
			glColor3f(1.0f, 0.0f, 0.0f);
			glScalef(2.0f, 1.0f, 1.0f);
			prisma();
		glPopMatrix();//termino Antebrazo

			glTranslatef(1.0f, 0.0f, 0.0f);
			glRotatef(angMuñeca, 0.0f, 1.0f, 0.0f);
			glTranslatef(0.5f, 0.0f, 0.0f);

		//Palma
		glPushMatrix();//inicio Palma
			glColor3f(0.0f, 0.0f, 1.0f);
			glScalef(1.0f, 1.0f, 0.5f);
			prisma();
		glPopMatrix();//termino Palma


		//Dedo pulgar
		glPushMatrix();//Inicio pulgar
			glTranslatef(-0.4f, 0.5f, 0);
			glRotatef(angF1, 1.0f, 0.0f, 0.0f);
			glTranslatef(0.0f, 0.1f, 0.0f);

		//Primer falange
			glPushMatrix();
			glColor3f(0.882f, 0.019f, 0.811f);
				glScalef(0.2f, 0.2f, 0.5f);
				prisma();
			glPopMatrix();

				glTranslatef(0.0f, 0.1f, 0.0f);
				glRotatef(angF1 * 0.3f, 1.0f, 0.0f, 0.0f);
				glTranslatef(0.0f, 0.1f, 0.0f);

			//Segundo falanje
				glPushMatrix();
				glColor3f(0.882f, 0.019f, 0.811f);
					glScalef(0.2f, 0.2f, 0.5f);
					prisma();
				glPopMatrix();

		glPopMatrix();//Termino pulgar

	//Dedo indice
	glPushMatrix();//Inicio indice
		glTranslatef(0.5f, 0.45f, 0.0f);
		glRotatef(angDindice, 0.0f, 1.0f, 0.0f);
		glTranslatef(0.15f, 0.0f, 0.0f);
			glPushMatrix();
			glColor3f(0.882f, 0.019f, 0.811f);
				glScalef(0.3f, 0.1f, 0.2f);
				prisma();
			glPopMatrix();

				glTranslatef(0.15f, 0.0f, 0.0f);
				glRotatef(angDindice * 0.3f, 0.0f, 1.0f, 0.0f);
				glTranslatef(0.15f, 0.0f, 0.0f);

			glPushMatrix();
			glColor3f(0.882f, 0.019f, 0.811f);
				glScalef(0.3f, 0.1f, 0.2f);
				prisma();
			glPopMatrix();

				glTranslatef(0.15f, 0.0f, 0.0f);
				glRotatef(angDindice * 0.3f, 0.0f, 1.0f, 0.0f);
				glTranslatef(0.15f, 0.0f, 0.0f);

			glPushMatrix();
			glColor3f(0.882f, 0.019f, 0.811f);
				glScalef(0.3f, 0.1f, 0.2f);
				prisma();
			glPopMatrix();

	glPopMatrix();//Termino indice


	//Dedo medio
	glPushMatrix();//Inicio medio
		glTranslatef(0.55f, 0.15f, 0.0f);
		glRotatef(angDmedio, 0.0f, 1.0f, 0.0f);
		glTranslatef(0.15f, 0.0f, 0.0f);

		glPushMatrix();
			glColor3f(0.882f, 0.019f, 0.811f);
			glScalef(0.4f, 0.1f, 0.2f);
			prisma();
		glPopMatrix();

		glTranslatef(0.25f, 0.0f, 0.0f);
		glRotatef(angDmedio * 0.3, 0.0f, 1.0f, 0.0f);
		glTranslatef(0.15f, 0.0f, 0.0f);

		glPushMatrix();
			glColor3f(0.882f, 0.019f, 0.811f);
			glScalef(0.4f, 0.1f, 0.2f);
			prisma();
		glPopMatrix();


		glTranslatef(0.25f, 0.0f, 0.0f);
		glRotatef(angDmedio * 0.3, 0.0f, 1.0f, 0.0f);
		glTranslatef(0.15f, 0.0f, 0.0f);

		glPushMatrix();
			glColor3f(0.882f, 0.019f, 0.811f);
			glScalef(0.4f, 0.1f, 0.2f);
			prisma();
		glPopMatrix();

	glPopMatrix();//Termino medio

	//Dedo anular
	glPushMatrix();//inicio anular
		glTranslatef(0.5f, -0.15f, 0.0f);
		glRotatef(angDanular, 0.0f, 1.0f, 0.0f);
		glTranslatef(0.15f, 0.0f, 0.0f);

		glPushMatrix();
			glColor3f(0.882f, 0.019f, 0.811f);
			glScalef(0.3f, 0.1f, 0.2f);
			prisma();
		glPopMatrix();

		glTranslatef(0.15f, 0.0f, 0.0f);
		glRotatef(angDanular * 0.3, 0.0f, 1.0f, 0.0f);
		glTranslatef(0.15f, 0.0f, 0.0f);

		glPushMatrix();
			glColor3f(0.882f, 0.019f, 0.811f);
			glScalef(0.3f, 0.1f, 0.2f);
			prisma();
		glPopMatrix();

		glTranslatef(0.15f, 0.0f, 0.0f);
		glRotatef(angDanular * 0.3, 0.0f, 1.0f, 0.0f);
		glTranslatef(0.15f, 0.0f, 0.0f);

		glPushMatrix();
			glColor3f(0.882f, 0.019f, 0.811f);
			glScalef(0.3f, 0.1f, 0.2f);
			prisma();
		glPopMatrix();

	glPopMatrix();//Termino anular

	//Dedo meñique
	glPushMatrix();//Inicio meñique
		glTranslatef(0.45f, -0.45f, 0.0f);
		glRotatef(angDmeñique, 0.0f, 1.0f, 0.0f);
		glTranslatef(0.15f, 0.0f, 0.0f);

		glPushMatrix();
			glColor3f(0.882f, 0.019f, 0.811f);
			glScalef(0.2f, 0.1f, 0.2f);
			prisma();
		glPopMatrix();

		glTranslatef(0.05f, 0.0f, 0.0f);
		glRotatef(angDmeñique * 0.3, 0.0f, 1.0f, 0.0f);
		glTranslatef(0.15f, 0.0f, 0.0f);

		glPushMatrix();
			glColor3f(0.882f, 0.019f, 0.811f);
			glScalef(0.2f, 0.1f, 0.2f);
			prisma();
		glPopMatrix();

		glTranslatef(0.05f, 0.0f, 0.0f);
		glRotatef(angDmeñique * 0.3, 0.0f, 1.0f, 0.0f);
		glTranslatef(0.15f, 0.0f, 0.0f);

		glPushMatrix();
			glColor3f(0.882f, 0.019f, 0.811f);
			glScalef(0.2f, 0.1f, 0.2f);
			prisma();
		glPopMatrix();

	glPopMatrix();//Termino meñique

glPopMatrix();//Temino palma
glPopMatrix();//final

	glutSwapBuffers();
}

void reshape(int width, int height)   // Creamos funcion Reshape
{
	if (height == 0){
		height = 1;
	}

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);						// Seleccionamos Projection Matrix
	glLoadIdentity();
	glFrustum(-5, 5, -5, 5, 4.0, 20.0);

	glMatrixMode(GL_MODELVIEW);							// Seleccionamos Modelview Matrix								
}

void keyboard(unsigned char key, int x, int y)  // Create Keyboard Function
{
	switch (key) {
	case 'w':
	case 'W':
		transZ += 0.2f;
		break;
	case 's':
	case 'S':
		transZ -= 0.2f;
		break;
	case 'a':
	case 'A':
		transX += 0.2f;
		break;
	case 'd':
	case 'D':
		transX -= 0.2f;
		break;


	case 'r':
		if (angCodo <= 130)
			angCodo += 2.0f;

		break;
	case 'R':
		if (angCodo >= 0)
			angCodo -= 2.0f;

		break;

	case 't':
		if (angMuñeca <= 85)
			angMuñeca += 2.0f;

		break;
	case 'T':
		if (angMuñeca >= -30)
			angMuñeca -= 2.0f;

		break;

	case 'y':
		if (angF1 >= -90)
			angF1 -= 2.0f;
		break;
	case 'Y':
		if (angF1 <= 0)
			angF1 += 2.0f;
		break;

	case 'u':
		if (angDindice <= 90)
			angDindice += 2.0f;
		break;
	case 'U':
		if (angDindice >= 0)
			angDindice -= 2.0f;
		break;

	case 'i':
		if (angDmedio <= 90)
			angDmedio += 2.0f;
		break;
	case 'I':
		if (angDmedio >= 0)
			angDmedio -= 2.0f;
		break;

	case 'o':
		if (angDanular <= 90)
			angDanular += 2.0f;
		break;
	case 'O':
		if (angDanular >= 0)
			angDanular -= 2.0f;
		break;

	case 'p':
		if (angDmeñique <= 90)
			angDmeñique += 2.0f;
		break;
	case 'P':
		if (angDmeñique >= 0)
			angDmeñique -= 2.0f;
		break;




	case 27:        // Cuando Esc es presionado...
		exit(0);   // Salimos del programa
		break;
	default:        // Cualquier otra
		break;
	}
	glutPostRedisplay();
}


void arrow_keys(int a_keys, int x, int y)  // Funcion para manejo de teclas especiales (arrow keys)
{
	switch (a_keys) {
	case GLUT_KEY_UP:		// Presionamos tecla ARRIBA...
		angleX += 2.0f;
		break;
	case GLUT_KEY_DOWN:		// Presionamos tecla ABAJO...
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


int main(int argc, char** argv)   // Main Function
{
	glutInit(&argc, argv); // Inicializamos OpenGL
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // Display Mode (Clores RGB y alpha | Buffer Doble )
	screenW = glutGet(GLUT_SCREEN_WIDTH);
	screenH = glutGet(GLUT_SCREEN_HEIGHT);
	glutInitWindowSize(500, 500);	// Tamaño de la Ventana
	glutInitWindowPosition(0, 0);	//Posicion de la Ventana
	glutCreateWindow(argv[1]); // Nombre de la Ventana
	InitGL();						// Parametros iniciales de la aplicacion
	glutDisplayFunc(display);  //Indicamos a Glut función de dibujo
	glutReshapeFunc(reshape);	//Indicamos a Glut función en caso de cambio de tamano
	glutKeyboardFunc(keyboard);	//Indicamos a Glut función de manejo de teclado
	glutSpecialFunc(arrow_keys);	//Otras
	glutMainLoop();          // 

	return 0;
}