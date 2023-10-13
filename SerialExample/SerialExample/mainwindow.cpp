#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    serialObj = new serialmanagemnet; // Declarar "objeto" como un puntero
    serialObj->search_arduino();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    serialObj->send_data("Esto es una cadena a enviar");
}


void MainWindow::on_pushButton_2_clicked()
{
    ui->pushButton_2->setText("AQUI");
    serialObj->test();
}


void MainWindow::on_pushButton_3_clicked() //Boton de conectar/desconectar microcontrolador
{
    if(serialObj->microController->isOpen()){
        serialObj->serial_close();
        ui->pushButton_3->setText("Conectar");
    }else{
     serialObj->search_arduino();
        ui->pushButton_3->setText("Desconectar");
    }
}


