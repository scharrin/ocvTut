#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>

using namespace std;
using namespace cv;

Mat
mat_img_original_mono
, mat_img_destination
, mat_img_detected_edges;

int
lowThreshold = 50
, highThreshold = 150;

static void CannyThresholdCallback(int, void* )
{
    blur(mat_img_original_mono, mat_img_detected_edges, Size(3,3));
    Canny(mat_img_detected_edges, mat_img_detected_edges, lowThreshold, highThreshold);
    
    imshow("Canny Edge", mat_img_detected_edges);
}

int main(int argc, const char * argv[]) {
    
//    string imgPath = "${path}cvTest/src/sweater.jpg";
//    Mat mat_img_original = imread(imgPath);
    Mat mat_img_original;
    VideoCapture vc(0);
    resizeWindow("Canny Edge", 400, 600);
    if ( vc.isOpened() == false ) return -1;
    vc.set(CAP_PROP_FRAME_WIDTH, 400);
    vc.set(CAP_PROP_FRAME_HEIGHT, 600);
    
    while (1) {
        vc >> mat_img_original;
        
        if ( mat_img_original.empty() == true ) break;
  
//    if ( mat_img_original.empty() == true )
//    {
//        return -1;
//    }
    
    cvtColor(mat_img_original, mat_img_original_mono, COLOR_BGR2GRAY);
    
    namedWindow("Canny Edge", WINDOW_AUTOSIZE);
    createTrackbar("min threshold", "Canny Edge", &lowThreshold, 1000, CannyThresholdCallback);
    createTrackbar("max threshold", "Canny Edge", &highThreshold, 1000, CannyThresholdCallback);
    CannyThresholdCallback(0,0);
//    waitKey(0);
     
        if (waitKey(1000) > 0) {
            break;
        }
    }
    return 0;
}



