#include "gamefieldmodel.h"

GameFieldModel::GameFieldModel(QObject *parent)
    : QAbstractListModel(parent)
{
    firstLevel();
}

int GameFieldModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_field.size();
}

QVariant GameFieldModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    eField value = m_field.at(index.row());

    switch (value){
        case EMPTY:
            return QVariant ("pics/empty.png");
        case WALL:
            return QVariant ("pics/wall.png");
        case PLAYER:
            return QVariant ("pics/player.png");
        case BOX:
            return QVariant ("pics/box.png");
        case BOX_POSITION:
            return QVariant ("pics/boxPosition.png");
        case BOX_ON_POSITION:
            return QVariant ("pics/box.png");    //return QVariant ("pics/boxOnPosition.png");
        case PLAYER_ON_POSITION:
            return QVariant ("pics/player.png"); //return QVariant ("pics/playerOnPosition.png");
    }

    switch(role){
        case iconSourceRole:
            return value;
        default:
            return QVariant();
    }
}

QHash<int, QByteArray> GameFieldModel::roleNames() const
{
    QHash<int,QByteArray> roles;
    roles[iconSourceRole] = "iconSource";
    return roles;
}

void GameFieldModel::moveObject(qint32 offsetPlayerIcon, qint32 offsetIconAfterPlayerIcon)
{
    int nextNextPosition;
    int nextPosition = m_playerPosition + offsetPlayerIcon; //next line
    if (m_columns <= nextPosition && nextPosition <= m_field.size()-m_columns) {
        nextNextPosition = m_playerPosition + offsetIconAfterPlayerIcon; //next next line
        } else {nextNextPosition = 0; }

    qDebug() << "been"  << m_playerPosition;
    qDebug() << "current" << nextPosition;
    qDebug() << "become" << nextNextPosition;

    auto &playerPosition = m_field[m_playerPosition];
    auto &beforePlayerPosition = m_field[nextPosition];
    auto &afterPlayerPosition = m_field[nextNextPosition];

    bool moved = false;

    switch(beforePlayerPosition) {
        case EMPTY: {
        if (m_playerPosition == 36 || m_playerPosition == 14 || m_playerPosition == 9 || m_playerPosition == 49 || m_playerPosition == 54) {
            if ((offsetPlayerIcon == -8) && (offsetIconAfterPlayerIcon == -16)) { // вверх
                beginMoveRows(parent, m_playerPosition, m_playerPosition,parent, nextPosition+1);
                endMoveRows();
                beginMoveRows(parent, nextPosition, nextPosition,parent, m_playerPosition+1);
                endMoveRows();
            } else if ((offsetPlayerIcon == 8) && (offsetIconAfterPlayerIcon == 16)){ // вниз
                    beginMoveRows(parent, m_playerPosition, m_playerPosition,parent, nextPosition);
                    endMoveRows();
                    beginMoveRows(parent, nextPosition, nextPosition,parent, m_playerPosition);
                    endMoveRows();
                } else if ((offsetPlayerIcon == -1) && (offsetIconAfterPlayerIcon == -2)) { // влево
                            beginMoveRows(parent, m_playerPosition, m_playerPosition, parent, nextPosition);
                            endMoveRows();
                        } else if ((offsetPlayerIcon == 1) && (offsetIconAfterPlayerIcon == 2)) {//вправо
                                beginMoveRows(parent, m_playerPosition, m_playerPosition, parent, nextPosition+1);
                                endMoveRows();
                        }

            beginRemoveRows(parent,m_playerPosition,m_playerPosition);
            endRemoveRows();
            beginInsertRows(parent,m_playerPosition,m_playerPosition);
            endInsertRows();

        } else if ((offsetPlayerIcon == -8) && (offsetIconAfterPlayerIcon == -16)) { // вверх
            beginMoveRows(parent, m_playerPosition, m_playerPosition,parent, nextPosition+1);
            endMoveRows();
            beginMoveRows(parent, nextPosition, nextPosition,parent, m_playerPosition+1);
            endMoveRows();} else if ((offsetPlayerIcon == 8) && (offsetIconAfterPlayerIcon == 16)){ // вниз
                beginMoveRows(parent, m_playerPosition, m_playerPosition,parent, nextPosition);
                endMoveRows();
                beginMoveRows(parent, nextPosition, nextPosition,parent, m_playerPosition);
                endMoveRows();} else if ((offsetPlayerIcon == -1) && (offsetIconAfterPlayerIcon == -2)) { // влево
                    beginMoveRows(parent, m_playerPosition, m_playerPosition, parent, nextPosition);
                    endMoveRows(); } else if ((offsetPlayerIcon == 1) && (offsetIconAfterPlayerIcon == 2)) {//вправо
                        beginMoveRows(parent, m_playerPosition, m_playerPosition, parent, nextPosition+1);
                        endMoveRows(); }

            playerPosition == PLAYER ? playerPosition = EMPTY : playerPosition = BOX_POSITION;
            beforePlayerPosition = PLAYER;
            moved = true;
            break;
        }
        case BOX_POSITION:{

        if ((offsetPlayerIcon == -8) && (offsetIconAfterPlayerIcon == -16)) { // вверх
            beginMoveRows(parent, m_playerPosition, m_playerPosition,parent, nextPosition+1);
            endMoveRows();
            beginMoveRows(parent, nextPosition, nextPosition,parent, m_playerPosition+1);
            endMoveRows();
            beginRemoveRows(parent,m_playerPosition,m_playerPosition);
            endRemoveRows();
            beginInsertRows(parent,m_playerPosition,m_playerPosition);
            endInsertRows();


        } else if ((offsetPlayerIcon == 8) && (offsetIconAfterPlayerIcon == 16)){ // вниз
                beginMoveRows(parent, m_playerPosition, m_playerPosition,parent, nextPosition);
                endMoveRows();
                beginMoveRows(parent, nextPosition, nextPosition,parent, m_playerPosition);
                endMoveRows();
                beginRemoveRows(parent,m_playerPosition,m_playerPosition);
                endRemoveRows();
                beginInsertRows(parent,m_playerPosition,m_playerPosition);
                endInsertRows();
            } else if ((offsetPlayerIcon == -1) && (offsetIconAfterPlayerIcon == -2)) { // влево
                        beginMoveRows(parent, m_playerPosition, m_playerPosition, parent, nextPosition);
                        endMoveRows();
                        beginRemoveRows(parent,m_playerPosition,m_playerPosition);
                        endRemoveRows();
                        beginInsertRows(parent,m_playerPosition,m_playerPosition);
                        endInsertRows();
                    } else if ((offsetPlayerIcon == 1) && (offsetIconAfterPlayerIcon == 2)) {//вправо
                            beginMoveRows(parent, m_playerPosition, m_playerPosition, parent, nextPosition+1);
                            endMoveRows();
                            beginRemoveRows(parent,m_playerPosition,m_playerPosition);
                            endRemoveRows();
                            beginInsertRows(parent,m_playerPosition,m_playerPosition);
                            endInsertRows();
                    }

            playerPosition == PLAYER ? playerPosition = EMPTY: playerPosition = BOX_POSITION;
            beforePlayerPosition = PLAYER_ON_POSITION;
            moved = true;
            break;
        }
        case BOX_ON_POSITION: {
            if(afterPlayerPosition == BOX_POSITION){
                playerPosition == PLAYER ? playerPosition = EMPTY: playerPosition = BOX_POSITION;
                beforePlayerPosition = PLAYER_ON_POSITION;
                afterPlayerPosition = BOX_ON_POSITION;
                moved = true;
                if ((offsetPlayerIcon == -8) && (offsetIconAfterPlayerIcon == -16)) { // вверх
                    beginMoveRows(parent, nextPosition, nextPosition,parent, nextNextPosition+1);
                    endMoveRows();
                    beginMoveRows(parent, m_playerPosition, m_playerPosition,parent, nextPosition+1);
                    endMoveRows();
                    beginMoveRows(parent, nextNextPosition, nextNextPosition,parent, nextPosition+1);
                    endMoveRows();
                    beginMoveRows(parent, nextPosition, nextPosition,parent, m_playerPosition+1);
                    endMoveRows();
                    beginRemoveRows(parent,m_playerPosition,m_playerPosition);
                    endRemoveRows();
                    beginInsertRows(parent,m_playerPosition,m_playerPosition);
                    endInsertRows();

                     } else if ((offsetPlayerIcon == 8) && (offsetIconAfterPlayerIcon == 16)){ // вниз
                        beginMoveRows(parent, nextPosition, nextPosition,parent, nextNextPosition);
                        endMoveRows();
                        beginMoveRows(parent, m_playerPosition, m_playerPosition,parent, nextPosition);
                        endMoveRows();
                        beginMoveRows(parent, nextNextPosition, nextNextPosition,parent, nextPosition);
                        endMoveRows();
                        beginMoveRows(parent, nextPosition, nextPosition,parent, m_playerPosition);
                        endMoveRows();
                        beginRemoveRows(parent,m_playerPosition,m_playerPosition);
                        endRemoveRows();
                        beginInsertRows(parent,m_playerPosition,m_playerPosition);
                        endInsertRows();
                         } else if ((offsetPlayerIcon == -1) && (offsetIconAfterPlayerIcon == -2)) { // влево
                                beginMoveRows(parent, nextPosition, nextPosition,parent, nextNextPosition);
                                endMoveRows();
                                beginMoveRows(parent, m_playerPosition, m_playerPosition,parent, nextPosition);
                                endMoveRows();
                                beginRemoveRows(parent,m_playerPosition,m_playerPosition);
                                endRemoveRows();
                                beginInsertRows(parent,m_playerPosition,m_playerPosition);
                                endInsertRows();
                             } else if ((offsetPlayerIcon == 1) && (offsetIconAfterPlayerIcon == 2)) {//вправо
                                    beginMoveRows(parent, nextPosition, nextPosition,parent, nextNextPosition+1);
                                    endMoveRows();
                                    beginMoveRows(parent, m_playerPosition, m_playerPosition,parent, nextPosition+1);
                                    endMoveRows();
                                    beginRemoveRows(parent,m_playerPosition,m_playerPosition);
                                    endRemoveRows();
                                    beginInsertRows(parent,m_playerPosition,m_playerPosition);
                                    endInsertRows();
                            }
                break;
            }
            if (afterPlayerPosition == EMPTY) {
                playerPosition == PLAYER ? playerPosition = EMPTY: playerPosition = BOX_POSITION;
                beforePlayerPosition = PLAYER_ON_POSITION;
                afterPlayerPosition = BOX;
                moved = true;
                if ((offsetPlayerIcon == -8) && (offsetIconAfterPlayerIcon == -16)) { // вверх
                    beginMoveRows(parent, nextPosition, nextPosition,parent, nextNextPosition+1);
                    endMoveRows();
                    beginMoveRows(parent, m_playerPosition, m_playerPosition,parent, nextPosition+1);
                    endMoveRows();
                    beginMoveRows(parent, nextNextPosition, nextNextPosition,parent, nextPosition+1);
                    endMoveRows();
                    beginMoveRows(parent, nextPosition, nextPosition,parent, m_playerPosition+1);
                    endMoveRows();
                    beginRemoveRows(parent,m_playerPosition,m_playerPosition);
                    endRemoveRows();
                    beginInsertRows(parent,m_playerPosition,m_playerPosition);
                    endInsertRows();

                     } else if ((offsetPlayerIcon == 8) && (offsetIconAfterPlayerIcon == 16)){ // вниз
                        beginMoveRows(parent, nextPosition, nextPosition,parent, nextNextPosition);
                        endMoveRows();
                        beginMoveRows(parent, m_playerPosition, m_playerPosition,parent, nextPosition);
                        endMoveRows();
                        beginMoveRows(parent, nextNextPosition, nextNextPosition,parent, nextPosition);
                        endMoveRows();
                        beginMoveRows(parent, nextPosition, nextPosition,parent, m_playerPosition);
                        endMoveRows();
                        beginRemoveRows(parent,m_playerPosition,m_playerPosition);
                        endRemoveRows();
                        beginInsertRows(parent,m_playerPosition,m_playerPosition);
                        endInsertRows();
                         } else if ((offsetPlayerIcon == -1) && (offsetIconAfterPlayerIcon == -2)) { // влево
                                beginMoveRows(parent, nextPosition, nextPosition,parent, nextNextPosition);
                                endMoveRows();
                                beginMoveRows(parent, m_playerPosition, m_playerPosition,parent, nextPosition);
                                endMoveRows();
                                beginRemoveRows(parent,m_playerPosition,m_playerPosition);
                                endRemoveRows();
                                beginInsertRows(parent,m_playerPosition,m_playerPosition);
                                endInsertRows();
                             } else if ((offsetPlayerIcon == 1) && (offsetIconAfterPlayerIcon == 2)) {//вправо
                                    beginMoveRows(parent, nextPosition, nextPosition,parent, nextNextPosition+1);
                                    endMoveRows();
                                    beginMoveRows(parent, m_playerPosition, m_playerPosition,parent, nextPosition+1);
                                    endMoveRows();
                                    beginRemoveRows(parent,m_playerPosition,m_playerPosition);
                                    endRemoveRows();
                                    beginInsertRows(parent,m_playerPosition,m_playerPosition);
                                    endInsertRows();
                            }
                --m_boxOnPosition;
                emit boxesOnPositionChanged(m_boxOnPosition);
                break;
            }
            break;
        }
        case BOX: {
            if(afterPlayerPosition == BOX_POSITION) {
                    playerPosition == PLAYER ? playerPosition = EMPTY : playerPosition = BOX_POSITION;
                    beforePlayerPosition = PLAYER;
                    afterPlayerPosition = BOX_ON_POSITION;
                    moved = true;
                    if ((offsetPlayerIcon == -8) && (offsetIconAfterPlayerIcon == -16)) { // вверх
                        beginMoveRows(parent, nextPosition, nextPosition,parent, nextNextPosition+1);
                        endMoveRows();
                        beginMoveRows(parent, m_playerPosition, m_playerPosition,parent, nextPosition+1);
                        endMoveRows();
                        beginMoveRows(parent, nextNextPosition, nextNextPosition,parent, nextPosition+1);
                        endMoveRows();
                        beginMoveRows(parent, nextPosition, nextPosition,parent, m_playerPosition+1);
                        endMoveRows();
                        beginRemoveRows(parent,m_playerPosition,m_playerPosition);
                        endRemoveRows();
                        beginInsertRows(parent,m_playerPosition,m_playerPosition);
                        endInsertRows();

                         } else if ((offsetPlayerIcon == 8) && (offsetIconAfterPlayerIcon == 16)){ // вниз
                            beginMoveRows(parent, nextPosition, nextPosition,parent, nextNextPosition);
                            endMoveRows();
                            beginMoveRows(parent, m_playerPosition, m_playerPosition,parent, nextPosition);
                            endMoveRows();
                            beginMoveRows(parent, nextNextPosition, nextNextPosition,parent, nextPosition);
                            endMoveRows();
                            beginMoveRows(parent, nextPosition, nextPosition,parent, m_playerPosition);
                            endMoveRows();
                            beginRemoveRows(parent,m_playerPosition,m_playerPosition);
                            endRemoveRows();
                            beginInsertRows(parent,m_playerPosition,m_playerPosition);
                            endInsertRows();
                             } else if ((offsetPlayerIcon == -1) && (offsetIconAfterPlayerIcon == -2)) { // влево
                                    beginMoveRows(parent, nextPosition, nextPosition,parent, nextNextPosition);
                                    endMoveRows();
                                    beginMoveRows(parent, m_playerPosition, m_playerPosition,parent, nextPosition);
                                    endMoveRows();
                                    beginRemoveRows(parent,m_playerPosition,m_playerPosition);
                                    endRemoveRows();
                                    beginInsertRows(parent,m_playerPosition,m_playerPosition);
                                    endInsertRows();
                                 } else if ((offsetPlayerIcon == 1) && (offsetIconAfterPlayerIcon == 2)) {//вправо
                                        beginMoveRows(parent, nextPosition, nextPosition,parent, nextNextPosition+1);
                                        endMoveRows();
                                        beginMoveRows(parent, m_playerPosition, m_playerPosition,parent, nextPosition+1);
                                        endMoveRows();
                                        beginRemoveRows(parent,m_playerPosition,m_playerPosition);
                                        endRemoveRows();
                                        beginInsertRows(parent,m_playerPosition,m_playerPosition);
                                        endInsertRows();
                                }
                    ++m_boxOnPosition;
                    emit boxesOnPositionChanged(m_boxOnPosition);
                    break;
                }
            if(afterPlayerPosition == EMPTY) {
                   playerPosition == PLAYER ? playerPosition = EMPTY : playerPosition = BOX_POSITION;
                   beforePlayerPosition = PLAYER;
                   afterPlayerPosition = BOX;
                   moved = true;
                   if ((offsetPlayerIcon == -8) && (offsetIconAfterPlayerIcon == -16)) { // вверх
                       beginMoveRows(parent, nextPosition, nextPosition,parent, nextNextPosition+1);
                       endMoveRows();
                       beginMoveRows(parent, m_playerPosition, m_playerPosition,parent, nextPosition+1);
                       endMoveRows();
                       beginMoveRows(parent, nextNextPosition, nextNextPosition,parent, nextPosition+1);
                       endMoveRows();
                       beginMoveRows(parent, nextPosition, nextPosition,parent, m_playerPosition+1);
                       endMoveRows();
                        } else if ((offsetPlayerIcon == 8) && (offsetIconAfterPlayerIcon == 16)){ // вниз
                           beginMoveRows(parent, nextPosition, nextPosition,parent, nextNextPosition);
                           endMoveRows();
                           beginMoveRows(parent, m_playerPosition, m_playerPosition,parent, nextPosition);
                           endMoveRows();
                           beginMoveRows(parent, nextNextPosition, nextNextPosition,parent, nextPosition);
                           endMoveRows();
                           beginMoveRows(parent, nextPosition, nextPosition,parent, m_playerPosition);
                           endMoveRows();
                            } else if ((offsetPlayerIcon == -1) && (offsetIconAfterPlayerIcon == -2)) { // влево
                                   beginMoveRows(parent, nextPosition, nextPosition,parent, nextNextPosition);
                                   endMoveRows();
                                   beginMoveRows(parent, m_playerPosition, m_playerPosition,parent, nextPosition);
                                   endMoveRows();
                                } else if ((offsetPlayerIcon == 1) && (offsetIconAfterPlayerIcon == 2)) {//вправо
                                       beginMoveRows(parent, nextPosition, nextPosition,parent, nextNextPosition+1);
                                       endMoveRows();
                                       beginMoveRows(parent, m_playerPosition, m_playerPosition,parent, nextPosition+1);
                                       endMoveRows();
                               }

                   beginRemoveRows(parent,m_playerPosition,m_playerPosition);
                   endRemoveRows();
                   beginInsertRows(parent,m_playerPosition,m_playerPosition);
                   endInsertRows();

                   break;
                 }
            break;
        }
        case PLAYER_ON_POSITION:
        case WALL:
        case PLAYER:
        break;
    }

    m_fieldMemory.append(m_field);
    m_playerPositionMemory.append(m_playerPosition);
    m_boxOnPositionMemory.append(m_boxOnPosition);

    for (auto t: m_fieldMemory.at(m_fieldMemory.size()-2)) {
        m_fieldBefore.push_back(t);
    }


    for (int i = 0; i < m_field.size(); ++i) {
        if (m_field.at(i) != m_fieldBefore.at(i)) {
            m_fieldDeltaIndex.append(i);
            m_fieldDeltaPos.append(m_fieldBefore.at(i));
        }
    }

    m_fieldIndex.append(m_fieldDeltaIndex); //indexi
    m_fieldPos.append(m_fieldDeltaPos); //pos

        if(moved){
            m_playerPosition = nextPosition;
            ++m_stepsCount;
            emit stepChanged(m_stepsCount);
            if(m_boxPosition == m_boxOnPosition)
                m_isComplete = true;
                emit isCompleteChanged(m_isComplete);

        }

//    qDebug() << "bilo";
//    for (auto i = m_fieldBefore.begin(); i!=m_fieldBefore.end(); ++i) { //vector ne perezapisivaetsya, menyayutsya yachejki mestami
//        qDebug() << *i;
//    }
    for (auto i = m_fieldPos.begin(); i!=m_fieldPos.end(); ++i) { //vector ne perezapisivaetsya, menyayutsya yachejki mestami
        qDebug () << *i;
    }
    for (auto i = m_fieldIndex.begin(); i!=m_fieldIndex.end(); ++i) { //vector ne perezapisivaetsya, menyayutsya yachejki mestami
        qDebug () << *i;
    }
//    qDebug() << "stalo";
//    for (auto i = m_field.begin(); i!=m_field.end(); ++i) { //vector ne perezapisivaetsya, menyayutsya yachejki mestami
//        qDebug() << *i;
//    }
//    qDebug() << "deltaIndex";
//    for (auto i = m_fieldDeltaIndex.begin(); i!=m_fieldDeltaIndex.end(); ++i) { //vector ne perezapisivaetsya, menyayutsya yachejki mestami
//        qDebug() << *i;
//    }
//    qDebug() << "deltaPos";
//    for (auto i = m_fieldDeltaPos.begin(); i!=m_fieldDeltaPos.end(); ++i) { //vector ne perezapisivaetsya, menyayutsya yachejki mestami
//        qDebug() << *i;
//    }

    m_fieldDeltaPos.clear();
    m_fieldDeltaIndex.clear();
    m_fieldBefore.clear();
//    m_fieldMemory.removeAt(m_fieldMemory.size()-2);
//    qDebug() << "shagi"<< step();
//    qDebug() << "yashiki"<< boxesOnPosition() << "/" << boxes() ;
//    qDebug() << "konec"<< isComplete();
//            for (auto i = m_field.begin(); i!=m_field.end(); ++i) { //vector ne perezapisivaetsya, menyayutsya yachejki mestami
//                qDebug() << *i;
//            }
//    qDebug() << "size play1" << m_playerPositionMemory.size();
//    for (auto i = m_playerPositionMemory.begin(); i!=m_playerPositionMemory.end(); ++i) { //vector ne perezapisivaetsya, menyayutsya yachejki mestami
//        qDebug() << *i;
//    }
//    for (auto i = m_boxOnPositionMemory.begin(); i!=m_boxOnPositionMemory.end(); ++i) { //vector ne perezapisivaetsya, menyayutsya yachejki mestami
//            qDebug () << *i;
//    }
        //    for (auto i = m_fieldMemory.begin(); i!=m_fieldMemory.end(); ++i) { //vector ne perezapisivaetsya, menyayutsya yachejki mestami
        //        qDebug() << *i;
        //    }
}

void GameFieldModel::moveUp()
{
    moveObject(-m_columns, -m_columns*2);
    qDebug() << "moveUp";
    qDebug() << "size" << m_field.size();
    qDebug() << "";
}

void GameFieldModel::moveDown()
{
    moveObject(m_columns, m_columns*2);
    qDebug() << "moveDown";
    qDebug() << "size" << m_field.size();
    qDebug() << "";
   }

void GameFieldModel::moveLeft()
{
    moveObject(-1, -2);
    qDebug() << "moveLeft";
    qDebug() << "size" << m_field.size();
    qDebug() << "";
}

void GameFieldModel::moveRight()
{
    moveObject(1, 2);
    qDebug() << "moveRight";
    qDebug() << "size" << m_field.size();
    qDebug() << "";
}

void GameFieldModel::firstLevel()
{
    beginResetModel();
    m_fieldMemory.clear();
    m_playerPositionMemory.clear();
    m_boxOnPositionMemory.clear();
    m_fieldIndex.clear();
    m_fieldPos.clear();
    m_field.clear();
    m_playerPosition = 26;
    m_boxPosition = 2;
    m_stepsCount = 0;
    emit stepChanged(m_stepsCount);
    m_boxOnPosition = 0;
    emit boxesOnPositionChanged(m_boxOnPosition);
    m_isComplete = false;
    emit isCompleteChanged(m_isComplete);
    m_field.append({WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL});
    m_field.append({WALL,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,BOX_POSITION,WALL});
    m_field.append({WALL,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,BOX,WALL});
    m_field.append({WALL,EMPTY,PLAYER,WALL,BOX,EMPTY,EMPTY,WALL});
    m_field.append({WALL,EMPTY,EMPTY,WALL,BOX_POSITION,EMPTY,EMPTY,WALL});
    m_field.append({WALL,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL});
    m_field.append({WALL,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,WALL});
    m_field.append({WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL});
    endResetModel();
    m_fieldMemory.append(m_field);
}

void GameFieldModel::nextLevel()
{
    beginResetModel();
    m_fieldMemory.clear();
    m_playerPositionMemory.clear();
    m_boxOnPositionMemory.clear();
    m_fieldIndex.clear();
    m_fieldPos.clear();
    m_field.clear();
    m_playerPosition = 38;
    m_boxPosition = 4;
    m_lvlCount = 2;
    emit lvlCountChanged(m_lvlCount);
    m_stepsCount = 0;
    emit stepChanged(m_stepsCount);
    m_boxOnPosition = 0;
    emit boxesOnPositionChanged(m_boxOnPosition);
    m_isComplete = false;
    emit isCompleteChanged(m_isComplete);
    m_field.append({WALL,WALL, WALL, WALL, WALL,WALL, WALL,WALL});
    m_field.append({WALL,BOX_POSITION,EMPTY,EMPTY,EMPTY,EMPTY,BOX_POSITION,WALL});
    m_field.append({WALL,EMPTY,WALL,EMPTY,EMPTY,WALL,EMPTY,WALL});
    m_field.append({WALL,EMPTY,BOX,EMPTY,EMPTY,BOX,EMPTY,WALL});
    m_field.append({WALL,EMPTY,BOX,EMPTY,EMPTY,BOX,PLAYER,WALL});
    m_field.append({WALL,EMPTY,WALL,EMPTY,EMPTY,WALL,EMPTY, WALL});
    m_field.append({WALL,BOX_POSITION,EMPTY,EMPTY,EMPTY,EMPTY,BOX_POSITION,WALL});
    m_field.append({WALL,WALL, WALL, WALL, WALL,WALL,WALL,WALL});
    endResetModel();
    m_fieldMemory.append(m_field);
}

void GameFieldModel::stepBack()
{
    beginResetModel();
    auto sizeFieldIndex = m_fieldIndex.size()-1;
    auto sizePlayerPos = m_playerPositionMemory.size();

    if (sizePlayerPos-1 != -1) {
        for (int i = 0; i < m_fieldIndex.back().size(); ++i) {
            m_field.removeAt(m_fieldIndex.at(sizeFieldIndex).at(i));
            m_field.insert(m_fieldIndex.at(sizeFieldIndex).at(i),m_fieldPos.at(sizeFieldIndex).at(i));
        }
    }
    endResetModel();

    if (m_fieldIndex.size() != 0) {
        m_fieldIndex.removeAt(sizeFieldIndex);
        m_fieldPos.removeAt(sizeFieldIndex);
        if (m_stepsCount != 0) m_stepsCount--;
        emit stepChanged(m_stepsCount);
    }
        for (auto i = m_fieldPos.begin(); i!=m_fieldPos.end(); ++i) { //vector ne perezapisivaetsya, menyayutsya yachejki mestami
            qDebug () << *i;
        }
        for (auto i = m_fieldIndex.begin(); i!=m_fieldIndex.end(); ++i) { //vector ne perezapisivaetsya, menyayutsya yachejki mestami
            qDebug () << *i;
        }

//    qDebug() << "m_playerPos" << m_playerPositionMemory.back();
//      qDebug() << "size field"<< m_fieldMemory.size();
//    qDebug() << "size boxOnPos"<< m_boxOnPositionMemory.size();

//    for (auto i = m_fieldMemory.begin(); i!=m_fieldMemory.end(); ++i) { //vector ne perezapisivaetsya, menyayutsya yachejki mestami
//        qDebug() << *i;
//    }
//    for (auto i = m_playerPositionMemory.begin(); i!=m_playerPositionMemory.end(); ++i) { //vector ne perezapisivaetsya, menyayutsya yachejki mestami
//        qDebug() << *i;
//    }
//    for (auto i = m_boxOnPositionMemory.begin(); i!=m_boxOnPositionMemory.end(); ++i) { //vector ne perezapisivaetsya, menyayutsya yachejki mestami
//            qDebug () << *i;
//    }

    if (!m_boxOnPositionMemory.isEmpty()) m_boxOnPositionMemory.pop_back();
    if (!m_boxOnPositionMemory.isEmpty()) m_boxOnPosition = m_boxOnPositionMemory.back();
    emit boxesOnPositionChanged(m_boxOnPosition);

    if (!m_playerPositionMemory.isEmpty()) m_playerPosition = m_playerPositionMemory.back();
    if (!m_playerPositionMemory.isEmpty()) m_playerPositionMemory.pop_back();
}


bool GameFieldModel::isComplete()
{
    return m_isComplete;
}

qint32 GameFieldModel::step()
{
    return m_stepsCount;
}

qint32 GameFieldModel::boxes()
{
    return m_boxPosition;
}

qint32 GameFieldModel::boxesOnPosition()
{
    return m_boxOnPosition;
}

qint32 GameFieldModel::lvlCount()
{
    return m_lvlCount;
}

void GameFieldModel::read(const QJsonObject &json)
{
    if (json.contains("playerPos") && json["playerPos"].isDouble())
        m_playerPosition = json["playerPos"].toInt();
    if (json.contains("boxOnPos") && json["boxOnPos"].isDouble())
        m_boxOnPosition = json["boxOnPos"].toInt();
    if (json.contains("steps") && json["steps"].isDouble())
        m_stepsCount = json["steps"].toInt();
    if (json.contains("boxes") && json["boxes"].isDouble())
        m_boxPosition = json["boxes"].toInt();
    if (json.contains("lvl") && json["lvl"].isDouble())
        m_lvlCount = json["lvl"].toInt();

    if (json.contains("field") && json["field"].isArray()) {
        QJsonArray fieldArray = json["field"].toArray();
        m_field.clear();
        m_field.reserve(fieldArray.size());
        for (int fieldIndex = 0; fieldIndex < fieldArray.size(); ++fieldIndex) {
            QJsonValue fieldVal = fieldArray[fieldIndex].toInt();
            m_field.append(eField(fieldVal.toInt()));
        }
    }
}

void GameFieldModel::write(QJsonObject &json) const
{
    json["playerPos"] = m_playerPosition;
    json["lvl"] = m_lvlCount;
    json["boxOnPos"] = m_boxOnPosition;
    json["steps"] = m_stepsCount;
    json["boxes"] = m_boxPosition;

    QJsonArray fieldArray;
    for (const eField &field: m_field) {
        fieldArray.append(field);
    }
    json["field"] = fieldArray;
}

bool GameFieldModel::loadGame()
{
    beginResetModel();

    m_fieldMemory.clear();
    m_playerPositionMemory.clear();
    m_boxOnPositionMemory.clear();
    m_fieldIndex.clear();
    m_fieldPos.clear();
    m_field.clear();

    QFile loadFile( QStringLiteral("save.json"));

    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    QByteArray saveData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
    read(loadDoc.object());
    emit lvlCountChanged(m_lvlCount);
    emit stepChanged(m_stepsCount);
    emit boxesOnPositionChanged(m_boxOnPosition);
    emit boxesChanged(m_boxPosition);
    endResetModel();
    m_fieldMemory.append(m_field);

    return true;
}

bool GameFieldModel::saveGame() const
{
    QFile saveFile(QStringLiteral("save.json"));

    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    QJsonObject gameObject;
    write(gameObject);
    QJsonDocument saveDoc(gameObject);
    saveFile.write(saveDoc.toJson());

    return true;
}




