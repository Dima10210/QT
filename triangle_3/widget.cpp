#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{




    ui->setupUi(this);
    this->resize(600,600);          // Задаем размеры виджета, то есть окна
    this->setFixedSize(600,600);    // Фиксируем размеры виджета

    scene = new QGraphicsScene();   // Инициализируем графическую сцену
    triangle = new Triangle();      // Инициализируем треугольник

    ui->graphicsView->setScene(scene);  // Устанавливаем графическую сцену в graphicsView
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);    // Устанавливаем сглаживание
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Отключаем скроллбар по вертикали
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Отключаем скроллбар по горизонтали

    scene->setSceneRect(-250,-250,500,500); // Устанавливаем область графической сцены

    scene->addItem(triangle);   // Добавляем на сцену треугольник
    triangle->setPos(0,0);      // Устанавливаем треугольник в центр сцены

    m_popup = new QWidget(0);  //Создание нового окна
    m_popup->setGeometry(0, 0, 600, 600);
    QPushButton *add = new QPushButton(m_popup); //Добавление кнопки на новом окне
    add->setText("add");
    QPushButton *start = new QPushButton(m_popup);
    start->setText("Start");
    start->move(0,50);
    connect(add, SIGNAL (released()),this, SLOT (createLabel()));  //Призязка нажатия кнопок к действиям
    connect(start, SIGNAL (released()),this, SLOT (startToDoList()));
    m_popup->show();
    this->toDoList = new QList<ClickableLabel*>;  //Создание списка всех Лейблов

}

void Widget::addToDoList(ClickableLabel *label)
{
    this->toDoList->append(label);
}

void Widget::delFromDoList(int i)
{
    this->toDoList->removeAt(i);
}

void Widget::createLabel()
{
    ClickableLabel *label = new ClickableLabel("up 20",this->m_popup);//Добавление лейбла на форму
    label->move(100,this->toDoList->size()*20);//Перемещение на необходимые координаты
    label->show();
    label->resize(35,20);
    label->setTag(toDoList->size());//Задание номера лейбла
    connect(label, SIGNAL(clicked(QMouseEvent*)),this, SLOT(labelClicked(QMouseEvent*)));//Привязка события щелчка по лейблу с функцией обработчиком
    label->setStyleSheet("QLabel {"
                                 "border-style: solid;"
                                 "border-width: 1px;"
                                 "border-color: black; "
                                 "}");

    this->addToDoList(label);//Добавление лейбла в список
}

void Widget::startToDoList()//Функция исполнения действий из списка
{
    if(!this->toDoList->size())return;
    float j = 1.0/toDoList->size();//Разбиение на шаги для анимации
    float i = j;
    QTimeLine *timer = new QTimeLine(toDoList->size()*1000, this);//Создание таймера анимации
    QGraphicsItemAnimation *animation = new QGraphicsItemAnimation(timer);
    animation->setItem(this->triangle);//Привязка Анимации к объекту
    animation->setTimeLine(timer);
    QPointF eventPos(this->triangle->pos());//Получение текущей позиции объекта
    for (QLabel *var : *this->toDoList) {
        QStringList list = var->text().split(QRegExp("\\s+"), QString::SkipEmptyParts);//Парсинг лейблов на команды
        if(list.size()){
            QString command = list.at(0);


            if(list.at(0)=="up")
                eventPos.setY(eventPos.ry()-list.at(1).toInt());   //Создание позиции для перемещения
            else if(list.at(0)=="down")
                eventPos.setY(eventPos.ry()+list.at(1).toInt());
            else if(list.at(0)=="right")
                eventPos.setX(eventPos.rx()+list.at(1).toInt());
            else if(list.at(0)=="left")
                eventPos.setX(eventPos.rx()-list.at(1).toInt());
            animation->setPosAt(i, eventPos);//Добавление позиции перемещения в очередь i это шаг изменяется от 0 до 1.0

            i+=j;
        }


    }
    timer->start();//Запуск анимации
}



void Widget::labelClicked(QMouseEvent *event)//Обработка щелчка по лейблу
{
    int i=((ClickableLabel *)sender())->tag();//Получаем номер лейбла по которому кликнули
    if(event->buttons() == Qt::LeftButton){//Обрабатываем щелчок левой кнопкой мыши
        QInputDialog a;
        QString text = a.getText(this,"Get text","Example of command is:\ndown 40\nright 15\nleft 10",QLineEdit().Normal,"up 20");
        QStringList list = text.split(QRegExp("\\s+"), QString::SkipEmptyParts);
        if(list.size()!=2)return;
        toDoList->at(i)->setText(text);
        toDoList->at(i)->resize(text.size()*7,20);
    }
    if(event->buttons() == Qt::RightButton){//Обработка правым щелчком
        toDoList->removeAt(i);
        delete (ClickableLabel *)sender();//Удаление лейбла по которому кликнули
        if(i == (toDoList->size()-1)){
            return;
        }
        else{
            int j = toDoList->size();
            for (int i = 0;i < j;i++) {//Перемещение лейблов и их номеров, в случае если был удален не последний элемент списка
                ClickableLabel* a= toDoList->at(i);
                a->setTag(i);
                a->move(100,i*20);
            }
        }
    }
}

Widget::~Widget()
{
    delete ui;
}
