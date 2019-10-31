/// ROI... it seems like just rectangular ranged matrix..

///
#include <iostream>
#include "opencv2/opencv.hpp"
#include <vector>

using namespace std;
using namespace cv;

Mat
window(300, 300, CV_8UC3);

int main(int argc, const char * argv[]) {
    
    namedWindow("w");
    window.setTo(255);
    string filePath = "${path}cvTest/src/jacket.jpg";
    window = imread(filePath);
    imshow("w", window);
    
    Rect roi(50, 30, 100, 130);
    imshow("w2", window(roi));
    Mat window2 = window;
    window2.adjustROI(-10, -100, 40, 39);
    imshow("w3", window2);
    Mat roi3 = window(Rect(100, 200, 400, 340));
    Mat window3;
    roi3.copyTo(window3);
    imshow("w4", window3);
    
    int int_keyInput;
    while (1) {
//        imshow("w", window);
        int_keyInput = waitKey(1);
        if ( int_keyInput == 27 ) break;    /// esc key
    }
    destroyAllWindows();
    
    return 0;
}



