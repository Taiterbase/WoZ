#include "ScriptPCH.h"

bool GossipHello_EDtele(Player *player, Creature *creature)
{
	// mm
	if (player->HasItemCount(60000, 1, true))
	{
		player->ADD_GOSSIP_ITEM( 5, "[Elite Donor Options]"				,GOSSIP_SENDER_MAIN, 1);
	}
		player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
		return true;
}
void SendDefaultMenu_EDtele(Player *player, Creature *creature, uint32 action )
{
switch(action)
{
case 0: //mm
	if (player->HasItemCount(60000, 1, true))
	{
		player->ADD_GOSSIP_ITEM( 5, "[Elite Donor Options]"				,GOSSIP_SENDER_MAIN, 1);
	}
		player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
		break;
	
case 1: // ed opt
    player->ADD_GOSSIP_ITEM( 5, "[The Emerald Dream]"	,GOSSIP_SENDER_MAIN, 2);
	player->ADD_GOSSIP_ITEM( 5, "[WoC Party Island]"	,GOSSIP_SENDER_MAIN, 3);
	player->ADD_GOSSIP_ITEM( 5, "[Emerald Vendors]"		,GOSSIP_SENDER_MAIN, 4);
	player->ADD_GOSSIP_ITEM( 5, "[Emerald Profession]"	,GOSSIP_SENDER_MAIN, 5);
	player->ADD_GOSSIP_ITEM( 5, "[Emerald Trainers]"	,GOSSIP_SENDER_MAIN, 60);
	player->ADD_GOSSIP_ITEM( 5, "[Emerald Skydive]"		,GOSSIP_SENDER_MAIN, 70);
	if (player->getClass() == CLASS_HUNTER)
	player->ADD_GOSSIP_ITEM( 5, "[Level My Pet]"		,GOSSIP_SENDER_MAIN, 303);
	if (player->getClass() == CLASS_HUNTER)
	player->ADD_GOSSIP_ITEM( 5, "Get a Pet!"			,GOSSIP_SENDER_MAIN, 400);
	
	player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
	break;

// emerald vends
case 4:
	player->ADD_GOSSIP_ITEM( 5, "[Emerald's Custom Content Vendors]"		,GOSSIP_SENDER_MAIN, 40);
	player->ADD_GOSSIP_ITEM( 5, "[Emerald's Reagent Vendors]"				,GOSSIP_SENDER_MAIN, 41);
	player->ADD_GOSSIP_ITEM( 5, "[Emerald's Retail Vendors]"				,GOSSIP_SENDER_MAIN, 42);
	
	player->ADD_GOSSIP_ITEM( 7, "[Back]"									,GOSSIP_SENDER_MAIN, 1);
	
	player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
	break;
	
// emerald prof
case 5:
	player->ADD_GOSSIP_ITEM( 5, "[First Floor Profession Trainers]"			,GOSSIP_SENDER_MAIN, 50);
	player->ADD_GOSSIP_ITEM( 5, "[Emerald's Reagent Vendors]"				,GOSSIP_SENDER_MAIN, 51);
	player->ADD_GOSSIP_ITEM( 5, "[Second Floor Profession Trainers]"		,GOSSIP_SENDER_MAIN, 52);
	
	player->ADD_GOSSIP_ITEM( 7, "[Back]"									,GOSSIP_SENDER_MAIN, 1);
	
	player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
	break;
	
// ---### Elite Donor Options ###---
case 20: // ED
	player->CLOSE_GOSSIP_MENU();
	player->TeleportTo(169, -248.969f, 2906.88f, 98.4927f, 3.81664f); // sel done
	break;
	
case 30: // party isle
	player->CLOSE_GOSSIP_MENU();
	player->TeleportTo(1, 16223.94f, 16248.89f, 12.2025f, 1.43409f); // sel done
	break;

case 40: // Emerald cust cont vend
	player->CLOSE_GOSSIP_MENU();
	player->TeleportTo(169, -295.305847f, 2885.3896f, 97.225f, 3.665f);  // sel done
	break;
	
case 41: // Emerald reagents
	player->CLOSE_GOSSIP_MENU();
	player->TeleportTo(169, -162.2336f, 2905.369f, 100.09f, 3.265f); // sel done
	break;
	
case 42: // Emerald retail vend
	player->CLOSE_GOSSIP_MENU();
	player->TeleportTo(169, -337.228424f, 2937.094f, 97.8224f, 3.10429f);  // sel done
	break;

case 50: // Emerald profession Trainers
	player->CLOSE_GOSSIP_MENU();
	player->TeleportTo(169, -162.2336f, 2905.369f, 100.09f, 3.265f); // sel done
	break;
	
case 51: // Emerald reagent vends 2
	player->CLOSE_GOSSIP_MENU();
	player->TeleportTo(169, -162.2336f, 2905.369f, 100.09f, 3.265f); // sel done
	break;

case 52: // Emerald top floor prof build
	player->CLOSE_GOSSIP_MENU();
	player->TeleportTo(169, -160.8299f, 2915.911f, 114.6723f, 4.7292f);  // sel done
	break;

case 60: // Emerald Trainers
	player->CLOSE_GOSSIP_MENU();
	player->TeleportTo(169, -234.6968f, 3020.811f, 98.135f, 4.6796f);  // sel done
	break;

case 70: //em sd
	player->CLOSE_GOSSIP_MENU();
	player->TeleportTo(169, -305.723175f, 3051.3704f, 225.1394f, 5.482f); // sel done
	break;
	
// hunter options
case 303: // level pet
    player->CLOSE_GOSSIP_MENU();
    if (Creature* pet = player->GetPet())
	{
	    ((Pet*)pet)->GivePetLevel(player->getLevel());
		((Pet*)pet)->SetLoyaltyLevel(BEST_FRIEND);
		player->GetSession()->SendNotification("Your pet has reached your level.");
	}
	else
	{
	player->GetSession()->SendNotification("You do not have a pet.");
	}
	break;
	
case 400: //getapet
	player->CLOSE_GOSSIP_MENU();
	player->TeleportTo(169, -163.130f, 2975.344f, 124.4122f, 2.4589f); // sel done
	break;

}
}
bool GossipSelect_EDtele(Player *player, Creature *creature, uint32 sender, uint32 action)
{

	if (sender == GOSSIP_SENDER_MAIN)
	SendDefaultMenu_EDtele( player, creature, action );

return true;
}

void AddSC_EDtele()
{
    Script *newscript;

	newscript = new Script;
    newscript->Name = "EDtele";
    newscript->pGossipHello = &GossipHello_EDtele;
    newscript->pGossipSelect = &GossipSelect_EDtele;
    newscript->RegisterSelf();
}