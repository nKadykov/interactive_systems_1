#ifndef KEYBOARD_H
#define KEYBOARD_H
#include <QWidget>
#include <QTime>
#include <QTimer>
#include <QPalette>
#include <QColor>
#include <QElapsedTimer>
#include <QTimer>
#include <QKeyEvent>
#include <QTableWidget>
#include <QTableWidgetItem>

QT_BEGIN_NAMESPACE
class QLineEdit;
QT_END_NAMESPACE
class Button;

class Keyboard : public QWidget
{
    Q_OBJECT
public:
    Keyboard(QWidget* parent = nullptr);

    void setMode();
    void changeColor(int index);
    void changeColorSide(int index);
    void showMessage();
    void resetTable();
private slots:
    void clickButton();
    void timeHit();
    void keyPressEvent(QKeyEvent *event);
private:
    enum class Mode {
        FIRST = 0,
        SECOND,
        THIRD,
        FOURTH,
        FIFTH
    };
    template<typename PointerToMemberFunction1>
    Button *createButton(const QString&, const PointerToMemberFunction1&);
    QLineEdit *m_display;
    enum {NUMBER = 10};
    Button *m_buttons[NUMBER];
    enum {NUMBER_SIDE = 10};
    Button *m_buttons_side[NUMBER_SIDE];
    enum {NUMBER_MODE = 5};
    Button *m_buttons_mode[NUMBER_MODE];
    QTimer *m_timer;
    QElapsedTimer *m_elapsed;
    QColor m_color;
    QPalette m_palette;
    bool m_is_changed = false;
    Mode m_mode = Mode::FIRST;
    QTableWidget* m_table;
    QString m_result_string;
    int index = 1;
    int m_passed_time;
};

#endif // KEYBOARD_H
