#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qlabel.h"
#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
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
    void readSerial();
    void on_connecter_clicked();

    void on_disconnecter_clicked();



private:
    Ui::MainWindow *ui;
     QSerialPort *STM32F030R8T6;
    static const quint16 STM32F030R8T6_vendor_id = 1155;
    static const quint16 STM32F030R8T6_product_id = 14162;
    QString STM32F030R8T6_port_name;
    bool STM32F030R8T6_is_available;
};
#endif // MAINWINDOW_H
