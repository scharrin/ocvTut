/// image transformation

///
#include <iostream>
#include "opencv2/opencv.hpp"
#include "dd.h"

using namespace std;
using namespace cv;

Point2f pPerspective1[4];
Point2f pPerspective2[4];

struct MouseParam {
    int* count;
    Point2f* ppnts;
    Mat* mat_pntLayer;
    Mat* mat_pntLayerResult;
    int* pCircleRadius;
    int* pCircleLineWeight;
};

void musCallback( int ev, int x, int y, int flag, void* param )
{
    if ( ev == EVENT_LBUTTONDOWN )
    {
        MouseParam* mp = (MouseParam*)param;
        int index = *(mp->count);
        if ( index <= 3 )
        {
            mp->ppnts[index] = Point2f(x, y);
            circle(*(mp->mat_pntLayer), Point(x, y), *(mp->pCircleRadius), Scalar(255, 0, 0), *(mp->pCircleLineWeight));
            if ( index == 3 )
            {
                float x = (float)mp->mat_pntLayerResult->rows;
                float y = (float)mp->mat_pntLayerResult->cols;
                Point2f point_result_vertex[4]={{0, 0}, {x, 0}, {0, y}, {x, y}};
                Mat matPerspective = getPerspectiveTransform(mp->ppnts, point_result_vertex);
                warpPerspective(*(mp->mat_pntLayerResult), *(mp->mat_pntLayerResult), matPerspective, Size(mp->mat_pntLayerResult->rows, mp->mat_pntLayerResult->cols));
            }
            ++*(mp->count);
        }
        else    /// when the index over 4
        {
            mp->mat_pntLayer->setTo(0);
            mp->count = 0;
        }
    }
}

int main(int argc, const char * argv[]) {
    
    Mat
    mat_result
    , mat_img_logo
    , mat_img_flower
    , mat_img_perspective
    , mat_img_perspective_merged
    , mat_img_perspective_result
    , mat_img_perspective_points
    , mat_img_shrunk_logo
    , mat_img_zoomed_logo
    , mat_warpAffine
    , mat_warpAffineRotation
    , mat_warpAffineTransformation
    , mat_img_result_warpAffineTransformation
    ;
    
    string
    str_filename_logo = "logo_2.png"
    , str_filename_flower = "flower1.jpg"
    ;
    
    int
    int_width_img
    , int_height_img
    ;
    
    double
    dbl_magnitudeX
    , dbl_magnitudeY
    ;
    
    namedWindow("w");
    
    /// resize
    /// resize
    mat_img_logo = imread(str_path_download + str_filename_logo);
    mat_img_flower = imread(str_path_download + str_filename_flower);
    int_width_img = mat_img_logo.cols;
    int_height_img = mat_img_logo.rows;
    dbl_magnitudeX = 0.5;
    dbl_magnitudeY = 0.5;
    resize(mat_img_logo, mat_img_shrunk_logo, Size(int_width_img * dbl_magnitudeX, int_height_img * dbl_magnitudeY), 0, 0, INTER_AREA);
    resize(mat_img_logo, mat_img_zoomed_logo, Size(), 2, 2, INTER_CUBIC);
//    imshow("result", mat_img_logo);
//    imshow("mat_img_shrunk_logo", mat_img_shrunk_logo);
//    imshow("mat_img_zoomed_logo", mat_img_zoomed_logo);
    
    
    /// warpAffine
    /// warpAffine
    float ary_int_warpAffine[2][3] = {{1, 0 , 10}, {0, 1, 20}}; /// this type should be float never int!!!
    mat_warpAffine = Mat(2, 3, CV_32F, ary_int_warpAffine);
    warpAffine(mat_img_logo, mat_result, mat_warpAffine, Size(int_width_img, int_height_img));
//    imshow("result", mat_img_logo);
//    imshow("result2", mat_result);

    
    /// image rotation with warpAffine
    /// image rotation with warpAffine
    mat_warpAffineRotation = getRotationMatrix2D(Point2f(int_height_img / 2, int_width_img / 2 ), 90, 0.5);
//    cout << mat_warpAffineRotation << endl;
    warpAffine(mat_img_logo, mat_result, mat_warpAffineRotation, Size(int_width_img, int_height_img));
//    imshow("result", mat_img_logo);
//    imshow("result2", mat_result);
    
    
    /// warpAffine transformation from 3 points
    /// warpAffine transformation from 3 points
    Point2f p1[3] = {{200, 100},{400, 100},{200, 200}};
    Point2f p2[3] = {{200, 300},{400, 200},{200, 400}};
    
    circle(mat_img_flower, p1[0], 10, Scalar(255, 0, 0), -1);
    circle(mat_img_flower, p1[1], 10, Scalar(0, 255, 0), -1);
    circle(mat_img_flower, p1[2], 10, Scalar(0, 0, 255), -1);
    
    mat_warpAffineTransformation = getAffineTransform(p1, p2);
//    cout << mat_warpAffineTransformation << endl;
    warpAffine(mat_img_flower, mat_img_result_warpAffineTransformation, mat_warpAffineTransformation, Size(mat_img_flower.cols, mat_img_flower.rows));
//    imshow("result", mat_img_flower);
//    imshow("result2", mat_img_result_warpAffineTransformation);
    
    
    /// perspective transformation
    /// perspective transformation
    /// layer merging is not work
    int
    cnt = 0
    , circleRadius = 5
    , circleLineWeight = -1
    ;
    Point2f pts[4];
    MouseParam mp;
    namedWindow("perspective");
    mat_img_perspective = imread(str_path_download + "file_example_PNG_500kB.png");
    mp.count = &cnt;
    mp.pCircleRadius = &circleRadius;
    mp.pCircleLineWeight = &circleLineWeight;
    mp.ppnts = pts;
    mp.mat_pntLayer = &mat_img_perspective_points;
    mp.mat_pntLayerResult = &mat_img_perspective_result;
    
    setMouseCallback("perspective", musCallback, (void*)&mp);
    
    imshow("perspective", mat_img_perspective);
    while (1) {
        
//        add(mat_img_perspective, mat_img_perspective_points, mat_img_perspective_merged);
//        imshow("perspective", mat_img_perspective_merged);
//        imshow("perspectiveResult", mat_img_perspective_result);

        int int_keyInput = waitKey(100);
        if ( int_keyInput == 27 ) break;    /// esc key
    }
    destroyAllWindows();
    
    return 0;
}
