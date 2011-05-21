/* 
 * File:   Robot.h
 * Author: Davide Aversa
 *
 * Created on March 30, 2011, 9:44 PM
 */

#ifndef ROBOT_H
#define	ROBOT_H

#include<GL/gl.h>

#include"denavit.h"
#include"RLink.h"

class Robot {
    /**
     * Class Robot.
     * 
     * @attrib linklist : Link List.
     * @attrib numlink  : Number of link.
     * @attrib textures : Textures.
     */
    
public:
    /**
     * Constructor.
     * 
     * @param numlink : Number of link.
     * @param dhtable : A matrix representing a DH-Table.
     * @param textures : Textures array.
     */
    Robot(int numlink, double* dhtable, GLuint* textures);
    Robot(const Robot& orig);
    virtual ~Robot();
    
    double getQ(int idlink);
    
    void updateQ(int idlink, double newq);
    void update();
    void draw();
private:
    RLink** linklist;
    int numlink;
    GLuint* textures;
    
    /**
     * This private method draw the end-effector.
     */
    void drawEndEffector();

};

#endif	/* ROBOT_H */

