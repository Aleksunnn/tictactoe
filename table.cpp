#include "table.h"
#include <QDebug>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QLabel>
#include "subject.h"
#include <vector>

Table::Table(QWidget *parent) : QTableWidget(parent){
    setAcceptDrops(true);
    setDragEnabled(true);
    setDragDropMode(QAbstractItemView::InternalMove);
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            m_field[i][j] = '1';

}

void Table::setSignInTable(char sign, int xPos, int yPos)
{
    m_field[xPos][yPos] = sign;
}

void Table::writeWinner(QString winner)
{
    if(winner != 'D')
        qDebug() << winner+" WIN";
    else
        qDebug() << "DRAW";
    if(winner == 'X')
        emit changeScores(10, 0);
    else if(winner == 'O')
        emit changeScores(0, 10);
    else
        emit changeScores(5, 5);
    emit disable();
    m_currentStep = NOONE;
}

void Table::startAgain()
{
    for(int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            m_field[i][j] = '1';
            removeCellWidget(i, j);
            emit setZero();
            m_currentStep = CROSS;
        }
    }
    if(m_bot == true)
    {
        int randomFirstStep = rand() % 2;
        if(randomFirstStep == 1) // бот ходит первым
            bestMove(1);
    }
}

bool Table::redrawTable()
{
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(m_field[i][j] == 'X')
            {
                Subject *sub = new Subject();
                sub->setImage("/home/aleksun/parea/A5_2019/krest.jpg");
                removeCellWidget(i, j);
                sub->setStateDrag(false);
                setCellWidget(i, j, sub);
            }
            else if(m_field[i][j] == 'O')
            {
                Subject *sub = new Subject();
                sub->setImage("/home/aleksun/parea/A5_2019/nolik.png");
                removeCellWidget(i, j);
                sub->setStateDrag(false);
                setCellWidget(i, j, sub);
            }
            else
                removeCellWidget(i, j);
        }
    }
    if(m_currentStep == CROSS)
        emit setZero();
    else if(m_currentStep == ZERO)
        emit setCross();
    else
        emit disable();
    return true;
}

QChar Table::getTable(int row, int column)
{
    return m_field[row][column];
}

QString Table::getCurrentStep()
{
    return enumToString(m_currentStep);
}


QString Table::enumToString(currentStep STEP)
{
    if(STEP == currentStep::CROSS) return "CROSS";
    if(STEP == currentStep::ZERO) return "ZERO";
    if(STEP == currentStep::NOONE) return "NOONE";
    return "ERROR";
}

void Table::setBotMode(bool bot)
{
    m_bot = bot;
}

void Table::bestMove(int player)
{
    //ходит компьютер
    if(checkWin() != 'D')
    {
        AIMove move = minimax(player);
        setSign(move.x, move.y, player);
    }
}

AIMove Table::minimax(int player)
{
    QChar result = checkWin();
    if(result == 'X')
        return AIMove(-10);
    else if(result == 'O')
        return AIMove(10);
    else if(result == 'D')
        return AIMove(0);

    QVector<AIMove> moves;

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(m_field[i][j] == '1')
            {
                AIMove move;
                move.x = i;
                move.y = j;
                if(player == 0)
                {
                    m_field[i][j] = 'O';
                    move.score = minimax(1).score;
                }
                else
                {
                    m_field[i][j] = 'X';
                    move.score = minimax(0).score;
                }
                moves.push_back(move);
                m_field[i][j] = '1';
            }
        }
    }

    int bestMove = 0;
    if(player == 0)
    {
        int bestScore = std::numeric_limits<int>::min();
        for(int i = 0; i < moves.size(); i++)
        {
            if(moves[i].score > bestScore)
            {
                bestMove = i;
                bestScore = moves[i].score;
            }
        }
    }
    else
    {
        int bestScore = std::numeric_limits<int>::max();
        for(int i = 0; i < moves.size(); i++)
        {
            if(moves[i].score < bestScore)
            {
                bestMove = i;
                bestScore = moves[i].score;
            }
        }
    }
    return moves[bestMove];
}

void Table::setSign(int i, int j, int player)
{
    Subject *sub = new Subject();
    if(player == 0)
    {
        sub->setImage("/home/aleksun/parea/A5_2019/nolik.png");
        setSignInTable('O', i, j);
        sub->setStateDrag(false);
        setCellWidget(i, j, sub);
        emit setZero();
        m_currentStep = CROSS;
    }
    else
    {
        sub->setImage("/home/aleksun/parea/A5_2019/krest.jpg");
        setSignInTable('X', i, j);
        sub->setStateDrag(false);
        setCellWidget(i, j, sub);
        emit setCross();
        m_currentStep = ZERO;
    }
    QChar winner = checkWin();
    if(winner != 'N')
    {
        QString stringWinner = winner;
        writeWinner(winner);
    }
}

QChar Table::checkWin()
{
    QChar winnerChar;
    for(int i = 0; i < 3; i++)
    {
        winnerChar = m_field[0][i];
        if(winnerChar == m_field[1][i] && winnerChar == m_field[2][i] && winnerChar != '1')
        {
            return winnerChar;
        }
    }
    for(int i = 0; i < 3; i++)
    {
        winnerChar = m_field[i][0];
        if(winnerChar == m_field[i][1] && winnerChar == m_field[i][2] && winnerChar != '1')
        {
            return winnerChar;
        }
    }
    winnerChar = m_field[0][0];
    if(winnerChar == m_field[1][1] && m_field[1][1] == m_field[2][2] && winnerChar != '1')
    {
        return winnerChar;
    }
    winnerChar = m_field[0][2];
    if(winnerChar == m_field[1][1] && m_field[1][1] == m_field[2][0] && winnerChar != '1')
    {
        return winnerChar;
    }
    int k = 0;
    for(int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if(m_field[i][j] == 'X' || m_field[i][j] == 'O')
                k++;
        }
    }
    if(k == 9)
    {
        return 'D';
    }
    return 'N';
}


bool Table::getBotMode()
{
    if(m_bot)
        return true;
    return false;
}

bool Table::setCurrentStep(currentStep STEP)
{
    m_currentStep = STEP;
    return true;
}

void Table::dragEnterEvent(QDragEnterEvent *event)
{
   // qDebug() <<"dragEnterEvent";
    if(event->mimeData()->hasFormat("application/krest") ||
            event->mimeData()->hasFormat("application/zero"))
    {
      //  qDebug() <<"acceptProposedAction";
        event->acceptProposedAction();
    }
    else
    {
        qDebug() <<"ignore";
         event->ignore();
    }
}
void Table::dropEvent(QDropEvent *event){
  //  qDebug() <<"dropEvent";
    QModelIndex index = indexAt(event->pos());
    if(!index.isValid())
    {
        qDebug() <<"index.isValid()";
        return;
    }
    qDebug() <<"row = "<<index.row() <<" col = "<<index.column();
    if(cellWidget(index.row(),index.column()) !=nullptr){
        qDebug() <<"widget already added";
        return;
    }
    Subject *sub = new Subject();
    if(event->mimeData()->hasFormat("application/krest"))
    {
        sub->setImage("/home/aleksun/parea/A5_2019/krest.jpg");
        setSignInTable('X', index.row(), index.column());
        emit setCross();
        m_currentStep = ZERO;
        //checkWin();
        QChar winner = checkWin();
        if(winner != 'N')
        {
            QString stringWinner = winner;
            writeWinner(winner);
        }
        else if(m_bot == true)
            bestMove(0);
    }
    else
    {
        sub->setImage("/home/aleksun/parea/A5_2019/nolik.png");
        setSignInTable('O', index.row(), index.column());
        emit setZero();
        m_currentStep = CROSS;
        //checkWin();
        QChar winner = checkWin();
        if(winner != 'N')
        {
            QString stringWinner = winner;
            writeWinner(winner);
        }
        else if(m_bot == true)
            bestMove(1);
    }

    sub->setStateDrag(false);
    setCellWidget(index.row(),index.column(),sub);
  //  qDebug() <<"widget added";
}
