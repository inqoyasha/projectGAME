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
public:
    explicit Player(QQuickItem *parent = nullptr);
    void paint(QPainter *painter) Q_DECL_OVERRIDE;
    QColor color() const;
    void setColor(QColor color);
signals:
    void positionChanged();
    void colorChanged(QColor color);
public slots:
private:
    void keyPressEvent(QKeyEvent *event) override;
    QColor m_color = QColor("green");

};

#endif // PLAYER_H
