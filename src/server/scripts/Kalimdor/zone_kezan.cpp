/*
Staleness' CataclysmicWrath
for Trinitycore 3.3.5a
*/

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "Player.h"
#include "ScriptedGossip.h"
#include "GossipDef.h"

/*_______________________
-------------------------\
--------------------------\
----Delinquent Miners------\
----Gossip Script----------/
--------------------------/
________________________*/


class npc_delinquent_miner : public CreatureScript
{
public:
	npc_delinquent_miner() : CreatureScript("npc_delinquent_miner") { }

	bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
	{
		player->PlayerTalkClass->ClearMenus();
		{
			creature->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_NONE);

			switch (urand(0, 1))
			{
			case 0:
				creature->Say(100071, player); // these are broadcast text ids
				player->KilledMonsterCredit(creature->GetEntry(), creature->GetGUID());
				creature->SetWalk(true);
				creature->GetMotionMaster()->MovePoint(0, -8442.295898f, 1323.998901f, 101.797685f);  // move away from the pool
				creature->DespawnOrUnsummon(5000);
				break;
			case 1:
				creature->Say(100068, player); // these are broadcast text ids
				creature->setFaction(1902);
				creature->Attack(player, true);
				creature->DespawnOrUnsummon(100000);   // if no one kills him, despawn
				break;
			}
		}
		return true;
	}
};

void AddSC_kezan()
{
	new npc_delinquent_miner();
}