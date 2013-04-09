#include <stdio.h>
#include <stdlib.h>
#include <GL\glew.h>
#include <GL\glut.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "glsl.h"
#include "RK/matrix.hpp"
#include <time.h>

using namespace RK;

double dX = -0.9;
double dY = -0.9;

	

int numVertices = 0;
int numIndices = 0;



cwc::glShader *shader;
Matrix modelView;


void CreatePlanet(float x, float y, float z, float tx, float ty, float tz, float alphaX, float alphaY, float alphaZ)
{
	//modelView = Matrix(1.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,tx,ty,tz,1.0);
	
	modelView = Matrix(tx, 0.0f, 0.0f, 0.0f,
		               0.0f, ty, 0.0f, 0.0f,
					   0.0f, 0.0f, tz, 0.0f,
					   0.0f, 0.0f, 0.0f, 1.0f);

	modelView *= Matrix(Vector(x,y,z));

	//Rotation um die z-Achse
	modelView *=Matrix(cos(alphaZ), -sin(alphaZ), 0.0f, 0.0f,
					   sin(alphaZ), cos(alphaZ), 0.0f, 0.0f,
					   0.0f      , 0.0f      , 1.0f, 0.0f,
					   0.0f      ,0.0f       , 0.0f , 1.0f);
	//Rotation um die y-Achse
	

	modelView *=Matrix(cos(alphaY), 0.0f , sin(alphaY), 0.0f,
					   0.0f, 1.0f, 0.0f, 0.0f,
					   -sin(alphaY)    , 0.0f      , cos(alphaY), 0.0f,
					   0.0f      ,0.0f       , 0.0f , 1.0f);
	
	//Rotation um ide x-Achse
	
	modelView *=Matrix(1.0f, 0.0f, 0.0f, 0.0f,
					   0.0f, cos(alphaX),-sin(alphaX), 0.0f,
					   0.0f      , sin(alphaX) , cos(alphaX), 0.0f,
					   0.0f      ,0.0f       , 0.0f , 1.0f);
	

	shader->setUniformMatrix4fv("uni_modelView", 1, GL_FALSE, modelView.data);
	glDrawElements(GL_QUADS, numIndices, GL_UNSIGNED_INT, NULL);
}

void display() 
{
	
	int time;
	


	time=glutGet(GLUT_ELAPSED_TIME);

	

	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	
	
	
	CreatePlanet(0.0f,0.0f,time * 0.002 -15, 1.0f, 1.0f, 1.0f, 0, time * 0.00005, time * 0.002);
	CreatePlanet(2.0f,0.0f,-10.0f, 0.2f,0.2f, 0.2f, 0, 0, 0);

	

	glutSwapBuffers();
}




void mouseButton(int button, int state, int x, int y) {

	dX =  2.0*double(x)/800.0 - 1.0;
	dY = -2.0*double(y)/600.0 + 1.0;

	glutPostRedisplay();
}

void mouseMove(int x, int y) {

	dX =  2.0*double(x)/800.0 - 1.0;
	dY = -2.0*double(y)/600.0 + 1.0;

	glutPostRedisplay();
}

void idleFunction() {
	glutPostRedisplay();
}

void resizeFunction(int w, int h) 
{

	double radius = sqrt(3.0); 
	double viewAngle = M_PI / 3.0; 
	double distance = radius / sin(viewAngle/2.0);
	double front = distance - radius;
	double back  = distance + radius;
	double aspect = double(w)/double(h); //<<<<<<
	double top = front * tan(viewAngle/2.0);
	double bottom = -top;
	double left = top * aspect;
	double right = -left;

	/*
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(left, right, bottom, top, front, back);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslated(0.0, 0.0, -distance);*/

	glViewport(0,0,w,h);
}

void InitGeometrie()
{
	GLuint myBuffers[2] = {0,0};

	glGenBuffers(2, myBuffers);

	//Geometrie

	int thetaStep = 1;
	int phiStep = 1;
	int numFloatsPerVertex = 9;

	int numRows = (180/thetaStep);
	int numCols = (360/phiStep);
	numVertices = (numRows+1) * numCols;
	
	int numFloats = numVertices * numFloatsPerVertex; // Anzahl an Float-Werten
	float *buffer = new float[numFloats]; 
	int bufferSize = numFloats * sizeof(float); // Grösse in bytes

	int index = 0;
	float x,y,z;
	for(int theta = 0; theta <= 180; theta += thetaStep) {
		for(int phi = 0; phi < 360; phi += phiStep) {
			double phiR    = double(phi)*M_PI/180.0;
			double thetaR  = double(theta)*M_PI/180.0;

			x = sin(thetaR) * cos(phiR);
			y = sin(thetaR) * sin(phiR);
			z = cos(thetaR);

			buffer[index++] = (x+1.0)/2.0; // COLOR R
			buffer[index++] = (y+1.0)/2.0; // COLOR G
			buffer[index++] = (z+1.0)/2.0; // COLOR B
			buffer[index++] = x; // Normal X
			buffer[index++] = y; // Normal Y
			buffer[index++] = z; // Normal Z
			buffer[index++] = x; // Position X
			buffer[index++] = y; // Position Y
			buffer[index++] = z; // Position Z
		}
	}

	numIndices = numRows * numCols * 4;
	unsigned int *indexBuffer = new unsigned int[numIndices];
	int indexBufferSize = numIndices * sizeof(unsigned int);
	index = 0;

	for(int i = 0; i < (numRows); i++) {
		for(int j = 0; j < numCols; j++) {
			indexBuffer[index++] =  i    * numCols + j;
			indexBuffer[index++] =  i    * numCols + (j+1)%numCols;
			indexBuffer[index++] = (i+1) * numCols + (j+1)%numCols;
			indexBuffer[index++] = (i+1) * numCols + j;
		}
	}


	glBindBuffer(GL_ARRAY_BUFFER, myBuffers[0]);
	glBufferData(GL_ARRAY_BUFFER, bufferSize, buffer, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myBuffers[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBufferSize, indexBuffer, GL_STATIC_DRAW);

	delete [] buffer;
}

int main(int argc, char **argv) 
{
	glutInit(&argc, argv);

	
	



	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(800,800);
	glutInitWindowPosition(10,10);
	glutCreateWindow("OpenGL");
	


	glutDisplayFunc(display);
	glutMouseFunc(mouseButton); 
	glutMotionFunc(mouseMove);
	glutIdleFunc(idleFunction);
	glutReshapeFunc(resizeFunction);
	
	glutShowWindow();

	glewInit();

	cwc::glShaderManager shaderManager;
	
	shader = shaderManager.loadfromFile("../Planetensystem/shader/vertex.glsl", "../Planetensystem/shader/fragment.glsl");

	

	shader->BindAttribLocation(0, "att_vertex");
	shader->BindAttribLocation(1, "att_normal");
	shader->BindAttribLocation(2, "att_color");

	shader->begin();

	

	
	Matrix matrix = Matrix::Perspective(0.1,1000,800,800,50);

	shader->setUniformMatrix4fv("uni_perspective", 1, GL_FALSE, matrix.data);
	

	glEnable(GL_DEPTH_TEST);
	GLuint myArray;
	GLuint program = glCreateProgram();
	 
	glGenVertexArrays(1, &myArray); 
	glBindVertexArray(myArray);
	InitGeometrie();

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9*sizeof(float), (void*)(NULL + 6*sizeof(float)));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9*sizeof(float), (void*)(NULL + 3*sizeof(float)));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9*sizeof(float), NULL);
	
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glClearColor(0.5,0.5,1.0,0.0);

	glutMainLoop();
	
	return 0;
}


