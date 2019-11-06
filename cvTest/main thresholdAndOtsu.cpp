/// threshold, adaptive-threshold, otsu threshold

///
#include <iostream>
#include "opencv2/opencv.hpp"
#include <vector>

using namespace std;
using namespace cv;

int int_keyInput;

int main(int argc, const char * argv[]) {
    
    namedWindow("w");
    
//    string imgPath = "${path}flower1.jpg";
//    string imgPath = "${path}imagenoise_tones.jpg";
    string imgPath = "/${path}noize image sample.png";
    Mat mat_img = imread(imgPath, 0);
    Mat
    mat_effectedGlobal_img
    , mat_effectedGlobalOtsu_img
    , mat_effectedBlurGlobalOtsu_img
    , mat_effectedMean_img
    , mat_effectedGaussian_img
    , mat_effectedBlurred_img
    ;
    double
    douThreshVal = 127
    , douThreshVal2 = 0
    , douThreshMax = 255
    ;
    
    threshold(mat_img, mat_effectedGlobal_img, douThreshVal, douThreshMax, THRESH_BINARY);
    threshold(mat_img, mat_effectedGlobalOtsu_img, douThreshVal2, douThreshMax, THRESH_BINARY + THRESH_OTSU);
    GaussianBlur(mat_img, mat_effectedBlurred_img, Size(5,5), 0);
    threshold(mat_effectedBlurred_img, mat_effectedBlurGlobalOtsu_img, douThreshVal2, douThreshMax, THRESH_BINARY+THRESH_OTSU);
    adaptiveThreshold(mat_img, mat_effectedMean_img, douThreshMax, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 15, 2);
    adaptiveThreshold(mat_img, mat_effectedGaussian_img, douThreshMax, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 15, 2);
    imshow("normal", mat_img);
    imshow("global", mat_effectedGlobal_img);
    imshow("otsu", mat_effectedGlobalOtsu_img);
    imshow("blurOtsu", mat_effectedBlurGlobalOtsu_img);
    imshow("mean", mat_effectedMean_img);
    imshow("gausi", mat_effectedGaussian_img);
    
    /// Otsu threshold
    /// For bimodal image which has 2 peaks in histogram, Otsu threshold can make binary the image automatically.
    /// first things to do that, emerge
    
    while (1) {
    
//        vc >> capturedFrame;
//
//        if ( capturedFrame.empty() == true ) break;
//
//        cvtColor(capturedFrame, capturedFrameHSV, COLOR_BGR2HSV);
//        lower_blue = {110, 50, 50};
//        upper_blue = {130, 255, 255};
//
//        inRange( capturedFrameHSV, lower_blue, upper_blue, mask );
//        bitwise_and(capturedFrame, capturedFrame, result, mask);
//        imshow("w1", mask);
//        imshow("w2", result);
//        imshow("w", capturedFrame);
        int_keyInput = waitKey(1);
        if ( int_keyInput == 27 ) break;    /// esc key
    }
    destroyAllWindows();
    
    return 0;
}
