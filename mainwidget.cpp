#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QHeaderView>
#include "scores.h"
#include "QDebug"
#include <QFile>
#include <QDir>
Mainwidget::Mainwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Mainwidget)
{
    ui->setupUi(this);
    m_subjectCross = new Subject();
    m_subjectZero = new Subject();
    m_scores = new Scores();
    m_subjectCross->setImage("/home/aleksun/parea/A5_2019/krest.jpg");
    m_subjectZero->setImage("/home/aleksun/parea/A5_2019/nolik_low.png");
    m_subjectCross->setIdDrag("application/krest");
    m_subjectZero->setIdDrag("application/zero");
    m_subjectZero->setEnabled(false);
    ui->verticalLayout->insertWidget(0,m_subjectCross);
    ui->verticalLayout->insertWidget(1,m_subjectZero);
    ui->verticalLayout->insertWidget(2, m_scores);

    m_table = new Table(this);
    m_table->setRowCount(3);
    m_table->setColumnCount(3);
    m_table->verticalHeader()->setVisible(false);
    m_table->horizontalHeader()->setVisible(false);
    for (int i = 0; i < m_table->rowCount(); i++)
        m_table->setRowHeight(i, 100);
    for (int i = 0; i < m_table->columnCount(); i++)
        m_table->setColumnWidth(i, 100);
    m_table->setFixedSize(302, 302);
    ui->horizontalLayout_2->insertWidget(0,m_table);
    connect(m_table, SIGNAL(setCross()), this, SLOT(setDisabledCross()));
    connect(m_table, SIGNAL(setZero()), this, SLOT(setDisabledZero()));
    connect(m_table, SIGNAL(setDisabledCrossZero()), this, SLOT(setDisabledCrossZero()));
    connect(m_table, SIGNAL(changeScores(int, int)), m_scores, SLOT(changeScores(int, int)));
}

currentStep Mainwidget::stringToEnum(QString sign)
{
    if(sign == "CROSS") return CROSS;
    if(sign == "ZERO") return ZERO;
    if(sign == "NOONE") return NOONE;
    return ERROR;
}

Mainwidget::~Mainwidget()
{
    delete ui;
}

void Mainwidget::setDisabledCross()
{
    m_subjectCross->setEnabled(false);
    m_subjectCross->setImage("/home/aleksun/parea/A5_2019/krest_low.jpg");
    m_subjectZero->setEnabled(true);
    m_subjectZero->setImage("/home/aleksun/parea/A5_2019/nolik.png");
}

void Mainwidget::setDisabledZero()
{
    m_subjectCross->setEnabled(true);
    m_subjectCross->setImage("/home/aleksun/parea/A5_2019/krest.jpg");
    m_subjectZero->setEnabled(false);
    m_subjectZero->setImage("/home/aleksun/parea/A5_2019/nolik_low.png");
}

void Mainwidget::setDisabledCrossZero()
{
    m_subjectCross->setEnabled(false);
    m_subjectCross->setImage("/home/aleksun/parea/A5_2019/krest_low.jpg");
    m_subjectZero->setEnabled(false);
    m_subjectZero->setImage("/home/aleksun/parea/A5_2019/nolik_low.png");
}

void Mainwidget::clickedPlayAgain()
{
    m_table->setBotMode(false);
    m_table->startAgain();
    setDisabledZero();
}

bool Mainwidget::clickedSave()
{
    QDir buildDir("");
    QFile *file = new QFile(buildDir.absolutePath()+"/save.txt");
    file->resize(0);
    file->open(QIODevice::Append);
    if(!file->isOpen())
    {
        qDebug() << "Error";
        return true;
    }
    QString writeFile = QString::number(m_scores->getScoresX())+" "+QString::number(m_scores->getScoresO())+"\n";
    file->write(writeFile.toUtf8());

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            writeFile = m_table->getTable(i, j);
            file->write(writeFile.toUtf8()+" ");

        }
        if(i == 2)
        {
            writeFile = m_table->getCurrentStep();
            file->write(writeFile.toUtf8());
        }
        file->write("\n");
    }
    if(m_table->getBotMode())
        file->write("AI");
    else
        file->write("NONAI");
    file->close();
    delete file;
    qDebug() << "Saved in " << buildDir.absolutePath()+"/save.txt";
    return true;
}

bool Mainwidget::clickedLoad()
{
    QDir buildDir("");
    int scoresX;
    int scoresO;
    QString currentStepLoad;
    QFile *file = new QFile(buildDir.absolutePath()+"/save.txt");
    QTextStream readFile(file);
    file->open(QIODevice::ReadOnly);
    if(!file->isOpen())
    {
        qDebug() << "No file";
        file->close();
        return false;
    }
    QString line = readFile.readLine();
    QStringList lineSplit = line.split(" ");
    scoresX = lineSplit[0].toInt();
    scoresO = lineSplit[1].toInt();
    m_scores->setScores(scoresX, scoresO);
    for(int i = 0; i < 3; i++)
    {
        line = readFile.readLine();
        lineSplit = line.split(" ");
        for(int j = 0; j < 3; j++)
        {
            if(lineSplit[j] == 'X')
                m_table->setSignInTable('X', i, j);
            else if(lineSplit[j] == 'O')
                m_table->setSignInTable('O', i, j);
            else
                m_table->setSignInTable('1', i, j);
        }
        if(i == 2)
            currentStepLoad = lineSplit[3];
    }
    if(currentStepLoad == "ERROR")
    {
        qDebug() << "ERROR";
        file->close();
        return false;
    }
    line = readFile.readLine();
    if(line == "AI")
        m_table->setBotMode(true);
    else if(line == "NONAI")
        m_table->setBotMode(false);
    else
    {
        qDebug() << "ERROR READING GAMEMODE";
        file->close();
        return false;
    }
    m_table->setCurrentStep(stringToEnum(currentStepLoad));
    m_table->redrawTable();
    file->close();
    delete file;
    return true;
}

bool Mainwidget::clickedPlayBot()
{
    m_table->setBotMode(true);
    m_table->startAgain();
    return true;
}



