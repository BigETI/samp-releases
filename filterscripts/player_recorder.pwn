#include <a_samp>
#include <list>

MEM::struct player_info
{
	player_info_time,
	player_info_skin_weapon,
	player_info_vehicle,
	Float:player_info_pos[4],
	Float:player_info_velocity[3],
	player_info_animation
}

new LIST::init<player_recorder[MAX_PLAYERS]>, bool:deny_action = false, first_tick[MAX_PLAYERS];

stock SavePlayerRecord(playerid)
{
	new year, month, day, hour, minute, second, name[MAX_PLAYER_NAME], file_name[43+MAX_PLAYER_NAME];
	getdate(year, month, day);
	gettime(hour, minute, second);
	GetPlayerName(playerid, name, sizeof name);
	format(file_name, sizeof file_name, "player_recordings/%d-%02d-%02d_%02d-%02d-%02d_%s.crec", year, month, day, hour, minute, second, name);
	LIST::save(player_recorder[playerid], file_name, true);
}

public OnFilterScriptInit()
{
	for(new i = 0, tick = GetTickCount(); i < MAX_PLAYERS; i++)
	{
		if(!IsPlayerConnected(i)) continue;
		first_tick[i] = tick;
	}
	print("\n===========================");
	print("= Instant player recorder =");
	print("=     Made by BigETI      =");
	print("=         Loaded!         =");
	print("===========================\n");
	return 1;
}

public OnFilterScriptExit()
{
	deny_action = true;
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(!IsPlayerConnected(i)) continue;
		SavePlayerRecord(i);
	}
	print("\n===========================");
	print("= Instant player recorder =");
	print("=     Made by BigETI      =");
	print("=        Unloaded!        =");
	print("===========================\n");
	return 1;
}

public OnPlayerConnect(playerid)
{
	if(deny_action) return 1;
	first_tick[playerid] = GetTickCount();
	return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
	if(deny_action) return 1;
	SavePlayerRecord(playerid);
	return 1;
}

public OnPlayerUpdate(playerid)
{
	if(deny_action) return 1;
	static player_buffer[player_info], vehicleid;
	player_buffer[player_info_time] = GetTickCount()-first_tick[playerid];
	player_buffer[player_info_skin_weapon] = GetPlayerSkin(playerid)|(GetPlayerWeapon(playerid)<<16);
	if((vehicleid = GetPlayerVehicleID(playerid)))
	{
		player_buffer[player_info_vehicle] = GetVehicleModel(vehicleid)|(GetPlayerVehicleSeat(playerid)<<16);
		GetVehiclePos(vehicleid, player_buffer[player_info_pos][0], player_buffer[player_info_pos][1], player_buffer[player_info_pos][2]);
		GetVehicleZAngle(vehicleid, player_buffer[player_info_pos][3]);
		GetVehicleVelocity(vehicleid, player_buffer[player_info_velocity][0], player_buffer[player_info_velocity][1], player_buffer[player_info_velocity][2]);
	}
	else
	{
		GetPlayerPos(playerid, player_buffer[player_info_pos][0], player_buffer[player_info_pos][1], player_buffer[player_info_pos][2]);
		GetPlayerFacingAngle(playerid, player_buffer[player_info_pos][3]);
		GetPlayerVelocity(playerid, player_buffer[player_info_velocity][0], player_buffer[player_info_velocity][1], player_buffer[player_info_velocity][2]);
	}
	player_buffer[player_info_animation] = GetPlayerAnimationIndex(playerid);
	LIST::push_back_arr(player_recorder[playerid], player_buffer);
	return 1;
}