#include "mainwindow.h"
#include "ui_mainwindow.h"

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


void MainWindow::on_pushButton_clicked()
{
    ui->plainTextEdit_2->appendPlainText(ui->plainTextEdit_1->toPlainText());
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->plainTextEdit_2->clear();
    ui->plainTextEdit_2->appendPlainText(ui->plainTextEdit_1->toPlainText());
    ui->plainTextEdit_1->clear();
}

void MainWindow::on_pushButton_3_clicked()
{
    const QString html = "<font color='red'>Hello</font>";
    ui->plainTextEdit_2->clear();
    ui->plainTextEdit_2->appendHtml(html);
}
