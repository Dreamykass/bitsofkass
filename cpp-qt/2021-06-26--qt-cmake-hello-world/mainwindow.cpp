#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <string>

MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::on_pushButton_pressed() {
  std::cerr << "button pressed\n";
  this->counter_value++;
  auto* textEdit = this->findChild<QTextEdit*>("textEdit");
  Q_ASSERT(textEdit);
  textEdit->setText(
    QString::fromStdString(std::to_string(this->counter_value)));
}
