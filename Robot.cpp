/* 
 * File:   Robot.cpp
 * Author: kratux
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
    glPushMatrix();
    glTranslated(0,0.5,0);
    glutSolidCone(0.4,2,20,20);
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(0,-0.5,0);
    glutSolidCone(0.4,2,20,20);
    glPopMatrix();
}