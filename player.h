#ifndef PLAYER_H
#define PLAYER_H

#include <QQuickItem>
#include <QQuickPaintedItem>
#include <QColor>
#include <QKeyEvent>

class Player : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
  //  Q_PROPERTY(qreal x READ x WRITE setX NOTIFY xChanged FINAL)
   // Q_PROPERTY(qreal y READ y WRITE setY NOTIFY yChanged FINAL)
  //  Q_PROPERTY(qreal z READ z WRITE setZ NOTIFY zChanged FINAL)
public:
    explicit Player(QQuickItem *parent = nullptr);
    void paint(QPainter *painter) Q_DECL_OVERRIDE;
 //   void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry) Q_DECL_OVERRIDE;

    Q_INVOKABLE void moveUp();
    Q_INVOKABLE void moveDown();
    Q_INVOKABLE void moveLeft();
    Q_INVOKABLE void moveRight();
signals:
    void colorChanged(QColor color);
    void xChanged(qreal x);
    void yChanged(qreal y);
    void zChanged(qreal z);
public slots:
    QColor color() const;
    void setColor(QColor color);

    qreal x() const;
    qreal y() const;
    qreal z() const;

    void setX(qreal x);
    void setY(qreal y);
    void setZ(qreal z);
private:
    QColor m_color = QColor("green");
    qreal m_x = 100;
    qreal m_y;
    qreal m_z;

};

#endif // PLAYER_H
