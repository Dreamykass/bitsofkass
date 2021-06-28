#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QtDebug>
#include <QPixmap>
#include <opencv2/opencv.hpp>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_pressed()
{
    auto fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "C:/Users/grune/Downloads", tr("Image Files (*.png *.jpg *.bmp)"));
    qDebug() << "filename: " << fileName;

    auto *button = this->findChild<QPushButton *>("pushButton");

    auto cv_image = cv::imread(fileName.toStdString());
    if (!cv_image.empty())
    {
        qDebug() << "cv_image is ok";
        qDebug() << "rows: " << cv_image.cols << "; cols:" << cv_image.rows;

        cv::cvtColor(cv_image, cv_image, cv::COLOR_BGR2GRAY);
        cv::cvtColor(cv_image, cv_image, cv::COLOR_GRAY2RGBA);
        qDebug() << "converted...";

        auto qt_image = QImage(cv_image.data, cv_image.cols, cv_image.rows, QImage::Format_RGBA8888);
        auto pixmap = QPixmap::fromImage(qt_image);
        button->setIcon(pixmap);
        button->setIconSize(QSize(600, 600));
        qDebug() << "done";
    }
    else
    {
        qDebug() << "cv_image is empty";
    }
}
