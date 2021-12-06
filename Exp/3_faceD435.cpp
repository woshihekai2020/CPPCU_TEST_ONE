//
// Created by hk003ros on 2021/12/2.
//

#include <iostream>
#include <librealsense2/rs.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>

using namespace std;


#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/opencv.h>
#include <iostream>

using namespace dlib;


#define Width 640
#define Height 480
#define Fps 30

void enable_stream_init(rs2::config cfg)
{
    //Add desired streams to configuration
    cfg.enable_stream(RS2_STREAM_COLOR, Width, Height, RS2_FORMAT_BGR8, Fps);//向配置添加所需的流
    cfg.enable_stream(RS2_STREAM_DEPTH, Width, Height, RS2_FORMAT_Z16, Fps);
    cfg.enable_stream(RS2_STREAM_INFRARED, 1, Width, Height, RS2_FORMAT_Y8, Fps);
    cfg.enable_stream(RS2_STREAM_INFRARED, 2, Width, Height, RS2_FORMAT_Y8, Fps);
    cfg.enable_stream(RS2_STREAM_ACCEL, RS2_FORMAT_MOTION_XYZ32F);
    cfg.enable_stream(RS2_STREAM_GYRO, RS2_FORMAT_MOTION_XYZ32F);
}

cv::Rect Detect_3( cv::Mat im )
{
    cv::Rect R;
    frontal_face_detector detector = get_frontal_face_detector();
    array2d<bgr_pixel> img;
    assign_image( img, cv_image<uchar>(im) );
    std::vector<dlib::rectangle> dets = detector( img );

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
    cout << "hello D435" << endl;

    //配置realsense
    rs2::context ctx;
    auto list = ctx.query_devices(); // Get a snapshot of currently connected devices
    if (list.size() == 0)
        throw std::runtime_error("No device detected. Is it plugged in?");
    rs2::device dev = list.front();

    rs2::frameset frames;
    //Contruct a pipeline which abstracts the device
    rs2::pipeline pipe;//创建一个通信管道//https://baike.so.com/doc/1559953-1649001.html pipeline的解释
    //Create a configuration for configuring the pipeline with a non default profile
    rs2::config cfg;//创建一个以非默认配置的配置用来配置管道
    enable_stream_init(cfg);
    // start stream
    pipe.start(cfg);//指示管道使用所请求的配置启动流

    while( 1 )
    {
        cout << "frame" << endl;
        frames = pipe.wait_for_frames();//等待所有配置的流生成框架

        //   Align to color
        rs2::align align_to_color(RS2_STREAM_COLOR);
        frames = align_to_color.process(frames);

        //Get each frame
        rs2::frame color_frame = frames.get_color_frame();
        // Creating OpenCV Matrix from a color image
        cv::Mat color(cv::Size(Width, Height), CV_8UC3, (void*)color_frame.get_data(), cv::Mat::AUTO_STEP);

        if(color.empty()) return 1;


        cv::Mat tmp = color.clone();
        cv::cvtColor( tmp, tmp, CV_BGR2GRAY );
        cv::Rect box;
        box = Detect_3( tmp );
        cv::rectangle( color, box, cv::Scalar(0, 0, 255), 2, 1, 0 );

        cv::imshow( "color", color);
        cv::waitKey( 10 );
    }

    return 1;
}

