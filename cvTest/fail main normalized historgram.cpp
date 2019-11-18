/// histogram

///
#include <iostream>
#include "opencv2/opencv.hpp"
#include "dd.h"

using namespace std;
using namespace cv;
RNG rng;

int main(int argc, const char * argv[]) {
    
    Mat img = imread(str_path_download + "histogramTest2.png");
    namedWindow("w");
    imshow("w", img);

    Mat img_gray;
    cvtColor(img, img_gray, COLOR_RGB2GRAY);
    img_gray.reshape(1);
    MatND hist;
    int histSize = 255;
    float rng[] = {0, 255};
    float* rngs[] = {rng};
    int channel[] = {0};
    int dim = 1;
    calcHist(&img_gray, 1, channel, Mat(), hist, dim, histSize, rngs);
    
    while (1) {
        
        int int_keyInput = waitKey(1000);
        if ( int_keyInput == 27 ) break;    /// esc key
    }
    destroyAllWindows();
    
    return 0;
}
