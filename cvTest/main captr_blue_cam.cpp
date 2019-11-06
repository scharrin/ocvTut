/// showing blue things on cam

///
#include <iostream>
#include "opencv2/opencv.hpp"
#include <vector>

using namespace std;
using namespace cv;

int main(int argc, const char * argv[]) {
    
    namedWindow("w");
    
    VideoCapture vc(0);
    vc.set(CAP_PROP_FRAME_WIDTH, 320);
    vc.set(CAP_PROP_FRAME_HEIGHT, 240);
    
    Mat
    capturedFrame
    , mask
    , result
    , capturedFrameHSV
    ;
    Vec3b
    lower_blue
    , upper_blue
    ;
    int int_keyInput;
    
    while (1) {
    
        vc >> capturedFrame;
        
        if ( capturedFrame.empty() == true ) break;
        
        cvtColor(capturedFrame, capturedFrameHSV, COLOR_BGR2HSV);
        lower_blue = {110, 50, 50};
        upper_blue = {130, 255, 255};
        
        inRange( capturedFrameHSV, lower_blue, upper_blue, mask );
        bitwise_and(capturedFrame, capturedFrame, result, mask);
        imshow("w1", mask);
        imshow("w2", result);
        imshow("w", capturedFrame);
        int_keyInput = waitKey(1);
        if ( int_keyInput == 27 ) break;    /// esc key
    }
    destroyAllWindows();
    
    return 0;
}
