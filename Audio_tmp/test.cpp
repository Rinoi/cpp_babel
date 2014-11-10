#include <iostream>
#include <opencv/cv.h>
#include <opencv/highgui.h>
 
using namespace std;
 
int main(int argc, char *argv[])
{
  IplImage* img = 0;
  int height,width,step,channels;
  uchar *data;
 
  // creation et deplacement de la fenetre.
  cvNamedWindow("Fenetre_test", CV_WINDOW_AUTOSIZE);
  cvMoveWindow("Fenetre_test", 100, 100);
 
  // Initialise la capture 
  CvCapture* capture = cvCaptureFromCAM(0);
  
 
  while(cvWaitKey(20)!=' '){
    img=cvQueryFrame(capture);   
 
 
    // get the image data
    height    = img->height;
    width     = img->width;
    step      = img->widthStep;
    channels  = img->nChannels;
    data      = (uchar *)img->imageData;
    cout << "Processing a " << width << "x" << height << " image with " << channels << " channels" << endl;
 
    // show the image
    cvShowImage("Fenetre_test", img );
 
  }
 
  // release the image
  cvReleaseImage(&img );
  cvReleaseCapture(&capture);
  return 0;
}
