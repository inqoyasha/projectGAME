#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <QQuickItem>
#include <QQuickPaintedItem>
#include <QColor>

class GameField : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
public:
    explicit GameField(QQuickItem *parent = nullptr);
    void paint(QPainter *painter) Q_DECL_OVERRIDE;
    QColor color() const;
    void setColor(QColor color);

signals:
    void colorChanged(QColor color);
public slots:
private:
    QColor m_color = QColor("grey");

};

#endif // GAMEFIELD_H
