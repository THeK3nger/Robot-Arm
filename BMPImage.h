/* 
 * File:   BMPImage.h
 * Author: Davide Aversa
 *
 * Created on April 6, 2011, 4:47 PM
 */

#ifndef BMPIMAGE_H
#define	BMPIMAGE_H

#include <string>
using namespace std;

class BMPImage {
public:
    BMPImage();
    BMPImage(const BMPImage& orig);
    virtual ~BMPImage();
    
    /**
     * Load a bitmap image.
     *
     * ARGS:
     *  * filename : Path to file.
     */
    int loadImage(string strfilename);
    
    /**
     * Get Image Data
     */
    char* getData();

    // Get height and width.
    unsigned long getX();
    unsigned long getY();
    
private:
    unsigned long sizeX;
    unsigned long sizeY;
    char *data;

};

#endif	/* BMPIMAGE_H */

