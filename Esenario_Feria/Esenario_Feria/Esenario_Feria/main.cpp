
#include <stdlib.h>
#include <GL/glut.h>
#include <windows.h>

#include "texture.h"
#include "figuras.h"
#include "Camera.h"
#include "Textura_piel.c"
#include "Textura_bola.c"
#include "Textura_blanco.c"
#include "Textura_negro.c"
#include "Textura_piso.c"
#include "Textura_metal.c"
#include "Textura_amarillo.c"
#include "Textura_azul.c"
#include "Textura_azulm.c"
#include "Textura_lad.c"
#include "Textura_madero.c"
#include "Textura_morado.c"
#include "Textura_rojo.c"
#include "Textura_rosa.c"
#include "Textura_suelo.c"
#include "Textura_tela.c"
#include "Textura_verde.c"
#include "Textura_tubo.c"
#include "Textura_algodon.c"
#include "Textura_CI.c"
#include "Textura_CS.c"
#include "Textura_P1.c"
#include "Textura_P2.c"
#include "Textura_P3.c"
#include "Textura_P4.c"
#include "Textura_P5.c"
#include "Textura_P6.c"

#include "cmodel/CModel.h"

//incluir la biblioteca irrKlang.h
#include <irrKlang.h>
//enlazar el dll con la instrucción pragma
#pragma comment(lib, "irrKlang.lib")
//arrancar el motor de sonido
irrklang::ISoundEngine* engine = irrklang::createIrrKlangDevice();
//agregar fuente de sonido para el audio de fondo
irrklang::ISoundSource* audioFondo = engine->addSoundSourceFromFile("audios/101-opening.mp3");
//agregar fuente de sonido para el audio de pikachu que es lanzado con tecla
irrklang::ISoundSource* audioPikachu = engine->addSoundSourceFromFile("audios/025-Pikachu.wav");

//importante para cargar modelos porque hace referencia al .lib de CModel
//Solo para Visual Studio 2015 o mayor
#if (_MSC_VER >= 1900)
#   pragma comment( lib, "legacy_stdio_definitions.lib" )
#endif

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
GLuint idTextura_suelo;
GLuint idTextura_piso;
GLuint idTextura_metal;
GLuint idTextura_tela;
GLuint idTextura_verde;
GLuint idTextura_rosa;
GLuint idTextura_rojo;
GLuint idTextura_morado;
GLuint idTextura_madero;
GLuint idTextura_lad;
GLuint idTextura_azul;
GLuint idTextura_azulm;
GLuint idTextura_amarillo;
GLuint idTextura_tubo;
GLuint idTextura_algodon;
GLuint idTextura_CI;
GLuint idTextura_CS;
GLuint idTextura_P1;
GLuint idTextura_P2;
GLuint idTextura_P3;
GLuint idTextura_P4;
GLuint idTextura_P5;
GLuint idTextura_P6;

CTexture Textura_pino;
CTexture Textura_campo;
CTexture Textura_puerta_madera;
CTexture Textura_puerta_madera_lateral;

CTexture Textura_Elicoctero_A;
CTexture Textura_Elicoctero_B;
CTexture Textura_Elicoctero_C;
CTexture Textura_Elicoctero_D;
CTexture Textura_Elicoctero_E;
CTexture Textura_Elicoctero_F;
CTexture Textura_Elicoctero_G;

CTexture Textura_Oso_A;
CTexture Textura_Oso_B;

CTexture Textura_Aguila_A;
CTexture Textura_Aguila_B;

CTexture Textura_Banca_A;
CTexture Textura_Banca_B;

CTexture Textura_Contenedor_A;
CTexture Textura_Contenedor_B;

CTexture Textura_Puesto_A;
CTexture Textura_Puesto_B;
CTexture Textura_Puesto_C;

CTexture Textura_Carreta_A;

CTexture Textura_Arbol_A;
CTexture Textura_Arbol_B;
CTexture Textura_Arbol_C;

//Variable para la Animación puerta
GLint ang_rot_puerta = 0;

struct timeval strart;
DWORD dwFrames = 0;
DWORD dwCurrentTime = 0;
DWORD dwLastUpdateTime = 0;
DWORD dwElapsedTime = 0;

int giraRotaTorso = 0.0f;
int giraRotaEje = 0.0f;
int giraRotaBarra = 0.0f;
int giraRotaP1 = 0.0f;
int giraRotaCono = 0.0f;
int giraRotaElic = 0.0f;
int giraRotaCanoa = 0.0f;

//variables para cámara
CCamera objCamera;	//Create objet Camera
GLfloat g_lookupdown = 0.0f;    // Look Position In The Z-Axis (NEW) 

CCamera objCamera_Sillas;	//Create objet Camera
CCamera objCamera_Pulpo;	//Create objet Camera
CCamera objCamera_Elic;	//Create objet Camera
CCamera objCamera_Rueda;	//Create objet Camera
CCamera objCamera_Bosque;	//Create objet Camera

//objetos de textura para skybox
CTexture textSkyboxUnica;
CTexture textSkyboxFrontal;
CTexture textSkyboxAtras;
CTexture textSkyboxIzquierda;
CTexture textSkyboxDerecha;
CTexture textSkyboxArriba;
CTexture textSkyboxAbajo;

//objetos de figura
CFiguras figSkybox;

//objetos de cmodel para cargar modelos externos en .3ds
CModel Oso;
CModel Elicoctero;
CModel Aguila;
CModel Banca;
CModel Contenedor;
CModel Puesto;
CModel Carreta;
CModel Arbol;
CModel Perro;

//Animación de traslacion
float movKit = 0.0;
bool Activa_sillas = false;
bool avanza = true;

bool Activa_Pulpo = false;
bool Activa_Rueda = false;
bool Activa_Canoa = false;

			
void inicializar ( void )     // Inicializamos parametros
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	// Negro de fondo	

	glEnable(GL_TEXTURE_2D);

	glShadeModel (GL_SMOOTH);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glClearDepth(1.0f);			// Configuramos Depth Buffer
	glEnable(GL_DEPTH_TEST);	// Habilitamos Depth Testing
	glDepthFunc(GL_LEQUAL);		// Tipo de Depth Testing a realizar
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);
	
	textSkyboxFrontal.LoadTGA("ely_hills/hills_ft.tga");
	textSkyboxFrontal.BuildGLTexture();
	textSkyboxFrontal.ReleaseImage();
	
	textSkyboxAtras.LoadTGA("ely_hills/hills_bk.tga");
	textSkyboxAtras.BuildGLTexture();
	textSkyboxAtras.ReleaseImage();

	textSkyboxIzquierda.LoadTGA("ely_hills/hills_lf.tga");
	textSkyboxIzquierda.BuildGLTexture();
	textSkyboxIzquierda.ReleaseImage();

	textSkyboxDerecha.LoadTGA("ely_hills/hills_rt.tga");
	textSkyboxDerecha.BuildGLTexture();
	textSkyboxDerecha.ReleaseImage();
	
	textSkyboxArriba.LoadTGA("ely_hills/hills_up.tga");
	textSkyboxArriba.BuildGLTexture();
	textSkyboxArriba.ReleaseImage();

	textSkyboxAbajo.LoadTGA("ely_hills/hills_dn.tga");
	textSkyboxAbajo.BuildGLTexture();
	textSkyboxAbajo.ReleaseImage();

	Textura_pino.LoadTGA("pino1.tga");
	Textura_pino.BuildGLTexture();
	Textura_pino.ReleaseImage();

	Textura_campo.LoadTGA("campo.tga");
	Textura_campo.BuildGLTexture();
	Textura_campo.ReleaseImage();

	Textura_puerta_madera.LoadTGA("puerta_madera.tga");
	Textura_puerta_madera.BuildGLTexture();
	Textura_puerta_madera.ReleaseImage();

	Textura_puerta_madera_lateral.LoadTGA("puerta_madera_lateral.tga");
	Textura_puerta_madera_lateral.BuildGLTexture();
	Textura_puerta_madera_lateral.ReleaseImage();
	
	Textura_Oso_A.LoadTGA("modelos/Oso/BEAR_BLK.tga");
	Textura_Oso_A.BuildGLTexture();
	Textura_Oso_A.ReleaseImage();

	Textura_Oso_B.LoadTGA("modelos/Oso/BEAR_BK.tga");
	Textura_Oso_B.BuildGLTexture();
	Textura_Oso_B.ReleaseImage();

	Oso._3dsLoad("modelos/Oso/BEAR_BLK.3DS");
	Oso.LoadTextureImages();
	Oso.GLIniTextures();

	Textura_Elicoctero_A.LoadTGA("modelos/Helicoctero/1.tga");
	Textura_Elicoctero_A.BuildGLTexture();
	Textura_Elicoctero_A.ReleaseImage();

	Textura_Elicoctero_B.LoadTGA("modelos/Helicoctero/2.tga");
	Textura_Elicoctero_B.BuildGLTexture();
	Textura_Elicoctero_B.ReleaseImage();

	Textura_Elicoctero_C.LoadTGA("modelos/Helicoctero/fuselage.tga");
	Textura_Elicoctero_C.BuildGLTexture();
	Textura_Elicoctero_C.ReleaseImage();

	Textura_Elicoctero_D.LoadTGA("modelos/Helicoctero/land.tga");
	Textura_Elicoctero_D.BuildGLTexture();
	Textura_Elicoctero_D.ReleaseImage();

	Textura_Elicoctero_E.LoadTGA("modelos/Helicoctero/pal.tga");
	Textura_Elicoctero_E.BuildGLTexture();
	Textura_Elicoctero_E.ReleaseImage();

	Textura_Elicoctero_F.LoadTGA("modelos/Helicoctero/panel.tga");
	Textura_Elicoctero_F.BuildGLTexture();
	Textura_Elicoctero_F.ReleaseImage();

	Textura_Elicoctero_G.LoadTGA("modelos/Helicoctero/Plt.tga");
	Textura_Elicoctero_G.BuildGLTexture();
	Textura_Elicoctero_G.ReleaseImage();

	Elicoctero._3dsLoad("modelos/Helicoctero/uh60.3ds");
	Elicoctero.LoadTextureImages();
	Elicoctero.GLIniTextures();

	Textura_Aguila_A.LoadTGA("modelos/Aguila/EAGLE_2.tga");
	Textura_Aguila_A.BuildGLTexture();
	Textura_Aguila_A.ReleaseImage();

	Textura_Aguila_B.LoadTGA("modelos/Aguila/EAGLE2.tga");
	Textura_Aguila_B.BuildGLTexture();
	Textura_Aguila_B.ReleaseImage();

	Aguila._3dsLoad("modelos/Aguila/EAGLE_2.3DS");
	Aguila.LoadTextureImages();
	Aguila.GLIniTextures();

	Textura_Banca_A.LoadTGA("modelos/Banca/BENCH_2K.tga");
	Textura_Banca_A.BuildGLTexture();
	Textura_Banca_A.ReleaseImage();

	Textura_Banca_B.LoadTGA("modelos/Banca/Bench_2K_Bump.tga");
	Textura_Banca_B.BuildGLTexture();
	Textura_Banca_B.ReleaseImage();

	Banca._3dsLoad("modelos/Banca/Cgtuts_Wood_Bench_3DS.3DS");
	Banca.LoadTextureImages();
	Banca.GLIniTextures();

	Textura_Contenedor_A.LoadTGA("modelos/Contenedor/green_ref.tga");
	Textura_Contenedor_A.BuildGLTexture();
	Textura_Contenedor_A.ReleaseImage();

	Textura_Contenedor_B.LoadTGA("modelos/Contenedor/GREEN_DI.tga");
	Textura_Contenedor_B.BuildGLTexture();
	Textura_Contenedor_B.ReleaseImage();

	Contenedor._3dsLoad("modelos/Contenedor/Garbage_Bin.3DS");
	Contenedor.LoadTextureImages();
	Contenedor.GLIniTextures();

	Textura_Puesto_A.LoadTGA("modelos/CITY_STA/city_stall_d.tga");
	Textura_Puesto_A.BuildGLTexture();
	Textura_Puesto_A.ReleaseImage();

	Textura_Puesto_B.LoadTGA("modelos/city_stall_n.tga");
	Textura_Puesto_B.BuildGLTexture();
	Textura_Puesto_B.ReleaseImage();

	Textura_Puesto_C.LoadTGA("modelos/CITY_STA/city_stall_s.tga");
	Textura_Puesto_C.BuildGLTexture();
	Textura_Puesto_C.ReleaseImage();

	Puesto._3dsLoad("modelos/CITY_STA/city_stall.3DS");
	Puesto.LoadTextureImages();
	Puesto.GLIniTextures();

	Textura_Carreta_A.LoadTGA("modelos/Carreta/Wagen_1.tga");
	Textura_Carreta_A.BuildGLTexture();
	Textura_Carreta_A.ReleaseImage();

	Carreta._3dsLoad("modelos/Carreta/wagen1_Lp_End.3ds");
	Carreta.LoadTextureImages();
	Carreta.GLIniTextures();

	Textura_Arbol_A.LoadTGA("modelos/Arbol/blatt1_a.tga");
	Textura_Arbol_A.BuildGLTexture();
	Textura_Arbol_A.ReleaseImage();

	Textura_Arbol_B.LoadTGA("modelos/Arbol/blatt1.tga");
	Textura_Arbol_B.BuildGLTexture();
	Textura_Arbol_B.ReleaseImage();

	Textura_Arbol_C.LoadTGA("modelos/Arbol/bark_loo.tga");
	Textura_Arbol_C.BuildGLTexture();
	Textura_Arbol_C.ReleaseImage();

	Arbol._3dsLoad("modelos/Arbol/Tree1.3ds");
	Arbol.LoadTextureImages();
	Arbol.GLIniTextures();

	Perro._3dsLoad("modelos/Perro/G_SHEPRD.3DS");
	Perro.LoadTextureImages();
	Perro.GLIniTextures();

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

	//cargaa textura suelo
	glGenTextures(1, &idTextura_suelo);
	glBindTexture(GL_TEXTURE_2D, idTextura_suelo);

	gluBuild2DMipmaps(GL_TEXTURE_2D,
		Textura_suelo.bytes_per_pixel, Textura_suelo.width,
		Textura_suelo.height, GL_RGB, GL_UNSIGNED_BYTE,
		Textura_suelo.pixel_data);

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

	//cargaa textura metal
	glGenTextures(1, &idTextura_metal);
	glBindTexture(GL_TEXTURE_2D, idTextura_metal);

	gluBuild2DMipmaps(GL_TEXTURE_2D,
		Textura_metal.bytes_per_pixel, Textura_metal.width,
		Textura_metal.height, GL_RGB, GL_UNSIGNED_BYTE,
		Textura_metal.pixel_data);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// En caso de no querer repetir las texturas, comentar estas
	// dos líneas
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	glEnable(GL_TEXTURE_2D);

	//cargaa textura tela
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

	//cargaa textura verde
	glGenTextures(1, &idTextura_verde);
	glBindTexture(GL_TEXTURE_2D, idTextura_verde);

	gluBuild2DMipmaps(GL_TEXTURE_2D,
		Textura_verde.bytes_per_pixel, Textura_verde.width,
		Textura_verde.height, GL_RGB, GL_UNSIGNED_BYTE,
		Textura_verde.pixel_data);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// En caso de no querer repetir las texturas, comentar estas
	// dos líneas
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	glEnable(GL_TEXTURE_2D);

	//cargaa textura rosa
	glGenTextures(1, &idTextura_rosa);
	glBindTexture(GL_TEXTURE_2D, idTextura_rosa);

	gluBuild2DMipmaps(GL_TEXTURE_2D,
		Textura_rosa.bytes_per_pixel, Textura_rosa.width,
		Textura_rosa.height, GL_RGB, GL_UNSIGNED_BYTE,
		Textura_rosa.pixel_data);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// En caso de no querer repetir las texturas, comentar estas
	// dos líneas
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	glEnable(GL_TEXTURE_2D);

	//cargaa textura rojo
	glGenTextures(1, &idTextura_rojo);
	glBindTexture(GL_TEXTURE_2D, idTextura_rojo);

	gluBuild2DMipmaps(GL_TEXTURE_2D,
		Textura_rojo.bytes_per_pixel, Textura_rojo.width,
		Textura_rojo.height, GL_RGB, GL_UNSIGNED_BYTE,
		Textura_rojo.pixel_data);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// En caso de no querer repetir las texturas, comentar estas
	// dos líneas
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	glEnable(GL_TEXTURE_2D);

	//cargaa textura morado
	glGenTextures(1, &idTextura_morado);
	glBindTexture(GL_TEXTURE_2D, idTextura_morado);

	gluBuild2DMipmaps(GL_TEXTURE_2D,
		Textura_morado.bytes_per_pixel, Textura_morado.width,
		Textura_morado.height, GL_RGB, GL_UNSIGNED_BYTE,
		Textura_morado.pixel_data);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// En caso de no querer repetir las texturas, comentar estas
	// dos líneas
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	glEnable(GL_TEXTURE_2D);

	//cargaa textura madero
	glGenTextures(1, &idTextura_madero);
	glBindTexture(GL_TEXTURE_2D, idTextura_madero);

	gluBuild2DMipmaps(GL_TEXTURE_2D,
		Textura_madero.bytes_per_pixel, Textura_madero.width,
		Textura_madero.height, GL_RGB, GL_UNSIGNED_BYTE,
		Textura_madero.pixel_data);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// En caso de no querer repetir las texturas, comentar estas
	// dos líneas
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	glEnable(GL_TEXTURE_2D);

	//cargaa textura lad
	glGenTextures(1, &idTextura_lad);
	glBindTexture(GL_TEXTURE_2D, idTextura_lad);

	gluBuild2DMipmaps(GL_TEXTURE_2D,
		Textura_lad.bytes_per_pixel, Textura_lad.width,
		Textura_lad.height, GL_RGB, GL_UNSIGNED_BYTE,
		Textura_lad.pixel_data);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// En caso de no querer repetir las texturas, comentar estas
	// dos líneas
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	glEnable(GL_TEXTURE_2D);

	//cargaa textura azul
	glGenTextures(1, &idTextura_azul);
	glBindTexture(GL_TEXTURE_2D, idTextura_azul);

	gluBuild2DMipmaps(GL_TEXTURE_2D,
		Textura_azul.bytes_per_pixel, Textura_azul.width,
		Textura_azul.height, GL_RGB, GL_UNSIGNED_BYTE,
		Textura_azul.pixel_data);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// En caso de no querer repetir las texturas, comentar estas
	// dos líneas
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	glEnable(GL_TEXTURE_2D);

	//cargaa textura azul marino
	glGenTextures(1, &idTextura_azulm);
	glBindTexture(GL_TEXTURE_2D, idTextura_azulm);

	gluBuild2DMipmaps(GL_TEXTURE_2D,
		Textura_azulm.bytes_per_pixel, Textura_azulm.width,
		Textura_azulm.height, GL_RGB, GL_UNSIGNED_BYTE,
		Textura_azulm.pixel_data);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// En caso de no querer repetir las texturas, comentar estas
	// dos líneas
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	glEnable(GL_TEXTURE_2D);

	//cargaa textura amarillo
	glGenTextures(1, &idTextura_amarillo);
	glBindTexture(GL_TEXTURE_2D, idTextura_amarillo);

	gluBuild2DMipmaps(GL_TEXTURE_2D,
		Textura_amarillo.bytes_per_pixel, Textura_amarillo.width,
		Textura_amarillo.height, GL_RGB, GL_UNSIGNED_BYTE,
		Textura_amarillo.pixel_data);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// En caso de no querer repetir las texturas, comentar estas
	// dos líneas
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	glEnable(GL_TEXTURE_2D);

	//cargaa textura tubo
	glGenTextures(1, &idTextura_tubo);
	glBindTexture(GL_TEXTURE_2D, idTextura_tubo);

	gluBuild2DMipmaps(GL_TEXTURE_2D,
		Textura_tubo.bytes_per_pixel, Textura_tubo.width,
		Textura_tubo.height, GL_RGB, GL_UNSIGNED_BYTE,
		Textura_tubo.pixel_data);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// En caso de no querer repetir las texturas, comentar estas
	// dos líneas
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	glEnable(GL_TEXTURE_2D);

	//cargaa textura algodon
	glGenTextures(1, &idTextura_algodon);
	glBindTexture(GL_TEXTURE_2D, idTextura_algodon);

	gluBuild2DMipmaps(GL_TEXTURE_2D,
		Textura_algodon.bytes_per_pixel, Textura_algodon.width,
		Textura_algodon.height, GL_RGB, GL_UNSIGNED_BYTE,
		Textura_algodon.pixel_data);

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


	objCamera.Position_Camera(0,2.5f,3, 0,2.5f,0, 0, 1, 0);

	if (!engine)
	{
		printf("\n No pude crear el motor de audio :(");
		exit(0); //termina ejecución justo aquí
	}

	//reproduce con el 20% del sonido
	audioFondo->setDefaultVolume(0.2f);

	//reproduce el sonido sin detenerse
	engine->play2D(audioFondo, true);


}

void anima(void) {
	// Calculate the number of frames per one second:
	//dwFrames++;
	dwCurrentTime = GetTickCount(); // Even better to use timeGetTime()
	dwElapsedTime = dwCurrentTime - dwLastUpdateTime;

	if (dwElapsedTime >= 30) {
		giraRotaElic = (giraRotaElic - 1) % 360;
		dwLastUpdateTime = dwCurrentTime;
	}

	if (Activa_Pulpo) {
		if (dwElapsedTime >= 30) {
			giraRotaTorso = (giraRotaTorso - 3) % 360;
			giraRotaP1 = (giraRotaP1 - 1) % 360;
			dwLastUpdateTime = dwCurrentTime;
		}
	}

	if (Activa_Rueda) {
		if (dwElapsedTime >= 30) {
			giraRotaEje = (giraRotaEje - 5) % 360;
			giraRotaBarra = (giraRotaBarra + 5) % 360;
			dwLastUpdateTime = dwCurrentTime;
		}
	}

	if (Activa_sillas) {
		if (dwElapsedTime >= 30) {
			giraRotaCono = (giraRotaCono + 5) % 360;
			if (avanza) {
				movKit += 0.4;
				if (movKit > 17)
					avanza = false;
			}
			else {
				movKit -= 0.4;
				if (movKit < 0)
					avanza = true;
			}
			dwLastUpdateTime = dwCurrentTime;
		}
		
	}

	if (Activa_Canoa) {
		if (dwElapsedTime >= 30) {
			giraRotaCanoa = (giraRotaCanoa + 1) % 360;
			
			dwLastUpdateTime = dwCurrentTime;
		}
	}

	glutPostRedisplay();
}

void ciudad(void){
	glPushMatrix(); //Campo
					//glTranslatef(23.5,0.0,0.0);
					//el campo mide 100 x 64 pero usaré la mitad de tamaño
					//agrego 4 más por el pasto fuera del campo
	glScalef(240, 0.1, 240);
	glDisable(GL_LIGHTING);
	figSkybox.prisma2(Textura_campo.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();
}

void dibuja_arbol(GLfloat copa, GLfloat alto, GLuint textura){

	glDisable(GL_LIGHTING);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1);
	glBindTexture(GL_TEXTURE_2D, textura);
		glPushMatrix();
		glTranslatef(0.0, 14.75, 0.0);
		glScalef(3.0, 5.0, 3.0);
			for (GLbyte i = 0; i < 4; i++) {
				glRotatef(45 * i, 0, 1, 0);
				figSkybox.plano(copa, alto, textura);
			}
		glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_ALPHA_TEST);
}

void puerta_madera(GLfloat largo, GLfloat alto, GLfloat profundidad) {
	glPushMatrix();
	glScalef(largo, alto, profundidad);
	figSkybox.prisma_4_text(Textura_puerta_madera.GLindex, Textura_puerta_madera.GLindex, Textura_puerta_madera_lateral.GLindex, Textura_puerta_madera_lateral.GLindex, Textura_puerta_madera_lateral.GLindex, Textura_puerta_madera_lateral.GLindex);
	glPopMatrix();
}

void Pulpo() {
	//dibujar cuerpo
	//dibujar base
	glPushMatrix();
	glTranslatef(0.0f, -2.5f, 0.0f);
	figSkybox.cilindro(0.75, 1.5, 50, idTextura_piel);
	glPopMatrix();
		
	glPushMatrix();
		glTranslatef(0.0f, -2.5f, 0.0f);
		glScalef(2, 0.5, 2);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();
		
	glPushMatrix();
		glTranslatef(0.0f, -3.0f, 0.0f);
		glScalef(3, 0.5, 3);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(0.0f, -3.5f, 0.0f);
		glScalef(4, 0.5, 4);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();
	

	//dibujar bola inferior
	glPushMatrix();
	glTranslatef(0.0f, 0.5f, 0.0f);
	glRotatef(giraRotaTorso, 0.0, 1.0, 0.0); //el torso jira sobre su propio eje
	figSkybox.esfera(2.0, 50, 50, idTextura_piel);

		//tentaculo derecho

		glPushMatrix();
			glTranslatef(1.75f, 0.0f, 0.0f);
			figSkybox.esfera(0.5, 50, 50, idTextura_bola);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(1.5f, -0.5f, 0.0f);
			glRotatef(240.0f, 0.0, 0.0, 1.0);
			figSkybox.cilindro(0.75, 1.0, 50, idTextura_piel);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0f, -0.5f, 0.0f);
			glTranslatef(4.5f, -0.5f, 0.0f);
			glRotatef(90.0f, 0.0, 0.0, 1.0);
			figSkybox.cilindro(0.70, 2.0, 50, idTextura_piel);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0f, -0.5f, 0.0f);
			glTranslatef(2.5f, -0.5f, 0.0f);
			figSkybox.esfera(0.75, 50, 50, idTextura_bola);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0f, -0.5f, 0.0f);
			glTranslatef(4.5f, -0.5f, 0.0f);
			figSkybox.esfera(0.75, 50, 50, idTextura_bola);
			glPushMatrix();
				glTranslatef(0.0f, -0.1f, 0.0f);
				glRotatef(315.0f, 0.0, 0.0, 1.0);
				figSkybox.cilindro(0.60, 1.0, 50, idTextura_piel);
			glPopMatrix();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0f, -0.5f, 0.0f);
			glTranslatef(5.0f, 0.5f, 0.0f);
			glRotatef(giraRotaP1, 1.0, 0.0, 0.0); //el asiento jira sobre su propio eje
			figSkybox.esfera(1.0, 50, 50, idTextura_P1);
		glPopMatrix();

		
		//tentaculo atras derecho

		glPushMatrix();
			glTranslatef(1.0f, 0.0f, -1.5f);
			figSkybox.esfera(0.5, 50, 50, idTextura_bola);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(1.0f, -1.0f, -2.0f);
			glRotatef(330.0f, 0.0, 1.0, 0.0);
			glRotatef(55.0f, 1.0, 0.0, 0.0);
			figSkybox.cilindro(0.75, 1.0, 50, idTextura_piel);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0f, -0.5f, 0.0f);
			glTranslatef(1.0f, -0.60f, -2.2f);
			figSkybox.esfera(0.80, 50, 50, idTextura_bola);
			glPushMatrix();
				glTranslatef(1.0f, -0.1f, -2.0f);
				glRotatef(330.0f, 0.0, 1.0, 0.0);
				glRotatef(90.0f, 1.0, 0.0, 0.0);
				figSkybox.cilindro(0.70, 2.0, 50, idTextura_piel);
			glPopMatrix();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0f, -0.5f, 0.0f);
		glTranslatef(1.9f, -0.70f, -4.0f);
		figSkybox.esfera(0.75, 50, 50, idTextura_bola);
			glPushMatrix();
				glTranslatef(0.0f, 0.1f, 0.0f);
				glRotatef(330.0f, 0.0, 1.0, 0.0);
				glRotatef(315.0f, 1.0, 0.0, 0.0);
				figSkybox.cilindro(0.60, 1.0, 50, idTextura_piel);
			glPopMatrix();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0f, -0.5f, 0.0f);
			glTranslatef(2.5f, 0.70f, -5.0f);
			glRotatef(giraRotaP1, 1.0, 0.0, 0.0); //el asiento jira sobre su propio eje
			figSkybox.esfera(1.0, 50, 50, idTextura_P2);
		glPopMatrix();

		//tentaculo atras izquierdo

		glPushMatrix();
			glTranslatef(-1.0f, 0.0f, -1.5f);
			figSkybox.esfera(0.5, 50, 50, idTextura_bola);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-1.0f, -1.0f, -2.0f);
			glRotatef(30.0f, 0.0, 1.0, 0.0);
			glRotatef(55.0f, 1.0, 0.0, 0.0);
			figSkybox.cilindro(0.75, 1.0, 50, idTextura_piel);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0f, -0.5f, 0.0f);
			glTranslatef(-1.0f, -0.60f, -2.2f);
			figSkybox.esfera(0.80, 50, 50, idTextura_bola);
			glPushMatrix();
				glTranslatef(-1.0f, -0.1f, -2.0f);
				glRotatef(30.0f, 0.0, 1.0, 0.0);
				glRotatef(90.0f, 1.0, 0.0, 0.0);
				figSkybox.cilindro(0.70, 2.0, 50, idTextura_piel);
			glPopMatrix();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0f, -0.5f, 0.0f);
			glTranslatef(-1.9f, -0.70f, -4.0f);
			figSkybox.esfera(0.75, 50, 50, idTextura_bola);
			glPushMatrix();
				glTranslatef(0.0f, 0.1f, 0.0f);
				glRotatef(30.0f, 0.0, 1.0, 0.0);
				glRotatef(315.0f, 1.0, 0.0, 0.0);
				figSkybox.cilindro(0.60, 1.0, 50, idTextura_piel);
			glPopMatrix();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0f, -0.5f, 0.0f);
			glTranslatef(-2.5f, 0.70f, -5.0f);
			glRotatef(giraRotaP1, 1.0, 0.0, 0.0); //el asiento jira sobre su propio eje
			figSkybox.esfera(1.0, 50, 50, idTextura_P3);
		glPopMatrix();

		//tentaculo izquierdo

		glPushMatrix();
			glTranslatef(-1.75f, 0.0f, 0.0f);
			figSkybox.esfera(0.5, 50, 50, idTextura_bola);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-1.5f, -0.5f, 0.0f);
			glRotatef(120.0f, 0.0, 0.0, 1.0);
			figSkybox.cilindro(0.75, 1.0, 50, idTextura_piel);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0f, -0.5f, 0.0f);
			glTranslatef(-2.5f, -0.5f, 0.0f);
			figSkybox.esfera(0.75, 50, 50, idTextura_bola);
			glRotatef(90.0f, 0.0, 0.0, 1.0);
			figSkybox.cilindro(0.70, 2.0, 50, idTextura_piel);
		glPopMatrix();
							
		glPushMatrix();
		glTranslatef(0.0f, -0.5f, 0.0f);
			glTranslatef(-4.5f, -0.5f, 0.0f);
			figSkybox.esfera(0.75, 50, 50, idTextura_bola);
			glPushMatrix();
				glTranslatef(0.0f, 0.1f, 0.0f);
				glRotatef(45.0f, 0.0, 0.0, 1.0);
				figSkybox.cilindro(0.60, 1.0, 50, idTextura_piel);
			glPopMatrix();
		glPopMatrix();
							
		glPushMatrix();
		glTranslatef(0.0f, -0.5f, 0.0f);
			glTranslatef(-5.3f, 0.85f, 0.0f);
			glRotatef(giraRotaP1, 1.0, 0.0, 0.0); //el asiento jira sobre su propio eje
			figSkybox.esfera(1.0, 50, 50, idTextura_P4);
		glPopMatrix();

		//tentaculo enfrente izquierdo

		glPushMatrix();
			glTranslatef(-0.95f, 0.0f, 1.5f);
			figSkybox.esfera(0.5, 50, 50, idTextura_bola);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-0.7f, -0.5f, 1.5f);
			glRotatef(330.0f, 0.0, 1.0, 0.0);
			glRotatef(120.0f, 1.0, 0.0, 0.0);
			figSkybox.cilindro(0.75, 1.0, 50, idTextura_piel);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0f, -0.5f, 0.0f);
			glTranslatef(1.2f, -0.5f, 2.2f);
			figSkybox.esfera(0.80, 50, 50, idTextura_bola);
			glPushMatrix();
				glTranslatef(0.0f, -0.1f, 0.0f);
				glRotatef(30.0f, 0.0, 1.0, 0.0);
				glRotatef(90.0f, 1.0, 0.0, 0.0);
				figSkybox.cilindro(0.70, 2.0, 50, idTextura_piel);
			glPopMatrix();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0f, -0.5f, 0.0f);
			glTranslatef(-2.35f, -0.5f, 4.25f);
			figSkybox.esfera(0.75, 50, 50, idTextura_bola);
			glPushMatrix();
				glTranslatef(0.0f, -0.1f, 0.0f);
				glRotatef(330.0f, 0.0, 1.0, 0.0);
				glRotatef(45.0f, 1.0, 0.0, 0.0);
				figSkybox.cilindro(0.60, 1.0, 50, idTextura_piel);
			glPopMatrix();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0f, -0.5f, 0.0f);
			glTranslatef(-2.50f, 0.5f, 4.7f);
			glRotatef(giraRotaP1, 1.0, 0.0, 0.0); //el asiento jira sobre su propio eje
			figSkybox.esfera(1.0, 50, 50, idTextura_P5);
		glPopMatrix();

		//tentaculo enfrente derecho

		glPushMatrix();
			glTranslatef(0.95f, 0.0f, 1.5f);
			figSkybox.esfera(0.5, 50, 50, idTextura_bola);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.7f, -0.5f, 1.5f);
			glRotatef(30.0f, 0.0, 1.0, 0.0);
			glRotatef(120.0f, 1.0, 0.0, 0.0);
			figSkybox.cilindro(0.75, 1.0, 50, idTextura_piel);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0f, -0.5f, 0.0f);
			glTranslatef(-1.2f, -0.5f, 2.2f);
			figSkybox.esfera(0.80, 50, 50, idTextura_bola);
			glPushMatrix();
				glTranslatef(0.0f, -0.1f, 0.0f);
				glRotatef(330.0f, 0.0, 1.0, 0.0);
				glRotatef(90.0f, 1.0, 0.0, 0.0);
				figSkybox.cilindro(0.70, 2.0, 50, idTextura_piel);
			glPopMatrix();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0f, -0.5f, 0.0f);
			glTranslatef(2.35f, -0.5f, 4.25f);
			figSkybox.esfera(0.75, 50, 50, idTextura_bola);
			glPushMatrix();
				glTranslatef(0.0f, -0.1f, 0.0f);
				glRotatef(30.0f, 0.0, 1.0, 0.0);
				glRotatef(45.0f, 1.0, 0.0, 0.0);
				figSkybox.cilindro(0.60, 1.0, 50, idTextura_piel);
			glPopMatrix();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0f, -0.5f, 0.0f);
			glTranslatef(2.50f, 0.5f, 4.7f);
			glRotatef(giraRotaP1, 1.0, 0.0, 0.0); //el asiento jira sobre su propio eje
			figSkybox.esfera(1.0, 50, 50, idTextura_P6);
		glPopMatrix();

	glPopMatrix();

	//dibujar bola superior
	glPushMatrix();
	glTranslatef(0.0f, 1.5f, 0.0f);
	figSkybox.esfera(2.0, 50, 50, idTextura_piel);
	glPopMatrix();

	//dibujar manchas amarillas
	glPushMatrix();
	glTranslatef(0.0f, 3.25f, 0.0f);
	figSkybox.esfera(0.5, 50, 50, idTextura_bola);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 3.0f, 1.0f);
	figSkybox.esfera(0.5, 50, 50, idTextura_bola);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 3.0f, -1.0f);
	figSkybox.esfera(0.5, 50, 50, idTextura_bola);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 2.25f, -1.5f);
	figSkybox.esfera(0.5, 50, 50, idTextura_bola);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 1.5f, -1.7f);
	figSkybox.esfera(0.5, 50, 50, idTextura_bola);
	glPopMatrix();


	//dibujar cara
	//nariz
	glPushMatrix();
	glTranslatef(0.0f, 2.0f, 1.5f); 
	glRotatef(90.0f, 1.0, 0.0, 0.0);
	figSkybox.cono(1.5, 0.75, 10, idTextura_piel);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0.0f, 2.0f, 2.0f); 
	glRotatef(90.0f, 1.0, 0.0, 0.0);
	figSkybox.cilindro(0.5, 1.0, 50, idTextura_piel);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 2.0f, 2.75f);
	figSkybox.esfera(0.3, 50, 50, idTextura_negro);
	glPopMatrix();

	//ojo izquierdo
	glPushMatrix();
	glTranslatef(-0.5f, 2.25f, 1.0f);
	figSkybox.esfera(0.75, 50, 50, idTextura_blanco);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.5f, 2.5f, 1.5f);
	figSkybox.esfera(0.25, 50, 50, idTextura_negro);
	glPopMatrix();

	//ojo derecho
	glPushMatrix();
	glTranslatef(0.5f, 2.25f, 1.0f);
	figSkybox.esfera(0.75, 50, 50, idTextura_blanco);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.5f, 2.5f, 1.5f);
	figSkybox.esfera(0.25, 50, 50, idTextura_negro);
	glPopMatrix();
}

void Rueda_Foirtuna() {
	//dibujar base
	glPushMatrix();
		glTranslatef(0.0f, -2.5f, 0.0f);
		glScalef(2, 0.5, 2);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.0f, -3.0f, 0.0f);
		glScalef(3, 0.5, 3);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.0f, -3.5f, 0.0f);
		glScalef(4, 0.5, 4);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();
	
	//dibujar soportes
	glPushMatrix();
		glTranslatef(6.5f, -5.0f, 2.75f);
		glRotatef(35.0f, 0.0, 0.0, 1.0);
		figSkybox.cilindro(0.25, 12, 50, idTextura_metal);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-6.5f, -5.0f, 2.75f);
		glRotatef(325.0f, 0.0, 0.0, 1.0);
		figSkybox.cilindro(0.25, 12, 50, idTextura_metal);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(6.5f, -5.0f, -2.75f);
		glRotatef(35.0f, 0.0, 0.0, 1.0);
		figSkybox.cilindro(0.25, 12, 50, idTextura_metal);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-6.5f, -5.0f, -2.75f);
		glRotatef(325.0f, 0.0, 0.0, 1.0);
		figSkybox.cilindro(0.25, 12, 50, idTextura_metal);
	glPopMatrix();

	//dibujar barilla central
	glPushMatrix();
	glTranslatef(0.0f, 5.0f, -3.0f);
		glRotatef(90.0f, 1.0, 0.0, 0.0);
		glRotatef(giraRotaEje, 0.0, 1.0, 0.0); //la barilla jira sobre su propio eje
		figSkybox.cilindro(0.25, 6, 50, idTextura_metal);
		//primer exagono
		glPushMatrix();
			glTranslatef(0.0f, 1.0f, 0.0f);
			glRotatef(-90.0f, 1.0, 0.0, 0.0);
			glRotatef(60.0f, 0.0, 0.0, 1.0);
			figSkybox.cilindro(0.25, 4, 50, idTextura_metal);
			glPushMatrix();
				glTranslatef(0.0f, 4.0f, 0.0f);
				figSkybox.esfera(0.5, 50, 50, idTextura_metal);
				glPushMatrix();
					glRotatef(120.0f, 0.0, 0.0, 1.0);
					figSkybox.cilindro(0.25, 4, 50, idTextura_metal);
				glPopMatrix();
				glPushMatrix();
					glRotatef(90.0f, 1.0, 0.0, 0.0);
					glRotatef(giraRotaBarra, 0.0, 1.0, 0.0); //la barra jira sobre su propio eje (movimiento acorde al jiro del eje)
					figSkybox.cilindro(0.25, 4, 50, idTextura_metal);
					glPushMatrix();
						glTranslatef(0.0f, 2.0f, 0.0f);
						glRotatef(-90.0f, 1.0, 0.0, 0.0);
						figSkybox.cilindro(0.25, 1, 50, idTextura_metal);
						glPushMatrix();
							glTranslatef(0.0f, 2.0f, 0.0f);
							glRotatef(giraRotaP1, 1.0, 0.0, 0.0); //el asiento jira sobre su propio eje
							figSkybox.esfera(1.0, 50, 50, idTextura_P1);
						glPopMatrix();
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.0f, 1.0f, 0.0f);
			glRotatef(-90.0f, 1.0, 0.0, 0.0);
			glRotatef(120.0f, 0.0, 0.0, 1.0);
			figSkybox.cilindro(0.25, 4, 50, idTextura_metal);
			glPushMatrix();
				glTranslatef(0.0f, 4.0f, 0.0f);
				figSkybox.esfera(0.5, 50, 50, idTextura_metal);
				glPushMatrix();
					glRotatef(120.0f, 0.0, 0.0, 1.0);
					figSkybox.cilindro(0.25, 4, 50, idTextura_metal);
				glPopMatrix();
				glPushMatrix();
					glRotatef(90.0f, 1.0, 0.0, 0.0);
					glRotatef(giraRotaBarra, 0.0, 1.0, 0.0); //la barra jira sobre su propio eje (movimiento acorde al jiro del eje)
					figSkybox.cilindro(0.25, 4, 50, idTextura_metal);
					glPushMatrix();
						glTranslatef(0.0f, 2.0f, 0.0f);
						glRotatef(-90.0f, 1.0, 0.0, 0.0);
						figSkybox.cilindro(0.25, 1, 50, idTextura_metal);
						glPushMatrix();
							glTranslatef(0.0f, 2.0f, 0.0f);
							glRotatef(giraRotaP1, 1.0, 0.0, 0.0); //el asiento jira sobre su propio eje
							figSkybox.esfera(1.0, 50, 50, idTextura_P1);
						glPopMatrix();
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.0f, 1.0f, 0.0f);
			glRotatef(-90.0f, 1.0, 0.0, 0.0);
			glRotatef(180.0f, 0.0, 0.0, 1.0);
			figSkybox.cilindro(0.25, 4, 50, idTextura_metal);
			glPushMatrix();
				glTranslatef(0.0f, 4.0f, 0.0f);
				figSkybox.esfera(0.5, 50, 50, idTextura_metal);
				glPushMatrix();
					glRotatef(120.0f, 0.0, 0.0, 1.0);
					figSkybox.cilindro(0.25, 4, 50, idTextura_metal);
				glPopMatrix();
				glPushMatrix();
					glRotatef(90.0f, 1.0, 0.0, 0.0);
					glRotatef(giraRotaBarra, 0.0, 1.0, 0.0); //la barra jira sobre su propio eje (movimiento acorde al jiro del eje)
					figSkybox.cilindro(0.25, 4, 50, idTextura_metal);
					glPushMatrix();
						glTranslatef(0.0f, 2.0f, 0.0f);
						glRotatef(-90.0f, 1.0, 0.0, 0.0);
						figSkybox.cilindro(0.25, 1, 50, idTextura_metal);
						glPushMatrix();
							glTranslatef(0.0f, 2.0f, 0.0f);
							glRotatef(giraRotaP1, 1.0, 0.0, 0.0); //el asiento jira sobre su propio eje
							figSkybox.esfera(1.0, 50, 50, idTextura_P1);
						glPopMatrix();
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.0f, 1.0f, 0.0f);
			glRotatef(-90.0f, 1.0, 0.0, 0.0);
			glRotatef(240.0f, 0.0, 0.0, 1.0);
			figSkybox.cilindro(0.25, 4, 50, idTextura_metal);
			glPushMatrix();
				glTranslatef(0.0f, 4.0f, 0.0f);
				figSkybox.esfera(0.5, 50, 50, idTextura_metal);
				glPushMatrix();
					glRotatef(120.0f, 0.0, 0.0, 1.0);
					figSkybox.cilindro(0.25, 4, 50, idTextura_metal);
				glPopMatrix();
				glPushMatrix();
					glRotatef(90.0f, 1.0, 0.0, 0.0);
					glRotatef(giraRotaBarra, 0.0, 1.0, 0.0); //la barra jira sobre su propio eje (movimiento acorde al jiro del eje)
					figSkybox.cilindro(0.25, 4, 50, idTextura_metal);
					glPushMatrix();
						glTranslatef(0.0f, 2.0f, 0.0f);
						glRotatef(-90.0f, 1.0, 0.0, 0.0);
						figSkybox.cilindro(0.25, 1, 50, idTextura_metal);
						glPushMatrix();
							glTranslatef(0.0f, 2.0f, 0.0f);
							glRotatef(giraRotaP1, 1.0, 0.0, 0.0); //el asiento jira sobre su propio eje
							figSkybox.esfera(1.0, 50, 50, idTextura_P1);
						glPopMatrix();
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.0f, 1.0f, 0.0f);
			glRotatef(-90.0f, 1.0, 0.0, 0.0);
			glRotatef(300.0f, 0.0, 0.0, 1.0);
			figSkybox.cilindro(0.25, 4, 50, idTextura_metal);
			glPushMatrix();
				glTranslatef(0.0f, 4.0f, 0.0f);
				figSkybox.esfera(0.5, 50, 50, idTextura_metal);
				glPushMatrix();
					glRotatef(120.0f, 0.0, 0.0, 1.0);
					figSkybox.cilindro(0.25, 4, 50, idTextura_metal);
				glPopMatrix();
				glPushMatrix();
					glRotatef(90.0f, 1.0, 0.0, 0.0);
					glRotatef(giraRotaBarra, 0.0, 1.0, 0.0); //la barra jira sobre su propio eje (movimiento acorde al jiro del eje)
					figSkybox.cilindro(0.25, 4, 50, idTextura_metal);
					glPushMatrix();
						glTranslatef(0.0f, 2.0f, 0.0f);
						glRotatef(-90.0f, 1.0, 0.0, 0.0);
						figSkybox.cilindro(0.25, 1, 50, idTextura_metal);
						glPushMatrix();
							glTranslatef(0.0f, 2.0f, 0.0f);
							glRotatef(giraRotaP1, 1.0, 0.0, 0.0); //el asiento jira sobre su propio eje
							figSkybox.esfera(1.0, 50, 50, idTextura_P1);
						glPopMatrix();
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.0f, 1.0f, 0.0f);
			glRotatef(-90.0f, 1.0, 0.0, 0.0);
			glRotatef(360.0f, 0.0, 0.0, 1.0);
			figSkybox.cilindro(0.25, 4, 50, idTextura_metal);
			glPushMatrix();
				glTranslatef(0.0f, 4.0f, 0.0f);
				figSkybox.esfera(0.5, 50, 50, idTextura_metal);
				glPushMatrix();
					glRotatef(120.0f, 0.0, 0.0, 1.0);
					figSkybox.cilindro(0.25, 4, 50, idTextura_metal);
				glPopMatrix();
				glPushMatrix();
					glRotatef(90.0f, 1.0, 0.0, 0.0);
					glRotatef(giraRotaBarra, 0.0, 1.0, 0.0); //la barra jira sobre su propio eje (movimiento acorde al jiro del eje)
					figSkybox.cilindro(0.25, 4, 50, idTextura_metal);
					glPushMatrix();
						glTranslatef(0.0f, 2.0f, 0.0f);
						glRotatef(-90.0f, 1.0, 0.0, 0.0);
						figSkybox.cilindro(0.25, 1, 50, idTextura_metal);
						glPushMatrix();
							glTranslatef(0.0f, 2.0f, 0.0f);
							glRotatef(giraRotaP1, 1.0, 0.0, 0.0); //el asiento jira sobre su propio eje
							figSkybox.esfera(1.0, 50, 50, idTextura_P1);
						glPopMatrix();
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
		//segundo exagono
		glPushMatrix();
			glTranslatef(0.0f, 5.0f, 0.0f);
			glRotatef(-90.0f, 1.0, 0.0, 0.0);
			glRotatef(60.0f, 0.0, 0.0, 1.0);
			figSkybox.cilindro(0.25, 4, 50, idTextura_metal);
			glPushMatrix();
				glTranslatef(0.0f, 4.0f, 0.0f);
				figSkybox.esfera(0.5, 50, 50, idTextura_metal);
				glPushMatrix();
					glRotatef(120.0f, 0.0, 0.0, 1.0);
					figSkybox.cilindro(0.25, 4, 50, idTextura_metal);
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.0f, 5.0f, 0.0f);
			glRotatef(-90.0f, 1.0, 0.0, 0.0);
			glRotatef(120.0f, 0.0, 0.0, 1.0);
			figSkybox.cilindro(0.25, 4, 50, idTextura_metal);
			glPushMatrix();
				glTranslatef(0.0f, 4.0f, 0.0f);
				figSkybox.esfera(0.5, 50, 50, idTextura_metal);
				glPushMatrix();
					glRotatef(120.0f, 0.0, 0.0, 1.0);
					figSkybox.cilindro(0.25, 4, 50, idTextura_metal);
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.0f, 5.0f, 0.0f);
			glRotatef(-90.0f, 1.0, 0.0, 0.0);
			glRotatef(180.0f, 0.0, 0.0, 1.0);
			figSkybox.cilindro(0.25, 4, 50, idTextura_metal);
			glPushMatrix();
				glTranslatef(0.0f, 4.0f, 0.0f);
				figSkybox.esfera(0.5, 50, 50, idTextura_metal);
				glPushMatrix();
					glRotatef(120.0f, 0.0, 0.0, 1.0);
					figSkybox.cilindro(0.25, 4, 50, idTextura_metal);
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.0f, 5.0f, 0.0f);
			glRotatef(-90.0f, 1.0, 0.0, 0.0);
			glRotatef(240.0f, 0.0, 0.0, 1.0);
			figSkybox.cilindro(0.25, 4, 50, idTextura_metal);
			glPushMatrix();
				glTranslatef(0.0f, 4.0f, 0.0f);
				figSkybox.esfera(0.5, 50, 50, idTextura_metal);
				glPushMatrix();
					glRotatef(120.0f, 0.0, 0.0, 1.0);
					figSkybox.cilindro(0.25, 4, 50, idTextura_metal);
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.0f, 5.0f, 0.0f);
			glRotatef(-90.0f, 1.0, 0.0, 0.0);
			glRotatef(300.0f, 0.0, 0.0, 1.0);
			figSkybox.cilindro(0.25, 4, 50, idTextura_metal);
			glPushMatrix();
				glTranslatef(0.0f, 4.0f, 0.0f);
				figSkybox.esfera(0.5, 50, 50, idTextura_metal);
				glPushMatrix();
					glRotatef(120.0f, 0.0, 0.0, 1.0);
					figSkybox.cilindro(0.25, 4, 50, idTextura_metal);
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.0f, 5.0f, 0.0f);
			glRotatef(-90.0f, 1.0, 0.0, 0.0);
			glRotatef(360.0f, 0.0, 0.0, 1.0);
			figSkybox.cilindro(0.25, 4, 50, idTextura_metal);
			glPushMatrix();
				glTranslatef(0.0f, 4.0f, 0.0f);
				figSkybox.esfera(0.5, 50, 50, idTextura_metal);
				glPushMatrix();
					glRotatef(120.0f, 0.0, 0.0, 1.0);
					figSkybox.cilindro(0.25, 4, 50, idTextura_metal);
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}

void cillas_voladoras() {
	//dibujar base	
	glPushMatrix();
		glTranslatef(0.0f, 1.0f, 0.0f);
		glScalef(2, 0.5, 2);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();
		
	glPushMatrix();
		glTranslatef(0.0f, 0.75f, 0.0f);
		glScalef(3, 0.5, 3);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(0.0f, 0.5f, 0.0f);
		glScalef(4, 0.5, 4);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0f, 1.0f, 0.0f);
		figSkybox.cilindro(0.75, 22.0, 50, idTextura_blanco);
	glPopMatrix();

	//Dibujar Aguila 
	glPushMatrix();
		glTranslatef(0.0, 24.0, 1.0);
		glScalef(10.0, 10.0, 10.0);
		Aguila.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	//Dibujar base de Aguila
	glPushMatrix();
		glTranslatef(0.0f, 23.0f, 0.0f);
		glScalef(1.75, 1.0, 1.75);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	//dibujar aros
	glPushMatrix();
		glTranslatef(0.0f, 6.0f, 0.0f);
		figSkybox.torus(1.25, 0.75, 50, 50);
		glRotatef(giraRotaCono, 0.0, 1.0, 0.0);
		glPushMatrix();
		glTranslatef(0.0, movKit, 0.0);

		glPushMatrix();
			glTranslatef(0.0f, -1.0f, 0.0f);
			figSkybox.torus(2.25, 1.75, 50, 50);
			//dibujar tubo
			glPushMatrix();
				glTranslatef(-3.75f, -2.0f, 0.0f);
				glRotatef(315.0, 0.0, 0.0, 1.0);
				figSkybox.cilindro(0.25, 4.5, 50, idTextura_blanco);
				glPushMatrix();
					glTranslatef(0.0f, 0.0f, 0.0f);
					figSkybox.esfera(0.5, 50, 50, idTextura_P1);

					glPushMatrix();
						glTranslatef(0.5f, -0.5f, 0.0f);
						glRotatef(45.0, 0.0, 0.0, 1.0);
						figSkybox.cilindro(0.25, 0.5, 50, idTextura_lad);
						glPushMatrix();
							glTranslatef(0.0f, -0.5f, 0.0f);
							glScalef(0.15, 1.75, 1.0);
							figSkybox.prisma2(idTextura_piso, idTextura_piso);

							glPushMatrix();
								glTranslatef(0.0f, 0.0f, -0.5f);
								glRotatef(90.0, 0.0, 0.0, 1.0);
								figSkybox.cilindro(0.1, 4.0, 50, idTextura_lad);
							glPopMatrix();

							glPushMatrix();
								glTranslatef(0.0f, 0.0f, 0.5f);
								glRotatef(90.0, 0.0, 0.0, 1.0);
								figSkybox.cilindro(0.1, 4.0, 50, idTextura_lad);
							glPopMatrix();

							glPushMatrix();
								glTranslatef(-4.0f, 0.0f, -0.5f);
								glRotatef(90.0, 1.0, 0.0, 0.0);
								figSkybox.cilindro(0.1, 1.0, 50, idTextura_lad);
							glPopMatrix();

							glPushMatrix();
								glTranslatef(-2.0f, -0.5f, 0.0f);
								glScalef(6.6, 0.085, 1.0);
								figSkybox.prisma2(idTextura_piso, idTextura_piso);
							glPopMatrix();

						glPopMatrix();
					glPopMatrix();

				glPopMatrix();
			glPopMatrix();

			//dibujar tubo
			glPushMatrix();
				glTranslatef(3.75f, -2.0f, 0.0f);
				glRotatef(45.0, 0.0, 0.0, 1.0);
				figSkybox.cilindro(0.25, 4.5, 50, idTextura_blanco);
				glPushMatrix();
					glTranslatef(0.0f, 0.0f, 0.0f);
					figSkybox.esfera(0.5, 50, 50, idTextura_P2);

					glPushMatrix();
						glTranslatef(-0.5f, -0.5f, 0.0f);
						glRotatef(315.0, 0.0, 0.0, 1.0);
						figSkybox.cilindro(0.25, 0.5, 50, idTextura_lad);
						glRotatef(180.0, 0.0, 1.0, 0.0);
						glPushMatrix();
							glTranslatef(0.0f, -0.5f, 0.0f);
							glScalef(0.15, 1.75, 1.0);
							figSkybox.prisma2(idTextura_piso, idTextura_piso);

							glPushMatrix();
								glTranslatef(0.0f, 0.0f, -0.5f);
								glRotatef(90.0, 0.0, 0.0, 1.0);
								figSkybox.cilindro(0.1, 4.0, 50, idTextura_lad);
							glPopMatrix();

							glPushMatrix();
								glTranslatef(0.0f, 0.0f, 0.5f);
								glRotatef(90.0, 0.0, 0.0, 1.0);
								figSkybox.cilindro(0.1, 4.0, 50, idTextura_lad);
							glPopMatrix();

							glPushMatrix();
								glTranslatef(-4.0f, 0.0f, -0.5f);
								glRotatef(90.0, 1.0, 0.0, 0.0);
								figSkybox.cilindro(0.1, 1.0, 50, idTextura_lad);
							glPopMatrix();

							glPushMatrix();
								glTranslatef(-2.0f, -0.5f, 0.0f);
								glScalef(6.6, 0.085, 1.0);
								figSkybox.prisma2(idTextura_piso, idTextura_piso);
							glPopMatrix();

						glPopMatrix();
					glPopMatrix();

				glPopMatrix();
			glPopMatrix();

			//dibujar tubo
			glPushMatrix();
				glTranslatef(0.0f, -2.0f, -3.75f);
				glRotatef(45.0, 1.0, 0.0, 0.0);
				figSkybox.cilindro(0.25, 4.5, 50, idTextura_blanco);
				glPushMatrix();
					glTranslatef(0.0f, 0.0f, 0.0f);
					figSkybox.esfera(0.5, 50, 50, idTextura_P3);

					glPushMatrix();
						glTranslatef(0.0f, -0.5f, 0.5f);
						glRotatef(-45.0, 1.0, 0.0, 0.0);
						figSkybox.cilindro(0.25, 0.5, 50, idTextura_lad);
						glRotatef(270.0, 0.0, 1.0, 0.0);
						glPushMatrix();
							glTranslatef(0.0f, -0.5f, 0.0f);
							glScalef(0.15, 1.75, 1.0);
							figSkybox.prisma2(idTextura_piso, idTextura_piso);

							glPushMatrix();
								glTranslatef(0.0f, 0.0f, -0.5f);
								glRotatef(90.0, 0.0, 0.0, 1.0);
								figSkybox.cilindro(0.1, 4.0, 50, idTextura_lad);
							glPopMatrix();

							glPushMatrix();
								glTranslatef(0.0f, 0.0f, 0.5f);
								glRotatef(90.0, 0.0, 0.0, 1.0);
								figSkybox.cilindro(0.1, 4.0, 50, idTextura_lad);
							glPopMatrix();

							glPushMatrix();
								glTranslatef(-4.0f, 0.0f, -0.5f);
								glRotatef(90.0, 1.0, 0.0, 0.0);
								figSkybox.cilindro(0.1, 1.0, 50, idTextura_lad);
							glPopMatrix();

							glPushMatrix();
								glTranslatef(-2.0f, -0.5f, 0.0f);
								glScalef(6.6, 0.085, 1.0);
								figSkybox.prisma2(idTextura_piso, idTextura_piso);
							glPopMatrix();

						glPopMatrix();
					glPopMatrix();

				glPopMatrix();
			glPopMatrix();

			//dibujar tubo
			glPushMatrix();
				glTranslatef(0.0f, -2.0f, 3.75f);
				glRotatef(315.0, 1.0, 0.0, 0.0);
				figSkybox.cilindro(0.25, 4.5, 50, idTextura_blanco);
				glPushMatrix();
					glTranslatef(0.0f, 0.0f, 0.0f);
					figSkybox.esfera(0.5, 50, 50, idTextura_P4);

					glPushMatrix();
						glTranslatef(0.0f, -0.5f, -0.5f);
						glRotatef(-315.0, 1.0, 0.0, 0.0);
						figSkybox.cilindro(0.25, 0.5, 50, idTextura_lad);
						glRotatef(90.0, 0.0, 1.0, 0.0);
						glPushMatrix();
							glTranslatef(0.0f, -0.5f, 0.0f);
							glScalef(0.15, 1.75, 1.0);
							figSkybox.prisma2(idTextura_piso, idTextura_piso);

							glPushMatrix();
								glTranslatef(0.0f, 0.0f, -0.5f);
								glRotatef(90.0, 0.0, 0.0, 1.0);
								figSkybox.cilindro(0.1, 4.0, 50, idTextura_lad);
							glPopMatrix();

							glPushMatrix();
								glTranslatef(0.0f, 0.0f, 0.5f);
								glRotatef(90.0, 0.0, 0.0, 1.0);
								figSkybox.cilindro(0.1, 4.0, 50, idTextura_lad);
							glPopMatrix();

							glPushMatrix();
								glTranslatef(-4.0f, 0.0f, -0.5f);
								glRotatef(90.0, 1.0, 0.0, 0.0);
								figSkybox.cilindro(0.1, 1.0, 50, idTextura_lad);
							glPopMatrix();

							glPushMatrix();
								glTranslatef(-2.0f, -0.5f, 0.0f);
								glScalef(6.6, 0.085, 1.0);
								figSkybox.prisma2(idTextura_piso, idTextura_piso);
							glPopMatrix();

						glPopMatrix();
					glPopMatrix();

				glPopMatrix();
			glPopMatrix();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.0f, -2.5f, 0.0f);
			figSkybox.torus(3.75, 3.25, 50, 50);
		glPopMatrix();

		glPopMatrix();
	glPopMatrix();
}

void Canoa() {
	//dibujar base	
	glPushMatrix();
		glTranslatef(0.0f, 1.0f, 0.0f);
		glScalef(2, 0.5, 2);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();
		
	glPushMatrix();
		glTranslatef(0.0f, 0.75f, 0.0f);
		glScalef(3, 0.5, 3);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(0.0f, 0.5f, 0.0f);
		glScalef(4, 0.5, 4);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	//soportes
	glPushMatrix();
		glTranslatef(-1.0f, 0.0f, 2.5f);
		glRotatef(-12.0, 0.0, 0.0, 1.0);
		figSkybox.cilindro(0.15, 5.0, 50, idTextura_blanco);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(1.0f, 0.0f, 2.5f);
		glRotatef(12.0, 0.0, 0.0, 1.0);
		figSkybox.cilindro(0.15, 5.0, 50, idTextura_blanco);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-1.0f, 0.0f, -2.5f);
		glRotatef(-12.0, 0.0, 0.0, 1.0);
		figSkybox.cilindro(0.15, 5.0, 50, idTextura_blanco);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(1.0f, 0.0f, -2.5f);
		glRotatef(12.0, 0.0, 0.0, 1.0);
		figSkybox.cilindro(0.15, 5.0, 50, idTextura_blanco);
	glPopMatrix();

	//barilla central
	glPushMatrix();
		glTranslatef(0.0f, 4.5f, -2.75f);
		glRotatef(90.0, 1.0, 0.0, 0.0);
		glRotatef(giraRotaCanoa, 0.0, 1.0, 0.0);
		figSkybox.cilindro(0.15, 5.5, 50, idTextura_blanco);

		//Soportes internos
		glPushMatrix();
			glRotatef(-90.0, 1.0, 0.0, 0.0);
			glTranslatef(0.0f, 0.0f, 1.0f);
			glRotatef(125.0, 0.0, 0.0, 1.0);
			figSkybox.cilindro(0.15, 2.5, 50, idTextura_blanco);
		glPopMatrix();

		glPushMatrix();
			glRotatef(-90.0, 1.0, 0.0, 0.0);
			glTranslatef(0.0f, 0.0f, 4.0f);
			glRotatef(125.0, 0.0, 0.0, 1.0);
			figSkybox.cilindro(0.15, 2.5, 50, idTextura_blanco);
		glPopMatrix();

		glPushMatrix();
			glRotatef(-90.0, 1.0, 0.0, 0.0);
			glTranslatef(0.0f, 0.0f, 1.0f);
			glRotatef(-125.0, 0.0, 0.0, 1.0);
			figSkybox.cilindro(0.15, 2.5, 50, idTextura_blanco);
		glPopMatrix();

		glPushMatrix();
			glRotatef(-90.0, 1.0, 0.0, 0.0);
			glTranslatef(0.0f, 0.0f, 4.0f);
			glRotatef(-125.0, 0.0, 0.0, 1.0);
			figSkybox.cilindro(0.15, 2.5, 50, idTextura_blanco);
		glPopMatrix();

		//Cuerpo
		glPushMatrix();
			glRotatef(-90.0, 1.0, 0.0, 0.0);
			glTranslatef(0.0f, -2.0f, 2.5f);
			glScalef(2.0, 1.0, 3.5);
			figSkybox.prisma2(idTextura_verde, idTextura_verde);
		glPopMatrix();

		glPushMatrix();
			glRotatef(-90.0, 1.0, 0.0, 0.0);
			glTranslatef(1.0f, -2.0f, 2.5f);
			glRotatef(-55.0, 0.0, 0.0, 1.0);
			glScalef(0.75, 2.85, 3.5);
			figSkybox.prisma2(idTextura_verde, idTextura_verde);
		glPopMatrix();

		glPushMatrix();
			glRotatef(-90.0, 1.0, 0.0, 0.0);
			glTranslatef(-1.0f, -2.0f, 2.5f);
			glRotatef(55.0, 0.0, 0.0, 1.0);
			glScalef(0.75, 2.85, 3.5);
			figSkybox.prisma2(idTextura_verde, idTextura_verde);
		glPopMatrix();


	glPopMatrix();
}

void Puesto_A () {
	//dibujar estructura
	//abajo
	glPushMatrix();
		glTranslatef(-2.0f, -3.25f, 0.0f);
		glScalef(2, 1.5, 6);
		figSkybox.prisma2(idTextura_tela, idTextura_tela);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0f, -3.25f, 0.0f);
		glScalef(2, 1.5, 6);
		figSkybox.prisma2(idTextura_tela, idTextura_tela);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(2.0f, -3.25f, 0.0f);
		glScalef(2, 1.5, 6);
		figSkybox.prisma2(idTextura_tela, idTextura_tela);
	glPopMatrix();

	//esquinas
	glPushMatrix();
		glTranslatef(2.5f, -2.0f, 2.5f);
		figSkybox.esfera(0.5, 50, 50, idTextura_P1);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(2.5f, -2.0f, -2.5f);
		figSkybox.esfera(0.5, 50, 50, idTextura_P1);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-2.5f, -2.0f, 2.5f);
		figSkybox.esfera(0.5, 50, 50, idTextura_P1);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-2.5f, -2.0f, -2.5f);
		figSkybox.esfera(0.5, 50, 50, idTextura_P1);
	glPopMatrix();

	//tubos
	//enmedio
	glPushMatrix();
		glTranslatef(-1.5f, -2.5f, 0.0f);
		figSkybox.cilindro(0.25, 1, 50, idTextura_algodon);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0f, -2.5f, 0.0f);
		figSkybox.cilindro(0.25, 0.7, 50, idTextura_algodon);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(1.5f, -2.5f, 0.0f);
		figSkybox.cilindro(0.25, 0.5, 50, idTextura_algodon);
	glPopMatrix();

	//atras
	glPushMatrix();
		glTranslatef(-1.5f, -2.5f, -1.5f);
		figSkybox.cilindro(0.25, 0.7, 50, idTextura_algodon);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0f, -2.5f, -1.5f);
		figSkybox.cilindro(0.25, 1.2, 50, idTextura_algodon);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(1.5f, -2.5f, -1.5f);
		figSkybox.cilindro(0.25, 1.5, 50, idTextura_algodon);
	glPopMatrix();

	//enfrente
	glPushMatrix();
		glTranslatef(-1.5f, -2.5f, 1.5f);
		figSkybox.cilindro(0.25, 1, 50, idTextura_algodon);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0f, -2.5f, 1.5f);
		figSkybox.cilindro(0.25, 1.5, 50, idTextura_algodon);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(1.5f, -2.5f, 1.5f);
		figSkybox.cilindro(0.25, 0.5, 50, idTextura_algodon);
	glPopMatrix();

	//aros
	glPushMatrix();
		glTranslatef(0.0f, -2.40f, 0.0f);
		figSkybox.torus(0.7, 0.5, 50, 50);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-1.5f, -2.40f, 1.5f);
		figSkybox.torus(0.5, 0.3, 50, 50);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0f, -2.40f, 2.0f);
		figSkybox.torus(0.7, 0.5, 50, 50);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-1.5f, -2.40f, -1.5f);
		figSkybox.torus(0.5, 0.3, 50, 50);
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(1.5f, -2.40f, 1.5f);
		figSkybox.torus(0.7, 0.5, 50, 50);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-1.0f, -2.40f, 2.5f);
		figSkybox.torus(0.5, 0.3, 50, 50);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-1.0f, -2.40f, -0.5f);
		figSkybox.torus(0.5, 0.3, 50, 50);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(1.0f, -2.40f, 2.5f);
		figSkybox.torus(0.5, 0.3, 50, 50);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(1.0f, -2.40f, -2.5f);
		figSkybox.torus(0.5, 0.3, 50, 50);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0f, -2.40f, -2.0f);
		figSkybox.torus(0.7, 0.5, 50, 50);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-1.85f, -2.40f, 0.0f);
		figSkybox.torus(0.7, 0.5, 50, 50);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-1.6f, -2.40f, 2.5f);
		figSkybox.torus(0.5, 0.3, 50, 50);
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(1.5f, -2.40f, -0.5f);
		figSkybox.torus(0.7, 0.5, 50, 50);
	glPopMatrix();
}

void Carpa() {
	//dibujar cuerpo
	//dibujar base
	glPushMatrix();
		glTranslatef(0.0f, -0.5f, 0.0f);
		figSkybox.cilindro(1.5, 1.5, 50, idTextura_CI);
	glPopMatrix();

	//dibujar cono superior
	glPushMatrix();
		glTranslatef(0.0f, 1.0f, 0.0f);
		figSkybox.cono(1, 2.0, 50, idTextura_CI);
	glPopMatrix();

	//dibujar banderin
	//palo
	glPushMatrix();
		glTranslatef(0.0f, 1.75f, 0.0f);
		figSkybox.cilindro(0.1, 1.0, 50, idTextura_negro);
	glPopMatrix();
	//bandera
	glPushMatrix();
		glTranslatef(0.5f, 2.5f, 0.0f);
		glScalef(1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_CS, idTextura_CS);
	glPopMatrix();
}

void Splash() {
		//dibujar estructura
	//abajo
	glPushMatrix();
		glTranslatef(0.0f, -3.25f, 0.0f);
		glScalef(2, 1.5, 2);
		figSkybox.prisma2(idTextura_madero, idTextura_madero);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-2.0f, -3.25f, 0.0f);
		glScalef(2, 1.5, 2);
		figSkybox.prisma2(idTextura_madero, idTextura_madero);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(2.0f, -3.25f, 0.0f);
		glScalef(2, 1.5, 2);
		figSkybox.prisma2(idTextura_madero, idTextura_madero);
	glPopMatrix();
	
	//atraz
	glPushMatrix();
		glTranslatef(0.0f, -1.25f, -0.90f);
		glScalef(6, 2.5, 0.25);
		figSkybox.prisma2(idTextura_tela, idTextura_tela);
	glPopMatrix();

	//laterales
	glPushMatrix();
		glTranslatef(2.75f, -1.25f, 0.0f);
		glScalef(0.25, 2.5, 1.5);
		figSkybox.prisma2(idTextura_tela, idTextura_tela);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-2.75f, -1.25f, 0.0f);
		glScalef(0.25, 2.5, 1.5);
		figSkybox.prisma2(idTextura_tela, idTextura_tela);
	glPopMatrix();

	//arriba
	glPushMatrix();
		glTranslatef(0.0f, 0.0f, 0.0f);
		glScalef(6, 0.25, 2);
		figSkybox.prisma2(idTextura_madero, idTextura_madero);
	glPopMatrix();

	//dibujar tubos
	//izquierdo
	glPushMatrix();
		glTranslatef(-1.5f, -2.5f, 0.0f);
		figSkybox.cilindro(0.25, 2, 50, idTextura_tubo);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-1.5f, -2.5f, 0.1f);
		figSkybox.esfera(0.20, 50, 50, idTextura_rojo);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-1.5f, -2.25f, 0.1f);
		figSkybox.esfera(0.20, 50, 50, idTextura_amarillo);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-1.5f, -2.0f, 0.1f);
		figSkybox.esfera(0.20, 50, 50, idTextura_verde);
	glPopMatrix();
	/*
	glPushMatrix();
		glTranslatef(-1.5f, -1.75f, 0.1f);
		esfera(0.20, 50, 50, idTextura_azul);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-1.5f, -1.5f, 0.1f);
		esfera(0.20, 50, 50, idTextura_azulm);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-1.5f, -1.25f, 0.1f);
		esfera(0.20, 50, 50, idTextura_rosa);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-1.5f, -1.0f, 0.1f);
		esfera(0.20, 50, 50, idTextura_morado);
	glPopMatrix();
	*/
	glPushMatrix();
		glTranslatef(-1.5f, -0.5f, 0.1f);
		figSkybox.esfera(0.4, 50, 50, idTextura_P1);
	glPopMatrix();

	//boton de presin de agua
	glPushMatrix();
		glTranslatef(-1.5f, -2.5f, 0.75f);
		figSkybox.esfera(0.25, 50, 50, idTextura_negro);
	glPopMatrix();

	// central
	glPushMatrix();
		glTranslatef(0.0f, -2.5f, 0.0f);
		figSkybox.cilindro(0.25, 2, 50, idTextura_tubo);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0f, -2.5f, 0.1f);
		figSkybox.esfera(0.20, 50, 50, idTextura_rojo);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0f, -2.25f, 0.1f);
		figSkybox.esfera(0.20, 50, 50, idTextura_amarillo);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0f, -2.0f, 0.1f);
		figSkybox.esfera(0.20, 50, 50, idTextura_verde);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0f, -1.75f, 0.1f);
		figSkybox.esfera(0.20, 50, 50, idTextura_azul);
	glPopMatrix();
	/*
	glPushMatrix();
		glTranslatef(0.0f, -1.5f, 0.1f);
		esfera(0.20, 50, 50, idTextura_azulm);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0f, -1.25f, 0.1f);
		esfera(0.20, 50, 50, idTextura_rosa);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0f, -1.0f, 0.1f);
		esfera(0.20, 50, 50, idTextura_morado);
	glPopMatrix();
	*/
	glPushMatrix();
		glTranslatef(0.0f, -0.5f, 0.1f);
		figSkybox.esfera(0.4, 50, 50, idTextura_P1);
	glPopMatrix();

	//boton de presin de agua
	glPushMatrix();
		glTranslatef(0.0f, -2.5f, 0.75f);
		figSkybox.esfera(0.25, 50, 50, idTextura_negro);
	glPopMatrix();

	//derecho
	glPushMatrix();
		glTranslatef(1.5f, -2.5f, 0.0f);
		figSkybox.cilindro(0.25, 2, 50, idTextura_tubo);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(1.5f, -2.5f, 0.1f);
		figSkybox.esfera(0.20, 50, 50, idTextura_rojo);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(1.5f, -2.25f, 0.1f);
		figSkybox.esfera(0.20, 50, 50, idTextura_amarillo);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(1.5f, -2.0f, 0.1f);
		figSkybox.esfera(0.20, 50, 50, idTextura_verde);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(1.5f, -1.75f, 0.1f);
		figSkybox.esfera(0.20, 50, 50, idTextura_azul);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(1.5f, -1.5f, 0.1f);
		figSkybox.esfera(0.20, 50, 50, idTextura_azulm);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(1.5f, -1.25f, 0.1f);
		figSkybox.esfera(0.20, 50, 50, idTextura_rosa);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(1.5f, -1.0f, 0.1f);
		figSkybox.esfera(0.20, 50, 50, idTextura_morado);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(1.5f, -0.5f, 0.1f);
		figSkybox.esfera(0.4, 50, 50, idTextura_P1);
	glPopMatrix();

	//boton de presin de agua
	glPushMatrix();
		glTranslatef(1.5f, -2.5f, 0.75f);
		figSkybox.esfera(0.25, 50, 50, idTextura_negro);
	glPopMatrix();
}

void Inflable() {
		//dibujar estructura 1
	//abajo
	glPushMatrix();
		glTranslatef(-10.0f, 0.0f, -10.0f);
		glScalef(2, 1.0, 7);
		figSkybox.prisma2(idTextura_lad, idTextura_lad);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-2.0f, -3.5f, 0.0f);
		glScalef(2, 1.0, 7);
		figSkybox.prisma2(idTextura_tela, idTextura_tela);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0f, -3.5f, 0.0f);
		glScalef(2, 1.0, 7);
		figSkybox.prisma2(idTextura_tela, idTextura_tela);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(2.0f, -3.5f, 0.0f);
		glScalef(2, 1.0, 7);
		figSkybox.prisma2(idTextura_tela, idTextura_tela);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(4.0f, -3.5f, 0.0f);
		glScalef(2, 1.0, 7);
		figSkybox.prisma2(idTextura_tela, idTextura_tela);
	glPopMatrix();

	//en medio
	glPushMatrix();
		glTranslatef(-3.5f, -3.0f, 0.0f);
		glScalef(2, 1.0, 6.5);
		figSkybox.prisma2(idTextura_tela, idTextura_tela);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-2.0f, -3.0f, 0.0f);
		glScalef(2, 1.0, 6.5);
		figSkybox.prisma2(idTextura_tela, idTextura_tela);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0f, -3.0f, 0.0f);
		glScalef(2, 1.0, 6.5);
		figSkybox.prisma2(idTextura_tela, idTextura_tela);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(2.0f, -3.0f, 0.0f);
		glScalef(2, 1.0, 6.5);
		figSkybox.prisma2(idTextura_tela, idTextura_tela);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(3.5f, -3.0f, 0.0f);
		glScalef(2, 1.0, 6.5);
		figSkybox.prisma2(idTextura_tela, idTextura_tela);
	glPopMatrix();


	//arriba
	glPushMatrix();
		glTranslatef(-2.0f, -2.5f, 0.0f);
		glScalef(2, 1.0, 6);
		figSkybox.prisma2(idTextura_tela, idTextura_tela);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0f, -2.5f, 0.0f);
		glScalef(2, 1.0, 6);
		figSkybox.prisma2(idTextura_tela, idTextura_tela);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(2.0f, -2.5f, 0.0f);
		glScalef(2, 1.0, 6);
		figSkybox.prisma2(idTextura_tela, idTextura_tela);
	glPopMatrix();

	//esquinas
	glPushMatrix();
		glTranslatef(2.0f, -2.0f, 2.0f);
		figSkybox.cilindro(0.5, 2.5, 50, idTextura_algodon);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(2.0f, -2.0f, -2.0f);
		figSkybox.cilindro(0.5, 2.5, 50, idTextura_algodon);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-2.0f, -2.0f, 2.0f);
		figSkybox.cilindro(0.5, 2.5, 50, idTextura_algodon);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-2.0f, -2.0f, -2.0f);
		figSkybox.cilindro(0.5, 2.5, 50, idTextura_algodon);
	glPopMatrix();

	//dibujar estructura 2
	//laterales
	glPushMatrix();
		glTranslatef(-12.0f, -2.9f, -10.0f);
		glScalef(1, 2.5, 13);
		figSkybox.prisma2(idTextura_algodon, idTextura_algodon);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-4.0f, -2.9f, -10.0f);
		glScalef(1, 2.5, 13);
		figSkybox.prisma2(idTextura_algodon, idTextura_algodon);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(4.0f, -2.9f, -10.0f);
		glScalef(1, 2.5, 13);
		figSkybox.prisma2(idTextura_algodon, idTextura_algodon);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(12.0f, -2.9f, -10.0f);
		glScalef(1, 2.5, 13);
		figSkybox.prisma2(idTextura_algodon, idTextura_algodon);
	glPopMatrix();

	//atras
	glPushMatrix();
		glTranslatef(0.0f, -2.9f, -16.0f);
		glScalef(24, 2.5, 1);
		figSkybox.prisma2(idTextura_algodon, idTextura_algodon);
	glPopMatrix();

	//enfrente
	glPushMatrix();
		glTranslatef(-8.0f, -2.9f, -3.5f);
		glScalef(8, 2.5, 1);
		figSkybox.prisma2(idTextura_algodon, idTextura_algodon);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(8.0f, -2.9f, -3.5f);
		glScalef(8, 2.5, 1);
		figSkybox.prisma2(idTextura_algodon, idTextura_algodon);
	glPopMatrix();

	//base
	glPushMatrix();
		glTranslatef(-8.0f, -2.9f, -10.0f);
		glScalef(8, 1.0, 13);
		figSkybox.prisma2(idTextura_amarillo, idTextura_amarillo);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0f, -2.9f, -10.0f);
		glScalef(8, 1.0, 13);
		figSkybox.prisma2(idTextura_rosa, idTextura_rosa);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(8.0f, -2.9f, -10.0f);
		glScalef(8, 1.0, 13);
		figSkybox.prisma2(idTextura_azul, idTextura_azul);
	glPopMatrix();

	//muro 
	glPushMatrix();
		glTranslatef(0.0f, -2.0f, -16.0f);
		glRotatef(130.0f, 1.0, 0.0, 0.0);
		glScalef(26, 2.5, 3);
		figSkybox.prisma2(idTextura_tela, idTextura_tela);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0f, -2.0f, -23.0f);
		glScalef(26, 3.0, 15);
		figSkybox.prisma2(idTextura_tela, idTextura_tela);
	glPopMatrix();

	//esquinas
	glPushMatrix();
		glTranslatef(13.0f, -2.0f, -16.0f);
		figSkybox.cilindro(2.0, 8, 50, idTextura_tela);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-13.0f, -2.0f, -16.0f);
		figSkybox.cilindro(2.0, 8, 50, idTextura_tela);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(13.0f, -2.0f, -31.0f);
		figSkybox.cilindro(2.0, 8, 50, idTextura_tela);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-13.0f, -2.0f, -31.0f);
		figSkybox.cilindro(2.0, 8, 50, idTextura_tela);
	glPopMatrix();
}

void Mesas() {
	//Mesa 1
	glPushMatrix();
		glTranslatef(9.0f, 0.5f, -28.0f);
		glScalef(0.1, 1.0, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(9.0f, 0.5f, -32.0f);
		glScalef(0.1, 1.0, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(11.0f, 0.5f, -28.0f);
		glScalef(0.1, 1.0, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(11.0f, 0.5f, -32.0f);
		glScalef(0.1, 1.0, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(10.0f, 1.25f, -30.0f);
		glScalef(2.5, 0.5, 4.5);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	//asiento 1
	glPushMatrix();
		glTranslatef(8.0f, 0.25f, -28.5f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(8.0f, 0.25f, -31.0f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(8.5f, 0.25f, -28.5f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(8.5f, 0.25f, -31.0f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(8.25f, 0.75f, -30.0f);
		glScalef(0.75, 0.5, 4.0);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	//asiento 2
	glPushMatrix();
		glTranslatef(11.5f, 0.25f, -28.5f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(11.5f, 0.25f, -31.0f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(12.0f, 0.25f, -28.5f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(12.0f, 0.25f, -31.0f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(11.75f, 0.75f, -30.0f);
		glScalef(0.75, 0.5, 4.0);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	//Mesa 2
	glPushMatrix();
		glTranslatef(9.0f, 0.5f, -48.0f);
		glScalef(0.1, 1.0, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(9.0f, 0.5f, -52.0f);
		glScalef(0.1, 1.0, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(11.0f, 0.5f, -48.0f);
		glScalef(0.1, 1.0, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(11.0f, 0.5f, -52.0f);
		glScalef(0.1, 1.0, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(10.0f, 1.25f, -50.0f);
		glScalef(2.5, 0.5, 4.5);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	//asiento 1
	glPushMatrix();
		glTranslatef(8.0f, 0.25f, -48.5f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(8.0f, 0.25f, -51.0f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(8.5f, 0.25f, -48.5f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(8.5f, 0.25f, -51.0f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(8.25f, 0.75f, -50.0f);
		glScalef(0.75, 0.5, 4.0);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	//asiento 2
	glPushMatrix();
		glTranslatef(11.5f, 0.25f, -48.5f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(11.5f, 0.25f, -51.0f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(12.0f, 0.25f, -48.5f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(12.0f, 0.25f, -51.0f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(11.75f, 0.75f, -50.0f);
		glScalef(0.75, 0.5, 4.0);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	//Mesa 3
	glPushMatrix();
		glTranslatef(-9.0f, 0.5f, -28.0f);
		glScalef(0.1, 1.0, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-9.0f, 0.5f, -32.0f);
		glScalef(0.1, 1.0, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-11.0f, 0.5f, -28.0f);
		glScalef(0.1, 1.0, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-11.0f, 0.5f, -32.0f);
		glScalef(0.1, 1.0, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-10.0f, 1.25f, -30.0f);
		glScalef(2.5, 0.5, 4.5);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	//asiento 1
	glPushMatrix();
		glTranslatef(-8.0f, 0.25f, -28.5f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-8.0f, 0.25f, -31.0f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-8.5f, 0.25f, -28.5f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-8.5f, 0.25f, -31.0f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-8.25f, 0.75f, -30.0f);
		glScalef(0.75, 0.5, 4.0);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	//asiento 2
	glPushMatrix();
		glTranslatef(-11.5f, 0.25f, -28.5f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-11.5f, 0.25f, -31.0f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-12.0f, 0.25f, -28.5f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-12.0f, 0.25f, -31.0f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-11.75f, 0.75f, -30.0f);
		glScalef(0.75, 0.5, 4.0);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	//Mesa 4
	glPushMatrix();
		glTranslatef(-9.0f, 0.5f, -48.0f);
		glScalef(0.1, 1.0, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-9.0f, 0.5f, -52.0f);
		glScalef(0.1, 1.0, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-11.0f, 0.5f, -48.0f);
		glScalef(0.1, 1.0, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-11.0f, 0.5f, -52.0f);
		glScalef(0.1, 1.0, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-10.0f, 1.25f, -50.0f);
		glScalef(2.5, 0.5, 4.5);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	//asiento 1
	glPushMatrix();
		glTranslatef(-8.0f, 0.25f, -48.5f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-8.0f, 0.25f, -51.0f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-8.5f, 0.25f, -48.5f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-8.5f, 0.25f, -51.0f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-8.25f, 0.75f, -50.0f);
		glScalef(0.75, 0.5, 4.0);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	//asiento 2
	glPushMatrix();
		glTranslatef(-11.5f, 0.25f, -48.5f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-11.5f, 0.25f, -51.0f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-12.0f, 0.25f, -48.5f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-12.0f, 0.25f, -51.0f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-11.75f, 0.75f, -50.0f);
		glScalef(0.75, 0.5, 4.0);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	//Mesa 5
	glPushMatrix();
		glTranslatef(9.0f, 0.5f, 28.0f);
		glScalef(0.1, 1.0, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(9.0f, 0.5f, 32.0f);
		glScalef(0.1, 1.0, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(11.0f, 0.5f, 28.0f);
		glScalef(0.1, 1.0, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(11.0f, 0.5f, 32.0f);
		glScalef(0.1, 1.0, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(10.0f, 1.25f, 30.0f);
		glScalef(2.5, 0.5, 4.5);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	//asiento 1
	glPushMatrix();
		glTranslatef(8.0f, 0.25f, 28.5f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(8.0f, 0.25f, 31.0f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(8.5f, 0.25f, 28.5f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(8.5f, 0.25f, 31.0f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(8.25f, 0.75f, 30.0f);
		glScalef(0.75, 0.5, 4.0);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	//asiento 2
	glPushMatrix();
		glTranslatef(11.5f, 0.25f, 28.5f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(11.5f, 0.25f, 31.0f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(12.0f, 0.25f, 28.5f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(12.0f, 0.25f, 31.0f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(11.75f, 0.75f, 30.0f);
		glScalef(0.75, 0.5, 4.0);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	//Mesa 6
	glPushMatrix();
		glTranslatef(9.0f, 0.5f, 48.0f);
		glScalef(0.1, 1.0, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(9.0f, 0.5f, 52.0f);
		glScalef(0.1, 1.0, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(11.0f, 0.5f, 48.0f);
		glScalef(0.1, 1.0, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(11.0f, 0.5f, 52.0f);
		glScalef(0.1, 1.0, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(10.0f, 1.25f, 50.0f);
		glScalef(2.5, 0.5, 4.5);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	//asiento 1
	glPushMatrix();
		glTranslatef(8.0f, 0.25f, 48.5f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(8.0f, 0.25f, 51.0f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(8.5f, 0.25f, 48.5f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(8.5f, 0.25f, 51.0f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(8.25f, 0.75f, 50.0f);
		glScalef(0.75, 0.5, 4.0);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	//asiento 2
	glPushMatrix();
		glTranslatef(11.5f, 0.25f, 48.5f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(11.5f, 0.25f, 51.0f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(12.0f, 0.25f, 48.5f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(12.0f, 0.25f, 51.0f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(11.75f, 0.75f, 50.0f);
		glScalef(0.75, 0.5, 4.0);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	//Mesa 7
	glPushMatrix();
		glTranslatef(-9.0f, 0.5f, 28.0f);
		glScalef(0.1, 1.0, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-9.0f, 0.5f, 32.0f);
		glScalef(0.1, 1.0, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-11.0f, 0.5f, 28.0f);
		glScalef(0.1, 1.0, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-11.0f, 0.5f, 32.0f);
		glScalef(0.1, 1.0, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-10.0f, 1.25f, 30.0f);
		glScalef(2.5, 0.5, 4.5);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	//asiento 1
	glPushMatrix();
		glTranslatef(-8.0f, 0.25f, 28.5f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-8.0f, 0.25f, 31.0f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-8.5f, 0.25f, 28.5f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-8.5f, 0.25f, 31.0f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-8.25f, 0.75f, 30.0f);
		glScalef(0.75, 0.5, 4.0);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	//asiento 2
	glPushMatrix();
		glTranslatef(-11.5f, 0.25f, 28.5f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-11.5f, 0.25f, 31.0f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-12.0f, 0.25f, 28.5f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-12.0f, 0.25f, 31.0f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-11.75f, 0.75f, 30.0f);
		glScalef(0.75, 0.5, 4.0);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	//Mesa 8
	glPushMatrix();
		glTranslatef(-9.0f, 0.5f, 48.0f);
		glScalef(0.1, 1.0, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-9.0f, 0.5f, 52.0f);
		glScalef(0.1, 1.0, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-11.0f, 0.5f, 48.0f);
		glScalef(0.1, 1.0, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-11.0f, 0.5f, 52.0f);
		glScalef(0.1, 1.0, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-10.0f, 1.25f, 50.0f);
		glScalef(2.5, 0.5, 4.5);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	//asiento 1
	glPushMatrix();
		glTranslatef(-8.0f, 0.25f, 48.5f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-8.0f, 0.25f, 51.0f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-8.5f, 0.25f, 48.5f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-8.5f, 0.25f, 51.0f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-8.25f, 0.75f, 50.0f);
		glScalef(0.75, 0.5, 4.0);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	//asiento 2
	glPushMatrix();
		glTranslatef(-11.5f, 0.25f, 48.5f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-11.5f, 0.25f, 51.0f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-12.0f, 0.25f, 48.5f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-12.0f, 0.25f, 51.0f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-11.75f, 0.75f, 50.0f);
		glScalef(0.75, 0.5, 4.0);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	//Mesa 9
	glPushMatrix();
		glTranslatef(49.0f, 0.5f, -28.0f);
		glScalef(0.1, 1.0, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(49.0f, 0.5f, -32.0f);
		glScalef(0.1, 1.0, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(51.0f, 0.5f, -28.0f);
		glScalef(0.1, 1.0, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(51.0f, 0.5f, -32.0f);
		glScalef(0.1, 1.0, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(50.0f, 1.25f, -30.0f);
		glScalef(2.5, 0.5, 4.5);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	//asiento 1
	glPushMatrix();
		glTranslatef(48.0f, 0.25f, -28.5f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(48.0f, 0.25f, -31.0f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(48.5f, 0.25f, -28.5f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(48.5f, 0.25f, -31.0f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(48.25f, 0.75f, -30.0f);
		glScalef(0.75, 0.5, 4.0);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	//asiento 2
	glPushMatrix();
		glTranslatef(51.5f, 0.25f, -28.5f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(51.5f, 0.25f, -31.0f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(52.0f, 0.25f, -28.5f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(52.0f, 0.25f, -31.0f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(51.75f, 0.75f, -30.0f);
		glScalef(0.75, 0.5, 4.0);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	//Mesa 10
	glPushMatrix();
		glTranslatef(-49.0f, 0.5f, -28.0f);
		glScalef(0.1, 1.0, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-49.0f, 0.5f, -32.0f);
		glScalef(0.1, 1.0, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-51.0f, 0.5f, -28.0f);
		glScalef(0.1, 1.0, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-51.0f, 0.5f, -32.0f);
		glScalef(0.1, 1.0, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-50.0f, 1.25f, -30.0f);
		glScalef(2.5, 0.5, 4.5);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	//asiento 1
	glPushMatrix();
		glTranslatef(-48.0f, 0.25f, -28.5f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-48.0f, 0.25f, -31.0f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-48.5f, 0.25f, -28.5f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-48.5f, 0.25f, -31.0f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-48.25f, 0.75f, -30.0f);
		glScalef(0.75, 0.5, 4.0);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	//asiento 2
	glPushMatrix();
		glTranslatef(-51.5f, 0.25f, -28.5f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-51.5f, 0.25f, -31.0f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-52.0f, 0.25f, -28.5f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-52.0f, 0.25f, -31.0f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-51.75f, 0.75f, -30.0f);
		glScalef(0.75, 0.5, 4.0);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	//Mesa 11
	glPushMatrix();
		glTranslatef(-49.0f, 0.5f, 28.0f);
		glScalef(0.1, 1.0, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-49.0f, 0.5f, 32.0f);
		glScalef(0.1, 1.0, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-51.0f, 0.5f, 28.0f);
		glScalef(0.1, 1.0, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-51.0f, 0.5f, 32.0f);
		glScalef(0.1, 1.0, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-50.0f, 1.25f, 30.0f);
		glScalef(2.5, 0.5, 4.5);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	//asiento 1
	glPushMatrix();
		glTranslatef(-48.0f, 0.25f, 28.5f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-48.0f, 0.25f, 31.0f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-48.5f, 0.25f, 28.5f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-48.5f, 0.25f, 31.0f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-48.25f, 0.75f, 30.0f);
		glScalef(0.75, 0.5, 4.0);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	//asiento 2
	glPushMatrix();
		glTranslatef(-51.5f, 0.25f, 28.5f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-51.5f, 0.25f, 31.0f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-52.0f, 0.25f, 28.5f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-52.0f, 0.25f, 31.0f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-51.75f, 0.75f, 30.0f);
		glScalef(0.75, 0.5, 4.0);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	//Mesa 12
	glPushMatrix();
		glTranslatef(49.0f, 0.5f, 48.0f);
		glScalef(0.1, 1.0, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(49.0f, 0.5f, 52.0f);
		glScalef(0.1, 1.0, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(51.0f, 0.5f, 48.0f);
		glScalef(0.1, 1.0, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(51.0f, 0.5f, 52.0f);
		glScalef(0.1, 1.0, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(50.0f, 1.25f, 50.0f);
		glScalef(2.5, 0.5, 4.5);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	//asiento 1
	glPushMatrix();
		glTranslatef(48.0f, 0.25f, 48.5f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(48.0f, 0.25f, 51.0f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(48.5f, 0.25f, 48.5f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(48.5f, 0.25f, 51.0f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(48.25f, 0.75f, 50.0f);
		glScalef(0.75, 0.5, 4.0);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	//asiento 2
	glPushMatrix();
		glTranslatef(51.5f, 0.25f, 48.5f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(51.5f, 0.25f, 51.0f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(52.0f, 0.25f, 48.5f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(52.0f, 0.25f, 51.0f);
		glScalef(0.1, 0.5, 0.1);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(51.75f, 0.75f, 50.0f);
		glScalef(0.75, 0.5, 4.0);
		figSkybox.prisma2(idTextura_piso, idTextura_piso);
	glPopMatrix();
}

void Caminos() {
				//Caminos horisontales
			glPushMatrix();
				glTranslatef(0.0, 0.0, 60.0);
				glScalef(2.0, 0.25, 80.0);
				figSkybox.prisma2(idTextura_suelo, idTextura_suelo);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(0.0, 0.0, -60.0);
				glScalef(2.0, 0.25, 80.0);
				figSkybox.prisma2(idTextura_suelo, idTextura_suelo);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(20.0, 0.0, 0.0);
				glScalef(2.0, 0.25, 200.0);
				figSkybox.prisma2(idTextura_suelo, idTextura_suelo);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(40.0, 0.0, 0.0);
				glScalef(2.0, 0.25, 200.0);
				figSkybox.prisma2(idTextura_suelo, idTextura_suelo);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(60.0, 0.0, 30.0);
				glScalef(2.0, 0.25, 140.0);
				figSkybox.prisma2(idTextura_suelo, idTextura_suelo);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(60.0, 0.0, -90.0);
				glScalef(2.0, 0.25, 20.0);
				figSkybox.prisma2(idTextura_suelo, idTextura_suelo);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(80.0, 0.0, 0.0);
				glScalef(2.0, 0.25, 200.0);
				figSkybox.prisma2(idTextura_suelo, idTextura_suelo);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(100.0, 0.0, 0.0);
				glScalef(2.0, 0.25, 200.0);
				figSkybox.prisma2(idTextura_suelo, idTextura_suelo);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-20.0, 0.0, 0.0);
				glScalef(2.0, 0.25, 200.0);
				figSkybox.prisma2(idTextura_suelo, idTextura_suelo);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-40.0, 0.0, 0.0);
				glScalef(2.0, 0.25, 200.0);
				figSkybox.prisma2(idTextura_suelo, idTextura_suelo);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-60.0, 0.0, -30.0);
				glScalef(2.0, 0.25, 140.0);
				figSkybox.prisma2(idTextura_suelo, idTextura_suelo);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-60.0, 0.0, 90.0);
				glScalef(2.0, 0.25, 20.0);
				figSkybox.prisma2(idTextura_suelo, idTextura_suelo);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-80.0, 0.0, 0.0);
				glScalef(2.0, 0.25, 200.0);
				figSkybox.prisma2(idTextura_suelo, idTextura_suelo);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-100.0, 0.0, 0.0);
				glScalef(2.0, 0.25, 200.0);
				figSkybox.prisma2(idTextura_suelo, idTextura_suelo);
			glPopMatrix();

			//Caminos verticales
			glPushMatrix();
				glTranslatef(60.0, 0.0, 0.0);
				glRotatef(90.0, 0.0, 1.0, 0.0);
				glScalef(2.0, 0.25, 80.0);
				figSkybox.prisma2(idTextura_suelo, idTextura_suelo);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-60.0, 0.0, 0.0);
				glRotatef(90.0, 0.0, 1.0, 0.0);
				glScalef(2.0, 0.25, 80.0);
				figSkybox.prisma2(idTextura_suelo, idTextura_suelo);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(0.0, 0.0, 20.0);
				glRotatef(90.0, 0.0, 1.0, 0.0);
				glScalef(2.0, 0.25, 200.0);
				figSkybox.prisma2(idTextura_suelo, idTextura_suelo);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(0.0, 0.0, 40.0);
				glRotatef(90.0, 0.0, 1.0, 0.0);
				glScalef(2.0, 0.25, 200.0);
				figSkybox.prisma2(idTextura_suelo, idTextura_suelo);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(30.0, 0.0, 60.0);
				glRotatef(90.0, 0.0, 1.0, 0.0);
				glScalef(2.0, 0.25, 140.0);
				figSkybox.prisma2(idTextura_suelo, idTextura_suelo);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-90.0, 0.0, 60.0);
				glRotatef(90.0, 0.0, 1.0, 0.0);
				glScalef(2.0, 0.25, 20.0);
				figSkybox.prisma2(idTextura_suelo, idTextura_suelo);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(0.0, 0.0, 80.0);
				glRotatef(90.0, 0.0, 1.0, 0.0);
				glScalef(2.0, 0.25, 200.0);
				figSkybox.prisma2(idTextura_suelo, idTextura_suelo);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(0.0, 0.0, 100.0);
				glRotatef(90.0, 0.0, 1.0, 0.0);
				glScalef(2.0, 0.25, 200.0);
				figSkybox.prisma2(idTextura_suelo, idTextura_suelo);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(0.0, 0.0, -20.0);
				glRotatef(90.0, 0.0, 1.0, 0.0);
				glScalef(2.0, 0.25, 200.0);
				figSkybox.prisma2(idTextura_suelo, idTextura_suelo);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(0.0, 0.0, -40.0);
				glRotatef(90.0, 0.0, 1.0, 0.0);
				glScalef(2.0, 0.25, 200.0);
				figSkybox.prisma2(idTextura_suelo, idTextura_suelo);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-30.0, 0.0, -60.0);
				glRotatef(90.0, 0.0, 1.0, 0.0);
				glScalef(2.0, 0.25, 140.0);
				figSkybox.prisma2(idTextura_suelo, idTextura_suelo);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(90.0, 0.0, -60.0);
				glRotatef(90.0, 0.0, 1.0, 0.0);
				glScalef(2.0, 0.25, 20.0);
				figSkybox.prisma2(idTextura_suelo, idTextura_suelo);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(0.0, 0.0, -80.0);
				glRotatef(90.0, 0.0, 1.0, 0.0);
				glScalef(2.0, 0.25, 200.0);
				figSkybox.prisma2(idTextura_suelo, idTextura_suelo);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(0.0, 0.0, -100.0);
				glRotatef(90.0, 0.0, 1.0, 0.0);
				glScalef(2.0, 0.25, 200.0);
				figSkybox.prisma2(idTextura_suelo, idTextura_suelo);
			glPopMatrix();
}

void Bancas() {
			//Ilera de Bancas 1
			glPushMatrix();
				glTranslatef(-22.0, -1.0, 25.0);
				glRotatef(90.0, 0.0, 1.0, 0.0);
				glScalef(0.01, 0.01, 0.01);
				Banca.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-22.0, -1.0, 33.0);
				glRotatef(90.0, 0.0, 1.0, 0.0);
				glScalef(0.01, 0.01, 0.01);
				Banca.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-18.0, -1.0, 26.0);
				glRotatef(270.0, 0.0, 1.0, 0.0);
				glScalef(0.01, 0.01, 0.01);
				Banca.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-18.0, -1.0, 34.0);
				glRotatef(270.0, 0.0, 1.0, 0.0);
				glScalef(0.01, 0.01, 0.01);
				Banca.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			//Ilera de Bancas 2
			glPushMatrix();
				glTranslatef(22.0, -1.0, 25.0);
				glRotatef(270.0, 0.0, 1.0, 0.0);
				glScalef(0.01, 0.01, 0.01);
				Banca.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(22.0, -1.0, 33.0);
				glRotatef(270.0, 0.0, 1.0, 0.0);
				glScalef(0.01, 0.01, 0.01);
				Banca.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(18.0, -1.0, 26.0);
				glRotatef(90.0, 0.0, 1.0, 0.0);
				glScalef(0.01, 0.01, 0.01);
				Banca.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(18.0, -1.0, 34.0);
				glRotatef(90.0, 0.0, 1.0, 0.0);
				glScalef(0.01, 0.01, 0.01);
				Banca.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			//Ilera de Bancas 3
			glPushMatrix();
				glTranslatef(-22.0, -1.0, -25.0);
				glRotatef(90.0, 0.0, 1.0, 0.0);
				glScalef(0.01, 0.01, 0.01);
				Banca.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-22.0, -1.0, -33.0);
				glRotatef(90.0, 0.0, 1.0, 0.0);
				glScalef(0.01, 0.01, 0.01);
				Banca.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-18.0, -1.0, -26.0);
				glRotatef(270.0, 0.0, 1.0, 0.0);
				glScalef(0.01, 0.01, 0.01);
				Banca.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-18.0, -1.0, -34.0);
				glRotatef(270.0, 0.0, 1.0, 0.0);
				glScalef(0.01, 0.01, 0.01);
				Banca.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			//Ilera de Bancas 4
			glPushMatrix();
				glTranslatef(22.0, -1.0, -25.0);
				glRotatef(270.0, 0.0, 1.0, 0.0);
				glScalef(0.01, 0.01, 0.01);
				Banca.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(22.0, -1.0, -33.0);
				glRotatef(270.0, 0.0, 1.0, 0.0);
				glScalef(0.01, 0.01, 0.01);
				Banca.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(18.0, -1.0, -26.0);
				glRotatef(90.0, 0.0, 1.0, 0.0);
				glScalef(0.01, 0.01, 0.01);
				Banca.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(18.0, -1.0, -34.0);
				glRotatef(90.0, 0.0, 1.0, 0.0);
				glScalef(0.01, 0.01, 0.01);
				Banca.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			//Ilera de Bancas 5
			glPushMatrix();
				glTranslatef(62.0, -1.0, -25.0);
				glRotatef(270.0, 0.0, 1.0, 0.0);
				glScalef(0.01, 0.01, 0.01);
				Banca.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(62.0, -1.0, -33.0);
				glRotatef(270.0, 0.0, 1.0, 0.0);
				glScalef(0.01, 0.01, 0.01);
				Banca.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(58.0, -1.0, -26.0);
				glRotatef(90.0, 0.0, 1.0, 0.0);
				glScalef(0.01, 0.01, 0.01);
				Banca.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(58.0, -1.0, -34.0);
				glRotatef(90.0, 0.0, 1.0, 0.0);
				glScalef(0.01, 0.01, 0.01);
				Banca.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			//Ilera de Bancas 6
			glPushMatrix();
				glTranslatef(62.0, -1.0, 25.0);
				glRotatef(270.0, 0.0, 1.0, 0.0);
				glScalef(0.01, 0.01, 0.01);
				Banca.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(62.0, -1.0, 33.0);
				glRotatef(270.0, 0.0, 1.0, 0.0);
				glScalef(0.01, 0.01, 0.01);
				Banca.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(58.0, -1.0, 26.0);
				glRotatef(90.0, 0.0, 1.0, 0.0);
				glScalef(0.01, 0.01, 0.01);
				Banca.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(58.0, -1.0, 34.0);
				glRotatef(90.0, 0.0, 1.0, 0.0);
				glScalef(0.01, 0.01, 0.01);
				Banca.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			//Ilera de Bancas 7
			glPushMatrix();
				glTranslatef(-62.0, -1.0, 25.0);
				glRotatef(90.0, 0.0, 1.0, 0.0);
				glScalef(0.01, 0.01, 0.01);
				Banca.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-62.0, -1.0, 33.0);
				glRotatef(90.0, 0.0, 1.0, 0.0);
				glScalef(0.01, 0.01, 0.01);
				Banca.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-58.0, -1.0, 26.0);
				glRotatef(270.0, 0.0, 1.0, 0.0);
				glScalef(0.01, 0.01, 0.01);
				Banca.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-58.0, -1.0, 34.0);
				glRotatef(270.0, 0.0, 1.0, 0.0);
				glScalef(0.01, 0.01, 0.01);
				Banca.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			//Ilera de Bancas 8
			glPushMatrix();
				glTranslatef(-62.0, -1.0, -25.0);
				glRotatef(90.0, 0.0, 1.0, 0.0);
				glScalef(0.01, 0.01, 0.01);
				Banca.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-62.0, -1.0, -33.0);
				glRotatef(90.0, 0.0, 1.0, 0.0);
				glScalef(0.01, 0.01, 0.01);
				Banca.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-58.0, -1.0, -26.0);
				glRotatef(270.0, 0.0, 1.0, 0.0);
				glScalef(0.01, 0.01, 0.01);
				Banca.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-58.0, -1.0, -34.0);
				glRotatef(270.0, 0.0, 1.0, 0.0);
				glScalef(0.01, 0.01, 0.01);
				Banca.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			//Ilera de Bancas 9
			glPushMatrix();
				glTranslatef(-22.0, -1.0, 65.0);
				glRotatef(90.0, 0.0, 1.0, 0.0);
				glScalef(0.01, 0.01, 0.01);
				Banca.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-22.0, -1.0, 73.0);
				glRotatef(90.0, 0.0, 1.0, 0.0);
				glScalef(0.01, 0.01, 0.01);
				Banca.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-18.0, -1.0, 66.0);
				glRotatef(270.0, 0.0, 1.0, 0.0);
				glScalef(0.01, 0.01, 0.01);
				Banca.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-18.0, -1.0, 74.0);
				glRotatef(270.0, 0.0, 1.0, 0.0);
				glScalef(0.01, 0.01, 0.01);
				Banca.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			//Ilera de Bancas 10
			glPushMatrix();
				glTranslatef(22.0, -1.0, 65.0);
				glRotatef(270.0, 0.0, 1.0, 0.0);
				glScalef(0.01, 0.01, 0.01);
				Banca.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(22.0, -1.0, 73.0);
				glRotatef(270.0, 0.0, 1.0, 0.0);
				glScalef(0.01, 0.01, 0.01);
				Banca.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(18.0, -1.0, 66.0);
				glRotatef(90.0, 0.0, 1.0, 0.0);
				glScalef(0.01, 0.01, 0.01);
				Banca.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(18.0, -1.0, 74.0);
				glRotatef(90.0, 0.0, 1.0, 0.0);
				glScalef(0.01, 0.01, 0.01);
				Banca.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			//Ilera de Bancas 11
			glPushMatrix();
				glTranslatef(-22.0, -1.0, -65.0);
				glRotatef(90.0, 0.0, 1.0, 0.0);
				glScalef(0.01, 0.01, 0.01);
				Banca.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-22.0, -1.0, -73.0);
				glRotatef(90.0, 0.0, 1.0, 0.0);
				glScalef(0.01, 0.01, 0.01);
				Banca.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-18.0, -1.0, -66.0);
				glRotatef(270.0, 0.0, 1.0, 0.0);
				glScalef(0.01, 0.01, 0.01);
				Banca.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-18.0, -1.0, -74.0);
				glRotatef(270.0, 0.0, 1.0, 0.0);
				glScalef(0.01, 0.01, 0.01);
				Banca.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			//Ilera de Bancas 12
			glPushMatrix();
				glTranslatef(22.0, -1.0, -65.0);
				glRotatef(270.0, 0.0, 1.0, 0.0);
				glScalef(0.01, 0.01, 0.01);
				Banca.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(22.0, -1.0, -73.0);
				glRotatef(270.0, 0.0, 1.0, 0.0);
				glScalef(0.01, 0.01, 0.01);
				Banca.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(18.0, -1.0, -66.0);
				glRotatef(90.0, 0.0, 1.0, 0.0);
				glScalef(0.01, 0.01, 0.01);
				Banca.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(18.0, -1.0, -74.0);
				glRotatef(90.0, 0.0, 1.0, 0.0);
				glScalef(0.01, 0.01, 0.01);
				Banca.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();
}

void Contenedores() {
			//Ilera de Contenedores 1
			glPushMatrix();
				glTranslatef(5.0, 0.60, 65.0);
				glRotatef(90.0, 0.0, 1.0, 0.0);
				glScalef(0.03, 0.03, 0.03);
				Contenedor.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-5.0, 0.60, 35.0);
				glRotatef(270.0, 0.0, 1.0, 0.0);
				glScalef(0.03, 0.03, 0.03);
				Contenedor.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			//Ilera de Contenedores 2
			glPushMatrix();
				glTranslatef(5.0, 0.60, -65.0);
				glRotatef(90.0, 0.0, 1.0, 0.0);
				glScalef(0.03, 0.03, 0.03);
				Contenedor.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-5.0, 0.60, -35.0);
				glRotatef(270.0, 0.0, 1.0, 0.0);
				glScalef(0.03, 0.03, 0.03);
				Contenedor.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			//Ilera de Contenedores 3
			glPushMatrix();
				glTranslatef(-65.0, 0.60, 5.0);
				glRotatef(90.0, 0.0, 1.0, 0.0);
				glScalef(0.03, 0.03, 0.03);
				Contenedor.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-35.0, 0.60, -25.0);
				glRotatef(270.0, 0.0, 1.0, 0.0);
				glScalef(0.03, 0.03, 0.03);
				Contenedor.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			//Ilera de Contenedores 4
			glPushMatrix();
				glTranslatef(65.0, 0.60, 5.0);
				glRotatef(90.0, 0.0, 1.0, 0.0);
				glScalef(0.03, 0.03, 0.03);
				Contenedor.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(35.0, 0.60, -25.0);
				glRotatef(270.0, 0.0, 1.0, 0.0);
				glScalef(0.03, 0.03, 0.03);
				Contenedor.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();
}

void Baños() {
	//Baño 1
	glPushMatrix();
		glTranslatef(5.0f, 3.0f, -85.0f);
		glScalef(3.0, 6.0, 3.0);
		figSkybox.prisma2(idTextura_lad, idTextura_lad);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(5.0f, 2.5f, -83.25f);
		glScalef(2.5, 5.5, 0.5);
		figSkybox.prisma2(idTextura_azulm, idTextura_azulm);
	glPopMatrix();

	//Baño 2
	glPushMatrix();
		glTranslatef(10.0f, 3.0f, -85.0f);
		glScalef(3.0, 6.0, 3.0);
		figSkybox.prisma2(idTextura_lad, idTextura_lad);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(10.0f, 2.5f, -83.25f);
		glScalef(2.5, 5.5, 0.5);
		figSkybox.prisma2(idTextura_azulm, idTextura_azulm);
	glPopMatrix();

		//Baño 2
	glPushMatrix();
		glTranslatef(15.0f, 3.0f, -85.0f);
		glScalef(3.0, 6.0, 3.0);
		figSkybox.prisma2(idTextura_lad, idTextura_lad);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(15.0f, 2.5f, -83.25f);
		glScalef(2.5, 5.5, 0.5);
		figSkybox.prisma2(idTextura_azulm, idTextura_azulm);
	glPopMatrix();

	//Baño 4
	glPushMatrix();
		glTranslatef(25.0f, 3.0f, -85.0f);
		glScalef(3.0, 6.0, 3.0);
		figSkybox.prisma2(idTextura_lad, idTextura_lad);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(25.0f, 2.5f, -83.25f);
		glScalef(2.5, 5.5, 0.5);
		figSkybox.prisma2(idTextura_azulm, idTextura_azulm);
	glPopMatrix();

	//Baño 5
	glPushMatrix();
		glTranslatef(30.0f, 3.0f, -85.0f);
		glScalef(3.0, 6.0, 3.0);
		figSkybox.prisma2(idTextura_lad, idTextura_lad);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(30.0f, 2.5f, -83.25f);
		glScalef(2.5, 5.5, 0.5);
		figSkybox.prisma2(idTextura_azulm, idTextura_azulm);
	glPopMatrix();

	//Baño 6
	glPushMatrix();
		glTranslatef(35.0f, 3.0f, -85.0f);
		glScalef(3.0, 6.0, 3.0);
		figSkybox.prisma2(idTextura_lad, idTextura_lad);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(35.0f, 2.5f, -83.25f);
		glScalef(2.5, 5.5, 0.5);
		figSkybox.prisma2(idTextura_azulm, idTextura_azulm);
	glPopMatrix();

	//Baño 7
	glPushMatrix();
		glTranslatef(-5.0f, 3.0f, -85.0f);
		glScalef(3.0, 6.0, 3.0);
		figSkybox.prisma2(idTextura_lad, idTextura_lad);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-5.0f, 2.5f, -83.25f);
		glScalef(2.5, 5.5, 0.5);
		figSkybox.prisma2(idTextura_azulm, idTextura_azulm);
	glPopMatrix();

	//Baño 8
	glPushMatrix();
		glTranslatef(-10.0f, 3.0f, -85.0f);
		glScalef(3.0, 6.0, 3.0);
		figSkybox.prisma2(idTextura_lad, idTextura_lad);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-10.0f, 2.5f, -83.25f);
		glScalef(2.5, 5.5, 0.5);
		figSkybox.prisma2(idTextura_azulm, idTextura_azulm);
	glPopMatrix();

	//Baño 9
	glPushMatrix();
		glTranslatef(-15.0f, 3.0f, -85.0f);
		glScalef(3.0, 6.0, 3.0);
		figSkybox.prisma2(idTextura_lad, idTextura_lad);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-15.0f, 2.5f, -83.25f);
		glScalef(2.5, 5.5, 0.5);
		figSkybox.prisma2(idTextura_azulm, idTextura_azulm);
	glPopMatrix();

	//Baño 10
	glPushMatrix();
		glTranslatef(-25.0f, 3.0f, -85.0f);
		glScalef(3.0, 6.0, 3.0);
		figSkybox.prisma2(idTextura_lad, idTextura_lad);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-25.0f, 2.5f, -83.25f);
		glScalef(2.5, 5.5, 0.5);
		figSkybox.prisma2(idTextura_azulm, idTextura_azulm);
	glPopMatrix();

	//Baño 11
	glPushMatrix();
		glTranslatef(-30.0f, 3.0f, -85.0f);
		glScalef(3.0, 6.0, 3.0);
		figSkybox.prisma2(idTextura_lad, idTextura_lad);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-30.0f, 2.5f, -83.25f);
		glScalef(2.5, 5.5, 0.5);
		figSkybox.prisma2(idTextura_azulm, idTextura_azulm);
	glPopMatrix();

	//Baño 12
	glPushMatrix();
		glTranslatef(-35.0f, 3.0f, -85.0f);
		glScalef(3.0, 6.0, 3.0);
		figSkybox.prisma2(idTextura_lad, idTextura_lad);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-35.0f, 2.5f, -83.25f);
		glScalef(2.5, 5.5, 0.5);
		figSkybox.prisma2(idTextura_azulm, idTextura_azulm);
	glPopMatrix();

	//Baño 13
	glPushMatrix();
		glTranslatef(5.0f, 3.0f, 85.0f);
		glScalef(3.0, 6.0, 3.0);
		figSkybox.prisma2(idTextura_lad, idTextura_lad);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(5.0f, 2.5f, 83.25f);
		glScalef(2.5, 5.5, 0.5);
		figSkybox.prisma2(idTextura_azulm, idTextura_azulm);
	glPopMatrix();

	//Baño 14
	glPushMatrix();
		glTranslatef(10.0f, 3.0f, 85.0f);
		glScalef(3.0, 6.0, 3.0);
		figSkybox.prisma2(idTextura_lad, idTextura_lad);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(10.0f, 2.5f, 83.25f);
		glScalef(2.5, 5.5, 0.5);
		figSkybox.prisma2(idTextura_azulm, idTextura_azulm);
	glPopMatrix();

	//Baño 15
	glPushMatrix();
		glTranslatef(15.0f, 3.0f, 85.0f);
		glScalef(3.0, 6.0, 3.0);
		figSkybox.prisma2(idTextura_lad, idTextura_lad);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(15.0f, 2.5f, 83.25f);
		glScalef(2.5, 5.5, 0.5);
		figSkybox.prisma2(idTextura_azulm, idTextura_azulm);
	glPopMatrix();

	//Baño 16
	glPushMatrix();
		glTranslatef(25.0f, 3.0f, 85.0f);
		glScalef(3.0, 6.0, 3.0);
		figSkybox.prisma2(idTextura_lad, idTextura_lad);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(25.0f, 2.5f, 83.25f);
		glScalef(2.5, 5.5, 0.5);
		figSkybox.prisma2(idTextura_azulm, idTextura_azulm);
	glPopMatrix();

	//Baño 17
	glPushMatrix();
		glTranslatef(30.0f, 3.0f, 85.0f);
		glScalef(3.0, 6.0, 3.0);
		figSkybox.prisma2(idTextura_lad, idTextura_lad);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(30.0f, 2.5f, 83.25f);
		glScalef(2.5, 5.5, 0.5);
		figSkybox.prisma2(idTextura_azulm, idTextura_azulm);
	glPopMatrix();

	//Baño 18
	glPushMatrix();
		glTranslatef(35.0f, 3.0f, 85.0f);
		glScalef(3.0, 6.0, 3.0);
		figSkybox.prisma2(idTextura_lad, idTextura_lad);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(35.0f, 2.5f, 83.25f);
		glScalef(2.5, 5.5, 0.5);
		figSkybox.prisma2(idTextura_azulm, idTextura_azulm);
	glPopMatrix();

	//Baño 19
	glPushMatrix();
		glTranslatef(-5.0f, 3.0f, 85.0f);
		glScalef(3.0, 6.0, 3.0);
		figSkybox.prisma2(idTextura_lad, idTextura_lad);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-5.0f, 2.5f, 83.25f);
		glScalef(2.5, 5.5, 0.5);
		figSkybox.prisma2(idTextura_azulm, idTextura_azulm);
	glPopMatrix();

	//Baño 20
	glPushMatrix();
		glTranslatef(-10.0f, 3.0f, 85.0f);
		glScalef(3.0, 6.0, 3.0);
		figSkybox.prisma2(idTextura_lad, idTextura_lad);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-10.0f, 2.5f, 83.25f);
		glScalef(2.5, 5.5, 0.5);
		figSkybox.prisma2(idTextura_azulm, idTextura_azulm);
	glPopMatrix();

	//Baño 21
	glPushMatrix();
		glTranslatef(-15.0f, 3.0f, 85.0f);
		glScalef(3.0, 6.0, 3.0);
		figSkybox.prisma2(idTextura_lad, idTextura_lad);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-15.0f, 2.5f, 83.25f);
		glScalef(2.5, 5.5, 0.5);
		figSkybox.prisma2(idTextura_azulm, idTextura_azulm);
	glPopMatrix();

	//Baño 22
	glPushMatrix();
		glTranslatef(-25.0f, 3.0f, 85.0f);
		glScalef(3.0, 6.0, 3.0);
		figSkybox.prisma2(idTextura_lad, idTextura_lad);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-25.0f, 2.5f, 83.25f);
		glScalef(2.5, 5.5, 0.5);
		figSkybox.prisma2(idTextura_azulm, idTextura_azulm);
	glPopMatrix();

	//Baño 23
	glPushMatrix();
		glTranslatef(-30.0f, 3.0f, 85.0f);
		glScalef(3.0, 6.0, 3.0);
		figSkybox.prisma2(idTextura_lad, idTextura_lad);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-30.0f, 2.5f, 83.25f);
		glScalef(2.5, 5.5, 0.5);
		figSkybox.prisma2(idTextura_azulm, idTextura_azulm);
	glPopMatrix();

	//Baño 24
	glPushMatrix();
		glTranslatef(-35.0f, 3.0f, 85.0f);
		glScalef(3.0, 6.0, 3.0);
		figSkybox.prisma2(idTextura_lad, idTextura_lad);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-35.0f, 2.5f, 83.25f);
		glScalef(2.5, 5.5, 0.5);
		figSkybox.prisma2(idTextura_azulm, idTextura_azulm);
	glPopMatrix();
}

void Puestos() {
			//CARPA
			glPushMatrix();
				glTranslatef(-50.0f, 1.0f, -50.0f);
				glScalef(4.0, 4.0, 4.0);
				Carpa();
			glPopMatrix();

			//Puesto Splash
			glPushMatrix();
				glTranslatef(-30.0f, 4.0f, 15.0f);
				glScalef(0.80, 0.80, 0.80);
				Splash();
			glPopMatrix();

			//Puesto de Aros
			glPushMatrix();
				glTranslatef(-25.0f, 2.0f, 5.0f);
				glScalef(0.5, 0.5, 0.5);
				Puesto_A();
			glPopMatrix();

			//PUESTO BLANCO
			glPushMatrix();
				glTranslatef(-30.0, 0.0, 25.0);
				glScalef(0.04, 0.04, 0.04);
				Puesto.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			//Puesto de Aros
			glPushMatrix();
				glTranslatef(25.0f, 2.0f, 5.0f);
				glScalef(0.5, 0.5, 0.5);
				Puesto_A();
			glPopMatrix();

			//Inflable
			glPushMatrix();
				glTranslatef(50.0f, 1.75f, 16.0f);
				glScalef(0.45, 0.45, 0.45);
				Inflable();
			glPopMatrix();
			
			//PUESTO BLANCO
			glPushMatrix();
				glTranslatef(70.0, 0.0, 25.0);
				glScalef(0.04, 0.04, 0.04);
				Puesto.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			//PUESTO BLANCO
			glPushMatrix();
				glTranslatef(30.0, 0.0, 45.0);
				glScalef(0.04, 0.04, 0.04);
				Puesto.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			//PUESTO BLANCO
			glPushMatrix();
				glTranslatef(-70.0, 0.0, 25.0);
				glScalef(0.04, 0.04, 0.04);
				Puesto.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			//PUESTO BLANCO
			glPushMatrix();
				glTranslatef(-30.0, 0.0, 45.0);
				glScalef(0.04, 0.04, 0.04);
				Puesto.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			//PUESTO BLANCO
			glPushMatrix();
				glTranslatef(70.0, 0.0, -25.0);
				glScalef(0.04, 0.04, 0.04);
				Puesto.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			//PUESTO BLANCO
			glPushMatrix();
				glTranslatef(30.0, 0.0, -45.0);
				glScalef(0.04, 0.04, 0.04);
				Puesto.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			//PUESTO BLANCO
			glPushMatrix();
				glTranslatef(-70.0, 0.0, -25.0);
				glScalef(0.04, 0.04, 0.04);
				Puesto.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			//PUESTO BLANCO
			glPushMatrix();
				glTranslatef(-30.0, 0.0, -45.0);
				glScalef(0.04, 0.04, 0.04);
				Puesto.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();
}

void Moviliario() {
			//CAMINOS
			glPushMatrix();
				Caminos();
			glPopMatrix();

			//Mesas
			glPushMatrix();
				Mesas();
			glPopMatrix();

			//BANCAS
			glPushMatrix();
				Bancas();
			glPopMatrix();

			//CONTENEDORES
			glPushMatrix();
				Contenedores();
			glPopMatrix();

			//Baños
			glPushMatrix();
				Baños();
			glPopMatrix();

			//Dibujar Elicoctero
			glPushMatrix();
				glTranslatef(-60.0, 4.5, 60.0);
				glRotatef(giraRotaElic, 0.0, 1.0, 0.0);
				glScalef(1.0, 1.0, 1.0);
				Elicoctero.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			//base de aterrisaje
			glPushMatrix();
				glTranslatef(-60.0, 0.0, 60);
				glScalef(30.0, 0.75, 30.0);
				figSkybox.prisma2(idTextura_suelo, idTextura_suelo);
			glPopMatrix();
			
			//Carreta
			glPushMatrix();
				glTranslatef(35.0, 0.0, -10.0);
				glScalef(0.02, 0.02, 0.02);
				Carreta.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();
}

void Animales() {	
			//Oso
			glPushMatrix();
				glTranslatef(-82.0, 0.0, -82.0);
				glScalef(1.0, 1.0, 1.0);
				Oso.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			//Dibujar Aguila
			glPushMatrix();
				glTranslatef(-80.0, 5.0, -80.0);
				glScalef(1.0, 1.0, 1.0);
				Aguila.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			//Dibujar Triangulo de Aguilas
			glPushMatrix();
				glTranslatef(-100.0, 15.0, -85.0);
				glScalef(2.0, 2.0, 2.0);
				Aguila.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-95.0, 15.0, -90.0);
				glScalef(2.0, 2.0, 2.0);
				Aguila.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-105.0, 15.0, -90.0);
				glScalef(2.0, 2.0, 2.0);
				Aguila.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			//Dibujar Triangulo de Aguilas
			glPushMatrix();
				glTranslatef(10.0, 10.0, 15.0);
				glScalef(1.0, 1.0, 1.0);
				Aguila.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(12.0, 10.0, 12.0);
				glScalef(1.0, 1.0, 1.0);
				Aguila.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(8.0, 10.0, 12.0);
				glScalef(1.0, 1.0, 1.0);
				Aguila.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			//Dibujar Triangulo de Aguilas
			glPushMatrix();
				glTranslatef(50.0, 10.0, 35.0);
				glScalef(1.0, 1.0, 1.0);
				Aguila.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(52.0, 10.0, 32.0);
				glScalef(1.0, 1.0, 1.0);
				Aguila.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(48.0, 10.0, 32.0);
				glScalef(1.0, 1.0, 1.0);
				Aguila.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			//Dibujar Triangulo de Aguilas
			glPushMatrix();
				glTranslatef(-50.0, 10.0, -22.0);
				glScalef(1.0, 1.0, 1.0);
				Aguila.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-52.0, 10.0, -25.0);
				glScalef(1.0, 1.0, 1.0);
				Aguila.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-48.0, 10.0, -25.0);
				glScalef(1.0, 1.0, 1.0);
				Aguila.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			//Dibujar Triangulo de Aguilas
			glPushMatrix();
				glTranslatef(-10.0, 10.0, -62.0);
				glScalef(1.0, 1.0, 1.0);
				Aguila.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-12.0, 10.0, -65.0);
				glScalef(1.0, 1.0, 1.0);
				Aguila.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-8.0, 10.0, -65.0);
				glScalef(1.0, 1.0, 1.0);
				Aguila.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			//Dibujar Triangulo de Aguilas
			glPushMatrix();
				glTranslatef(10.0, 10.0, -32.0);
				glScalef(1.0, 1.0, 1.0);
				Aguila.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(12.0, 10.0, -35.0);
				glScalef(1.0, 1.0, 1.0);
				Aguila.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(8.0, 10.0, -35.0);
				glScalef(1.0, 1.0, 1.0);
				Aguila.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			//Dibujar Triangulo de Aguilas
			glPushMatrix();
				glTranslatef(0.0, 10.0, 32.0);
				glScalef(1.0, 1.0, 1.0);
				Aguila.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(2.0, 10.0, 30.0);
				glScalef(1.0, 1.0, 1.0);
				Aguila.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-2.0, 10.0, 30.0);
				glScalef(1.0, 1.0, 1.0);
				Aguila.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			//Perro
			glPushMatrix();
				glTranslatef(-5.0, 0.0, 25.0);
				glScalef(1.0, 1.0, 1.0);
				Perro.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			//Perro
			glPushMatrix();
				glTranslatef(5.0, 0.0, 45.0);
				glScalef(1.0, 1.0, 1.0);
				Perro.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			//Perro
			glPushMatrix();
				glTranslatef(-5.0, 0.0, 65.0);
				glScalef(1.0, 1.0, 1.0);
				Perro.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			//Perro
			glPushMatrix();
				glTranslatef(-25.0, 0.0, 65.0);
				glScalef(1.0, 1.0, 1.0);
				Perro.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			//Perro
			glPushMatrix();
				glTranslatef(-5.0, 0.0, -25.0);
				glScalef(1.0, 1.0, 1.0);
				Perro.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			//Perro
			glPushMatrix();
				glTranslatef(5.0, 0.0, -45.0);
				glScalef(1.0, 1.0, 1.0);
				Perro.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			//Perro
			glPushMatrix();
				glTranslatef(-5.0, 0.0, -65.0);
				glScalef(1.0, 1.0, 1.0);
				Perro.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			//Perro
			glPushMatrix();
				glTranslatef(-25.0, 0.0, -65.0);
				glScalef(1.0, 1.0, 1.0);
				Perro.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			//Perro
			glPushMatrix();
				glTranslatef(25.0, 0.0, -65.0);
				glScalef(1.0, 1.0, 1.0);
				Perro.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			//Perro
			glPushMatrix();
				glTranslatef(25.0, 0.0, 65.0);
				glScalef(1.0, 1.0, 1.0);
				Perro.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			//Perro
			glPushMatrix();
				glTranslatef(-45.0, 0.0, -25.0);
				glScalef(1.0, 1.0, 1.0);
				Perro.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			//Perro
			glPushMatrix();
				glTranslatef(-45.0, 0.0, 25.0);
				glScalef(1.0, 1.0, 1.0);
				Perro.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();
}

void Juegos() {
			//JUEGO MECANICO UNO (PULPO)
			glPushMatrix();
				glTranslatef(0.0f, 4.0f, 0.0f);
				glScalef(1.0, 1.0, 1.0);
				Pulpo();
			glPopMatrix();

			//JUEGO MECANICO DOS (RUEDA DE LA FORTUNA)
			glPushMatrix();
				glTranslatef(60.0f, 8.0f, -60.0f);
				glScalef(2.0, 2.0, 2.0);
				Rueda_Foirtuna();
			glPopMatrix();

			//JUEGO MECANICO TRES (CILLAS VOLADORAS)
			glPushMatrix();
				glTranslatef(-30.0f, 0.0f, -10.0f);
				glScalef(1.0, 1.0, 1.0);
				cillas_voladoras();
			glPopMatrix();

			//JUEGO MECANICO CUATRO (CANOA)
			glPushMatrix();
				glTranslatef(-50.0f, 0.0f, -10.0f);
				glScalef(1.0, 1.0, 1.0);
				Canoa();
			glPopMatrix();
}

void Arboles() {
			//Pinos
			glPushMatrix();
				glTranslatef(-100.0, transY, -100.0f);
				dibuja_arbol(5.6, 6.0, Textura_pino.GLindex);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-90.0, transY, -95.0f);
				dibuja_arbol(5.6, 6.0, Textura_pino.GLindex);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-80.0, transY, -100.0f);
				dibuja_arbol(5.6, 6.0, Textura_pino.GLindex);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-90.0, transY, -110.0f);
				dibuja_arbol(5.6, 6.0, Textura_pino.GLindex);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-80.0, transY, -110.0f);
				dibuja_arbol(5.6, 6.0, Textura_pino.GLindex);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-100.0, transY, -110.0f);
				dibuja_arbol(5.6, 6.0, Textura_pino.GLindex);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-110.0, transY, -110.0f);
				dibuja_arbol(5.6, 6.0, Textura_pino.GLindex);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-70.0, transY, -110.0f);
				dibuja_arbol(5.6, 6.0, Textura_pino.GLindex);
			glPopMatrix();

			//Arboles
			glPushMatrix();
				glTranslatef(30.0, 0.0, 30.0);
				glScalef(1.0, 1.0, 1.0);
				Arbol.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(30.0, 0.0, 70.0);
				glScalef(1.0, 1.0, 1.0);
				Arbol.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-30.0, 0.0, 30.0);
				glScalef(1.0, 1.0, 1.0);
				Arbol.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-30.0, 0.0, 70.0);
				glScalef(1.0, 1.0, 1.0);
				Arbol.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(70.0, 0.0, 30.0);
				glScalef(1.0, 1.0, 1.0);
				Arbol.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(70.0, 0.0, -30.0);
				glScalef(1.0, 1.0, 1.0);
				Arbol.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-70.0, 0.0, 30.0);
				glScalef(1.0, 1.0, 1.0);
				Arbol.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-70.0, 0.0, -30.0);
				glScalef(1.0, 1.0, 1.0);
				Arbol.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(30.0, 0.0, -30.0);
				glScalef(1.0, 1.0, 1.0);
				Arbol.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(30.0, 0.0, -70.0);
				glScalef(1.0, 1.0, 1.0);
				Arbol.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-30.0, 0.0, -30.0);
				glScalef(1.0, 1.0, 1.0);
				Arbol.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-30.0, 0.0, -70.0);
				glScalef(1.0, 1.0, 1.0);
				Arbol.GLrender(NULL, _SHADED, 1.0);
			glPopMatrix();
}

void dibujar ( void )   // Creamos la funcion donde se dibuja
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Limpiamos pantalla y Depth Buffer
	
	glLoadIdentity();
	glTranslatef(transX, transY, transZ);
	glRotatef(angleY, 0.0, 1.0, 0.0);
	glRotatef(angleX, 1.0, 0.0, 0.0);
	
	glPushMatrix();
	
		glRotatef(g_lookupdown,1.0f,0,0);

		gluLookAt(	objCamera.mPos.x,  objCamera.mPos.y,  objCamera.mPos.z,	
					objCamera.mView.x, objCamera.mView.y, objCamera.mView.z,	
					objCamera.mUp.x,   objCamera.mUp.y,   objCamera.mUp.z);
	
		glPushMatrix();		

			glPushMatrix(); //Creamos esenario
				glDisable(GL_LIGHTING);
				figSkybox.skyboxH(240.0, 240.0, 240.0,textSkyboxFrontal.GLindex, textSkyboxAtras.GLindex, textSkyboxIzquierda.GLindex, textSkyboxDerecha.GLindex, textSkyboxArriba.GLindex);
				glEnable(GL_LIGHTING);
			glPopMatrix();
		
			//Dibuja piso
			glPushMatrix();
			glTranslatef(0.0f, 0.0f, 0.0f);
				ciudad();
			glPopMatrix();

			//Dibujar objetos
			Puestos();
			Moviliario();
			Animales();
			Juegos();
			Arboles();

			

			/*
			//dibujar puerta de madera
			glPushMatrix();
				//mover el eje para rotar la puerta
				glTranslatef(5.0, -500.0, -10.0);
				glRotatef(-ang_rot_puerta, 0.0, 1.0, 0.0);

				glTranslatef(100.0, 100.0, 0.0);
				puerta_madera(100.0, 200.0, 10.0);

			glPopMatrix();

			glPushMatrix();
				//mover el eje para rotar la puerta
				glTranslatef(-5.0, -500.0, -10.0);
				glRotatef(ang_rot_puerta, 0.0, 1.0, 0.0);

				glTranslatef(100.0, 100.0, 0.0);
				puerta_madera(100.0, 200.0, 10.0);
			glPopMatrix();


			glPushMatrix();
			//generador idraulico
				glTranslatef(15.0, 2.0, 15.0f);
				glScalef(0.5,0.5,0.5);
				Rueda_Agua();
			glPopMatrix();
			*/

		glPopMatrix();
	glPopMatrix();
	

	glFlush();
	glutSwapBuffers ( );

}

void remodelar ( int width , int height )
{
	if (height==0)	// Prevenir división entre cero
	{
		height=1;
	}

	glViewport(0,0,width,height);	

	glMatrixMode(GL_PROJECTION);	// Seleccionamos Projection Matrix
	glLoadIdentity();

	// Tipo de Vista
	glFrustum (-0.1, 0.1,-0.1, 0.1, 0.1, 1000.0);

	glMatrixMode(GL_MODELVIEW);		// Seleccionamos Modelview Matrix
	glLoadIdentity();
}

void teclado ( unsigned char key, int x, int y )
{
	switch ( key ) {
		case 'w': case 'W':
			objCamera.Move_Camera( CAMERASPEED+0.2 );
			break;

		case 's': case 'S':
			objCamera.Move_Camera(-(CAMERASPEED+0.2));
			break;

		case 'a': case 'A':
			objCamera.Strafe_Camera(-(CAMERASPEED+0.4));
			break;

		case 'd': case 'D':
			objCamera.Strafe_Camera( CAMERASPEED+0.4 );
			break;

		// Animacion de la puerta
		case 'p':
			if (ang_rot_puerta < 90 && ang_rot_puerta >= -90) {
				ang_rot_puerta = ang_rot_puerta + 15.0;
			}
			break;
		case 'P':
			if (ang_rot_puerta <= 90 && ang_rot_puerta > -90) {
				ang_rot_puerta = ang_rot_puerta - 15;
			}
			break;

		//teclas para activar sillas
		case 'z': case 'Z':
			Activa_sillas ^= true; //Activamos/desactivamos la nimacion
			movKit = 0.0f;
			engine->play2D(audioPikachu);
			break;

			//teclas para activar pulpo
		case 'x': case 'X':
			Activa_Pulpo ^= true; //Activamos/desactivamos la nimacion
			engine->play2D(audioPikachu);
			break;

			//teclas para activar rueda
		case 'c': case 'C':
			Activa_Rueda ^= true; //Activamos/desactivamos la nimacion
			engine->play2D(audioPikachu);
			break;

			//teclas para activar canoa
		case 'v': case 'V':
			Activa_Canoa ^= true; //Activamos/desactivamos la nimacion
			engine->play2D(audioPikachu);
			break;

		case 27:  //Si presiona tecla ESC (ASCII 27) sale
			exit ( 0 );
			break;        
		default:  //Si es cualquier otra tecla no hace nada
			break;
  }

  glutPostRedisplay();
}

void teclasFlechasFunc ( int a_keys, int x, int y )
{
  switch ( a_keys ) {


	case GLUT_KEY_PAGE_UP:	//tecla avance de página
		objCamera.UpDown_Camera(CAMERASPEED);
		break;

	case GLUT_KEY_PAGE_DOWN:	//tecla retroceso de página
		objCamera.UpDown_Camera(-CAMERASPEED);
		break;

    case GLUT_KEY_UP:	//tecla ARRIBA
		g_lookupdown -= 1.0f;
		break;

    case GLUT_KEY_DOWN:	//tecla ABAJO
		g_lookupdown += 1.0f;
		break;

	case GLUT_KEY_LEFT:	//tecla izquierda
		objCamera.Rotate_View(-CAMERASPEED);
		break;

	case GLUT_KEY_RIGHT:	//tecla derecha
		objCamera.Rotate_View( CAMERASPEED);
		break;
		
	//teclas para cámara
	case GLUT_KEY_F1:
		//cámara en el juego del pulpo
		objCamera.Position_Camera(0, 2.5f, 3,     0, 2.5f, 0,    0, 1, 0);
		break;

	case GLUT_KEY_F2:
		//cámara en el juego de las sillas voladoras
		objCamera.Position_Camera(-30, 2.5f, 0,     0, 2.5f, 0,   0, 1, 0);
		break;

	case GLUT_KEY_F3:
		//cámara en el plano superior
		objCamera.Position_Camera(25.0, 15.0f, 0,    25, 0, 0,    1, 0, 0);
		break;
	
	case GLUT_KEY_F4:
		//cámara en el Elicoctero
		objCamera.Position_Camera(-90.0, 2.5f, 100,   0, 2.5f, 0,   0, 1, 0);
		break;
		
	case GLUT_KEY_F6:
		//cámara en la rueda de la fortuna
		objCamera.Position_Camera(60.0, 2.5f, -40,   0, 2.5f, 0,   0, 1, 0);
		break;

	case GLUT_KEY_F7:
		//cámara en el bosque
		objCamera.Position_Camera(-80.0, 2.5f, -80,   0, 2.5f, 0,   0, 1, 0);
		break;

    default:
		break;
  }
  glutPostRedisplay();
}

int main ( int argc, char** argv )   // Main Function
{
	//inicializa GLUT con el sistema de ventanas pasando los argumentos del main
	glutInit(&argc, argv);
	//Buffer simple para dibujar
	//Colores RGB y alpha
	//Buffer de profundidad
	glutInitDisplayMode (GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	//Define ventana de 1000 pixeles de ancho por 768 de alto
	glutInitWindowSize(1000, 768);
	//Posiciona la ventana en el centro de la pantaya
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - 1000) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - 768) / 2);
	//Crea y abre la ventana y recibe el nombre que va en su barra de título
	glutCreateWindow(argv[1]);
	//Llamada a función propia para inicializar estados de opengl
	inicializar();
	//Llamada a la función a ser dibujada y redibujada
	glutDisplayFunc(dibujar);
	//Llamada a función para cambio de tamaño de ventana
	glutReshapeFunc(remodelar);
	//Lamada a función que maneja eventos del teclado con teclas normales
	glutKeyboardFunc(teclado);
	//Lamada a función que maneja eventos del teclado con teclas de flechas de dirección y f1, f2 .. fn
	glutSpecialFunc(teclasFlechasFunc);
	//Llama a función que ace la animación
	glutIdleFunc(anima);
	//Llamada a función que cede el control a GLUT y procesa eventos de ventana, ratón
	glutMainLoop();
	
	//termina la ejecución devolviendo cero
	return 0;
	
}
