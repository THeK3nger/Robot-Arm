/* 
 * File:   main.cpp
 * Author: kratux
 *
 * Created on March 30, 2011, 7:58 PM
 */

#include <cstdlib>
#include <iostream>
#include <stdio.h>

#include <GL/glut.h>
#include <GL/gl.h>

#include "denavit.h"
#include "RLink.h"
#include "Robot.h"
#include "BMPImage.h"

#define pi2 11.0/7.0

//TODO: Floor.
//TODO: Textures.
//TODO: Refining Command.
//TODO: User interface with info about.
//TODO (Optional) : Automatic Mobility?

using namespace std;

/*
 * GLOBAL VARIABLE
 */

float cameray = 5;
float camerax = 0;
float cameraz = -25;

float cameraangle = 0;

int linksel = 0;
int numlink = 5;

double dh[] =   {0,pi2,5.0,1,
                0,pi2,0,1,
                0,pi2,5,1,
                0,pi2,0,1,
                0,0,5,1};
Robot* r;

GLuint texture[1];

void LoadGLTextures() {	
    // Load Texture
    BMPImage *image1 = new BMPImage();

    if (!image1->loadImage("./res/copper.bmp")) {
	exit(1);
    }        

    // Create Texture	
    glGenTextures(1, &texture[0]);
    glBindTexture(GL_TEXTURE_2D, texture[0]);   // 2d texture (x and y size)

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // scale linearly when image bigger than texture
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // scale linearly when image smalled than texture
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);

    // 2d texture, level of detail 0 (normal), 3 components (red, green, blue), x size from image, y size from image, 
    // border 0 (normal), rgb color data, unsigned byte data, and finally the data itself.
    glTexImage2D(GL_TEXTURE_2D, 0, 3, image1->getX(), image1->getY(), 0, GL_RGB, GL_UNSIGNED_BYTE, image1->getData());
};

void init(){
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0};
    GLfloat mat_shininess[] = { 25.0};
    GLfloat light_position[] = { 20.0, 20.0, 20.0, 1.0};
    GLfloat white_light[] = { 1, 1, 1, 1.0 };
    GLfloat lmodel_ambient[] = { 0.3, 0.3, 0.3, 1.0 };
    
    glClearColor(0.0,0.0,0.0,0.0);
    glShadeModel(GL_SMOOTH);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    
    LoadGLTextures();
    r = new Robot(numlink,dh,texture);
    glEnable(GL_TEXTURE_2D);
    
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    glEnable(GL_TEXTURE_GEN_R);
    glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
    glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
    glTexGeni(GL_R,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
}

void drawFloor() {
    double size = 100.0;
    glBegin(GL_QUADS);
    glNormal3f(0.0, 1.0, 0.0);
    glVertex3d(-size,0,size);
    glVertex3d(-size,0,-size);
    glVertex3d(size,0,-size);
    glVertex3d(size,0,size);
    glEnd();    
}

void display(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();    
    glPushMatrix();
    gluLookAt(camerax,cameray,cameraz,camerax,cameray,cameraz + 5,0,1,0);
    glRotated(cameraangle, 0, 1, 0);
    // OBJECT DRAWING
    
    drawFloor();
    r->draw();
    
    // END OBJECT
    glPopMatrix();
    glFlush();
    
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(30.0,(GLsizei) w/(GLsizei) h, 0.1, 100);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

#define STEP 0.1

void keycontrol(unsigned char key, int x, int y) {
    switch (key) {
        case 'w' :
            cameraz = cameraz + STEP;
            glutPostRedisplay();
            break;
        case 's' :
            cameraz = cameraz - STEP;
            glutPostRedisplay();
            break;
        case 'a' :
            camerax = camerax + STEP;
            glutPostRedisplay();
            break;
        case 'd':
            camerax = camerax - STEP;
            glutPostRedisplay();
            break;
        case 'q' :
            cameraangle = cameraangle - (STEP*10);
            glutPostRedisplay();
            break;
        case 'e' :
            cameraangle = cameraangle + (STEP*10);
            glutPostRedisplay();
            break;
        case 'r' :
            cameray = cameray + STEP;
            glutPostRedisplay();
            break;
        case 'f':
            cameray = cameray - STEP;
            glutPostRedisplay();
            break;
        case '+':
            linksel = (linksel + 1) % numlink;
            break;
        case '-':
            linksel = (linksel - 1);
            if (linksel<0) linksel = numlink - 1;
            break;
        case 'p':
            r->updateQ(linksel,r->getQ(linksel) + 0.1);
            glutPostRedisplay();
            break;
        case 'o':
            r->updateQ(linksel,r->getQ(linksel) - 0.1);
            glutPostRedisplay();
            break;
        default:
            break;
    }
}

/*
 * 
 */
int main(int argc, char** argv) {

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(100,100);
    glutCreateWindow("ROBOT ARMS v0.1");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keycontrol);
    glutMainLoop();
    return 0;
}

