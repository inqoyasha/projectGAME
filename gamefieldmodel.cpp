#include "gamefieldmodel.h"

GameFieldModel::GameFieldModel(QObject *parent)
    : QAbstractListModel(parent)
{
    firstLevel();
    m_fieldMemory.append(m_field);
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
            break;
        case WALL:
            return QVariant ("pics/wall.png");
            break;
        case PLAYER:
            return QVariant ("pics/player.png");
            break;
        case BOX:
            return QVariant ("pics/box.png");
            break;
        case BOX_POSITION:
            return QVariant ("pics/boxPosition.png");
            break;
        case BOX_ON_POSITION:
            return QVariant ("pics/boxOnPosition.png");
            break;
        case PLAYER_ON_POSITION:
            return QVariant ("pics/playerOnPosition.png");
            break;
    }

    switch(role){
        case iconSourceRole:
            return value;
    }
}

QHash<int, QByteArray> GameFieldModel::roleNames() const
{
    QHash<int,QByteArray> roles;
    roles[iconSourceRole] = "iconSource";
    return roles;
}

void GameFieldModel::moveObject(int offsetPlayerIcon, int offsetIconAfterPlayerIcon)
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
            playerPosition == PLAYER ? playerPosition = EMPTY : playerPosition = BOX_POSITION;
            beforePlayerPosition = PLAYER;
            moved = true;

            break;
        }
        case BOX_POSITION:{
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
                break;
            }
            if (afterPlayerPosition == EMPTY) {
                playerPosition == PLAYER ? playerPosition = EMPTY: playerPosition = BOX_POSITION;
                beforePlayerPosition = PLAYER_ON_POSITION;
                afterPlayerPosition = BOX;
                moved = true;
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
                    ++m_boxOnPosition;
                    emit boxesOnPositionChanged(m_boxOnPosition);
                    break;
                }
            if(afterPlayerPosition == EMPTY) {
                   playerPosition == PLAYER ? playerPosition = EMPTY : playerPosition = BOX_POSITION;
                   beforePlayerPosition = PLAYER;
                   afterPlayerPosition = BOX;
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

    m_fieldMemory.append(m_field);
    m_playerPositionMemory.append(m_playerPosition);
        if(moved){
            beginResetModel();
            endResetModel();
//            m_playerPositionMemory.append(m_playerPosition);
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
}

void GameFieldModel::nextLevel()
{
    beginResetModel();
    m_field.clear();
    m_playerPositionMemory.clear();
    m_fieldMemory.clear();
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
}

void GameFieldModel::stepBack()
{
    int z = 0;
    ++countCallStepBack;

    auto size = m_fieldMemory.size();

    m_field.clear();
    for (auto t: m_fieldMemory.at(size-countCallStepBack-1)) {
        m_field.push_back(t);
    }
    beginResetModel();

    qDebug() << "size "<< m_fieldMemory.size();
    qDebug() << "count "<< countCallStepBack;

    for (auto i = m_playerPositionMemory.begin(); i!=m_playerPositionMemory.end(); ++i) { //vector ne perezapisivaetsya, menyayutsya yachejki mestami
        qDebug() << *i;
    }

//    if (!m_playerPositionMemory.endsWith(m_playerPositionMemory.front())) {
    m_playerPosition = m_playerPositionMemory.back();
//        } else {
//            m_playerPosition = m_playerPositionMemory.front();
//        }

//    for (auto i = m_playerPositionMemory.begin(); i!=m_playerPositionMemory.end(); ++i) { //vector ne perezapisivaetsya, menyayutsya yachejki mestami
//        qDebug() << *i;
//    }


//    m_playerPosition = m_playerPositionMemory.at(m_playerPositionMemory.size()-1);
//    m_playerPositionMemory.pop_back();

    endResetModel();
    //return m_field;
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



