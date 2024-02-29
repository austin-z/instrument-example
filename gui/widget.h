#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QSpinBox>
#include "instruments/scissors.h"

class Widget : public QWidget {
  Q_OBJECT

public:
  Widget(QWidget *parent = nullptr);
  ~Widget();

private slots:

private:
  QPushButton *btn_clockwise_shaft_;
  QPushButton *btn_counterclockwise_shaft_;
  QPushButton *btn_left_end_;
  QPushButton *btn_right_end_;
  QPushButton *btn_open_gripper_;
  QPushButton *btn_close_gripper_;

  QSpinBox *box_shaft_speed_;
  QSpinBox *box_end_speed_;
  QSpinBox *box_gripper_speed_;

  Scissors *scissors_;
};

#endif