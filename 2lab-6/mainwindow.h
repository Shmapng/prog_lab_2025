#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QJsonObject>
#include <QTableWidget>

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
    void on_pushButtonLoad_clicked();

private:
    Ui::MainWindow *ui;

    bool isValidFood(QJsonObject obj);

    void addToTable(QTableWidget *table,
                    QJsonObject obj);
};

#endif // MAINWINDOW_H
