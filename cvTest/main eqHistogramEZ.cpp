/// equalize histogram, CLAHE

///
#include <iostream>
#include "opencv2/opencv.hpp"
#include "dd.h"

using namespace std;
using namespace cv;
RNG rng;

int main(int argc, const char * argv[]) {
    
    Mat img = imread(str_path_download + "test4.png", 0);
    namedWindow("w");

    MatND hist;
    int histSize = 255;
    float rng[] = {0, 255};
    const float* rngs = rng;
    int channel[] = {0};
    int dim = 1;
    calcHist(&img, 1, channel, Mat(), hist, dim, &histSize, &rngs);
    
    int graphW = 400;
    int graphH = 300;
    int
    relValY
    , relEqualizedValY
    , relCLAHEEqualizedValY
    ;
    int mostHit = 0;
    Scalar graphLine(255, 255, 255);
    Mat graph(graphH, graphW, CV_8UC1, Scalar(0, 0, 0));
    Mat graphEqu(graphH, graphW, CV_8UC1, Scalar(0, 0, 0));
    Mat graphEquCLAHE(graphH, graphW, CV_8UC1, Scalar(0, 0, 0));

    Mat normalizedHist;
    Mat equalizedHist;
    Mat equalizedImg;
    Mat CLAHEequalizedImg;
    Mat CLAHEequalizedHist;

    normalize(hist, normalizedHist, 0, histSize, NORM_MINMAX);
    equalizeHist(img, equalizedImg);
    /// CV_EXPORTS_W Ptr<CLAHE> createCLAHE(double clipLimit = 40.0, Size tileGridSize = Size(8, 8));
    Ptr<CLAHE> Clahe = createCLAHE(2.0);
    Clahe->apply(img, CLAHEequalizedImg);
    
    calcHist(&equalizedImg, 1, channel, Mat(), equalizedHist, 1, &histSize, &rngs);
    calcHist(&CLAHEequalizedImg, 1, channel, Mat(), CLAHEequalizedHist, 1, &histSize, &rngs);

    for ( int i = 0; i < histSize; i++ )
    {
        if ( mostHit < hist.at<float>(i) ) mostHit = hist.at<float>(i);
    }

    for ( int i = 0; i < histSize; i++ )
    {
        relValY = hist.at<float>(i) * graphH / (float)mostHit;
        relEqualizedValY = equalizedHist.at<float>(i) * graphH / (float)mostHit;
        relCLAHEEqualizedValY = CLAHEequalizedHist.at<float>(i) * graphH / (float)mostHit;
        line(graph, Point(i, graphH), Point(i, graphH-relValY), graphLine);
        line(graphEqu, Point(i, graphH), Point(i, graphH-relEqualizedValY), graphLine);
        line(graphEquCLAHE, Point(i, graphH), Point(i, graphH-relCLAHEEqualizedValY), graphLine);
    }
    
    imshow("w", img);
    imshow("graph", graph);
    imshow("graphEqu", graphEqu);
    imshow("graphEquCLAHE", graphEquCLAHE);
    imshow("equalizedImg", equalizedImg);
    imshow("CLAHEequalizedImg", CLAHEequalizedImg);

    while (1) {
        
        int int_keyInput = waitKey(1000);
        if ( int_keyInput == 27 ) break;    /// esc key
    }
    destroyAllWindows();
    
    return 0;
}
