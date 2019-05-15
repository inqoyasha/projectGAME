#include "gamefieldmodel.h"

GameFieldModel::GameFieldModel(QObject *parent)
    : QAbstractListModel(parent)
//    , mField(nullptr)
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
                return QVariant ("pics/empty.png");//QVariant ("white");
        case wallRole:
             if (value == WALL)
                return QVariant ("pics/wall.png");//QVariant ("orange");
        case playerRole:
             if (value == PLAYER)
                return QVariant ("pics/player.png");//QVariant ("red");
        case boxRole:
             if (value == BOX)
                return QVariant ("pics/box.png"); //QVariant ("blue");
        case boxPositionRole:
             if (value == BOX_POSITION)
                return QVariant ("pics/boxPosition.png");//QVariant ("yellow");
        case boxOnPositionRole:
             if (value == BOX_ON_POSITION)
                return QVariant ("pics/boxOnPosition.png");//QVariant ("lightblue");
        case playerOnPositionRole:
             if (value == PLAYER_ON_POSITION)
                return QVariant ("pics/playerOnPosition.png");//QVariant ("gray");
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

void GameFieldModel::moveObject(int offset, int offset2)
{
    int nnp;
    int np = m_playerPosition + offset; //next line
    if (m_columns <= np && np <= m_field.size()-m_columns) { //np >= m_columns
        nnp = m_playerPosition + offset2; //next next line
        } else {nnp = 0; }
    qDebug() << "bilo"<< m_playerPosition;
    qDebug() << "stalo"<< np;
    qDebug() << "bydet"<<nnp;

    auto &p = m_field[m_playerPosition];
    auto &op = m_field[np];
    auto &oop = m_field[nnp];

    bool moved = false;

    switch(op) {
        case EMPTY: {
            p == PLAYER ? p = EMPTY : p = BOX_POSITION;
            op = PLAYER;
            moved = true;
            break;
        }
        case BOX_POSITION:{
            p == PLAYER ? p = EMPTY: p = BOX_POSITION;
            op = PLAYER_ON_POSITION;
            moved = true;
            break;
        }
        case BOX_ON_POSITION: {
            if(oop == BOX_POSITION){
                p == PLAYER ? p = EMPTY: p = BOX_POSITION;
                op = PLAYER_ON_POSITION;
                oop = BOX_ON_POSITION;
                moved = true;
                break;
            }
            if (oop == EMPTY) {
                p == PLAYER ? p = EMPTY: p = BOX_POSITION;
                op = PLAYER_ON_POSITION;
                oop = BOX;
                moved = true;
                --m_boxOnPosition;
                break;
            }
            break;
        }
        case BOX: {
            if(oop == BOX_POSITION) {
                    p == PLAYER ? p = EMPTY : p = BOX_POSITION;
                    op = PLAYER;
                    oop = BOX_ON_POSITION;
                    moved = true;
                    ++m_boxOnPosition;
                    break;
                }
            if(oop == EMPTY) {
                   p == PLAYER ? p = EMPTY : p = BOX_POSITION;
                   op = PLAYER;
                   oop = BOX;
                   moved = true;
                   break;
                 }
            break;
        }
        case PLAYER_ON_POSITION:
        case WALL:
        case PLAYER:
        break;
    }
        if(moved){
            m_playerPosition = np;
            ++m_stepsCount;
            if(m_boxPosition == m_boxOnPosition)
                m_isComplete = true;
        }

//            for (auto i = m_field.begin(); i!=m_field.end(); ++i) { //vector ne perezapisivaetsya, menyayutsya yachejki mestami
//                qDebug() << *i;
//            }

}

void GameFieldModel::moveUp()
{
    beginResetModel();
        moveObject(-m_columns, -m_columns*2);
        qDebug() << "moveUp";
        qDebug() << "";
        qDebug() << m_field.size();
      //  m_field.resize(64);
    endResetModel();
}

void GameFieldModel::moveDown()
{
    beginResetModel();
        moveObject(m_columns, m_columns*2);
        qDebug() << "moveDown";
        qDebug() << "";
        qDebug() << m_field.size();
      //  m_field.resize(64);
    endResetModel();
   }

void GameFieldModel::moveLeft()
{
    beginResetModel();
        moveObject(-1, -2);
        qDebug() << "moveLeft";
        qDebug() << "";
        qDebug() << m_field.size();
     //   m_field.resize(64);
    endResetModel();
}

void GameFieldModel::moveRight()
{
    beginResetModel();
        moveObject(1, 2);
        qDebug() << "moveRight";
        qDebug() << "";
        qDebug() << m_field.size();
      //  m_field.resize(64);
    endResetModel();
}
bool GameFieldModel::isComplete()
{
    return m_isComplete;
}

qint32 GameFieldModel::stepsCount()
{
    return m_stepsCount;
}

qint32 GameFieldModel::boxPosition()
{
    return m_boxPosition;
}

qint32 GameFieldModel::boxOnPosition()
{
    return m_boxOnPosition;
}


