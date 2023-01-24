#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QStringList list {"C++","Python","Java","C#","PHP","Javascript","Go","Rust"};
    model = new QStandardItemModel(list.size(),1,this);

    for (int i =0; i<model->rowCount();++i){
        QModelIndex index = model->index(i,0);
        QString str = list[i];
        model->setData(index,str,Qt::DisplayRole);
        model->setData(index,QIcon(":/icons/"+str+".png"),Qt::DecorationRole);
    }

    ui->listView->setViewMode(QListView::ListMode);
    ui->listView->setSelectionMode(QAbstractItemView::SingleSelection);

    setDragAndDropList();

    ui->listView->setModel(model);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete model;
}


void MainWindow::on_addButton_clicked()
{
    QStandardItem* item = new QStandardItem{QIcon(":/icons/default.png"),"New"};
    model->appendRow(item);
}
void MainWindow::on_cloneButton_clicked()
{
    QModelIndex selected_index = ui->listView->selectionModel()->currentIndex();
    QStandardItem* item = new QStandardItem(model->itemFromIndex(selected_index)->icon(),model->itemFromIndex(selected_index)->text());
    model->appendRow(item);
}

void MainWindow::on_deleteButton_clicked()
{
    QModelIndex selected_index = ui->listView->selectionModel()->currentIndex();
    QStandardItem* item = new QStandardItem(model->itemFromIndex(selected_index)->text());
    model->removeRows(selected_index.row(),1);
    delete item; //check if this is needed
}

void MainWindow::on_iconViewCheckBox_stateChanged(int arg1)
{
    if (ui->iconViewCheckBox->isChecked()){
        ui->listView->setViewMode(QListView::IconMode);
    }
    else{
        ui->listView->setViewMode(QListView::ListMode);
        setDragAndDropList();
    }
}

void MainWindow::setDragAndDropList()
{
    ui->listView->setDragEnabled(true);
    ui->listView->setDragDropMode(QAbstractItemView::DragDrop);
    ui->listView->setDefaultDropAction(Qt::MoveAction);
    ui->listView->setAcceptDrops(true);
    ui->listView->setDropIndicatorShown(true);
}
