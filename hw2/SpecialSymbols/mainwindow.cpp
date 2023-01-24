#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    parseText = new ParseText();
    //if (!parseText) close();
}

MainWindow::~MainWindow()
{
    if (parseText) {
        delete parseText;
        parseText = nullptr;
    }
    delete ui;
}


void MainWindow::on_plainTextEdit_textChanged()
{
    QString str = ui->plainTextEdit->toPlainText(); // получаем текст виджета
    if (parseText->change(str)) {// были ли примеры
        ui->plainTextEdit->setPlainText(parseText->getText()); // заменяем текст примеры с результатами
        set_text_cursor_to_end();
    }

}

void MainWindow::set_text_cursor_to_end()
{
    QTextCursor cursor= ui->plainTextEdit->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->plainTextEdit->setTextCursor(cursor);
}
