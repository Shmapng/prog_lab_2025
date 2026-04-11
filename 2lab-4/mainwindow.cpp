#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QRegularExpression>
#include <QDate>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Сброс всех полей
void MainWindow::on_pushButtonReset_clicked()
{
    ui->lineEditFIO->clear();
    ui->lineEditDateTime->clear();
    ui->lineEditCode->clear();
    ui->checkCredit->setChecked(false);
    ui->checkDeposit->setChecked(false);
    ui->checkInsurance->setChecked(false);
}

// Сохранение с проверками
void MainWindow::on_pushButtonSave_clicked()
{
    QString fio = ui->lineEditFIO->text().trimmed();
    QString dateTime = ui->lineEditDateTime->text().trimmed();
    QString code = ui->lineEditCode->text().trimmed();

    // Проверка обязательности (все кроме услуг)
    if (fio.isEmpty() || dateTime.isEmpty() || code.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Все поля, кроме услуг, обязательны для заполнения!");
        return;
    }

    // 1. ФИО: анг+рус, каждое слово с заглавной буквы
    QRegularExpression regFIO(
        "^([A-ZА-ЯЁ][a-zа-яё]+)( [A-ZА-ЯЁ][a-zа-яё]+)*$"
    );
    if (!regFIO.match(fio).hasMatch()) {
        QMessageBox::warning(this, "Ошибка",
            "ФИО должно содержать только английские или русские буквы.\n"
            "Каждое слово начинается с заглавной, остальные строчные.\n"
            "Пример: Иван Иванов или John Smith");
        return;
    }

    // 2. Дата и время: дд.мм.гггг/чч:мм
    QRegularExpression regDateTime(
        "^(\\d{2})\\.(\\d{2})\\.(\\d{4})/(\\d{2}):(\\d{2})$"
    );
    QRegularExpressionMatch matchDT = regDateTime.match(dateTime);
    if (!matchDT.hasMatch()) {
        QMessageBox::warning(this, "Ошибка",
            "Дата и время должны быть в формате: дд.мм.гггг/чч:мм\n"
            "Пример: 15.04.2025/14:30");
        return;
    }
    // Дополнительная проверка корректности даты/времени
    int day = matchDT.captured(1).toInt();
    int month = matchDT.captured(2).toInt();
    int year = matchDT.captured(3).toInt();
    int hour = matchDT.captured(4).toInt();
    int minute = matchDT.captured(5).toInt();

    QDate date(year, month, day);
    if (!date.isValid() || date.year() != year || date.month() != month || date.day() != day) {
        QMessageBox::warning(this, "Ошибка", "Некорректная дата!");
        return;
    }
    if (hour < 0 || hour > 23 || minute < 0 || minute > 59) {
        QMessageBox::warning(this, "Ошибка", "Некорректное время! Часы 0-23, минуты 0-59.");
        return;
    }

    // 3. Код: 1-5 символов A-D, затем 6-30 символов A-F
    QRegularExpression regCode("^[A-D]{1,5}[A-F]{6,30}$");
    if (!regCode.match(code).hasMatch()) {
        QMessageBox::warning(this, "Ошибка",
            "Код услуги: сначала 1-5 заглавных букв A-D, затем 6-30 заглавных букв A-F.\n"
            "Пример: ABDFFFFFF");
        return;
    }

    // Сбор выбранных услуг (необязательные)
    QStringList services;
    if (ui->checkCredit->isChecked())   services << "Кредитование";
    if (ui->checkDeposit->isChecked())  services << "Вклад";
    if (ui->checkInsurance->isChecked()) services << "Страхование";

    // Создание объекта и сохранение
    BankRequest request(fio, dateTime, code, services);
    if (request.saveToFile("result.txt")) {
        QMessageBox::information(this, "Успех", "Данные сохранены в result.txt");
    } else {
        QMessageBox::critical(this, "Ошибка", "Не удалось записать файл!");
    }
}
