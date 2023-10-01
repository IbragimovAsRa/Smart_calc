#ifndef DEPOSITWINDOW_H
#define DEPOSITWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QPlainTextEdit>
#include <QScrollArea>
#include <QScrollBar>
#include <QStandardItemModel>
#include <QTableView>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QWidget>

namespace Ui {
class DepositWindow;
}

class DepositWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit DepositWindow(QWidget *parent = nullptr);
  ~DepositWindow();

 private slots:
  void on_pushButtonAddDeposit_clicked();

  void on_pushButtonCalc_clicked();

  void on_isInsertDeposit_stateChanged(int arg1);

  void on_checkBoxCurrentDate_stateChanged(int arg1);

  void on_amountDeposit_editingFinished();

  void on_periodDeposit_editingFinished();

  void on_percentRate_editingFinished();

  void on_percentCapitalization_stateChanged(int arg1);

  void on_dateStart_editingFinished();

  void on_periodPayments_currentIndexChanged(int index);

  void on_pushButtonMoveup_clicked();

  // void on_pushButtonInsDepClean_clicked();

  void on_pushButton_clicked();

  void on_pushButtonInsDepAdd_clicked();

  void on_pushButtonInsDepClean_clicked();

  void on_periodDepositFormat_currentIndexChanged(int index);

  void on_pushButtonTakeDepAdd_clicked();

  void on_pushButtonTakeDepClean_clicked();

  void on_isTakeDeposit_stateChanged(int arg1);

  void on_isTax_stateChanged(int arg1);

 private:
  Ui::DepositWindow *ui;

  bool percentCapitalization;
  int periodDeposit;
  double amountDeposit;
  double percentRate;
  int periodPayments;
  int periodDepositFormat;
  QDate *dateStart;
  QDate *dateFinish;
  double koefPercentRate;
  double accruedAmount;
  double amountTax;

  double getAmountDeposit();
  int getPeriodDeposit();
  int getPeriodDepositFormat();
  int getPeriodPayments();
  double getPercentRate();
  bool getPercentCapitalization();

  void configureDateStart();
  void configureDateFinish();

  void makeLog(QString str);

  void insertTable_1();
  void cleanTable_1();

  void insertTable_2();
  void cleanTable_2();

  void insertTable_3(QStringList strList);
  void cleanTable_3();

  QDate increaseDate(QDate curDate, int format, int count);

  void updatePeriodDepositFormat();
  void updateState();

  void checkAdding(double *dep, double *tmpAccrInter, QDate *prevPay,
                   QDate tmpDate);
  void taxHandler(double accrInter);
};

#endif  // DEPOSITWINDOW_H
