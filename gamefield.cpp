#include "gamefield.h"

#include <QPainterPath>
#include <QPainter>
#include <QDebug>

GameField::GameField(QQuickItem *parent)
    :QQuickPaintedItem(parent)
{
}

void GameField::paint(QPainter *painter)
{
    map();
    draw_grid(painter);
    draw_objects(painter);
}

void GameField::draw_grid(QPainter *painter)
{
    for (int i=0; i<=m_columns; ++i) {
        painter->drawLine((width()/m_columns)*i, 0, (width()/m_columns)*i, height());
    }
    for (int i=0; i<=m_rows; ++i) {
        painter->drawLine(0, (height()/m_rows)*i, width(), (height()/m_rows)*i);
    }
}

void GameField::draw_objects(QPainter *painter)
{
    for (int r=0;r<m_rows;++r) {
        for (int c=0;c<m_columns;++c ) {
            switch (m_field[(r*m_columns)+c]) {
                case BOX:
                    painter->fillRect((width()/m_columns)*c, (height()/m_rows)*r, (width()/m_columns), (height()/m_rows),Qt::blue);
                    break;
                case WALL:
                    painter->fillRect((width()/m_columns)*c, (height()/m_rows)*r, (width()/m_columns), (height()/m_rows),Qt::black);
                    break;
                case PLAYER:
                    m_playerPosition = (r*m_columns)+c;
                    painter->fillRect((width()/m_columns)*c, (height()/m_rows)*r, (width()/m_columns), (height()/m_rows),Qt::red);
                    break;
                case EMPTY:
                    painter->fillRect((width()/m_columns)*c, (height()/m_rows)*r, (width()/m_columns), (height()/m_rows),Qt::white);
                    break;
                case BOX_POSITION:
                    painter->fillRect((width()/m_columns)*c, (height()/m_rows)*r, (width()/m_columns), (height()/m_rows),Qt::yellow);
                    break;
                case PLAYER_ON_POSITION:{
                    painter->fillRect((width()/m_columns)*c, (height()/m_rows)*r, (width()/m_columns), (height()/m_rows),Qt::gray);
                    break;
                }
                case BOX_ON_POSITION:{
                    painter->fillRect((width()/m_columns)*c, (height()/m_rows)*r, (width()/m_columns), (height()/m_rows),Qt::cyan);
                    break;
                }
            }
        }
    }

}
void GameField::map()
{
    for (int i=0; i<m_columns; ++i) m_field.append(WALL);

    m_field.append(WALL);
    for (int i=0; i<m_columns-2; ++i) m_field.append(EMPTY);
    m_field.append(WALL);

//    for (int i=0; i<m_columns; ++i) m_field.append(EMPTY);
//    for (int i=0; i<m_columns; ++i) m_field.append(EMPTY);

    m_field.append(WALL);
    m_field.append(PLAYER);
    m_field.append(EMPTY);
    m_field.append(BOX);
    m_field.append(EMPTY);
    m_field.append(WALL);

    m_field.append(WALL);
    m_field.append(EMPTY);
    m_field.append(EMPTY);
    m_field.append(BOX_POSITION);
    m_field.append(EMPTY);
    m_field.append(WALL);

//    for (int i=0; i<m_columns; ++i) m_field.append(EMPTY);
//    for (int i=0; i<m_columns; ++i) m_field.append(EMPTY);

    m_field.append(WALL);
    for (int i=0; i<m_columns-2; ++i) m_field.append(EMPTY);
    m_field.append(WALL);

    for (int i=0; i<m_columns; ++i) m_field.append(WALL);
}

void GameField::stepBack()
{
}

void GameField::moveObject(int offset, int offset2)
{
    int np = m_playerPosition + offset; //next line
    int nnp = m_playerPosition + offset2; //next next line

    qDebug() << "c"<< m_playerPosition;
    qDebug() << "n"<< np;
    qDebug() << "nn"<<nnp;

    auto &p = m_field[m_playerPosition];
    auto &op = m_field[np];
    auto &oop = m_field[nnp];

    switch(op) {
        case EMPTY: {
            p == PLAYER ? p = EMPTY : p = BOX_POSITION;
            op = PLAYER;         
            break;
        }
        case BOX_POSITION:{
            p == PLAYER ? p = EMPTY: p = BOX_POSITION;
            op = PLAYER_ON_POSITION;
            break;
        }
        case BOX_ON_POSITION: {
            if(oop == BOX_POSITION){
                p == PLAYER ? p = EMPTY: p = BOX_POSITION;
                op = PLAYER_ON_POSITION;
                oop = BOX_ON_POSITION;
                break;
            }
            if (oop == EMPTY) {
                p == PLAYER ? p = EMPTY: p = BOX_POSITION;
                op = PLAYER_ON_POSITION;
                oop = BOX;
                break;
            }
            break;
        }
        case BOX: {
            if(oop == BOX_POSITION) {
                    p == PLAYER ? p = EMPTY : p = BOX_POSITION;
                    op = PLAYER;
                    oop = BOX_ON_POSITION;
                    break;
                }
            if(oop == EMPTY) {
                   p == PLAYER ? p = EMPTY : p = BOX_POSITION;
                   op = PLAYER;
                   oop = BOX;
                   break;
                 }
            break;
        }
        case PLAYER_ON_POSITION:
        case WALL:
        case PLAYER:
        break;
    }
}

void GameField::moveUp()
{
    moveObject(-m_columns, -m_columns*2);
    qDebug() << "moveUp";
    qDebug() << "";
    update();
}

void GameField::moveDown()
{
    moveObject(m_columns, m_columns*2);
    qDebug() << "moveDown";
    qDebug() << "";
    update();
   }

void GameField::moveLeft()
{
    moveObject(-1, -2);
    qDebug() << "moveLeft";
    qDebug() << "";
    update();
}

void GameField::moveRight()
{
    moveObject(1, 2);
    qDebug() << "moveRight";
    qDebug() << "";
    update();
}

bool GameField::isComplete()
{
    return m_isComplete;
}

qint32 GameField::stepsCount()
{
    return m_stepsCount;
}

qint32 GameField::boxPosition()
{
    return m_boxPosition;
}

qint32 GameField::boxOnPosition()
{
    return m_boxOnPosition;
}





