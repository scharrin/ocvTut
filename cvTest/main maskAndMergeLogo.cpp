/// merge images by addweighted

///
#include <iostream>
#include "opencv2/opencv.hpp"
#include <vector>

using namespace std;
using namespace cv;

Mat
matFlower
, matImgLogo
, matImgLogoBG
, matImgLogoGray
, result
, imgMask
, imgMaskInv
, matMorphKernel
, roiOfBgImg
;

int
thresholdColorLimit = 255
, thresholdMorphSizeLimit
, thresholdColorInitialValue = 10
, thresholdMorphSizeInitialValue = 0
;

int main(int argc, const char * argv[]) {
    
    namedWindow("w");
    string filePath = "${path}Downloads/";
    string img1FileName = "flower1.jpg";
    //    string img2FileName = "flower2.jpg";
    //    string img2FileName = "${path}${path2}cvTest/cvTest/src/key-circular-button.png";
    string img2FileName = "${path}Downloads/logo_2.png";
    matFlower = imread(filePath + img1FileName);
    //    matImgLogo = imread(img2FileName, -1);
    //    Mat channels[4];
    //    split(matImgLogo, channels);
    //    bitwise_not(channels[3], channels[3]);
    //    imshow("logo", channels[3]);
      
    matImgLogo = imread(img2FileName);
    //    matImgLogoBG.copySize(matImgLogo);
    //    matImgLogoBG.setTo(255);
    //    imshow("logo", matImgLogo);
  
    Rect roi(0, 0, matImgLogo.cols, matImgLogo.rows);
    roiOfBgImg = matFlower(roi);
    cvtColor(matImgLogo, matImgLogoGray, COLOR_RGB2GRAY);
    
//    if ( matImgLogoGray.rows > matImgLogoGray.cols ) thresholdMorphSizeLimit = matImgLogoGray.cols + 1;
//    else thresholdMorphSizeLimit = matImgLogoGray.rows + 1;
    
    createTrackbar("thres", "w", &thresholdColorInitialValue, thresholdColorLimit);
//    createTrackbar("morphSize", "w", &thresholdMorphSizeInitialValue, thresholdMorphSizeLimit);
    
    int int_keyInput, trackbarValue, trackbarMorphValue;
    
    while (1) {
        trackbarValue = getTrackbarPos("thres", "w");
//        trackbarMorphValue = getTrackbarPos("morphSize", "w") + 1;
        threshold(matImgLogoGray, imgMask, trackbarValue, thresholdColorLimit, THRESH_BINARY);
//        matMorphKernel = Mat::ones(trackbarMorphValue, trackbarMorphValue, CV_8U);
//        morphologyEx(imgMask, imgMask, MORPH_CLOSE, matMorphKernel);
        
        bitwise_not(imgMask, imgMaskInv);

//        matImgLogo.copyTo(matImgLogo, imgMask);
//        roiOfBgImg.copyTo(roiOfBgImg, imgMaskInv);
        
        bitwise_and(matImgLogo, matImgLogo, matImgLogo, imgMask);
        bitwise_and(roiOfBgImg, roiOfBgImg, roiOfBgImg, imgMaskInv);
        
        add(roiOfBgImg, matImgLogo,  result);
//        imshow("w1", result);

        matFlower(roi) = result;
        imshow("w", matFlower);
        int_keyInput = waitKey(1);
        if ( int_keyInput == 27 ) break;    /// esc key
    }
    destroyAllWindows();
    
    return 0;
}
