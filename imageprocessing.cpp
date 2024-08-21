#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
void adjustBrightness(const string& imagePath) {
    Mat image = imread(imagePath);
    Mat newimage = image.clone();
    for (int x = 0; x < image.rows; ++x) {
        for (int y = 0; y < image.cols; ++y) {
            Vec3b pixel = image.at<Vec3b>(x, y);
            for (int c = 0; c < 3; ++c) {
                pixel[c] = saturate_cast<uchar>(pixel[c] + 50);  // Increase brightness
            }
            newimage.at<Vec3b>(x, y) = pixel;
        }
    }
    imshow("Original Image", image);
    imshow("Brightness Adjusted Image", newimage);
    waitKey(0);
}
void adjustSaturation(const string& imagePath) {
    Mat image = imread(imagePath);
    Mat hsv;
    cvtColor(image, hsv, COLOR_BGR2HSV);
    for (int x = 0; x < hsv.rows; ++x) {
        for (int y = 0; y < hsv.cols; ++y) {
            Vec3b pixel = hsv.at<Vec3b>(x, y);
            pixel[1] = 255;  // Set saturation to maximum
            hsv.at<Vec3b>(x, y) = pixel;
        }
    }
    Mat newimage;
    cvtColor(hsv, newimage, COLOR_HSV2BGR);
    imshow("Original Image", image);
    imshow("Saturation Maxed Image", newimage);
    waitKey(0);
}
void upscaleImage(const string& imagePath, double factor) {
    Mat image = imread(imagePath);
    int rows = static_cast<int>(factor * image.rows);
    int cols = static_cast<int>(factor * image.cols);
    Mat newimage(rows, cols, CV_8UC3);   
    for (int x = 0; x < newimage.rows; ++x) {
        for (int y = 0; y < newimage.cols; ++y) {
            int f = static_cast<int>(x / factor);
            int g = static_cast<int>(y / factor);
            Vec3b pixel = image.at<Vec3b>(f, g);
            newimage.at<Vec3b>(x, y) = pixel;
        }
    }
    imshow("Original Image", image);
    imshow("Upscaled Image", newimage);
    waitKey(0);
}
void downscaleImage(const string& imagePath, double factor) {
    Mat image = imread(imagePath);
    int i = static_cast<int>(image.rows * factor);
    int j = static_cast<int>(image.cols * factor);
    Mat newimage(i, j, CV_8UC3);   
    for (int x = 0; x < i; ++x) {
        for (int y = 0; y < j; ++y) {
            int g = static_cast<int>(x / factor);
            int f = static_cast<int>(y / factor);
            newimage.at<Vec3b>(x, y) = image.at<Vec3b>(g, f);
        }
    }
    imshow("Original Image", image);
    imshow("Downscaled Image", newimage);
    waitKey(0);
}

int main(int argc, char** argv) {
    if (argc < 2) {
	cout<<"insufficient arguments"<<endl;
        return 1;
    }
    string operation = argv[1];
    string imagepath = argv[2];
    if (operation == "brightness") {
        adjustBrightness(imagepath);
    } else if (operation == "saturate") {
        adjustSaturation(imagepath);
    } else if (operation == "upscale") {
        if (argc < 4) {
            cout << "Error: Scaling factor not provided for upscaling!" << endl;
            return 1;
        }
        double factor = stod(argv[3]);
        upscaleImage(imagepath, factor);
    } else if (operation == "downscale") {
        if (argc < 4) {
            cout << "Error: Scaling factor not provided for downscaling!" << endl;
            return 1;
        }
        double factor = stod(argv[3]);
        downscaleImage(imagepath, factor);
    } else {
        cout << "Error: Unknown operation '" <<endl;
        return 1;
    }

    return 0;
}
