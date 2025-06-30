#include <QApplication>
#include <QTimer>
#include <QLabel>
#include <QVBoxLayout>
#include <QPixmap>
#include <QImage>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>

QImage Mat2QImage(const cv::Mat &mat) {
    if (mat.type() == CV_8UC3) {
        return QImage(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888).rgbSwapped();
    } else if (mat.type() == CV_8UC1) {
        return QImage(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_Grayscale8);
    }
    return QImage();
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QLabel videoLabel;
    videoLabel.setWindowTitle("Face Detection");
    videoLabel.resize(640, 480);

    // Load Haar cascade
    cv::CascadeClassifier faceCascade;
    faceCascade.load("frontalface.xml");

    // Open camera
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        qWarning("Camera not opened");
        return -1;
    }

    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, [&]() {
        cv::Mat frame;
        cap >> frame;
        if (frame.empty()) return;

        std::vector<cv::Rect> faces;
        cv::Mat gray;
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
        faceCascade.detectMultiScale(gray, faces);

        // Draw rectangles on faces
        for (const auto& face : faces) {
            cv::rectangle(frame, face, cv::Scalar(0, 255, 0), 2);
            cv::putText(frame, "Face", cv::Point(face.x, face.y - 10),
            cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar(0, 255, 0), 2);
        }

        videoLabel.setPixmap(QPixmap::fromImage(Mat2QImage(frame)).scaled(videoLabel.size(), Qt::KeepAspectRatio));
    });

    timer.start(30);  // ~33 fps
    videoLabel.show();

    return app.exec();
}
