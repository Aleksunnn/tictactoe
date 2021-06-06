#include "subject.h"
#include "ui_subject.h"
#include <QDebug>
#include <QMouseEvent>
#include <QMimeData>
#include <QPainter>
Subject::Subject(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Subject)
{
    ui->setupUi(this);
    setFixedSize(100, 100);
    m_id = "application/subject";
    m_zeroPicPath = "/home/aleksun/parea/A5_2019/nolik.png";
    m_crossPicPath = "/home/aleksun/parea/A5_2019/krest.jpg";
}

Subject::~Subject()
{
    delete ui;
}
bool Subject::setImage(QString data)
{
    m_pixmap.load(data);
    return true;
}

bool Subject::setStateDrag(bool state)
{
    m_stateDrag = state;
    return true;
}

bool Subject::setIdDrag(QString id)
{
    m_id = id;
    return true;
}

bool Subject::setAnotherPic(QString crossPath, QString zeroPath)
{
    m_crossPicPath = crossPath;
    m_zeroPicPath = zeroPath;
    return true;
}

QString Subject::getCrossPic()
{
    return m_crossPicPath;
}

QString Subject::getZeroPic()
{
    return m_zeroPicPath;
}

void Subject::mousePressEvent(QMouseEvent *event)
{
   // qDebug() << "mousePressEvent";
    m_startDrag = event->pos();
    QWidget::mousePressEvent(event);
}
void Subject::mouseMoveEvent(QMouseEvent *event)
{
   // qDebug() << "mouseMoveEvent";
    if((event->buttons()&Qt::LeftButton)
            && QApplication::startDragDistance()<=
            (event->pos() - m_startDrag ).manhattanLength()
            && m_stateDrag)
    {
     //   qDebug() << "mouseMoveEvent!!!";
        makeDrag()->exec(Qt::MoveAction);
    }
    QWidget::mouseMoveEvent(event);
}

void Subject::paintEvent(QPaintEvent *event)
{
    //qDebug()<<"paintEvent";
    QPainter painter(this);
    if(!m_pixmap.isNull())
    {
        QSize widgetSize = size();
        QPixmap scaledPixmap = m_pixmap.scaled(widgetSize, Qt::KeepAspectRatio);
        QPoint center((widgetSize.width()-scaledPixmap.width())/2,
                      (widgetSize.height()-scaledPixmap.height())/2);
        painter.drawPixmap(center, scaledPixmap);
    }
    QWidget::paintEvent(event);
}

QDrag *Subject::makeDrag()
{
    QDrag *drag = new QDrag(this);
    QByteArray itemData;
    QDataStream stream(&itemData, QIODevice::WriteOnly);
    QMimeData *mimeData = new QMimeData;
    mimeData->setData(m_id, itemData);
    drag->setMimeData(mimeData);
    drag->setPixmap(m_pixmap.scaled(size(),Qt::KeepAspectRatio));
    return drag;
}
