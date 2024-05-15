#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), timer(new QTimer(this))
{
    ui->setupUi(this);
    timer->setInterval(1000);
    connect(timer, &QTimer::timeout, this, &MainWindow::timerHit);
    timer->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timerHit() {
}
