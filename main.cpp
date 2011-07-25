#include <cstdio>
#include <highgui.h>
#include <cv.h>

int recogniseTrafficSigns(char* file)
{
    int FPS = 5;//Domyślny 5 milisekund

    cvNamedWindow("Camera",CV_WINDOW_AUTOSIZE);
    CvCapture* capture = 0;

    if(file == 0)
    {
        capture = cvCreateFileCapture(file);//Korzystamy z pliku
        FPS = cvGetCaptureProperty(capture,CV_CAP_PROP_FPS);//Jaki FPS ma film
    }
    else capture = cvCreateCameraCapture(-1);//Bierzemy dowolną kamerkę zakładam ,że mamy 1

    if(capture == 0){printf("\nNo source!\n");return -1;}

    IplImage* frame = cvQueryFrame(capture);//Zakładam ,że wszystkie klatki będą takie same póxniej poprawie aby nie tracić tej 1 klatki
    if(!frame)return -1;
    IplImage* smallerFrame = cvCreateImage(cvSize(frame->width / 2 ,frame->height/2 ),frame->depth,frame->nChannels);

    while(true)
    {
        frame = cvQueryFrame(capture);
        if(!frame)break;//Przerywamy jeżeli nie ma klatki
        cvPyrDown(frame,smallerFrame);

        cvShowImage("Camera",frame);

        char c = cvWaitKey(FPS);//Z jaką prędkością będzie pokazywany obraz
        if(c == 27)break;//Esc - jeżeli wciśnięty to przerywamy
    }

    cvReleaseCapture(&capture);//Sprzątamy po sobie
    cvDestroyWindow("Camera");
    return 0;
}

int main(int argc,char* argv[])
{
    if(recogniseTrafficSigns(argv[0]) == -1)printf("Error occured");

	return 0;
}
