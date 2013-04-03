#include <stdio.h>
#include <GL\glew.h>
#include <GL\glut.h>
#define _USE_MATH_DEFINES
#include <math.h>

double dX = -0.9;
double dY = -0.9;

void display() {

	
	
	

	

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


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

void resizeFunction(int w, int h) {

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

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(left, right, bottom, top, front, back);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslated(0.0, 0.0, -distance);

	glViewport(0,0,w,h);
	
}

void InitGeometrie()
{
	GLuint myBuffers[2] = {0,0};

	

	glGenBuffers(2, myBuffers);
	
	glBindBuffer(GL_ARRAY_BUFFER, myBuffers[0]);
	glBufferData(GL_ARRAY_BUFFER, 0, NULL, GL_STATIC_DRAW);

	//Geometrie


	
}

int main(int argc, char **argv) {

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

	glClearColor(0.5,0.5,1.0,0.0);
	InitGeometrie();

	glutMainLoop();
	
	return 0;
}


