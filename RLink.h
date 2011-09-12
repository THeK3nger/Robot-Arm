/* 
 * File:   RLink.h
 * Author: Davide Aversa
 *
 * Created on March 30, 2011, 9:47 PM
 */

#ifndef RLINK_H
#define	RLINK_H

#include<GL/gl.h>

#include"denavit.h"

/**
 * This class models a link with a Revolute Joint according to
 * Denavit-Hartenberg convention.
 */
class RLink {
    
public:
    /**
     * Constructor.
     *
     * @param a     : 'a' value in denavit-hartenberg convention.
     * @param alpha : 'alpha' value in denavit-hartenberg convention.
     * @param d     : 'd' value in denavit-hartenberg convention.
     * @param teta  : 'teta' value in denavit-hartenberg convention.
     */ 
    RLink(double a, double alpha, double d, double teta);
    
    /**
     * Constructor.
     * 
     * @see RLink(double a, double alpha, double d, double teta)
     * @param parameters : A row of DH-Table.
     */
    RLink(double* parameters);
    RLink(const RLink& orig);
    virtual ~RLink();
    
    /**
     * Getter for 'qvalue'
     *
     * @return qvalue of the current link.
     */
    double getQ();
    
    /**
     * Setter for 'qvalue'
     *
     * @param newq : New q value for the current link.
     */
    void updateQ(double newq);
    
    /**
     * Setter for 'qdot'
     *
     * @param newqdot : New qdot value for the current link.
     */
    void updateQDot(double newqdot);
    
    /**
     * Update the current link q value according qdot.
     */
    void update();

    /**
     * Draw this link.
     */
    void draw();
    
    /**
     * Setter for 'textures'.
     */
    void setTextures(GLuint* textures);
    
private:
    dhmatrix* dhm;      // Pointer to a transformation matrix for this link.
    double qvalue;      // Value of joint variable.
    GLuint* textures;   // Textures Array.
    double qdot;        // Link Angular Velocity.
    
    void enableSphereTexture(); // Enable Textures for Joint.
    void enablePrismaTexture(); // Enable Textures for Link.
};

#endif	/* RLINK_H */

