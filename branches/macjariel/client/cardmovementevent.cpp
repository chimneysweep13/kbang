/***************************************************************************
 *   Copyright (C) 2008 by MacJariel                                       *
 *   echo "badmailet@gbalt.dob" | tr "edibmlt" "ecrmjil"                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "cardmovementevent.h"

#include <QtCore>
#include <QtDebug>

#include "cardwidget.h"
#include "cardlist.h"
#include "game.h"
#include "parser/parserstructs.h"

#include <math.h>

using namespace client;

const int       tickTime        = 20;
const double    pixelsPerTick   = 24;

QBasicTimer CardMovementEvent:: sm_timer;

CardMovementEvent::CardMovementEvent(Game* game, const StructCardMovement& structCardMovement):
        GameEvent(game),
        m_structCardMovement(structCardMovement),
        mp_card(0),
        mp_destPocket(0),
        m_tick(0),
        m_isRunning(0),
        m_cardAndPocketIsSet(0)
{
}

CardMovementEvent::~CardMovementEvent()
{
}

bool CardMovementEvent::isReadyRun()
{
    if (!m_cardAndPocketIsSet)
        setCardAndPocket();
    return (mp_card->isVisible() && mp_destPocket->isVisible());
}

bool CardMovementEvent::isRunning()
{
    return m_isRunning;
}



void CardMovementEvent::run()
{
    if (!m_cardAndPocketIsSet)
        setCardAndPocket();
    startTransition();
}

void CardMovementEvent::setCardAndPocket()
{
    PlayerWidget* srcPlayer  = mp_game->playerWidget(m_structCardMovement.playerFrom);
    PlayerWidget* destPlayer = mp_game->playerWidget(m_structCardMovement.playerTo);

    switch(m_structCardMovement.pocketTypeFrom)
    {
    case POCKET_DECK:
        mp_card = mp_game->deck()->pop();
        break;
    case POCKET_GRAVEYARD:
        mp_card = mp_game->graveyard()->pop();
        break;
    case POCKET_HAND:
        if (!srcPlayer) {
            qCritical("Invalid card movement from POCKET_HAND (unknown player).");
            break;
        }
        if (srcPlayer->isLocalPlayer() && m_structCardMovement.cardDetails.cardId == 0) {
            qCritical("Invalid card movement from POCKET_HAND (unknown card).");
            break;
        }
        mp_card = srcPlayer->hand()->take(srcPlayer->isLocalPlayer() ?
                                          m_structCardMovement.cardDetails.cardId :
                                          0);
        break;
    case POCKET_TABLE:
        if (!srcPlayer) {
            qCritical("Invalid card movement from POCKET_TABLE (unknown player).");
            break;
        }
        if (m_structCardMovement.cardDetails.cardId == 0) {
            qCritical("Invalid card movement from POCKET_TABLE (unknown card).");
            break;
        }
        mp_card = srcPlayer->table()->take(m_structCardMovement.cardDetails.cardId);
        break;
    case POCKET_PLAYED:
        // todo
        break;
    case POCKET_SELECTION:
        // todo
        break;
    case POCKET_INVALID:
        break;
    }

    switch(m_structCardMovement.pocketTypeTo)
    {
    case POCKET_DECK:
        mp_destPocket = mp_game->deck();
        break;
    case POCKET_GRAVEYARD:
        mp_destPocket = mp_game->graveyard();
        break;
    case POCKET_HAND:
        mp_destPocket = destPlayer != 0 ? destPlayer->hand() : 0;
        break;
    case POCKET_TABLE:
        mp_destPocket = destPlayer != 0 ? destPlayer->table() : 0;
        break;
    case POCKET_PLAYED:
        /// \todo Implement moveCard to POCKET_PLAYED
        break;
    case POCKET_SELECTION:
        /// \todo Implement moveCard to POCKET_SELECTION
        break;
    case POCKET_INVALID:
        break;
    }
    if (mp_card == 0)
    {
        qCritical("Cannot find card for movement.");
        return;
    }
    if (mp_destPocket == 0)
    {
        qCritical("Cannot find target pocket for card movement.");
        return;
    }
    if (m_structCardMovement.cardDetails.cardId != 0)
        mp_card->setCardId(m_structCardMovement.cardDetails.cardId);
    m_cardAndPocketIsSet = 1;
}


void CardMovementEvent::startTransition()
{
    Q_ASSERT(mp_destPocket->isVisible());
    Q_ASSERT(mp_card->isVisible());
    Q_ASSERT(!sm_timer.isActive());

    m_isRunning = 1;

    if (mp_card->parent() != mp_game->mainWidget())
    {
        QPoint pos = mp_card->mapTo(mp_game->mainWidget(), QPoint(0,0));
        mp_card->setParent(mp_game->mainWidget());
        mp_card->move(pos);
    }
    mp_card->raise();
    mp_card->show();
    m_currPos = m_srcPos = mp_card->pos();
    m_destPos = mp_destPocket->mapTo(mp_game->mainWidget(), mp_destPocket->newCardPosition());
    m_length  = sqrt(pow(m_destPos.x() - m_srcPos.x(), 2) + pow(m_destPos.y() - m_srcPos.y(), 2));
    mp_card->setShadowMode();
    sm_timer.start(tickTime, this);
}

void CardMovementEvent::timerEvent(QTimerEvent*)
{
    m_tick++;
    qreal progress = (m_tick * pixelsPerTick) / m_length;
    if (progress >= 1) {
        stopTransition();
    } else {
        m_currPos = m_srcPos + (m_destPos - m_srcPos) * progress;
        mp_card->move(m_currPos);
    }
}

void CardMovementEvent::stopTransition()
{
    sm_timer.stop();
    if (!m_structCardMovement.cardDetails.cardType.isEmpty()) {
        mp_card->setCardId(m_structCardMovement.cardDetails.cardId);
        mp_card->setCardClass(m_structCardMovement.cardDetails.cardType);
        mp_card->applyNewProperties();
    }
    mp_card->unsetShadowMode();
    mp_destPocket->push(mp_card);
    m_isRunning = 0;
    emit finished(this);
}