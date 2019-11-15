/// pyramids

///
#include <iostream>
#include "opencv2/opencv.hpp"
#include "dd.h"

using namespace std;
using namespace cv;

int main(int argc, const char * argv[]) {
    
    int pyr_magnitude = 5;
    Mat img = imread(str_path_download + "faces.png");
    Mat img2 = imread(str_path_download + "kaki pants.jpg");
    Mat img3 = imread(str_path_download + "gray pants.jpg");
    namedWindow("w");
    
    Mat imgGaus;
    Mat resultPyup;
    Mat resultPydown;
    Mat resultPyupdownEdge;
    Mat resultPyupdownEdge2;
    Mat resultPyupdownEdge3;
    Mat resultPyupdownEdge4;
    Mat GaussianPyramidsA[pyr_magnitude];
    Mat GaussianPyramidsB[pyr_magnitude];
    Mat lpA[pyr_magnitude];
    Mat lpB[pyr_magnitude];
    Mat lAccumuatedSum[pyr_magnitude];
//    Mat lAccumuatedSum2[pyr_magnitude];
    Mat lAccumuatedSum2;
    
    ///    concatenate images
    ///    concatenate images
    /// collect downs
    pyrDown(img2, GaussianPyramidsA[0]);
    pyrDown(img3, GaussianPyramidsB[0]);
    
    for ( auto i = 1; i < pyr_magnitude; i++ )
    {
        pyrDown(GaussianPyramidsB[i - 1], GaussianPyramidsB[i]);
        pyrDown(GaussianPyramidsA[i - 1], GaussianPyramidsA[i]);
    }

    /// make Laplacian Pyramid
    Mat tmp, tmp2;
    for ( auto i = pyr_magnitude - 1; i > -1; i-- )
    {
        pyrUp(GaussianPyramidsA[i], tmp);
        if ( i == 0 )
        {
            resize(GaussianPyramidsA[i], tmp2, Size(tmp.cols, tmp.rows));
        }
        else
        {
            resize(GaussianPyramidsA[i-1], tmp2, Size(tmp.cols, tmp.rows));
        }
        subtract(tmp2, tmp, lpA[i]);

        pyrUp(GaussianPyramidsB[i], tmp);
        if ( i == 0 )
        {
            resize(GaussianPyramidsB[i], tmp2, Size(tmp.cols, tmp.rows));
        }
        else
        {
            resize(GaussianPyramidsB[i-1], tmp2, Size(tmp.cols, tmp.rows));
        }
        subtract(tmp2, tmp, lpB[i]);
    }

    for ( auto i = 0; i < pyr_magnitude; i++ )
    {
        hconcat(
        lpA[i](Range::all(), Range(0, lpA[i].cols / 2))
        , lpB[i](Range::all(), Range(lpB[i].cols / 2, lpB[i].cols))
        , lAccumuatedSum[i]
        );
        //// not showing background just outlines
        imshow("lAccumuatedSum"+to_string(i), lAccumuatedSum[i]);
    }

    lAccumuatedSum2 = lAccumuatedSum[0];
    for ( auto i = 1; i < pyr_magnitude; i++ )
    {
        pyrUp(lAccumuatedSum2, tmp);
        resize(lAccumuatedSum[i], tmp2, Size(tmp.cols, tmp.rows));
        add(tmp, tmp2, lAccumuatedSum2);
    }

    imshow("w", lAccumuatedSum2);
    
    while (1) {
    
        int int_keyInput = waitKey(100);
        if ( int_keyInput == 27 ) break;    /// esc key
    }
    destroyAllWindows();
    
    return 0;
}
