/// merge png logo image

///
#include <iostream>
#include "opencv2/opencv.hpp"
#include <vector>
#include "dd.h"

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
, testLogo
, roiImg
;

int
thresholdColorLimit = 255
, thresholdMorphSizeLimit
, thresholdColorInitialValue = 100
, thresholdMorphSizeInitialValue = 0
;

int main(int argc, const char * argv[]) {
    
    namedWindow("w");
    string img1FileName = "flower1.jpg";
    //    string img2FileName = "flower2.jpg";
    //    string img2FileName = "${path}${path2}/key-circular-button.png";
    string img2FileName = "logo_2.png";
    matFlower = imread(str_path_download + img1FileName);
//    matImgLogo = imread(img2FileName, -1);
//////problem//////problem//////problem//////problem//////problem
// how can the logo name 'opencv' to white? it has also icons above of the name
//////problem//////problem//////problem//////problem//////problem
//    Mat channels[4];
//    split(matImgLogo, channels);
//    threshold(channels[3], channels[3], 1, 255, THRESH_BINARY);
//    Mat matImgLogo;
//    matImgLogo.copyTo(matImgLogo2, channels[3]);
//    imshow("ttt", matImgLogo2);
    matImgLogo = imread(str_path_download + img2FileName);
//    matImgLogoBG.copySize(matImgLogo);
//    matImgLogoBG.setTo(255);
//    imshow("logo", matImgLogo);
  
    Rect roi(0, 0, matImgLogo.cols, matImgLogo.rows);
    roiOfBgImg = matFlower(roi);
    cvtColor(matImgLogo, matImgLogoGray, COLOR_RGBA2GRAY);

//    if ( matImgLogoGray.rows > matImgLogoGray.cols ) thresholdMorphSizeLimit = matImgLogoGray.cols + 1;
//    else thresholdMorphSizeLimit = matImgLogoGray.rows + 1;

//    createTrackbar("thres", "w", &thresholdColorInitialValue, thresholdColorLimit);
//    createTrackbar("morphSize", "w", &thresholdMorphSizeInitialValue, thresholdMorphSizeLimit);

    int int_keyInput, trackbarValue, trackbarMorphValue;
    
    while (1) {
        trackbarValue = 10;
//        trackbarValue = getTrackbarPos("thres", "w");
//        trackbarMorphValue = getTrackbarPos("morphSize", "w") + 1;
        threshold(matImgLogoGray, imgMask, trackbarValue, thresholdColorLimit, THRESH_BINARY);
//        matMorphKernel = Mat::ones(trackbarMorphValue, trackbarMorphValue, CV_8U);
//        morphologyEx(imgMask, imgMask, MORPH_CLOSE, matMorphKernel);

        bitwise_not(imgMask, imgMaskInv);

        matImgLogo.copyTo(testLogo, imgMask);
        roiOfBgImg.copyTo(roiImg, imgMaskInv);

        add(testLogo, roiImg, result);
//        imshow("tt", result);

//////problem//////problem//////problem//////problem//////problem
        //////////// here's some problem.. images are not glues

//        matFlower.(roi) = result; //// not working..
//////problem//////problem//////problem//////problem//////problem
        for (int i = 0; i < matImgLogo.rows; ++i)
        {
            for (int j = 0; j < matImgLogo.cols; ++j)
            {
                matFlower.at<Vec3b>(i, j) = result.at<Vec3b>(i, j);
            }
        }
//        Mat result2;
//        add(result, roiOfBgImg, result2);
        imshow("w", matFlower);
        int_keyInput = waitKey(1);
        if ( int_keyInput == 27 ) break;    /// esc key
    }
    destroyAllWindows();
    
    return 0;
}
