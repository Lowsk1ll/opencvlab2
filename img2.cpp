#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>
#include "opencv2/opencv.hpp"
#include <opencv2/imgproc.hpp>
#include <vector>

using namespace cv;
using namespace std;
	
void filter (const Mat& vvod, Mat& vivod, vector<double> kernel) {
	vivod = vvod;
	for (int i=1; i<vivod.rows-1; i++) {
		for (int j = 1; j<vivod.cols-1; j++) {
			vivod.at<Vec3b>(i,j)[0] = vvod.at<Vec3b>(i-1,j-1)[0]*kernel[0]+vvod.at<Vec3b>(i,j-1)[0]*kernel[1]+vvod.at<Vec3b>(i+1,j-1)[0]*kernel[2]+vvod.at<Vec3b>(i-1,j)[0]*kernel[3]+vvod.at<Vec3b>(i,j)[0]*kernel[4]+vvod.at<Vec3b>(i+1,j)[0]*kernel[5]+vvod.at<Vec3b>(i-1,j+1)[0]*kernel[6]+vvod.at<Vec3b>(i,j+1)[0]*kernel[7]+vvod.at<Vec3b>(i+1,j+1)[0]*kernel[8];
			vivod.at<Vec3b>(i,j)[1] = vvod.at<Vec3b>(i-1,j-1)[1]*kernel[0]+vvod.at<Vec3b>(i,j-1)[1]*kernel[1]+vvod.at<Vec3b>(i+1,j-1)[1]*kernel[2]+vvod.at<Vec3b>(i-1,j)[1]*kernel[3]+vvod.at<Vec3b>(i,j)[1]*kernel[4]+vvod.at<Vec3b>(i+1,j)[1]*kernel[5]+vvod.at<Vec3b>(i-1,j+1)[1]*kernel[6]+vvod.at<Vec3b>(i,j+1)[1]*kernel[7]+vvod.at<Vec3b>(i+1,j+1)[1]*kernel[8];
			vivod.at<Vec3b>(i,j)[2] = vvod.at<Vec3b>(i-1,j-1)[2]*kernel[0]+vvod.at<Vec3b>(i,j-1)[2]*kernel[1]+vvod.at<Vec3b>(i+1,j-1)[2]*kernel[2]+vvod.at<Vec3b>(i-1,j)[2]*kernel[3]+vvod.at<Vec3b>(i,j)[2]*kernel[4]+vvod.at<Vec3b>(i+1,j)[2]*kernel[5]+vvod.at<Vec3b>(i-1,j+1)[2]*kernel[6]+vvod.at<Vec3b>(i,j+1)[2]*kernel[7]+vvod.at<Vec3b>(i+1,j+1)[2]*kernel[8];
			}
		}
	}
void Blur (const Mat& vvod, Mat& vivod){
	vector<double> kernel = {0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1};
	filter(vvod,vivod,kernel);
}
	

int zapad(Mat img, int x, int y)
	{
		return img.at<uchar>(y-1,x-1)+2*img.at<uchar>(y,x-1)+img.at<uchar>(y+1,x-1)-img.at<uchar>(y-1,x+1)-2*img.at<uchar>(y,x+1)-img.at<uchar>(y+1,x+1);
	}
	
void Sobel(const Mat& vvod, Mat& vivod) {
	vivod = vvod.clone();
	int newt;
	for (int y=0; y<vvod.rows; y++)
		for(int x=0; x<vvod.cols; x++)
			vivod.at<uchar>(y,x) = 0.0;
	for(int y=1; y<vvod.rows-1;y++){
		for(int x=1; x<vvod.cols-1;x++){
			newt = zapad(vvod,x,y);
			vivod.at<uchar>(y,x) = newt;
		}
	}
}

int main(int argc, char** argv)
{
 // Read the image file
 Mat image = imread("image1.jpg");
 Mat image1;
 Mat image2;
 Mat image3;
 Mat image4;
 Mat image5 = imread("image1.jpg");

 // Check for failure
 if (image.empty()) 
 {
  cout << "Could not open or find the image" << endl;
  cin.get(); //wait for any key press
  return -1;
 }
 
 GaussianBlur(image,image1,Size(5,5),0,0);
 cvtColor(image,image2,COLOR_BGR2GRAY);
 
 Blur(image5,image3);
 
 Sobel(image2,image4);

 String windowName = "image1"; //Name of the window
 
 String windowName1 = "image2";
 
 String windowName2 = "image3";
 
 String windowName3 = "image4";

 namedWindow(windowName); // Create a window
 
 namedWindow(windowName1);
 
 namedWindow(windowName2);
 
 namedWindow(windowName3);
 
 imshow(windowName, image);

 imshow(windowName1, image1); // Show our image inside the created window.
 
 imshow(windowName2, image3);
 
 imshow(windowName3, image4);

 waitKey(0); // Wait for any keystroke in the window

 destroyWindow(windowName); //destroy the created window
 
 destroyWindow(windowName1);
 
 destroyWindow(windowName2);
 
 destroyWindow(windowName3); 

 return 0;
}
