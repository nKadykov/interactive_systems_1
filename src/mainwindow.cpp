#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QTime>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), timer(new QTimer(this))
{
    ui->setupUi(this);
    // timer->setInterval(1000);
    // connect(timer, &QTimer::timeout, this, QOverload<>::of(&MainWindow::update));
    // timer->start();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
}

void MainWindow::push_button_1_clicked()
{
    ui->text_browser->setText("1");
}

void MainWindow::push_button_2_clicked()
{
    ui->text_browser->setText(tr("2"));
}

void MainWindow::push_button_3_clicked()
{
    ui->text_browser->setText(tr("3"));
}


void MainWindow::push_button_4_clicked()
{
    ui->text_browser->setText(tr("4"));
}


void MainWindow::push_button_5_clicked()
{
    ui->text_browser->setText(tr("5"));
}


void MainWindow::push_button_6_clicked()
{
    ui->text_browser->setText(tr("6"));
}


void MainWindow::push_button_7_clicked()
{
    ui->text_browser->setText(tr("7"));
}


void MainWindow::push_button_8_clicked()
{
    ui->text_browser->setText(tr("8"));
}


void MainWindow::push_button_9_clicked()
{
    ui->text_browser->setText(tr("9"));
}

void MainWindow::push_button_0_clicked()
{
    ui->text_browser->setText(tr("0"));
}
