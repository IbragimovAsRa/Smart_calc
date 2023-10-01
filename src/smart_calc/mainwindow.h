#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
extern "C" {
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../calculations.h"
}
#include <QMessageBox>
#include <QVector>
#include <iostream>
#include <string>

#include "creditwindow.h"
#include "depositwindow.h"
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  CreditWindow *creditWindow;
  DepositWindow *depositWindow;
  double xBegin, xEnd, yBegin, yEnd, h, X;
  int N;
  QVector<double> x, y;

  void digits_numbers();
  void calculate(char *xStr);
  void plot_graf(char *exprsnStr);
  void clean_graf();
  void clean_workspace();

 private slots:

  void on_pushButtonEqual_clicked();
  void on_pushButtonZero_clicked();
  void on_pushButtonOne_clicked();
  void on_pushButtonTwo_clicked();
  void on_pushButtonThree_clicked();
  void on_pushButtonFour_clicked();
  void on_pushButtonFive_clicked();
  void on_pushButtonSix_clicked();
  void on_pushButtonSeven_clicked();
  void on_pushButtonEight_clicked();
  void on_pushButtonNine_clicked();
  void on_pushButtonPlus_clicked();
  void on_pushButtonOpenBrace_clicked();
  void on_pushButtonCloseBrace_clicked();
  void on_pushButtonPow_clicked();
  void on_pushButtonDivision_clicked();
  void on_pushButtonMult_clicked();
  void on_pushButtonAC_clicked();
  void on_pushButtonX_clicked();
  void on_pushButtonPlot_clicked();
  void on_pushButtonSqrt_clicked();
  void on_pushButtonLn_clicked();
  void on_pushButtonLog_clicked();
  void on_pushButtonMod_clicked();
  void on_pushButtonSin_clicked();
  void on_pushButtonCos_clicked();
  void on_pushButtonTan_clicked();
  void on_pushButtonAsin_clicked();
  void on_pushButtonAcos_clicked();
  void on_pushButtonAtan_clicked();
  void on_pushButtonClean_clicked();
  void on_pushButtonDefault_clicked();
  void on_pushButtonCreditWindow_clicked();
  void on_pushButtonDepositWindow_clicked();
  void on_pushButtonMinus_clicked();
  void on_pushButtonDot_clicked();
  void on_pushButtonBack_clicked();
};
#endif  // MAINWINDOW_H
