#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect/barcode.hpp>

int main()
{

    cv::barcode::BarcodeDetector barcodeDetector("/home/cayirova/Downloads/opencv_3rdparty-wechat_qrcode/sr.prototxt",
                                                 "/home/cayirova/Downloads/opencv_3rdparty-wechat_qrcode/sr.caffemodel");
    cv::namedWindow("FrameOut",0);
    cv::namedWindow("FrameIn",0);
    std::vector< cv::Point > corners;
    std::vector< std::string > decoded_type;
    std::vector< std::string > decoded_info;

    cv::Mat frame = cv::imread("/home/cayirova/Downloads/opencv_3rdparty-wechat_qrcode/4_barcodes.jpg");

    cv::VideoCapture cap(0);

    while(1)
    {
        cap >> frame;

        cv::imshow("FrameIn",frame);

        barcodeDetector.detectAndDecodeWithType(frame,decoded_info,decoded_type,corners);


        //1- there is no barcode
        //2- barcode detected - but not recognized
        //3- barcode detected - but recognized

        if(!corners.empty())
        {
            cv::putText(frame, "Barcode detected !!!",cv::Point(50,50),cv::FONT_HERSHEY_COMPLEX,
                        1,cv::Scalar(0,255,255));

            for(int i = 0; i<(int)corners.size(); i+=4)
            {

                if(decoded_info[i/4].empty())
                {
                    cv::line(frame, corners[i],corners[i+1],cv::Scalar(255,0,0),2);
                    cv::line(frame, corners[i+1],corners[i+2],cv::Scalar(255,0,0),2);
                    cv::line(frame, corners[i+2],corners[i+3],cv::Scalar(255,0,0),2);
                    cv::line(frame, corners[i],corners[i+3],cv::Scalar(255,0,0),2);

                }
                else
                {
                    cv::line(frame, corners[i],corners[i+1],cv::Scalar(0,255,255),2);
                    cv::line(frame, corners[i+1],corners[i+2],cv::Scalar(0,255,255),2);
                    cv::line(frame, corners[i+2],corners[i+3],cv::Scalar(0,255,255),2);
                    cv::line(frame, corners[i],corners[i+3],cv::Scalar(0,255,255),2);

                    cv::putText(frame, decoded_type[i/4] + ":  " + decoded_info[i/4],corners[i],cv::FONT_HERSHEY_COMPLEX,
                            0.8,cv::Scalar(0,0,255));
                    std::cout<<decoded_type[i/4] + ":  " + decoded_info[i/4]<<std::endl;

                }




            }
        }

        cv::imshow("FrameOut",frame);
        cv::waitKey(1);
    }




    return 0;
}
