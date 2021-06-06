#include "scores.h"
#include "ui_scores.h"
#include <QDebug>

Scores::Scores(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Scores)
{
    ui->setupUi(this);
    setFixedSize(100,100);
    ui->lineEdit->setReadOnly(true);
    ui->lineEdit_2->setReadOnly(true);
    ui->lineEdit_3->setReadOnly(true);

    ui->lineEdit->setFrame(false);
    ui->lineEdit_2->setFrame(false);
    ui->lineEdit_3->setFrame(false);

    ui->lineEdit->setText("Scores");
    ui->lineEdit_2->setText("X: 0");
    ui->lineEdit_3->setText("O: 0");
    m_scoresO = 0;
    m_scoresX = 0;
}


int Scores::getScoresX()
{
    return m_scoresX;
}

int Scores::getScoresO()
{
    return m_scoresO;
}

void Scores::setScores(int scoresX, int scoresO)
{
    m_scoresX = scoresX;
    m_scoresO = scoresO;
    setScoresInWindow();
}

void Scores::changeScores(int scoresX, int scoresO)
{
    m_scoresX += scoresX;
    m_scoresO += scoresO;
    setScoresInWindow();
}

Scores::~Scores()
{
    delete ui;
}

void Scores::setScoresInWindow()
{
    ui->lineEdit_2->setText("X: "+QString::number(m_scoresX));
    ui->lineEdit_3->setText("O: "+QString::number(m_scoresO));
}
