#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    serialObj = new serialmanagemnet;   //Crear objeto para manejar el serial
    dataObj = new datamanagment;    //Crear objeto para almacenar los datos
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_comboBox_activated(int index)   //Se activa cada vez que se selecciona un elemento de la lista
{
    int indiceSeleccionado = ui->comboBox->currentIndex(); // Obtiene el índice del elemento seleccionado
    serialObj->serial_close();  //Cierra la conexion con el puerto serial para evitar inconvenientes de conexion
    if (indiceSeleccionado != -1) { // Si el índice seleccionado es diferente de -1, significa que hay un elemento seleccionado
        QString valorSeleccionado = ui->comboBox->itemText(indiceSeleccionado); //Obtiene el nombre del elemento de la lista (nombre del microcontrolador seleccionado)
        serialObj->microcontroller_conecction(valorSeleccionado); //Inicia la conexion con el micrcontrolador seleccionado
    } else {
        ui->comboBox->addItem("No se encuentran microcontroladores");
    }
}


void MainWindow::on_btn_test_clicked()  //Boton para probar cosas
{
    dataObj->dataWrite(ui->fileName->text());   
}

void MainWindow::on_btn_guardarDatos_clicked() //Boton para iniciar a guardar datos
{
    dataObj->fileCreation();    //Crear archivo
}


void MainWindow::on_btnSendData_clicked() //Boton para enviar datos al micrcontrolador
{
    serialObj->send_data(ui->edtDataToSend->text());    //Enviar los datos
}


void MainWindow::on_btnSearchControllers_clicked() //Boton para buscar los microcontroladores y ponerlos en la lista de disponibles
{
    serialObj->serial_close();  //Cerar la comunicacion con el serial para evitar problemas
    serialObj->search_port_description();   //Leer que elementos estan disponibles en el puerto serial

    ui->comboBox->clear();  //Eliminar los elementos de la lista para evitar inconvenientes
    ui->comboBox->addItem("Seleccione");
    foreach (QString data, serialObj->microControllerNames) {   //Escribir todos los microcontroladores en la lista
        ui->comboBox->addItem(data);
    }
}


void MainWindow::on_btnDisconnect_clicked() // Boton para terminar la comunicación serial
{
    serialObj->serial_close();
}

