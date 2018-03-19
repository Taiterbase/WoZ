/*
 * This file is part of the BlizzLikeCore Project.
 * See CREDITS and LICENSE files for Copyright information.
 */

/* ScriptData
Name: Boss_Ras_Frostwhisper
Complete(%): 100
Comment:
Category: Scholomance
EndScriptData */

#include "ScriptPCH.h"

#define SPELL_FROSTBOLT         21369
#define SPELL_ICEARMOR          18100                       //This is actually a buff he gives himself
#define SPELL_FREEZE            18763
#define SPELL_FEAR              26070
#define SPELL_CHILLNOVA         18099
#define SPELL_FROSTVOLLEY       8398

struct boss_rasfrostAI : public ScriptedAI
{
    boss_rasfrostAI(Creature* c) : ScriptedAI(c) {}

    uint32 IceArmor_Timer;
    uint32 Frostbolt_Timer;
    uint32 Freeze_Timer;
    uint32 Fear_Timer;
    uint32 ChillNova_Timer;
    uint32 FrostVolley_Timer;

    void Reset()
    {
        IceArmor_Timer = 2000;
        Frostbolt_Timer = 8000;
        ChillNova_Timer = 12000;
        Freeze_Timer = 18000;
        FrostVolley_Timer = 24000;
        Fear_Timer = 45000;

        DoCast(me, SPELL_ICEARMOR, true);
    }

    void EnterCombat(Unit* /*who*/){}

    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictim())
            return;

        //IceArmor_Timer
        if (IceArmor_Timer <= diff)
        {
            DoCast(me, SPELL_ICEARMOR);
            IceArmor_Timer = 180000;
        } else IceArmor_Timer -= diff;

        //Frostbolt_Timer
        if (Frostbolt_Timer <= diff)
        {
            if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                DoCast(pTarget, SPELL_FROSTBOLT);

            Frostbolt_Timer = 8000;
        } else Frostbolt_Timer -= diff;

        //Freeze_Timer
        if (Freeze_Timer <= diff)
        {
            DoCast(me->getVictim(), SPELL_FREEZE);
            Freeze_Timer = 24000;
        } else Freeze_Timer -= diff;

        //Fear_Timer
        if (Fear_Timer <= diff)
        {
            DoCast(me->getVictim(), SPELL_FEAR);
            Fear_Timer = 30000;
        } else Fear_Timer -= diff;

        //ChillNova_Timer
        if (ChillNova_Timer <= diff)
        {
            DoCast(me->getVictim(), SPELL_CHILLNOVA);
            ChillNova_Timer = 14000;
        } else ChillNova_Timer -= diff;

        //FrostVolley_Timer
        if (FrostVolley_Timer <= diff)
        {
            DoCast(me->getVictim(), SPELL_FROSTVOLLEY);
            FrostVolley_Timer = 15000;
        } else FrostVolley_Timer -= diff;

        DoMeleeAttackIfReady();
    }
};
CreatureAI* GetAI_boss_rasfrost(Creature* pCreature)
{
    return new boss_rasfrostAI (pCreature);
}

void AddSC_boss_rasfrost()
{
    Script* newscript;
    newscript = new Script;
    newscript->Name = "boss_boss_ras_frostwhisper";
    newscript->GetAI = &GetAI_boss_rasfrost;
    newscript->RegisterSelf();
}

