#include <assert.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef __MACOSX__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#elif defined __LINUX__ || defined __CYGWIN__
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#endif


//#include "debug.h"
//#include "geom356.h"

//#include "surfaces_lights.h"
//#include "scene.h"

void Initialize();
void Draw();


int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);//GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
	
	
	if (!glutGet(GLUT_DISPLAY_MODE_POSSIBLE)) {
    	fprintf(stderr, "Cannot get requested display mode.\n") ;
        exit(EXIT_FAILURE) ;
    }

    glutInitWindowSize(500,500);
	glutInitWindowPosition(200,0);

	
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
	glutCreateWindow("EMM.....");
	//glutSetWindow(win);
	Initialize();

	glutDisplayFunc(Draw);
	glutMainLoop();

	return 0;
}


void Draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);

	// Set material properties
	GLfloat qaBlack[] = {0.0, 0.0, 0.0, 1.0};
	GLfloat qaGreen[] = {0.0, 1.0, 0.0, 1.0};
	GLfloat qaRed[] = {1.0, 0.0, 0.0, 1.0};
	GLfloat qaBlue[] = {0.0, 0.0, 1.0, 1.0};
	GLfloat qaWhite[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat qaLowAmbient[] = {0.2, 0.2, 0.2, 1.0};
	GLfloat qaFullAmbient[] = {1.0, 1.0, 1.0, 1.0};

	for (int iIndex = 0; iIndex < 2; ++iIndex) {
		if (iIndex == 0) {
			glShadeModel(GL_FLAT);
		} else {
			glShadeModel(GL_SMOOTH);
		}

		//Set, ambient, diffuse and specular lighting. Set ambient to 20%.
		glMaterialfv(GL_FRONT, GL_AMBIENT, qaGreen);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, qaGreen);
		glMaterialfv(GL_FRONT, GL_SPECULAR, qaWhite);
		glMaterialf(GL_FRONT, GL_SHININESS, 128.0);
		glLightfv(GL_LIGHT0, GL_AMBIENT, qaLowAmbient);

		// Draw a sphere
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glPushMatrix();
			glTranslatef(-0.5 + (float)iIndex, 0.5, -2.0);
			glutSolidSphere(.5, 30, 30);
		glPopMatrix();

		// Turn off diffuse and specular reflection. Set ambient light to full.
		glMaterialfv(GL_FRONT, GL_DIFFUSE, qaBlack);
		glMaterialfv(GL_FRONT, GL_SPECULAR, qaBlack);
		glLightfv(GL_LIGHT0, GL_AMBIENT, qaFullAmbient);

		// Draw a triangle with one red, green, and blue vertex.
		glBegin(GL_TRIANGLES);
			glMaterialfv(GL_FRONT, GL_AMBIENT, qaRed);
			glVertex3f(-.5 + (float)iIndex, 0.0, -.2);
			glMaterialfv(GL_FRONT, GL_AMBIENT, qaGreen);
			glVertex3f(-.933 + (float)iIndex, -.75, -.2);
			glMaterialfv(GL_FRONT, GL_AMBIENT, qaBlue);
			glVertex3f(-.067 + (float)iIndex, -.75, -.2);
		glEnd();
	}

	glFlush();
}

void Initialize() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -3.0, 3.0);

	// Lighting set up
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// Set lighting intensity and color
	GLfloat qaAmbientLight[]	= {0.2, 0.2, 0.2, 1.0};
	GLfloat qaDiffuseLight[]	= {0.8, 0.8, 0.8, 1.0};
	GLfloat qaSpecularLight[]	= {1.0, 1.0, 1.0, 1.0};
	glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight);

	// Set the light position
	GLfloat qaLightPosition[]	= {0.0, 1.0, -.5, 1.0};
	glLightfv(GL_LIGHT0, GL_POSITION, qaLightPosition);
}




