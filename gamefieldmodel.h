#ifndef GAMEFIELDMODEL_H
#define GAMEFIELDMODEL_H

#include <QAbstractListModel>
#include <QVector>
#include <QDebug>

#include "gamefield.h"

class GameFieldModel : public QAbstractListModel
{
    Q_OBJECT

public:    
    explicit GameFieldModel(QObject *parent = nullptr);


    class GameField;

    enum {
        DisplayRole,
        emptyRole = Qt::UserRole + 1,
        boxRole,
        wallRole,
        playerRole,
        boxPositionRole,
        boxOnPositionRole,
        playerOnPositionRole
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



    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
//    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
//    Qt::ItemFlags flags(const QModelIndex& index) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    void moveObject(int offset, int offset2);
    GameField *mField;
//    QVector<QVector<eField>> m_field;
    QVector<eField> m_field;
    qint32 m_columns = 8;
    qint32 m_rows = 8;
    qint32 m_playerPosition = 26;
};

#endif // GAMEFIELDMODEL_H
