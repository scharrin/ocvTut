//
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
    
    cout << "opencv version : " << CV_VERSION << endl;
    cout << "opencv major version : " << CV_MAJOR_VERSION << endl;
    cout << "opencv MINOR version : " << CV_MINOR_VERSION << endl;
    cout << "opencv SUBMINOR version : " << CV_SUBMINOR_VERSION << endl;

    return 0;
}
