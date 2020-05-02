#include "Player.h"
#include "Unit.h"
#include "Creature.h"
#include "ScriptedCreature.h"
#include "ObjectMgr.h"
#include "SpellScript.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "PlayerAI.h"
#include "GameEventMgr.h"

enum
{
	GILNEAN_TRANSFORM_MALE = 37101,
	GILNEAN_TRANSFORM_FEMALE = 37105,
	GILNEAN_TRANSFORM_QUEST = 4902
};

class GilneanStartForm : public PlayerScript
{
public:
	GilneanStartForm() : PlayerScript("GilneanStartForm") { }

	void OnLogin(Player* player, bool firstLogin)
	{
		if (player->GetRace() != RACE_FEL_ORC)
			return;

		if (player->GetQuestStatus(GILNEAN_TRANSFORM_QUEST) != (QUEST_STATUS_COMPLETE))
		{
			if (player->GetGender() == GENDER_MALE)
			{
				player->SetDisplayId(GILNEAN_TRANSFORM_MALE);
				return;
			}
			else
			{
				player->SetDisplayId(GILNEAN_TRANSFORM_FEMALE);
				return;
			}
		}
	}
};

void AddSC_gilneas()
{
	new GilneanStartForm();
}
