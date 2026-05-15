#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QStringList>
#include <QFile>
#include <QTextStream>

class Ticket
{
public:
    QString from;
    QString to;
    QString dateTime;
    QString place;
    QString baggage;
    QStringList services;

    Ticket(QString f, QString t, QString dt,
           QString p, QString b, QStringList s)
        : from(f), to(t), dateTime(dt),
        place(p), baggage(b), services(s) {}

    bool saveToFile(const QString &filename)
    {
        QFile file(filename);

        if(file.open(QIODevice::WriteOnly |
                      QIODevice::Append |
                      QIODevice::Text))
        {
            QTextStream out(&file);

            out << "Откуда: " << from << "\n";
            out << "Куда: " << to << "\n";
            out << "Дата и время: " << dateTime << "\n";
            out << "Место: " << place << "\n";
            out << "Доп. багаж: " << baggage << "\n";

            out << "Услуги: ";

            if(services.isEmpty())
                out << "Нет";
            else
                out << services.join(", ");

            out << "\n----------------------\n";

            file.close();
            return true;
        }

        return false;
    }
};

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonReset_clicked();

    void on_pushButtonSave_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
