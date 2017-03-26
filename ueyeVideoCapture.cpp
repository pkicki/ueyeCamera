#include <iostream>
#include <ueye.h>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
HIDS hCam = 1;

int main() {
	cout<<"Success-Code: "<<IS_SUCCESS<<endl;

	// camera initialization
	int returnedStatus = is_InitCamera(&hCam, NULL);
	cout<<"Status Init: "<<returnedStatus<<endl;

	// set image size
	int imgWidth=792, imgHeight=480;

	char *capturedImage = NULL;
	int memoryId = 0;

	// allocate memory for image capturing
	returnedStatus = is_AllocImageMem(hCam, imgWidth, imgHeight, 24, &capturedImage, &memoryId);
	cout<<"Status AllocImage: "<<returnedStatus<<endl;

	returnedStatus = is_SetImageMem(hCam, capturedImage, memoryId);
	cout<<"Status SetImageMem: "<<returnedStatus<<endl;

	char c;
	for(;;){
		// capture frame
		is_CaptureVideo(hCam, 10);
		IplImage* tmpImg;
		tmpImg = cvCreateImageHeader(cvSize(imgWidth, imgHeight), IPL_DEPTH_8U, 3);

		// assign image address to IplImage data pointer
		tmpImg->imageData = capturedImage;

		// create openCV Mat object with frame obtained form camera
		cv::Mat image = cv::Mat(tmpImg,false);

		// display captured image
		imshow( "Display window", image );
		c = (char)cvWaitKey(10);
		if (c == 27) break;
	}

	is_ExitCamera(hCam);
}
