#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <QQuickItem>
#include <QQuickPaintedItem>
#include <QColor>
#include <QLinkedList>

class GameField : public QQuickPaintedItem
{
    Q_OBJECT
public:
    explicit GameField(QQuickItem *parent = nullptr);
    void paint(QPainter *painter) Q_DECL_OVERRIDE; //otrisovka?

    void draw_grid(QPainter *painter);
    void draw_objects(QPainter *painter);
    void draw_stats(QPainter *painter);

    Q_INVOKABLE void map(); //karta
    Q_INVOKABLE void stepBack(); // shag nazad
    Q_INVOKABLE void moveUp();
    Q_INVOKABLE void moveDown();
    Q_INVOKABLE void moveLeft();
    Q_INVOKABLE void moveRight();
    bool isComplete();

    qint32 stepsCount(); //sdelannie shagi
    qint32 boxPosition(); //skolko mest pod gruz
    qint32 boxOnPosition(); //skolko mest zanyato

    enum eField {
        EMPTY,
        BOX,
        WALL,
        PLAYER,
        BOX_POSITION,
        BOX_ON_POSITION,
        PLAYER_ON_POSITION
    };

signals:
public slots:
private:
    void moveObject(int offset, int offset2);
    QVector<eField> m_field;
    qint32 m_columns = 6;
    qint32 m_rows = 6;
    qint32 m_stepsCount;
    qint32 m_boxPosition;
    qint32 m_boxOnPosition;
    bool   m_isComplete = false;
    qint32 m_playerPosition;
};

#endif // GAMEFIELD_H
