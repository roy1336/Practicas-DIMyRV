//C
#include <stdio.h>
#include <stdlib.h>
//C++
#include <iostream>
#include <vector>
#include <string>
#include <array>
//Glut openGL
#include <GL/glut.h>
//clase OBJ
#include <OBJ.h>
using namespace std;

OBJ objeto;
bool fileExists;
float posx = 0, posz = 0, posy = 0, escala = 0.1f, alpha = 0;

vector<string> splitStr(string str, string separator) {
	vector<string> cadenaDividida;
	int x;
	x = str.find(separator);

	while (x > -1) {
		cadenaDividida.push_back(str.substr(0, x));
		str = str.substr(x + 1);
		x = str.find(separator);
	}
	cadenaDividida.push_back(str.substr(0));
	
	return cadenaDividida;
}

vector<string> splitStr(string str, char separator) {
	vector<string> cadenaDividida;
	int x;
	x = str.find(separator);

	while (x > -1) {
		cadenaDividida.push_back(str.substr(0, x));
		str = str.substr(x + 1);
		x = str.find(separator);
	}
	cadenaDividida.push_back(str.substr(0));

	return cadenaDividida;
}

void InitGL()     // Inicializamos parametros
{
	//glShadeModel(GL_SMOOTH);							// Habilitamos Smooth Shading
	glClearColor(0.0f, 1.0f, 0.0f, 1.0f);				// Blanco de fondo
	glClearDepth(1.0f);									// Configuramos Depth Buffer
	glEnable(GL_DEPTH_TEST);							// Habilitamos Depth Testing
	glDepthFunc(GL_LEQUAL);								// Tipo de Depth Testing a realizar
														//glEnable ( GL_COLOR_MATERIAL );
														//glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	//GLfloat light_ambient[] =
	//{ 0.1, 0.1, 0.1, 1.0 };
	//GLfloat light_diffuse[] =
	//{ 1.0, 1.0, 1.0, 1.0 };
	//GLfloat light_specular[] =
	//{ 1.0, 1.0, 1.0, 1.0 };
	//GLfloat light_position[] =
	//{ -30.0, 20.0, 60.0, 0.0 };
	//
	//glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	//glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	//glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	//glEnable(GL_LIGHT0);
	//glDepthFunc(GL_LESS);
	//glEnable(GL_DEPTH_TEST);
	//glEnable(GL_LIGHTING);

	char *caja = "Modelos/box.obj";
	char *caterpillar = "Modelos/caterpillar.obj";
	char *cessna = "Modelos/cessna.obj";
	char *cubo = "Modelos/cube.obj";
	char *duque = "Modelos/Duke.obj";
	char *estuche = "Modelos/estuche_violin.obj";
	char *link = "Modelos/link.obj";
	char *intento = "Modelos/intento.obj";

	fileExists = objeto.lectorArchivo(link);
	if (fileExists) {
		cout << "Obj Cargado";
		//objeto.printOBJ();
	}

}

void display(void)   // Creamos la funcion donde se dibuja
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Limiamos pantalla y Depth Buffer
	glMatrixMode(GL_MODELVIEW);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLoadIdentity();
	
	gluLookAt(0, 0, -50.0, 0.0, 0.0, 50, 0.0, 1.0, 0.0);

	
	glTranslatef(posx,posy,posz);
	
	glScalef(escala, escala, escala);
	glRotatef(alpha, 0.0f, 1.0f, 0.0f);
	if (fileExists) {
		objeto.dibujaOBJ();
	}
	//glPointSize(10.0);
	//glLineWidth(5.0);
	//glBegin(GL_POINTS);
	//glBegin(GL_LINE_STRIP);
	glutSwapBuffers();
	//glFlush();
	// Swap The Buffers
	glutPostRedisplay();
}

void reshape(int width, int height)   // Creamos funcion Reshape
{
	if (height == 0)										// Prevenir division entre cero
	{
		height = 1;
	}

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);						// Seleccionamos Projection Matrix
	glLoadIdentity();

	// Tipo de Vista
	//glOrtho(-11,11,-11,14,0.1,2);
	//glOrtho(-20,15,-10,20,0.2,2);//left, right, bottom, top, near, far
	glFrustum(-1.0f, 1.0f, -1.0f, 1.0f, 10.0f, 150.0f);

	glMatrixMode(GL_MODELVIEW);							// Seleccionamos Modelview Matrix
														//glLoadIdentity();									
}

void keyboard(unsigned char key, int x, int y)  // Create Keyboard Function
{
	switch (key) {
	case 'a':        // Cuando Esc es presionado...
		posx += 1;
		break;
	case 'd':        // Cuando Esc es presionado...
		posx -= 1;
		break;
	case 'w':        // Cuando Esc es presionado...
		posy += 1;
		break;
	case 's':        // Cuando Esc es presionado...
		posy -= 1;
		break;
	case 'i':        // Cuando Esc es presionado...
		posz += 1;
		break;
	case 'k':        // Cuando Esc es presionado...
		posz -= 1;
		break;
	case '1':        // Cuando Esc es presionado...
		escala *= 0.7;
		break;
	case '2':        // Cuando Esc es presionado...
		escala *= 1.3;
		break;
	case '8':        // Cuando Esc es presionado...
		alpha-= 1.0;
		break;
	case '9':        // Cuando Esc es presionado...
		alpha += 1.0;
		break;
	case 27:        // Cuando Esc es presionado...
		exit(0);   // Salimos del programa
		break;
	default:        // Cualquier otra
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv)   // Main Function
{
	glutInit(&argc, argv); // Inicializamos OpenGL
						   //glutInitDisplayMode (GLUT_RGBA | GLUT_SINGLE | GLUT_DEPTH); // Display Mode (Clores RGB y alpha | Buffer Sencillo )
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // Display Mode (Clores RGB y alpha | Buffer Doble )
	glutInitWindowSize(800, 800);	// Tamaño de la Ventana
	glutInitWindowPosition(200, 10);	//Posicion de la Ventana
	glutCreateWindow("Practica 1: OBJ"); // Nombre de la Ventana
										 //glutFullScreen     ( );         // Full Screen
	InitGL();						// Parametros iniciales de la aplicacion
	glutDisplayFunc(display);  //Indicamos a Glut función de dibujo
	glutReshapeFunc(reshape);	//Indicamos a Glut función en caso de cambio de tamano
	glutKeyboardFunc(keyboard);	//Indicamos a Glut función de manejo de teclado
								//glutSpecialFunc     ( arrow_keys );	//Otras
								//glutIdleFunc		  ( display );	//Hace animacíon
	glutMainLoop();          // 

	return 0;
}