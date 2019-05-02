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
    reset();
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
    for (auto i = m_field.begin(); i != m_field.end(); ++i) {
        switch (*i) {
            case BOX:
                qDebug() << "я вызвалсяB";
                painter->fillRect((width()/6)*3, (height()/6)*2, (width()/6), (height()/6),Qt::blue);
                break;
            case WALL:
                qDebug() << "я вызвалсяW";
                painter->fillRect(0, 0, width()/6, height()/6,Qt::black);
                break;
            case PLAYER:
                qDebug() << "я вызвалсяP";
                painter->fillRect(width()/6, (height()/6)*2, (width()/6), (height()/6),Qt::red);
                break;
            case EMPTY:
                qDebug() << "я вызвалсяE";
                painter->fillRect(width(), 0, width(), height(),Qt::white);
                break;
            case BOX_POSITION:
                qDebug() << "я вызвалсяBP";
                painter->fillRect((width()/6)*3, (height()/6)*3, width()/6, height()/6,Qt::yellow);
                break;
        }
    }
}

void GameField::reset()
{
    for (int i=0; i<6; ++i) m_field.append(WALL);

    m_field.append(WALL);
    for (int i=0; i<4; ++i) m_field.append(EMPTY);
    m_field.append(WALL);

    m_field.append(WALL);
    m_field.append(PLAYER);
    m_field.append(WALL);
    m_field.append(BOX);
    m_field.append(EMPTY);
    m_field.append(WALL);

    m_field.append(WALL);
    m_field.append(EMPTY);
    m_field.append(WALL);
    m_field.append(BOX_POSITION);
    m_field.append(EMPTY);
    m_field.append(WALL);

    m_field.append(WALL);
    for (int i=0; i<4; ++i) m_field.append(EMPTY);
    m_field.append(WALL);

    for (int i=0; i<6; ++i) m_field.append(WALL);

    for (auto i = m_field.begin(); i != m_field.end(); ++i) {
        qDebug() << *i;
    }
}

void GameField::stepBack()
{
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


