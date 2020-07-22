#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QPushButton>
#include <QList>
#include <QLabel>
#include <QtDebug>
#include <QStringList>
#include <QInputDialog>
#include <QLineEdit>
#include <QTimeLine>
#include <QGraphicsItemAnimation>
#include <triangle.h>
#include <clickablelabel.h>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    QList<ClickableLabel*> *toDoList;
    void addToDoList(ClickableLabel*);
    void delFromDoList(int);
    enum RequestTypes{
            up,
            down,
            left,
            right
    };

    QWidget *m_popup;

    ~Widget();

private:
    Ui::Widget      *ui;
    QGraphicsScene  *scene;     // Объявляем графическую сцену
    Triangle        *triangle;  // и треугольник
public slots:
    void createLabel();
    void startToDoList();

    void labelClicked (QMouseEvent *event);
};

#endif // WIDGET_H
