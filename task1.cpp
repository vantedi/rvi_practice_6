//Задание 1
//Картинка
/*#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    CascadeClassifier face_cascade, eyes_cascade, smile_cascade;

    if (!face_cascade.load("C:/Users/James-Bond/Desktop/Распознование зрительных образов/Каскады/haarcascade_frontalface_default.xml") ||
        !eyes_cascade.load("C:/Users/James-Bond/Desktop/Распознование зрительных образов/Каскады/haarcascade_eye_tree_eyeglasses.xml") ||
        !smile_cascade.load("C:/Users/James-Bond/Desktop/Распознование зрительных образов/Каскады/haarcascade_smile.xml")) {
        printf("ошибка загрузки\n");
        return -1;
    }

    Mat image = imread("C:/Users/James-Bond/Downloads/ZUA1.png");
    if (image.empty()) {
        cout << "ошибка загрузки картинки" << endl;
        return -1;
    }

    Mat gray_image;
    cvtColor(image, gray_image, COLOR_BGR2GRAY);
    equalizeHist(gray_image, gray_image);

    vector<Rect> faces;
    face_cascade.detectMultiScale(gray_image, faces);
    
    for (const Rect& face : faces) {
        rectangle(image, face, Scalar(255, 0, 0), 2);

        Mat faceROI = gray_image(face);
        vector<Rect> eyes, smile;
       
        eyes_cascade.detectMultiScale(faceROI, eyes);
        for (const Rect& eye : eyes) {
            rectangle(image, face.tl() + eye.tl(), face.tl() + eye.br(), Scalar(0, 255, 0), 2);
        }
        
        //smile_cascade.detectMultiScale(faceROI, smile, 2.209, 3, 0, Size(40, 40));
        smile_cascade.detectMultiScale(faceROI, smile, 1.1, 30, 0, Size(30, 30));
        for (const Rect& s : smile) {
            rectangle(image, face.tl() + s.tl(), face.tl() + s.br(), Scalar(0, 0, 255), 2);
        }

    }
    
    namedWindow("распознавание лиц", WINDOW_NORMAL);
    resizeWindow("распознавание лиц", 600, 338);
    imshow("распознавание лиц", image);
    waitKey(0);

    return 0;
}*/

//Видео
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    CascadeClassifier face_cascade, eyes_cascade, smile_cascade;

    if (!face_cascade.load("C:/Users/James-Bond/Desktop/Распознование зрительных образов/Каскады/haarcascade_frontalface_default.xml") ||
        !eyes_cascade.load("C:/Users/James-Bond/Desktop/Распознование зрительных образов/Каскады/haarcascade_eye_tree_eyeglasses.xml") ||
        !smile_cascade.load("C:/Users/James-Bond/Desktop/Распознование зрительных образов/Каскады/haarcascade_smile.xml")) {
        printf("Error loading cascade classifiers!\n");
        return -1;
    }

    String videoPath = "C:/Users/James-Bond/Downloads/ZUA.mp4";
    VideoCapture cap(videoPath);

    if (!cap.isOpened()) {
        cout << "ошибка загрузки видео" << endl;
        return -1;
    }
    
    VideoWriter outputVideo("C:/Users/James-Bond/Downloads/ZUA_output.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), cap.get(CAP_PROP_FPS),Size(1280, 720));
    
    while (true) {
        Mat frame;
        cap >> frame;

        if (frame.empty())
            break;

        Mat gray_frame;
        cvtColor(frame, gray_frame, COLOR_BGR2GRAY);
        equalizeHist(gray_frame, gray_frame);

        GaussianBlur(frame, frame, Size(3, 3), 0);

        vector<Rect> faces;
        face_cascade.detectMultiScale(gray_frame, faces);

        for (const Rect& face : faces) {
            rectangle(frame, face, Scalar(255, 0, 0), 2);

            Mat faceROI = gray_frame(face);
            vector<Rect> eyes, smile;

            eyes_cascade.detectMultiScale(faceROI, eyes);
            for (const Rect& eye : eyes) {
                rectangle(frame, face.tl() + eye.tl(), face.tl() + eye.br(), Scalar(0, 255, 0), 2);
            }

            smile_cascade.detectMultiScale(faceROI, smile, 1.1, 30, 0, Size(30, 30));
            for (const Rect& s : smile) {
                rectangle(frame, face.tl() + s.tl(), face.tl() + s.br(), Scalar(0, 0, 255), 2);
            }

        }

        namedWindow("распознавание лиц", WINDOW_NORMAL);
        resizeWindow("распознавание лиц", 600, 338);
        imshow("распознавание лиц", frame);
        outputVideo.write(frame);

        if (waitKey(1) == 27)
            break;
    }

    cap.release();
    outputVideo.release();
    destroyAllWindows();

    return 0;
}
