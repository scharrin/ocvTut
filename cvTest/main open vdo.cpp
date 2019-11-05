// lec2  about mat 1

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
    
    const string mvPath = "${downloadPath}2019_earthquaketraining.mp4";
    VideoCapture mv(mvPath);
    Mat frame;
    
    ///checking file is opened
    if ( mv.isOpened() == false )
    {
        printf("fail to load the movie file in\n");
        cout << mvPath << endl;
        return 0;
    }
    
    /// create window named mv
    namedWindow("mv");
    
    while (1) {
//        mv >> frame;
        mv.read(frame);
        
        if ( frame.empty() )
        {
            break;
        }
        
        imshow("mv", frame);
        if ( waitKey(30) > 0 ) break;
    }
    
    return 0;
}
