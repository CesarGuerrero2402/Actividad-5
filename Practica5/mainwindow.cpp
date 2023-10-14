#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "Neuronas.h"
#include <string>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

Neuronas *neu=new Neuronas();

int i,o,p,r,g,b,neuronas=0;
double v;

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::on_pushButtonM_clicked()
{
    int n=1;
    ui->stackedWidget->setCurrentIndex(1);
    if(neuronas>0)
    {
        while(n<=neuronas)
        {
        neu->mostrar(i,v,o,p,r,g,b,n);
        QString mostrar;
        mostrar.setNum(i);
        ui->plainTextEditMostrar->insertPlainText(mostrar);
        mostrar.setNum(v);
        ui->plainTextEditMostrar->insertPlainText("\t" + mostrar);
        mostrar.setNum(o);
        ui->plainTextEditMostrar->insertPlainText("\t" + mostrar);
        mostrar.setNum(p);
        ui->plainTextEditMostrar->insertPlainText("\t" + mostrar);
        mostrar.setNum(r);
        ui->plainTextEditMostrar->insertPlainText("\t" + mostrar);
        mostrar.setNum(g);
        ui->plainTextEditMostrar->insertPlainText("\t" + mostrar);
        mostrar.setNum(b);
        ui->plainTextEditMostrar->insertPlainText("\t" + mostrar +"\n");
        n=n+1;
        }
    }
    else 
        {
             ui->plainTextEditMostrar->insertPlainText("No hay neuronas guardadas.\n");
        }
    ui->labelMostrar->clear();
}

void MainWindow::on_pushButtonRegresar_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->plainTextEditMostrar->clear();
    ui->labelMostrar2->clear();
    ui->labelMostrar3->clear();

}


void MainWindow::on_pushButtonAI_clicked()
{
    neu->insertarinicio(i,v,o,p,r,g,b);
    neuronas++;
    ui->labelMostrar->setText("Neurona insertada al inicio de la lista.");
}


void MainWindow::on_spinBoxID_valueChanged(int arg1)
{
    i=arg1;
}


void MainWindow::on_doubleSpinBoxV_valueChanged(double arg1)
{
    v=arg1;
}


void MainWindow::on_spinBoxX_valueChanged(int arg1)
{
    o=arg1;
}

void MainWindow::on_spinBoxY_valueChanged(int arg1)
{
    p=arg1;
}


void MainWindow::on_spinBoxR_valueChanged(int arg1)
{
    r=arg1;
}


void MainWindow::on_spinBoxG_valueChanged(int arg1)
{
    g=arg1;
}


void MainWindow::on_spinBoxB_valueChanged(int arg1)
{
    b=arg1;
}




void MainWindow::on_pushButtonAF_clicked()
{
    neu->insertarfinal(i,v,o,p,r,g,b);
    neuronas++;
    ui->labelMostrar->setText("Neurona insertada al final de la lista.");
}



void MainWindow::on_pushButtonGuardar_clicked()
{
    QString guardar = QFileDialog::getSaveFileName(this,"Guarde el archivo","C://","Archivo de Texto(*.txt)");
    QFile file(guardar);

    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
             QMessageBox::warning(this,"ERROR","No se pudo abrir el archivo");
    }
    QTextStream out(&file);
    QString text = ui->plainTextEditMostrar->toPlainText();
    out<<text;
    file.flush();
    file.close();
    ui->labelMostrar2->setText("Lista de neuronas guardada con exito.");
    ui->labelMostrar3->setText("Dirección: " + guardar);
}


void MainWindow::on_pushButtonRecuperar_clicked()
{

    QString recuperar = QFileDialog::getOpenFileName(this,"Abre el archivo","C://","Archivos de Texto(*.txt)");
    QFile file(recuperar);

    string re= recuperar.toStdString();



    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
             QMessageBox::warning(this,"ERROR","No se pudo abrir el archivo");
    }
    QTextStream in(&file);
    QString text = in.readAll();
    ui->plainTextEditMostrar->setPlainText(text);

    ifstream arch;
    arch.open(re,ios::in);

    while(!arch.eof())
    {
             arch >>i>>v>>o>>p>>r>>g>>b;
             neu->insertarfinal(i,v,o,p,r,g,b);
             neuronas++;
    }

    ui->labelMostrar2->setText("Lista de neuronas recuperada con exito.");
    ui->labelMostrar3->setText("Dirección: " + recuperar);
}

