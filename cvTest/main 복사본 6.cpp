//
//  main.cpp
//  cvTest
//
//  Created by macproo on 25/10/2019.
//  Copyright © 2019 macproo. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, const char * argv[]) {
    
    const string imgPath = "${path}cvTest/src/jacket.jpg";
    Mat imgMat = imread(imgPath);
    
    ////// copy matrix
    ///    Mat imgCopy = imgMat;  /// byref (connected to original mat)
    Mat imgCopy = imgMat.clone(); /// by value
    //////
    
    ////// make rectangle object
    Rect r = Rect_<int>(imgCopy.cols / 4, imgCopy.rows / 4, imgCopy.cols / 4 * 2, imgCopy.rows / 4 * 2);
    /// or Rect r(img2.cols / 4, img2.rows / 4, img2.cols / 4 * 2, img2.rows / 4 * 2);
    cout << r << endl; /// shows log the size of rectangle x, y, width, height [260 x 346 from (130, 173)]
    //////
    
    ////// size widnow to rectangle ( by value )
    Mat imgSizeRect = imgMat(r).clone();
    //////
    
    ////// copyTo method ( by value )
    Mat imgCopyTo;
    imgMat.copyTo(imgCopyTo);
    //////

    ////// copyTo method of original ( by value, same as above )
    Mat imgRectedCopyTo;
    imgMat(r).copyTo(imgRectedCopyTo);
    //////
    
    ////// copyTo next ( by value )
    Mat imgCopyToNext(Size(imgMat.cols * 2, imgMat.rows), imgMat.type());
//    imgCopyToNext.setTo(255);   ///white
    imgMat.copyTo(imgCopyToNext(Range::all(), Range(0, imgMat.cols)));  /// rows, cols (height, width) of target matrix start from 0, 0
    bitwise_not(imgCopy, imgCopyToNext(Range::all(), Range(imgCopy.cols, imgCopy.cols * 2)));
    /// rows, cols (height, width) of target matrix.
    /// the cols start from imgMat's col number and end at double of that
    /// and invert color of copied matrix
    //////
    
    ////// resize and invert color ( by reference )`
    Mat imgSizeInverse(imgMat, r);  /// copy by reference ( connected to origin )
    bitwise_not(imgSizeInverse, imgSizeInverse);    /// it also inverse color of origin image and the position of changing is followed by r
    //////
    
    /// gen image windows
    namedWindow("imgMat");
    namedWindow("imgCopy");
    namedWindow("imgSizeRect");
    namedWindow("imgCopyTo");
    namedWindow("imgRectedCopyTo");
    namedWindow("imgCopyToNext");
    namedWindow("imgSizeInverse");

    while(1)
    {
        // add an effect
        
        // bit operation to original image
        bitwise_not(imgMat, imgMat);
//        Sobel(imgMat, imgMat, imgMat.depth(), 1, 0);
        
        imshow("imgMat", imgMat);
        imshow("imgCopy", imgCopy);
        imshow("imgSizeRect", imgSizeRect);
        imshow("imgCopyTo", imgCopyTo);
        imshow("imgRectedCopyTo", imgRectedCopyTo);
        imshow("imgCopyToNext", imgCopyToNext);
        imshow("imgSizeInverse", imgSizeInverse);

        if(waitKey(0) >= 0) break;
    }
    
    destroyAllWindows();
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}
