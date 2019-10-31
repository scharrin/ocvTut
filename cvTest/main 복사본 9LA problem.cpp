#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace std;
using namespace cv;

int main(int argc, const char * argv[]) {
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// dot, cross product
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    double va[] = {1,2,3};
    double vb[] = {0,0,6};
    double vc[3];
    Mat Va(3, 1, CV_64FC1, va);
    Mat Vb(3, 1, CV_64FC1, vb);
    Mat Vc(3, 1, CV_64FC1, vc);
   
//    cout << Va << endl << Vb << endl << Vc << endl;
    
    double res = Va.dot(Vb);    /// dot product
    Vc = Va.cross(Vb); /// cross product
    
//    cout << res << endl << Vc << endl;
//    cout << endl;
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// inhomogeneous linear system solver (related linear algebra)
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    double dm2[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
    Mat A(3, 3, CV_64FC1, dm2);
    Mat x(3, 1, CV_64FC1);
    
    double vvb[] = { 14, 32, 52 };
    Mat b(3, 1, CV_64FC1, vvb);
    solve(A, b, x, DECOMP_SVD); /// get x from Ax - b = 0

//    cout << "A * x" << endl << A * x << endl;   /// almost close b
//    cout << endl;
    
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// wired... (rightside) eigen vector and value (related algebra)
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    double f11[] = { 1, 0.466, -0.56, 0.446, 1, -0.239, -0.56, 0.39, 1 };
    Mat data(3, 3, CV_64FC1, f11);
//    cout << "input data" << endl;
//    cout << data << endl;
//    cout << endl;
    
    Mat eigvalues, eigvectors;
    eigen(data, eigvalues, eigvectors);
//    cout << "Eigenvalues" << endl;
//    cout << eigvalues << endl;
//    cout << "Eigenvectors" << endl;
//    cout << eigvectors << endl;
//    cout << endl;
//
    /// to validate this rightside eigen vector sould be
    /// A * eigVec = eigVal * eigVec /// It's not same both side production
    /// from eigen method comment
    /// src * eigenvectors.row(i).t() = eigenvalues.at<srcType>(i) * eigenvectors.row(i).t()
    
//    cout << "eigen vector validation" << endl;
//    cout << data * eigvectors << endl;   /// left side production (A)(eigVec)
//    cout << "sould be same" << endl;
    
    Mat ValueEye = Mat::eye(3, 3, CV_64FC1);  /// {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}

    ValueEye.at<double>(0, 0) = eigvalues.at<double>(0, 0);
    ValueEye.at<double>(1, 1) = eigvalues.at<double>(1, 0);
    ValueEye.at<double>(2, 2) = eigvalues.at<double>(2, 0);
//    cout << ValueEye * eigvectors << endl;
    
    
      
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// wired also.. validation needed
    /// SVD singualar value decomposition
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    double f12[] = { 1, 0.466, -0.56, 0.446, 1, -0.239, -0.56, 0.39, 1 };
    Mat data2(3, 3, CV_64FC1, f12);
    
    Mat u, v, w;
    SVDecomp(data2, w, u, v);
    
    cout << "SVD of" << endl;
    cout << data2 << endl << endl;
    cout << "w" << endl << w << endl;
    cout << "u" << endl << u << endl;
    cout << "v" << endl << v << endl;
//    cout << "w * u * v" << endl << (w * u * v).t() << endl;

    return 0;
}
