/// blur

///
#include <iostream>
#include "opencv2/opencv.hpp"
#include "dd.h"

using namespace std;
using namespace cv;

int main(int argc, const char * argv[]) {
    
    Mat img = imread(str_path_download + "file_example_PNG_500kB.png");
    namedWindow("w");
    createTrackbar("kunn", "w", 0, 20);
    
    int trackVal;
    Mat kernel;
    Mat result1;
    Mat result2;
    Mat result3;
    Mat result4;
    Mat result5;
    
    blur(img, result2, Size(7, 7));
    GaussianBlur(img, result3, Size(5, 5), 0);
    medianBlur(img, result4, 9);
    bilateralFilter(img, result5, 9, 75, 75);
    imshow("w2", result2);
    imshow("w3", result3);
    imshow("w4", result4);
    imshow("w5", result5);

    while (1) {
        
        trackVal = getTrackbarPos("kunn", "w");
        if ( trackVal == 0 ) trackVal = 1;
        
        kernel = Mat::ones(trackVal, trackVal, CV_32F) / (trackVal / 2);
        filter2D(img, result1, -1, kernel);
        
        imshow("w", result1);
        int int_keyInput = waitKey(100);
        if ( int_keyInput == 27 ) break;    /// esc key
    }
    destroyAllWindows();
    
    return 0;
}
