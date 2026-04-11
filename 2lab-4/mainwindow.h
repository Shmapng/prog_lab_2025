#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QFile>
#include <QTextStream>

// Класс для хранения данных заявки
class BankRequest {
public:
    QString fio;
    QString dateTime;
    QString code;
    QStringList services;  // выбранные услуги

    BankRequest(QString f, QString dt, QString c, QStringList s)
        : fio(f), dateTime(dt), code(c), services(s) {}

    bool saveToFile(const QString &filename) {
        QFile file(filename);
        if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
            QTextStream out(&file);
            out << "ФИО клиента: " << fio << "\n";
            out << "Дата и время: " << dateTime << "\n";
            out << "Код услуги: " << code << "\n";
            out << "Выбранные услуги: " << (services.isEmpty() ? "Нет" : services.join(", ")) << "\n";
            out << "----------------------\n";
            file.close();
            return true;
        }
        return false;
    }
};

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
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
