#ifndef GAMEFIELDMODEL_H
#define GAMEFIELDMODEL_H

#include <QAbstractListModel>
#include <QVector>
#include <QDebug>
#include <QList>
#include <QFile>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonDocument>


class GameFieldModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(qint32 step READ step NOTIFY stepChanged)
    Q_PROPERTY(qint32 boxes READ boxes NOTIFY boxesChanged)
    Q_PROPERTY(qint32 boxesOnPosition READ boxesOnPosition NOTIFY boxesOnPositionChanged)
    Q_PROPERTY(qint32 lvlCount READ lvlCount NOTIFY lvlCountChanged)
    Q_PROPERTY(bool   isComplete READ isComplete NOTIFY isCompleteChanged)

public:
    explicit GameFieldModel(QObject *parent = nullptr);

    enum {
        iconSourceRole = Qt::UserRole + 1,
    };

    enum eField {
        EMPTY,
        BOX,
        WALL,
        PLAYER,
        BOX_POSITION,
        BOX_ON_POSITION,
        PLAYER_ON_POSITION
    };

    Q_INVOKABLE void moveUp();
    Q_INVOKABLE void moveDown();
    Q_INVOKABLE void moveLeft();
    Q_INVOKABLE void moveRight();
    Q_INVOKABLE void firstLevel();

    Q_INVOKABLE void nextLevel();

    Q_INVOKABLE void stepBack();

    bool isComplete();

    qint32 step(); //sdelannie shagi
    qint32 boxes(); //skolko mest pod gruz = yashikov
    qint32 boxesOnPosition(); //skolko mest zanyato
    qint32 lvlCount(); // lvl

    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;
    Q_INVOKABLE bool saveGame() const;
    Q_INVOKABLE bool loadGame();

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;

    // Editable:
    QHash<int, QByteArray> roleNames() const override;

signals:
    void stepChanged(qint32 m_stepsCount);
    void boxesChanged(qint32 m_boxPosition);
    void boxesOnPositionChanged(qint32 m_boxOnPosition);
    void isCompleteChanged(bool m_isComplete);
    void lvlCountChanged(qint32 m_lvlCount);
private:
    void moveObject(qint32 offsetPlayerIcon, qint32 offsetIconAfterPlayerIcon);

    const QModelIndex parent;

    QVector<QVector<eField>> m_fieldMemory;
    QList<qint32> m_playerPositionMemory;
    QList<qint32> m_boxOnPositionMemory;

    QVector<eField> m_field;
    QVector<eField> m_fieldBefore;

    QVector<eField> m_fieldDeltaPos;
    QVector<qint32> m_fieldDeltaIndex;

    QVector<QVector<eField>> m_fieldPos;
    QVector<QVector<qint32>> m_fieldIndex;

    qint32 m_columns = 8;
    qint32 m_rows = 8;
    qint32 m_playerPosition = 26;
    qint32 m_boxPosition = 2;
    qint32 m_stepsCount = 0;
    qint32 m_boxOnPosition = 0;
    qint32 m_lvlCount = 1;
    bool   m_isComplete = false;
};

#endif // GAMEFIELDMODEL_H
