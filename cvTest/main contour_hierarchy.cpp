/// contour hierarchy

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
    Mat flower = imread(str_path_download + "flower2.jpg");
    Mat hierTest = imread(str_path_download + "hierachyTest.jpg");
    img = hierTest;
    namedWindow("w");
    createTrackbar("tbr", "w", 0, 255);

    /// contour outlines
    Mat imgGray;
    Mat imgBinary;
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy; /// should be 4 channel
    vector<Vec4i> hierarchy_external; /// should be 4 channel
    vector<Vec4i> hierarchy_ccomp; /// should be 4 channel
    vector<Vec4i> hierarchy_tree; /// should be 4 channel

    cvtColor(img, imgGray, COLOR_BGR2GRAY);
    
    threshold(imgGray, imgBinary, binaryThreshold, maxThreshold, 0);
    findContours(imgBinary, contours, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE);
    findContours(imgBinary, contours, hierarchy_ccomp, RETR_CCOMP, CHAIN_APPROX_SIMPLE);
    findContours(imgBinary, contours, hierarchy_external, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    findContours(imgBinary, contours, hierarchy_tree, RETR_TREE, CHAIN_APPROX_SIMPLE);
    for ( auto i = 0; i < contours.size(); i++ )
    {
        drawContours(img, contours, i, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), 1);
    }
    imshow("w", img);
    cout << "RETR_LIST" << endl;
    for ( auto h : hierarchy )
    {
        cout << h << endl;
    }
    cout << "RETR_CCOMP" << endl;
    for ( auto h : hierarchy_ccomp )
    {
        cout << h << endl;
    }
    cout << "RETR_EXTERNAL" << endl;
    for ( auto h : hierarchy_external )
    {
        cout << h << endl;
    }
    cout << "RETR_TREE" << endl;
    for ( auto h : hierarchy_tree )
    {
        cout << h << endl;
    }
    while (1) {
//
//        thresholdFromTrackbar = getTrackbarPos("tbr", "w");
//        threshold(imgGray, imgBinary, thresholdFromTrackbar, maxThreshold, 0);
//        findContours(imgBinary, contours, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE);
//        for ( auto i = 0; i < contours.size(); i++ )
//        {
//            drawContours(img, contours, i, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), lineWeight);
//        }
//        imshow("w", img);
        
        int int_keyInput = waitKey(1000);
        if ( int_keyInput == 27 ) break;    /// esc key
    }
    destroyAllWindows();
    
    return 0;
}
