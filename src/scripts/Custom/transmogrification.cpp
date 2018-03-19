/*####
##TRANSMOGRIFICATION
####*/

#include "ScriptPCH.h"

#define transmog_cost 2000000 // 200 gold

bool GossipHello_transmog(Player* player, Creature* _creature)
{
    player->ADD_GOSSIP_ITEM(0, "Christmas Outfit (200 gold)",		GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
	player->ADD_GOSSIP_ITEM(0, "Chaos' Wardrobe (200 gold)",		GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
	player->ADD_GOSSIP_ITEM(0, "Halloween Costume! (200 gold)",		GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
	player->ADD_GOSSIP_ITEM(0, "Fun Rogue Set (200 gold)",			GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
	player->ADD_GOSSIP_ITEM(0, "Fun Mage Set (200 gold)",			GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);
	player->ADD_GOSSIP_ITEM(0, "Fun Priest Set (200 gold)",			GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
	player->ADD_GOSSIP_ITEM(0, "Fun Shadow Warlock Set (200 gold)",	GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 12);
	player->ADD_GOSSIP_ITEM(0, "Fun Warlock Set 2 (200 gold)",		GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 13);
	player->ADD_GOSSIP_ITEM(0, "Deathbone Set (200 gold)",			GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 14);
	player->ADD_GOSSIP_ITEM(0, "Bloody Rogue Costume (200 gold)",	GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 15);
	player->ADD_GOSSIP_ITEM(0, "Hunter Steampunk (200 gold)", 		GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 16);
	player->ADD_GOSSIP_ITEM(0, "Ladies' Steampunk (200 gold)",		GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 17);
	player->ADD_GOSSIP_ITEM(0, "Caster Steampunk (200 gold)",		GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 18);


    player->SEND_GOSSIP_MENU(50055,_creature->GetGUID());
    return true;
}

void UpdateGear(Player* player)
{
    // Send update to player
    player->SendUpdateToPlayer(player);

    // Force client to reload this player
    WorldPacket data(SMSG_FORCE_DISPLAY_UPDATE, 8);
    data << player->GetGUID();
    player->SendMessageToSet(&data,true);

    // Vanish visual spell
    player->CastSpell(player,24222,true);
}

bool GossipSelect_transmog(Player* player, Creature* _creature, uint32 sender, uint32 action)
{
    if(player->GetMoney() > transmog_cost)
	{
        player->ModifyMoney(-transmog_cost);
        switch (action)
        {
            case GOSSIP_ACTION_INFO_DEF + 1:
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 21524);
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 0); // shoulder
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_4_0 , 0); // shirt
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 34085);
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 0); // waist
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 0); // pants
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 34086);
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 0); // wrist
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 0); // gloves
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_15_0 , 0); // cloak
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_16_0 , 0); // mainhand
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_17_0 , 0); // offhand
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_18_0 , 0); // bow
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_19_0 , 0); // tabard
            break;

			case GOSSIP_ACTION_INFO_DEF + 6:
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 32329); // helm
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 32273); // shoulder
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_4_0 , 6833); // shirt
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 16565); // chest
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 20150); // waste
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 16567); // pants
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 16569); // boots
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 23092); // wrist
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 16571); // gloves
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_15_0 , 28660); // cloak
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_18_0 , 34334); // bow
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_19_0 , 19031); // tabard
			break;

			case GOSSIP_ACTION_INFO_DEF + 7:
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 33808); // helm
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 28333); // shoulder
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_4_0 , 0); // shirt
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 28334); // chest
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 0); // waste
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 28332); // pants
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 32793); // boots
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 23092); // wrist
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 28335); // gloves
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_15_0 , 0); // cloak
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_16_0 , 0); // mainhand
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_17_0 , 0); // offhand
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_18_0 , 0); // bow
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_19_0 , 0); // tabard
			break;

			case GOSSIP_ACTION_INFO_DEF + 8:
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 9470); // helm
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 23258); // shoulder
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_4_0 , 4335); // shirt
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 8200); // chest
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 0); // waist
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 0); // pants
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 35141); // boots
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 34436); // wrist
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 0); // gloves
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_15_0 , 33484); // cloak
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_16_0 , 0); // mainhand
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_17_0 , 0); // offhand
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_18_0 , 0); // bow
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_19_0 , 0); // tabard
			break;

			case GOSSIP_ACTION_INFO_DEF + 10:
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 23909); // helm
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 23311); // shoulder
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_4_0 , 0); // shirt
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 23297); // chest
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 0); // waist
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 0); // pants
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 23283); // boots
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 0); // wrist
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 23282); // gloves
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_15_0 , 0); // cloak
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_16_0 , 29133); // mainhand
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_17_0 , 0); // offhand
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_18_0 , 0); // bow
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_19_0 , 0); // tabard
			break;

			case GOSSIP_ACTION_INFO_DEF + 11:
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 32235); // helm
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 22983); // shoulder
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_4_0 , 0); // shirt
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 34233); // chest
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 0); // waist
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 0); // pants
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 0); // boots
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 0); // wrist
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 0); // gloves
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_15_0 , 0); // cloak
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_16_0 , 0); // mainhand
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_17_0 , 0); // offhand
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_18_0 , 0); // bow
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_19_0 , 0); // tabard
			break;

			case GOSSIP_ACTION_INFO_DEF + 12:
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 28963); // helm
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 22499); // shoulder
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_4_0 , 3427); // shirt
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 21364); // chest
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 0); // waist
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 21362); // pants
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 21359); // boots
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 0); // wrist
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 28968); // gloves
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_15_0 , 0); // cloak
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_16_0 , 0); // mainhand
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_17_0 , 0); // offhand
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_18_0 , 0); // bow
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_19_0 , 0); // tabard
			break;

			case GOSSIP_ACTION_INFO_DEF + 13:
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 33677); // helm
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 27775); // shoulder
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_4_0 , 3427); // shirt
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 28230); // chest
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 35164); // waist
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 0); // pants
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 35149); // boots
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 0); // wrist
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 27536); // gloves
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_15_0 , 33484); // cloak
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_16_0 , 30732); // mainhand
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_17_0 , 0); // offhand
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_18_0 , 0); // bow
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_19_0 , 0); // tabard
			break;

			case GOSSIP_ACTION_INFO_DEF + 14:
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 21347); // helm
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 29316); // shoulder
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_4_0 , 3427); // shirt
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 13394); // chest
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 18547); // waist
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 29783); // pants
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 21706); // boots
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 0); // wrist
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 18722); // gloves
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_15_0 , 0); // cloak
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_16_0 , 22798); // mainhand
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_17_0 , 0); // offhand
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_18_0 , 0); // bow
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_19_0 , 0); // tabard
			break;

			case GOSSIP_ACTION_INFO_DEF + 15:
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 16908); // helm
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 31030); // shoulder
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_4_0 , 14617); // shirt
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 31028); // chest
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 16910); // waist
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 31029); // pants
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 16906); // boots
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 0); // wrist
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 31026); // gloves
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_15_0 , 34190); // cloak
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_16_0 , 30865); // mainhand
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_17_0 , 30865); // offhand
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_18_0 , 0); // bow
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_19_0 , 0); // tabard
			break;

			case GOSSIP_ACTION_INFO_DEF + 16:
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 4368); // helm
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 15583); // shoulder
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_4_0 , 4344); // shirt
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 4074); // chest
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 27521); // waist
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 4800); // pants
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 8130); // boots
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 0); // wrist
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 25669); // gloves
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_15_0 , 21456); // cloak
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_16_0 , 20434); // mainhand
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_17_0 , 0); // offhand
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_18_0 , 23746); // bow
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_19_0 , 0); // tabard
			break;

			case GOSSIP_ACTION_INFO_DEF + 17:
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 4368); // helm
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 0); // shoulder
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_4_0 , 0); // shirt
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 24679); // chest
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 24677); // waist
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 0); // pants
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 24678); // boots
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 0); // wrist
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 11888); // gloves
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_15_0 , 0); // cloak
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_16_0 , 20434); // mainhand
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_17_0 , 0); // offhand
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_18_0 , 23746); // bow
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_19_0 , 0); // tabard
			break;

			case GOSSIP_ACTION_INFO_DEF + 18:
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_1_0 , 34353); // helm
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_3_0 , 33757); // shoulder
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_4_0 , 0); // shirt
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_5_0 , 28964); // chest
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_6_0 , 35164); // waist
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_7_0 , 0); // pants
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_8_0 , 35149); // boots
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_9_0 , 0); // wrist
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_10_0 , 28968); // gloves
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_15_0 , 33484); // cloak
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_16_0 , 28345); // mainhand
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_17_0 , 0); // offhand
            player->SetUInt32Value(PLAYER_VISIBLE_ITEM_18_0 , 0); // bow
			player->SetUInt32Value(PLAYER_VISIBLE_ITEM_19_0 , 31405); // tabard
			break;
			}
        player->PlayerTalkClass->CloseGossip();
        UpdateGear(player);
        return true;
    }
    else
    player->PlayerTalkClass->CloseGossip();
    player->SendBuyError(BUY_ERR_NOT_ENOUGHT_MONEY, _creature, 0, 0);
    return true;
}


void AddSC_transmog()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name="transmog";
    newscript->pGossipHello =                  &GossipHello_transmog;
    newscript->pGossipSelect =                &GossipSelect_transmog;
    newscript->RegisterSelf();
}