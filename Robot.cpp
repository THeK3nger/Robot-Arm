/* 
 * File:   Robot.cpp
 * Author: Davide Aversa
 * 
 * Created on March 30, 2011, 9:44 PM
 */

#include "Robot.h"
#include "RLink.h"

#include <GL/freeglut_std.h>

Robot::Robot(int numlink, double* dhtable, GLuint* textures) {
    this->linklist = new RLink*[numlink];
    this->numlink = numlink;
    this->textures = textures;
    for (int i=0;i<numlink;++i)
    {
        linklist[i] = new RLink(&dhtable[i*4]);
        linklist[i]->setTextures(textures);
    }
}

Robot::Robot(const Robot& orig) {
}

Robot::~Robot() {
}

void Robot::draw() {
    glPushMatrix();
    GLdouble t[] = {-1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1};
    glMultMatrixd(t);
    
    for (int i=0;i<this->numlink;++i) {
        this->linklist[i]->draw();
    }    
    
    this->drawEndEffector();
    
    glPopMatrix();
}

void Robot::updateQ(int idlink, double newq) {
    this->linklist[idlink]->updateQ(newq);
}

double Robot::getQ(int idlink) {
    return this->linklist[idlink]->getQ();
}

void Robot::drawEndEffector() {
    glBindTexture(GL_TEXTURE_2D, this->textures[0]);
    
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // scale linearly when image bigger than texture
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // scale linearly when image smaller than texture
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    
    glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
    glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
    
    glPushMatrix();
    glTranslated(0,0.5,0);
    glutSolidCone(0.4,2,20,20);
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(0,-0.5,0);
    glutSolidCone(0.4,2,20,20);
    glPopMatrix();
}

void Robot::update() {
    for (int i=0;i<this->numlink;i++) {
        this->linklist[i]->update();
    }
}
