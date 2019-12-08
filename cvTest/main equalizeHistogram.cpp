/// equalize histogram

///
#include <iostream>
#include "opencv2/opencv.hpp"
#include "dd.h"

using namespace std;
using namespace cv;
RNG rng;

int main(int argc, const char * argv[]) {
  
    namedWindow("w");
    Mat img = imread(str_path_download + "adjHistorgramTest.jpg", 0);
    //    Mat img = imread(str_path_download + "");
    
    ///  make histogram
    const int int8bitMax = 256;
    const int result_w = 500;
    const int result_h = 300;
    int hist[int8bitMax] = {0, };
    int atVal;
    for ( int i = 0; i < img.rows; i++ )
    {
        for ( int j = 0; j < img.cols; j++ )
        {
            atVal = img.at<uchar>(i, j);
            hist[atVal] += 1;
        }
    }
    
    /// accumulated histogram also
    int cumulateHist[int8bitMax] = {0, };
    int sum = 0;
    
    for ( int i = 1; i < int8bitMax; i++ )
    {
//        sum += hist.at<uchar>(i);
        sum += hist[i];
        cumulateHist[i] = sum;
    }

    ///     normalize
    float normalizedHist[int8bitMax] = {0, };
    float imgSz = (float)(img.rows * img.cols);

    for ( int i = 0; i < int8bitMax; i++ )
    {
        normalizedHist[i] = cumulateHist[i] / imgSz;
    }
    ///     recalculate image matrix from normalized histogram
    int histResult[int8bitMax] = {0, };
    Mat result(img.rows, img.cols, CV_8UC1);
    for ( int i = 0; i < img.rows; i++ )
    {
        for ( int j = 0; j < img.cols; j++ )
        {
            result.at<uchar>(i, j) = normalizedHist[img.at<uchar>(i, j)] * 255; /// set pixcel
            histResult[result.at<uchar>(i, j)] += 1;    /// to new histogram
        }
    }
    ///     cumulate normalized
    int hist_cumulative_result[int8bitMax] = {0, };
    int hist_cumulated_result_sum = 0;

    for ( int i = 1; i < int8bitMax; i++ )
    {
        hist_cumulated_result_sum += histResult[i];
        hist_cumulative_result[i] = hist_cumulated_result_sum;
    }

    Mat histImg(result_h, result_w , CV_8UC1, Scalar(0, 0, 0));
    Mat histResultImg(result_h, result_w , CV_8UC1, Scalar(0, 0, 0));

    ///     get max for graph size
    int max = 0;
    int max2 = 0;
    for ( int i = 0; i < int8bitMax; i++ )
    {
        if ( max < hist[i] ) max = hist[i];
    }

    for ( int i = 0; i < int8bitMax; i++ )
    {
        if ( max2 < histResult[i] ) max2 = histResult[i];
    }

    ///     draw graphs
    int histoPointY;
    int histoResultPointY;
    int histoCumulativePointY;
    int histoResultCumulativePointY;
    Scalar lineColor(255, 255, 255);
    for ( int i = 0; i < int8bitMax; i++ )
    {
        histoPointY = result_h * hist[i] / (float)max;
        histoCumulativePointY = result_h * cumulateHist[i] / (float)cumulateHist[int8bitMax-1];
        line(histImg, Point(i, result_h), Point(i, result_h-histoPointY), lineColor);
        line(histImg, Point(i+result_h, result_h), Point(i+result_h, result_h-histoCumulativePointY), lineColor);

        histoResultPointY = result_h * histResult[i] / (float)max2;
        histoResultCumulativePointY = result_h * hist_cumulative_result[i] / (float)hist_cumulative_result[int8bitMax-1];
        line(histResultImg, Point(i, result_h), Point(i, result_h-histoResultPointY), lineColor);
        line(histResultImg, Point(i+result_h, result_h), Point(i+result_h, result_h-histoResultCumulativePointY), lineColor);
    }
    
    imshow("img", img);
    imshow("histImg", histImg);
    imshow("histResultImg", histResultImg);
    imshow("result", result);

    while (1) {
        
        int int_keyInput = waitKey(1000);
        if ( int_keyInput == 27 ) break;    /// esc key
    }
    destroyAllWindows();
    
    return 0;
}
