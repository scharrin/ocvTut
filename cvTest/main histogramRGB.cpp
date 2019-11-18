/// histogram

///
#include <iostream>
#include "opencv2/opencv.hpp"
#include "dd.h"

using namespace std;
using namespace cv;
RNG rng;

int main(int argc, const char * argv[]) {
    
    const int binaryThreshold = 127;
    const int maxThreshold = 255;
    const int lineWeight = 3;
    const int circleRadius = 10;
    int thresholdFromTrackbar = binaryThreshold;
    
    Mat img = imread(str_path_download + "test.jpg");
    Mat img2 = imread(str_path_download + "test2.jpg");
    Mat img3 = imread(str_path_download + "hand.jpg");
    Mat img4 = imread(str_path_download + "test4.png");
    Mat flower = imread(str_path_download + "flower1.jpg");
    Mat flower2 = imread(str_path_download + "flower2.jpg");
    Mat hierTest = imread(str_path_download + "hierachyTest.jpg");
    img = hierTest;
    namedWindow("w");

    /// contour outlines
    Mat imgGray;
    Mat imgBinary;
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy; /// should be 4 channel
    vector<Vec4i> hierarchy_external; /// should be 4 channel
    vector<Vec4i> hierarchy_ccomp; /// should be 4 channel
    vector<Vec4i> hierarchy_tree; /// should be 4 channel

    int channel[] = {0, 1}; /// hue, saturation
    int dims = 2;
    int hueBin = 30;
    int saturationBin = 32;
    int histSize[] = {hueBin, saturationBin};
    float hueRng[] = {0, 180};
    float saturationRng[] = {0, 256};
    const float* rnges[] = {hueRng, saturationRng};
    MatND hist;
    Mat hsvConverted;
    
//    cvtColor(flower, hsvConverted, COLOR_BGR2HSV);
//    /// https://docs.opencv.org/2.4/modules/imgproc/doc/histograms.html
//    calcHist(&hsvConverted, 1, channel, Mat(), hist , dims, histSize, rnges, true, false);
//    double maxVal = 0;
//    minMaxLoc(hist, 0, &maxVal, 0, 0);
//
//    int scale = 10;
//    Mat histImg = Mat::zeros(saturationBin*scale, hueBin*scale, CV_8UC3);
//
//    for ( auto i = 0; i < hueBin; i++ )
//    {
//        for ( auto j = 0; j < saturationBin; j++ )
//        {
//            float binVal = hist.at<float>(i, j);
//            int intensity = cvRound(binVal*255 / maxVal);
//            rectangle(histImg, Point(i*scale, j*scale), Point((i+1)*scale-1, (j+1)*scale-1), Scalar::all(intensity), FILLED);
//        }
//    }
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    int number_bin = 255;
    int hist_w = 512;
    int hist_h = 400;
    int bin_w = round((double)hist_w / number_bin);

//    Mat histPlot(hist_h, hist_w, CV_8UC1);
//    normalize(hist, hist, 0, histPlot.rows, NORM_MINMAX, -1, Mat());
//
//    for ( int i = 0; i < number_bin; i++ )
//    {
//        line(histPlot, Point(bin_w*(i-1), hist_h-round(hist.at<float>(i-1))), Point(bin_w*(i), hist_h-round(hist.at<float>(i))), Scalar(255, 0, 0));
//    }
//
//    namedWindow("hist2");
//    imshow("hist2", histPlot);
//
//    namedWindow("histogram");
//    imshow("histogram", histImg);
    
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////doesn't work here..////////////////////////////////////////////////////////////////////////////
    int chaB[] = {0};
    int chaG[] = {1};
    int chaR[] = {2};
    MatND histB, histG, histR;
    float channelRng[] = {0, 255};
    const float* channelRngs = channelRng;  /// should be constant!!!
    int dimss = 1;
//    vector<Mat> flowerBGR;
//    split(flower, flowerBGR);
    
    ///// error point
    ///// error point
    calcHist(&flower, 1, chaB, Mat(), histB, dimss, &number_bin, &channelRngs);
    calcHist(&flower, 1, chaG, Mat(), histG, dimss, &number_bin, &channelRngs);
    calcHist(&flower, 1, chaR, Mat(), histR, dimss, &number_bin, &channelRngs);
    ///// error point
    ///// error point
    
    Mat histPlotB(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));
    normalize(histB, histB, 0, histPlotB.rows, NORM_MINMAX, -1, Mat());
    Mat histPlotG(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));
    normalize(histG, histG, 0, histPlotG.rows, NORM_MINMAX, -1, Mat());
    Mat histPlotR(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));
    normalize(histR, histR, 0, histPlotR.rows, NORM_MINMAX, -1, Mat());
    
    for ( int i = 1; i < number_bin; i++ )
    {
        line(histPlotB, Point(bin_w*(i-1), hist_h-round(histB.at<float>(i-1))), Point(bin_w*(i), hist_h-round(histB.at<float>(i))), Scalar(255, 0, 0));
        line(histPlotG, Point(bin_w*(i-1), hist_h-round(histG.at<float>(i-1))), Point(bin_w*(i), hist_h-round(histG.at<float>(i))), Scalar(0, 255, 0));
        line(histPlotR, Point(bin_w*(i-1), hist_h-round(histR.at<float>(i-1))), Point(bin_w*(i), hist_h-round(histR.at<float>(i))), Scalar(0, 0, 255));
    }

//    imshow("w", flower);
    namedWindow("histPlotB");
    imshow("histPlotB", histPlotB);
    namedWindow("histPlotG");
    imshow("histPlotG", histPlotG);
    namedWindow("histPlotR");
    imshow("histPlotR", histPlotR);
    
    
    while (1) {
        
        int int_keyInput = waitKey(1000);
        if ( int_keyInput == 27 ) break;    /// esc key
    }
    destroyAllWindows();
    
    return 0;
}
