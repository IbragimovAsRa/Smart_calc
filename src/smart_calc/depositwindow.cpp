#include "depositwindow.h"

#include "ui_depositwindow.h"

DepositWindow::DepositWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::DepositWindow) {
  ui->setupUi(this);

  // инициализация
  dateStart = new QDate();
  dateFinish = new QDate();

  percentCapitalization = getPercentCapitalization();
  periodDeposit = getPeriodDeposit();
  amountDeposit = getAmountDeposit();
  percentRate = getPercentRate();
  periodPayments = ui->periodPayments->currentIndex();
  periodDepositFormat = getPeriodDepositFormat();

  // Начальные настройки
  ui->label_14->setEnabled(false);
  ui->label_10->setEnabled(false);
  ui->amountTax->setEnabled(false);
  ui->tax->setEnabled(false);

  ui->pushButtonInsDepClean->setEnabled(false);
  ui->pushButtonInsDepAdd->setEnabled(false);

  ui->comboBoxInsDepPeriod->setEnabled(false);
  ui->dateEditInsDep->setEnabled(false);
  ui->spinBoxInsDepAmount->setEnabled(false);

  ui->pushButtonTakeDepClean->setEnabled(false);
  ui->pushButtonTakeDepAdd->setEnabled(false);

  ui->comboBoxTakeDepPeriod->setEnabled(false);
  ui->dateEditTakeDep->setEnabled(false);
  ui->spinBoxTakeDepAmount->setEnabled(false);

  ui->dateStart->setDate(QDate::currentDate());
  ui->dateStart->setReadOnly(true);
  ui->checkBoxCurrentDate->setChecked(true);
  *dateStart = ui->dateStart->date();
  configureDateFinish();

  // Настройка таблицы 1.
  ui->tableWidget_1->setVisible(false);
  ui->tableWidget_1->setColumnCount(3);
  ui->tableWidget_1->horizontalHeader()->setVisible(false);
  ui->tableWidget_1->verticalHeader()->setVisible(false);
  ui->tableWidget_1->setColumnWidth(0, 130);
  ui->tableWidget_1->setColumnWidth(1, 110);
  ui->tableWidget_1->horizontalHeader()->setSectionResizeMode(
      2, QHeaderView::Stretch);

  // Настройка таблицы 2.
  ui->tableWidget_2->setVisible(false);
  ui->tableWidget_2->setColumnCount(3);
  ui->tableWidget_2->horizontalHeader()->setVisible(false);
  ui->tableWidget_2->verticalHeader()->setVisible(false);
  ui->tableWidget_2->setColumnWidth(0, 130);
  ui->tableWidget_2->setColumnWidth(1, 110);
  ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(
      2, QHeaderView::Stretch);

  // Настройка таблицы 3.
  ui->tableWidget_3->setColumnCount(4);
  ui->tableWidget_3->setHorizontalHeaderLabels(
      {"Дата", "Начислено %, ₽", "Вклад пополнен, ₽", "Остаток на вкладе, ₽"});
  ui->tableWidget_3->setShowGrid(true);
  ui->tableWidget_3->verticalHeader()->setVisible(false);
  ui->tableWidget_3->setEditTriggers(QAbstractItemView::NoEditTriggers);

  for (int col = 1; col < 4; ++col) {
    ui->tableWidget_3->horizontalHeader()->setSectionResizeMode(
        col, QHeaderView::Stretch);
  }
}

DepositWindow::~DepositWindow() {
  delete ui;
  delete dateStart;
}

void DepositWindow::insertTable_3(QStringList strList) {
  QTableWidgetItem* item_0 = new QTableWidgetItem(strList.at(0));
  QTableWidgetItem* item_1 = new QTableWidgetItem(strList.at(1));
  QTableWidgetItem* item_2 = new QTableWidgetItem(strList.at(2));
  QTableWidgetItem* item_3 = new QTableWidgetItem(strList.at(3));

  int rowCount = ui->tableWidget_3->rowCount();

  ui->tableWidget_3->insertRow(rowCount);

  ui->tableWidget_3->setItem(rowCount, 0, item_0);
  ui->tableWidget_3->setItem(rowCount, 1, item_1);
  ui->tableWidget_3->setItem(rowCount, 2, item_2);
  ui->tableWidget_3->setItem(rowCount, 3, item_3);
}

void DepositWindow::cleanTable_3() {
  ui->tableWidget_3->clearContents();
  ui->tableWidget_3->setRowCount(0);
}

void DepositWindow::on_pushButtonAddDeposit_clicked() {}
double DepositWindow::getAmountDeposit() { return ui->amountDeposit->value(); }

int DepositWindow::getPeriodDeposit() { return ui->periodDeposit->value(); }

double DepositWindow::getPercentRate() {
  double res = ui->percentRate->value() / 100;
  koefPercentRate = res / 365;
  return res;
}

bool DepositWindow::getPercentCapitalization() {
  return ui->percentCapitalization->checkState();
}
int DepositWindow::getPeriodDepositFormat() {
  return ui->periodDepositFormat->currentIndex();
}

QDate DepositWindow::increaseDate(QDate curDate, int format, int count) {
  if (format == 0) {
    curDate = curDate.addMonths(1 * count);  // увеличить на месяц
  } else if (format == 1) {
    curDate = curDate.addDays(1 * count);  // увеличить на день
  } else if (format == 2) {
    curDate = curDate.addDays(7 * count);  // увеличить на неделю
  } else if (format == 3) {
    curDate = curDate.addMonths(3 * count);  // увеличить на квартал
  } else if (format == 4) {
    curDate = curDate.addMonths(6 * count);  // увеличить на полгода
  } else if (format == 5) {
    curDate = curDate.addMonths(12 * count);  // увеличить на год
  }
  return curDate;
}

void DepositWindow::on_pushButtonCalc_clicked() {
  cleanTable_3();
  QDate tmpDate = *dateStart;
  QDate prevPay = *dateStart;

  double dep = amountDeposit;
  double accrInter = 0;
  double tmpAccrInter = 0;

  while (tmpDate < *dateFinish) {
    accrInter += dep * koefPercentRate;
    tmpAccrInter += dep * koefPercentRate;
    tmpDate = tmpDate.addDays(1);
    checkAdding(&dep, &tmpAccrInter, &prevPay, tmpDate);
  }
  taxHandler(accrInter);
  ui->accruedAmount->setText(QString::number(accrInter, 'f', 2).append(" ₽"));
  ui->amountDepositEnd->setText(
      QString::number(amountDeposit + accrInter, 'f', 2).append(" ₽"));
  ui->amountTax->setText(QString::number(amountTax, 'f', 2).append(" ₽"));
}

void DepositWindow::taxHandler(double accrInter) {
  double k1 = 0.045;  // ставка центрального банка
  double k2 = ui->tax->value();  // налоговая ставка

  int daysDif = dateStart->daysTo(*dateFinish);
  double k11 = k1 * (daysDif / 365.0);

  if (ui->isTax->checkState()) {
    if ((accrInter) > ((amountDeposit) * (k11))) {
      amountTax =
          ((amountDeposit + accrInter) - ((amountDeposit) * (1 + k11))) *
          (k2 / 100.0);
    } else {
      amountTax = 0;
    }
  } else {
    amountTax = 0;
  }
}

void DepositWindow::checkAdding(double* dep, double* tmpAccrInter,
                                QDate* prevPay, QDate tmpDate) {
  // обработка капитализации
  bool flag = false;

  switch (periodPayments) {
    case 0:  // месяц
      if (prevPay->addMonths(1) == tmpDate) {
        *prevPay = prevPay->addMonths(1);
        flag = true;
      }
      break;
    case 1:  // день
      flag = true;
      break;
    case 2:  // неделя
      if (prevPay->addDays(7) == tmpDate) {
        *prevPay = prevPay->addDays(7);
        flag = true;
      }
      break;
    case 3:  // квартал
      if (prevPay->addMonths(3) == tmpDate) {
        *prevPay = prevPay->addMonths(3);
        flag = true;
      }
      break;
    case 4:  // полгода
      if (prevPay->addMonths(6) == tmpDate) {
        *prevPay = prevPay->addMonths(6);
        flag = true;
      }
      break;
    case 5:  // год
      if (prevPay->addYears(1) == tmpDate) {
        *prevPay = prevPay->addYears(1);
        flag = true;
      }
      break;
  }
  if (flag) {
    if (percentCapitalization) {
      *dep += *tmpAccrInter;
      insertTable_3({tmpDate.toString("dd.MM.yyyy"),
                     QString::number(*tmpAccrInter, 'f', 2),
                     QString::number(*tmpAccrInter, 'f', 2),
                     QString::number(*dep, 'f', 2)});
    } else {
      insertTable_3({tmpDate.toString("dd.MM.yyyy"),
                     QString::number(*tmpAccrInter, 'f', 2), "0",
                     QString::number(*dep, 'f', 2)});
    }
    *tmpAccrInter = 0;
  }

  // обработка зачислений
  int rowCount = ui->tableWidget_1->rowCount();

  if (ui->isInsertDeposit->isEnabled() && rowCount > 0) {
    for (int i = 0; i < rowCount; i++) {
      QWidget* cellWidget = ui->tableWidget_1->cellWidget(i, 1);
      if (cellWidget) {
        QDateEdit* dateEdit = qobject_cast<QDateEdit*>(cellWidget);
        if (dateEdit) {
          QDate date = dateEdit->date();
          if (date == tmpDate) {
            cellWidget = ui->tableWidget_1->cellWidget(i, 2);
            QDoubleSpinBox* spinBox = qobject_cast<QDoubleSpinBox*>(cellWidget);
            *dep = *dep + spinBox->value();
            insertTable_3({tmpDate.toString("dd.MM.yyyy"), " ",
                           QString::number(spinBox->value(), 'f', 2),
                           QString::number(*dep, 'f', 2)});
          }
        }
      }
    }
  }
  // обработка снятий

  int rowCount_2 = ui->tableWidget_2->rowCount();

  if (ui->isTakeDeposit->isEnabled() && rowCount_2 > 0) {
    for (int i = 0; i < rowCount_2; i++) {
      QWidget* cellWidget_2 = ui->tableWidget_2->cellWidget(i, 1);
      if (cellWidget_2) {
        QDateEdit* dateEdit_2 = qobject_cast<QDateEdit*>(cellWidget_2);
        if (dateEdit_2) {
          QDate date_2 = dateEdit_2->date();
          if (date_2 == tmpDate) {
            cellWidget_2 = ui->tableWidget_2->cellWidget(i, 2);
            QDoubleSpinBox* spinBox_2 =
                qobject_cast<QDoubleSpinBox*>(cellWidget_2);
            *dep = *dep - spinBox_2->value();
            insertTable_3({tmpDate.toString("dd.MM.yyyy"), " ",
                           QString::number((-1) * spinBox_2->value(), 'f', 2),
                           QString::number(*dep, 'f', 2)});
          }
        }
      }
    }
  }
}

void DepositWindow::configureDateFinish() {
  if (periodDepositFormat == 0) {
    *dateFinish = dateStart->addYears(periodDeposit);
  } else if (periodDepositFormat == 1) {
    *dateFinish = dateStart->addMonths(periodDeposit);
  } else {
    *dateFinish = dateStart->addDays(periodDeposit);
  }
}

void DepositWindow::on_isInsertDeposit_stateChanged(int arg1) {
  if (arg1 == 2) {
    ui->pushButtonInsDepClean->setEnabled(true);
    ui->pushButtonInsDepAdd->setEnabled(true);
    if (ui->tableWidget_1->rowCount() != 0) {
      ui->tableWidget_1->setVisible(true);
      ui->tableWidget_1->setEnabled(true);
    }

    ui->comboBoxInsDepPeriod->setEnabled(true);
    ui->spinBoxInsDepAmount->setEnabled(true);
    ui->dateEditInsDep->setEnabled(true);
  } else {
    ui->pushButtonInsDepClean->setEnabled(false);
    ui->pushButtonInsDepAdd->setEnabled(false);

    if (ui->tableWidget_1->rowCount() == 0) {
      ui->tableWidget_1->setVisible(false);
    } else {
      ui->tableWidget_1->setEnabled(false);
    }

    ui->comboBoxInsDepPeriod->setEnabled(false);
    ui->spinBoxInsDepAmount->setEnabled(false);
    ui->dateEditInsDep->setEnabled(false);
  }
}

void DepositWindow::on_checkBoxCurrentDate_stateChanged(int arg1) {
  if (arg1 == 0) {
    ui->dateStart->setReadOnly(false);
  } else {
    ui->dateStart->setDate(QDate::currentDate());
    ui->dateStart->setReadOnly(true);
    ui->checkBoxCurrentDate->setChecked(true);
  }
}

void DepositWindow::on_amountDeposit_editingFinished() {
  amountDeposit = getAmountDeposit();
}

void DepositWindow::on_periodDeposit_editingFinished() {
  periodDeposit = getPeriodDeposit();
  *dateStart = ui->dateStart->date();
  configureDateFinish();
}

void DepositWindow::on_percentRate_editingFinished() {
  percentRate = getPercentRate();
}

void DepositWindow::on_percentCapitalization_stateChanged(int arg1) {
  percentCapitalization = getPercentCapitalization();
}

void DepositWindow::on_dateStart_editingFinished() {
  *dateStart = ui->dateStart->date();
  configureDateFinish();
}

void DepositWindow::on_periodPayments_currentIndexChanged(int index) {
  periodPayments = ui->periodPayments->currentIndex();
}

void DepositWindow::on_pushButtonMoveup_clicked() {
  // ui->scrollArea1->move();
  // ui->scrollArea1->pos();
}

void DepositWindow::on_pushButton_clicked() {
  cleanTable_3();
  ui->amountTax->setText(QString::number(0, 'f', 2).append(" ₽"));

  ui->accruedAmount->setText(QString::number(0, 'f', 2).append(" ₽"));

  ui->amountDepositEnd->setText(QString::number(0, 'f', 2).append(" ₽"));
}

void DepositWindow::on_pushButtonInsDepAdd_clicked() {
  insertTable_1();
  ui->tableWidget_1->setVisible(true);
  ui->tableWidget_1->setEnabled(true);
}

void DepositWindow::insertTable_1() {
  int rowCount = ui->tableWidget_1->rowCount();

  ui->tableWidget_1->insertRow(rowCount);

  QComboBox* comboBox = new QComboBox();
  QDateEdit* dateEdit = new QDateEdit(ui->dateEditInsDep->date());
  QDoubleSpinBox* spinBox = new QDoubleSpinBox();

  spinBox->setMaximum(1000000000);
  spinBox->setValue(ui->spinBoxInsDepAmount->value());
  QStringList itemList;
  int itemCount = ui->comboBoxInsDepPeriod->count();
  for (int i = 0; i < itemCount; ++i) {
    itemList.append(ui->comboBoxInsDepPeriod->itemText(i));
  }
  comboBox->addItems(itemList);
  comboBox->setCurrentIndex(ui->comboBoxInsDepPeriod->currentIndex());

  ui->tableWidget_1->setCellWidget(rowCount, 0, comboBox);
  ui->tableWidget_1->setCellWidget(rowCount, 1, dateEdit);
  ui->tableWidget_1->setCellWidget(rowCount, 2, spinBox);
}

void DepositWindow::on_pushButtonInsDepClean_clicked() {
  ui->tableWidget_1->clearContents();
  ui->tableWidget_1->setRowCount(0);

  ui->tableWidget_1->setEnabled(false);
  ui->tableWidget_1->setVisible(false);
}

void DepositWindow::on_periodDepositFormat_currentIndexChanged(int index) {
  periodDepositFormat = getPeriodDepositFormat();
  *dateStart = ui->dateStart->date();
  configureDateFinish();
}

void DepositWindow::on_pushButtonTakeDepAdd_clicked() {
  insertTable_2();

  ui->tableWidget_2->setVisible(true);
  ui->tableWidget_2->setEnabled(true);
}
void DepositWindow::insertTable_2() {
  int rowCount = ui->tableWidget_2->rowCount();

  ui->tableWidget_2->insertRow(rowCount);

  QComboBox* comboBox = new QComboBox();
  QDateEdit* dateEdit = new QDateEdit(ui->dateEditTakeDep->date());
  QDoubleSpinBox* spinBox = new QDoubleSpinBox();

  spinBox->setMaximum(1000000000);
  spinBox->setValue(ui->spinBoxTakeDepAmount->value());

  QStringList itemList;
  int itemCount = ui->comboBoxTakeDepPeriod->count();
  for (int i = 0; i < itemCount; ++i) {
    itemList.append(ui->comboBoxTakeDepPeriod->itemText(i));
  }
  comboBox->addItems(itemList);
  comboBox->setCurrentIndex(ui->comboBoxTakeDepPeriod->currentIndex());

  ui->tableWidget_2->setCellWidget(rowCount, 0, comboBox);
  ui->tableWidget_2->setCellWidget(rowCount, 1, dateEdit);
  ui->tableWidget_2->setCellWidget(rowCount, 2, spinBox);
}

void DepositWindow::cleanTable_2() {
  ui->tableWidget_2->clearContents();
  ui->tableWidget_2->setRowCount(0);

  ui->tableWidget_2->setEnabled(false);
  ui->tableWidget_2->setVisible(false);
}

void DepositWindow::on_pushButtonTakeDepClean_clicked() { cleanTable_2(); }

void DepositWindow::on_isTakeDeposit_stateChanged(int arg1) {
  if (arg1 == 2) {
    ui->pushButtonTakeDepClean->setEnabled(true);
    ui->pushButtonTakeDepAdd->setEnabled(true);
    if (ui->tableWidget_2->rowCount() != 0) {
      ui->tableWidget_2->setVisible(true);
      ui->tableWidget_2->setEnabled(true);
    }

    ui->comboBoxTakeDepPeriod->setEnabled(true);
    ui->spinBoxTakeDepAmount->setEnabled(true);
    ui->dateEditTakeDep->setEnabled(true);
  } else {
    ui->pushButtonTakeDepClean->setEnabled(false);
    ui->pushButtonTakeDepAdd->setEnabled(false);

    if (ui->tableWidget_2->rowCount() == 0) {
      ui->tableWidget_2->setVisible(false);
    } else {
      ui->tableWidget_2->setEnabled(false);
    }

    ui->comboBoxTakeDepPeriod->setEnabled(false);
    ui->spinBoxTakeDepAmount->setEnabled(false);
    ui->dateEditTakeDep->setEnabled(false);
  }
}

void DepositWindow::on_isTax_stateChanged(int arg1) {
  if (arg1 == 2) {
    ui->label_10->setEnabled(true);
    ui->label_14->setEnabled(true);
    ui->amountTax->setEnabled(true);
    ui->tax->setEnabled(true);

  } else {
    ui->label_14->setEnabled(false);
    ui->label_10->setEnabled(false);
    ui->amountTax->setEnabled(false);
    ui->tax->setEnabled(false);
  }
}
