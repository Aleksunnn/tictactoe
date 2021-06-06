#ifndef MAINWIDJET_H
#define MAINWIDJET_H
#include "subject.h"
#include "table.h"
#include <QWidget>
#include "scores.h"
#include <QFile>

namespace Ui {
class Mainwidget;
}

class Mainwidget : public QWidget
{
    Q_OBJECT

public:
    explicit Mainwidget(QWidget *parent = nullptr);
    currentStep stringToEnum(QString sign);
    ~Mainwidget();
public slots:
    void setDisabledCross();
    void setDisabledZero();
    void setDisabledCrossZero();
    void clickedPlayAgain();
    bool clickedSave();
    bool clickedLoad();
    bool clickedPlayBot();
  //  bool clickedAppVsOr();

private:
    Ui::Mainwidget *ui;
    Subject *m_subjectCross;
    Subject *m_subjectZero;
    Table *m_table;
    Scores *m_scores;
};

#endif // MAINWIDJET_H
