#include "creditwindow.h"

#include "ui_creditwindow.h"

CreditWindow::CreditWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::CreditWindow) {
  ui->setupUi(this);

  ui->creditAmount->setValidator(new QDoubleValidator(1, 10e9, 0, this));
  ui->creditPeriod->setValidator(new QIntValidator(1, 100, this));
  ui->percentageRate->setValidator(new QDoubleValidator(1, 100, 3, this));
}

CreditWindow::~CreditWindow() { delete ui; }

void CreditWindow::on_pushButtonCalc_clicked() {
  int n;
  double monthlyPayment;
  double totalPayments = 0;
  double Q;  // остаток тела займа
  double m;

  char *creditAmountStr =
      (char *)ui->creditAmount->text().toLocal8Bit().constData();
  double creditAmount = strtod(creditAmountStr, NULL);
  char *creditPeriodStr =
      (char *)ui->creditPeriod->text().toLocal8Bit().constData();
  int creditPeriod = strtol(creditPeriodStr, NULL, 10);
  char *percentageRateStr =
      (char *)ui->percentageRate->text().toLocal8Bit().constData();
  int percentageRate = strtol(percentageRateStr, NULL, 10);

  if (ui->typePeriod->currentIndex() == 1) {
    n = creditPeriod * 12;
  } else {
    n = creditPeriod;
  }
  m = 1.0 * percentageRate / 12.0 / 100;

  if (ui->paymentsType->currentIndex() == 0) {
    double k = (pow((1 + m), n) * m) / (pow((1 + m), n) - 1);
    monthlyPayment = creditAmount * k;
    totalPayments = monthlyPayment * n;
    ui->labelMonthlyPayment->setText(QString("%1 ₽").arg(monthlyPayment));

  } else {
    double monthlyPaymentBody = 1.0 * creditAmount / n;
    Q = creditAmount;
    for (int i = 0; i < n; i++) {
      totalPayments += monthlyPaymentBody + (Q * m);
      Q -= monthlyPaymentBody;
    }
    ui->labelMonthlyPayment->setText(
        QString("%1 ... %2 ₽")
            .arg(monthlyPaymentBody + (creditAmount * m))
            .arg(monthlyPaymentBody + (monthlyPaymentBody * m)));
  }
  ui->labelTotalPayments->setText(QString("%1 ₽").arg(totalPayments));
  ui->labelOverPayment->setText(
      QString("%1 ₽").arg(totalPayments - creditAmount));

  //  ui->statusBar->showMessage("FAILED", 5000);
  // ui->statusBar->setStyleSheet("color: red;");success

  ui->statusBar->showMessage("SUCCESS", 5e3);
  ui->statusBar->setStyleSheet("color: green;");
}

void CreditWindow::on_pushButtonClean_clicked() {
  ui->labelMonthlyPayment->clear();
  ui->labelTotalPayments->clear();
  ui->labelOverPayment->clear();

  ui->creditAmount->clear();
  ui->creditPeriod->clear();
  ui->percentageRate->clear();
}
