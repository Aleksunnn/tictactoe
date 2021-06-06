#ifndef SCORES_H
#define SCORES_H

#include <QWidget>
#include <QFile>

namespace Ui {
class Scores;
}

class Scores : public QWidget
{
    Q_OBJECT

public:
    explicit Scores(QWidget *parent = nullptr);
    int getScoresX();
    int getScoresO();
    void setScoresInWindow();
    ~Scores();

public slots:
    void setScores(int scoresX, int scoresO);
    void changeScores(int scoresX, int scoresO);
private:
    Ui::Scores *ui;
    int m_scoresX;
    int m_scoresO;

};

#endif // SCORES_H
