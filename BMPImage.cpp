/* 
 * File:   BMPImage.cpp
 * Author: Davide Aversa
 * 
 * Created on April 6, 2011, 4:47 PM
 */

#include "BMPImage.h"
#include <stdio.h>

BMPImage::BMPImage() {
}

BMPImage::BMPImage(const BMPImage& orig) {
}

BMPImage::~BMPImage() {
}

int BMPImage::loadImage(char *filename) {
    FILE *file;
    unsigned long size;                 // size of the image in bytes.
    unsigned long i;                    // standard counter.
    unsigned short int planes;          // number of planes in image (must be 1) 
    unsigned short int bpp;             // number of bits per pixel (must be 24)
    char temp;                          // temporary color storage for bgr-rgb conversion.

    // make sure the file is there.
    if ((file = fopen(filename, "rb"))==NULL)
    {
	printf("\tFile Not Found : %s\n",filename);
	return 0;
    }
    
    // seek through the bmp header, up to the width/height:
    fseek(file, 18, SEEK_CUR);

    // read the width
    if ((i = fread(&this->sizeX, 4, 1, file)) != 1) {
	printf("\tError reading width from %s.\n", filename);
	return 0;
    }
    printf("\tWidth of %s: %lu\n", filename, this->sizeX);
    
    // read the height 
    if ((i = fread(&this->sizeY, 4, 1, file)) != 1) {
	printf("Error reading height from %s.\n", filename);
	return 0;
    }
    printf("\tHeight of %s: %lu\n", filename, this->sizeY);
    
    // calculate the size (assuming 24 bits or 3 bytes per pixel).
    size = this->sizeX * this->sizeY * 3;

    // read the planes
    if ((fread(&planes, 2, 1, file)) != 1) {
	printf("\tError reading planes from %s.\n", filename);
	return 0;
    }
    if (planes != 1) {
	printf("\tPlanes from %s is not 1: %u\n", filename, planes);
	return 0;
    }

    // read the bpp
    if ((i = fread(&bpp, 2, 1, file)) != 1) {
	printf("\tError reading bpp from %s.\n", filename);
	return 0;
    }
    if (bpp != 24) {
	printf("\tBpp from %s is not 24: %u\n", filename, bpp);
	return 0;
    }
	
    // seek past the rest of the bitmap header.
    fseek(file, 24, SEEK_CUR);

    // read the data. 
    this->data = new char[size];
    if (this->data == NULL) {
	printf("\tError allocating memory for color-corrected image data");
	return 0;	
    }

    if ((i = fread(this->data, size, 1, file)) != 1) {
	printf("\tError reading image data from %s.\n", filename);
	return 0;
    }

    for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
	temp = this->data[i];
	this->data[i] = this->data[i+2];
	this->data[i+2] = temp;
    }
    
    // we're done.
    return 1;
}

char* BMPImage::getData() {
    return this->data;
}

unsigned long BMPImage::getX(){
    return this->sizeX;
}

unsigned long BMPImage::getY() {
    return this->sizeY;
}
