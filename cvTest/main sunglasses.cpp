/// set a sunglasses to face image

#include <iostream>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/objdetect.hpp"
#include <vector>

using namespace std;
using namespace cv;

void detectAndDraw ( Mat& img
                    , CascadeClassifier& cascade
                    , CascadeClassifier& nestedCascade
                    , double scale
                    , bool tryflip
                    , Mat glasses
                    );

void overlayImage ( const Mat& background
                   , const Mat* foreground
                   , Mat& output
                   , Point2i location
                   );

string cascadeName;
string nestedCascadeName;

int main(int argc, const char * argv[]) {
    
    VideoCapture vc;
    Mat frame, image, glasses;
    
    string faceImgPath = "${downloadPath}faces.png";
    string glassesImgPath = "${downloadPath}sunglasses.png";
    bool tryFlip = false;
    CascadeClassifier cascade, nestedCascade;
    double scale = 1;
    
    glasses = imread(glassesImgPath, IMREAD_UNCHANGED);
    if ( glasses.empty() == true ) return -1;
    
    if (!nestedCascade.load(samples::findFileOrKeep("haarcascade_eye_tree_eyeglasses.xml")))
    
    
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



