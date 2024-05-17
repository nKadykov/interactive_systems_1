#ifndef KEYBOARD_H
#define KEYBOARD_H
#include <QWidget>
#include <QTimer>
#include <QPalette>
#include <QColor>
#include <QElapsedTimer>
#include <QTimer>
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
class QLineEdit;
QT_END_NAMESPACE
class Button;

class Keyboard : public QWidget
{
    Q_OBJECT
public:
    Keyboard(QWidget* parent = nullptr);
private slots:
    void clickButton();
    void changeColor(int index);
    void timeHit();
    void keyPressEvent(QKeyEvent *event);
private:
    template<typename PointerToMemberFunction1>
    Button *createButton(const QString&, const PointerToMemberFunction1&);
    QLineEdit *m_display;
    enum {NUMBER = 10};
    Button *m_buttons[NUMBER];
    enum {NUMBER_SIDE = 10};
    Button *m_buttons_side[NUMBER_SIDE];
    QTimer *m_timer;
    QElapsedTimer *m_elapsed;
    QColor m_color;
    QPalette m_palette;
    bool m_is_changed = false;
};

#endif // KEYBOARD_H
