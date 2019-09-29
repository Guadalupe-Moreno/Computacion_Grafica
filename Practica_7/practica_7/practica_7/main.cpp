/*
Practica_7:
	Sistema solar con iluminacion
*/
#include <stdlib.h>
#include<GL/glut.h>
#include <windows.h>

float transZ = -10.0f;
float transX = 0.0f;
float transY = 0.0f;

float angleX = 0.0f;
float angleY = 0.0f;

int giraRotaLuisMi = 0.0f;

//variables de animacion
struct timeval strart;
DWORD dwFrames = 0;
DWORD dwCurrentTime = 0;
DWORD dwLastUpdateTime = 0;
DWORD dwElapsedTime = 0;

// Datos de las componentes ambiente, difusa y especular
// de nuestra fuente de luz.
//ambiente reflejada de todas partes - poca 
//difusa reflejada de la fuente de luz - mucha
//especular reflejada en el punto - mucha
GLfloat luzAmbiente[] = { 0.2f, 0.2f, 0.2f, 1.0f };
GLfloat luzDifusa[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat luzEspecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };


//sol - direccional - como el último es cero debe ser a donde alumbra, hacia abajo
GLfloat luzPosicionSol[] = { 0.0f, 1.0f, 0.0f, 0.0f };

//foco - puntual - el último es uno, los otros son las coordenadas del foco
GLfloat luzPosicionFoco[] = { 2.0f, 2.0f, 0.0f, 1.0f };

//linterna - focal - lleva posición de la linterna, vector con la dirección a la q apunta y
// ángulo con el cono de apertura de la luz
GLfloat luzPosicionLinterna[] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat luzDireccionLinterna[] = { 0.0f, 0.0f, -2.0f };
float anguloLinterna = 30.0f;


// Datos de las componentes ambiente, difusa y especular
// del primer material. 
GLfloat mat_ambient[] = { 1.0, 1.0, 0.0 };					// Color background
GLfloat mat_diffuse[] = { 0.0, 1.0, 0.0, 1.0 };					// Object Color main
GLfloat mat_specular[] = { 0.0, 0.0, 1.0, 1.0 };				// Specular color
GLfloat mat_shininess[] = { 100.0 };							// 1 to greatest


void inicializar(void) {
	glClearColor(0.831, 0.949, 0.988, 1);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	//glShadeModel(GL_SMOOTH); 
	glShadeModel(GL_FLAT);

	glLightfv(GL_LIGHT1, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, luzDifusa);
	glLightfv(GL_LIGHT1, GL_SPECULAR, luzEspecular);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);
}

void anima(void) {
	// Calculate the number of frames per one second:
	//dwFrames++;
	dwCurrentTime = GetTickCount(); // Even better to use timeGetTime()
	dwElapsedTime = dwCurrentTime - dwLastUpdateTime;

	if (dwElapsedTime >= 30) {
		giraRotaLuisMi = (giraRotaLuisMi - 1) % 360;

		dwLastUpdateTime = dwCurrentTime;
	}

	glutPostRedisplay();
}

void dibujar(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Limpiamos pantalla y Depth Buffer

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//probando tipos de luces

	//La luz del sol va antes de las transformaciones para mantener su pocicion
	//glLightfv(GL_LIGHT1, GL_POSITION, luzPosicionSol);

	//La luz del foco va antes para mantener su posicion
	//glLightfv(GL_LIGHT1, GL_POSITION, luzPosicionFoco);

	//La luz de la linterna va antes para mantener su posicion
	//se debe pasar tambien la propiedad del angulo 
	glLightfv(GL_LIGHT1, GL_POSITION, luzPosicionLinterna);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, luzDireccionLinterna);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, anguloLinterna);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 50.0);

	//se debe recorrer hacia z negativo xq la cara de enfrente está mi espalda
	//si no lo recorro lo suficiente las caras de los lados se verán largas
	glTranslatef(transX, transY, transZ);

	glRotatef(angleY, 0.0, 1.0, 0.0);	 //gira sobre y sentido horario
	glRotatef(angleX, 1.0, 0.0, 0.0);	 //gira sobre x sentido antihorario

	glRotatef(giraRotaLuisMi, 0.0, 1.0, 0.0); //el sol gira sobre su propio eje

	//glColor3f(1.0,1.0,0.0); //sol amarillo
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glutSolidSphere(1.9, 12, 12); //Draw Sun (radio,H,V);
	//glutWireSphere(1.9,12,12);   //Draw Sun (radio,H,V);
	//prisma();

	//glFlush();
	glutSwapBuffers();
}

void remodelar(int width, int heigth) {
	if (heigth == 0) {
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

int main(int argc, char* argv[]) {
	//inicializa GLUT con el sistema de ventanas pasando los argumentos del main
	glutInit(&argc, argv);

	//Buffer simple para dibujar
	//Colores RGB y alpha
	//Buffer de profundidad
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	//Define ventana de 500 pixeles de ancho por 500 de alto
	glutInitWindowSize(600, 600);
	//Posiciona la ventana de izquierda a derecha 50 pixeles y de arriba a abajo 25
	glutInitWindowPosition(400, 100);
	//Crea y abre la ventana y recibe el nombre que va en su barra de título
	glutCreateWindow("MorenoMadridMariaGuadalupe");
	//Llamada a función propia para inicializar estados de opengl
	inicializar();
	//Llamada a la función a ser dibujada y redibujada
	glutDisplayFunc(dibujar);
	glutReshapeFunc(remodelar);
	//Lamada a función que maneja eventos del teclado
	glutKeyboardFunc(teclado);
	glutSpecialFunc(teclasFlechas);
	glutIdleFunc(anima);
	//glutIdleFunc( luisMianima );
	//Llamada a función que cede el control a GLUT y procesa eventos de ventana, ratón
	glutMainLoop();
	//termina la ejecución devolviendo cero
	return 0;
}