#include "gamefieldmodel.h"

#include "windows.h"
#include <thread>

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
        beginResetModel();
        endResetModel();

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
        if(moved){
            m_playerPosition = nextPosition;
            ++m_stepsCount;
            emit stepChanged(m_stepsCount);
            if(m_boxPosition == m_boxOnPosition)
                m_isComplete = true;
                emit isCompleteChanged(m_isComplete);
        }

    qDebug() << "shagi"<< step();
    qDebug() << "yashiki"<< boxesOnPosition() << "/" << boxes() ;
    qDebug() << "konec"<< isComplete();
//            for (auto i = m_field.begin(); i!=m_field.end(); ++i) { //vector ne perezapisivaetsya, menyayutsya yachejki mestami
//                qDebug() << *i;
//            }
    qDebug() << "size play1" << m_playerPositionMemory.size();
    qDebug() << "size field1"<< m_fieldMemory.size();
//    for (auto i = m_fieldMemory.begin(); i!=m_fieldMemory.end(); ++i) { //vector ne perezapisivaetsya, menyayutsya yachejki mestami
//        qDebug() << *i;
//    }
//    for (auto i = m_playerPositionMemory.begin(); i!=m_playerPositionMemory.end(); ++i) { //vector ne perezapisivaetsya, menyayutsya yachejki mestami
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
    m_field.clear();
    m_playerPosition = 38;
    m_boxPosition = 4;
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
    auto sizePlayerPos = m_playerPositionMemory.size();

    m_field.clear();
    if (sizePlayerPos-1 != -1) {
        for (auto t: m_fieldMemory.at(sizePlayerPos-1)) {
            m_field.push_back(t);
        }
    } else {
        for (auto t: m_fieldMemory.at(0)) {
            m_field.push_back(t);
        }
    }
    endResetModel();

//    for (auto i = m_boxOnPosition1.begin(); i!=m_boxOnPosition1.end(); ++i) { //vector ne perezapisivaetsya, menyayutsya yachejki mestami
//            qDebug () << *i << "s" << m_boxOnPosition1.at(m_boxOnPosition1.size()-1);
//    }
//    for (auto i = m_field.begin(); i!=m_field.end(); ++i) { //vector ne perezapisivaetsya, menyayutsya yachejki mestami
//        if (*i != BOX_ON_POSITION) {
//            m_boxOnPosition--;
//            qDebug () << "-1" << m_boxOnPosition;
//        }
//    }

    if (m_fieldMemory.size() != 1) {
        m_fieldMemory.removeAt(sizePlayerPos);
        if (m_stepsCount != 0) m_stepsCount--;
        emit stepChanged(m_stepsCount);
//        if (m_boxOnPosition != 0) { // nuzhen massiv
//            m_boxOnPosition--;
//            emit boxesOnPositionChanged(m_boxOnPosition);
//        }
    }
//    qDebug() << "size play2" << m_playerPositionMemory.size();
//    qDebug() << "size field2"<< m_fieldMemory.size();
//    qDebug() << "count "<< countCallStepBack;
//    for (auto i = m_field.begin(); i!=m_field.end(); ++i) { //vector ne perezapisivaetsya, menyayutsya yachejki mestami
//        qDebug() << *i;
//    }
//    for (auto i = m_playerPositionMemory.begin(); i!=m_playerPositionMemory.end(); ++i) { //vector ne perezapisivaetsya, menyayutsya yachejki mestami
//        qDebug() << *i;
//    }
//    qDebug() << "position ="<< m_playerPositionMemory.back();

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



