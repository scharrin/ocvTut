/// image gradients

///
#include <iostream>
#include "opencv2/opencv.hpp"
#include "dd.h"

using namespace std;
using namespace cv;

int main(int argc, const char * argv[]) {
    
    Mat img = imread(str_path_download + "faces.png");
    namedWindow("w");
    
    Mat imgGaus;
    Mat resultCanny;
    Mat resultCannyGaus;
    Mat resultLaplacian;
    Mat resultSobelX;
    Mat resultSobelY;
    
    GaussianBlur(img, imgGaus, Size(5,5), 0);
    Canny(imgGaus, resultCannyGaus, 30, 70);
    Canny(img, resultCanny, 30, 70);
    Laplacian(img, resultLaplacian, img.depth());
    Sobel(img, resultSobelX, img.depth(), 1, 0);
    Sobel(img, resultSobelY, img.depth(), 0, 1);
    
    imshow("resultCanny", resultCanny);
    imshow("resultCannyGaus", resultCannyGaus);
    imshow("resultLaplacian", resultLaplacian);
    imshow("resultSobelX", resultSobelX);
    imshow("resultSobelY", resultSobelY);
    
    while (1) {
    
        int int_keyInput = waitKey(100);
        if ( int_keyInput == 27 ) break;    /// esc key
    }
    destroyAllWindows();
    
    return 0;
}
