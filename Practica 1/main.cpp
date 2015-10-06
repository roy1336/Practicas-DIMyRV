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

using namespace std;

#define VERTICE 0
#define TEXTURA 1
#define NORMAL 2

struct vec2 {
	float x, y;
};
struct vec3 {
	float x, y, z;
};

vector<string> splitStr(string, string);
vector<string> splitStr(string, char);

class OBJ {
public:
	vector<vector <array<int,3>>> temp_f;
	vector<vec3> temp_v;
	vector<vec3> temp_vt;
	vector<vec3> temp_vn;
	vector<string> use_mat;
	string mat;

	bool lectorArchivo(char *ruta);
	void dibujaOBJ();
	void printOBJ();
};

bool OBJ::lectorArchivo(char *ruta) {
	FILE *archivo;
	char linea[64];
	vector<string> tokens;
	char keyword[64];
	archivo = fopen(ruta, "r");
	// Abrimos el archivo .obj
	if ((archivo) == NULL) {
		cout << "No se pudo leer el archivo.\n";
		return false;
	}
	else {
		while (!feof(archivo)) {
			fscanf(archivo, "%s", keyword);
			// Vertices
			if (strcmp(keyword, "v") == 0) {
				vec3 vertice_aux;
				fgets(linea, 64, archivo);
				tokens.swap(splitStr(linea, ' '));
				int i = 0, size;
				size = tokens.size();
				if (i < size) {
					while (tokens[i].length() == 0) {
						i++;
						if (i >= size) {
							break;
						}
					}
					if (i < size) {
						vertice_aux.x = stof(tokens[i]);
						i++;
						if (i < size) {
							while (tokens[i].length() == 0) {
								i++;
								if (i >= size) {
									break;
								}
							}
							if (i < size) {
								vertice_aux.y = stof(tokens[i]);
								i++;
								if (i < size) {
									while (tokens[i].length() == 0) {
										i++;
										if (i >= size) {
											break;
										}
									}
									vertice_aux.z = stof(tokens[i]);
								}
							}
						}
					}
				}
				tokens.clear();
				temp_v.push_back(vertice_aux);
			}

			// Texturas
			else if (strcmp(keyword, "vt") == 0) {
				vec3 textura_aux;
				fgets(linea, 64, archivo);
				tokens.swap(splitStr(linea, ' '));
				int i = 0, size;
				size = tokens.size();
				if (i < size) {
					while (tokens[i].length() == 0) {
						i++;
						if (i >= size) {
							break;
						}
					}
					if (i < size) {
						textura_aux.x = stof(tokens[i]);
						i++;
						if (i < size) {
							while (tokens[i].length() == 0) {
								i++;
								if (i >= size) {
									break;
								}
							}
							if (i < size) {
								textura_aux.y = stof(tokens[i]);
								i++;
								if (i < size) {
									while (tokens[i].length() == 0) {
										i++;
										if (i >= size) {
											break;
										}
									}
									textura_aux.z = stof(tokens[i]);
								}
							}
						}
					}
				}
				
				tokens.clear();
				temp_vt.push_back(textura_aux);
			}

			// Normales
			else if (strcmp(keyword, "vn") == 0) {
				vec3 normal_aux;
				fgets(linea, 64, archivo);
				tokens.swap(splitStr(linea, ' '));
				int i = 0, size;
				size = tokens.size();
				if (i < size) {
					while (tokens[i].length() == 0) {
						i++;
						if (i >= size) {
							break;
						}
					}
					if (i < size) {
						normal_aux.x = stof(tokens[i]);
						i++;
						if (i < size) {
							while (tokens[i].length() == 0) {
								i++;
								if (i >= size) {
									break;
								}
							}
							if (i < size) {
								normal_aux.y = stof(tokens[i]);
								i++;
								if (i < size) {
									while (tokens[i].length() == 0) {
										i++;
										if (i >= size) {
											break;
										}
									}
									normal_aux.z = stof(tokens[i]);
								}
							}
						}
					}
				}
				tokens.clear();
				temp_vn.push_back(normal_aux);
			}

			//////////////////// Caras//////////////////////////////////////////////////////////
			else if (strcmp(keyword, "f") == 0) {
				int size, _size;
				vector<array<int,3>> tokens_int;
				vector<string> tokens2;
				tokens = vector<string>();

				fgets(linea, 64, archivo);
				tokens.swap(splitStr(linea, ' '));

				size = tokens.size();
				for (int i = 0;i < size;i++) {
					array<int, 3> temp_cara;
					if ((int)tokens[i].find('/') > -1) {
						tokens2.swap(splitStr(tokens[i], '/'));
						//_size = tokens2.size();
						for (int j = 0; j < 3;j++) {
							if (tokens2[j].length() > 0) {
								temp_cara[j] = stoi(tokens2[j]);
							}
							else {
								temp_cara[j] = 0;
							}
						}
						tokens_int.push_back(temp_cara);
					}
					else if (tokens[i].length() > 0) {
						tokens2.swap(splitStr(tokens[i], '/'));
						_size = tokens2.size();
						for (int j = 0; j < _size;j++) {
							if (tokens2[j].length() > 0) {
								temp_cara[j] = stoi(tokens2[j]);
							}
							else {
								temp_cara[j] = 0;
							}
						}
						temp_cara[1] = 0;
						temp_cara[2] = 0;
						tokens_int.push_back(temp_cara);
					}
				}
				temp_f.push_back(tokens_int);
				
				//cout << temp_f.at(0).at(0) << "\n";
			}
			/////////////////////////////////////////////////////////////////////////////////			
			// Libreria de materiales
			else if (strcmp(keyword, "mtllib") == 0) {
				fgets(linea, 64, archivo);
				tokens = splitStr(linea, ' ');
				int size = tokens.size();
				for (int i = 0;i < size;i++) {
					if (tokens[i].length()!= 0) {
						mat = tokens[i];
						i = size;
					}
				}
				if (strstr(linea, ".mtl") == NULL) {
					cout << "Archivo de materiales no valido.\n";
					//return false;
				}

				FILE *archivo_material;
				archivo_material = fopen(mat.c_str(), "r");
				// Abrimos el archivo .obj
				if ((archivo_material) == NULL) {
					cout << "No se encontro el archivo:" << mat << "\n";
				}
				else {
					fclose(archivo_material);
				}

			}
			// Uso de materiales 
			else if (strcmp(keyword, "usemtl") == 0) {
				char aux_mat[64];
				fgets(aux_mat, 64, archivo);
				use_mat.push_back(aux_mat);
			}
			else if (strcmp(keyword, "#") == 0 || strcmp(keyword, "g") == 0 || strcmp(keyword, "s") == 0) {
				fgets(linea, 64, archivo);
			}
			else {
				//return false;
			}
		}
	}
	fclose(archivo);
	return true;
}

void OBJ::printOBJ() {
	int size, _size;
	//vector<vec3> temp_v;
	cout << "Lista de vertices: " << endl;
	size = temp_v.size();
	for (int i = 0; i < size; i++) {
		cout << " v[" << i + 1 << "]:  " << temp_v[i].x << ", " << temp_v[i].y << ", " << temp_v[i].z << endl;
	}

	//vector<vec3> temp_vt;
	cout << "\nLista de coordenadas de textura: " << endl;
	size = temp_vt.size();
	for (int i = 0; i < size; i++) {
		cout << " vt[" << i + 1 << "]:  " << temp_vt[i].x << ", " << temp_vt[i].y << ", " << temp_vt[i].z << endl;
	}

	//vector<vec3> temp_vn;
	cout << "\nLista de vectores normales: " << endl;
	size = temp_vn.size();
	for (int i = 0; i < size; i++) {
		cout << " vn[" << i + 1 << "]:  " << temp_vn[i].x << ", " << temp_vn[i].y << ", " << temp_vn[i].z << endl;
	}

	//vector<char *> use_mat;
	cout << "\nLista de materiales: " << endl;
	size = use_mat.size();
	for (int i = 0; i < size; i++) {
		cout << " mat[" << i + 1 << "]:  " << use_mat[i] << endl;
	}

	//char mat[64];
	cout << "\nArchivo de materiales: " << endl <<
		" " << mat << endl;

	//vector<vector <string>> temp_f;
	cout << "\nLista de Caras: " << endl;
	size = temp_f.size();
	for (int i = 0; i < size; i++) {
		_size = temp_f[i].size();
		cout << " f[" << i + 1 << "]:  ";
		for (int j = 0; j < _size; j++) {
			cout << temp_f[i][j][VERTICE] << "/" << temp_f[i][j][TEXTURA] << "/" << temp_f[i][j][NORMAL] << " ";
		}
		cout << endl;
	}
}

void OBJ::dibujaOBJ() {
	bool normal, text;
	int size,_size;
	glPushMatrix();
	size = temp_f.size();
	for (int i = 0; i < size; i++) {
		normal = false;
		text = false;
		glBegin(GL_POLYGON);
		glColor3f(1.0f, 0.0f, 0.0f);
		/*switch (i%3) {
		case 0:
			glColor3f(1.0f, 0.0f, 0.0f);
			break;
		case 1:
			glColor3f(0.0f, 1.0f, 0.0f);
			break;
		case 2:
			glColor3f(0.0f, 0.0f, 1.0f);
			break;
		}*/
		_size = temp_f[i].size();
		for (int k = 0; k < _size; k++) {
			//Dibuja Cara
			//Vector normal
			if (temp_f[i][k][NORMAL] > 0) {
				glNormal3f(temp_vn[temp_f[i][k][NORMAL] - 1].x, temp_vn[temp_f[i][k][NORMAL] - 1].y, temp_vn[temp_f[i][k][NORMAL] - 1].z);
			}
			else if (temp_f[i][k][NORMAL] < 0) {
				int num_n = temp_vn.size();
				glNormal3f(temp_vn[num_n + temp_f[i][k][NORMAL]].x, temp_vn[num_n + temp_f[i][k][NORMAL]].y, temp_vn[num_n + temp_f[i][k][NORMAL]].z);
			}
			//Coordenadas de txtura
			if (temp_f[i][k][TEXTURA]>0) {
					glTexCoord2f(temp_vt[temp_f[i][k][TEXTURA] - 1].x, temp_vt[temp_f[i][k][TEXTURA] - 1].y);
			}
			else if (temp_f[i][k][TEXTURA] > 0) {
				int num_t = temp_vt.size();
				glTexCoord2f(temp_vt[num_t + temp_f[i][k][TEXTURA]].x, temp_vt[num_t + temp_f[i][k][TEXTURA]].y);
			}
			//Vertice
			if (temp_f[i][k][VERTICE]>0) {
				glVertex3f(temp_v[temp_f[i][k][VERTICE] - 1].x, temp_v[temp_f[i][k][VERTICE] - 1].y, temp_v[temp_f[i][k][VERTICE] - 1].z);
			}
			else if (temp_f[i][k][VERTICE]<0) {
				int num_v = temp_v.size();
				glVertex3f(temp_v[num_v + temp_f[i][k][VERTICE]].x, temp_v[num_v + temp_f[i][k][VERTICE]].y, temp_v[num_v + temp_f[i][k][VERTICE]].z);
			}
		}
		glEnd();
	}
	glPopMatrix();
}

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

	fileExists = objeto.lectorArchivo(estuche);
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