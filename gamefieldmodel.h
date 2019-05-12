#ifndef GAMEFIELDMODEL_H
#define GAMEFIELDMODEL_H

#include <QAbstractListModel>
#include <QVector>
#include <QDebug>

class GameFieldModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit GameFieldModel(QObject *parent = nullptr);

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


    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
//    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
//    Qt::ItemFlags flags(const QModelIndex& index) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
//    QVector<QVector<eField>> m_field;
    QVector<eField> m_field;
    qint32 m_columns = 8;
    qint32 m_rows = 8;
    qint32 m_playerPosition = 27;
};

#endif // GAMEFIELDMODEL_H
