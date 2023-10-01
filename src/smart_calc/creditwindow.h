#ifndef CREDITWINDOW_H
#define CREDITWINDOW_H

#include <QMainWindow>
#include <cmath>
#include <iostream>

namespace Ui {
class CreditWindow;
}

class CreditWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit CreditWindow(QWidget *parent = nullptr);
  ~CreditWindow();

 private slots:

  void on_pushButtonCalc_clicked();

  void on_pushButtonClean_clicked();

 private:
  Ui::CreditWindow *ui;
};

#endif  // CREDITWINDOW_H
