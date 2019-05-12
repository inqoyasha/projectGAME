#include "gamefieldmodel.h"

GameFieldModel::GameFieldModel(QObject *parent)
    : QAbstractListModel(parent)
{
    m_field.append({WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL});
    m_field.append({WALL,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,BOX_POSITION,WALL});
    m_field.append({WALL,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,BOX,WALL});
    m_field.append({WALL,EMPTY,PLAYER,WALL,BOX,EMPTY,EMPTY,WALL});
    m_field.append({WALL,EMPTY,EMPTY,WALL,BOX_POSITION,EMPTY,EMPTY,WALL});
    m_field.append({WALL,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL});
    m_field.append({WALL,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL});
    m_field.append({WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL});

}

int GameFieldModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_field.size();
}

//int GameFieldModel::columnCount(const QModelIndex &parent) const
//{
//    if (parent.isValid())
//        return 0;

//    return m_field.at(0).size();
//}

QVariant GameFieldModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    eField value = m_field.at(index.row());//.at(index.column());

    switch(role){
        case DisplayRole:
            return value;
        case emptyRole:
             if (value == EMPTY)
                return QVariant ("white");
        case wallRole:
             if (value == WALL)
                return QVariant ("orange");
        case playerRole:
             if (value == PLAYER)
                return QVariant ("red");
        case boxRole:
             if (value == BOX)
                return QVariant ("blue");
        case boxPositionRole:
             if (value == BOX_POSITION)
                return QVariant ("yellow");
        case boxOnPositionRole:
             if (value == BOX_ON_POSITION)
                return QVariant ("lightblue");
        case playerOnPositionRole:
             if (value == PLAYER_ON_POSITION)
                return QVariant ("gray");
        }
    return QVariant();
}



//Qt::ItemFlags GameFieldModel::flags(const QModelIndex &index) const
//{
//    if (!index.isValid())
//        return Qt::NoItemFlags;

//    return Qt::ItemIsEditable;
//}

QHash<int, QByteArray> GameFieldModel::roleNames() const
{
    QHash<int,QByteArray> roles;
    roles[DisplayRole] = "value";
    roles[emptyRole] = "empty";
    roles[wallRole] = "wall";
    roles[boxRole] = "box";
    roles[playerOnPositionRole] = "playerOnPosition";
    roles[boxOnPositionRole] = "boxOnPosition";
    roles[boxPositionRole] = "boxPosition";
    roles[playerRole] = "player";
    return roles;
}


