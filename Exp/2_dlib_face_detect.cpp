//
// Created by hk003ros on 2021/12/2.
//
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/opencv.h>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace dlib;
using namespace std;

cv::Rect Detect( cv::Mat im )
{
    cv::Rect R;
    frontal_face_detector detector = get_frontal_face_detector();
    array2d<bgr_pixel> img;
    assign_image( img, cv_image<uchar>(im) );
    std::vector<rectangle> dets = detector( img );

    if( dets.size() != 0 )
    {
        int Max = 0;
        int area = 0;
        for( unsigned long t = 0; t < dets.size(); ++t )
        {
            if( area < dets[t].width() * dets[t].height() )
            {
                area = dets[t].width() * dets[t].height();
                Max = t;
            }
        }

        R.x = dets[Max].left();
        R.y = dets[Max].top();
        R.width = dets[Max].width();
        R.height = dets[Max].height();
        cout << "(" << R.x << "," << R.y << "," << R.width << "," << R.height << ")" << endl;
    }
    return R;
}

int main()
{
    cout << "hello face detect" << endl;

    string path = "/home/hk003ros/Downloads/face.png";

    try
    {
        cv::Mat src, dec;
        src = cv::imread( path );
        src.copyTo( dec );
        cv::cvtColor( dec, dec, CV_BGR2GRAY );
        cv::Rect box;
        box = Detect( dec );
        cv::rectangle( src, box, cv::Scalar(0, 0, 255), 2, 1, 0 );

        cv::imshow( "frame", src );
        cv::waitKey( 0 );
    }
    catch( exception& e )
    {
        cout << e.what() << endl;
    }

    return 0;
}





//
//
//#include <dlib/image_processing/frontal_face_detector.h>
//#include <dlib/gui_widgets.h>
//#include <dlib/image_io.h>
//#include <iostream>
//
//using namespace dlib;
//using namespace std;
//
//
//int main_no_Use()
//{
//    cout << "hello face detect " << endl;
//
//    try
//    {
//        frontal_face_detector detector = get_frontal_face_detector();
//        image_window win;
//        string img_path = "/home/hk003ros/Downloads/face.png";
//
//        cout << "processing image ..." << endl;
//        array2d<unsigned char> img;
//        load_image( img, img_path.c_str() );
//        pyramid_up( img );
//
//        std::vector<rectangle> dets = detector( img );
//
//        cout << "number of faces detected" << dets.size() << endl;
//
//        win.clear_overlay();
//        win.set_image( img );
//        win.add_overlay( dets, rgb_pixel(255, 0, 0));
//
//        cout << "processing is over." << endl;
//        cin.get();
//    }
//    catch (exception& e)
//    {
//        cout << "\nexception thrown!" << endl;
//        cout << e.what() << endl;
//    }
//
//    return 0;
//}