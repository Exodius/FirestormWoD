////////////////////////////////////////////////////////////////////////////////
//
//  MILLENIUM-STUDIO
//  Copyright 2015 Millenium-studio SARL
//  All Rights Reserved.
//
////////////////////////////////////////////////////////////////////////////////


#include <ScriptPCH.h>
#include <ScriptMgr.h>

class WarningUpdateClient : public PlayerScript
{
    const uint32 k_WarningUpdateTimer = 300000; ///< 5 mins

    public:
        WarningUpdateClient() : PlayerScript("WarningUpdateClient") {}

        std::map<uint64/*guid*/, uint32/*WarningTimer*/> m_WarningTimers;

        void OnLogin(Player* p_Player)
        {
            if (p_Player->GetSession()->GetClientBuild() != sWorld->getIntConfig(CONFIG_LAST_CLIENT_BUILD))
            {
                //ChatHandler(p_Player).SendSysMessage(TrinityStrings::LangWarningUpdateClient);
                m_WarningTimers[p_Player->GetGUID()] = k_WarningUpdateTimer;
            }
        }

        void OnLogout(Player * p_Player)
        {
            m_WarningTimers.erase(p_Player->GetGUID());
        }

        void OnUpdate(Player * p_Player, uint32 p_Diff)
        {
            if (m_WarningTimers.find(p_Player->GetGUID()) == m_WarningTimers.end())
                return;

            if (m_WarningTimers[p_Player->GetGUID()] <= p_Diff)
            {
                //ChatHandler(p_Player).SendSysMessage(TrinityStrings::LangWarningUpdateClient);
                m_WarningTimers[p_Player->GetGUID()] = k_WarningUpdateTimer;
            }
            else
                m_WarningTimers[p_Player->GetGUID()] -= p_Diff;
        }
};

void AddSC_warning_update_client()
{
    new WarningUpdateClient();
};
