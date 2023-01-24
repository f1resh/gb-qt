#include "mainwindow.h"
#include "ui_mainwindow.h"

const QString possibleCharacters("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    model = new QStandardItemModel(this);

    ui->tableView->setModel(model);
    ui->tableView->setSelectionMode(QAbstractItemView::MultiSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QStringList header_list{"№","Computer Name","IP address","MAC address"};
    model->setHorizontalHeaderLabels(header_list);

    for (int i=0; i<10;++i){
        QList<QStandardItem*> list;
        list.append(new QStandardItem(QString::number(i+1)));
        list.append(new QStandardItem(generateName()));
        list.append(new QStandardItem(generateIP()));
        list.append(new QStandardItem(generateMAC()));
        model->appendRow(list);
    }


}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::generateName()
{
    const int randomStringLength = 8; // assuming you want random strings of 12 characters

       QString randomString;
       for(int i=0; i<randomStringLength; ++i)
       {
           int index = qrand() % possibleCharacters.length();
           QChar nextChar = possibleCharacters.at(index);
           randomString.append(nextChar);
       }
    return randomString;
}

QString MainWindow::generateIP()
{
    QString result;
    for (int i=0;i<4;++i ){
        result += QString::number(qrand()%255)+".";
    }
    result.chop(1);
    return result;
}

QString MainWindow::generateMAC()
{
    QString result;
    for (int i=0;i<6;++i ){
        result += QString::number(qrand()%255,16)+":";
    }
    result.chop(1);
    return result;
}


void MainWindow::on_colorButton_clicked()
{
    QModelIndexList index_list = ui->tableView->selectionModel()->selectedRows();
    for (const QModelIndex idx : index_list){
        for (int j = 0; j<model->columnCount();++j){
            const QModelIndex index = model->index(idx.row(),j);
            model->setData(index, QColor(255, 255, 0), Qt::BackgroundRole);
        }
    }
    ui->tableView->clearSelection();


}
