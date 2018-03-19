/*
 * This file is part of the BlizzLikeCore Project.
 * See CREDITS and LICENSE files for Copyright information.
 */

#ifndef __WORLDSESSION_H
#define __WORLDSESSION_H

#include "Common.h"
#include "QueryResult.h"
#include "World.h"

struct ItemPrototype;
struct AuctionEntry;
struct DeclinedName;

class Creature;
class Item;
class Object;
class Player;
class Unit;
class WorldPacket;
class WorldSocket;
class QueryResult;
class LoginQueryHolder;
class CharacterHandler;

struct OpcodeHandler;

enum PartyOperation
{
    PARTY_OP_INVITE = 0,
    PARTY_OP_LEAVE = 2
};

enum PartyResult
{
    PARTY_RESULT_OK                   = 0,
    PARTY_RESULT_CANT_FIND_TARGET     = 1,
    PARTY_RESULT_NOT_IN_YOUR_PARTY    = 2,
    PARTY_RESULT_NOT_IN_YOUR_INSTANCE = 3,
    PARTY_RESULT_PARTY_FULL           = 4,
    PARTY_RESULT_ALREADY_IN_GROUP     = 5,
    PARTY_RESULT_YOU_NOT_IN_GROUP     = 6,
    PARTY_RESULT_YOU_NOT_LEADER       = 7,
    PARTY_RESULT_TARGET_UNFRIENDLY    = 8,
    PARTY_RESULT_TARGET_IGNORE_YOU    = 9,
    PARTY_RESULT_INVITE_RESTRICTED    = 13
};

// Player session in the World
class WorldSession
{
    friend class CharacterHandler;

    public:
        WorldSession(uint32 id, WorldSocket *sock, uint32 sec, bool ispremium, uint8 expansion, time_t mute_time, LocaleConstant locale);
        ~WorldSession();

        bool PlayerLoading() const { return m_playerLoading; }
        bool PlayerLogout() const { return m_playerLogout; }
        bool PlayerLogoutWithSave() const { return m_playerLogout && m_playerSave; }

        void SizeError(WorldPacket const& packet, uint32 size) const;

        void SendPacket(WorldPacket const* packet);
        void SendNotification(const char *format,...) ATTR_PRINTF(2,3);
        void SendNotification(int32 string_id,...);
        void SendPetNameInvalid(uint32 error, const std::string& name, DeclinedName *declinedName);
        void SendLfgResult(uint32 type, uint32 entry, uint8 lfg_type);
        void SendPartyResult(PartyOperation operation, const std::string& member, PartyResult res);
        void SendAreaTriggerMessage(const char* Text, ...) ATTR_PRINTF(2,3);

        uint32 GetSecurity() const { return _security; }
        bool IsPremium() const { return _ispremium; }
        uint32 GetAccountId() const { return _accountId; }
        Player* GetPlayer() const { return _player; }
        char const* GetPlayerName() const;
        void SetSecurity(uint32 security) { _security = security; }
        std::string const& GetRemoteAddress() { return m_Address; }
        void SetPlayer(Player* plr) { _player = plr; }
        uint8 Expansion() const { return m_expansion; }

        // Session in auth.queue currently
        void SetInQueue(bool state) { m_inQueue = state; }

        // Is the user engaged in a log out process?
        bool isLogingOut() const { return _logoutTime || m_playerLogout; }

        // Engage the logout process for the user
        void LogoutRequest(time_t requestTime)
        {
            _logoutTime = requestTime;
        }

        // Is logout cooldown expired?
        bool ShouldLogOut(time_t currTime) const
        {
            return (_logoutTime > 0 && currTime >= _logoutTime + 20);
        }

        void LogoutPlayer(bool Save);
        void KickPlayer();

        void QueuePacket(WorldPacket* new_packet);
        bool Update(uint32 diff);

        // Handle the authentication waiting queue (to be completed)
        void SendAuthWaitQue(uint32 position);

        //void SendTestCreatureQueryOpcode(uint32 entry, uint64 guid, uint32 testvalue);
        void SendNameQueryOpcode(Player* p);
        void SendNameQueryOpcodeFromDB(uint64 guid);
        static void SendNameQueryOpcodeFromDBCallBack(QueryResult_AutoPtr result, uint32 accountId);

        void SendTrainerList(uint64 guid);
        void SendTrainerList(uint64 guid, const std::string& strTitle);
        void SendListInventory(uint64 guid);
        void SendShowBank(uint64 guid);
        void SendTabardVendorActivate(uint64 guid);
        void SendSpiritResurrect();
        void SendBindPoint(Creature* npc);
        void SendGMTicketGetTicket(uint32 status, char const* text);

        void SendAttackStop(Unit const* enemy);

        void SendBattlegGroundList(uint64 guid, uint32 bgTypeId);

        void SendTradeStatus(uint32 status);
        void SendCancelTrade();

        void SendStablePet(uint64 guid);
        void SendPetitionQueryOpcode(uint64 petitionguid);
        void SendUpdateTrade();

        //pet
        void SendPetNameQuery(uint64 guid, uint32 petnumber);

        bool SendItemInfo(uint32 itemid, WorldPacket data);

        // External Mail
        static void SendExternalMails();

        //auction
        void SendAuctionHello(uint64 guid, Creature* unit);
        void SendAuctionCommandResult(uint32 auctionId, uint32 Action, uint32 ErrorCode, uint32 bidError = 0);
        void SendAuctionBidderNotification(uint32 location, uint32 auctionId, uint64 bidder, uint32 bidSum, uint32 diff, uint32 item_template);
        void SendAuctionOwnerNotification(AuctionEntry * auction);
        void SendAuctionOutbiddedMail(AuctionEntry * auction, uint32 newPrice);
        void SendAuctionCancelledToBidderMail(AuctionEntry* auction);

        //Item Enchantment
        void SendEnchantmentLog(uint64 Target, uint64 Caster,uint32 ItemID,uint32 SpellID);
        void SendItemEnchantTimeUpdate(uint64 Playerguid, uint64 Itemguid,uint32 slot,uint32 Duration);

        //Taxi
        void SendTaxiStatus(uint64 guid);
        void SendTaxiMenu(Creature* unit);
        void SendDoFlight(uint16 MountId, uint32 path, uint32 pathNode = 0);
        bool SendLearnNewTaxiNode(Creature* unit);
        void SendActivateTaxiReply(ActivateTaxiReply reply);

        // Guild/Arena Team
        void SendGuildCommandResult(uint32 typecmd, const std::string& str, uint32 cmdresult);
        void SendArenaTeamCommandResult(uint32 team_action, const std::string& team, const std::string& player, uint32 error_id);
        void SendNotInArenaTeamPacket(uint8 type);
        void SendPetitionShowList(uint64 guid);
        void SendSaveGuildEmblem(uint32 msg);
        void SendBattleGroundOrArenaJoinError(uint8 err);

        // Looking For Group
        // TRUE values set by client sending CMSG_LFG_SET_AUTOJOIN and CMSG_LFM_CLEAR_AUTOFILL before player login
        bool LookingForGroup_auto_join;
        bool LookingForGroup_auto_add;

        void BuildPartyMemberStatsChangedPacket(Player* player, WorldPacket* data);

        void DoLootRelease(uint64 lguid);

        // Account mute time
        time_t m_muteTime;

        // Locales
        LocaleConstant GetSessionDbcLocale() const { return m_sessionDbcLocale; }
        int GetSessionDbLocaleIndex() const { return m_sessionDbLocaleIndex; }
        const char *GetBlizzLikeString(int32 entry) const;

        uint32 GetLatency() const { return m_latency; }
        void SetLatency(uint32 latency) { m_latency = latency; }
        uint32 getDialogStatus(Player* pPlayer, Object* questgiver, uint32 defstatus);

        time_t m_timeOutTime;
        void UpdateTimeOutTime(uint32 diff)
        {
            if (diff > m_timeOutTime)
                m_timeOutTime = 0;
            else
                m_timeOutTime -= diff;
        }
        void ResetTimeOutTime()
        {
            m_timeOutTime = sWorld.getConfig(CONFIG_SOCKET_TIMEOUTTIME);
        }
        bool IsConnectionIdle() const
        {
            if (m_timeOutTime <= 0 && !m_inQueue)
                return true;
            return false;
        }

    // Misc;
    void SendPlaySpellVisual(ObjectGuid guid, uint32 spellArtKit);
    void SendItemPageInfo(ItemPrototype* itemProto);

    public:                                                 // opcodes handlers

        void Handle_NULL(WorldPacket& recvPacket);          // not used
        void Handle_EarlyProccess(WorldPacket& recvPacket);// just mark packets processed in WorldSocket::OnRead
        void Handle_ServerSide(WorldPacket& recvPacket);    // sever side only, can't be accepted from client
        void Handle_Deprecated(WorldPacket& recvPacket);    // never used anymore by client

        void HandleCharEnumOpcode(WorldPacket& recvPacket);
        void HandleCharDeleteOpcode(WorldPacket& recvPacket);
        void HandleCharCreateOpcode(WorldPacket& recvPacket);
        void HandlePlayerLoginOpcode(WorldPacket& recvPacket);
        void HandleCharEnum(QueryResult_AutoPtr result);
        void HandlePlayerLogin(LoginQueryHolder * holder);

        // played time
        void HandlePlayedTime(WorldPacket& recvPacket);

        // new
        void HandleMoveUnRootAck(WorldPacket& recvPacket);
        void HandleMoveRootAck(WorldPacket& recvPacket);
        void HandleLookingForGroup(WorldPacket& recvPacket);

        // new inspect
        void HandleInspectOpcode(WorldPacket& recvPacket);

        // new party stats
        void HandleInspectHonorStatsOpcode(WorldPacket& recvPacket);

        void HandleMoveWaterWalkAck(WorldPacket& recvPacket);
        void HandleFeatherFallAck(WorldPacket& recv_data);

        void HandleMoveHoverAck(WorldPacket& recv_data);

        void HandleMountSpecialAnimOpcode(WorldPacket &recvdata);

        // character view
        void HandleToggleHelmOpcode(WorldPacket& recv_data);
        void HandleToggleCloakOpcode(WorldPacket& recv_data);

        // repair
        void HandleRepairItemOpcode(WorldPacket& recvPacket);

        // Knockback
        void HandleMoveKnockBackAck(WorldPacket& recvPacket);

        void HandleMoveTeleportAck(WorldPacket& recvPacket);
        void HandleForceSpeedChangeAck(WorldPacket& recv_data);

        void HandlePingOpcode(WorldPacket& recvPacket);
        void HandleAuthSessionOpcode(WorldPacket& recvPacket);
        void HandleRepopRequestOpcode(WorldPacket& recvPacket);
        void HandleAutostoreLootItemOpcode(WorldPacket& recvPacket);
        void HandleLootMoneyOpcode(WorldPacket& recvPacket);
        void HandleLootOpcode(WorldPacket& recvPacket);
        void HandleLootReleaseOpcode(WorldPacket& recvPacket);
        void HandleLootMasterGiveOpcode(WorldPacket& recvPacket);
        void HandleWhoOpcode(WorldPacket& recvPacket);
        void HandleLogoutRequestOpcode(WorldPacket& recvPacket);
        void HandlePlayerLogoutOpcode(WorldPacket& recvPacket);
        void HandleLogoutCancelOpcode(WorldPacket& recvPacket);

        // GM Ticket opcodes
        void HandleGMTicketCreateOpcode(WorldPacket& recvPacket);
        void HandleGMTicketUpdateOpcode(WorldPacket& recvPacket);
        void HandleGMTicketDeleteOpcode(WorldPacket& recvPacket);
        void HandleGMTicketGetTicketOpcode(WorldPacket& recvPacket);
        void HandleGMTicketSystemStatusOpcode(WorldPacket& recvPacket);

        void HandleGMSurveySubmit(WorldPacket& recvPacket);

        void HandleTogglePvP(WorldPacket& recvPacket);

        void HandleZoneUpdateOpcode(WorldPacket& recvPacket);
        void HandleSetTargetOpcode(WorldPacket& recvPacket);
        void HandleSetSelectionOpcode(WorldPacket& recvPacket);
        void HandleStandStateChangeOpcode(WorldPacket& recvPacket);
        void HandleEmoteOpcode(WorldPacket& recvPacket);
        void HandleFriendListOpcode(WorldPacket& recvPacket);
        void HandleAddFriendOpcode(WorldPacket& recvPacket);
        static void HandleAddFriendOpcodeCallBack(QueryResult_AutoPtr result, uint32 accountId, std::string friendNote);
        void HandleDelFriendOpcode(WorldPacket& recvPacket);
        void HandleAddIgnoreOpcode(WorldPacket& recvPacket);
        static void HandleAddIgnoreOpcodeCallBack(QueryResult_AutoPtr result, uint32 accountId);
        void HandleDelIgnoreOpcode(WorldPacket& recvPacket);
        void HandleSetFriendNoteOpcode(WorldPacket& recvPacket);
        void HandleBugOpcode(WorldPacket& recvPacket);
        void HandleSetAmmoOpcode(WorldPacket& recvPacket);
        void HandleItemNameQueryOpcode(WorldPacket& recvPacket);

        void HandleAreaTriggerOpcode(WorldPacket& recvPacket);

        void HandleSetFactionAtWar(WorldPacket& recv_data);
        void HandleSetFactionCheat(WorldPacket& recv_data);
        void HandleSetWatchedFactionIndexOpcode(WorldPacket& recv_data);
        void HandleSetWatchedFactionInactiveOpcode(WorldPacket& recv_data);

        void HandleUpdateAccountData(WorldPacket& recvPacket);
        void HandleRequestAccountData(WorldPacket& recvPacket);
        void HandleSetActionButtonOpcode(WorldPacket& recvPacket);

        void HandleGameObjectUseOpcode(WorldPacket& recPacket);
        void HandleMeetingStoneInfo(WorldPacket& recPacket);

        void HandleNameQueryOpcode(WorldPacket& recvPacket);

        void HandleQueryTimeOpcode(WorldPacket& recvPacket);

        void HandleCreatureQueryOpcode(WorldPacket& recvPacket);

        void HandleGameObjectQueryOpcode(WorldPacket& recvPacket);

        void HandleMoveWorldportAckOpcode(WorldPacket& recvPacket);
        void HandleMoveWorldportAckOpcode();                // for server-side calls

        void HandleMovementOpcodes(WorldPacket& recvPacket);
        void HandleSetActiveMoverOpcode(WorldPacket& recv_data);
        void HandleMoveNotActiveMoverOpcode(WorldPacket& recv_data);
        void HandleMoveTimeSkippedOpcode(WorldPacket& recv_data);

        void HandleRequestRaidInfoOpcode(WorldPacket& recv_data);

        void HandleBattlefieldStatusOpcode(WorldPacket& recv_data);
        void HandleBattleMasterHelloOpcode(WorldPacket& recv_data);

        void HandleGroupInviteOpcode(WorldPacket& recvPacket);
        //void HandleGroupCancelOpcode(WorldPacket& recvPacket);
        void HandleGroupAcceptOpcode(WorldPacket& recvPacket);
        void HandleGroupDeclineOpcode(WorldPacket& recvPacket);
        void HandleGroupUninviteNameOpcode(WorldPacket& recvPacket);
        void HandleGroupUninviteGuidOpcode(WorldPacket& recvPacket);
        void HandleGroupSetLeaderOpcode(WorldPacket& recvPacket);
        void HandleGroupLeaveOpcode(WorldPacket& recvPacket);
        void HandleGroupPassOnLootOpcode(WorldPacket& recv_data);
        void HandleLootMethodOpcode(WorldPacket& recvPacket);
        void HandleLootRoll(WorldPacket& recv_data);
        void HandleRequestPartyMemberStatsOpcode(WorldPacket& recv_data);
        void HandleRaidIconTargetOpcode(WorldPacket& recv_data);
        void HandleRaidReadyCheckOpcode(WorldPacket& recv_data);
        void HandleRaidReadyCheckFinishOpcode(WorldPacket& recv_data);
        void HandleRaidConvertOpcode(WorldPacket& recv_data);
        void HandleGroupChangeSubGroupOpcode(WorldPacket& recv_data);
        void HandleGroupAssistantOpcode(WorldPacket& recv_data);
        void HandlePartyAssignmentOpcode(WorldPacket& recv_data);

        void HandlePetitionBuyOpcode(WorldPacket& recv_data);
        void HandlePetitionShowSignOpcode(WorldPacket& recv_data);
        void HandlePetitionQueryOpcode(WorldPacket& recv_data);
        void HandlePetitionRenameOpcode(WorldPacket& recv_data);
        void HandlePetitionSignOpcode(WorldPacket& recv_data);
        void HandlePetitionDeclineOpcode(WorldPacket& recv_data);
        void HandleOfferPetitionOpcode(WorldPacket& recv_data);
        void HandleTurnInPetitionOpcode(WorldPacket& recv_data);

        void HandleGuildQueryOpcode(WorldPacket& recvPacket);
        void HandleGuildCreateOpcode(WorldPacket& recvPacket);
        void HandleGuildInviteOpcode(WorldPacket& recvPacket);
        void HandleGuildRemoveOpcode(WorldPacket& recvPacket);
        void HandleGuildAcceptOpcode(WorldPacket& recvPacket);
        void HandleGuildDeclineOpcode(WorldPacket& recvPacket);
        void HandleGuildInfoOpcode(WorldPacket& recvPacket);
        void HandleGuildEventLogOpcode(WorldPacket& recvPacket);
        void HandleGuildRosterOpcode(WorldPacket& recvPacket);
        void HandleGuildPromoteOpcode(WorldPacket& recvPacket);
        void HandleGuildDemoteOpcode(WorldPacket& recvPacket);
        void HandleGuildLeaveOpcode(WorldPacket& recvPacket);
        void HandleGuildDisbandOpcode(WorldPacket& recvPacket);
        void HandleGuildLeaderOpcode(WorldPacket& recvPacket);
        void HandleGuildMOTDOpcode(WorldPacket& recvPacket);
        void HandleGuildSetPublicNoteOpcode(WorldPacket& recvPacket);
        void HandleGuildSetOfficerNoteOpcode(WorldPacket& recvPacket);
        void HandleGuildRankOpcode(WorldPacket& recvPacket);
        void HandleGuildAddRankOpcode(WorldPacket& recvPacket);
        void HandleGuildDelRankOpcode(WorldPacket& recvPacket);
        void HandleGuildChangeInfoOpcode(WorldPacket& recvPacket);
        void HandleGuildSaveEmblemOpcode(WorldPacket& recvPacket);

        void HandleTaxiNodeStatusQueryOpcode(WorldPacket& recvPacket);
        void HandleTaxiQueryAvailableNodesOpcode(WorldPacket& recvPacket);
        void HandleActivateTaxiOpcode(WorldPacket& recvPacket);
        void HandleActivateTaxiFarOpcode(WorldPacket& recvPacket);
        void HandleTaxiNextDestinationOpcode(WorldPacket& recvPacket);

        void HandleTabardVendorActivateOpcode(WorldPacket& recvPacket);
        void HandleBankerActivateOpcode(WorldPacket& recvPacket);
        void HandleBuyBankSlotOpcode(WorldPacket& recvPacket);
        void HandleTrainerListOpcode(WorldPacket& recvPacket);
        void HandleTrainerBuySpellOpcode(WorldPacket& recvPacket);

        void HandlePetitionShowListOpcode(WorldPacket& recvPacket);
        void HandleGossipHelloOpcode(WorldPacket& recvPacket);
        void HandleGossipSelectOptionOpcode(WorldPacket& recvPacket);
        void HandleSpiritHealerActivateOpcode(WorldPacket& recvPacket);
        void HandleNpcTextQueryOpcode(WorldPacket& recvPacket);
        void HandleBinderActivateOpcode(WorldPacket& recvPacket);
        void HandleListStabledPetsOpcode(WorldPacket& recvPacket);
        void HandleStablePet(WorldPacket& recvPacket);
        void HandleUnstablePet(WorldPacket& recvPacket);
        void HandleBuyStableSlot(WorldPacket& recvPacket);
        void HandleStableRevivePet(WorldPacket& recvPacket);
        void HandleStableSwapPet(WorldPacket& recvPacket);

        void HandleDuelAcceptedOpcode(WorldPacket& recvPacket);
        void HandleDuelCancelledOpcode(WorldPacket& recvPacket);

        void HandleAcceptTradeOpcode(WorldPacket& recvPacket);
        void HandleBeginTradeOpcode(WorldPacket& recvPacket);
        void HandleBusyTradeOpcode(WorldPacket& recvPacket);
        void HandleCancelTradeOpcode(WorldPacket& recvPacket);
        void HandleClearTradeItemOpcode(WorldPacket& recvPacket);
        void HandleIgnoreTradeOpcode(WorldPacket& recvPacket);
        void HandleInitiateTradeOpcode(WorldPacket& recvPacket);
        void HandleSetTradeGoldOpcode(WorldPacket& recvPacket);
        void HandleSetTradeItemOpcode(WorldPacket& recvPacket);
        void HandleUnacceptTradeOpcode(WorldPacket& recvPacket);

        void HandleAuctionHelloOpcode(WorldPacket& recvPacket);
        void HandleAuctionListItems(WorldPacket& recv_data);
        void HandleAuctionListBidderItems(WorldPacket& recv_data);
        void HandleAuctionSellItem(WorldPacket& recv_data);
        void HandleAuctionRemoveItem(WorldPacket& recv_data);
        void HandleAuctionListOwnerItems(WorldPacket& recv_data);
        void HandleAuctionPlaceBid(WorldPacket& recv_data);

        void HandleGetMail(WorldPacket& recv_data);
        void HandleSendMail(WorldPacket& recv_data);
        void HandleTakeMoney(WorldPacket& recv_data);
        void HandleTakeItem(WorldPacket& recv_data);
        void HandleMarkAsRead(WorldPacket& recv_data);
        void HandleReturnToSender(WorldPacket& recv_data);
        void HandleMailDelete(WorldPacket& recv_data);
        void HandleItemTextQuery(WorldPacket& recv_data);
        void HandleMailCreateTextItem(WorldPacket& recv_data);
        void HandleMsgQueryNextMailtime(WorldPacket& recv_data);
        void HandleCancelChanneling(WorldPacket& recv_data);

        void HandleSplitItemOpcode(WorldPacket& recvPacket);
        void HandleSwapInvItemOpcode(WorldPacket& recvPacket);
        void HandleDestroyItemOpcode(WorldPacket& recvPacket);
        void HandleAutoEquipItemOpcode(WorldPacket& recvPacket);
        void HandleItemQuerySingleOpcode(WorldPacket& recvPacket);
        void HandleSellItemOpcode(WorldPacket& recvPacket);
        void HandleBuyItemInSlotOpcode(WorldPacket& recvPacket);
        void HandleBuyItemOpcode(WorldPacket& recvPacket);
        void HandleListInventoryOpcode(WorldPacket& recvPacket);
        void HandleAutoStoreBagItemOpcode(WorldPacket& recvPacket);
        void HandleReadItemOpcode(WorldPacket& recvPacket);
        void HandleAutoEquipItemSlotOpcode(WorldPacket & recvPacket);
        void HandleSwapItemOpcode(WorldPacket & recvPacket);
        void HandleBuybackItem(WorldPacket & recvPacket);
        void HandleAutoBankItemOpcode(WorldPacket& recvPacket);
        void HandleAutoStoreBankItemOpcode(WorldPacket& recvPacket);
        void HandleWrapItemOpcode(WorldPacket& recvPacket);

        void HandleAttackSwingOpcode(WorldPacket& recvPacket);
        void HandleAttackStopOpcode(WorldPacket& recvPacket);
        void HandleSetSheathedOpcode(WorldPacket& recvPacket);

        void HandleUseItemOpcode(WorldPacket& recvPacket);
        void HandleOpenItemOpcode(WorldPacket& recvPacket);
        void HandleCastSpellOpcode(WorldPacket& recvPacket);
        void HandleCancelCastOpcode(WorldPacket& recvPacket);
        void HandleCancelAuraOpcode(WorldPacket& recvPacket);
        void HandleCancelGrowthAuraOpcode(WorldPacket& recvPacket);
        void HandleCancelAutoRepeatSpellOpcode(WorldPacket& recvPacket);

        void HandleLearnTalentOpcode(WorldPacket& recvPacket);
        void HandleTalentWipeOpcode(WorldPacket& recvPacket);
        void HandleUnlearnSkillOpcode(WorldPacket& recvPacket);

        void HandleQuestgiverStatusQueryOpcode(WorldPacket& recvPacket);
        void HandleQuestgiverStatusQueryMultipleOpcode(WorldPacket& recvPacket);
        void HandleQuestgiverHelloOpcode(WorldPacket& recvPacket);
        void HandleQuestgiverAcceptQuestOpcode(WorldPacket& recvPacket);
        void HandleQuestgiverQuestQueryOpcode(WorldPacket& recvPacket);
        void HandleQuestgiverChooseRewardOpcode(WorldPacket& recvPacket);
        void HandleQuestgiverRequestRewardOpcode(WorldPacket& recvPacket);
        void HandleQuestQueryOpcode(WorldPacket& recvPacket);
        void HandleQuestgiverCancel(WorldPacket& recv_data);
        void HandleQuestLogSwapQuest(WorldPacket& recv_data);
        void HandleQuestLogRemoveQuest(WorldPacket& recv_data);
        void HandleQuestConfirmAccept(WorldPacket& recv_data);
        void HandleQuestgiverCompleteQuest(WorldPacket& recv_data);
        void HandleQuestAutoLaunch(WorldPacket& recvPacket);
        void HandleQuestPushToParty(WorldPacket& recvPacket);
        void HandleQuestPushResult(WorldPacket& recvPacket);

        bool processChatmessageFurtherAfterSecurityChecks(std::string&, uint32);
        void HandleMessagechatOpcode(WorldPacket& recvPacket);
        void SendPlayerNotFoundNotice(std::string name);
        void SendWrongFactionNotice();
        void HandleTextEmoteOpcode(WorldPacket& recvPacket);
        void HandleChatIgnoredOpcode(WorldPacket& recvPacket);

        void HandleCorpseReclaimOpcode(WorldPacket& recvPacket);
        void HandleCorpseQueryOpcode(WorldPacket& recvPacket);
        void HandleResurrectResponseOpcode(WorldPacket& recvPacket);
        void HandleSummonResponseOpcode(WorldPacket& recv_data);

        void HandleChannelJoin(WorldPacket& recvPacket);
        void HandleChannelLeave(WorldPacket& recvPacket);
        void HandleChannelList(WorldPacket& recvPacket);
        void HandleChannelPassword(WorldPacket& recvPacket);
        void HandleChannelSetOwner(WorldPacket& recvPacket);
        void HandleChannelOwner(WorldPacket& recvPacket);
        void HandleChannelModerator(WorldPacket& recvPacket);
        void HandleChannelUnmoderator(WorldPacket& recvPacket);
        void HandleChannelMute(WorldPacket& recvPacket);
        void HandleChannelUnmute(WorldPacket& recvPacket);
        void HandleChannelInvite(WorldPacket& recvPacket);
        void HandleChannelKick(WorldPacket& recvPacket);
        void HandleChannelBan(WorldPacket& recvPacket);
        void HandleChannelUnban(WorldPacket& recvPacket);
        void HandleChannelAnnounce(WorldPacket& recvPacket);
        void HandleChannelModerate(WorldPacket& recvPacket);
        void HandleChannelRosterQuery(WorldPacket& recvPacket);
        void HandleChannelInfoQuery(WorldPacket& recvPacket);
        void HandleChannelJoinNotify(WorldPacket& recvPacket);

        void HandleCompleteCinematic(WorldPacket& recvPacket);
        void HandleNextCinematicCamera(WorldPacket& recvPacket);

        void HandlePageQuerySkippedOpcode(WorldPacket& recvPacket);
        void HandlePageQueryOpcode(WorldPacket& recvPacket);

        void HandleTutorialFlag (WorldPacket& recv_data);
        void HandleTutorialClear(WorldPacket& recv_data);
        void HandleTutorialReset(WorldPacket& recv_data);

        //Pet
        void HandlePetAction(WorldPacket& recv_data);
        void HandlePetActionHelper(Unit* pet, uint64 guid1, uint16 spellid, uint16 flag, uint64 guid2);
        void HandlePetNameQuery(WorldPacket& recv_data);
        void HandlePetSetAction(WorldPacket& recv_data);
        void HandlePetAbandon(WorldPacket& recv_data);
        void HandlePetRename(WorldPacket& recv_data);
        void HandlePetCancelAuraOpcode(WorldPacket& recvPacket);
        void HandlePetUnlearnOpcode(WorldPacket& recvPacket);
        void HandlePetSpellAutocastOpcode(WorldPacket& recvPacket);
        void HandlePetCastSpellOpcode(WorldPacket& recvPacket);

        void HandleSetActionBar(WorldPacket& recv_data);

        void HandleChangePlayerNameOpcode(WorldPacket& recv_data);
        static void HandleChangePlayerNameOpcodeCallBack(QueryResult_AutoPtr result, uint32 accountId, std::string newname);
        void HandleSetPlayerDeclinedNamesOpcode(WorldPacket& recv_data);

        void HandleTotemDestroyed(WorldPacket& recv_data);

        //BattleGround
        void HandleBattleGroundHelloOpcode(WorldPacket& recv_data);
        void HandleBattleGroundJoinOpcode(WorldPacket& recv_data);
        void HandleBattleGroundPlayerPositionsOpcode(WorldPacket& recv_data);
        void HandleBattleGroundPVPlogdataOpcode(WorldPacket& recv_data);
        void HandleBattleGroundPlayerPortOpcode(WorldPacket& recv_data);
        void HandleBattleGroundListOpcode(WorldPacket& recv_data);
        void HandleBattleGroundLeaveOpcode(WorldPacket& recv_data);
        void HandleBattleGroundArenaJoin(WorldPacket& recv_data);
        void HandleBattleGroundReportAFK(WorldPacket& recv_data);

        void HandleWardenDataOpcode(WorldPacket& recv_data);
        void HandleWorldTeleportOpcode(WorldPacket& recv_data);
        void HandleMinimapPingOpcode(WorldPacket& recv_data);
        void HandleRandomRollOpcode(WorldPacket& recv_data);
        void HandleFarSightOpcode(WorldPacket& recv_data);
        void HandleSetLfgOpcode(WorldPacket& recv_data);
        void HandleDungeonDifficultyOpcode(WorldPacket& recv_data);
        void HandleMoveSetCanFlyAckOpcode(WorldPacket& recv_data);
        void HandleLfgAutoJoinOpcode(WorldPacket& recv_data);
        void HandleLfgCancelAutoJoinOpcode(WorldPacket& recv_data);
        void HandleLfmAutoAddMembersOpcode(WorldPacket& recv_data);
        void HandleLfmCancelAutoAddmembersOpcode(WorldPacket& recv_data);
        void HandleLfgClearOpcode(WorldPacket& recv_data);
        void HandleLfmSetNoneOpcode(WorldPacket& recv_data);
        void HandleLfmSetOpcode(WorldPacket& recv_data);
        void HandleLfgSetCommentOpcode(WorldPacket& recv_data);
        void HandleChooseTitleOpcode(WorldPacket& recv_data);
        void HandleRealmStateRequestOpcode(WorldPacket& recv_data);
        void HandleTimeSyncResp(WorldPacket& recv_data);
        void HandleWhoisOpcode(WorldPacket& recv_data);
        void HandleResetInstancesOpcode(WorldPacket& recv_data);

        // Arena Team
        void HandleInspectArenaStatsOpcode(WorldPacket& recv_data);
        void HandleArenaTeamQueryOpcode(WorldPacket& recv_data);
        void HandleArenaTeamRosterOpcode(WorldPacket& recv_data);
        void HandleArenaTeamAddMemberOpcode(WorldPacket& recv_data);
        void HandleArenaTeamInviteAcceptOpcode(WorldPacket& recv_data);
        void HandleArenaTeamInviteDeclineOpcode(WorldPacket& recv_data);
        void HandleArenaTeamLeaveOpcode(WorldPacket& recv_data);
        void HandleArenaTeamRemoveFromTeamOpcode(WorldPacket& recv_data);
        void HandleArenaTeamDisbandOpcode(WorldPacket& recv_data);
        void HandleArenaTeamPromoteToCaptainOpcode(WorldPacket& recv_data);

        void HandleAreaSpiritHealerQueryOpcode(WorldPacket& recv_data);
        void HandleAreaSpiritHealerQueueOpcode(WorldPacket& recv_data);
        void HandleDismountOpcode(WorldPacket& recv_data);
        void HandleSelfResOpcode(WorldPacket& recv_data);
        void HandleReportSpamOpcode(WorldPacket& recv_data);
        void HandleRequestPetInfoOpcode(WorldPacket& recv_data);

        // Socket gem
        void HandleSocketOpcode(WorldPacket& recv_data);

        void HandleCancelTempItemEnchantmentOpcode(WorldPacket& recv_data);

        void HandleChannelEnableVoiceOpcode(WorldPacket& recv_data);
        void HandleVoiceSettingsOpcode(WorldPacket& recv_data);
        void HandleChannelVoiceChatQuery(WorldPacket& recv_data);
        void HandleSetTaxiBenchmarkOpcode(WorldPacket& recv_data);

        // Guild Bank
        void HandleGuildBankGetRights(WorldPacket& recv_data);
        void HandleGuildBankGetMoneyAmount(WorldPacket& recv_data);
        void HandleGuildBankQuery(WorldPacket& recv_data);
        void HandleGuildBankTabColon(WorldPacket& recv_data);
        void HandleGuildBankLog(WorldPacket& recv_data);
        void HandleGuildBankDeposit(WorldPacket& recv_data);
        void HandleGuildBankWithdraw(WorldPacket& recv_data);
        void HandleGuildBankDepositItem(WorldPacket& recv_data);
        void HandleGuildBankModifyTab(WorldPacket& recv_data);
        void HandleGuildBankBuyTab(WorldPacket& recv_data);
        void HandleGuildBankTabText(WorldPacket& recv_data);
        void HandleGuildBankSetTabText(WorldPacket& recv_data);
    private:
        // private trade methods
        void moveItems(Item* myItems[], Item* hisItems[]);

        void ExecuteOpcode(OpcodeHandler const& opHandle, WorldPacket* packet);

        // logging helper
        void LogUnexpectedOpcode(WorldPacket* packet, const char * reason);
        void LogUnprocessedTail(WorldPacket* packet);

        Player* _player;
        WorldSocket *m_Socket;
        std::string m_Address;

        uint32 _security;
        uint32 _accountId;
        uint8 m_expansion;
        bool _ispremium;

        time_t _logoutTime;
        bool m_inQueue;                                     // session wait in auth.queue
        bool m_playerLoading;                               // code processed in LoginPlayer
        bool m_playerLogout;                                // code processed in LogoutPlayer
        bool m_playerRecentlyLogout;
        bool m_playerSave;
        LocaleConstant m_sessionDbcLocale;
        int m_sessionDbLocaleIndex;
        uint32 m_latency;

        ACE_Based::LockedQueue<WorldPacket*,ACE_Thread_Mutex> _recvQueue;
};
#endif

