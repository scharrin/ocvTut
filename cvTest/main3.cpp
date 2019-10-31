//  this is about image showing
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

int main(int argc, const char * argv[]) {
    
    namedWindow("imgWindow", 0);
    namedWindow("imgWindow2", 0);
    namedWindow("imgWindow3", 0);
    
    Mat img = imread("${path}ocvTest/ocvTest/src/sweater.jpg");
    Mat img2, img3;
    Sobel(img, img2, img.depth(), 1, 0); // set an effect
    flip(img, img3, 1); // flip image
    
    imshow("imgWindow", img);
    imshow("imgWindow2", img2);
    imshow("imgWindow3", img3);
    
    waitKey(); // wait any key for unlimited time, also 0 unlimited
    
    destroyAllWindows();
    
    return 0;
}
