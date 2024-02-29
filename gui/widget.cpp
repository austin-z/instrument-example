#include "widget.h"
#include <QGridLayout>
#include <QIntValidator>

namespace {

void setAutoRepeat(QPushButton *btn) {
    btn->setAutoRepeat(true);
    btn->setAutoRepeatInterval(40);
    btn->setAutoRepeatDelay(200);
}

void initializeSpinbox(QSpinBox *box, int min_value, int max_value, int value) {
    box->setMinimum(min_value);
    box->setMaximum(max_value);
    box->setValue(value);
}

}

Widget::Widget(QWidget *parent)
    : QWidget(parent),
      btn_clockwise_shaft_(new QPushButton(QStringLiteral("绕杆旋转"), this)),
      btn_counterclockwise_shaft_(new QPushButton(QStringLiteral("绕杆旋转"), this)),
      btn_left_end_(new QPushButton(QStringLiteral("末端摆动"), this)),
      btn_right_end_(new QPushButton(QStringLiteral("末端摆动"), this)),
      btn_open_gripper_(new QPushButton(QStringLiteral("张开"), this)),
      btn_close_gripper_(new QPushButton(QStringLiteral("闭合"), this)),
      box_shaft_speed_(new QSpinBox(this)),
      box_end_speed_(new QSpinBox(this)),
      box_gripper_speed_(new QSpinBox(this)),
      scissors_(new Scissors("/dev/ttyUSB0")) {

    auto layout = new QGridLayout(this);
    layout->addWidget(btn_clockwise_shaft_, 0, 0);
    layout->addWidget(btn_counterclockwise_shaft_, 0, 1);
    layout->addWidget(btn_left_end_, 1, 0);
    layout->addWidget(btn_right_end_, 1, 1);
    layout->addWidget(btn_open_gripper_, 2, 0);
    layout->addWidget(btn_close_gripper_, 2, 1);

    setAutoRepeat(btn_clockwise_shaft_);
    setAutoRepeat(btn_counterclockwise_shaft_);
    setAutoRepeat(btn_left_end_);
    setAutoRepeat(btn_right_end_);
    setAutoRepeat(btn_open_gripper_);
    setAutoRepeat(btn_close_gripper_);

    layout->addWidget(box_shaft_speed_, 0, 2);
    layout->addWidget(box_end_speed_, 1, 2);
    layout->addWidget(box_gripper_speed_, 2, 2);

    initializeSpinbox(box_shaft_speed_, 20, 300, 100);
    initializeSpinbox(box_end_speed_, 20, 200, 50);
    initializeSpinbox(box_gripper_speed_, 20, 300, 50);

    resize(300, 200);

    scissors_->initialize();

    connect(btn_clockwise_shaft_, &QPushButton::clicked, this, [this]() {
          scissors_->control({0, (int16_t)box_shaft_speed_->value(), 0, 0});
      }
    );

    connect(btn_counterclockwise_shaft_, &QPushButton::clicked, this, [this]() {
          scissors_->control({0, (int16_t)-box_shaft_speed_->value(), 0, 0});
      }
    );

    connect(btn_left_end_, &QPushButton::clicked, this, [this]() {
          scissors_->control({0, 0, (int16_t)box_end_speed_->value(), 0});
      }
    );

    connect(btn_right_end_, &QPushButton::clicked, this, [this]() {
          scissors_->control({0, 0, (int16_t)-box_end_speed_->value(), 0});
      }
    );

    connect(btn_open_gripper_, &QPushButton::clicked, this, [this]() {
          int16_t v = box_gripper_speed_->value();
          scissors_->control({v, 0, 0, v});
      }
    );

    connect(btn_close_gripper_, &QPushButton::clicked, this, [this]() {
          int16_t v = -box_gripper_speed_->value();
          scissors_->control({v, 0, 0, v});
      }
    );
}

Widget::~Widget() {
    scissors_->uninitialize();
}
