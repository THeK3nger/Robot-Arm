/* 
 * File:   RLink.cpp
 * Author: Davide Aversa
 * 
 * Created on March 30, 2011, 9:47 PM
 */

#include <GL/freeglut_std.h>

#include "RLink.h"

RLink::RLink(double a, double alpha, double d, double teta) {
    this->dhm = createMatrix(a,alpha,d,teta);
    this->qvalue = teta;
    this->qdot = 0.1;
}

RLink::RLink(double* parameters){
    this->dhm = createMatrix(parameters);
    this->qvalue = parameters[3];
    this->qdot = 0.1;
}

RLink::RLink(const RLink& orig) {
}

RLink::~RLink() {
}

void RLink::draw() {
    
    // ONLY IF D != 0.
    if (this->dhm->d != 0) {  
        glPushMatrix();
            // Pre-rotate by 'q' along z axis
            glRotated((this->qvalue * 180)/3.1416,0,0,1);
            // Draw first sphere.
            glPushMatrix();
                glScaled(0.7,0.7,0.7);
                enableSphereTexture();
                glutSolidSphere(1,20,20);
            glPopMatrix();

            // Draw first part.
            glPushMatrix();
                glTranslated(0,0,(this->dhm->d) / 2);
                glScaled(0.7,0.7,this->dhm->d);
                enablePrismaTexture();
                glutSolidCube(1);
            glPopMatrix();
        glPopMatrix();
    }
    
    // Go to next frame.
    glMultMatrixd(this->dhm->matrix);
    //glTranslated(0,0,this->dhm->d);
    //glRotated((this->dhm->alpha * 180)/3.1416,0,1,0);
    //glTranslated(0,0,this->dhm->a);
    
    // ONLY IF A != 0
    if (this->dhm->a != 0) {
        // Draw second sphere.
        glPushMatrix();
            glTranslated(-(this->dhm->a),0,0);
            glScaled(0.7,0.7,0.7);
            enableSphereTexture();
            glutSolidSphere(1,20,20);
        glPopMatrix();

        // Draw second part.
        glPushMatrix();
            glTranslated(-(this->dhm->a) / 2,0,0);
            glScaled(this->dhm->a,0.7,0.7);
            enablePrismaTexture();
            glutSolidCube(1);
        glPopMatrix();
    }
    
} 

void RLink::updateQ(double newq) {
    this->dhm->theta = newq;
    this->dhm = createMatrix(this->dhm->a,this->dhm->alpha,this->dhm->d,this->dhm->theta);
    this->qvalue = newq;
}

double RLink::getQ() {
    return this->qvalue;
}

void RLink::setTextures(GLuint* textures) {
    this->textures = textures;
}

void RLink::enableSphereTexture() {
    glBindTexture(GL_TEXTURE_2D, this->textures[0]);
    
    glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
    glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
}

void RLink::enablePrismaTexture() {
    glBindTexture(GL_TEXTURE_2D, this->textures[1]);
    
    glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_EYE_LINEAR);
    glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_EYE_LINEAR);
}

void RLink::updateQDot(double newqdot) {
    this->qdot = newqdot;
}

void RLink::update() {
    this->updateQ(this->qvalue + this->qdot * 0.1);  
}
