#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QtMath"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_solveButton_clicked()
{
    bool ok_a,ok_b,ok_c;

    int a = ui->aEdit->text().toInt(&ok_a);
    int b = ui->bEdit->text().toInt(&ok_b);
    int c = ui->cEdit->text().toInt(&ok_c);

    if (ok_a && ok_b && ok_c){
        QPair<QString,QString> roots = SolveEquation(a,b,c);
        ui->x1ResultEdit->setText(roots.first);
        ui->x2ResultEdit->setText(roots.second);
    }
    else{
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Incorrect values are entered! Please enter integer values");
        messageBox.setFixedSize(500,200);
    }
}

QPair<QString, QString> MainWindow::SolveEquation(int a, int b, int c)
{

    QString x1;
    QString x2;

    if (a==0){
        x1 = QString::number(1.0*-c / b,'g',4);
        x2 = "";
        return QPair<QString,QString>{x1,x2};
    }

    double D = b*b-4*a*c;

    if (D<0) {
        D = qSqrt(-D);
        double first = b == 0 ? 0 : -b*0.5 / a;
        x1 = QString::number(first,'g',4) + "+" + QString::number(D/(2*a),'g',4) + "i";
        x2 = QString::number(first,'g',4) + "-" + QString::number(D/(2*a),'g',4) + "i";
    }
    else if (D>0){
        D = qSqrt(D);
        x1 = QString::number((-b+D)/(2*a),'g',4);
        x2 = QString::number((-b-D)/(2*a),'g',4);
    }
    else{
        x1 =QString::number(-b/(2*a),'g',2);
        x2 =QString::number(-b/(2*a),'g',2);
    }


    return QPair<QString,QString>{x1,x2};
}
