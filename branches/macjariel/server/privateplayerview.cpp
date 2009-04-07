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
#include "privateplayerview.h"
#include "player.h"
#include "cardabstract.h"

PrivatePlayerView::PrivatePlayerView(Player* player)
 : PublicPlayerView(player)
{
}


PrivatePlayerView::~PrivatePlayerView()
{
}

PlayerRole PrivatePlayerView::role() const
{
    return mp_player->role();
}

QList<CardAbstract* > PrivatePlayerView::hand() const
{
    return mp_player->cardsInHand();
}

PrivatePlayerData PrivatePlayerView::privatePlayerData() const
{
    PrivatePlayerData res;
    res.id          = id();
    res.role        = role();
    foreach (CardAbstract* card, hand()) {
        CardData cardData;
        cardData.id = card->id();
        cardData.type = card->type();
        res.hand.append(cardData);
    }
    return res;
}


StructPlayer PrivatePlayerView::structPlayer() const
{
    return mp_player->structPlayer(1);
}

