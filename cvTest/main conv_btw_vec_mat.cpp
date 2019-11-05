// transition b/w data structure vector and matrix class data

//  main4.cpp
//  ocvTest
//
//  Created by macproo on 16/10/2019.
//  Copyright © 2019 macproo. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, const char * argv[]) {
    
    /// vector to matrix class
    int r = 3, c = 4;
    vector<float> vf;
    
    int cnt = 0;
    for ( int i = 0; i < c; ++i )
    {
        for ( int j = 0; j < r; ++j )
        {
            vf.push_back(cnt++);
        }
    }
    
    Mat m = Mat(r, c, CV_32FC1);
    
    memcpy(m.data, vf.data(), vf.size() * sizeof(float));
    
    cout << m << endl;
    
    /// matrix class to vector
    
    vector<float> vf2;
    vf2.assign((float*)m.datastart, (float*)m.dataend);
    
    cnt = 0;
    for ( int i = 0; i < c; ++i )
    {
        for ( int j = 0; j < r; ++j )
        {
            printf("%lf ", vf2[cnt++]);
        }
        printf("\n");
    }
    
    return 0;
}
