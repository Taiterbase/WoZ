#include "ScriptPCH.h"

bool GossipHello_Playertools(Player *player, Creature *creature)
{
	if (player->HasItemCount(60000, 1, true))
	{
		player->ADD_GOSSIP_ITEM( 5, "[Player Tools]"			,GOSSIP_SENDER_MAIN, 2);
	}
		player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
		return true;
}
void SendDefaultMenu_Playertools(Player *player, Creature *creature, uint32 action )
{
switch(action)
{

case 0:
	if (player->HasItemCount(60000, 1, true))
	{
	player->ADD_GOSSIP_ITEM( 5, "[Player Tools]"				,GOSSIP_SENDER_MAIN, 2);
	}
	player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
	break;

case 2:
	if (player->getClass() == CLASS_PALADIN)
	player->ADD_GOSSIP_ITEM( 5, "[Learn Missing Spells]"		,GOSSIP_SENDER_MAIN, 304);
	if (player->getClass() == CLASS_WARRIOR)
	player->ADD_GOSSIP_ITEM( 5, "[Learn Missing Spells]"		,GOSSIP_SENDER_MAIN, 304);
	if (player->getClass() == CLASS_SHAMAN)
	player->ADD_GOSSIP_ITEM( 5, "[Learn Missing Spells]"		,GOSSIP_SENDER_MAIN, 304);
	if (player->getClass() == CLASS_WARLOCK)
	player->ADD_GOSSIP_ITEM( 5, "[Learn Missing Spells]"		,GOSSIP_SENDER_MAIN, 304);
	if (player->getClass() == CLASS_ROGUE)
	player->ADD_GOSSIP_ITEM( 5, "[Learn Missing Spells]"		,GOSSIP_SENDER_MAIN, 304);
	if (player->getClass() == CLASS_DRUID)
	player->ADD_GOSSIP_ITEM( 5, "[Learn Missing Spells]"		,GOSSIP_SENDER_MAIN, 304);
	if (player->getClass() == CLASS_HUNTER)
	player->ADD_GOSSIP_ITEM( 5, "[Learn Missing Spells]"		,GOSSIP_SENDER_MAIN, 304);
	if (player->getClass() == CLASS_HUNTER)
	player->ADD_GOSSIP_ITEM( 5, "[Level my Pet]"				,GOSSIP_SENDER_MAIN, 303);
	player->ADD_GOSSIP_ITEM( 5, "[Max out my Weapon Skills]"	,GOSSIP_SENDER_MAIN, 302);
	player->ADD_GOSSIP_ITEM( 5, "[Teach me Riding]"				,GOSSIP_SENDER_MAIN, 317);
	player->ADD_GOSSIP_ITEM( 5, "[Reset my Talents]"			,GOSSIP_SENDER_MAIN, 319);
	if (player->getClass() == CLASS_HUNTER)
	player->ADD_GOSSIP_ITEM( 5, "[Pet Store]"					,GOSSIP_SENDER_MAIN, 400);
	
	player->ADD_GOSSIP_ITEM( 7, "[Main Menu]"					,GOSSIP_SENDER_MAIN, 0);
	
	player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
	break;
	
// ### Player Tools ###
case 302:
	player->CLOSE_GOSSIP_MENU();
	player->UpdateSkillsToMaxSkillsForLevel();
	player->GetSession()->SendNotification("Your weapon skills have been 'Maxed'.");
	break;
case 303:
    player->CLOSE_GOSSIP_MENU();
    if (Creature* pet = player->GetPet())
	{
	    ((Pet*)pet)->GivePetLevel(player->getLevel());
		((Pet*)pet)->SetLoyaltyLevel(BEST_FRIEND);
		player->GetSession()->SendNotification("Your pet has reached your level!");
	}
	else
	{
	player->GetSession()->SendNotification("You don't have a pet!");
	}
	break;
case 304:
	player->CLOSE_GOSSIP_MENU();
	if (player->getClass() == CLASS_PALADIN)
	{
		player->learnSpell(7328);
		player->learnSpell(13819);
		player->learnSpell(23214);
		player->learnSpell(5502);
	}
	if (player->getClass() == CLASS_WARRIOR)
	{
		player->learnSpell(2458);
		player->learnSpell(71);
		player->learnSpell(20252);
		player->learnSpell(7386);
		player->learnSpell(674);
	}
	if (player->getClass() == CLASS_SHAMAN)
	{
		player->learnSpell(2075);
		player->learnSpell(8073);
		player->learnSpell(5396);
		player->learnSpell(674);
	}
	if (player->getClass() == CLASS_WARLOCK)
	{
		player->learnSpell(688);
		player->learnSpell(697);
		player->learnSpell(712);
		player->learnSpell(691);
		player->learnSpell(1122);
		player->learnSpell(5784);
		player->learnSpell(23161);
	}
	if (player->getClass() == CLASS_ROGUE)
	{
		player->learnSpell(2842);
		player->learnSpell(674);
	}
	if (player->getClass() == CLASS_DRUID)
	{
		player->learnSpell(1066);
		player->learnSpell(5487);
		player->learnSpell(9634);
		player->learnSpell(6807);
	}
	if (player->getClass() == CLASS_HUNTER)
	{
		player->learnSpell(883);
		player->learnSpell(2641);
		player->learnSpell(6991);
		player->learnSpell(982);
		player->learnSpell(1515);
		player->learnSpell(674);
	}
	player->GetSession()->SendNotification("Your missing spells have been added.");
	break;

case 400: //getapet
	player->CLOSE_GOSSIP_MENU();
	player->TeleportTo(0, -6375.71f, 1260.069f, 7.0f, 5.418462f);
	break;

// -----------------------------### END OF Playertools ###-----------------------------
}
}
bool GossipSelect_Playertools(Player *player, Creature *creature, uint32 sender, uint32 action)
{
	// Main Menu
	if (sender == GOSSIP_SENDER_MAIN)
	SendDefaultMenu_Playertools( player, creature, action );

return true;
}

void AddSC_Playertools()
{
    Script *newscript;

	newscript = new Script;
    newscript->Name = "Playertools";
    newscript->pGossipHello = &GossipHello_Playertools;
    newscript->pGossipSelect = &GossipSelect_Playertools;
    newscript->RegisterSelf();
}