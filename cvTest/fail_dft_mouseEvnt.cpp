/// dft spectrum and invert to show the orignal image
/// and also filtering the spectrum to change result
///
/// https://www.youtube.com/watch?v=PRoHcorBNgI&list=PLAp0ZhYvW6XbEveYeefGSuLhaPlFML9gP&index=9
/// https://stackoverflow.com/questions/10269456/inverse-fourier-transformation-in-opencv

/// spectrum changing https://vgg.fiit.stuba.sk/2012-05/frequency-domain-filtration/
#include <iostream>
#include "opencv2/opencv.hpp"
#include "dd.h"

using namespace std;
using namespace cv;

void recenterSpectrum(Mat& input);
//void showDFT(Mat& input);
void wait();
void onMouse( int event, int x, int y, int, void* param);
Mat doDFT(Mat img);
Mat createGausFilterMask(Size mask_size, int x, int y, int ksize, bool normalization, bool invert);
void doInvDFT(Mat& input);
void getMag(Mat& input, Mat& output);
void getLogMag(Mat& input);

int kernel_size = 1;

int main(int argc, const char * argv[]) {
    
    Mat img = imread(str_path_download + "test5.jpg", IMREAD_GRAYSCALE);
    namedWindow("invDFT");
    imshow("invDFT", img);
    Mat cmplx, spectrum, result;
    
    cmplx = doDFT(img);
    
    createTrackbar("gaussian kernel size", "invDFT", &kernel_size, 255, 0);
    setMouseCallback("invDFT", onMouse, &cmplx);
    
    getLogMag(cmplx);
    doInvDFT(cmplx);
    wait();

    return 0;
}

Mat doDFT(Mat input)
{
    Mat padded;
    int m = getOptimalDFTSize(input.rows);
    int n = getOptimalDFTSize(input.cols);
    copyMakeBorder(input, padded, 0, m-input.rows, 0, n-input.cols, BORDER_CONSTANT, Scalar::all(0));
    Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
    Mat cmplx;
    merge(planes, 2, cmplx);
    dft(cmplx, cmplx, DFT_COMPLEX_OUTPUT);
    return cmplx;
}

void doInvDFT(Mat& input)
{
    Mat tmp;
    idft(input, tmp);
    Mat planes[] = {Mat::zeros(input.size(), CV_32F), Mat::zeros(input.size(), CV_32F)};
    split(tmp, planes);
    magnitude(planes[0], planes[1], tmp);
    normalize(tmp, tmp, 0, 1, NORM_MINMAX);
    imshow("dftResultImg", tmp);
}

void getLogMag(Mat& input)
{
    Mat showImg;
    Mat planes[] = {Mat::zeros(input.size(), CV_32F), Mat::zeros(input.size(), CV_32F)};
    split(input, planes);
    magnitude(planes[0], planes[1], showImg);
    showImg += Scalar::all(1);
    log(showImg, showImg);
    
    recenterSpectrum(showImg);
    normalize(showImg, showImg, 1, 0, NORM_INF);
    imshow("spectrum_magnitude", showImg);
}

void onMouse( int event, int x, int y, int, void* param)
{
    if ( event == EVENT_LBUTTONDOWN )
    {
        Mat* pCmplx = (Mat*) param;
        Mat complex = *pCmplx;
        Mat mask = createGausFilterMask(complex.size(), x, y, kernel_size, true, true);
        imshow("mask", mask);
        recenterSpectrum(mask);
        Mat kernelSpec, tmp, resultImg;
        Mat tmpPlanes[] = {Mat::zeros(complex.size(), CV_32F), Mat::zeros(complex.size(), CV_32F)};
        tmpPlanes[0] = mask;
        tmpPlanes[1] = mask;
        merge(tmpPlanes, 2, kernelSpec);
        mulSpectrums(complex, kernelSpec, complex, DFT_ROWS);
        getLogMag(complex);
        doInvDFT(complex);
        *pCmplx = resultImg;
    }
}

Mat createGausFilterMask(Size mask_size, int x, int y, int ksize, bool normalization, bool invert) {
    // Some corrections if out of bounds
    if(x < (ksize / 2)) {
        ksize = x * 2;
    }
    if(y < (ksize / 2)) {
        ksize = y * 2;
    }
    if(mask_size.width - x < ksize / 2 ) {
        ksize = (mask_size.width - x ) * 2;
    }
    if(mask_size.height - y < ksize / 2 ) {
        ksize = (mask_size.height - y) * 2;
    }
 
    // call openCV gaussian kernel generator
    double sigma = -1;
    Mat kernelX = getGaussianKernel(ksize, sigma, CV_32F);
    Mat kernelY = getGaussianKernel(ksize, sigma, CV_32F);
    // create 2d gaus
    Mat kernel = kernelX * kernelY.t();
    // create empty mask
    Mat mask = Mat::zeros(mask_size, CV_32F);
    Mat maski = Mat::zeros(mask_size, CV_32F);
 
    // copy kernel to mask on x,y
    Mat pos(mask, Rect(x - ksize / 2, y - ksize / 2, ksize, ksize));
    kernel.copyTo(pos);
 
    // create mirrored mask
    Mat posi(maski, Rect(( mask_size.width - x) - ksize / 2, (mask_size.height - y) - ksize / 2, ksize, ksize));
    kernel.copyTo(posi);
    // add mirrored to mask
    add(mask, maski, mask);
 
    // transform mask to range 0..1
    if(normalization) {
        normalize(mask, mask, 0, 1, NORM_MINMAX);
    }
 
    // invert mask
    if(invert) {
        mask = Mat::ones(mask.size(), CV_32F) - mask;
    }
 
    return mask;
}


//void showDFT(Mat& input)
//{
//    Mat magnitudeDFT;
//    Mat splitAry[2] = {Mat::zeros(input.size(), CV_32F), Mat::zeros(input.size(), CV_32F)};
//    split(input, splitAry);
//    magnitude(splitAry[0], splitAry[1], magnitudeDFT);
//    magnitudeDFT += Scalar::all(1);
//    log(magnitudeDFT, magnitudeDFT);
//    normalize(magnitudeDFT, magnitudeDFT, 0, 1, NORM_MINMAX);
//    recenterSpectrum(magnitudeDFT);
//    imshow("magnitudeDFT", magnitudeDFT);
//}

void recenterSpectrum(Mat& input)
{
    input = input(Rect(0, 0, input.cols & -2, input.rows & -2));
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
