#include "keyboard.h"
#include "button.h"

#include <QGridLayout>
#include <QLineEdit>

Keyboard::Keyboard(QWidget* parent) : QWidget(parent) {
    m_display = new QLineEdit("0");
    m_display->setReadOnly(true);
    m_display->setAlignment(Qt::AlignRight);

    for(int i = 0; i < NUMBER; ++i) {
        m_buttons[i] = createButton(QString::number(i), &Keyboard::clickButton);
    }

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(m_display, 0, 0);
    for(int i = 0; i < 10; ++i) {
        mainLayout->addWidget(m_buttons[i], 1, i);
    }
    setLayout(mainLayout);
}

template<typename PointerToMemberFunction>
Button *Keyboard::createButton(const QString &text, const PointerToMemberFunction &member) {
    Button *button = new Button(text);
    connect(button, &Button::clicked, this, member);

    return button;
}

void Keyboard::clickButton() {
    Button *clicked_button = qobject_cast<Button*>(sender());
    int digitValue = clicked_button->text().toInt();
    m_display->setText(QString::number(digitValue));
}
