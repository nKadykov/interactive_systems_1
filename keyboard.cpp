#include "keyboard.h"
#include "button.h"

#include <QGridLayout>
#include <QLineEdit>
#include <QMessageBox>

Keyboard::Keyboard(QWidget* parent) : QWidget(parent), m_timer(new QTimer(this)), m_elapsed(new QElapsedTimer()) {
    m_table = new QTableWidget;
    m_table->setRowCount(20);
    m_table->setColumnCount(2);
    QTableWidgetItem *item1 = new QTableWidgetItem;
    item1->setText(QString("Mode"));
    m_table->setItem(0, 0, item1);
    QTableWidgetItem *item2 = new QTableWidgetItem;
    item2->setText(QString("Time"));
    m_table->setItem(0, 1, item2);

    m_timer->setInterval(1000);
    m_elapsed->start();
    QFont* font = new QFont;
    font->setPointSize(50);
    m_display = new QLineEdit("0 ms");
    m_display->setReadOnly(true);
    m_display->setAlignment(Qt::AlignRight);
    m_display->setMinimumSize(500, 50);
    m_display->setFont(*font);
    m_color = QColor(Qt::white);
    m_palette.setColor(QPalette::Button, QColor(Qt::green));
    connect(m_timer, &QTimer::timeout, this, &Keyboard::timeHit);

    for(int i = 0; i < NUMBER; ++i) {
        m_buttons[i] = createButton(QString::number(i), &Keyboard::clickButton);
        m_buttons[i]->setStyleSheet("background-color: white");
    }
    m_buttons[10] = createButton(tr("-"), &Keyboard::clickButton);
    m_buttons[10]->setStyleSheet("background-color: white");
    m_buttons[11] = createButton(tr("+"), &Keyboard::clickButton);
    m_buttons[11]->setStyleSheet("background-color: white");
    for(int i = 0; i < 10; ++i) {
        m_buttons_side[i] = createButton(QString::number(i), &Keyboard::clickButton);
        m_buttons_side[i]->setStyleSheet("background-color: white");
    }
    m_buttons_side[10] = createButton(tr("Num\nLock"), &Keyboard::clickButton);
    m_buttons_side[10]->setStyleSheet("background-color: white");
    m_buttons_side[11] = createButton(tr("/"), &Keyboard::clickButton);
    m_buttons_side[11]->setStyleSheet("background-color: white");
    m_buttons_side[12] = createButton(tr("*"), &Keyboard::clickButton);
    m_buttons_side[12]->setStyleSheet("background-color: white");
    m_buttons_side[13] = createButton(tr("-"), &Keyboard::clickButton);
    m_buttons_side[13]->setStyleSheet("background-color: white");
    m_buttons_side[14] = createButton(tr("+"), &Keyboard::clickButton);
    m_buttons_side[14]->setStyleSheet("background-color: white");
    m_buttons_side[15] = createButton(tr("Enter"), &Keyboard::clickButton);
    m_buttons_side[15]->setStyleSheet("background-color: white");
    m_buttons_side[16] = createButton(tr("."), &Keyboard::clickButton);
    m_buttons_side[16]->setStyleSheet("background-color: white");
    for(int i = 0; i < NUMBER_MODE; ++i) {
        m_buttons_mode[i] = createButton(tr("MODE: ") + QString::number(i + 1), &Keyboard::setMode);
        m_buttons_mode[i]->setStyleSheet("background-color: white");
    }

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(m_display, 0, 0, 1, 11);
    for(int i = 1; i < 10; ++i) {
        mainLayout->addWidget(m_buttons[i], 1, i - 1, 1, 1);
    }
    mainLayout->addWidget(m_buttons[0], 1, 10, 1, 1);
    mainLayout->addWidget(m_buttons[10], 1, 11, 1, 1);
    mainLayout->addWidget(m_buttons[11], 1, 12, 1, 1);
    for(int i = 1; i < 10; ++i) {
        mainLayout->addWidget(m_buttons_side[i], 5 - ((i - 1) / 3), 10 + ((i - 1) % 3));
    }
    mainLayout->addWidget(m_buttons_side[0], 6, 10, 1, 2);
    mainLayout->addWidget(m_buttons_side[10], 2, 10, 1, 1);
    mainLayout->addWidget(m_buttons_side[11], 2, 11, 1, 1);
    mainLayout->addWidget(m_buttons_side[12], 2, 12, 1, 1);
    mainLayout->addWidget(m_buttons_side[13], 2, 13, 1, 1);
    mainLayout->addWidget(m_buttons_side[14], 3, 13, 2, 1);
    mainLayout->addWidget(m_buttons_side[15], 5, 13, 2, 1);
    mainLayout->addWidget(m_buttons_side[16], 6, 12, 1, 1);
    for(int i = 0; i < NUMBER_MODE; ++i) {
            mainLayout->addWidget(m_buttons_mode[i], 3, i, 1, 1);
    }
    mainLayout->addWidget(m_table, 0, 14, 10, 1);
    setLayout(mainLayout);
    setMinimumSize(1280, 500);
    m_timer->start();
}

template<typename PointerToMemberFunction1>
Button *Keyboard::createButton(const QString &text, const PointerToMemberFunction1 &member1) {
    Button *button = new Button(text);
    connect(button, &Button::clicked, this, member1);
    return button;
}

void Keyboard::setMode() {
    Button *clicked_button = qobject_cast<Button*>(sender());
    if(clicked_button == m_buttons_mode[0]) {
        m_table->clear();
        QTableWidgetItem *item1 = new QTableWidgetItem;
        item1->setText(QString("Mode"));
        m_table->setItem(0, 0, item1);
        QTableWidgetItem *item2 = new QTableWidgetItem;
        item2->setText(QString("Time"));
        m_table->setItem(0, 1, item2);
        index = 1;
        m_mode = Mode::FIRST;
    }
    if(clicked_button == m_buttons_mode[1]) {
        m_table->clear();
        QTableWidgetItem *item1 = new QTableWidgetItem;
        item1->setText(QString("Mode"));
        m_table->setItem(0, 0, item1);
        QTableWidgetItem *item2 = new QTableWidgetItem;
        item2->setText(QString("Time"));
        m_table->setItem(0, 1, item2);
        index = 1;
        m_mode = Mode::SECOND;
    }
    if(clicked_button == m_buttons_mode[2]) {
        m_table->clear();
        QTableWidgetItem *item1 = new QTableWidgetItem;
        item1->setText(QString("Mode"));
        m_table->setItem(0, 0, item1);
        QTableWidgetItem *item2 = new QTableWidgetItem;
        item2->setText(QString("Time"));
        m_table->setItem(0, 1, item2);
        index = 1;
        m_mode = Mode::THIRD;
    }
    if(clicked_button == m_buttons_mode[3]) {
        m_table->clear();
        QTableWidgetItem *item1 = new QTableWidgetItem;
        item1->setText(QString("Mode"));
        m_table->setItem(0, 0, item1);
        QTableWidgetItem *item2 = new QTableWidgetItem;
        item2->setText(QString("Time"));
        m_table->setItem(0, 1, item2);
        index = 1;
        m_mode = Mode::FOURTH;
    }
    if(clicked_button == m_buttons_mode[4]) {
        m_table->clear();
        QTableWidgetItem *item1 = new QTableWidgetItem;
        item1->setText(QString("Mode"));
        m_table->setItem(0, 0, item1);
        QTableWidgetItem *item2 = new QTableWidgetItem;
        item2->setText(QString("Time"));
        m_table->setItem(0, 1, item2);
        index = 1;
        m_mode = Mode::FIFTH;
    }
}

void Keyboard::clickButton() {
    Button *clicked_button = qobject_cast<Button*>(sender());
    m_color = clicked_button->palette().color(QPalette::Button);
    if(m_color == QColor(Qt::yellow)) {
        clicked_button->setStyleSheet("background-color: white");
        m_color = QColor(Qt::white);
        int e = m_elapsed->elapsed();
        m_result_string += (QString::number(e) + "\n");
        m_display->setText(QString::number(e) + " ms");
        m_is_changed = false;

        if(index > 20) {
            m_table->resize(index, 3);
        }
        QTableWidgetItem* item1 = new QTableWidgetItem;
        item1->setText(QString::number(static_cast<int>(m_mode) + 1));
        m_table->setItem(index, 0, item1);
        QTableWidgetItem* item2 = new QTableWidgetItem;
        item2->setText(QString::number(e / 1000) + "." + QString::number(e % 1000));
        m_table->setItem(index, 1, item2);
        index++;
    }
    m_elapsed->restart();
}

void Keyboard::changeColor(int index) {
    m_buttons[index]->setStyleSheet("background-color: yellow");
    m_is_changed = true;
    m_elapsed->restart();
}

void Keyboard::changeColorSide(int index) {
    m_buttons_side[index]->setStyleSheet("background-color: yellow");
    m_is_changed = true;
    m_elapsed->restart();
}

void Keyboard::timeHit() {
    int time = rand() % 3000;
    int elapsed = m_elapsed->elapsed();
    int index;
    int keyboard_part = 0;
    if(elapsed > time && (!m_is_changed)) {
        switch (m_mode) {
            case Mode::FIRST:
                index = 1;
                m_is_changed = true;
                changeColor(index);
                break;
            case Mode::SECOND:
                index = rand() % NUMBER;
                m_is_changed = true;
                changeColor(index);
                break;
            case Mode::THIRD:
                index = 1;
                changeColorSide(index);
                m_is_changed = true;
                break;
            case Mode::FOURTH:
                index = rand() % NUMBER_SIDE;
                changeColorSide(index);
                m_is_changed = true;
                break;
            case Mode::FIFTH:
                keyboard_part = rand() % 2;
                if(keyboard_part == 0) {
                    index = rand() % NUMBER;
                    changeColor(index);
                    m_is_changed = true;
                }
                if(keyboard_part == 1) {
                    index = rand() % NUMBER_SIDE;
                    changeColorSide(index);
                    m_is_changed = true;
                }
                m_is_changed = true;
                break;
        }
    }
}

void Keyboard::keyPressEvent(QKeyEvent* event) {
    int key = event->key();
    switch(key) {
        case Qt::Key_0:
            if(m_mode == Mode::FIRST) {
                QMessageBox message_box;
                message_box.setText("Wrong button");
                message_box.exec();
            }
            if(event->modifiers() & Qt::KeypadModifier)
                emit m_buttons_side[key - Qt::Key_0]->clicked();
            else
                emit m_buttons[key - Qt::Key_0]->clicked();
            m_is_changed = false;
            break;
        case Qt::Key_1:
            if(event->modifiers() & Qt::KeypadModifier)
                emit m_buttons_side[key - Qt::Key_0]->clicked();
            else
                emit m_buttons[key - Qt::Key_0]->clicked();
            m_is_changed = false;
            break;
        case Qt::Key_2:
            if(m_mode == Mode::FIRST) {
                QMessageBox message_box;
                message_box.setText("Wrong button");
                message_box.exec();
            }
            if(event->modifiers() & Qt::KeypadModifier)
                emit m_buttons_side[key - Qt::Key_0]->clicked();
            else
                emit m_buttons[key - Qt::Key_0]->clicked();
            m_is_changed = false;
            break;
        case Qt::Key_3:
            if(m_mode == Mode::FIRST) {
                QMessageBox message_box;
                message_box.setText("Wrong button");
                message_box.exec();
            }
            if(event->modifiers() & Qt::KeypadModifier)
                emit m_buttons_side[key - Qt::Key_0]->clicked();
            else
                emit m_buttons[key - Qt::Key_0]->clicked();
            m_is_changed = false;
            break;
        case Qt::Key_4:
            if(m_mode == Mode::FIRST) {
                QMessageBox message_box;
                message_box.setText("Wrong button");
                message_box.exec();
            }
            if(event->modifiers() & Qt::KeypadModifier)
                emit m_buttons_side[key - Qt::Key_0]->clicked();
            else
                emit m_buttons[key - Qt::Key_0]->clicked();
            m_is_changed = false;
            break;
        case Qt::Key_5:
            if(m_mode == Mode::FIRST) {
                QMessageBox message_box;
                message_box.setText("Wrong button");
                message_box.exec();
            }
            if(event->modifiers() & Qt::KeypadModifier)
                emit m_buttons_side[key - Qt::Key_0]->clicked();
            else
                emit m_buttons[key - Qt::Key_0]->clicked();
            m_is_changed = false;
            break;
        case Qt::Key_6:
            if(m_mode == Mode::FIRST) {
                QMessageBox message_box;
                message_box.setText("Wrong button");
                message_box.exec();
            }
            if(event->modifiers() & Qt::KeypadModifier)
                emit m_buttons_side[key - Qt::Key_0]->clicked();
            else
                emit m_buttons[key - Qt::Key_0]->clicked();
            m_is_changed = false;
            break;
        case Qt::Key_7:
            if(m_mode == Mode::FIRST) {
                QMessageBox message_box;
                message_box.setText("Wrong button");
                message_box.exec();
            }
            if(event->modifiers() & Qt::KeypadModifier)
                emit m_buttons_side[key - Qt::Key_0]->clicked();
            else
                emit m_buttons[key - Qt::Key_0]->clicked();
            m_is_changed = false;
            break;
        case Qt::Key_8:
            if(m_mode == Mode::FIRST) {
                QMessageBox message_box;
                message_box.setText("Wrong button");
                message_box.exec();
            }
            if(event->modifiers() & Qt::KeypadModifier)
                emit m_buttons_side[key - Qt::Key_0]->clicked();
            else
                emit m_buttons[key - Qt::Key_0]->clicked();
            m_is_changed = false;
            break;
        case Qt::Key_9:
            if(m_mode == Mode::FIRST) {
                QMessageBox message_box;
                message_box.setText("Wrong button");
                message_box.exec();
            }
            if(event->modifiers() & Qt::KeypadModifier)
                emit m_buttons_side[key - Qt::Key_0]->clicked();
            else
                emit m_buttons[key - Qt::Key_0]->clicked();
            m_is_changed = false;
            break;
        case Qt::Key_Minus:
            if(m_mode == Mode::FIRST) {
                QMessageBox message_box;
                message_box.setText("Wrong button");
                message_box.exec();
            }
            if(event->modifiers() & Qt::KeypadModifier)
                emit m_buttons_side[13]->clicked();
            else
                emit m_buttons[10]->clicked();
            m_is_changed = false;
            break;
        case Qt::Key_Equal:
            if(m_mode == Mode::FIRST) {
                QMessageBox message_box;
                message_box.setText("Wrong button");
                message_box.exec();
            }
            emit m_buttons[11]->clicked();
            m_is_changed = false;
            break;
        case Qt::Key_Plus:
            if(m_mode == Mode::FIRST) {
                QMessageBox message_box;
                message_box.setText("Wrong button");
                message_box.exec();
            }
            if(event->modifiers() & Qt::KeypadModifier)
                emit m_buttons_side[14]->clicked();
            else
                emit m_buttons[11]->clicked();
            m_is_changed = false;
            break;
        case Qt::Key_NumLock:
            if(m_mode == Mode::FIRST) {
                QMessageBox message_box;
                message_box.setText("Wrong button");
                message_box.exec();
            }
            emit m_buttons_side[10]->clicked();
            m_is_changed = false;
            break;
        case Qt::Key_Slash:
            if(m_mode == Mode::FIRST) {
                QMessageBox message_box;
                message_box.setText("Wrong button");
                message_box.exec();
            }
            emit m_buttons_side[11]->clicked();
            m_is_changed = false;
            break;
        case Qt::Key_Asterisk:
            if(m_mode == Mode::FIRST) {
                QMessageBox message_box;
                message_box.setText("Wrong button");
                message_box.exec();
            }
            emit m_buttons_side[12]->clicked();
            m_is_changed = false;
            break;
        case Qt::Key_Enter:
            if(m_mode == Mode::FIRST) {
                QMessageBox message_box;
                message_box.setText("Wrong button");
                message_box.exec();
            }
            emit m_buttons_side[15]->clicked();
            m_is_changed = false;
            break;
        case Qt::Key_Period:
            if(m_mode == Mode::FIRST) {
                QMessageBox message_box;
                message_box.setText("Wrong button");
                message_box.exec();
            }
            emit m_buttons_side[16]->clicked();
            m_is_changed = false;
            break;
    }
}
