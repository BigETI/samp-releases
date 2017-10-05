/*
	Anti C-Bug System gemacht von BigETI©
	Alle rechte gehören mir!
*/

//Includes
#include <a_samp>

//Defines
#define DRED								0x991111FF
#define PRESSED(%0)							(newkeys&(%0))&&!(oldkeys&(%0))
#define RELEASED(%0)						(oldkeys&(%0))&&!(newkeys&(%0))
#define CreateVarTimerEx(%0,%1)				%0 = SetTimerEx(%1)
#define SafeKillTimer(%0);					if(%0 != 0)\
	{\
	KillTimer(%0);\
	%0 = 0;\
	}
#define Create1VarTimerEx(%0,%1)			if(%0 == 0) %0 = SetTimerEx(%1)
#define ResetVar(%0)						%0 = 0
#define INVALID_WEAPON_SLOT_ID      		-1
#define UseBrackets							if(negative != positive)
#define SendClientMessageToAllF(%0,%1,%2);	UseBrackets\
	{\
	new formatstring[512];\
	format(formatstring,sizeof(formatstring),%1,%2);\
	SendClientMessageToAll(%0,formatstring);\
	}
	
//News
new kicktimer[MAX_PLAYERS], cbugtimer[MAX_PLAYERS], cbugcooldowntimer[MAX_PLAYERS], bool:negative = false, bool:positive = true;

//Forwards
forward KickPlayer(playerid);
forward CBugCoolDown(playerid);
forward UnCheckPlayerCBug(playerid);

//Stocks
stock ReturnPlayerName(playerid)
{
	new pname[MAX_PLAYER_NAME];
	GetPlayerName(playerid, pname, sizeof(pname));
	return pname;
}

stock ResetPlayerTimers(playerid)
{
    SafeKillTimer(kicktimer[playerid]);
	SafeKillTimer(cbugtimer[playerid]);
	SafeKillTimer(cbugcooldowntimer[playerid]);
}

stock GetPlayerWeaponSlot(playerid)
{
	new slot;
	switch(GetPlayerWeapon(playerid))
	{
		case 0,1: slot = 0;
		case 2..9: slot = 1;
		case 22..24: slot = 2;
		case 25..27: slot = 3;
		case 28,29,32: slot = 4;
		case 30,31: slot = 5;
		case 33,34: slot = 6;
		case 35..38: slot = 7;
		case 16..18,39: slot = 8;
		case 41..43: slot = 9;
		case 10..15: slot = 10;
		case 44..46: slot = 11;
		case 40: slot = 12;
		default: slot = INVALID_WEAPON_SLOT_ID;
	}
	return slot;
}

stock GivePVarInt(playerid, varname[], int_value) SetPVarInt(playerid, varname, GetPVarInt(playerid, varname)+int_value);

public KickPlayer(playerid)
{
	ResetVar(kicktimer[playerid]);
	Kick(playerid);
}

public CBugCoolDown(playerid)
{
	ResetVar(cbugcooldowntimer[playerid]);
	SetPVarInt(playerid, "CBugWarnings", 0);
}

public UnCheckPlayerCBug(playerid)
{
	ResetVar(cbugtimer[playerid]);
	SetPVarInt(playerid, "CBugCheck", 0);
}

public OnFilterScriptInit()
{
	print("\n=============================");
	print(" BigETI's Anti C-Bug System ©");
	print("=============================\n");
	return 1;
}

public OnFilterScriptExit()
{
    for(new playerid = 0; playerid < MAX_PLAYERS; playerid++) if(IsPlayerConnected(playerid)) ResetPlayerTimers(playerid);
	return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
    ResetPlayerTimers(playerid);
	return 1;
}

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(PRESSED(KEY_CROUCH))
	{
		if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
		{
			if(GetPVarInt(playerid, "CBugCheck") == 1 && (GetPlayerWeaponSlot(playerid) == 2 || GetPlayerWeaponSlot(playerid) == 3 || GetPlayerWeaponSlot(playerid) == 6))
		    {
				SafeKillTimer(cbugtimer[playerid]);
				SetPVarInt(playerid, "CBugCheck", 0);
				GivePVarInt(playerid, "CBugWarnings", 1);
				if(GetPVarInt(playerid, "CBugWarnings") == 4)
				{
                    SendClientMessageToAllF(DRED, "%s(%d) wurde wegen c-bugging gekickt.", ReturnPlayerName(playerid), playerid);
                    Create1VarTimerEx(kicktimer[playerid], "KickPlayer", 500, false, "d", playerid);
				}
				else if(GetPVarInt(playerid, "CBugWarnings") < 4)
				{
				    SafeKillTimer(cbugcooldowntimer[playerid]);
				    CreateVarTimerEx(cbugcooldowntimer[playerid], "CBugCoolDown", 10000, false, "d", playerid);
					SendClientMessage(playerid, DRED, "C-bugge nicht wieder, sonst wirst du gekickt!");
					//Hier kann man noch eine Nachricht für nur Admins einfügen.
					//Beispiel: SendClientMessageToAdminsF(DRED, "%s(%d) wurde beim c-buggen erwischt.", ReturnPlayerName(playerid), playerid);
				}
			}
		}
	}
	if(PRESSED(KEY_FIRE)) //Kann ausgeführt werden, während man die Feuer Taste gedrückt hält
	{
		if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
		{
		    if(GetPlayerWeaponSlot(playerid) == 2 || GetPlayerWeaponSlot(playerid) == 3 || GetPlayerWeaponSlot(playerid) == 6)
		    {
			    SafeKillTimer(cbugtimer[playerid]);
			    SetPVarInt(playerid, "CBugCheck", 1);
			    CreateVarTimerEx(cbugtimer[playerid], "UnCheckPlayerCBug", 300, false, "d", playerid);
			}
		}
	}
	if(RELEASED(KEY_FIRE)) //Kann ausgeführt werden, während man die Feuer Taste losgelassen hat.
	{
		SetPVarInt(playerid, "IsShooting", 0);
		if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
		{
		    if(GetPlayerWeaponSlot(playerid) == 2 || GetPlayerWeaponSlot(playerid) == 3 || GetPlayerWeaponSlot(playerid) == 6)
		    {
			    SafeKillTimer(cbugtimer[playerid]);
			    SetPVarInt(playerid, "CBugCheck", 1);
			    CreateVarTimerEx(cbugtimer[playerid], "UnCheckPlayerCBug", 300, false, "d", playerid);
			}
		}
	}
	return 1;
}