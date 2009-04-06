#ifndef GAMEEVENTHANDLER_H
#define GAMEEVENTHANDLER_H

#include <QObject>
#include "parser/parserstructs.h"

namespace client
{
class GameEventQueue;
class Game;

class GameEventHandler: public QObject
{
Q_OBJECT;
public:
    GameEventHandler(Game* game);
    void connectSlots(QObject* signalEmitter);

public slots:
    void onCardMovementEvent(const StructCardMovement&);

private:
    Game*           mp_game;
    GameEventQueue* mp_queue;
};

}
#endif // GAMEEVENTHANDLER_H