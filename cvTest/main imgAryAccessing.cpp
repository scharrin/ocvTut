// direct access img by matrix class
//  main4.cpp
//  ocvTest
//
//  Created by macproo on 16/10/2019.
//  Copyright © 2019 macproo. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, const char * argv[]) {
    
    namedWindow("img", 1);
    Mat img
    = imread("${path}ocvTest/ocvTest/src/sweater.jpg");

//    if ( img.depth() == CV_8U )
//        printf("8bit unsinged \n");
    
    /// access image by matrix
    /// using at
    for ( int i = img.rows / 10 * 2; i < img.rows / 10 * 3; ++i )
    {
        for ( int j = 0; j < img.cols; ++j )
        {
            /// vec3b means unchar 3ch
            unsigned char b = img.at< Vec3b >(i, j)[0];
            unsigned char g = img.at< Vec3b >(i, j)[1];
            unsigned char r = img.at< Vec3b >(i, j)[2];
            
            /// printf( "%d, %d, %d=n", b, g, r);
            img.at< Vec3b >(i, j)[0] = (unsigned char)(255 - b);  /// set an effect
            img.at< Vec3b >(i, j)[1] = (unsigned char)(255 - g);
            img.at< Vec3b >(i, j)[2] = (unsigned char)(255 - r);
        }
    }
    
    /// ptr way
    for ( int i = img.rows / 10 * 6; i < img.rows / 10 * 7; ++i )
    {
        Vec3b* ptr = img.ptr< Vec3b >(i);
        for ( int j = 0; j < img.cols; ++j )
        {
            Vec3b bgr = ptr[j];
            unsigned char b = bgr[0];
            unsigned char g = ptr[j][1];
            /// unsgined char g = bgr[1]; /// (same)
            unsigned char r = bgr[2];
            
            ptr[j] = Vec3b(255 - b, 255 - g, 255 - r);
        }
    }
    
    /// using data
    for ( int i = img.rows / 10 * 8 ; i < img.rows; ++i )
    {
        for ( int j = 0; j < img.cols; ++j )
        {
            unsigned char b, g, r;
            b = img.data[i + img.step + j * img.elemSize() + 0];
            g = img.data[i + img.step + j * img.elemSize() + 1];
            r = img.data[i + img.step + j * img.elemSize() + 2];
            
            img.data[i + img.step + j * img.elemSize() + 0]
            = (unsigned char) 255 - b;
            img.data[i + img.step + j * img.elemSize() + 1]
            = (unsigned char) 255 - g;
            img.data[i + img.step + j * img.elemSize() + 2]
            = (unsigned char) 255 - r;
        }
    }
    
    /// using iterater
    
    MatIterator_<Vec3b> itd = img.begin<Vec3b>(), itd_end = img.end<Vec3b>();
    for ( ;itd != itd_end; itd++ )
    {
        Vec3b bgr = *itd;
        (*itd)[0] = 255 - bgr[0];
        (*itd)[1] = 255 - bgr[1];
        (*itd)[2] = 255 - bgr[2];
    }
    
    imshow("img", img);
    waitKey();
    destroyAllWindows();
    
    return 0;
}
