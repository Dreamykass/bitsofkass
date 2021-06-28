#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "model.h"

QT_BEGIN_NAMESPACE
namespace Ui {
  class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

private slots:
  void on_buttonLoad_clicked();

  void on_buttonSave_clicked();

  void on_checkBoxGrayscale_toggled(bool checked);

  void on_checkBoxInverted_toggled(bool checked);

  void on_checkBoxNoRed_toggled(bool checked);

  void on_checkBoxNoGreen_toggled(bool checked);

  void on_checkBoxNoBlue_toggled(bool checked);

private:
  void refreshFromModel();

private:
  Ui::MainWindow* ui;
  Model model;
};
#endif // MAINWINDOW_H
