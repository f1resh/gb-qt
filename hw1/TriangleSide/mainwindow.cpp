#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QtMath"
#include "QMessageBox"

#define THRESHOLD 0.01

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(this->geometry().width(),this->geometry().height());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_calculateButton_clicked()
{
    bool ok_a,ok_b,ok_angle;

    float a = ui->aEdit->text().toFloat(&ok_a);
    float b = ui->bEdit->text().toFloat(&ok_b);
    float angle = ui->angleEdit->text().toFloat(&ok_angle);

    angle = ui->degreesRadioButton->isChecked() ? qDegreesToRadians(angle) : angle;
    if (fmod(angle,M_2_PI) > M_PI) angle -= M_PI;

    if (ok_a && ok_b && ok_angle && a>0 && b>0 && angle>0){
        float c = CalculateSide(a,b,angle);
        QString result = fmod(angle,M_PI) < THRESHOLD ? "Error!" : QString::number(c,'g',4);
        ui->cEdit->setText(result);
    }
    else{
        QMessageBox errorMessageBox;
        errorMessageBox.critical(0,"Error","Incorrect values! Please, enter non-negative float numbers for two sides and angle!");
        errorMessageBox.setFixedSize(500,200);
    }
}

float MainWindow::CalculateSide(float a, float b, float angle)
{
    float x = a*a + b*b - 2 * a * b * qCos(angle);
    return qSqrt(x);
}
