#include <stdio.h>
#include <stdlib.h>
#include <GL\glew.h>
#include <GL\glut.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "glsl.h"
#include "RK/matrix.hpp"
#include <time.h>
#include "bmpLoad.h"

using namespace RK;

double dX = -0.9;
double dY = -0.9;
int numVertices = 0;
int numIndices = 0;

//TextureID's
GLuint textures[6];

GLuint buffer_vertices;
GLuint buffer_indices;

GLuint myBuffers[2] = {0,0};
GLuint myArray[2];

Matrix projectionMatrix;
Matrix ortho;

float cameraPosition[3] = {0, 0, -10};	 //camera ist an z-position 10
float cameraRotation[3] = {-15.f, 0.0f, 0.0f};
float Light[3] = {0.f, 0.0f, 0.0f}; //camera rotation in degree
cwc::glShader *shader;

//matrizen

Matrix Translation(float x, float y, float z)
{
	Matrix mTranslation;
	//mTranslation = Matrix(Vector(x,y,z));
	mTranslation = Matrix(1.0f, 0.0f, 0.0f, 0.0f,   0.0f, 1.0f, 0.0f, 0.0f,   0.0f, 0.0f, 1.0f, 0.0f,   x, y, z, 1.0);

	return mTranslation;
}


Matrix Scale(float tx, float ty, float tz)
{

	Matrix mScale;
		mScale = Matrix(tx, 0.0f, 0.0f, 0.0f,
		               0.0f, ty, 0.0f, 0.0f,
					   0.0f, 0.0f, tz, 0.0f,
					   0.0f, 0.0f, 0.0f, 1.0f);
		return mScale;
}


Matrix Rotation(float alphaXDegree, float alphaYDegree, float alphaZDegree)
{
	float alphaX = alphaXDegree/360.0f * 2 * M_PI;
	float alphaY = alphaYDegree/360.0f * 2 * M_PI;
	float alphaZ = alphaZDegree/360.0f * 2 * M_PI;

	//Rotation um die z-Achse
	Matrix mRotation;

	mRotation *=Matrix(cos(alphaZ), -sin(alphaZ), 0.0f, 0.0f,
					   sin(alphaZ), cos(alphaZ), 0.0f, 0.0f,
					   0.0f      , 0.0f      , 1.0f, 0.0f,
					   0.0f      ,0.0f       , 0.0f , 1.0f);
	//Rotation um die y-Achse
	

	mRotation *=Matrix(cos(alphaY), 0.0f , sin(alphaY), 0.0f,
					   0.0f, 1.0f, 0.0f, 0.0f,
					   -sin(alphaY)    , 0.0f      , cos(alphaY), 0.0f,
					   0.0f      ,0.0f       , 0.0f , 1.0f);
	
	//Rotation um ide x-Achse
	
	mRotation *=Matrix(1.0f, 0.0f, 0.0f, 0.0f,
					   0.0f, cos(alphaX),-sin(alphaX), 0.0f,
					   0.0f      , sin(alphaX) , cos(alphaX), 0.0f,
					   0.0f      ,0.0f       , 0.0f , 1.0f);

	return mRotation;
}

void CreatePlanet(Matrix modelMatrix)
{
	shader->begin();
	
	projectionMatrix = Matrix::Perspective(0.1,1000,800,800,50);
	//Matrix viewMatrix = Rotation(cameraRotation[0], cameraRotation[1], cameraRotation[2]) * Tranlation(cameraPosition[0], cameraPosition[1], cameraPosition[2]);
	Matrix viewMatrix = Rotation(cameraRotation[0], cameraRotation[1], cameraRotation[2]) * Translation(cameraPosition[0], cameraPosition[1], cameraPosition[2]);

	shader->setUniformMatrix4fv("uni_perspective", 1, GL_FALSE, projectionMatrix.data);
	shader->setUniformMatrix4fv("uni_view", 1, GL_FALSE, viewMatrix.data);
	shader->setUniformMatrix4fv("uni_model", 1, GL_FALSE, modelMatrix.data);
	shader->setUniform3fv("uni_light", 1, Light);
	shader->setUniform1i("uni_texture", 0);
	glDrawElements(GL_QUADS, numIndices, GL_UNSIGNED_INT, NULL);
}


void display() 
{
	int time = 0;
	Matrix mMatrix;
	Matrix mErde;
	Matrix mMars;
	Matrix mNeptun;

	time = glutGet(GLUT_ELAPSED_TIME);

	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	ortho = Matrix::Orthogonal(0.1,1000,2,2);

	glBindVertexArray(myArray[1]);
	shader->setUniformMatrix4fv("uni_perspective", 1, GL_FALSE, ortho.data);
	shader->setUniformMatrix4fv("uni_view", 1, GL_FALSE, Matrix().data);
	shader->setUniformMatrix4fv("uni_model", 1, GL_FALSE, Translation(0,0,-10).data);
	glBindTexture(GL_TEXTURE_2D, textures[4]);

	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, NULL);

	glClear(GL_DEPTH_BUFFER_BIT);


	glBindVertexArray(myArray[0]);

	//Sonne
	mMatrix = Rotation(0,time * 0.09f, 0);
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	CreatePlanet(mMatrix);	

	//Erde
	mErde =  Translation(4.5f + 1.5 * sinf(time * 0.01f /360.0f * 2 * M_PI ), 0.0f, 0.0f) * Rotation(0, time * 0.01f, 0) * Rotation(0, 180, 25);
	mMatrix = Scale(0.2f,0.2f,0.2f) * Rotation(0,time * 0.19f, 0) * Rotation(0,0, 15) * Rotation(0,time * 0.19f, 0) * mErde ;
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	CreatePlanet(mMatrix);	

	//Mond
	//mMatrix = mErde * Rotation(0, 0, 15) * Rotation(0,time * 0.09f, 0)  * Tranlation(12.0f, 0.0f, 0.0f) * Scale(0.18f,0.18f,0.18f) ;
	mMatrix = Scale(0.06f,0.06f,0.06f) * Translation(0.50f, 0.0f, 0.0f) * Rotation(0,time * 0.09f, 0) * mErde;
	glBindTexture(GL_TEXTURE_2D, textures[3]);
	CreatePlanet(mMatrix);

	//Mars
	mMars = Translation(7.0f + 1.5 * sinf(-time * 0.09f /360.0f * 2 * M_PI ), 0.0f, 0.0f) * Rotation(0, -time * 0.09f, 0) * Rotation(0, 180, 25);
	mMatrix = Scale(0.5f,0.5f,0.5f) * Rotation(0,time * 0.19f, 0) * Rotation(0,0, 15) * Rotation(0,time * 0.29f, 0) * mMars;
	glBindTexture(GL_TEXTURE_2D, textures[2]);
	CreatePlanet(mMatrix);

	
	//Mars Mond1
	mMatrix = Scale(0.18f,0.18f,0.18f) * Translation(1.1f, 0.0f, 0.0f) * Rotation(0,time * 0.29f, 0) *  mMars;
	glBindTexture(GL_TEXTURE_2D, textures[3]);
	CreatePlanet(mMatrix);

	//Mars Mond2
	mMatrix = Scale(0.11f,0.11f,0.11f) * Translation(2.1f, 0.0f, 0.0f) * Rotation(0,-time * 0.2f, 0) *  mMars;
	glBindTexture(GL_TEXTURE_2D, textures[3]);
	CreatePlanet(mMatrix);

	//Jupiter
	mNeptun = Translation(2.0f + 0.5 * sinf(-time * 0.03f /360.0f * 2 * M_PI ), 0.0f, 0.0f) * Rotation(0, -time * 0.03f, 0) * Rotation(0, 180,25);
	mMatrix = Scale(0.31f,0.31f,0.31f) * Rotation(0, -time * 0.03f, 0) * mNeptun;
	glBindTexture(GL_TEXTURE_2D, textures[5]);
	CreatePlanet(mMatrix);

	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
switch(key) {
	case 'w':
		cameraPosition[2] += 0.1;
	break;
	case 'a':
		cameraPosition[0] += 0.1;
	break;
		case 's':
			cameraPosition[2] -= 0.1;
	break;
		case 'd':
			cameraPosition[0] -= 0.1;
	break;
		case 'q':
			cameraPosition[1] += 0.1;
	break;
		case 'e':
			cameraPosition[1] -= 0.1;
	break;
}
}



void mouseButton(int button, int state, int x, int y) 
{
	dX =  2.0*double(x)/800.0 - 1.0;
	dY = -2.0*double(y)/600.0 + 1.0;



	glutPostRedisplay();
}

void mouseMove(int x, int y) 
{
	dX =  2.0*double(x)/800.0 - 1.0;
	dY = -2.0*double(y)/800.0 + 1.0;

	cameraRotation[2] = dY * 45;
	cameraRotation[0] = dX * 45;

	printf("dX: %g dY: %g \n", dX, dY);

	glutPostRedisplay();
}

void idleFunction() 
{
	glutPostRedisplay();
}

void resizeFunction(int w, int h) 
{

	projectionMatrix = Matrix::Perspective(0.1,1000,w,h,50);
}

void InitGeometrie()
{

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
	for(int theta = 0; theta <= 180; theta += thetaStep) 
	{
		for(int phi = 0; phi < 360; phi += phiStep) 
		{
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

	glBindVertexArray(myArray[0]);
	glBindBuffer(GL_ARRAY_BUFFER, myBuffers[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myBuffers[1]);




	
	glBufferData(GL_ARRAY_BUFFER, bufferSize, buffer, GL_STATIC_DRAW);

	
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBufferSize, indexBuffer, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9*sizeof(float), (void*)(NULL + 6*sizeof(float)));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9*sizeof(float), (void*)(NULL + 3*sizeof(float)));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9*sizeof(float), NULL);

		glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	

	//LoadTextures
	textures[0] = LoadBmps("../Data/earthmap.bmp");
	textures[1] = LoadBmps("../Data/sunmap.bmp");
	textures[2] = LoadBmps("../Data/mars.bmp");
	textures[3] = LoadBmps("../Data/moonmap.bmp");
	textures[4] = LoadBmps("../Data/space.bmp");
	textures[5] = LoadBmps("../Data/neptunemap.bmp");

	//hintergrund
	GLuint buffer_vertices;
	GLuint buffer_indices;

	 GLfloat vertices[] = {
        -1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        0.0f, 0.0f, 1.0f,
		-1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f,
		0.0f, 0.0f, 1.0f,
		1.0f, 1.0f, -1.0f,
		1.0f, 1.0f, -1.0f,
		0.0f, 0.0f, 1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
    };

	 GLuint indices[] = {
        0, 1, 2,3
    };

	 	glBindVertexArray(myArray[1]);

	 glGenBuffers(1, &buffer_vertices);
    glGenBuffers(1, &buffer_indices);

	glBindBuffer(GL_ARRAY_BUFFER, buffer_vertices);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_indices);

	  glBufferData(GL_ARRAY_BUFFER, 36 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9*sizeof(float), (void*)(NULL + 6*sizeof(float)));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9*sizeof(float), (void*)(NULL + 3*sizeof(float)));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9*sizeof(float), NULL);

		glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	delete [] buffer;

}




int main(int argc, char **argv) 
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(800,800);
	glutInitWindowPosition(10,10);
	glutCreateWindow("OpenGL");
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);
	glutMouseFunc(mouseButton); 
	glutMotionFunc(mouseMove);
	glutIdleFunc(idleFunction);
	glutReshapeFunc(resizeFunction);
	
	glutShowWindow();

	glewInit();

	cwc::glShaderManager shaderManager;
	
	shader = nullptr;
	shader = shaderManager.loadfromFile("../Planetensystem/shader/vertex.glsl", "../Planetensystem/shader/fragment.glsl");

	shader->BindAttribLocation(0, "att_vertex");
	shader->BindAttribLocation(1, "att_normal");
	shader->BindAttribLocation(2, "att_color");
	//glBindFragDataLocation(shader->GetProgramObject(), 0, "r_color");

	glEnable(GL_DEPTH_TEST);
	
	
	GLuint program = glCreateProgram();
	
	glGenVertexArrays(2, myArray); 

	InitGeometrie();

	glClearColor(0.5,0.5,1.0,0.0);

	glutMainLoop();
	
	return 0;
}


