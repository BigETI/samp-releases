#if defined _CE_FIX_INCLUDED_
	#endinput
#endif
#define _CE_FIX_INCLUDED_
#include <a_samp>
static bool:ce_fix[MAX_PLAYERS] = {false, ...}, ce_on_script_found = false;
public OnGameModeInit()
{
	ce_on_script_found = true;
#if defined CE_OnGameModeInit
	return CE_OnGameModeInit();
#else
	return 1;
#endif
}
#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit CE_OnGameModeInit
#if defined CE_OnGameModeInit
forward CE_OnGameModeInit();
#endif
public OnFilterScriptInit()
{
	if(!ce_on_script_found)
	{
		ce_on_script_found = true;
		for(new i = 0; i < MAX_PLAYERS; i++) if(IsPlayerConnected(i)) ce_fix[i] = true;
	}
#if defined CE_OnFilterScriptInit
	return CE_OnFilterScriptInit();
#else
	return 1;
#endif
}
#if defined _ALS_OnFilterScriptInit
	#undef OnFilterScriptInit
#else
	#define _ALS_OnFilterScriptInit
#endif
#define OnFilterScriptInit CE_OnFilterScriptInit
#if defined CE_OnFilterScriptInit
forward CE_OnFilterScriptInit();
#endif
public OnPlayerConnect(playerid)
{
	if(ce_fix[playerid]) OnPlayerDisconnect(playerid, 3);
	else ce_fix[playerid] = true;
#if defined CE_OnPlayerConnect
	return CE_OnPlayerConnect(playerid);
#else
	return 1;
#endif
}
#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect CE_OnPlayerConnect
#if defined CE_OnPlayerConnect
forward CE_OnPlayerConnect(playerid);
#endif
public OnPlayerDisconnect(playerid, reason)
{
	ce_fix[playerid] = false;
#if defined CE_OnPlayerDisconnect
	return CE_OnPlayerDisconnect(playerid, reason);
#else
	return 1;
#endif
}
#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect CE_OnPlayerDisconnect
#if defined CE_OnPlayerDisconnect
forward CE_OnPlayerDisconnect(playerid, reason);
#endif