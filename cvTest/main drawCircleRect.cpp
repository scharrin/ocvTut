#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace std;
using namespace cv;

int main(int argc, const char * argv[]) {
    
    namedWindow("w");
    Mat m(500, 500, CV_8UC3);
    m.setTo(255);
    
    Point pt(300, 300);
    line(m, Point(10, 10), pt, CV_RGB(255, 0, 0), 2);
    line(m, Point(300, 10), Point(10, 300), CV_RGB(0, 255, 0), 1);
    circle(m, Point(450, 150), 20, Scalar(255, 255, 0), 4);
    circle(m, Point(236, 124), 40, Scalar(0, 255, 255), -2);    /// fill color inside from -1
    rectangle(m, Point(23,56), Point(42, -12), Scalar(0, 0, 255), 1);
    ellipse(m, Point(256, 335), Size(19, 144), -30, 0, 260, Scalar(255, 0, 0));
    
    RotatedRect rRect = RotatedRect(Point2f(300, 300), Size2f(300, 100), 30);
    ellipse(m, rRect, CV_RGB(20, 43, 125));
    Point2f vertices[4];
    rRect.points(vertices);
    cout << vertices << endl;
    for ( int i = 0; i < 4; i++ )
    {
        line(m, vertices[i], vertices[(i + 1) % 4], Scalar(0, 255, 0));
    }
    Rect boundingRect = rRect.boundingRect();
    rectangle(m, boundingRect, Scalar(255, 0 , 0), 2);
    
    imshow("w", m);
    waitKey();
    
    return 0;
}
