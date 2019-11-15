/// contents
////// contours
////// circle to center of mess
////// rectangle surrounded
////// draw minimum surrounding area rectangle,         /// ellipses
////// approximit contour
////// convex hull
////// convexity defects

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
    const float float_convtexity_defects_depth_threshold = 10;
    Mat img = imread(str_path_download + "test.jpg");
    Mat img2 = imread(str_path_download + "test2.jpg");
    Mat img3 = imread(str_path_download + "hand.jpg");
    Mat img4 = imread(str_path_download + "test4.png");
    img = img4;
    namedWindow("w");
    
    /// contour outlines
    Mat imgGray;
    Mat imgBinary;
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy; /// should be 4 channel
    
    cvtColor(img, imgGray, COLOR_BGR2GRAY);
    threshold(imgGray, imgBinary, binaryThreshold, maxThreshold, 0);
    findContours(imgBinary, contours, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE);
    
    for( auto i = 0; i < contours.size(); i++ )
    {
        drawContours(img, contours, i, Scalar(255, 0, 0), lineWeight);
    }
//    imshow("w", img);
    
    /// circle to center of mess
    Moments m;
    int
    centerX
    , centerY
    ;
    for ( auto c : contours )
    {
        m = moments(c);
        centerX = (int) (m.m10 / m.m00);
        centerY = (int) (m.m01 / m.m00);
        
        circle(img, Point(centerX, centerY), circleRadius, Scalar(255, 0, 255));
    }
    
//    imshow("w", img);
    
    /// rectangle surrounded
    Rect rect_tmp;
    for ( auto cc : contours )
    {
        rect_tmp = boundingRect(cc);
        rectangle(img, rect_tmp, Scalar(255, 0, 125));
    }
//    imshow("w", img);
    
    /// draw minimum surrounding area rectangle
    RotatedRect rect_minAreaSurrounding[contours.size()];
    RotatedRect rect_minSurroundingElipse[contours.size()];
    Point2f point_rect[4];
    for ( int i = 0; i < contours.size(); i++ )
    {
        /// fitted rectangle
        minAreaRect(contours[i]).points(point_rect);
        for ( auto j = 0; j < sizeof(point_rect)/sizeof(point_rect[0]); j++ )
        {
            line(img, point_rect[j], point_rect[(j+1)%4], Scalar(255, 255, 125));
        }
        /// ellipses
        if ( contours[i].size() > 5 )
        {
            rect_minSurroundingElipse[i] = fitEllipse(contours[i]);
            ellipse(img, fitEllipse(contours[i]), Scalar(125, 222, 124));
        }
    }
    /// https://docs.opencv.org/2.4/doc/tutorials/imgproc/shapedescriptors/bounding_rotated_ellipses/bounding_rotated_ellipses.html?highlight=minarearect
//    imshow("w", img);
    
    
    /// approximit contour
    cvtColor(img2, imgGray, COLOR_BGR2GRAY);
    threshold(imgGray, imgBinary, binaryThreshold, maxThreshold, 0);
    findContours(imgBinary, contours, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE);

    double epsilon;
    vector<vector<Point>> curves(contours.size());
    for ( int i = 0; i < contours.size(); i++ )
    {
        epsilon = 0.02*arcLength(contours[i], true);
        approxPolyDP(Mat(contours[i]), curves[i], epsilon, true);
        drawContours(img2, curves, i, Scalar(255, 255, 0), lineWeight);
    }
//    imshow("w", img2);
    
    
    /// convex hull
    cvtColor(img3, imgGray, COLOR_BGR2GRAY);
    threshold(imgGray, imgBinary, binaryThreshold, maxThreshold, 0);
    findContours(imgBinary, contours, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE);

    vector<vector<Point>> hull(contours.size());
    /// https://docs.opencv.org/2.4/doc/tutorials/imgproc/shapedescriptors/hull/hull.html?highlight=convexhull
    vector<vector<int>> hull_indies(contours.size());    ///  indices (type should be int from documentation)
    /// https://stackoverflow.com/questions/31354150/opencv-convexity-defects-drawing
    vector<vector<Vec4i>> defects(contours.size());
    /// https://stackoverflow.com/questions/10620981/calculating-convexitydefects-using-opencv-2-4-in-c
    
    for ( int i = 0; i < contours.size(); i++ )
    {
        /// contour
        drawContours(img3, contours, i, Scalar(255, 121, 55), lineWeight);
        
        /// convex hull
        convexHull(contours[i], hull[i]);
        drawContours(img3, hull, i, Scalar(12, 52, 235), lineWeight);
        
        /// convexity defects
        convexHull(contours[i], hull_indies[i]);
        if ( hull_indies[i].size() > 3 )    ///  needa more 3 indices
        {
            convexityDefects(contours[i], hull_indies[i], defects[i]);
            
            /// draw convexity defects
            for ( int j = 0; j < defects[i].size(); j++ )
            {
//                float depth = defects[i][j][3] / 256;
                /// 256 from or defect depth of convexityDefects doc https://docs.opencv.org/2.4/modules/imgproc/doc/structural_analysis_and_shape_descriptors.html?highlight=convexitydefects#CvSeq*%20cvConvexityDefects(const%20CvArr*%20contour,%20const%20CvArr*%20convexhull,%20CvMemStorage*%20storage)
                if ( defects[i][j][3] / 256 > float_convtexity_defects_depth_threshold ) /// depth of defects vector > threshold
                {
                    /// defect
                    /// 0 : start
                    /// , 1: end
                    /// , 2: far
                    /// , 3: depth (8fractional bits -> float by / 256)
//                    int startIdx = defects[i][j][0];
//                    int endIdx = defects[i][j][1];
//                    int farIdx = defects[i][j][2];
//                    Point start(contours[i][startIdx]);
//                    Point end(contours[i][endIdx]);
//                    Point far(contours[i][farIdx]);
//                    or

                    line(img3, Point(contours[i][defects[i][j][0]]), Point(contours[i][defects[i][j][1]]), Scalar(255, 215, 9), 2);   /// start to end
                    line(img3, Point(contours[i][defects[i][j][0]]), Point(contours[i][defects[i][j][2]]), Scalar(255, 215, 9), 2);   /// start to far
                    line(img3, Point(contours[i][defects[i][j][1]]), Point(contours[i][defects[i][j][2]]), Scalar(255, 215, 9), 2);   /// end to far
                    circle(img3, Point(contours[i][defects[i][j][0]]), circleRadius, Scalar(21,52,66), 4);
                }
            }
        }
    }
    imshow("w", img3);
    
    while (1) {
    
        int int_keyInput = waitKey(100);
        if ( int_keyInput == 27 ) break;    /// esc key
    }
    destroyAllWindows();
    
    return 0;
}
