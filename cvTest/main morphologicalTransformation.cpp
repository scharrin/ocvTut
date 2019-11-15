/// mophological transformation

///
#include <iostream>
#include "opencv2/opencv.hpp"
#include "dd.h"

using namespace std;
using namespace cv;

int main(int argc, const char * argv[]) {
    
    Mat img = imread(str_path_download + "imagenoise_tones.jpg");
    namedWindow("w");
    
    int trackVal;
    Mat kernel;
    Mat resultErosion;
    Mat resultDilation;
    Mat resultOpening;
    Mat resultClosing;
    Mat resultGradient;
    Mat resultTophat;
    Mat resultBlackhat;
    
    kernel = getStructuringElement(MORPH_RECT, Size(5,5));
    
    erode(img, resultErosion, kernel);
    dilate(img, resultDilation, kernel);
    morphologyEx(img, resultOpening, MORPH_OPEN, kernel);
    morphologyEx(img, resultClosing, MORPH_CLOSE, kernel);
    morphologyEx(img, resultGradient, MORPH_GRADIENT, kernel);
    morphologyEx(img, resultTophat, MORPH_TOPHAT, kernel);
    morphologyEx(img, resultBlackhat, MORPH_BLACKHAT, kernel);
    
    imshow("resultErosion", resultErosion);
    imshow("resultDilation", resultDilation);
    imshow("resultOpening", resultOpening);
    imshow("resultClosing", resultClosing);
    imshow("resultGradient", resultGradient);
    imshow("resultTophat", resultTophat);
    imshow("resultBlackhat", resultBlackhat);
    
    while (1) {
        
    
        int int_keyInput = waitKey(100);
        if ( int_keyInput == 27 ) break;    /// esc key
    }
    destroyAllWindows();
    
    return 0;
}
