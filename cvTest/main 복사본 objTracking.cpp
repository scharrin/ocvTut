#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace std;
using namespace cv;

Vec3b
vec3b_lower_blue1
, vec3b_upper_blue1
, vec3b_lower_blue2
, vec3b_upper_blue2
, vec3b_lower_blue3
, vec3b_upper_blue3
, vec3b_pixColor
;

Mat
mat_img
, mat_img_hsv
, mat_img_mask
, mat_img_mask1
, mat_img_mask2
, mat_img_mask3
, mat_img_toDisplay
, mat_rgb_pixColor
, mat_hsv_pixColor
, mat_elem
, mat_img_labels
, mat_stats
, mat_centeroids
;

int
int_window_width = 640
, int_window_heigh = 480
, int_threshold = 30                      /// minimum hsv value
, int_degree_rng_detection = 10
, int_max_hue = 180
, int_max_sat = 255
, int_max_value = 255
, int_trackbar_initial_hue = 30
, int_last_mouse_x
, int_last_mouse_y
, int_morph_size = 2
, int_labels_count
, int_minimal_area_squring = 100
, int_detected_circle_radius = 5
;

Size
size_window = Size(int_window_heigh, int_window_width);

//void dummy(int, void*);



void mouseCallback( int event, int x, int y, int flags, void* param )
{
    if ( event == EVENT_LBUTTONDOWN )
    {
        /// escape
        if ( x >= int_window_heigh || y >= int_window_width ) return;
        else
        {
            int_last_mouse_x = x;
            int_last_mouse_y = y;
        }
            
        int
        int_selected_hue
        , int_selected_saturation
        , int_selected_value
        ;
        
        int_threshold = getTrackbarPos("Thrshld", "before");
        
        vec3b_pixColor = mat_img.at<Vec3b>(x, y);
        mat_rgb_pixColor = Mat(1, 1, CV_8UC3, vec3b_pixColor); /// rows, cols, type, color (size 1x1 pixcel)
        cvtColor(mat_rgb_pixColor, mat_hsv_pixColor, COLOR_RGB2HSV);
        
        int_selected_hue         = mat_hsv_pixColor.at<Vec3b>(0, 0)[0];
        int_selected_saturation  = mat_hsv_pixColor.at<Vec3b>(0, 0)[1];
        int_selected_value       = mat_hsv_pixColor.at<Vec3b>(0, 0)[2];
        
        cout << endl;
        cout << "selected hsv : " << int_selected_hue << " " << int_selected_saturation << " " << int_selected_value << endl;
        
        /// set three vectors near the detect degree range ( to prevent over hue value )
        /// +, - int_degree_rng_detection in this code, 10
        
        /// 3 vectors needed cause opencv hsv is maximun 180 degrees so next will compose a + - clearence hue range
        if ( int_selected_hue < int_degree_rng_detection )  /// ig) if the detection rng = 10 degrees and selected hue is less then
        {
            cout << "case 1 : selected lower than threshold" << endl;
            vec3b_lower_blue1 = Vec3b(int_selected_hue - int_degree_rng_detection + int_max_hue, int_threshold, int_threshold);
            vec3b_upper_blue1 = Vec3b(int_max_hue, int_max_sat, int_max_value); /// dunno why...
            vec3b_lower_blue2 = Vec3b(0, int_threshold, int_threshold);
            vec3b_upper_blue2 = Vec3b(int_selected_hue, int_max_sat, int_max_value);
            vec3b_lower_blue3 = Vec3b(int_selected_hue, int_threshold, int_threshold);
            vec3b_upper_blue3 = Vec3b(int_selected_hue + int_degree_rng_detection, int_max_sat, int_max_value);
        }
        else if ( int_selected_hue > int_max_hue - int_degree_rng_detection )   /// when the selection over the hue range
        {
            cout << "case 2 : selected over hue maximum value ( selected + threshold > maximum hue )" << endl;
            vec3b_lower_blue1 = Vec3b(int_selected_hue, int_threshold, int_threshold);
            vec3b_upper_blue1 = Vec3b(int_max_hue, int_max_sat, int_max_value);
            vec3b_lower_blue2 = Vec3b(0, int_threshold, int_threshold);
            vec3b_upper_blue2 = Vec3b(int_selected_hue + int_degree_rng_detection - int_max_hue, int_max_sat, int_max_value);
            vec3b_lower_blue3 = Vec3b(int_selected_hue - int_degree_rng_detection, int_threshold, int_threshold);
            vec3b_upper_blue3 = Vec3b(int_selected_hue , int_max_sat, int_max_value);
        }
        else    /// when selected hue degree is within the range
        {
            cout << "case 3 : selected hue within the threshold range" << endl;
            vec3b_lower_blue1 = Vec3b(int_selected_hue, int_threshold, int_threshold);
            vec3b_upper_blue1 = Vec3b(int_selected_hue + int_degree_rng_detection, int_max_sat, int_max_value);
            vec3b_lower_blue2 = Vec3b(int_selected_hue - int_degree_rng_detection, int_threshold, int_threshold);
            vec3b_upper_blue2 = Vec3b(int_selected_hue, int_max_sat, int_max_value);
            vec3b_lower_blue3 = vec3b_lower_blue2;
            vec3b_upper_blue3 = vec3b_upper_blue2;
//            vec3b_lower_blue3 = Vec3b(int_selected_hue - int_degree_rng_detection, int_threshold, int_threshold);
//            vec3b_upper_blue3 = Vec3b(int_selected_hue, int_max_sat, int_max_value);
        }
        
        cout << "selected hue was "     << int_selected_hue     << endl;
        cout << "#1 sample range = "    << vec3b_lower_blue1    << " ~ " << vec3b_upper_blue1 << endl;
        cout << "#2 sample range = "    << vec3b_lower_blue2    << " ~ " << vec3b_upper_blue2 << endl;
        cout << "#3 sample range = "    << vec3b_lower_blue3    << " ~ " << vec3b_upper_blue3 << endl;
        
        mat_img_toDisplay.setTo(0);
    }
}

int main(int argc, const char * argv[]) {
    
    namedWindow("before");
    setMouseCallback("before", mouseCallback);
    
    /// set trackbar
    createTrackbar("Thrshld"
                   , "before"
                   , &int_threshold
                   , int_max_sat
                   , [](int, void*)
    {
        mouseCallback(EVENT_LBUTTONDOWN, int_last_mouse_x, int_last_mouse_y, NULL, nullptr);
    }
                   );
    setTrackbarPos("Thrshld", "before", int_trackbar_initial_hue);
    
    /// open cam and resize capture
    VideoCapture vc(0);
    vc.set(CAP_PROP_FRAME_WIDTH, int_window_width);
    vc.set(CAP_PROP_FRAME_HEIGHT, int_window_heigh);
    
    if ( vc.isOpened() == false ) return -1;
    
    while (1) {
        
        vc.read(mat_img);
        cvtColor(mat_img, mat_img_hsv, COLOR_RGB2HSV);
        inRange(mat_img_hsv, vec3b_lower_blue1, vec3b_upper_blue1, mat_img_mask1);
        inRange(mat_img_hsv, vec3b_lower_blue2, vec3b_upper_blue2, mat_img_mask2);
        inRange(mat_img_hsv, vec3b_lower_blue3, vec3b_upper_blue3, mat_img_mask3);
        mat_img_mask = mat_img_mask1 | mat_img_mask2 | mat_img_mask3;
        
        /// morphology fill hole in mask
        mat_elem = getStructuringElement(MORPH_RECT, Size(2 * int_morph_size + 1, 2 * int_morph_size + 1 ), Point(int_morph_size, int_morph_size));
        morphologyEx(mat_img_mask, mat_img_mask, MORPH_OPEN, mat_elem);
        morphologyEx(mat_img_mask, mat_img_mask, MORPH_CLOSE, mat_elem);
        
        /// masking and show
        bitwise_and(mat_img, mat_img, mat_img_toDisplay, mat_img_mask);
        
        /// labeling : get properties from statistic
        int_labels_count = connectedComponentsWithStats(mat_img_mask, mat_img_labels, mat_stats, mat_centeroids);
        for ( int i = 1; i < int_labels_count; ++i )
        {
            int area = mat_stats.at<int>(i, CC_STAT_AREA);
            int left = mat_stats.at<int>(i, CC_STAT_LEFT);
            int top = mat_stats.at<int>(i, CC_STAT_TOP);
            int width = mat_stats.at<int>(i, CC_STAT_WIDTH);
            int height = mat_stats.at<int>(i, CC_STAT_HEIGHT);
            int centerX = mat_centeroids.at<double>(i, 0);
            int centerY = mat_centeroids.at<double>(i, 1);

            /// draw only area over the minium
            if ( area > int_minimal_area_squring )
            {
                circle(mat_img, Point(centerX, centerY), int_detected_circle_radius, Scalar(255, 255, 0), 1);
                rectangle(mat_img, Point(left, top), Point(left + width, top + height), Scalar(0, 0, 255), 1);
            }
        }
        
        imshow("mask",      mat_img_mask);
        imshow("after",     mat_img_toDisplay);
        imshow("before",    mat_img);
        
        if ( waitKey(1) > 0 ) break;
    }
    
    destroyAllWindows();
    return 0;
}



