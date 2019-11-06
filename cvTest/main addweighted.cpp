/// merge images by addweighted

///
#include <iostream>
#include "opencv2/opencv.hpp"
#include <vector>

using namespace std;
using namespace cv;

Mat
matFlower
, matFlower2
, result
;

int main(int argc, const char * argv[]) {
    
    namedWindow("w");
    string filePath = "${path}Downloads/";
    string img1FileName = "flower1.jpg";
    string img2FileName = "flower2.jpg";

    matFlower = imread(filePath + img1FileName);
    matFlower2 = imread(filePath + img2FileName);
    
    createTrackbar("merge", "w", 0, 100);
    
    int int_keyInput, trackbarValue;
    
    while (1) {
        trackbarValue = getTrackbarPos("merge", "w");
        addWeighted(matFlower, 0.01 * ( 100 - trackbarValue ), matFlower2, 0.01 * trackbarValue, 0.0, result);
        
        imshow("w", result);
        int_keyInput = waitKey(1);
        if ( int_keyInput == 27 ) break;    /// esc key
    }
    destroyAllWindows();
    
    return 0;
}



