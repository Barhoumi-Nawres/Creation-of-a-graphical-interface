#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>
#include <QtWidgets>
#include <QString>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    STM32F030R8T6_is_available = false;
    STM32F030R8T6_port_name = "";
    STM32F030R8T6 = new QSerialPort;
    // Masquer l'image par défaut
    ui->imageLabel->setVisible(false);


   /* qDebug() << "Number of available ports: " << QSerialPortInfo::availablePorts().length();
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
        qDebug() << "Has vendor ID: " << serialPortInfo.hasVendorIdentifier();
        if(serialPortInfo.hasVendorIdentifier()){
            qDebug() << "Vendor ID: " << serialPortInfo.vendorIdentifier();
        }
        qDebug() << "Has Product ID: " << serialPortInfo.hasProductIdentifier();
        if(serialPortInfo.hasProductIdentifier()){
            qDebug() << "Product ID: " << serialPortInfo.productIdentifier();
        }
    }*/

    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
        if(serialPortInfo.hasVendorIdentifier() && serialPortInfo.hasProductIdentifier()){
            if(serialPortInfo.vendorIdentifier() == STM32F030R8T6_vendor_id){
                if(serialPortInfo.productIdentifier() == STM32F030R8T6_product_id){
                    STM32F030R8T6_port_name = serialPortInfo.portName();
                    STM32F030R8T6_is_available = true;
                }
            }
        }
    }
    if( STM32F030R8T6_is_available){
        qDebug() << "Found the STM32 port...\n";
         STM32F030R8T6->setPortName( STM32F030R8T6_port_name);
         STM32F030R8T6->open(QSerialPort::ReadOnly);
         STM32F030R8T6->setBaudRate(QSerialPort::Baud115200);
         STM32F030R8T6->setDataBits(QSerialPort::Data8);
         STM32F030R8T6->setFlowControl(QSerialPort::NoFlowControl);
         STM32F030R8T6->setParity(QSerialPort::NoParity);
         STM32F030R8T6->setStopBits(QSerialPort::OneStop);
        QObject::connect( STM32F030R8T6, SIGNAL(readyRead()), this, SLOT(readSerial()));
    }else{
        qDebug() << "Couldn't find the correct port for the STM32.\n";
        QMessageBox::information(this, "Serial Port Error", "Couldn't open serial port to STM32.");
    }

}

MainWindow::~MainWindow()
{
    if(STM32F030R8T6->isOpen()){
        STM32F030R8T6->close();
    }
    delete ui;
}
void MainWindow::readSerial()
{

   QByteArray serialData = STM32F030R8T6->readAll();

  // QString imageData =QString::fromStdString(serialData.toStdString());
   qDebug()<<serialData;

  QImage image(reinterpret_cast< const uchar*>(serialData.data()) ,320 ,120 , QImage::Format_RGB16);


  ui->imageLabel->setPixmap(QPixmap::fromImage(image));


     }

void MainWindow::on_connecter_clicked()
{
    qDebug()<<"user est connecté";
    // Afficher l'image sur la QLabel
    ui->imageLabel->setVisible(true); // Rendre l'image visible
}

void MainWindow::on_disconnecter_clicked()
{
    qDebug()<<"user est disconnecté";
    // Cacher l'image sur la QLabel
    ui->imageLabel->setVisible(false); // Rendre l'image invisible
}






