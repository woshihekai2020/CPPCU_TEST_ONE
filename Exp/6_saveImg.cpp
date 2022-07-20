//
// Created by hk003ros on 2021/12/3.
//
#include <iostream>

#include <string>
//#include <stdlib,h>
//#include <pthread.h>

#include <librealsense2/rs.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#define NUM_THREADS 1
#define WIDTH 1280
#define HEIGHT 720


int main()
{
    std::cout << "hello 5_save_video_img 2" << std::endl;

    rs2::log_to_console( RS2_LOG_SEVERITY_ERROR );
    rs2::config cfg;
    cfg.enable_stream( RS2_STREAM_COLOR, WIDTH, HEIGHT, RS2_FORMAT_BGR8, 30 );  //rgb  : 1920 X 1080 , RAW: 640 X 480
    cfg.enable_stream( RS2_STREAM_DEPTH, WIDTH, HEIGHT, RS2_FORMAT_Z16, 30 );   //depth:
    rs2::pipeline pipe;
    pipe.start( cfg );
    rs2::frameset data;

    std::string rgb_path   = "~/CLionProjects/CPP/CPPCU_TEST_ONE/1_data/color/";
    std::string depth_path = "~/CLionProjects/CPP/CPPCU_TEST_ONE/1_data/depth/";
    int num = 0;

    while( 1 )
    {
        data = pipe.wait_for_frames();
        rs2::frame depth = data.get_depth_frame();
        rs2::frame color = data.get_color_frame();
        if( !color || !depth ) break;

        std::string strNum = std::to_string( num );
        while( strNum.size() < 6 )
            strNum = std::to_string( 0 ) + strNum;

        cv::Mat image( cv::Size(WIDTH, HEIGHT), CV_8UC3, (void*)color.get_data(), cv::Mat::AUTO_STEP );
        cv::Mat depthmat( cv::Size(WIDTH, HEIGHT), CV_16U, (void*)depth.get_data(), cv::Mat::AUTO_STEP );

        std::string rgbStr   = rgb_path + strNum + ".color.jpg";
        std::string depthStr = depth_path + strNum + ".depth.png";

        cv::imshow( "rgb", image );
        cv::waitKey( 10 );

        cv::imwrite( rgbStr.c_str(), image );
        cv::imwrite( depthStr.c_str(), depthmat );

        num++ ;
    }

    while( cv::waitKey( 20 ) != 'q' );




//    pthread_t tids[ NUM_THREADS ];
//
//    int ret = pthread_create( *tidsp0], NULL, saveIMG, NULL );
//    if( ret != 0 )
//        std::cout << "pthread_create error : error_code = " << ret << std::endl;
//
//    pthread_exit( NULL );


    return 0;

}




//int saveIMG()
//{
//    rs2::log_to_console( RS2_LOG_SEVERITY_ERROR );
//    rs2::config cfg;
//    cfg.enable_stream( RS2_STREAM_COLOR, 640, 480, RS2_FORMAT_BGR8, 30 );
//    cfg.enable_stream( RS2_STREAM_DEPTH, 640, 480, RS2_FORMAT_Z16, 30 );
//    rs2::pipeline pipe;
//    pipe.start( cfg );
//    rs2::frameset data;
//
//    std::string rgb_path   = "/home/hk003ros/CLionProjects/CPP/data/color/";
//    std::string depth_path = "/home/hk003ros/CLionProjects/CPP/data/depth/";
//    int num = 0;
//
//    while( 1 )
//    {
//        data = pipe.wait_for_frames();
//        rs2::frame depth = data.get_depth_frame();
//        rs2::frame color = data.get_color_frame();
//        if( !color || !depth ) break;
//
//        std::string strNum = std::to_string( num );
//        while( strNum.size() < 6 )
//            strNum = std::to_string( 0 ) + strNum;
//
//        cv::Mat image( cv::Size(640, 480), CV_8UC3, (void*)color.get_data(), cv::Mat::AUTO_STEP );
//        cv::Mat depthmat( cv::Size(640, 480), CV_16U, (void*)depth.get_data(), cv::Mat::AUTO_STEP );
//
//        std::string rgbStr   = rgb_path + strNum + ".color.jpg";
//        std::string depthStr = depth_path + strNum + ".depth.png";
//
//        cv::imwrite( rgbStr.c_str(), image );
//        cv::imwrite( depthStr.c_str(), depthmat );
//
//        num++ ;
//    }
//
//    while( cv::waitKey( 20 ) != 'q' );
//
//    return -1;
//}









