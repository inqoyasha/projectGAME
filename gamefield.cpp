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
    QPainterPath path;

    path.lineTo(width(),0);
    path.lineTo(width(),height());
    path.lineTo(0,height());
    painter->setPen(Qt::NoPen);
    painter->fillPath(path, QBrush(m_color));
}

QColor GameField::color() const
{
    return m_color;
}

void GameField::setColor(QColor color)
{
    if (m_color != color){
        m_color = color;
        emit colorChanged(m_color);
        update();
    }
}
