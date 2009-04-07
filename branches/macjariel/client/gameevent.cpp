#include "gameevent.h"
#include "game.h"

using namespace client;

GameEvent::GameEvent(Game* game):
        QObject(game),
        mp_game(game),
        m_isRunning(0)
{
}

GameEvent::~GameEvent()
{
}

void GameEvent::run()
{
    qDebug() << "GameEvent starting" << this;
    m_isRunning = 1;
}

void GameEvent::finish()
{
    qDebug() << "GameEvent finishing" << this;
    m_isRunning = 0;
    emit finished(this);
}

bool GameEvent::isReadyRun()
{
    return 1;
}

bool GameEvent::isRunning()
{
    return m_isRunning;
}
