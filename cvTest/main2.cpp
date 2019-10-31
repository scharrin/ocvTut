//  this is about matrix class in open cv
//  main.cpp
//  ocvTest
//
//  Created by macproo on 04/10/2019.
//  Copyright © 2019 macproo. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void printMtx(const Mat _m);

int main(int argc, const char * argv[]) {
    
    Mat mtx(3, 3, CV_32F); // 3x3 32bit float
    Mat cmtx(10, 1, CV_64FC2);  // 10x1 64 float 2 channel matrix
    
    Mat img(Size(5, 3), CV_8UC3); // 3x5 8bit unsigned char 3 channel matrix
    
    Mat mtx2;
    mtx2 = Mat(3, 4, CV_32F);
    Mat cmtx2;
    cmtx2 = Mat(10, 1, CV_64FC1);
    
    Mat* pMtx3 = new Mat(3, 5, CV_32F);
//    delete pMtx3;
    
    mtx2.setTo(10);
//    cout << mtx2 << endl;
    
    pMtx3->setTo(11);
//    cout << pMtx3 << endl;
//    cout << &pMtx3 << endl;
    
    delete pMtx3;
    
    Mat m = Mat::ones(3, 4, CV_64F); // all elem is 1
    m = m * 3;
    
    double doubleMat[3][4] = {{1,2,3,5},{12,23,34,51},{12,32,53,35}};
    Mat doubleMat2 = Mat(3,4,CV_64F, doubleMat);
    // this refer to the source array so if the array changed its value, this matrix also change.
    
    Mat doubleMat3 = Mat(4,4,CV_64F, doubleMat);
    Mat doubleMat4 = Mat(4,3,CV_64F, doubleMat);
    Mat doubleMat5 = Mat(4,1,CV_64F, doubleMat);
    cout << doubleMat2 << endl;
    cout << doubleMat3 << endl; // this fill out one by one from the source array.
    cout << doubleMat4 << endl; // means ignore the source array row and column
    cout << doubleMat5 << endl; // just put one by one to matrix
    
    cout << doubleMat2 + m << endl;
    cout << doubleMat2 - m << endl;
    cout << doubleMat2 / m << endl;

    //    cout << doubleMat2 * m << endl; // error cause * means 'scalar product'
    cout << doubleMat2.mul(m) << endl; // now this means inner product space

    // when the size a, b ( a<>b ) are exist, axb * bxa is possible but not axb * axb.
    // it call also dot product
    
    Mat m2 = Mat(4,3, CV_64F, doubleMat); // 4x3, m is 3x4
    Mat m3 = doubleMat2 * m2; // this work, sizes; 3x4 * 4x3 => 3x3
    cout << m3 << endl;
    
    printMtx(m3.inv());
    // inversion matrix it's input should be squre matrix
    // which has same rows and columns ( axa ).
    
    printMtx(m3.t());
    // trasition matrix which trasit element row and column ( swap element 2,1 <=> element 1,2 )
    
    return 0;
}

void printMtx(const Mat _m)
{
    cout << endl;
    cout << _m << endl;
}

