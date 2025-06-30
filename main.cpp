#include <QApplication>
#include <QTimer>
#include <QLabel>
#include <QVBoxLayout>
#include <QPixmap>
#include <QImage>
#include <QMessageBox>
#include <QShortcut>
#include <QDateTime>
#include <QDir>
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

    // Load Haar cascade (make sure this file exists in the app folder)
    cv::CascadeClassifier faceCascade;
    if (!faceCascade.load("frontalface.xml")) {
        QMessageBox::critical(nullptr, "Error", "Failed to load face detection model (frontalface.xml)");
        return -1;
    }

    // Open camera
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        QMessageBox::critical(nullptr, "Error", "Failed to open camera");
        return -1;
    }

    cv::Mat frame;
    std::vector<cv::Rect> faces;

    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, [&]() {
        cap >> frame;
        if (frame.empty()) return;

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

    // Shortcut to save image: Space key
    QShortcut shortcutSpace(Qt::Key_Space, &videoLabel);
    QObject::connect(&shortcutSpace, &QShortcut::activated, [&]() {
        if (!frame.empty()) {
            QString filename = QDir::homePath() + "/Pictures/image_" +
                               QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss") + ".jpg";
            bool saved = cv::imwrite(filename.toStdString(), frame);
            if (saved) {
                QMessageBox::information(nullptr, "Image Saved", "The image has been saved:\n" + filename);
            } else {
                QMessageBox::warning(nullptr, "Save Failed", "Failed to save the image.");
            }
        }
    });

    return app.exec();
}
