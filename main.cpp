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
float cameraz = -15;

float cameraangle = 0;

int linksel = 0;
int numlink = 5;

double dh[] =   {0,pi2,5.0,1,
                0,pi2,0,1,
                0,pi2,5,1,
                0,pi2,0,1,
                0,0,5,1};
Robot* r;

GLuint texture[3];

static GLfloat xequalzero[] = {1.0, 0.0, 0.0, 0.0};
static GLfloat slanted[] = {1.0, 1.0, 1.0, 0.0};

void LoadGLTextures() {	
    // Load Texture
    BMPImage *image1 = new BMPImage();
    BMPImage *image2 = new BMPImage();
    BMPImage *image3 = new BMPImage();

    if (!image1->loadImage("./res/copper.bmp")) {
	exit(1);
    }       
    
    if (!image2->loadImage("./res/zink.bmp")) {
	exit(1);
    }
    
    if (!image3->loadImage("./res/grass.bmp")) {
	exit(1);
    }  

    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    
    // Create Texture	
    glGenTextures(3, &texture[0]);
    glBindTexture(GL_TEXTURE_2D, texture[0]);   // 2d texture (x and y size)


    // 2d texture, level of detail 0 (normal), 3 components (red, green, blue), x size from image, y size from image, 
    // border 0 (normal), rgb color data, unsigned byte data, and finally the data itself.
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image1->getX(), image1->getY(), 0, GL_RGB, GL_UNSIGNED_BYTE, image1->getData());
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // scale linearly when image bigger than texture
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // scale linearly when image smaller than texture
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

    glBindTexture(GL_TEXTURE_2D, texture[1]); 
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image2->getX(), image2->getY(), 0, GL_RGB, GL_UNSIGNED_BYTE, image2->getData());
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // scale linearly when image bigger than texture
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // scale linearly when image smaller than texture
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image3->getX(), image3->getY(), 0, GL_RGB, GL_UNSIGNED_BYTE, image3->getData());
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // scale linearly when image bigger than texture
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // scale linearly when image smaller than texture
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    
    delete image1;
    delete image2;
    delete image3;
};

void init(){
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0};
    GLfloat mat_shininess[] = { 25.0};
    GLfloat light_position[] = { 20.0, 20.0, 20.0, 0.0};
    GLfloat white_light[] = { 1, 1, 1, 1.0 };
    //GLfloat lmodel_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
    
    glClearColor(0.8,0.8,0.8,1.0);
    glClearDepth(1.0); 
    glShadeModel(GL_SMOOTH);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
    //glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    glEnable(GL_CULL_FACE);
    glEnable(GL_FOG);	
    glDepthMask(GL_TRUE);
    
    //FOG                                               // Which Fog To Use
    GLfloat fogColor[4]= {0.8f, 0.8f, 0.8f, 1.0f};	// Fog Color
    glFogi(GL_FOG_MODE, GL_LINEAR);                     // Fog Mode
    glFogfv(GL_FOG_COLOR, fogColor);			// Set Fog Color
    glFogf(GL_FOG_DENSITY, 0.3f);                       // How Dense Will The Fog Be
    glHint(GL_FOG_HINT, GL_DONT_CARE);			// Fog Hint Value
    glFogf(GL_FOG_START,10.0f);				// Fog Start Depth
    glFogf(GL_FOG_END, 40.0f);				// Fog End Depth
    				// Enables GL_FOG

    LoadGLTextures();
    r = new Robot(numlink,dh,texture);

}

void drawFloor() {
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    
    double size = 20.0;
    glBegin(GL_QUADS);
    glNormal3f(0.0, 1.0, 0.0);
    glTexCoord2f(0,0);
    glVertex3d(size,0,size);
    glTexCoord2f(0,1);
    glVertex3d(size,0,-size);
    glTexCoord2f(1,1);
    glVertex3d(-size,0,-size);
    glTexCoord2f(1,0);
    glVertex3d(-size,0,size);
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

    gluPerspective(60.0,(GLsizei) w/(GLsizei) h, 0.1, 100);
    
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
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
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

