#ifndef IMAGE_PROVIDER_H
#define IMAGE_PROVIDER_H

#include <opencv2/opencv.hpp>
#include <QQuickImageProvider>

class ImageProvider : public QQuickImageProvider
{
public:
    ImageProvider() : QQuickImageProvider(QQuickImageProvider::Image)
    {
        image1 = QImage("C:/Users/grune/Downloads/pics/____a.jpeg");
    }

    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize) override
    {
        qDebug() << "trying to serve: " << id;
        if (id == "image1")
            return image1;
        else
            return image2;
    }

public:
    void loadImages(const QString &filename)
    {
        auto fn = filename;
        fn.remove("file:///");
        qDebug() << "trying to load: " << fn;
        image1 = QImage(fn);
        qDebug() << "loaded; height: " << image1.size().height();

        auto cv_image = cv::imread(fn.toStdString());
        qDebug("cv_image read");
        Q_ASSERT(!cv_image.empty());
        cv::cvtColor(cv_image, cv_image, cv::COLOR_BGRA2GRAY);
        cv::cvtColor(cv_image, cv_image, cv::COLOR_GRAY2RGBA);
        qDebug("cv_image converted");
        image2 = QImage(cv_image.data, cv_image.cols, cv_image.rows, QImage::Format_RGBA8888);
        image2 = image2.copy();
        qDebug("cv_image set");
    }

private:
    QImage image1;
    QImage image2;
};

#endif // IMAGE_PROVIDER_H
