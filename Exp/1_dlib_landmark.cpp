//
// Created by hk003ros on 2021/12/1.
//
#include <dlib/opencv.h>
#include <opencv2/opencv.hpp>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>

using namespace dlib;
using namespace std;




//face 64 landmark
int main()
{
    try
    {

        // Load face detection and pose estimation models.
        frontal_face_detector detector = get_frontal_face_detector();
        shape_predictor pose_model;
        deserialize("/home/hk003ros/CLionProjects/CPP/data/shape_predictor_68_face_landmarks.dat") >> pose_model;

        // Grab a frame
        string path = "/home/hk003ros/Downloads/face.png";
        cv::Mat temp = cv::imread(path);
        //imshow( "face", temp );
        //cv::waitKey(0);


        cv_image<bgr_pixel> cimg(temp);
        // Detect faces
        std::vector<rectangle> faces = detector(cimg);
        // Find the pose of each face.
        std::vector<full_object_detection> shapes;
        for (unsigned long i = 0; i < faces.size(); ++i)
            shapes.push_back(pose_model(cimg, faces[i]));

        if (!shapes.empty()) {
            for (int i = 0; i < 68; i++) {
                circle(temp, cvPoint(shapes[0].part(i).x(), shapes[0].part(i).y()), 3, cv::Scalar(0, 0, 255), -1);
                //	shapes[0].part(i).x();//68个
            }
        }
        imshow("Dlib特征点", temp);
        //cv::imwrite("saveXZQ_landmark.jpg", temp);
        cv::waitKey(0);

    }
    catch (exception& e)
    {
        cout << e.what() << endl;
    }

    return 0;
}

