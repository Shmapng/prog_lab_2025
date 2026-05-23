#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>

#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Пропуска");

    ui->tableWidget->setColumnCount(4);

    ui->tableWidget->setHorizontalHeaderLabels(
        {"Фамилия",
         "Имя",
         "Отчество/2 имя",
         "Дата"}
        );
}

MainWindow::~MainWindow()
{
    for(auto p : people)
        delete p;

    delete ui;
}

void MainWindow::on_pushButtonLoad_clicked()
{
    QString fileName =
        QFileDialog::getOpenFileName(
            this,
            "Выберите txt",
            "",
            "*.txt");

    if(fileName.isEmpty())
        return;

    QFile file(fileName);

    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(
            this,
            "Ошибка",
            "Файл не открылся");

        return;
    }

    QTextStream in(&file);

    ui->tableWidget->setRowCount(0);

    for(auto p : people)
        delete p;

    people.clear();

    while(!in.atEnd())
    {
        int code;

        in >> code;

        if(code == 0)
        {
            ParentPerson* p =
                new ParentPerson;

            in >> p->surname
                >> p->name
                >> p->father
                >> p->birth.day
                >> p->birth.month
                >> p->birth.year;

            people.push_back(p);

            int row =
                ui->tableWidget->rowCount();

            ui->tableWidget->insertRow(row);

            ui->tableWidget->setItem(
                row,0,
                new QTableWidgetItem(
                    p->surname));

            ui->tableWidget->setItem(
                row,1,
                new QTableWidgetItem(
                    p->name));

            ui->tableWidget->setItem(
                row,2,
                new QTableWidgetItem(
                    p->father));

            QString date =
                QString("%1.%2.%3")
                    .arg(p->birth.day,2,10,QChar('0'))
                    .arg(p->birth.month,2,10,QChar('0'))
                    .arg(p->birth.year);

            ui->tableWidget->setItem(
                row,3,
                new QTableWidgetItem(date));
        }

        else if(code == 1)
        {
            ChildPerson* p =
                new ChildPerson;

            in >> p->name
                >> p->secondName
                >> p->surname
                >> p->birth.day
                >> p->birth.month
                >> p->birth.year;

            people.push_back(p);

            int row =
                ui->tableWidget->rowCount();

            ui->tableWidget->insertRow(row);

            ui->tableWidget->setItem(
                row,0,
                new QTableWidgetItem(
                    p->surname));

            ui->tableWidget->setItem(
                row,1,
                new QTableWidgetItem(
                    p->name));

            ui->tableWidget->setItem(
                row,2,
                new QTableWidgetItem(
                    p->secondName));

            QString date =
                QString("%1.%2.%3")
                    .arg(p->birth.day,2,10,QChar('0'))
                    .arg(p->birth.month,2,10,QChar('0'))
                    .arg(p->birth.year);

            ui->tableWidget->setItem(
                row,3,
                new QTableWidgetItem(date));
        }
    }

    file.close();
}

void MainWindow::on_tableWidget_cellDoubleClicked(
    int row,
    int column)
{
    Q_UNUSED(column);

    QDialog dialog(this);

    dialog.setWindowTitle("Информация");

    dialog.resize(300,350);

    QVBoxLayout* layout =
        new QVBoxLayout(&dialog);

    // Картинка
    QLabel* imageLabel =
        new QLabel;

    QPixmap pix("person.png");

    imageLabel->setPixmap(
        pix.scaled(
            120,
            120,
            Qt::KeepAspectRatio));

    imageLabel->setAlignment(
        Qt::AlignCenter);

    layout->addWidget(imageLabel);

    // Текст
    QLabel* label =
        new QLabel(
            people[row]->Craft());

    label->setAlignment(
        Qt::AlignCenter);

    layout->addWidget(label);

    // Кнопки
    QPushButton* btnPrint =
        new QPushButton("Печать");

    QPushButton* btnCancel =
        new QPushButton("Отмена");

    layout->addWidget(btnPrint);
    layout->addWidget(btnCancel);

    // Отмена
    connect(btnCancel,
            &QPushButton::clicked,
            &dialog,
            &QDialog::close);

    // Печать
    connect(btnPrint,
            &QPushButton::clicked,
            [&]()
            {
                // удалить из таблицы
                ui->tableWidget->removeRow(row);

                // удалить объект
                delete people[row];

                people.remove(row);

                dialog.accept();
            });

    dialog.exec();
}
