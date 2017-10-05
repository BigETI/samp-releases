/*
	SA:MP Soundz Player Filterscript made by BigETI ©
	Ideas from FoxHound (http://forum.sa-mp.de/san-andreas-multiplayer/scripting-base/showroom/24082-sound-player-sopla/)
	This script is not an extension or copy of the SoPla filterscript.
	So all rights are reserverd ©
*/

//Includes
#include <a_samp>

#define MAX_SOUNDS	63
#define MAX_ENTRIES 25
#define BSP_MENU_DIALOGID  				1000
#define BSP_LIST1_DIALOGID 				1001
#define BSP_LIST2_DIALOGID 				1002
#define BSP_LIST3_DIALOGID 				1003
#define BSP_CREDITS_DIALOGID            1004
#define RED                             0xFF0000FF

//Enums
enum Sound_Infos
{
	SOUND_NAME[33],
	SOUND_ID,
};

//News
new Sounds[][Sound_Infos] = {
{"CEILING_VENT_LAND", 1002,},
{"BONNET_DENT", 1009,},
{"CRANE_MOVE_START", 1020,},
{"CRANE_MOVE_STOP", 1021,},
{"CRANE_EXIT", 1022,},
{"WHEEL_OF_FORTUNE_CLACKER", 1027,},
{"SHUTTER_DOOR_START", 1035,},
{"SHUTTER_DOOR_STOP", 1036,},
{"PARACHUTE_OPEN", 1039,},
{"AMMUNATION_BUY_WEAPON", 1052,},
{"AMMUNATION_BUY_WEAPON_DENIED", 1053,},
{"SHOP_BUY", 1054,},
{"SHOP_BUY_DENIED", 1055,},
{"RACE_321", 1056,},
{"RACE_GO", 1057,},
{"PART_MISSION_COMPLETE", 1058,},
{"GOGO_TRACK_START(music)", 1062,},
{"GOGO_TRACK_STOP(music)", 1063,},
{"DUAL_TRACK_START(music)", 1068,},
{"DUAL_TRACK_STOP(music)", 1069,},
{"BEE_TRACK_START(music)", 1076,},
{"BEE_TRACK_STOP(music)", 1077,},
{"ROULETTE_ADD_CASH", 1083,},
{"ROULETTE_REMOVE_CASH", 1084,},
{"ROULETTE_NO_CASH", 1085,},
{"BIKE_PACKER_CLUNK", 1095,},
{"AWARD_TRACK_START(music)", 1097,},
{"AWARD_TRACK_STOP(music)", 1098,},
{"MESH_GATE_OPEN_START", 1100,},
{"MESH_GATE_OPEN_STOP", 1101,},
{"PUNCH_PED", 1130,},
{"AMMUNATION_GUN_COLLISION", 1131,},
{"CAMERA_SHOT", 1132,},
{"BUY_CAR_MOD", 1133,},
{"BUY_CAR_RESPRAY", 1134,},
{"BASEBALL_BAT_HIT_PED", 1135,},
{"STAMP_PED", 1136,},
{"CHECKPOINT_AMBER", 1137,},
{"CHECKPOINT_GREEN", 1138,},
{"CHECKPOINT_RED", 1139,},
{"CAR_SMASH_CAR", 1140,},
{"CAR_SMASH_GATE", 1141,},
{"OTB_TRACK_START", 1142,},
{"OTB_TRACK_STOP", 1143,},
{"PED_HIT_WATER_SPLASH", 1144,},
{"RESTAURANT_TRAY_COLLISION", 1145,},
{"SWEETS_HORN", 1147,},
{"MAGNET_VEHICLE_COLLISION", 1148,},
{"PROPERTY_PURCHASED", 1149,},
{"PICKUP_STANDARD", 1150,},
{"GARAGE_DOOR_START", 1153,},
{"GARAGE_DOOR_STOP", 1154,},
{"PED_COLLAPSE", 1163,},
{"SHUTTER_DOOR_SLOW_START", 1165,},
{"SHUTTER_DOOR_SLOW_STOP", 1166,},
{"RESTAURANT_CJ_PUKE", 1169,},
{"DRIVING_AWARD_TRACK_START(music)", 1183,},
{"DRIVING_AWARD_TRACK_STOP", 1184,},
{"BIKE_AWARD_TRACK_START(music)", 1185,},
{"BIKE_AWARD_TRACK_STOP", 1186,},
{"PILOT_AWARD_TRACK_START(music)", 1187,},
{"PILOT_AWARD_TRACK_STOP", 1188,},
{"SLAP", 1190,}
};

//Publics
public OnFilterScriptInit()
{
	print("\n=================================================");
	print(" SA:MP Soundz Player Filterscript made by BigETI©");
	print("=========== All rights are reserved! ============");
	print("=================================================\n");
	return 1;
}

public OnPlayerCommandText(playerid, cmdtext[])
{
	if(!strcmp("/soundplayer", cmdtext, true))
	{
	    ShowPlayerDialog(playerid, BSP_MENU_DIALOGID, DIALOG_STYLE_LIST, "SA:MP Soundz by BigETI", "Sounds (All)\nSearch\nCredits\nExit", "Choose", "Exit");
		return 1;
	}
	return 0;
}

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch(dialogid)
	{
		case BSP_MENU_DIALOGID:
		{
			if(response)
			{
				switch(listitem)
				{
					case 0:
					{
						new str[1024];
						for(new i = 0; i < MAX_ENTRIES; i++)
						{
							if(i == 0) format(str, sizeof(str), "%d %s\n", Sounds[i][SOUND_ID], Sounds[i][SOUND_NAME]);
							else if(i != MAX_ENTRIES-1) format(str, sizeof(str), "%s%d %s\n", str, Sounds[i][SOUND_ID], Sounds[i][SOUND_NAME]);
							else strcat(str, "Next");
						}
						ShowPlayerDialog(playerid, BSP_LIST1_DIALOGID, DIALOG_STYLE_LIST, "All sounds (1/3)", str, "Choose", "Back");
					}
					case 1:
					{
						SendClientMessage(playerid, RED, "The search engine has been turned off. Please wait for the version 2 release.");
						ShowPlayerDialog(playerid, BSP_MENU_DIALOGID, DIALOG_STYLE_LIST, "SA:MP Soundz by BigETI", "Sounds (All)\nSearch\nCredits\nExit", "Choose", "Exit");
					}
					case 2: ShowPlayerDialog(playerid, BSP_CREDITS_DIALOGID, DIALOG_STYLE_MSGBOX, "Credits", "SA:MP Soundz V1 Filterscript made\nby BigETI.\nAll rights are reserved!", "Back", "");
				}
			}
		}
		case BSP_LIST1_DIALOGID:
		{
			if(response)
			{
				if(listitem == MAX_ENTRIES-1)
				{
					new str[1024];
					for(new i = 0; i < MAX_ENTRIES; i++)
					{
						if(i == 0) format(str, sizeof(str), "%d %s\n", Sounds[i+(MAX_ENTRIES-1)][SOUND_ID], Sounds[i+(MAX_ENTRIES-1)][SOUND_NAME]);
						else if(i != MAX_ENTRIES-1) format(str, sizeof(str), "%s%d %s\n", str, Sounds[i+(MAX_ENTRIES-1)][SOUND_ID], Sounds[i+(MAX_ENTRIES-1)][SOUND_NAME]);
						else strcat(str, "Next");
					}
					ShowPlayerDialog(playerid, BSP_LIST2_DIALOGID, DIALOG_STYLE_LIST, "All sounds (2/3)", str, "Choose", "Back");
				}
				else
				{
					PlayerPlaySound(playerid, Sounds[listitem][SOUND_ID], 0.0, 0.0, 0.0);
					new str[1024];
					for(new i = 0; i < MAX_ENTRIES; i++)
					{
						if(i == 0) format(str, sizeof(str), "%d %s\n", Sounds[i][SOUND_ID], Sounds[i][SOUND_NAME]);
						else if(i != MAX_ENTRIES-1) format(str, sizeof(str), "%s%d %s\n", str, Sounds[i][SOUND_ID], Sounds[i][SOUND_NAME]);
						else strcat(str, "Next");
					}
					ShowPlayerDialog(playerid, BSP_LIST1_DIALOGID, DIALOG_STYLE_LIST, "All sounds (1/3)", str, "Choose", "Back");
				}
			}
			else ShowPlayerDialog(playerid, BSP_MENU_DIALOGID, DIALOG_STYLE_LIST, "SA:MP Soundz by BigETI", "Sounds (All)\nSearch\nCredits\nExit", "Choose", "Exit");
		}
		case BSP_LIST2_DIALOGID:
		{
			if(response)
			{
				if(listitem == MAX_ENTRIES-1)
				{
					new str[1024];
					for(new i = 0; i < MAX_ENTRIES; i++)
					{
						if(i == 0) format(str, sizeof(str), "%d %s\n", Sounds[i+(MAX_ENTRIES+MAX_ENTRIES-2)][SOUND_ID], Sounds[i+(MAX_ENTRIES+MAX_ENTRIES-2)][SOUND_NAME]);
						else if(i != MAX_ENTRIES-1 && i+(MAX_ENTRIES+MAX_ENTRIES-2) < MAX_SOUNDS) format(str, sizeof(str), "%s%d %s\n", str, Sounds[i+(MAX_ENTRIES+MAX_ENTRIES-2)][SOUND_ID], Sounds[i+(MAX_ENTRIES+MAX_ENTRIES-2)][SOUND_NAME]);
						else
						{
							strcat(str, "Back");
							break;
						}
					}
					ShowPlayerDialog(playerid, BSP_LIST3_DIALOGID, DIALOG_STYLE_LIST, "All sounds (3/3)", str, "Choose", "Back");
				}
				else
				{
					PlayerPlaySound(playerid, Sounds[listitem+(MAX_ENTRIES-1)][SOUND_ID], 0.0, 0.0, 0.0);
					new str[1024];
					for(new i = 0; i < MAX_ENTRIES; i++)
					{
						if(i == 0) format(str, sizeof(str), "%d %s\n", Sounds[i+(MAX_ENTRIES-1)][SOUND_ID], Sounds[i+(MAX_ENTRIES-1)][SOUND_NAME]);
						else if(i != MAX_ENTRIES-1) format(str, sizeof(str), "%s%d %s\n", str, Sounds[i+(MAX_ENTRIES-1)][SOUND_ID], Sounds[i+(MAX_ENTRIES-1)][SOUND_NAME]);
						else strcat(str, "Next");
					}
					ShowPlayerDialog(playerid, BSP_LIST2_DIALOGID, DIALOG_STYLE_LIST, "All sounds (2/3)", str, "Choose", "Back");
				}
			}
			else
			{
				new str[1024];
				for(new i = 0; i < MAX_ENTRIES; i++)
				{
					if(i == 0) format(str, sizeof(str), "%d %s\n", Sounds[i][SOUND_ID], Sounds[i][SOUND_NAME]);
					else if(i != MAX_ENTRIES-1) format(str, sizeof(str), "%s%d %s\n", str, Sounds[i][SOUND_ID], Sounds[i][SOUND_NAME]);
					else strcat(str, "Next");
				}
				ShowPlayerDialog(playerid, BSP_LIST1_DIALOGID, DIALOG_STYLE_LIST, "All sounds (1/3)", str, "Choose", "Back");
			}
		}
		case BSP_LIST3_DIALOGID:
		{
		    if(response)
		    {
				if(listitem+(MAX_ENTRIES+MAX_ENTRIES-2) == MAX_SOUNDS)
				{
					new str[1024];
					for(new i = 0; i < MAX_ENTRIES; i++)
					{
						if(i == 0) format(str, sizeof(str), "%d %s\n", Sounds[i+(MAX_ENTRIES-1)][SOUND_ID], Sounds[i+(MAX_ENTRIES-1)][SOUND_NAME]);
						else if(i != MAX_ENTRIES-1) format(str, sizeof(str), "%s%d %s\n", str, Sounds[i+(MAX_ENTRIES-1)][SOUND_ID], Sounds[i+(MAX_ENTRIES-1)][SOUND_NAME]);
						else strcat(str, "Next");
					}
					ShowPlayerDialog(playerid, BSP_LIST2_DIALOGID, DIALOG_STYLE_LIST, "All sounds (2/3)", str, "Choose", "Back");
				}
				else
				{
					PlayerPlaySound(playerid, Sounds[listitem+(MAX_ENTRIES+MAX_ENTRIES-2)][SOUND_ID], 0.0, 0.0, 0.0);
					new str[1024];
					for(new i = 0; i < MAX_ENTRIES; i++)
					{
						if(i == 0) format(str, sizeof(str), "%d %s\n", Sounds[i+(MAX_ENTRIES+MAX_ENTRIES-2)][SOUND_ID], Sounds[i+(MAX_ENTRIES+MAX_ENTRIES-2)][SOUND_NAME]);
						else if(i != MAX_ENTRIES-1 && i+(MAX_ENTRIES+MAX_ENTRIES-2) < MAX_SOUNDS) format(str, sizeof(str), "%s%d %s\n", str, Sounds[i+(MAX_ENTRIES+MAX_ENTRIES-2)][SOUND_ID], Sounds[i+(MAX_ENTRIES+MAX_ENTRIES-2)][SOUND_NAME]);
						else
						{
							strcat(str, "Back");
							break;
						}
					}
					ShowPlayerDialog(playerid, BSP_LIST3_DIALOGID, DIALOG_STYLE_LIST, "All sounds (3/3)", str, "Choose", "Back");
				}
			}
			else
			{
				new str[1024];
				for(new i = 0; i < MAX_ENTRIES; i++)
				{
					if(i == 0) format(str, sizeof(str), "%d %s\n", Sounds[i+(MAX_ENTRIES-1)][SOUND_ID], Sounds[i+(MAX_ENTRIES-1)][SOUND_NAME]);
					else if(i != MAX_ENTRIES-1) format(str, sizeof(str), "%s%d %s\n", str, Sounds[i+(MAX_ENTRIES-1)][SOUND_ID], Sounds[i+(MAX_ENTRIES-1)][SOUND_NAME]);
					else strcat(str, "Next");
				}
				ShowPlayerDialog(playerid, BSP_LIST2_DIALOGID, DIALOG_STYLE_LIST, "All sounds (2/3)", str, "Choose", "Back");
			}
		}
		case BSP_CREDITS_DIALOGID: ShowPlayerDialog(playerid, BSP_MENU_DIALOGID, DIALOG_STYLE_LIST, "SA:MP Soundz by BigETI", "Sounds (All)\nSearch\nCredits\nExit", "Choose", "Exit");
	}
	return 1;
}