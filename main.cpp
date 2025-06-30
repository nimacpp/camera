#include <QApplication>
#include <QCamera>
#include <QCameraInfo>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QShortcut>
#include <QDateTime>
#include <QDir>
#include <QMessageBox>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Main window
    QWidget window;
    window.setWindowTitle("Camera App");

    // Camera setup
    QCamera *camera = new QCamera(QCameraInfo::defaultCamera());
    QCameraViewfinder *viewfinder = new QCameraViewfinder;
    camera->setViewfinder(viewfinder);

    // Image capture
    QCameraImageCapture *imageCapture = new QCameraImageCapture(camera);

    // Capture button
    QPushButton *captureButton = new QPushButton("Capture Image");

    // Capture action (used by both button and shortcuts)
    auto captureImage = [&]() {
        QString filename = QDir::homePath() + "/Pictures/image_" +
                           QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss") + ".jpg";
        imageCapture->capture(filename);
    };

    QObject::connect(captureButton, &QPushButton::clicked, captureImage);

    // Shortcuts
    QShortcut *spaceShortcut = new QShortcut(QKeySequence(Qt::Key_Space), &window);
    QObject::connect(spaceShortcut, &QShortcut::activated, captureImage);

    QShortcut *ctrlSShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_S), &window);
    QObject::connect(ctrlSShortcut, &QShortcut::activated, captureImage);

    // Show confirmation when image is saved
    QObject::connect(imageCapture, &QCameraImageCapture::imageSaved,
                     [](int, const QString &fileName) {
                         QMessageBox::information(nullptr, "Image Saved", "Saved to:\n" + fileName);
                     });

    // Layout
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(viewfinder);
    layout->addWidget(captureButton);
    window.setLayout(layout);

    // Start
    camera->start();
    window.resize(800, 600);
    window.show();

    return app.exec();
}
