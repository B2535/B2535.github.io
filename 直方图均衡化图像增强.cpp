#include <iostream>  
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2\opencv.hpp>
#include<opencv2/dnn.hpp>
#include<fstream>

using namespace std;
using namespace cv;

Mat src, gray_src, edge_output;
const char* OUTPUT_TITLE = "Canny Result";

int main(int argc, char** argv) {
	src = imread("¿œ”•.png");
	if (!src.data) {
		printf("could not load image...\n");
		return -1;
	}

	char INPUT_TITLE[] = "input image";
	namedWindow(INPUT_TITLE, WINDOW_AUTOSIZE);
	imshow(INPUT_TITLE, src);
	cvtColor(src, gray_src, COLOR_BGR2GRAY);
	equalizeHist(gray_src,edge_output);
	imshow(OUTPUT_TITLE, edge_output);
	waitKey(0);
	return 0;
}



