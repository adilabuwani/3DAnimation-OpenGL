#include <iostream>
#include <gl/glut.h>
using namespace std;

GLfloat pos[] = { -2, 4, 5, 1 };    //position of light
GLfloat amb[] = { 0.3, 0.3, 0.3, 1.0 };  

//front and back side property in RGB
GLfloat front_amb_diff[] = { 0.7, 0.5, 0.1, 1.0 };

GLfloat capRing[] = { 1.0, 0.0, 0.0, 1.0 };
GLfloat face[] = { 0.0, 0.0, 1.0, 1.0 };
GLfloat eye[] = { 0.0, 0.7, 0.7, 1.0 };

GLfloat back_amb_diff[] = { 0.4, 0.7, 0.1, 1.0 };

//both front and back property
GLfloat spe[] = { 0.25, 0.25, 0.25, 1.0 };

//animation
GLfloat theta = 0;
GLfloat dt = 0.5;
GLfloat axes[3][3] = { {1, 0, 0},      //rotation around x, y, and z axis
					   {0, 1, 0},
					   {0, 0, 1}};

int axis = 0;


void drawCapTorus(void) {

	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, capRing);
	glTranslated(0, 1.2, 0);
	glRotated(90, 1, 0, 0);
	glutSolidTorus(0.2, 1.0, 48, 96);
	glPopMatrix();  //pop the translation from M

	//inner1
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, capRing);
	glTranslated(0, 1.6, 0);
	glRotated(90, 1, 0, 0);
	glutSolidTorus(0.2, 0.7, 48, 96);
	glPopMatrix();  //pop the translation from M
	
	//inner2
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, capRing);
	glTranslated(0, 2.0, 0);
	glRotated(90, 1, 0, 0);
	glutSolidTorus(0.2, 0.5, 48, 96);
	glPopMatrix();  //pop the translation from M

	//inner 3
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, capRing);
	glTranslated(0, 2.4, 0);
	glRotated(90, 1, 0, 0);
	glutSolidTorus(0.2, 0.3, 48, 96);
	glPopMatrix();  //pop the translation from M

}//end draw cap

void drawEye(void) {

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, eye);
	glPushMatrix();
	glTranslated(0.5, 4.5, 0.8);
	glutSolidCube(0.5);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-0.5, 4.5, 0.8);
	glutSolidCube(0.5);
	glPopMatrix();
}


void drawFace(void) {  //face diameter=2
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, face);
	glutSolidCube(2.0);
	glPopMatrix();
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//upepr face
	glPushMatrix();
	glTranslated(0, 4, 0); // translate both together
	drawCapTorus();
	drawFace();
	glPopMatrix();
	//////////////////////////////////////
	glPushMatrix();
	drawEye();
	glPopMatrix();


	glPushMatrix();
	//lovely code
	glScalef(0.5, 1.0, 2.0);
	glutSolidCube(2);

	glPopMatrix();



	//voiding animation for now
	/*
	if (axis < 3) {
		glRotated(theta, axes[axis][0], axes[axis][1], axes[axis][2]);
	}
	else {//when axis is 3
		glPushMatrix(); //prserve  CTM for the object
		glRotated(theta, 0, 0, 1); //shall rotate light around the z axis
		glLightfv(GL_LIGHT0, GL_POSITION, pos);   //light0, positioned at the desired position
		glPopMatrix(); //rstore  CTM for object
		

	}//end else
	*/

	//draw object -dadius in between ring, radius from the center, and number of lines in between
	//glutSolidTorus(0.2, 1.0, 48, 96);
	
	//glutSolidCone(0.8, 2.0, 48, 96);
	
	
	
	glutSwapBuffers();  ////////////////////////////////////////////////////////////////////
	//when the display is re called, update with new values
}//end display

/*
void idle(void) { //when nothing is pressed
	if (theta >= 360) {
		axis=(axis + 1) % 4; //cycle through the 4 stages
	}
	//less then 360, increment angle by 0.5
	if (theta < 360) {
		theta = (theta + dt);
	}
	else {
		theta = dt;
	}

	glutPostRedisplay(); //refrrh window
	
}//end idle
*/
void main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(200, 100);
	glutCreateWindow("3D OBJECTS");
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();


	glOrtho(-8, 8, -8, 8, 2, 8);
	//front light 
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, front_amb_diff);
	
	//back light
	glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, back_amb_diff);

	//front and back light specular
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spe);

	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 75);
	
	glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glTranslated(0, 0, -5); //to keep everything in the center
	
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glutDisplayFunc(display);
	//glutIdleFunc(idle);
	glutMainLoop();
}