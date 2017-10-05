// A way to read and write binary files and handle them as player stats files

#include <a_samp>
#include <b_io> // http://pastebin.com/HhZmT4JV

#define RED					0xFF0000FF
#define PLAYER_FILE			"%s.bacc"
#define MAX_WEAPON_SLOTS	(13)

BIO_E::ENUM P_STATS_ENUM
{
	BIO_E::16<P_STATS_SKIN>,
	BIO_E::32<P_STATS_MONEY>,
	BIO_E::32<P_STATS_SCORE>,
	BIO_E::8A<P_STATS_WEAPON>[MAX_WEAPON_SLOTS],
	BIO_E::32A<P_STATS_AMMO>[MAX_WEAPON_SLOTS],
	BIO_E::FA<P_STATS_POS>[4],
	BIO_E::8A<P_STATS_IP>[16]
}

new player_stats[MAX_PLAYERS][P_STATS_ENUM];

stock LoadPlayerStats(playerid)
{
	new pip[16], file_name[64], pname[MAX_PLAYER_NAME];
	GetPlayerIp(playerid, pip, sizeof pip);
	SetPVarString(playerid, "b_io_fs_IP", pip);
	GetPlayerName(playerid, pname, sizeof pname);
	format(file_name, sizeof file_name, PLAYER_FILE, pname);
	if(BIO::exist(file_name))
	{
		new BFile:file_handle = BIO::open(file_name, b_io_mode_read);
		if(file_handle)
		{
			player_stats[playerid][P_STATS_SKIN] = BIO::read_16(file_handle, P_STATS_SKIN, seek_start);
			printf("Skin: %d", player_stats[playerid][P_STATS_SKIN]);
			player_stats[playerid][P_STATS_MONEY] = BIO::read_32(file_handle, P_STATS_MONEY, seek_start);
			player_stats[playerid][P_STATS_SCORE] = BIO::read_32(file_handle, P_STATS_SCORE, seek_start);
			BIO::read_8_arr(file_handle, player_stats[playerid][P_STATS_WEAPON], MAX_WEAPON_SLOTS, P_STATS_WEAPON, seek_start);
			BIO::read_32_arr(file_handle, player_stats[playerid][P_STATS_AMMO], MAX_WEAPON_SLOTS, P_STATS_AMMO, seek_start);
			BIO::read_32_arr(file_handle, _:player_stats[playerid][P_STATS_POS], 4, P_STATS_POS, seek_start);
			BIO::read_8_arr(file_handle, player_stats[playerid][P_STATS_IP], 16, P_STATS_IP, seek_start);
			BIO::close(file_handle);
			SendClientMessage(playerid, RED, "Your stats (before they was saved):");
			new str[128];
			format(str, sizeof str, "-> Skin: %d", player_stats[playerid][P_STATS_SKIN]);
			SendClientMessage(playerid, RED, str);
			format(str, sizeof str, "-> Money: %d", player_stats[playerid][P_STATS_MONEY]);
			SendClientMessage(playerid, RED, str);
			format(str, sizeof str, "-> Score: %d", player_stats[playerid][P_STATS_SCORE]);
			SendClientMessage(playerid, RED, str);
			format(str, sizeof str, "-> Position: X: %.4f; Y: %.4f; Z: %.4f; RotZ: %.4f", player_stats[playerid][P_STATS_POS][0], player_stats[playerid][P_STATS_POS][1], player_stats[playerid][P_STATS_POS][2], player_stats[playerid][P_STATS_POS][3]);
			SendClientMessage(playerid, RED, str);
			format(str, sizeof str, "-> IP: %s", player_stats[playerid][P_STATS_IP]);
			SendClientMessage(playerid, RED, str);
			SetPVarInt(playerid, "b_io_fs_loaded", 1);
		}
		else printf("Failed to open file \"%s\"", file_name);
		return 1;
	}
	return 0;
}

stock SavePlayerStats(playerid)
{
	new file_name[64], pname[MAX_PLAYER_NAME];
	GetPlayerName(playerid, pname, sizeof pname);
	format(file_name, sizeof file_name, PLAYER_FILE, pname);
	new BFile:file_handle = BIO::open(file_name, b_io_mode_write);
	if(file_handle)
	{
		BIO::write_16(file_handle, player_stats[playerid][P_STATS_SKIN] = GetPlayerSkin(playerid), P_STATS_SKIN, seek_start);
		BIO::write_32(file_handle, player_stats[playerid][P_STATS_MONEY] = GetPlayerMoney(playerid), P_STATS_MONEY, seek_start);
		BIO::write_32(file_handle, player_stats[playerid][P_STATS_SCORE] = GetPlayerScore(playerid), P_STATS_SCORE, seek_start);
		for(new i = 0; i < MAX_WEAPON_SLOTS; i++) GetPlayerWeaponData(playerid, i, player_stats[playerid][P_STATS_WEAPON][i], player_stats[playerid][P_STATS_AMMO][i]);
		BIO::write_8_arr(file_handle, player_stats[playerid][P_STATS_WEAPON], MAX_WEAPON_SLOTS, P_STATS_WEAPON, seek_start);
		BIO::write_32_arr(file_handle, player_stats[playerid][P_STATS_AMMO], MAX_WEAPON_SLOTS, P_STATS_AMMO, seek_start);
		GetPlayerPos(playerid, player_stats[playerid][P_STATS_POS][0], player_stats[playerid][P_STATS_POS][1], player_stats[playerid][P_STATS_POS][2]);
		GetPlayerFacingAngle(playerid, player_stats[playerid][P_STATS_POS][3]);
		BIO::write_32_arr(file_handle, _:player_stats[playerid][P_STATS_POS], 4, P_STATS_POS, seek_start);
		GetPVarString(playerid, "b_io_fs_IP", player_stats[playerid][P_STATS_IP], 16);
		BIO::write_8_arr(file_handle, player_stats[playerid][P_STATS_IP], 16, P_STATS_IP, seek_start);
		BIO::close(file_handle);
		SetPVarInt(playerid, "b_io_fs_loaded", 1);
		return 1;
	}
	printf("Failed to open file \"%s\"", file_name);
	return 0;
}

public OnFilterScriptInit()
{
	for(new i = 0; i < MAX_PLAYERS; i++) if(IsPlayerConnected(i)) LoadPlayerStats(i);
	print("\n===================================================");
	print("= Binary files I/O plugin's example filter script =");
	print("=                                  Made by BigETI =");
	print("= Loaded!                                         =");
	print("===================================================\n");
	return 1;
}

public OnFilterScriptExit()
{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(!IsPlayerConnected(i)) continue;
		SavePlayerStats(i);
		DeletePVar(i, "b_io_fs_loaded");
	}
	print("\n===================================================");
	print("= Binary files I/O plugin's example filter script =");
	print("=                                  Made by BigETI =");
	print("= Unloaded!                                       =");
	print("===================================================\n");
	return 1;
}

public OnPlayerConnect(playerid)
{
	LoadPlayerStats(playerid);
	return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
	SavePlayerStats(playerid);
	return 1;
}

public OnPlayerSpawn(playerid) return 1;

public OnPlayerDeath(playerid, killerid, reason)
{
	if(SavePlayerStats(playerid)) return SendClientMessage(playerid, RED, "You died, so your stats have been saved.");
	return SendClientMessage(playerid, RED, "You died, but your stats can't be saved, because of an unknown error.");
}

public OnPlayerCommandText(playerid, cmdtext[])
{
	if(!strcmp("/savemystats", cmdtext, true))
	{
		if(SavePlayerStats(playerid)) return SendClientMessage(playerid, RED, "Your stats has been successfully saved!");
		return SendClientMessage(playerid, RED, "Failed to save your current stats!");
	}
	if(!strcmp("/returnmystats", cmdtext, true))
	{
		if(GetPVarType(playerid, "b_io_fs_loaded") == 0) return SendClientMessage(playerid, RED, "Please use \"/savemystats\", die, or re-log before you can use this command.");
		SetPlayerPos(playerid, player_stats[playerid][P_STATS_POS][0], player_stats[playerid][P_STATS_POS][1], player_stats[playerid][P_STATS_POS][2]);
		SetPlayerFacingAngle(playerid, player_stats[playerid][P_STATS_POS][3]);
		SetCameraBehindPlayer(playerid);
		SetPlayerSkin(playerid, player_stats[playerid][P_STATS_SKIN]);
		ResetPlayerMoney(playerid);
		GivePlayerMoney(playerid, player_stats[playerid][P_STATS_MONEY]);
		SetPlayerScore(playerid, player_stats[playerid][P_STATS_SCORE]);
		ResetPlayerWeapons(playerid);
		for(new i = 0; i < MAX_WEAPON_SLOTS; i++) GivePlayerWeapon(playerid, player_stats[playerid][P_STATS_WEAPON][i], player_stats[playerid][P_STATS_AMMO][i]);
		return SendClientMessage(playerid, RED, "You have successfully returned your older stats back.");
	}
	if(!strcmp("/checkskin", cmdtext, true))
	{
		if(GetPVarType(playerid, "b_io_fs_loaded") == 0) return SendClientMessage(playerid, RED, "Please use \"/savemystats\", die, or re-log before you can use this command.");
		new str[128], file_name[64], pname[MAX_PLAYER_NAME];
		GetPlayerName(playerid, pname, sizeof pname);
		format(file_name, sizeof file_name, PLAYER_FILE, pname);
		BIO_I::open(file_name, b_io_mode_read);
		format(str, sizeof str, "Your skin is saved as ID %d", BIO_I::read_16(P_STATS_SKIN));
		SendClientMessage(playerid, RED, str);
		return 1;
	}
	if(!strcmp("/checkmoney", cmdtext, true))
	{
		if(GetPVarType(playerid, "b_io_fs_loaded") == 0) return SendClientMessage(playerid, RED, "Please use \"/savemystats\", die, or re-log before you can use this command.");
		new str[128], file_name[64], pname[MAX_PLAYER_NAME];
		GetPlayerName(playerid, pname, sizeof pname);
		format(file_name, sizeof file_name, PLAYER_FILE, pname);
		BIO_I::open(file_name, b_io_mode_read);
		format(str, sizeof str, "Your money is saved as %d", BIO_I::read_32(P_STATS_MONEY));
		SendClientMessage(playerid, RED, str);
		return 1;
	}
	if(!strcmp("/checkscore", cmdtext, true))
	{
		if(GetPVarType(playerid, "b_io_fs_loaded") == 0) return SendClientMessage(playerid, RED, "Please use \"/savemystats\", die, or re-log before you can use this command.");
		new str[128], file_name[64], pname[MAX_PLAYER_NAME];
		GetPlayerName(playerid, pname, sizeof pname);
		format(file_name, sizeof file_name, PLAYER_FILE, pname);
		BIO_I::open(file_name, b_io_mode_read);
		format(str, sizeof str, "Your score is saved as %d", BIO_I::read_32(P_STATS_SCORE));
		SendClientMessage(playerid, RED, str);
		return 1;
	}
	if(!strcmp("/checkpos", cmdtext, true))
	{
		if(GetPVarType(playerid, "b_io_fs_loaded") == 0) return SendClientMessage(playerid, RED, "Please use \"/savemystats\", die, or re-log before you can use this command.");
		new str[128], file_name[64], pname[MAX_PLAYER_NAME], Float:p_pos[4];
		GetPlayerName(playerid, pname, sizeof pname);
		format(file_name, sizeof file_name, PLAYER_FILE, pname);
		BIO_I::open(file_name, b_io_mode_read);
		BIO_I::read_32_arr(_:p_pos, 4, P_STATS_POS);
		format(str, sizeof str, "Your pos is saved as X: %.4f; Y: %.4f; Z: %.4f; RotZ: %.4f", p_pos[0], p_pos[1], p_pos[2], p_pos[3]);
		SendClientMessage(playerid, RED, str);
		return 1;
	}
	if(!strcmp("/checkip", cmdtext, true))
	{
		if(GetPVarType(playerid, "b_io_fs_loaded") == 0) return SendClientMessage(playerid, RED, "Please use \"/savemystats\", die, or re-log before you can use this command.");
		new str[128], file_name[64], pname[MAX_PLAYER_NAME], ip[16];
		GetPlayerName(playerid, pname, sizeof pname);
		format(file_name, sizeof file_name, PLAYER_FILE, pname);
		BIO_I::open(file_name, b_io_mode_read);
		BIO_I::read_8_arr(ip, 16, P_STATS_IP, seek_start);
		format(str, sizeof str, "Your IP is saved as %s", ip);
		SendClientMessage(playerid, RED, str);
		return 1;
	}
	return 0;
}