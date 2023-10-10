#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>

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
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void serial_read();

    void on_pushButton_3_clicked();

    void search_arduino();

    void serial_close();

private:
    Ui::MainWindow *ui;
    QSerialPort *serial;
    QString portName;

    // Verificar tarjeta conectada de arduino
    quint16 vendorId;
    quint16 productId;

    bool arduinoAvailabe;

    void arduinoInit();

    QByteArray serialData;
    QString serialBuffer;
};
#endif // MAINWINDOW_H
