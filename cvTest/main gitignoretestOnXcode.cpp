/// draw circles or rect by mouse event (advanced)

/// key input m change mode, c is clear
#include <iostream>
#include "opencv2/opencv.hpp"
#include <vector>

using namespace std;
using namespace cv;

Mat
window(300, 300, CV_8UC3);

bool
isClicked = false
, isRect = true;

Scalar
Sc_inital_CircleColor = Scalar(255, 0, 0)
, Sc_inital_RectColor = Scalar(0, 255 , 0)
, *ptCircleColor = &Sc_inital_CircleColor
, *ptRectColor = &Sc_inital_RectColor
;

int
int_mouse_posX = -1
, int_mouse_posY = -1
, int_circle_radius = 5
;

//Scalar ScrRotateColor ( Scalar& _s )
//{
//
//    if ( _s[0] == 0 ) _s[0] = 255;
//    else _s[0] = --_s[0];
//    if ( _s[1] == 0 ) _s[1] = 255;
//    else _s[1] = --_s[1];
//    if ( _s[2] == 0 ) _s[2] = 255;
//    else _s[2] = --_s[2];
//    &_s = _s;
//    return _s;
//}

int int_getDistance ( Point p1, Point p2 )
{
    return (int)sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

void drawCircle(int ev, int x, int y, int flags, void* param)
{
//    cout << to_string((MouseEventTypes)ev) << endl;
    if ( ev == EVENT_LBUTTONDOWN )  /// clicked
    {
        isClicked = true;
        int_mouse_posX = x;
        int_mouse_posY = y;
    }
    else if ( ev == EVENT_MOUSEMOVE )
    {
        if ( isClicked == true )
        {
            if ( isRect == true )
            {
                rectangle(window, Point(int_mouse_posX, int_mouse_posY), Point(x, y), Sc_inital_RectColor);
            }
            else
            {
                circle(window, Point(x, y), int_getDistance(Point(int_mouse_posX, int_mouse_posY), Point(x, y)), Sc_inital_CircleColor);
            }
        }
    }
    else if ( ev == EVENT_LBUTTONUP )
    {
        isClicked = false;
        if ( isRect == true )
        {
            rectangle(window, Point(int_mouse_posX, int_mouse_posY), Point(x, y), Sc_inital_RectColor);
        }
        else
        {
            circle(window, Point(x, y), int_getDistance(Point(int_mouse_posX, int_mouse_posY), Point(x, y)), Sc_inital_CircleColor);
        }
    }
}

int main(int argc, const char * argv[]) {
    
    namedWindow("w");
//    resizeWindow("w", 300, 300);
    
    window.setTo(255);
    setMouseCallback("w", drawCircle);
    
    int int_keyInput;
    while (1) {
        imshow("w", window);
        int_keyInput = waitKey(1);
        if ( int_keyInput == 27 ) break;    /// esc key
        else if ( int_keyInput == 'm' ) isRect = !isRect;
        else if ( int_keyInput == 'c' ) window.setTo(255);
    }
    destroyAllWindows();
    
    return 0;
}



