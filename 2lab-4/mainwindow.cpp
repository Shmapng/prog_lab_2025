#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QMessageBox>
#include <QRegularExpression>
#include <QDate>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Сброс
void MainWindow::on_pushButtonReset_clicked()
{
    ui->lineEditFrom->clear();
    ui->lineEditTo->clear();
    ui->lineEditDateTime->clear();
    ui->lineEditPlace->clear();

    ui->radioYes->setAutoExclusive(false);
    ui->radioNo->setAutoExclusive(false);

    ui->radioYes->setChecked(false);
    ui->radioNo->setChecked(false);

    ui->radioYes->setAutoExclusive(true);
    ui->radioNo->setAutoExclusive(true);

    ui->checkFood->setChecked(false);
    ui->checkTaxi->setChecked(false);
    ui->checkVip->setChecked(false);
}

// Сохранение
void MainWindow::on_pushButtonSave_clicked()
{
    QString from = ui->lineEditFrom->text().trimmed();
    QString to = ui->lineEditTo->text().trimmed();
    QString dateTime = ui->lineEditDateTime->text().trimmed();
    QString place = ui->lineEditPlace->text().trimmed();

    // Проверка обязательности
    if(from.isEmpty() ||
        to.isEmpty() ||
        dateTime.isEmpty() ||
        place.isEmpty())
    {
        QMessageBox::warning(this,
                             "Ошибка",
                             "Все поля кроме услуг обязательны!");

        return;
    }

    // 1. Анг + рус, первая буква заглавная
    QRegularExpression regCity(
        "^([A-ZА-ЯЁ][a-zа-яё]+)"
        "( [A-ZА-ЯЁ][a-zа-яё]+)*$"
        );

    if(!regCity.match(from).hasMatch())
    {
        QMessageBox::warning(this,
                             "Ошибка",
                             "Поле 'Откуда' заполнено неверно!");

        return;
    }

    if(!regCity.match(to).hasMatch())
    {
        QMessageBox::warning(this,
                             "Ошибка",
                             "Поле 'Куда' заполнено неверно!");

        return;
    }

    // 2. Дата и время
    QRegularExpression regDate(
        "^(\\d{2})\\.(\\d{2})\\.(\\d{4})/(\\d{2}):(\\d{2})$"
        );

    QRegularExpressionMatch match =
        regDate.match(dateTime);

    if(!match.hasMatch())
    {
        QMessageBox::warning(this,
                             "Ошибка",
                             "Дата должна быть:\n"
                             "дд.мм.гггг/чч:мм");

        return;
    }

    int day = match.captured(1).toInt();
    int month = match.captured(2).toInt();
    int year = match.captured(3).toInt();

    int hour = match.captured(4).toInt();
    int minute = match.captured(5).toInt();

    QDate date(year, month, day);

    if(!date.isValid())
    {
        QMessageBox::warning(this,
                             "Ошибка",
                             "Некорректная дата!");

        return;
    }

    if(hour < 0 || hour > 23 ||
        minute < 0 || minute > 59)
    {
        QMessageBox::warning(this,
                             "Ошибка",
                             "Некорректное время!");

        return;
    }

    // 3. Место
        QRegularExpression regPlace(
            "^([1-5][A-D]|([6-9]|[1-2][0-9]|30)[A-F])$"
            );



    if(!regPlace.match(place).hasMatch())
    {
        QMessageBox::warning(this,
                             "Ошибка",
                             "Место должно быть:\n"
                             "1A-6F");

        return;
    }

    // Багаж
    QString baggage;

    if(ui->radioYes->isChecked())
        baggage = "Да";
    else if(ui->radioNo->isChecked())
        baggage = "Нет";
    else
    {
        QMessageBox::warning(this,
                             "Ошибка",
                             "Выберите доп. багаж!");

        return;
    }

    // Услуги
    QStringList services;

    if(ui->checkFood->isChecked())
        services << "Питание";

    if(ui->checkTaxi->isChecked())
        services << "Такси";

    if(ui->checkVip->isChecked())
        services << "VIP зал";

    // Создание объекта
    Ticket ticket(from,
                  to,
                  dateTime,
                  place,
                  baggage,
                  services);

    // Сохранение
    if(ticket.saveToFile("result.txt"))
    {
        QMessageBox::information(this,
                                 "Успех",
                                 "Данные сохранены!");
    }
    else
    {
        QMessageBox::critical(this,
                              "Ошибка",
                              "Ошибка записи файла!");
    }
