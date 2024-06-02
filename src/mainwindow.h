#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QPushButton>
#include <QTextBrowser>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void push_button_1_clicked();
    void push_button_2_clicked();
    void push_button_3_clicked();
    void push_button_4_clicked();
    void push_button_5_clicked();
    void push_button_6_clicked();
    void push_button_7_clicked();
    void push_button_8_clicked();
    void push_button_9_clicked();
    void push_button_0_clicked();

private:
    QTimer *timer;
};
#endif // MAINWINDOW_H
