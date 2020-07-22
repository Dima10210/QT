#include "clickablelabel.h"

ClickableLabel::ClickableLabel (const QString& text, QWidget* parent) : QLabel(parent) {
 setText (text);
 this->setTag(0);
}

ClickableLabel::~ClickableLabel() {}

void ClickableLabel::mousePressEvent (QMouseEvent *event) {
 emit clicked(event); //испускаем сигнал при нажатии кнопки мыши!
}

void ClickableLabel::setTag(int tag) {
 this->t = tag;
}
int ClickableLabel::tag(void) {
 return this->t;
}
