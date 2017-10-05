#include <a_samp>
#include <list>

#define NO_RESPONSE_DIALOGID							(0)
#define LASTKILLS_DIALOGID								(1000)

#if NO_RESPONSE_DIALOGID == LASTKILLS_DIALOGID
	#error You are not allowed to set NO_RESPONSE_DIALOGID equal LASTKILLS_DIALOGID.
#endif

#define NULL_PTR										(Pointer:NULL)
#define KILLS_FILE										"kills.binlist"
#define MAX_LIST_KILLS									(30)
#define GetDistanceBetweenPoints%6(%0,%1,%2,%3,%4,%5)	floatsqroot(floatpower((%3)-(%0),2.0)+floatpower((%4)-(%1),2.0)+floatpower((%5)-(%2),2.0))

MEM::struct kill_struct
{
	kill_datetime,
	kill_victimid,
	kill_victimip[16],
	kill_victimname[MAX_PLAYER_NAME],
	kill_killerid,
	kill_killerip[16],
	kill_killername[MAX_PLAYER_NAME],
	kill_reason,
	Float:kill_victimpos_x,
	Float:kill_victimpos_y,
	Float:kill_victimpos_z,
	Float:kill_victimpos_rotz,
	Float:kill_killerpos_x,
	Float:kill_killerpos_y,
	Float:kill_killerpos_z,
	Float:kill_killerpos_rotz
}

new LIST::init<kills_list>, Pointer:kill_ptrs_arr[MAX_PLAYERS] = {NULL_PTR, ...}, listed_kills[MAX_PLAYERS] = {0, ...};

static const WeapName[202][32] = {
	"N/A",					// 0
	"Brass Knuckles",		// 1
	"Golf Club",			// 2
	"Night Stick",			// 3
	"Knife",				// 4
	"Baseball Bat",			// 5
	"Shovel",				// 6
	"Pool Cue",				// 7
	"Katana",				// 8
	"Chainsaw",				// 9
	"Dildo",				// 10
	"B-White Vibrator",		// 11
	"M-White Vibrator",		// 12
	"S-White Vibrator",		// 13
	"Flowers",				// 14
	"Cane",					// 15
	"Grenade",				// 16
	"Teargas",				// 17
	"Molotov",				// 18
	"Vehicle missile",		// 19
	"Hydra flare",			// 20
	"Jetpack",				// 21
	"Pistol",				// 22
	"S-Pistol",				// 23
	"Deagle",				// 24
	"Shotgun",				// 25
	"Sawnoff",				// 26
	"SPAZ",					// 27
	"UZI",					// 28
	"MP5",					// 29
	"AK47",					// 30
	"M4",					// 31
	"Tec9",					// 32
	"Country Rifle",		// 33
	"Sniper",				// 34
	"RPG",					// 35
	"HS RPG",				// 36
	"Flamethrower",			// 37
	"Minigun",				// 38
	"Satchel Bombs",		// 39
	"Detonator",			// 40
	"Spray Can",			// 41
	"Fire Extinguisher",	// 42
	"Camera",				// 43
	"NV Goggles",			// 44
	"IRV Goggles",			// 45
	"Parachute",			// 46
	"Fake Pistol",			// 47
	" ",					//
	"Vehicle",				// 49
	"Helicopter blades",	// 50
	"Explosion",			// 51
	" ",					//
	" ",					//
	"Collision",			// 54
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					// 60
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					// 70
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					// 80
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					// 90
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					// 100
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					// 110
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					// 120
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					// 130
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					// 140
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					// 150
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					// 160
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					// 170
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					// 180
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					// 190
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	" ",					//
	"Connect",				// 200
	"Disconnect"			// 201
};

stock ReturnWeaponName(weaponid)
{
	new str[32];
	if(weaponid < 0 || weaponid > 201) format(str, sizeof(str), "Unknown");
	else format(str, sizeof(str), WeapName[weaponid]);
	return str;
}

stock bool:ShowLastKills(playerid, ListIt:iterator)
{
	new now = gettime(), captcha[22], kills_dialog_str[1586], days, hours, minutes, seconds;
	listed_kills[playerid] = 0;
	if((kill_ptrs_arr[playerid] = MEM::calloc(MAX_LIST_KILLS)) == NULL_PTR)
	{
		SendClientMessage(playerid, 0xFF0000FF, "An error has occured. Please retry later.");
		return false;
	}
	for(new ListIt:kills_it = iterator; _:kills_it != NULL; kills_it = ListIt:MEM_EX::get_val(Pointer:(kills_it)->LIST_IT_data_previous))
	{
		MEM::set_val(kill_ptrs_arr[playerid], listed_kills[playerid]++, _:kills_it);
		days = (hours = (minutes = 0));
		seconds = now-LIST_IT::data_val(kills_it, kill_datetime);
		while(seconds > 86399)
		{
			seconds -= 86400;
			days++;
		}
		while(seconds > 3599)
		{
			seconds -= 3600;
			hours++;
		}
		while(seconds > 59)
		{
			seconds -= 60;
			minutes++;
		}
		if(days == 0)
		{
			if(hours == 0)
			{
				if(minutes == 0)
				{
					if(seconds == 0) strcat(kills_dialog_str, "Now\r\n");
					else format(kills_dialog_str, sizeof kills_dialog_str, "%s%d %s ago\n", kills_dialog_str, seconds, (seconds == 1)?("second"):("seconds"));
				}
				else format(kills_dialog_str, sizeof kills_dialog_str, "%s%d %s, and %d %s ago\n", kills_dialog_str, minutes, (minutes == 1)?("minute"):("minutes"), seconds, (seconds == 1)?("second"):("seconds"));
			}
			else format(kills_dialog_str, sizeof kills_dialog_str, "%s%d %s, %d %s, and %d %s ago\n", kills_dialog_str, hours, (hours == 1)?("hour"):("hours"), minutes, (minutes == 1)?("minute"):("minutes"), seconds, (seconds == 1)?("second"):("seconds"));
		}
		else format(kills_dialog_str, sizeof kills_dialog_str, "%s%d %s, %d %s, %d %s, and %d %s ago\n", kills_dialog_str, days, (days == 1)?("day"):("days"), hours, (hours == 1)?("hour"):("hours"), minutes, (minutes == 1)?("minute"):("minutes"), seconds, (seconds == 1)?("second"):("seconds"));
		if(listed_kills[playerid] >= MAX_LIST_KILLS) break;
	}
	if(listed_kills[playerid] == 0)
	{
		MEM::free(kill_ptrs_arr[playerid]);
		kill_ptrs_arr[playerid] = NULL_PTR;
		if(iterator == ListIt:kills_list[LIST_base_end]) SendClientMessage(playerid, 0xFF0000FF, "There are no kills recorded.");
		else SendClientMessage(playerid, 0xFF0000FF, "There are no more kills recorded.");
		return false;
	}
	strcat(kills_dialog_str, "{FF7F00}More\n{7F7F7F}Exit");
	if(iterator == ListIt:kills_list[LIST_base_end]) format(captcha, sizeof captcha, "{FF0000}Last %d kills", listed_kills[playerid]);
	else format(captcha, sizeof captcha, "{FF0000}More %d kills", listed_kills[playerid]);
	ShowPlayerDialog(playerid, LASTKILLS_DIALOGID, DIALOG_STYLE_LIST, captcha, kills_dialog_str, "Choose", "Exit");
	return true;
}

public OnFilterScriptInit()
{
	LIST::load(kills_list, KILLS_FILE);
	print("\n===============================");
	print("= Example kills filter script =");
	print("=       Made by BigETI        =");
	print("=           Loaded!           =");
	print("===============================\n");
	return 1;
}

public OnFilterScriptExit()
{
	LIST::save(kills_list, KILLS_FILE, true);
	for(new i = 0; i < sizeof kill_ptrs_arr; i++)
	{
		if(kill_ptrs_arr[i] == NULL_PTR) continue;
		ShowPlayerDialog(i, -1, DIALOG_STYLE_MSGBOX, "", "", "", "");
		MEM::free(kill_ptrs_arr[i]);
	}
	print("\n===============================");
	print("= Example kills filter script =");
	print("=       Made by BigETI        =");
	print("=          Unloaded!          =");
	print("===============================\n");
	return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
	MEM::free(kill_ptrs_arr[playerid]);
	kill_ptrs_arr[playerid] = NULL_PTR;
	listed_kills[playerid] = 0;
	return 1;
}

public OnPlayerDeath(playerid, killerid, reason)
{
	new kill_buffer[kill_struct];
	kill_buffer[kill_datetime] = gettime();
	kill_buffer[kill_victimid] = playerid;
	GetPlayerIp(playerid, kill_buffer[kill_victimip], 16);
	GetPlayerName(playerid, kill_buffer[kill_victimname], MAX_PLAYER_NAME);
	if((kill_buffer[kill_killerid] = killerid) == INVALID_PLAYER_ID)
	{
		kill_buffer[kill_killerpos_x] = 0.0;
		kill_buffer[kill_killerpos_y] = 0.0;
		kill_buffer[kill_killerpos_z] = 0.0;
		kill_buffer[kill_killerpos_rotz] = 0.0;
	}
	else
	{
		GetPlayerIp(killerid, kill_buffer[kill_killerip], 16);
		GetPlayerName(killerid, kill_buffer[kill_killername], MAX_PLAYER_NAME);
		GetPlayerPos(killerid, kill_buffer[kill_killerpos_x], kill_buffer[kill_killerpos_y], kill_buffer[kill_killerpos_z]);
		GetPlayerFacingAngle(killerid, kill_buffer[kill_killerpos_rotz]);
	}
	kill_buffer[kill_reason] = reason;
	GetPlayerPos(playerid, kill_buffer[kill_victimpos_x], kill_buffer[kill_victimpos_y], kill_buffer[kill_victimpos_z]);
	GetPlayerFacingAngle(playerid, kill_buffer[kill_victimpos_rotz]);
	LIST::push_back_arr(kills_list, kill_buffer);
	return 1;
}

public OnPlayerCommandText(playerid, cmdtext[])
{
	if(!strcmp(cmdtext, "/lastkills", true, 11))
	{
		if(kill_ptrs_arr[playerid]) return SendClientMessage(playerid, 0xFF0000FF, "You are already looking for the last kills.");
		ShowLastKills(playerid, ListIt:kills_list[LIST_base_end]);
		return 1;
	}
	return 0;
}

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch(dialogid)
	{
		case LASTKILLS_DIALOGID:
		{
			if(response)
			{
				if(listitem >= listed_kills[playerid])
				{
					if(listitem == listed_kills[playerid]) {if(!ShowLastKills(playerid, LIST_IT::previous(MEM::get_val(kill_ptrs_arr[playerid], listed_kills[playerid]-1)))) return 1;}
					else
					{
						MEM::free(kill_ptrs_arr[playerid]);
						kill_ptrs_arr[playerid] = NULL_PTR;
						listed_kills[playerid] = 0;
						return SendClientMessage(playerid, 0xFF0000FF, "You have canceled the last kills dialog.");
					}
				}
				else
				{
					new kill_buffer[kill_struct], caption[52], kill_info_dialog_str[543], days, hours, minutes, seconds;
					MEM::get_arr(LIST_IT::data_ptr(ListIt:MEM::get_val(kill_ptrs_arr[playerid], listitem)), _, kill_buffer);
					seconds = gettime()-kill_buffer[kill_datetime];
					while(seconds > 86399)
					{
						seconds -= 86400;
						days++;
					}
					while(seconds > 3599)
					{
						seconds -= 3600;
						hours++;
					}
					while(seconds > 59)
					{
						seconds -= 60;
						minutes++;
					}
					if(days == 0)
					{
						if(hours == 0)
						{
							if(minutes == 0)
							{
								if(seconds == 0) format(caption, sizeof caption, "Now");
								else format(caption, sizeof caption, "%d %s ago", seconds, (seconds == 1)?("second"):("seconds"));
							}
							else format(caption, sizeof caption, "%d %s, and %d %s ago", minutes, (minutes == 1)?("minute"):("minutes"), seconds, (seconds == 1)?("second"):("seconds"));
						}
						else format(caption, sizeof caption, "%d %s, %d %s, and %d %s ago", hours, (hours == 1)?("hour"):("hours"), minutes, (minutes == 1)?("minute"):("minutes"), seconds, (seconds == 1)?("second"):("seconds"));
					}
					else format(caption, sizeof caption, "%d %s, %d %s, %d %s, and %d %s ago", days, (days == 1)?("day"):("days"), hours, (hours == 1)?("hour"):("hours"), minutes, (minutes == 1)?("minute"):("minutes"), seconds, (seconds == 1)?("second"):("seconds"));
					if(kill_buffer[kill_killerid] == INVALID_PLAYER_ID)
					{
						format(kill_info_dialog_str, sizeof kill_info_dialog_str, "{0000FF}Type: {FFFFFF}Suicide\n\n{0000FF}Suicides: {FFFFFF}%s ( %d : %s )\n{0000FF}Suicide weapon: {FFFFFF}%s{FFFFFF}\n\n\n{0000FF}Location:\n {FFFFFF}- X: %.4f\n - Y: %.4f\n - Z: %.4f\n - Angle: %.4f",
							kill_buffer[kill_victimname], kill_buffer[kill_victimid], kill_buffer[kill_victimip], ReturnWeaponName(kill_buffer[kill_reason]), kill_buffer[kill_victimpos_x], kill_buffer[kill_victimpos_y], kill_buffer[kill_victimpos_z], kill_buffer[kill_victimpos_rotz]);
					}
					else
					{
						format(kill_info_dialog_str, sizeof kill_info_dialog_str, "{0000FF}Type: {FFFFFF}Murder\n\n{0000FF}Victim: {FFFFFF}%s ( %d : %s )\n{0000FF}Killer: {FFFFFF}%s ( %d : %s )\n\n{0000FF}Murder weapon: {FFFFFF}%s ( %.4f meters )\n\n\n",
							kill_buffer[kill_victimname], kill_buffer[kill_victimid], kill_buffer[kill_victimip], kill_buffer[kill_killername], kill_buffer[kill_killerid], kill_buffer[kill_killerip], ReturnWeaponName(kill_buffer[kill_reason]),
							GetDistanceBetweenPoints(kill_buffer[kill_victimpos_x], kill_buffer[kill_victimpos_y], kill_buffer[kill_victimpos_z], kill_buffer[kill_killerpos_x], kill_buffer[kill_killerpos_y], kill_buffer[kill_killerpos_z]));
						format(kill_info_dialog_str, sizeof kill_info_dialog_str, "%s{0000FF}Victim: {FFFFFF}- X: %.4f\n - Y: %.4f\n - Z: %.4f\n - Angle: %.4f\n\n{0000FF}Killer: {FFFFFF}- X: %.4f\n - Y: %.4f\n - Z: %.4f\n - Angle: %.4f",
							kill_info_dialog_str, kill_buffer[kill_victimpos_x], kill_buffer[kill_victimpos_y], kill_buffer[kill_victimpos_z], kill_buffer[kill_victimpos_rotz], kill_buffer[kill_killerpos_x], kill_buffer[kill_killerpos_y], kill_buffer[kill_killerpos_z], kill_buffer[kill_killerpos_rotz]);
					}
					ShowPlayerDialog(playerid, NO_RESPONSE_DIALOGID, DIALOG_STYLE_MSGBOX, caption, kill_info_dialog_str, "OK", "");
					MEM::free(kill_ptrs_arr[playerid]);
					kill_ptrs_arr[playerid] = NULL_PTR;
					listed_kills[playerid] = 0;
				}
			}
			else
			{
				MEM::free(kill_ptrs_arr[playerid]);
				kill_ptrs_arr[playerid] = NULL_PTR;
				listed_kills[playerid] = 0;
			}
		}
	}
	return 1;
}