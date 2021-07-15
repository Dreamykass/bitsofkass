#ifndef IMAGE_PROVIDER_H
#define IMAGE_PROVIDER_H

#include <opencv2/opencv.hpp>
#include <QQuickImageProvider>

class ImageProvider : public QQuickImageProvider
{
public:
    ImageProvider() : QQuickImageProvider(QQuickImageProvider::Image)
    {
    }

    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize) override
    {
        qDebug() << "trying to serve: " << id;
        QImage temp;

        if (id == "imageOriginal")
            temp = imageOriginal;
        else if (id == "imageDistorted")
            temp = imageDistorted;

        return temp;
    }

public:
    void loadImage(const QString &filename)
    {
        auto fn = filename;
        fn.remove("file:///");
        qDebug() << "trying to load: " << fn;
        imageOriginal = QImage(fn);
        qDebug() << "loaded; height: " << imageOriginal.size().height();

        auto cv_image = cv::imread(fn.toStdString());
        qDebug("cv_image read");
        Q_ASSERT(!cv_image.empty());

        cv::cvtColor(cv_image, cv_image, cv::COLOR_BGRA2RGBA);
        qDebug("cv_image converted");

        matOriginal = cv_image;
        imageOriginal = QImage(cv_image.data, cv_image.cols, cv_image.rows, QImage::Format_RGBA8888);
        matDistorted = cv_image;
        imageDistorted = imageOriginal.copy();
        qDebug("cv_image set");
    }

    void distort(QList<QSharedPointer<Distortion>> dists)
    {
        qDebug("actually distorting...");

        matDistorted = matOriginal.clone();

        foreach (const auto &dist, dists) {
            dist->distort(matDistorted);
        }

        imageDistorted = QImage(matDistorted.data,
                                matDistorted.cols,
                                matDistorted.rows,
                                QImage::Format_RGBA8888);

        qDebug("done!");
    }

private:
    cv::Mat matOriginal;
    QImage imageOriginal;
    cv::Mat matDistorted;
    QImage imageDistorted;
};

#endif // IMAGE_PROVIDER_H
