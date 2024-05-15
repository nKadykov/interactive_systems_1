#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void buttonOneClicked();
    void buttonTwoClicked();
    void buttonThreeClicked();
    void buttonFourClicked();
    void buttonFiveClicked();
    void buttonSixClicked();
    void buttonSevenClicked();
    void buttonEightClicked();
    void buttonNineClicked();
    void buttonZeroClicked();
private slots:
    void timerHit();
private:
    Ui::MainWindow *ui;
    QTimer *timer;
};
#endif // MAINWINDOW_H
