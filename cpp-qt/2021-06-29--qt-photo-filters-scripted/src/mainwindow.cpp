#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "model.h"
#include <QFileDialog>
#include <QtDebug>
#include <QPixmap>
#include <QStandardPaths>
#include <opencv2/opencv.hpp>
#include <sol/sol.hpp>
#include <algorithm>

MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::on_buttonLoad_clicked() {
  qDebug("--load function");

  auto filename = QFileDialog::getOpenFileName(
    this,
    tr("Open Image"),
    QStandardPaths::writableLocation(QStandardPaths::DownloadLocation),
    tr("Image Files (*.png *.jpg *.bmp)"));
  qDebug() << "filename: " << filename;

  if (filename.isNull()) {
    qDebug() << "filename is null";
    qDebug("--done");
    return;
  }

  auto originalMat = cv::imread(filename.toStdString());

  if (!originalMat.empty()) {
    qDebug() << "originalMat is ok";
    cv::cvtColor(originalMat, originalMat, cv::COLOR_BGRA2RGBA);
    model.originalMat = originalMat;
    refreshFromModel();
  } else {
    qDebug() << "originalMat is empty";
  }
  qDebug("--done loading");
}

void MainWindow::refreshFromModel() {
  qDebug() << "---refresh function";

  auto& originalMat = model.originalMat;
  auto& transformedMat = model.transformedMat;
  qDebug() << "originalMat.empty() = " << originalMat.empty();
  qDebug() << "transformedMat.empty() = " << transformedMat.empty();

  // display the original image
  if (!originalMat.empty()) {
    auto qt_image = QImage(originalMat.data,
                           originalMat.cols,
                           originalMat.rows,
                           QImage::Format_RGBA8888);
    Q_ASSERT(!qt_image.isNull());

    auto pixmap = QPixmap::fromImage(qt_image);
    Q_ASSERT(!pixmap.isNull());

    int w = ui->imageOriginal->width();
    int h = ui->imageOriginal->height();
    ui->imageOriginal->setPixmap(pixmap.scaled(w, h, Qt::KeepAspectRatio));
  }

  // transform the image
  if (!originalMat.empty()) {
    transformedMat = originalMat.clone();

    auto& lua = model.lua;

    lua.set_function("grayscale", [&]() {
      cv::cvtColor(transformedMat, transformedMat, cv::COLOR_RGBA2GRAY);
      cv::cvtColor(transformedMat, transformedMat, cv::COLOR_GRAY2RGBA);
    });

    lua.set_function("invert", [&]() {
      transformedMat.forEach<cv::Vec4b>([](auto& pixel, auto) { //
        pixel[0] = 255 - pixel[0];
        pixel[1] = 255 - pixel[1];
        pixel[2] = 255 - pixel[2];
      });
    });

    lua.set_function("noRed", [&]() {
      transformedMat.forEach<cv::Vec4b>(
        [](auto& pixel, auto) { pixel[0] = 0; });
    });

    lua.set_function("noGreen", [&]() {
      transformedMat.forEach<cv::Vec4b>(
        [](auto& pixel, auto) { pixel[1] = 0; });
    });

    lua.set_function("noBlue", [&]() {
      transformedMat.forEach<cv::Vec4b>(
        [](auto& pixel, auto) { pixel[2] = 0; });
    });

    lua.set_function("resize", [&](float x, float y) {
      cv::resize(transformedMat, transformedMat, cv::Size(), x, y);
    });

    lua.set_function("clamp", [&](uchar channel, uchar a, uchar b) {
      channel = std::clamp(channel, (uchar)0, (uchar)3);
      a = std::clamp(a, (uchar)0, (uchar)255);
      b = std::clamp(b, (uchar)0, (uchar)255);
      if (b < a)
        std::swap(a, b);

      transformedMat.forEach<cv::Vec4b>([&](auto& pixel, auto) {
        pixel[channel] = std::clamp(pixel[channel], a, b);
      });
    });

    lua.script(ui->textEditLuaScript->toPlainText().toStdString());
  }

  // display the transformed image
  if (!transformedMat.empty()) {
    auto qt_image = QImage(transformedMat.data,
                           transformedMat.cols,
                           transformedMat.rows,
                           QImage::Format_RGBA8888);
    Q_ASSERT(!qt_image.isNull());

    auto pixmap = QPixmap::fromImage(qt_image);
    Q_ASSERT(!pixmap.isNull());

    int w = ui->imageTransformed->width();
    int h = ui->imageTransformed->height();
    ui->imageTransformed->setPixmap(pixmap.scaled(w, h, Qt::KeepAspectRatio));
  }

  qDebug() << "---refreshed";
}

void MainWindow::on_buttonSave_clicked() {
  qDebug("--save function");

  if (!model.transformedMat.empty()) {
    auto filename = QFileDialog::getSaveFileName(
      this,
      tr("Save Image"),
      QStandardPaths::writableLocation(QStandardPaths::DownloadLocation),
      tr("Image Files (*.png *.jpg *.bmp)"));
    qDebug() << "filename: " << filename;

    if (!filename.isEmpty())
      cv::imwrite(filename.toStdString(), model.transformedMat);
  }

  qDebug("--done saving");
}

void MainWindow::on_textEditLuaScript_textChanged() {
  refreshFromModel();
}
