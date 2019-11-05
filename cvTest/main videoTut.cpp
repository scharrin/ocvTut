//
//  main.cpp
//  cvTest
//
//  Created by macproo on 25/10/2019.
//  Copyright © 2019 macproo. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, const char * argv[]) {
    
    const string mvPath = "${downloadPath}2019_earthquaketraining.mp4";
    Mat edges;
    namedWindow("edges",1);

//    VideoCapture cap(mvPath); // get video from file
    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened()) { // check if we succeeded
        std::cout << "no capture device :(\n";
        return -1;
    }

    while(1)
    {
        Mat frame;
        cap >> frame; // get a new frame from camera
        
        if ( frame.empty() )
        {
            break;
        }
        
        // add an effect
        Sobel(frame, frame, frame.depth(), 1, 0);
        
//        cvtColor(frame, edges, COLOR_BGR2GRAY);
//        GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
//        Canny(edges, edges, 0, 30, 3);
        imshow("edges", frame);
        if(waitKey(30) >= 0) break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}
