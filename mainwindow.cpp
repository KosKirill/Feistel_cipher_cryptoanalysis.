#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QDebug>
#include "encrypt.h"
#include "decrypt.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    class encrypt encrypt_dialog;
    encrypt_dialog.setModal(true);
    encrypt_dialog.exec();

}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_checkBox_stateChanged(int arg1)
{

}
