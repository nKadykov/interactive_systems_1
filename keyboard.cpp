#include "keyboard.h"
#include "button.h"

#include <QGridLayout>
#include <QLineEdit>

Keyboard::Keyboard(QWidget* parent) : QWidget(parent), m_timer(new QTimer(this)) {
    m_timer->setInterval(1000);
    m_timer->start(1000);
    int time = rand() % 10;
    m_display = new QLineEdit("0");
    m_display->setReadOnly(true);
    m_display->setAlignment(Qt::AlignRight);
    m_color.setBlue(1);
    m_palette.setColor(QPalette::Button, QColor(Qt::blue));

    for(int i = 0; i < NUMBER; ++i) {
        m_buttons[i] = createButton(QString::number(i), &Keyboard::clickButton);
        m_buttons[i]->setPalette(m_palette);
        m_buttons[i]->setStyleSheet("background-color: white");
        m_color = QColor(Qt::white);
    }

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setSizeConstraint(QLayout::SetMaximumSize);
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
    m_color = clicked_button->palette().color(QPalette::Button);
    if(m_color == QColor(Qt::white)) {
        clicked_button->setStyleSheet("background-color: red");
        m_color = QColor(Qt::red);
    }
    else if(m_color == QColor(Qt::red)) {
        clicked_button->setStyleSheet("background-color: white");
        m_color = QColor(Qt::white);
    }
    m_display->setText(QString::number(digitValue));
}
