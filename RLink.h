/* 
 * File:   RLink.h
 * Author: kratux
 *
 * Created on March 30, 2011, 9:47 PM
 */

#ifndef RLINK_H
#define	RLINK_H

#include"denavit.h"
#include<GL/gl.h>

class RLink {
    /**
     * This class models a link with a Revolute Joint according to 
     * Denavit-Hartenberg convention.
     * 
     */
    
    
public:
    /**
     * Constructor.
     *
     * @param a : 'a' value in denavit-hartenberg convention.
     * @param alpha
     * @param d
     * @param teta 
     */ 
    RLink(double a, double alpha, double d, double teta);
    
    /**
     * Constructor.
     * 
     * @param parameters : A row of DH-Table.
     */
    RLink(double* parameters);
    RLink(const RLink& orig);
    virtual ~RLink();
    
    /**
     * Getter for 'qvalue'
     */
    double getQ();
    
    /**
     * Setter for 'qvalue'
     */
    void updateQ(double newq);
    
    void update();
    void draw();
    
    /**
     * Setter for 'textures'.
     */
    void setTextures(GLuint* textures);
    
private:
    dhmatrix* dhm; // Pointer to a transformation matrix for this link.
    double qvalue; // Value of joint variable.
    GLuint* textures; // Textures Array.
    
    void enableSphereTexture();
    void enablePrismaTexture();
};

#endif	/* RLINK_H */

