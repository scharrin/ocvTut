/// coloring window with trackbar

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
    createTrackbar("b", "w", 0, 255);
    createTrackbar("g", "w", 0, 255);
    createTrackbar("r", "w", 0, 255);
    string swTitle = "1: on/n0: off";
    createTrackbar(swTitle, "w", 0, 1);
    
    int int_keyInput, r, g, b, sw;
    while (1) {
        imshow("w", window);
        int_keyInput = waitKey(1);
        if ( int_keyInput == 27 ) break;    /// esc key

        r = getTrackbarPos("r", "w");
        g = getTrackbarPos("g", "w");
        b = getTrackbarPos("b", "w");
        sw = getTrackbarPos(swTitle, "w");
        
        if ( sw == false ) window.setTo(0);
        else window.setTo(Vec3b(b, g, r));
    }
    destroyAllWindows();
    
    return 0;
}



