#include <stdio.h>
#include <opencv2/opencv.hpp>

cv::Mat detectBlobs(cv::Mat image) {
    cv::Mat greyImage;
    cv::cvtColor(image, greyImage, CV_BGR2GRAY);

    cv::Mat binaryImage;
    cv::threshold(greyImage, binaryImage, 100.0, 255.0, cv::THRESH_BINARY);

    cv::SimpleBlobDetector::Params params; 

    params.thresholdStep = 5;
    params.minThreshold = 40;
    params.maxThreshold = 60;
    params.minDistBetweenBlobs = 10.0; 

    params.filterByColor = true;
    params.blobColor = 255;

    //params.filterByArea = false;        
    params.minArea = 100.0;              
    params.maxArea = 8000.0;             

    params.filterByCircularity = false;
    params.minCircularity = 0;
    params.maxCircularity = 99999;

    params.filterByInertia = false;
    params.minInertiaRatio = 0;
    params.maxInertiaRatio = 99999;

    params.filterByConvexity = false;
    params.minConvexity = 0;
    params.maxConvexity = 99999;

    cv::SimpleBlobDetector blobDetector(params);
    std::vector<cv::KeyPoint> blobs;
    blobDetector.detect(binaryImage, blobs);

    cv::Mat blobImage;
    cv::drawKeypoints(binaryImage, blobs, blobImage, cv::Scalar::all(-1), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

    return blobImage;
    //return image;
}

int main( int argc, char** argv )
{
    if (argc != 2) {
        printf("Invalid number of arguments (1 needed)\n");
        return -1;
    }

    cv::VideoCapture cap(std::stoi(argv[1]));//"../captures/1.avi");//

    if (!cap.isOpened())
    {
        printf("No video data\n");
        return -1;
    }

    cv::Mat image;

    cv::namedWindow("Result",1);

    cap >> image;

    while(true) {
        image = detectBlobs(image);
        cv::imshow("Result",image);

        cap >> image;
        cv::waitKey(1);
    }

    return 0;
}