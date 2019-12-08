///2nd hitogram

///
#include <iostream>
#include "opencv2/opencv.hpp"
#include "dd.h"

using namespace std;
using namespace cv;

int main(int argc, const char * argv[]) {
    
    Mat img = imread(str_path_download + "test5.jpg");
    namedWindow("w");

    MatND hist;
    Mat imgHSV;
    cvtColor(img, imgHSV, COLOR_BGR2HSV);
    
    int hue_bins = 30;  /// rows in the result histogram
    int sat_bins = 32;  /// cols
    int hue_max = 180;
    int sat_max = 255;
    int histSize[] = {hue_bins, sat_bins};
    float rngHue[] = {0, (float)hue_max};
    float rngSat[] = {0, (float)sat_max};
    const float* rngs[] = {rngHue, rngSat};
    int channel[] = {0, 1};
    int dim = 2;
    
    calcHist(&imgHSV, 1, channel, Mat(), hist, dim, histSize, rngs);
    normalize(hist, hist, hue_max, 0, NORM_MINMAX);
    
    int histRw = hue_max;
    int histCol = sat_max;
    int tmpSat = 255;
    int tmpVal = 255;
    int tmpR = 0;
    int tmpG = 0;
    int tmpB = 0;
    int tmpHue;
    Scalar tmpColar;
    Mat histColor(Size(sat_bins, hue_bins), CV_8UC3, Scalar(0, 0, 0));
    
    for ( int i = 0; i < hue_bins; i++ )
    {
        for (int j = 0; j < sat_bins; j++ )
        {
//            tmpHue = (int) hist.at<float>(i, j);
            tmpHue = 1;
            if ( 0 < tmpHue && tmpHue < 30 )
            {
                tmpR = tmpVal * tmpSat;
                tmpG = tmpVal * tmpSat * (1 - abs((tmpHue / 30)%2 - 1));
                tmpB = 0;

            }
            else if ( 30 <= tmpHue && tmpHue < 60 )
            {
                tmpR = tmpVal * tmpSat * (1 - abs((tmpHue / 30)%2 - 1));
                tmpG = tmpVal * tmpSat;
                tmpB = 0;
            }
            else if ( 60 <= tmpHue && tmpHue < 90 )
            {
                tmpR = 0;
                tmpG = tmpVal * tmpSat;
                tmpB = tmpVal * tmpSat * (1 - abs((tmpHue / 30)%2 - 1));
            }
            else if ( 90 <= tmpHue && tmpHue < 120 )
            {
                tmpR = 0;
                tmpG = tmpVal * tmpSat * (1 - abs((tmpHue / 30)%2 - 1));
                tmpB = tmpVal * tmpSat;
            }
            else if ( 120 <= tmpHue && tmpHue < 150 )
            {
                tmpR = tmpVal * tmpSat * (1 - abs((tmpHue / 30)%2 - 1));
                tmpG = 0;
                tmpB = tmpVal * tmpSat;
            }
            else if ( 150 <= tmpHue && tmpHue < 180 )
            {
                tmpR = tmpVal * tmpSat;
                tmpG = 0;
                tmpB = tmpVal * tmpSat * (1 - abs((tmpHue / 30)%2 - 1));
            }
            if ( tmpHue == 0 ) tmpColar = Scalar(255, 255, 255);
            else
            {
                tmpColar = Scalar( (tmpB+tmpVal-tmpVal*tmpSat)*255
                                  , (tmpG+tmpVal-tmpVal*tmpSat)*255
                                  , (tmpR+tmpVal-tmpVal*tmpSat)*255);
            }
            circle(histColor, Point(i, j), 1, tmpColar);
        }
    }
    imshow("histColor", histColor);
    
    cout << hist << endl; ///   row 30 cols 32
    
//    imshow("img", img);
//    imshow("hist", hist);
    
//    int graphW = 400;
//    int graphH = 300;
//    int
//    relValY
//    , relEqualizedValY
//    , relCLAHEEqualizedValY
//    ;
//    int mostHit = 0;
//    Scalar graphLine(255, 255, 255);
//    Mat graph(graphH, graphW, CV_8UC1, Scalar(0, 0, 0));
//    Mat graphEqu(graphH, graphW, CV_8UC1, Scalar(0, 0, 0));
//    Mat graphEquCLAHE(graphH, graphW, CV_8UC1, Scalar(0, 0, 0));
//
//    Mat normalizedHist;
//    Mat equalizedHist;
//    Mat equalizedImg;
//    Mat CLAHEequalizedImg;
//    Mat CLAHEequalizedHist;
//
//    normalize(hist, normalizedHist, 0, histSize, NORM_MINMAX);
//    equalizeHist(img, equalizedImg);
//    /// CV_EXPORTS_W Ptr<CLAHE> createCLAHE(double clipLimit = 40.0, Size tileGridSize = Size(8, 8));
//    Ptr<CLAHE> Clahe = createCLAHE(2.0);
//    Clahe->apply(img, CLAHEequalizedImg);
//
//    for ( int i = 0; i < histSize; i++ )
//    {
//        if ( mostHit < hist.at<float>(i) ) mostHit = hist.at<float>(i);
//    }
//
//    for ( int i = 0; i < histSize; i++ )
//    {
//        relValY = hist.at<float>(i) * graphH / (float)mostHit;
//        relEqualizedValY = equalizedHist.at<float>(i) * graphH / (float)mostHit;
//        relCLAHEEqualizedValY = CLAHEequalizedHist.at<float>(i) * graphH / (float)mostHit;
//        line(graph, Point(i, graphH), Point(i, graphH-relValY), graphLine);
//        line(graphEqu, Point(i, graphH), Point(i, graphH-relEqualizedValY), graphLine);
//        line(graphEquCLAHE, Point(i, graphH), Point(i, graphH-relCLAHEEqualizedValY), graphLine);
//    }
//
//    imshow("w", img);
//    imshow("graph", graph);
//    imshow("graphEqu", graphEqu);
//    imshow("graphEquCLAHE", graphEquCLAHE);
//    imshow("equalizedImg", equalizedImg);
//    imshow("CLAHEequalizedImg", CLAHEequalizedImg);

    while (1) {
        
        int int_keyInput = waitKey(1000);
        if ( int_keyInput == 27 ) break;    /// esc key
    }
    destroyAllWindows();
    
    return 0;
}
