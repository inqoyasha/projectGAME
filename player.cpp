#include "player.h"

#include <QPainterPath>
#include <QPainter>
#include <QDebug>

Player::Player(QQuickItem *parent)
    :QQuickPaintedItem(parent)
{

}

void Player::paint(QPainter *painter)
{
    QPainterPath path;

    path.lineTo(width(),0);
    path.lineTo(width(),height());
    path.lineTo(0,height());
    painter->setPen(Qt::NoPen);
    painter->fillPath(path, QBrush(m_color));
}

QColor Player::color() const
{
    return m_color;
}

void Player::setColor(QColor color)
{
    if (m_color != color){
        m_color = color;
        emit colorChanged(m_color);
        update();
    }
}

void Player::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_W){
     //   move();
    }
    if (event->key() == Qt::Key_S){
    //    move();
    }
    if (event->key() == Qt::Key_A){
    //    move();
    }
    if (event->key() == Qt::Key_D){
     //   move();
    }
}
