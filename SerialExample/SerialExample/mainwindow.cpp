#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    serialObj = new serialmanagemnet; // Declarar "objeto" como un puntero
    dataObj = new datamanagment;
    //serialObj->search_arduino();
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
    serialObj->serial_close();
    serialObj->search_port_description();

    ui->comboBox->clear();
    ui->comboBox->addItem("Seleccione");
    foreach (QString data, serialObj->microControllerNames) {
        ui->comboBox->addItem(data);
    }

}


void MainWindow::on_pushButton_3_clicked() //Boton de conectar/desconectar microcontrolador
{
   if(serialObj->microController->isOpen()){
        serialObj->serial_close();
        ui->pushButton_3->setText("Conectar");
    }else{
    // serialObj->search_arduino();
        ui->pushButton_3->setText("Desconectar");
    }
}



void MainWindow::on_comboBox_activated(int index)
{
    int indiceSeleccionado = ui->comboBox->currentIndex(); // Obtiene el índice del elemento seleccionado
    serialObj->serial_close();
    if (indiceSeleccionado != -1) {// Si el índice seleccionado es diferente de -1, significa que hay un elemento seleccionado

        QString valorSeleccionado = ui->comboBox->itemText(indiceSeleccionado);
        serialObj->microcontroller_conecction(valorSeleccionado);
        //qDebug()<<valorSeleccionado;// Realiza acciones con el índice o el valor del elemento seleccionado
    } else {
        ui->comboBox->addItem("No se encuentran microcontroladores");
    }
}


void MainWindow::on_pushButton_4_clicked()
{
    ui->comboBox->clear();
}


void MainWindow::on_btn_ruta_clicked()
{
    directorioSeleccionado = QFileDialog::getExistingDirectory(this, "Seleccionar Carpeta", QDir::homePath());
    qDebug()<<directorioSeleccionado;
}


void MainWindow::on_btn_test_clicked()
{
    dataObj->pathSelection();
    /*int a =0;
    QFile file(directorioSeleccionado + "/prueba.csv");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << "Dato" << "\n";


        while(true){
            out << QString::number(a) << "\n";
            a++;
        }

        file.close(); // Cierra el archivo después de escribir todos los datos.
    } else {
        // Manejar el error si no se pudo abrir el archivo.
        qDebug() << "No se abrió el archivo.";
    }*/
}

void MainWindow::on_btn_guardarDatos_clicked()
{
    dataObj->pathSelection();
    dataObj->fileCreation(ui->fileName->text(),dataObj->directorioSeleccionado);
}

