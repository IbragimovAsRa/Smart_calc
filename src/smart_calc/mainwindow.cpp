#include "mainwindow.h"

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::digits_numbers() {
  QPushButton *button = (QPushButton *)sender();
  ui->exprsnStr->setText(ui->exprsnStr->text() + button->text());
}

void MainWindow::on_pushButtonEqual_clicked() {
  MainWindow::calculate((char *)ui->xStr->text().toLocal8Bit().constData());
}

void MainWindow::on_pushButtonPlot_clicked() {
  MainWindow::plot_graf(
      (char *)ui->exprsnStr->text().toLocal8Bit().constData());
}
void MainWindow::plot_graf(char *exprsnStr) {
  clean_graf();

  char *xBeginStr = (char *)ui->xMin->text().toLocal8Bit().constData();
  MainWindow::xBegin = strtod(xBeginStr, NULL);

  char *xEndStr = (char *)ui->xMax->text().toLocal8Bit().constData();
  MainWindow::xEnd = strtod(xEndStr, NULL) + h;

  char *yBeginStr = (char *)ui->yMin->text().toLocal8Bit().constData();
  MainWindow::yBegin = strtod(yBeginStr, NULL);

  char *yEndStr = (char *)ui->yMax->text().toLocal8Bit().constData();
  MainWindow::yEnd = strtod(yEndStr, NULL);

  ui->widget->xAxis->setRange(xBegin, xEnd);
  ui->widget->yAxis->setRange(yBegin, yEnd);

  char *countPoint = (char *)ui->countPoint->text().toLocal8Bit().constData();
  MainWindow::N = (int)strtol(countPoint, NULL, 10);

  MainWindow::h = (xEnd - xBegin) / N;

  X = xBegin;
  while (X < xEnd) {
    x.push_back(X);
    y.push_back(computer(exprsnStr, X));
    X = X + h;
  }
  ui->widget->addGraph();
  ui->widget->graph(0)->addData(x, y);
  ui->widget->replot();
}

void MainWindow::calculate(char *xStr) {
  char *exprsnStr = (char *)ui->exprsnStr->text().toLocal8Bit().constData();
  double result = computer2(exprsnStr, (char *)xStr);
  ui->answerLabel->setText(QString::number(result));
}

void MainWindow::clean_workspace() {
  ui->exprsnStr->setText("");
  ui->answerLabel->setText("");
}
void MainWindow::clean_graf() {
  ui->widget->clearGraphs();
  x.clear();
  y.clear();
  ui->widget->replot();
}

void MainWindow::on_pushButtonDefault_clicked() {
  ui->xMin->setValue(-10);
  ui->yMin->setValue(-5);
  ui->xMax->setValue(10);
  ui->yMax->setValue(5);
  ui->xStr->setText("0");
  ui->countPoint->setValue(1000);
}

void MainWindow::on_pushButtonCreditWindow_clicked() {
  creditWindow = new CreditWindow(this);
  creditWindow->show();
}
void MainWindow::on_pushButtonDepositWindow_clicked() {
  depositWindow = new DepositWindow(this);
  depositWindow->show();
}

void MainWindow::on_pushButtonZero_clicked() { digits_numbers(); }

void MainWindow::on_pushButtonOne_clicked() { digits_numbers(); }

void MainWindow::on_pushButtonTwo_clicked() { digits_numbers(); }

void MainWindow::on_pushButtonThree_clicked() { digits_numbers(); }

void MainWindow::on_pushButtonFour_clicked() { digits_numbers(); }

void MainWindow::on_pushButtonFive_clicked() { digits_numbers(); }

void MainWindow::on_pushButtonSix_clicked() { digits_numbers(); }

void MainWindow::on_pushButtonSeven_clicked() { digits_numbers(); }

void MainWindow::on_pushButtonEight_clicked() { digits_numbers(); }

void MainWindow::on_pushButtonNine_clicked() { digits_numbers(); }

void MainWindow::on_pushButtonPlus_clicked() { digits_numbers(); }

void MainWindow::on_pushButtonOpenBrace_clicked() { digits_numbers(); }

void MainWindow::on_pushButtonCloseBrace_clicked() { digits_numbers(); }

void MainWindow::on_pushButtonPow_clicked() { digits_numbers(); }

void MainWindow::on_pushButtonDivision_clicked() { digits_numbers(); }

void MainWindow::on_pushButtonMult_clicked() { digits_numbers(); }

void MainWindow::on_pushButtonAC_clicked() { clean_workspace(); }

void MainWindow::on_pushButtonX_clicked() { digits_numbers(); }

void MainWindow::on_pushButtonSqrt_clicked() { digits_numbers(); }

void MainWindow::on_pushButtonLn_clicked() { digits_numbers(); }

void MainWindow::on_pushButtonLog_clicked() { digits_numbers(); }

void MainWindow::on_pushButtonMod_clicked() { digits_numbers(); }

void MainWindow::on_pushButtonSin_clicked() { digits_numbers(); }

void MainWindow::on_pushButtonCos_clicked() { digits_numbers(); }

void MainWindow::on_pushButtonTan_clicked() { digits_numbers(); }

void MainWindow::on_pushButtonAsin_clicked() { digits_numbers(); }

void MainWindow::on_pushButtonAcos_clicked() { digits_numbers(); }

void MainWindow::on_pushButtonAtan_clicked() { digits_numbers(); }

void MainWindow::on_pushButtonClean_clicked() { clean_graf(); }

void MainWindow::on_pushButtonMinus_clicked() { digits_numbers(); }

void MainWindow::on_pushButtonDot_clicked() { digits_numbers(); }

void MainWindow::on_pushButtonBack_clicked() {
  if (!ui->exprsnStr->text().isEmpty()) {
    QString str = ui->exprsnStr->text();
    str.chop(1);
    ui->exprsnStr->setText(str);  // Удаление последнего символа
  }
}
