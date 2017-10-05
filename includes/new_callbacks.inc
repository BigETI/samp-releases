/*
////////////////////////////////////////////////////////////
//========================================================//
//== New Player Callbacks include made by BigETI © 2011 ==//
//========================================================//
//== You are not allowed to edit this include ============//
//== and/or release it without my permissions! ===========//
//========================================================//
//== File name: new_callbacks.inc ========================//
//== Autor: Ethem Kurt © =================================//
//== Release Date: 06.09.2011 ============================//
//== Version: V1.3 =======================================//
//== Lines: 448 ==========================================//
//== File size: 18,9 KB ==================================//
//========================================================//
////////////////////////////////////////////////////////////
*/

//IMPORTANT: Define FILTERSCRIPT on top of your script to verify if you are yousing a filterscript or a gamemode!

//Just comment a define if you don't need it. Otherwise uncomment.
#define USE_OPU_DELAY					//Uses a delay at OnPlayerUpdate to prevent totally overkill (Usefull for anti cheats but the callbacks may get slower!)
//#define USE_OPU_SECONDS				//Callbacks delays >1 seconds otherwise they delays for >1 milliseconds. (Uncomment USE_OPU_DELAY to make this usable!) [Optional]
#define USE_PLAYER_CALLBACKS			//Makes the use of extended player callbacks.
//#define USE_PVAR_CALLBACKS			//Makes the use of PVar callbacks (Uncomment this if you want to use PVar Callbacks) [Optional]
#define CB_OnPlayerSkinChange			//Makes the use of OnPlayerSkinChange (Uncomment USE_PLAYER_CALLBACKS to make this usable!)
#define CB_OnPlayerHoldWeaponChange		//Makes the use of OnPlayerHoldWeaponChange (Uncomment USE_PLAYER_CALLBACKS to make this usable!)
#define CB_OnPlayerWeaponStateChange	//Makes the use of OnPlayerWeaponStateChange (Uncomment USE_PLAYER_CALLBACKS to make this usable!)
#define USE_WEAPON_DATA_CALLBACKS		//Makes the use of weapon data callbacks
#define CB_OnPlayerWeaponDataChange		//Makes the use of OnPlayerWeaponDataChange (Uncomment USE_PLAYER_CALLBACKS and USE_WEAPON_DATA_CALLBACKS to make this usable!)
#define CB_OnPlayerAmmoDataChange		//Makes the use of OnPlayerAmmoDataChange (Uncomment USE_PLAYER_CALLBACKS and USE_WEAPON_DATA_CALLBACKS to make this usable!)
#define CB_OnPlayerHealthChange			//Makes the use of OnPlayerHealthChange (Uncomment USE_PLAYER_CALLBACKS to make this usable!)
#define CB_OnPlayerArmourChange			//Makes the use of OnPlayerArmourChange (Uncomment USE_PLAYER_CALLBACKS to make this usable!)
#define CB_OnPlayerAnimationIndexChange	//Makes the use of OnPlayerAnimationIndexChange (Uncomment USE_PLAYER_CALLBACKS to make this usable!)
#define CB_OnPlayerSpecialActionChange	//Makes the use of OnPlayerSpecialActionChange (Uncomment USE_PLAYER_CALLBACKS to make this usable!)
#define CB_OnPlayerVirtualWorldChange	//Makes the use of OnPlayerVirtualWorldChange (Uncomment USE_PLAYER_CALLBACKS to make this usable!)
#define CB_OnPVarDelete					//Makes the use of OnPVarDelete (Uncomment USE_PVAR_CALLBACKS to make this usable!)
#define CB_OnPVarCreate					//Makes the use of OnPVarCreate (Uncomment USE_PVAR_CALLBACKS to make this usable!)
#define CB_OnPVarTypeChange				//Makes the use of OnPVarTypeChange (Uncomment USE_PVAR_CALLBACKS to make this usable!)
#define CB_OnPVarIntChange				//Makes the use of OnPVarIntChange (Uncomment USE_PVAR_CALLBACKS to make this usable!)
#define CB_OnPVarStringChange			//Makes the use of OnPVarStringChange (Uncomment USE_PVAR_CALLBACKS to make this usable!)
#define CB_OnPVarFloatChange			//Makes the use of OnPVarFloatChange (Uncomment USE_PVAR_CALLBACKS to make this usable!)

//Setable defines
#define ADD_OPU_DELAY	0				//You can increase/decrease the delay of OnPlayerUpdate by setting this define (0 is standard [means >1 s or ms delay]) (If USE_OPU_SECONDS is defined, then in seconds otherwise in milliseconds)


//Do not edit those things below!
#include <a_samp>
#if defined _BIGETI_NEW_PLAYER_CALLBACKS
	#endinput
#endif
#define	_BIGETI_NEW_PLAYER_CALLBACKS
#pragma library					new_callbacks
#define MAX_WEAPON_SLOTS		13
#define INVALID_WEAPON_SLOT_ID	-1
#if defined USE_PLAYER_CALLBACKS
	#if defined CB_OnPlayerSkinChange
forward OnPlayerSkinChange(playerid, oldskin, newskin);
	#endif
	#if defined CB_OnPlayerHoldWeaponChange
forward OnPlayerHoldWeaponChange(playerid, oldslot, oldweapon, newslot, newweapon);
	#endif
	#if defined CB_OnPlayerWeaponStateChange
forward OnPlayerWeaponStateChange(playerid, oldstate, newstate);
	#endif
	#if defined USE_WEAPON_DATA_CALLBACKS
		#if defined CB_OnPlayerWeaponDataChange
forward OnPlayerWeaponDataChange(playerid, slot, oldweapon, newweapon);
		#endif
		#if defined CB_OnPlayerAmmoDataChange
forward OnPlayerAmmoDataChange(playerid, slot, oldammo, newammo);
		#endif
	#endif
	#if defined CB_OnPlayerHealthChange
forward OnPlayerHealthChange(playerid, Float:oldhealth, Float:newhealth);
	#endif
	#if defined CB_OnPlayerArmourChange
forward OnPlayerArmourChange(playerid, Float:oldarmour, Float:newarmour);
	#endif
	#if defined CB_OnPlayerAnimationIndexChange
forward OnPlayerAnimationIndexChange(playerid, oldindex, newindex);
	#endif
	#if defined CB_OnPlayerSpecialActionChange
forward OnPlayerSpecialActionChange(playerid, oldsaction, newsaction);
	#endif
	#if defined CB_OnPlayerVirtualWorldChange
forward OnPlayerVirtualWorldChange(playerid, oldworld, newworld);
	#endif
enum CallBack_Infos
{
	nCallBack_Skin,
	nCallBack_HoldWeapon,
	nCallBack_WeaponState,
	nCallBack_Weapon[MAX_WEAPON_SLOTS],
	nCallBack_Ammo[MAX_WEAPON_SLOTS],
	Float:nCallBack_Health,
	Float:nCallBack_Armour,
	nCallBack_Animation,
	nCallBack_SpecialAction,
	bool:nCallBack_KickedBanned,
	nCallBack_OPUTime,
};
new pCallBack_Info[MAX_PLAYERS][CallBack_Infos], OPC_CallBack, OPDC_CallBack, OPU_CallBack;
	#define ETI_ReturnOPC(%0) ((OPC_CallBack != -1) ? CallLocalFunction("ETI_OnPlayerConnect", %0) : 1)
	#define ETI_ReturnOPDC(%0) ((OPDC_CallBack != -1) ? CallLocalFunction("ETI_OnPlayerDisconnect", %0) : 1)
	#define ETI_ReturnOPU(%0) ((OPU_CallBack != -1) ? CallLocalFunction("ETI_OnPlayerUpdate", %0) : 1)
stock GetWeaponSlot_ETI(weaponid)
{
    new slot;
	switch(weaponid)
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
	#if defined FILTERSCRIPT
public OnFilterScriptInit()
{
	OPC_CallBack = funcidx("OnPlayerConnect");
	OPDC_CallBack = funcidx("OnPlayerDisconnect");
	OPU_CallBack = funcidx("OnPlayerUpdate");
	return (funcidx("ETI_OnFilterScriptInit") != -1) ? CallLocalFunction("ETI_OnFilterScriptInit","") : 1;
}
		#if defined _ALS_OnFilterScriptInit
			#undef OnFilterScriptInit
		#else
			#define _ALS_OnFilterScriptInit
		#endif
		#define OnFilterScriptInit ETI_OnFilterScriptInit
forward ETI_OnFilterScriptInit();
	#else
public OnGameModeInit()
{
	OPC_CallBack = funcidx("OnPlayerConnect");
	OPDC_CallBack = funcidx("OnPlayerDisconnect");
	OPU_CallBack = funcidx("OnPlayerUpdate");
	return (funcidx("ETI_OnGameModeInit") != -1) ? CallLocalFunction("ETI_OnGameModeInit","") : 1;
}
		#if defined _ALS_OnGameModeInit
			#undef OnGameModeInit
		#else
			#define _ALS_OnGameModeInit
		#endif
		#define OnGameModeInit ETI_OnGameModeInit
forward ETI_OnGameModeInit();
	#endif
public OnPlayerConnect(playerid)
{
	pCallBack_Info[playerid][nCallBack_Health] = 100.0;
	pCallBack_Info[playerid][nCallBack_KickedBanned] = false;
	return ETI_ReturnOPC("d", playerid);
}
	#if defined _ALS_OnPlayerConnect
		#undef OnPlayerConnect
	#else
		#define _ALS_OnPlayerConnect
	#endif
	#define OnPlayerConnect ETI_OnPlayerConnect
forward ETI_OnPlayerConnect(playerid);
public OnPlayerDisconnect(playerid, reason)
{
	#if defined CB_OnPlayerSkinChange
	pCallBack_Info[playerid][nCallBack_Skin] = 0;
	#endif
	#if defined CB_OnPlayerWeaponChange
	pCallBack_Info[playerid][nCallBack_HoldWeapon] = 0;
	#endif
	#if defined CB_OnPlayerWeaponStateChange
	pCallBack_Info[playerid][nCallBack_WeaponState] = 0;
	#endif
	#if defined USE_WEAPON_DATA_CALLBACKS
	for(new i = 0; i < MAX_WEAPON_SLOTS; i++)
	{
		#if defined CB_OnPlayerWeaponDataChange
		pCallBack_Info[playerid][nCallBack_Weapon][i] = 0;
		#endif
		#if defined CB_OnPlayerAmmoDataChange
		pCallBack_Info[playerid][nCallBack_Ammo][i] = 0;
		#endif
	}
	#endif
	#if defined CB_OnPlayerHealthChange
	pCallBack_Info[playerid][nCallBack_Health] = 0.0;
	#endif
	#if defined CB_OnPlayerArmourChange
	pCallBack_Info[playerid][nCallBack_Armour] = 0.0;
	#endif
	#if defined CB_OnPlayerAnimationIndexChange
	pCallBack_Info[playerid][nCallBack_Animation] = 0;
	#endif
	#if defined CB_OnPlayerSpecialActionChange
	pCallBack_Info[playerid][nCallBack_SpecialAction] = 0;
	#endif
	return ETI_ReturnOPDC("dd", playerid, reason);
}
	#if defined _ALS_OnPlayerDisconnect
		#undef OnPlayerDisconnect
	#else
		#define _ALS_OnPlayerDisconnect
	#endif
	#define OnPlayerDisconnect ETI_OnPlayerDisconnect
forward ETI_OnPlayerDisconnect(playerid, reason);
public OnPlayerUpdate(playerid)
{
	if(pCallBack_Info[playerid][nCallBack_KickedBanned]) return ETI_ReturnOPU("d", playerid);
	new update_Variable[CallBack_Infos];
	#if defined USE_OPU_DELAY
		#if defined USE_OPU_SECONDS
	update_Variable[nCallBack_OPUTime] = gettime();
		#else
	update_Variable[nCallBack_OPUTime] = GetTickCount();
		#endif
	if(pCallBack_Info[playerid][nCallBack_OPUTime]+ADD_OPU_DELAY >= update_Variable[nCallBack_OPUTime]) return ETI_ReturnOPU("d", playerid);
	pCallBack_Info[playerid][nCallBack_OPUTime] = update_Variable[nCallBack_OPUTime];
	#endif
	#if defined CB_OnPlayerSkinChange
	update_Variable[nCallBack_Skin] = GetPlayerSkin(playerid);
	if(pCallBack_Info[playerid][nCallBack_Skin] != update_Variable[nCallBack_Skin])
	{
		CallLocalFunction("OnPlayerSkinChange", "ddd", playerid, pCallBack_Info[playerid][nCallBack_Skin], update_Variable[nCallBack_Skin]);
		pCallBack_Info[playerid][nCallBack_Skin] = update_Variable[nCallBack_Skin];
	}
	#endif
	#if defined CB_OnPlayerHoldWeaponChange
	update_Variable[nCallBack_HoldWeapon] = GetPlayerWeapon(playerid);
	if(pCallBack_Info[playerid][nCallBack_HoldWeapon] != update_Variable[nCallBack_HoldWeapon])
	{
		CallLocalFunction("OnPlayerHoldWeaponChange", "ddddd", playerid, GetWeaponSlot_ETI(pCallBack_Info[playerid][nCallBack_HoldWeapon]), pCallBack_Info[playerid][nCallBack_HoldWeapon], GetWeaponSlot_ETI(update_Variable[nCallBack_HoldWeapon]), update_Variable[nCallBack_HoldWeapon]);
		pCallBack_Info[playerid][nCallBack_HoldWeapon] = update_Variable[nCallBack_HoldWeapon];
	}
	#endif
	#if defined CB_OnPlayerWeaponStateChange
	update_Variable[nCallBack_WeaponState] = GetPlayerWeaponState(playerid);
	if(pCallBack_Info[playerid][nCallBack_WeaponState] != update_Variable[nCallBack_WeaponState])
	{
		CallLocalFunction("OnPlayerWeaponStateChange", "ddd", playerid, pCallBack_Info[playerid][nCallBack_WeaponState], update_Variable[nCallBack_WeaponState]);
		pCallBack_Info[playerid][nCallBack_WeaponState] = update_Variable[nCallBack_WeaponState];
	}
	#endif
	#if defined USE_WEAPON_DATA_CALLBACKS
	for(new i = 0; i < MAX_WEAPON_SLOTS; i++)
	{
		GetPlayerWeaponData(playerid, i, update_Variable[nCallBack_Weapon][i], update_Variable[nCallBack_Ammo][i]);
		#if defined CB_OnPlayerWeaponDataChange
		if(pCallBack_Info[playerid][nCallBack_Weapon][i] != update_Variable[nCallBack_Weapon][i])
		{
			CallLocalFunction("OnPlayerWeaponDataChange", "dddd", playerid, i, pCallBack_Info[playerid][nCallBack_Weapon][i], update_Variable[nCallBack_Weapon][i]);
			pCallBack_Info[playerid][nCallBack_Weapon][i] = update_Variable[nCallBack_Weapon][i];
		}
		#endif
		#if defined CB_OnPlayerAmmoDataChange
		if(pCallBack_Info[playerid][nCallBack_Ammo][i] != update_Variable[nCallBack_Ammo][i])
		{
			CallLocalFunction("OnPlayerAmmoDataChange", "dddd", playerid, i, pCallBack_Info[playerid][nCallBack_Ammo][i], update_Variable[nCallBack_Ammo][i]);
			pCallBack_Info[playerid][nCallBack_Ammo][i] = update_Variable[nCallBack_Ammo][i];
		}
		#endif
	}
	#endif
	#if defined CB_OnPlayerHealthChange
	GetPlayerHealth(playerid, update_Variable[nCallBack_Health]);
	if(pCallBack_Info[playerid][nCallBack_Health] != update_Variable[nCallBack_Health])
	{
		CallLocalFunction("OnPlayerHealthChange", "dff", playerid, pCallBack_Info[playerid][nCallBack_Health], update_Variable[nCallBack_Health]);
		pCallBack_Info[playerid][nCallBack_Health] = update_Variable[nCallBack_Health];
	}
	#endif
	#if defined CB_OnPlayerArmourChange
	GetPlayerArmour(playerid, update_Variable[nCallBack_Armour]);
	if(pCallBack_Info[playerid][nCallBack_Armour] != update_Variable[nCallBack_Armour])
	{
		CallLocalFunction("OnPlayerArmourChange", "dff", playerid, pCallBack_Info[playerid][nCallBack_Armour], update_Variable[nCallBack_Armour]);
		pCallBack_Info[playerid][nCallBack_Armour] = update_Variable[nCallBack_Armour];
	}
	#endif
	#if defined CB_OnPlayerAnimationIndexChange
	update_Variable[nCallBack_Animation] = GetPlayerAnimationIndex(playerid);
	if(pCallBack_Info[playerid][nCallBack_Animation] != update_Variable[nCallBack_Animation])
	{
		CallLocalFunction("OnPlayerAnimationIndexChange", "ddd", playerid, pCallBack_Info[playerid][nCallBack_Animation], update_Variable[nCallBack_Animation]);
		pCallBack_Info[playerid][nCallBack_Animation] = update_Variable[nCallBack_Animation];
	}
	#endif
	#if defined CB_OnPlayerSpecialActionChange
	update_Variable[nCallBack_SpecialAction] = GetPlayerSpecialAction(playerid);
	if(pCallBack_Info[playerid][nCallBack_SpecialAction] != update_Variable[nCallBack_SpecialAction])
	{
		CallLocalFunction("OnPlayerSpecialActionChange", "ddd", playerid, pCallBack_Info[playerid][nCallBack_SpecialAction], update_Variable[nCallBack_SpecialAction]);
		pCallBack_Info[playerid][nCallBack_SpecialAction] = update_Variable[nCallBack_SpecialAction];
	}
	#endif
	return ETI_ReturnOPU("d", playerid);
}
	#if defined _ALS_OnPlayerUpdate
		#undef OnPlayerUpdate
	#else
		#define _ALS_OnPlayerUpdate
	#endif
	#define OnPlayerUpdate ETI_OnPlayerUpdate
forward ETI_OnPlayerUpdate(playerid);
	#if defined CB_OnPlayerVirtualWorldChange
stock SetPlayerVirtualWorld_ETI(playerid, worldid)
{
	new oldworld = GetPlayerVirtualWorld(playerid);
	if(oldworld != worldid) CallLocalFunction("OnPlayerVirtualWorldChange", "ddd", playerid, oldworld, worldid);
	SetPlayerVirtualWorld(playerid, worldid);
}
		#define SetPlayerVirtualWorld(%0) SetPlayerVirtualWorld_ETI(%0)
	#endif
	#if !defined ETI_Kick
stock ETI_Kick(playerid)
{
	pCallBack_Info[playerid][nCallBack_KickedBanned] = true;
	Kick(playerid);
}
		#define Kick(%0) ETI_Kick(%0)
	#endif
	#if !defined ETI_Ban
stock ETI_Ban(playerid)
{
	pCallBack_Info[playerid][nCallBack_KickedBanned] = true;
	Ban(playerid);
}
		#define Ban(%0) ETI_Ban(%0)
	#endif
	#if !defined ETI_BanEx
stock ETI_BanEx(playerid, const reason[])
{
	pCallBack_Info[playerid][nCallBack_KickedBanned] = true;
	BanEx(playerid, reason);
}
		#define BanEx(%0) ETI_BanEx(%0)
	#endif
#endif
#if defined USE_PVAR_CALLBACKS
	#if defined CB_OnPVarDelete
forward OnPVarDelete(playerid, varname[], oldtype);
	#endif
	#if defined CB_OnPVarCreate
forward OnPVarCreate(playerid, varname[], type);
	#endif
	#if defined CB_OnPVarTypeChange
forward OnPVarTypeChange(playerid, varname[], oldtype, newtype);
	#endif
forward OnPVarIntChange(playerid, varname[], oldint_value, newint_value);
forward OnPVarStringChange(playerid, varname[], oldstring_value[], newstring_value[]);
forward OnPVarFloatChange(playerid, varname[], Float:oldfloat_value, Float:newfloat_value);
	#if !defined ReturnPVarString
stock ReturnPVarString(playerid, varname[])
{
	new pvstring[1024];
	GetPVarString(playerid, varname, pvstring, sizeof(pvstring));
	return pvstring;
}
	#endif
	#if defined CB_OnPVarDelete
stock DeletePVar_ETI(playerid, varname[])
{
	new pvartype = GetPVarType(playerid, varname);
	if(DeletePVar(playerid, varname))
	{
		CallLocalFunction("OnPVarDelete", "dsd", playerid, varname, pvartype);
		return 1;
	}
	return 0;
}
		#define DeletePVar(%0) DeletePVar_ETI(%0)
	#endif
stock SetPVarInt_ETI(playerid, varname[], int_value)
{
	#if defined CB_OnPVarCreate
	if(GetPVarType(playerid, varname) == 0) CallLocalFunction("OnPVarCreate", "dsd", playerid, varname, 1);
		#if defined CB_OnPVarTypeChange
	else
		#endif
	#endif
	#if defined CB_OnPVarTypeChange
	if(GetPVarType(playerid, varname) != 0 && GetPVarType(playerid, varname) != 1) CallLocalFunction("OnPVarTypeChange", "dsdd", playerid, varname, GetPVarType(playerid, varname), 1);
		#if defined CB_OnPVarIntChange
	else
		#endif
	#endif
	#if defined CB_OnPVarIntChange
	if(GetPVarInt(playerid, varname) != int_value) CallLocalFunction("OnPVarIntChange", "dsdd", playerid, varname, GetPVarInt(playerid, varname), int_value);
	#endif
	SetPVarInt(playerid, varname, int_value);
}
	#define SetPVarInt(%0) SetPVarInt_ETI(%0)
stock SetPVarString_ETI(playerid, varname[], string_value[])
{
	#if defined CB_OnPVarCreate
	if(GetPVarType(playerid, varname) == 0) CallLocalFunction("OnPVarCreate", "dsd", playerid, varname, 2);
		#if defined CB_OnPVarTypeChange
	else
		#endif
	#endif
	#if defined CB_OnPVarTypeChange
	if(GetPVarType(playerid, varname) != 0 && GetPVarType(playerid, varname) != 2) CallLocalFunction("OnPVarTypeChange", "dsdd", playerid, varname, GetPVarType(playerid, varname), 2);
		#if defined CB_OnPVarStringChange
	else
	{
		#endif
	#endif
	#if defined CB_OnPVarStringChange
		new strcmpval = strcmp(ReturnPVarString(playerid, varname), string_value);
		if(strcmpval == -1 || strcmpval == 1) CallLocalFunction("OnPVarStringChange", "dsss", playerid, varname, ReturnPVarString(playerid, varname), string_value);
		#if defined CB_OnPVarTypeChange
	}
		#endif
	#endif
	SetPVarString(playerid, varname, string_value);
}
	#define SetPVarString(%0) SetPVarString_ETI(%0)
stock SetPVarFloat_ETI(playerid, varname[], Float:float_value)
{
	#if defined CB_OnPVarCreate
	if(GetPVarType(playerid, varname) == 0) CallLocalFunction("OnPVarCreate", "dsd", playerid, varname, 3);
		#if defined CB_OnPVarTypeChange
	else
		#endif
	#endif
	#if defined CB_OnPVarTypeChange
	if(GetPVarType(playerid, varname) != 0 && GetPVarType(playerid, varname) != 3) CallLocalFunction("OnPVarTypeChange", "dsdd", playerid, varname, GetPVarType(playerid, varname), 3);
		#if defined CB_OnPVarFloatChange
	else
		#endif
	#endif
	#if defined CB_OnPVarFloatChange
	if(GetPVarFloat(playerid, varname) != float_value) CallLocalFunction("OnPVarFloatChange", "dsff", playerid, varname, GetPVarFloat(playerid, varname), float_value);
	#endif
	SetPVarFloat(playerid, varname, float_value);
}
	#define SetPVarFloat(%0) SetPVarFloat_ETI(%0)
#endif