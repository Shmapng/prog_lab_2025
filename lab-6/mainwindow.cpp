#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QTextStream>

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

// Загрузка из txt
void MainWindow::on_pushButtonTxt_clicked()
{
    QFile file("food.txt");

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this,
                             "Ошибка",
                             "Не удалось открыть food.txt");

        return;
    }

    QTextStream in(&file);

    QString name = in.readLine();
    QString description = in.readLine();
    QString hunger = in.readLine();
    QString price = in.readLine();
    QString weight = in.readLine();

    file.close();

    ui->lineEditName->setText(name);
    ui->lineEditDescription->setText(description);
    ui->lineEditHunger->setText(hunger);
    ui->lineEditPrice->setText(price);
    ui->lineEditWeight->setText(weight);
}

// Сохранение json
void MainWindow::on_pushButtonSave_clicked()
{
    QString name = ui->lineEditName->text();
    QString description = ui->lineEditDescription->text();

    int hunger = ui->lineEditHunger->text().toInt();
    int price = ui->lineEditPrice->text().toInt();
    int weight = ui->lineEditWeight->text().toInt();

    // Проверка
    if(name.isEmpty() ||
        description.isEmpty())
    {
        QMessageBox::warning(this,
                             "Ошибка",
                             "Заполните все поля");

        return;
    }

    if(hunger <= 0 ||
        price <= 0 ||
        weight <= 0)
    {
        QMessageBox::warning(this,
                             "Ошибка",
                             "Числа должны быть больше 0");

        return;
    }

    // Создаем объект
    QJsonObject obj;

    obj["name"] = name;
    obj["description"] = description;
    obj["hunger"] = hunger;
    obj["price"] = price;
    obj["weight"] = weight;

    QFile file("food.json");

    QJsonArray array;

    // Читаем старый json
    if(file.exists())
    {
        if(file.open(QIODevice::ReadOnly))
        {
            QByteArray data = file.readAll();

            QJsonDocument oldDoc =
                QJsonDocument::fromJson(data);

            if(oldDoc.isArray())
            {
                array = oldDoc.array();
            }

            file.close();
        }
    }

    // Добавляем новый объект
    array.append(obj);

    // Записываем обратно
    if(file.open(QIODevice::WriteOnly))
    {
        QJsonDocument doc(array);

        file.write(doc.toJson());

        file.close();

        QMessageBox::information(this,
                                 "Успех",
                                 "JSON сохранен");
    }
    else
    {
        QMessageBox::warning(this,
                             "Ошибка",
                             "Ошибка записи файла");
    }
}
