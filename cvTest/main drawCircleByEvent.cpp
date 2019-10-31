/// to draw circles from mouse event

/// right draw, left white all
#include <iostream>
#include "opencv2/opencv.hpp"
#include <vector>

using namespace std;
using namespace cv;

const int intCircleRadius = 50;
const Scalar ScCircleColor = Scalar(255, 0 , 0);

Mat
window(300, 300, CV_8UC3);

void drawCircle(int ev, int x, int y, int flags, void* param)
{
//    cout << to_string((MouseEventTypes)ev) << endl;
    if ( ev == EVENT_RBUTTONDOWN )
    {
        circle(window, Point(x, y), intCircleRadius, ScCircleColor, -1);
    }
    else if ( ev == EVENT_LBUTTONDOWN )
    {
        window.setTo(255);
    }
}

int main(int argc, const char * argv[]) {
    
    namedWindow("w");
//    resizeWindow("w", 300, 300);
    
    window.setTo(255);
    setMouseCallback("w", drawCircle);
    
    while (1) {
        imshow("w", window);
        if ( waitKey(1) > 0 ) break;
    }
    destroyAllWindows();
    
    return 0;
}



