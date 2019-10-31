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
    
    string imgPath = "${path}ocvTest/ocvTest/src/pants.jpg";
    Mat img = imread(imgPath, 0);
    
    namedWindow("img");
    imshow("img", img);
//    waitKey();
    while (true) {
        if ( waitKey() == 'c' ) break;
    }
    
    return 0;
}
