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

/**
 * Class Robot.
 */
class Robot {

    
public:
    /**
     * Constructor.
     * 
     * @param numlink  : Number of links.
     * @param dhtable  : A matrix representing a DH-Table.
     * @param textures : Textures array.
     */
    Robot(int numlink, double* dhtable, bool zapproach, GLuint* textures);
    Robot(const Robot& orig);
    virtual ~Robot();
    
    /**
     * Return the q value for the selected link.
     *
     * @param idlink : ID of the selected link.
     * @return The q value of the link.
     */
    double getQ(int idlink);
    
    /**
      * Update the q value for the selected link.
      *
      * @param idlink : ID of the selected link.
      * @param newq   : New q value.
      */
    void updateQ(int idlink, double newq);

    /**
      * Update every link in the robot according to the kinematic velocity.
      */
    void update();

    /**
      * Draw every link in the robot.
      */
    void draw();
private:
    RLink** linklist; /* List of Link */
    int numlink;      /* Total number of the link */
    GLuint* textures; /* Textures Array */
    bool zapproach;   /* True if robot approach along the z axis */
    
    /*
     * This private method draw the end-effector.
     */
    void drawEndEffector();

};

#endif	/* ROBOT_H */

