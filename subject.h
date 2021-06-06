#ifndef SUBJECT_H
#define SUBJECT_H
#include <QDrag>
#include <QWidget>

namespace Ui {
class Subject;
}

class Subject : public QWidget
{
    Q_OBJECT

public:
    explicit Subject(QWidget *parent = nullptr);
    ~Subject();
    bool setImage(QString data);
    bool setStateDrag(bool state);
    bool setIdDrag(QString id);
    bool setAnotherPic(QString crossPath, QString zeroPath);
    QString getCrossPic();
    QString getZeroPic();

protected:
    void mousePressEvent (QMouseEvent* event) override;
    void mouseMoveEvent (QMouseEvent* event) override;
    void paintEvent(QPaintEvent *event) override;
    QDrag * makeDrag();

private:
    Ui::Subject *ui;
    QPoint m_startDrag;
    QPixmap m_pixmap;
    bool m_stateDrag = true;
    QString m_id;
    QString m_crossPicPath;
    QString m_zeroPicPath;
};

#endif // SUBJECT_H
