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
-Good Help is Hard to Find-\
----Creature Script--------/
--------------------------/
________________________*/

enum TrollSlave
{
	QUEST_DEFIANT_TROLLS    = 99996,
	SPELL_BUFF_SLEEP        = 17743,
	SPELL_SHOCK_TROLL       = 150008
};

class npc_troll_slave : public CreatureScript
{
public:
	npc_troll_slave() : CreatureScript("npc_troll_slave") { }

	CreatureAI* GetAI(Creature* creature) const override
	{
		return new npc_troll_slaveAI(creature);
	}

	struct npc_troll_slaveAI : public ScriptedAI
	{
		npc_troll_slaveAI(Creature* creature) : ScriptedAI(creature)
		{
			Initialize();
		}

		void Initialize()
		{
			RebuffTimer = 0;
		}

		uint32 RebuffTimer;
		
		void Reset() override
		{
			Initialize();
		}

		void SpellHit(Unit* caster, const SpellInfo* spell) override
		{
			if (spell->Id != SPELL_SHOCK_TROLL)
				return;

			Player* player = caster->ToPlayer();


			player->KilledMonsterCredit(me->GetEntry(), me->GetGUID());
			me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_WORK_MINING);
			me->RemoveAura(SPELL_BUFF_SLEEP);
			Talk(0, caster);
		}

		void UpdateAI(uint32 diff)
		{
			if (RebuffTimer <= diff)
			{
				switch (urand(0, 1))
				{
				case 0:
					me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_WORK_MINING);
					break;
				case 1:
				    DoCast(me, SPELL_BUFF_SLEEP);
					break;
				}
				RebuffTimer = 120000; // reset timer
			}
			else
				RebuffTimer -= diff;
			if (!UpdateVictim())
				return;
		}
	};
};

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
	new npc_troll_slave();
	new npc_delinquent_miner();
}