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

qreal Player::x() const
{
    return m_x;
}

qreal Player::y() const
{
    return m_y;
}

qreal Player::z() const
{
    return m_z;
}

void Player::setX(qreal x)
{
    if (m_x == x)
        return;
    m_x = x;
    emit xChanged(m_x);
    update();
}

void Player::setY(qreal y)
{
    if (m_y != y){
        m_y = y;
        emit yChanged(m_y);
        update();

    }
}

void Player::setZ(qreal z)
{
    if (m_z != z){
        m_z = z;
        emit xChanged(m_z);
        update();

    }
}

void Player::moveUp()
{
    qDebug() << "moveUp";
    setColor(Qt::red);

}
void Player::moveDown()
{
    qDebug() << "moveDown";
    setColor(Qt::yellow);
   // setX(200);
  // setY(100);
}
void Player::moveLeft()
{
    qDebug() << "moveLeft";
    setColor(Qt::blue);
}
void Player::moveRight()
{
    qDebug() << "moveRight";
    setColor(Qt::black);
}



