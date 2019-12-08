///dft spectrum and invert to show the orignal image

/// https://stackoverflow.com/questions/10269456/inverse-fourier-transformation-in-opencv
/// https://www.youtube.com/watch?v=PRoHcorBNgI&list=PLAp0ZhYvW6XbEveYeefGSuLhaPlFML9gP&index=9
#include <iostream>
#include "opencv2/opencv.hpp"
#include "dd.h"

using namespace std;
using namespace cv;


void getDFT(Mat& input, Mat& output);
void recenterSpectrum(Mat& input);
void showDFT(Mat& input);
void wait();

int main(int argc, const char * argv[]) {
    
    Mat img = imread(str_path_download + "test5.jpg", IMREAD_GRAYSCALE);

    Mat floatImg, dftImg, invdftImg, resultImg;
    img.convertTo(floatImg, CV_32F);
    
    Mat dftOriginal, invDFT;
    dft(floatImg, dftOriginal, DFT_COMPLEX_OUTPUT);
    ///  if + dft_scale the spectrum gets smaller

//    getDFT(floatImg, dftOriginal);
    
    showDFT(dftOriginal);
    dft(dftOriginal, invDFT, DFT_INVERSE|DFT_REAL_OUTPUT|DFT_SCALE);
    /// if - dft_scale the result image goes to different
    
//    cout << invDFT << endl;
    /// this shows some close integers like 107.9999 should be 107 or 108 to draw. so
    
    invDFT.convertTo(resultImg, CV_8U);
    /// needed also, if not, the result image goes to different
    
    imshow("invDFT", resultImg);
    
    wait();

    return 0;
}

void getDFT(Mat& input, Mat& output)
{
    Mat originalComplex[2] = { input, Mat::zeros(input.size(), CV_32F)};
    Mat tmp;
    merge(originalComplex, 2, tmp); ///  not needed
    dft(tmp, output, DFT_COMPLEX_OUTPUT);
}

void showDFT(Mat& input)
{
    Mat magnitudeDFT;
    Mat splitAry[2] = {Mat::zeros(input.size(), CV_32F), Mat::zeros(input.size(), CV_32F)};
    split(input, splitAry);
    magnitude(splitAry[0], splitAry[1], magnitudeDFT);
    magnitudeDFT += Scalar::all(1);
    log(magnitudeDFT, magnitudeDFT);
    normalize(magnitudeDFT, magnitudeDFT, 0, 1, NORM_MINMAX);
    recenterSpectrum(magnitudeDFT);
    imshow("magnitudeDFT", magnitudeDFT);
}

void recenterSpectrum(Mat& input)
{
    int cx = input.cols/2;
    int cy = input.rows/2;
    Mat q1(input, Rect(0,0,cx,cy));
    Mat q2(input, Rect(cx,0,cx,cy));
    Mat q3(input, Rect(0,cy,cx,cy));
    Mat q4(input, Rect(cx,cy,cx,cy));
    Mat tmp;
    
    q4.copyTo(tmp);
    q1.copyTo(q4);
    tmp.copyTo(q1);
    q3.copyTo(tmp);
    q2.copyTo(q3);
    tmp.copyTo(q2);
}

void wait()
{
    while (1) {
        
        int int_keyInput = waitKey(1000);
        if ( int_keyInput == 27 ) break;    /// esc key
    }
    destroyAllWindows();
}
