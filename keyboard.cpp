#include "keyboard.h"
#include "button.h"

#include <QGridLayout>
#include <QLineEdit>

Keyboard::Keyboard(QWidget* parent) : QWidget(parent), m_timer(new QTimer(this)), m_elapsed(new QElapsedTimer()) {
    m_timer->setInterval(1000);
    m_elapsed->start();
    QFont* font = new QFont;
    font->setPointSize(50);
    m_display = new QLineEdit("0 ms");
    m_display->setReadOnly(true);
    m_display->setAlignment(Qt::AlignRight);
    m_display->setMinimumSize(10, 100);
    m_display->setFont(*font);
    m_color = QColor(Qt::white);
    m_palette.setColor(QPalette::Button, QColor(Qt::blue));
    connect(m_timer, &QTimer::timeout, this, &Keyboard::timeHit);
    for(int i = 0; i < NUMBER; ++i) {
        m_buttons[i] = createButton(QString::number(i), &Keyboard::clickButton);
        m_buttons[i]->setStyleSheet("background-color: white");
    }
    for(int i = 0; i < NUMBER_SIDE; ++i) {
        m_buttons_side[i] = createButton(QString::number(i), &Keyboard::clickButton);
        m_buttons_side[i]->setStyleSheet("background-color: white");
    }
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setSizeConstraint(QLayout::SetMaximumSize);
    mainLayout->addWidget(m_display, 0, 0, 1, 11);
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    for(int i = 1; i < 10; ++i) {
        mainLayout->addWidget(m_buttons[i], 1, i - 1, 1, 1);
    }
    mainLayout->addWidget(m_buttons[0], 1, 10, 1, 1);
    for(int i = 1; i < 10; ++i) {
        mainLayout->addWidget(m_buttons_side[i], 2 + ((i - 1) / 3), 10 + ((i - 1) % 3));
    }
    mainLayout->addWidget(m_buttons_side[0], 5, 10, 2, 1);
    setLayout(mainLayout);
    m_timer->start();
}

template<typename PointerToMemberFunction1>
Button *Keyboard::createButton(const QString &text, const PointerToMemberFunction1 &member1) {
    Button *button = new Button(text);
    connect(button, &Button::clicked, this, member1);

    return button;
}

void Keyboard::clickButton() {
    Button *clicked_button = qobject_cast<Button*>(sender());
    m_color = clicked_button->palette().color(QPalette::Button);
    if(m_color == QColor(Qt::red)) {
        clicked_button->setStyleSheet("background-color: white");
        m_color = QColor(Qt::white);
        int e = m_elapsed->elapsed();
        m_display->setText(QString::number(e) + " ms");
    }
    m_elapsed->restart();
}

void Keyboard::changeColor(int index) {
    m_buttons[index]->setStyleSheet("background-color: red");
    m_is_changed = true;
    m_elapsed->restart();
}

void Keyboard::timeHit() {
    int time = rand() % 3000;
    int elapsed = m_elapsed->elapsed();
    int index = rand() % 10;
    if(elapsed > time && (!m_is_changed)) {
        m_is_changed = true;
        changeColor(index);
    }
}

void Keyboard::keyPressEvent(QKeyEvent* event) {
    int key = event->key();
    switch(key) {
        case Qt::Key_0:
            emit m_buttons[key - Qt::Key_0]->clicked();
            m_is_changed = false;
            break;
        case Qt::Key_1:
            emit m_buttons[key - Qt::Key_0]->clicked();
            m_is_changed = false;
            break;
        case Qt::Key_2:
            emit m_buttons[key - Qt::Key_0]->clicked();
            m_is_changed = false;
            break;
        case Qt::Key_3:
            emit m_buttons[key - Qt::Key_0]->clicked();
            m_is_changed = false;
            break;
        case Qt::Key_4:
            emit m_buttons[key - Qt::Key_0]->clicked();
            m_is_changed = false;
            break;
        case Qt::Key_5:
            emit m_buttons[key - Qt::Key_0]->clicked();
            m_is_changed = false;
            break;
        case Qt::Key_6:
            emit m_buttons[key - Qt::Key_0]->clicked();
            m_is_changed = false;
            break;
        case Qt::Key_7:
            emit m_buttons[key - Qt::Key_0]->clicked();
            m_is_changed = false;
            break;
        case Qt::Key_8:
            emit m_buttons[key - Qt::Key_0]->clicked();
            m_is_changed = false;
            break;
        case Qt::Key_9:
            emit m_buttons[key - Qt::Key_0]->clicked();
            m_is_changed = false;
            break;
    }
}
