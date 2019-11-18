/// find most points by contour

///
#include <iostream>
#include "opencv2/opencv.hpp"
#include "dd.h"

using namespace std;
using namespace cv;

int main(int argc, const char * argv[]) {
    
    const int binaryThreshold = 127;
    const int maxThreshold = 255;
    const int lineWeight = 3;
    const int circleRadius = 10;
    struct mostPoints {
        Point rightMost;
        Point leftMost;
        Point topMost;
        Point bottomMost;
    };
    Mat img = imread(str_path_download + "test.jpg");
    Mat img2 = imread(str_path_download + "test2.jpg");
    Mat img3 = imread(str_path_download + "hand.jpg");
    Mat img4 = imread(str_path_download + "test4.png");
//    img = img4;
    namedWindow("w");
    
    /// contour outlines
    Mat imgGray;
    Mat imgBinary;
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy; /// should be 4 channel
    
    cvtColor(img, imgGray, COLOR_BGR2GRAY);
    threshold(imgGray, imgBinary, binaryThreshold, maxThreshold, 0);
    findContours(imgBinary, contours, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE);
    
    mostPoints mp;
    int maxIdxX, minIdxX, maxIdxY, minIdxY;
    
    for ( int i = 0; i < contours.size(); i++ )
    {
        maxIdxX = 0;
        minIdxX = 0;
        maxIdxY = 0;
        minIdxY = 0;
        mp.rightMost = contours[i][0];
        mp.leftMost = contours[i][0];
        mp.topMost = contours[i][0];
        mp.bottomMost = contours[i][0];
        
        for ( int j = 0; j < contours[i].size(); j++ )
        {
            if ( contours[i][j].x > contours[i][maxIdxX].x )
            {
                maxIdxX = j;
                mp.rightMost = contours[i][j];
            }
            else if ( contours[i][j].x < contours[i][minIdxX].x )
            {
                minIdxX = j;
                mp.leftMost = contours[i][j];
            }
            else if ( contours[i][j].y > contours[i][maxIdxY].y )
            {
                maxIdxY = j;
                mp.topMost = contours[i][j];
            }
            else if ( contours[i][j].y < contours[i][minIdxY].y )
            {
                minIdxY = j;
                mp.bottomMost = contours[i][j];
            }
        }
        circle(img, mp.rightMost, circleRadius, Scalar(255, 0, 0), lineWeight);
        circle(img, mp.leftMost, circleRadius, Scalar(255, 255, 0), lineWeight);
        circle(img, mp.topMost, circleRadius, Scalar(255, 0, 255), lineWeight);
        circle(img, mp.bottomMost, circleRadius, Scalar(0, 0, 255), lineWeight);
        
    }
    
//    for ( int i = 0; i < contours.size(); i++ )
//    {
//        drawContours(img, contours, i, Scalar(0, 255, 0), 1);
//    }

    imshow("w", img);
    
    while (1) {
    
        int int_keyInput = waitKey(100);
        if ( int_keyInput == 27 ) break;    /// esc key
    }
    destroyAllWindows();
    
    return 0;
}
