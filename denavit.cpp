#include"denavit.h"
#include<math.h>

#include<iostream>

using namespace std;

dhmatrix* createMatrix(double a, double alpha, double d, double theta)
{
    dhmatrix* result = new dhmatrix;
    result->matrix = new double[16];
    result->a = a;
    result->alpha = alpha;
    result->d = d;
    result->theta = theta;
    
    //Print Parameters for Debug
            
    // First Row
    result->matrix[0] = cos(theta);
    result->matrix[4] = -sin(theta)*cos(alpha);
    result->matrix[8] = sin(theta)*sin(alpha);
    result->matrix[12] = a*cos(theta);
    
    // Second Row
    result->matrix[1] = sin(theta);
    result->matrix[5] = cos(theta)*cos(alpha);
    result->matrix[9] = -cos(theta)*sin(alpha);
    result->matrix[13] = a*sin(theta);
    
    // Third Row
    result->matrix[2] = 0;
    result->matrix[6] = sin(alpha);
    result->matrix[10] = cos(alpha);
    result->matrix[14] = d;
    
    // Fourth Row
    result->matrix[3] = 0;
    result->matrix[7] = 0;
    result->matrix[11] = 0;
    result->matrix[15] = 1;
    
    return result;
}

dhmatrix* createMatrix(double* parameters) {
    return createMatrix(parameters[0],parameters[1],parameters[2],parameters[3]);
}
