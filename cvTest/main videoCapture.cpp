//
//  main.cpp
//  cvTest
//
//  Created by macproo on 25/10/2019.
//  Copyright © 2019 macproo. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace std;
using namespace cv;

void saveSnap(Mat _matImgToSave, string _strSaveImgPath, string _strFileName, string _strFileExt)
{
    imwrite(_strSaveImgPath + _strFileName + _strFileExt, _matImgToSave);
}

int main(int argc, const char * argv[]) {
    
//    const string imgPath = "${path}cvTest/src/jacket.jpg";
    const string strSaveImgPath = "${path}cvTest/src/";
//    const string strVideoPath = "${downloadPath}2019_earthquaketraining.mp4";
    const string strVideoPath = "${downloadPath}20190709002018_uxmbkwky.mp4";
    const string strSaveVideoFileName = "savedVideo";
    const string strSaveVideoFileExt = ".avi";
    const int intVideoWriterAPIprefer = 1;  /// display codex selection dialog (-1) or not (1)
    const int intVideoWriterIsColor = 1;  /// out as color (1: true, default) or mono (0 : false)
    const int BUFFERING_TIME_IN_MS = 5;
        
    unsigned char b, g, r;
    char cInputKey;
    Mat imgMat;
    VideoWriter vw;
//    vector<Mat> vecMat(3);
    
    namedWindow("imgMat");

    VideoCapture vc = VideoCapture(0);

    if (vc.isOpened() == false) return -1;
     
    vc >> imgMat;
    
//    VideoCapture vc = VideoCapture(strVideoPath);
    
//    Size S = Size(vc.get(CAP_PROP_FRAME_WIDTH), vc.get(CAP_PROP_FRAME_HEIGHT));
    
    int fourcc = vw.fourcc('M', 'J', 'P', 'G');
    
    vw.open(
            strSaveImgPath + strSaveVideoFileName + strSaveVideoFileExt
            , fourcc
            , vc.get(CAP_PROP_FPS)
//            , 25.0
            , imgMat.size()
            , (imgMat.type() == CV_8UC3)
            );
        
    
    while(1)
    {
//        vc.read(imgMat);
        vc >> imgMat;
        
        if (imgMat.empty()) break;

//        vw << imgMat;
        vw.write(imgMat);
        imshow("imgMat", imgMat);
        
        cInputKey = waitKey(BUFFERING_TIME_IN_MS);

        if(cInputKey >= 'c') break; /// exit
        
        else if (cInputKey == 'a')  /// take a snap and exit
        {
            saveSnap(imgMat, strSaveImgPath, "capture1", ".jpg" );
            break;
        }
//
//        else if (cInputKey == 'b')  /// take a snap and split it by channel and save each
//        {
//            split(imgMat, vecMat);
//            /// major color is brighter then other color
//            /// ig) splited red file shows more close white if the color is more adjacent to red.
//            saveSnap(vecMat[0], strSaveImgPath, "capture1Splitb", ".jpg" );
//            saveSnap(vecMat[1], strSaveImgPath, "capture1Splitg", ".jpg" );
//            break;
//        }
    }
    
    vw.release();
    destroyAllWindows();
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}
