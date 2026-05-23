#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHeaderView>

#include <QFileDialog>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QHeaderView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tableWidgetGood->setColumnCount(5);
    ui->tableWidgetGood->setHorizontalHeaderLabels(
        {"Название", "Описание", "Голод", "Цена", "Вес"}
        );

    ui->tableWidgetBad->setColumnCount(5);
    ui->tableWidgetBad->setHorizontalHeaderLabels(
        {"Название", "Описание", "Голод", "Цена", "Вес"}
        );

    ui->tableWidgetGood->horizontalHeader()
        ->setSectionResizeMode(QHeaderView::Stretch);

    ui->tableWidgetBad->horizontalHeader()
        ->setSectionResizeMode(QHeaderView::Stretch);

    ui->tableWidgetGood->horizontalHeader()
        ->setSectionsMovable(false);

    ui->tableWidgetBad->horizontalHeader()
        ->setSectionsMovable(false);

    ui->tableWidgetGood->setHorizontalScrollBarPolicy(
        Qt::ScrollBarAlwaysOff);

    ui->tableWidgetBad->setHorizontalScrollBarPolicy(
        Qt::ScrollBarAlwaysOff);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::isValidFood(QJsonObject obj)
{
    QString name = obj["name"].toString();
    QString description = obj["description"].toString();

    int hunger = obj["hunger"].toInt();
    int price = obj["price"].toInt();
    int weight = obj["weight"].toInt();

    if(name.isEmpty())
        return false;

    if(description.isEmpty())
        return false;

    if(hunger <= 0)
        return false;

    if(price <= 0)
        return false;

    if(weight <= 0)
        return false;

    return true;
}

void MainWindow::addToTable(QTableWidget *table,
                            QJsonObject obj)
{
    int row = table->rowCount();

    table->insertRow(row);

    table->setItem(row, 0,
                   new QTableWidgetItem(
                       obj["name"].toString()));

    table->setItem(row, 1,
                   new QTableWidgetItem(
                       obj["description"].toString()));

    table->setItem(row, 2,
                   new QTableWidgetItem(
                       QString::number(
                           obj["hunger"].toInt())));

    table->setItem(row, 3,
                   new QTableWidgetItem(
                       QString::number(
                           obj["price"].toInt())));

    table->setItem(row, 4,
                   new QTableWidgetItem(
                       QString::number(
                           obj["weight"].toInt())));
}

void MainWindow::on_pushButtonLoad_clicked()
{
    QString fileName =
        QFileDialog::getOpenFileName(
            this,
            "Выбрать json",
            "",
            "*.json");

    if(fileName.isEmpty())
        return;

    QFile file(fileName);

    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(
            this,
            "Ошибка",
            "Не удалось открыть файл");

        return;
    }

    QByteArray data = file.readAll();

    file.close();

    QJsonDocument doc =
        QJsonDocument::fromJson(data);

    QJsonArray arr = doc.array();

    ui->tableWidgetGood->setRowCount(0);
    ui->tableWidgetBad->setRowCount(0);

    QJsonArray brokenArray;

    for(auto value : arr)
    {
        QJsonObject obj = value.toObject();

        if(isValidFood(obj))
        {
            addToTable(ui->tableWidgetGood,
                       obj);
        }
        else
        {
            addToTable(ui->tableWidgetBad,
                       obj);

            brokenArray.append(obj);
        }
    }

    QFile brokenFile("broken.json");

    if(brokenFile.open(QIODevice::WriteOnly))
    {
        QJsonDocument brokenDoc(
            brokenArray);

        brokenFile.write(
            brokenDoc.toJson());

        brokenFile.close();
    }
}
