#ifndef TABLE_H
#define TABLE_H

#include <QWidget>
#include <QTableWidget>
#include <QFile>
#include <QTextStream>

enum currentStep
{
    CROSS,
    ZERO,
    NOONE,
    ERROR
};
struct AIMove
{
    AIMove() {}
    AIMove(int Score) : score(Score) {}
    int x;
    int y;
    int score;
};

class Table : public QTableWidget
{
    Q_OBJECT
public:
    explicit Table(QWidget *parent = nullptr);
    void setSignInTable(char sign, int xPos, int yPos);
    void writeWinner(QString winner);
    void startAgain();
    bool redrawTable();
    QChar getTable(int row, int column);
    QString getCurrentStep();
    QString enumToString(currentStep STEP);
    void setBotMode(bool bot);
    void bestMove(int player);
    AIMove minimax(int player);
    void setSign(int i, int j, int player);
    QChar checkWin();
    int scores(QChar sign);
    bool getBotMode();
    bool setCurrentStep(currentStep STEP);
signals:
    void setCross();
    void setZero();
    void disable();
    void changeScores(int scoresX, int scoresO);

protected:
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dropEvent(QDropEvent* event) override;
private:
    QChar m_field[3][3];
    bool m_bot = false;
    int m_bestScore;
    int m_score;
    QVector<int> m_vectorScores;
    currentStep m_currentStep = CROSS;
};

#endif // TABLE_H
