#ifndef KEYBOARD_H
#define KEYBOARD_H
#include <QWidget>

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
private:
    template<typename PointerToMemberFunction>
    Button *createButton(const QString &text, const PointerToMemberFunction &member);
    QLineEdit *m_display;
    enum {NUMBER = 10};
    Button *m_buttons[NUMBER];
};

#endif // KEYBOARD_H
