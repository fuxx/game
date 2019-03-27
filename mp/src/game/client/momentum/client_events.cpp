#include "cbase.h"

#include "client_events.h"

#include "filesystem.h"
#include "momentum/ui/IMessageboxPanel.h"
#include "fmtstr.h"
#include "steam/steam_api.h"

#include "tier0/memdbgon.h"

extern IFileSystem *filesystem;

bool CMOMClientEvents::Init()
{
    // Mount CSS content even if it's on a different drive than this game
    if (SteamApps())
    {
        char installPath[MAX_PATH];
        uint32 folderLen = SteamApps()->GetAppInstallDir(240, installPath, MAX_PATH);
        if (folderLen)
        {
            filesystem->AddSearchPath(CFmtStr("%s/cstrike", installPath), "GAME");
            filesystem->AddSearchPath(CFmtStr("%s/cstrike/cstrike_pak.vpk", installPath), "GAME");
            filesystem->AddSearchPath(CFmtStr("%s/cstrike/download", installPath), "GAME");
            filesystem->AddSearchPath(CFmtStr("%s/cstrike/download", installPath), "download");

            if (developer.GetInt())
                filesystem->PrintSearchPaths();
        }
    }

    return true;
}

void CMOMClientEvents::PostInit()
{
    // enable console by default
    ConVarRef con_enable("con_enable");
    con_enable.SetValue(true);

    // Version warning
    // MOM_TODO: Change this once we hit Beta
    // MOM_CURRENT_VERSION
    messageboxpanel->CreateMessageboxVarRef("#MOM_StartupMsg_Alpha_Title", "#MOM_StartupMsg_Alpha", "mom_toggle_versionwarn", "#MOM_IUnderstand");
    
    if (!SteamHTTP() || !SteamUtils())
    {
        messageboxpanel->CreateMessagebox("#MOM_StartupMsg_NoSteamApiContext_Title", "#MOM_StartupMsg_NoSteamApiContext", "#MOM_IUnderstand");
    }
}

void CMOMClientEvents::LevelInitPreEntity()
{
    //Precache();
}

void CMOMClientEvents::Precache()
{
    // MOM_TODO: Precache anything here
}

CMOMClientEvents g_MOMClientEvents("CMOMClientEvents");
