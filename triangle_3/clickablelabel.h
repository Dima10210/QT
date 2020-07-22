#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QLabel>
#include <QMouseEvent>

class ClickableLabel : public QLabel {
 Q_OBJECT
public:
 explicit ClickableLabel (const QString& text="", QWidget* parent=0);
 ~ClickableLabel();
signals:
 void clicked(QMouseEvent *); //объект класса будет испускать этот сигнал
protected:
 void mousePressEvent (QMouseEvent *event); //при нажатии кнопки мыши
private:
 int t; //"номер" кнопки , будем их различать по номерам,
        //если их много
public:
 void setTag(int); //метод для установки номера кнопки
 int tag(void);    //и для получения
};

#endif // CLICKABLELABEL_H
