/* 
 * File:   BMPImage.h
 * Author: kratux
 *
 * Created on April 6, 2011, 4:47 PM
 */

#ifndef BMPIMAGE_H
#define	BMPIMAGE_H

class BMPImage {
public:
    BMPImage();
    BMPImage(const BMPImage& orig);
    virtual ~BMPImage();
    
    int loadImage(char *filename);
    char* getData();
    unsigned long getX();
    unsigned long getY();
    
private:
    unsigned long sizeX;
    unsigned long sizeY;
    char *data;

};

#endif	/* BMPIMAGE_H */

