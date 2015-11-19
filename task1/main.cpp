//
//  main.cpp
//  GlutApp
//
//  Created by Asmat, Laksono, Malik on 2/11/2013.
//
//  press a,s,d to change speed
  
#ifdef _WIN32
    #include <windows.h>
#elif __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif

#include "COrb.h"

COrb Sun;
COrb* Mars;
COrb* Earth;
COrb* Moon;
COrb* Apollo11;
COrb* Sputnik;

GLfloat width = 1024;
GLfloat height = 768;

float camera1_z = 4;
float camera2_z = 0.1;

//angular velocity constant
float velocityConstant = 1.0;

void init(void){
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_FLAT);
    
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    glDepthRange(0.0f, 1.0f);
}

void initSolarSystem(){
    Sun = COrb(0.4, 0.0);
    Sun.setColor(1, 1, 0);
    
    // mars -> red
    Mars = Sun.addChild(0.1, 1.4);
    Mars->setColor(1, 0.5, 0);
	Mars->angularVelocity = 21;
    
    // earth -> blue
    Earth = Sun.addChild(0.07, 1);
    Earth->setColor(0, 0.667, 1);
    Earth->angularVelocity = 24;
    
    // sputnik -> purple
    Sputnik = Earth->addChild(0.03, 0.25);
    Sputnik->setColor(1,0,1);
	Sputnik->angularVelocity = 760;
    
    // moon -> white
    Moon = Earth->addChild(0.02, 0.14);
    Moon->setColor(1, 1, 1);
	Moon->angularVelocity = 55 ;
    
    // apollo -> green
    Apollo11 = Moon->addChild(0.01, 0.05);
    Apollo11->setColor(0, 1, 0.15);
	Apollo11->angularVelocity = 105;
}

void display(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    for(int disp = 0; disp < 2;disp++){
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        
        if(disp == 0){
            glViewport(0, 0, width / 2, height);

            // viewing transformation
            gluLookAt (0.0, 0.0, camera2_z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
        }
        else if(disp == 1) {
            glViewport(width / 2, 0.0, width / 2 , height);
            
            // viewing transformation
            glLoadIdentity();
			gluLookAt(0.0, camera1_z, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0);
        }
        
		Sun.draw();
        glPopMatrix();
    }
    
    glutSwapBuffers();
}

void animation(){
    int elapsedTime = glutGet(GLUT_ELAPSED_TIME);
    
    Earth->revAngle = (Earth->angularVelocity / 1000) * elapsedTime * velocityConstant;
    Earth->rotAngle = (Earth->rotVelocity / 1000) * elapsedTime;
    
    Sputnik->revAngle = (Sputnik->angularVelocity / 1000) * elapsedTime * velocityConstant;
    Sputnik->rotAngle = (Sputnik->rotVelocity / 1000) * elapsedTime;

    Mars->revAngle = (Mars->angularVelocity / 1000) * elapsedTime * velocityConstant;
    Mars->rotAngle = (Mars->rotVelocity / 1000) * elapsedTime;
    
    Moon->revAngle = (Moon->angularVelocity / 1000) * elapsedTime * velocityConstant;
    Moon->rotAngle = (Moon->rotVelocity / 1000) * elapsedTime;
    
    Apollo11->revAngle = (Apollo11->angularVelocity / 1000) * elapsedTime * velocityConstant;
    Apollo11->rotAngle =  (Apollo11->rotVelocity / 1000) * elapsedTime;
    
    glutPostRedisplay();
}

void reshape(int w, int h){
    // set for display method got the correct display
    width = w;
    height = h;
    
    // viewport set
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (width / 2) / height, 1.0, 10.0);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	gluLookAt(0.0, 0.0, camera1_z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void keymap(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'd':
        case 'D':
            velocityConstant = 1;
			break;
        
        case 's':
        case 'S':
            velocityConstant = velocityConstant / 2;
			break;
            
		case 'a':
        case 'A':
            velocityConstant = velocityConstant * 2;
			break;
	}
}
    
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(10,10);
    glutInitWindowSize(width, height);
    
    glutCreateWindow("Assignment 3, task 1");

    init();
    initSolarSystem();
    
    glutDisplayFunc(display);
	glutReshapeFunc(reshape);
    
    // keyboard handling
	glutKeyboardFunc(keymap);
    
	glutIdleFunc(animation);
    
    glutMainLoop();
    return 0;
}
