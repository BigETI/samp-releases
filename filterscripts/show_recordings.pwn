#include <a_samp>
#include <list>

#define NO_RESPONSE_DIALOGID	(0)
#define LOAD_RECORDING_DIALOGID	(1000)
#define LIST_RECORDING_DIALOGID	(1001)

#if LOAD_RECORDING_DIALOGID == NO_RESPONSE_DIALOGID
	#error You are not allowed to define "LOAD_RECORDING_DIALOGID" equal "NO_RESPONSE_DIALOGID".
#endif

#define MAX_RECORDING_ROWS		(96)
#define NULL_PTR				(Pointer:0)

MEM::struct player_info
{
	player_info_time,
	player_info_skin_weapon,
	player_info_vehicle,
	Float:player_info_pos[4],
	Float:player_info_velocity[3],
	player_info_animation
}

new LIST::init<player_session[MAX_PLAYERS]>, Pointer:session_ptrs_arr[MAX_PLAYERS] = {NULL_PTR, ...}, listed_events[MAX_PLAYERS] = {0, ...};

stock ShowRecording(playerid, ListIt:list_it)
{
	MEM::free(session_ptrs_arr[playerid]);
	if((session_ptrs_arr[playerid] = MEM::calloc(MAX_RECORDING_ROWS)) == NULL_PTR)
	{
		LIST::clear(player_session[playerid]);
		SendClientMessage(playerid, 0xFF0000FF, "An unexpected error has occured.");
		return;
	}
	new title[20], dstr[2042] = "{FF7F00}More\n{7F7F7F}Exit";
	listed_events[playerid] = 0;
	for(new ListIt:t_list_it = list_it; _:t_list_it != LIST_NULL_; t_list_it = ListIt:MEM_EX::get_val(Pointer:(t_list_it)->LIST_IT_data_next))
	{
		if(listed_events[playerid] >= MAX_RECORDING_ROWS) break;
		if(LIST_IT::data_size(t_list_it) != player_info)
		{
			LIST::clear(player_session[playerid]);
			MEM::free(session_ptrs_arr[playerid]);
			session_ptrs_arr[playerid] = NULL_PTR;
			listed_events[playerid] = 0;
			SendClientMessage(playerid, 0xFF0000FF, "Corrupt recording file.");
			return;
		}
		MEM::set_val(session_ptrs_arr[playerid], listed_events[playerid]++, _:t_list_it);
		format(dstr, sizeof dstr, "%s\n%d ms later", dstr, MEM::get_val(LIST_IT::data_ptr(t_list_it), player_info_time));
	}
	if(listed_events[playerid] <= 0)
	{
		LIST::clear(player_session[playerid]);
		MEM::free(session_ptrs_arr[playerid]);
		session_ptrs_arr[playerid] = NULL_PTR;
		listed_events[playerid] = 0;
		SendClientMessage(playerid, 0xFF0000FF, "No more results found.");
		return;
	}
	format(title, sizeof title, "%d %s", listed_events[playerid], (listed_events[playerid] == 1)?("result"):("results"));
	ShowPlayerDialog(playerid, LIST_RECORDING_DIALOGID, DIALOG_STYLE_LIST, title, dstr, "Select", "Exit");
}

public OnFilterScriptInit()
{
	print("\n=================================");
	print("= Show recordings filter script =");
	print("=        Made by BigETI         =");
	print("=            Loaded!            =");
	print("=================================\n");
	return 1;
}

public OnFilterScriptExit()
{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		ShowPlayerDialog(i, -1, DIALOG_STYLE_MSGBOX, "", "", "", "");
		LIST::clear(player_session[i]);
		MEM::free(session_ptrs_arr[i]);
	}
	print("\n=================================");
	print("= Show recordings filter script =");
	print("=        Made by BigETI         =");
	print("=           Unloaded!           =");
	print("=================================\n");
	return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
	LIST::clear(player_session[playerid]);
	MEM::free(session_ptrs_arr[playerid]);
	session_ptrs_arr[playerid] = NULL_PTR;
	listed_events[playerid] = 0;
}

public OnPlayerCommandText(playerid, cmdtext[])
{
	if(!strcmp("/loadrecording", cmdtext, true, 14))
	{
		ShowPlayerDialog(playerid, LOAD_RECORDING_DIALOGID, DIALOG_STYLE_INPUT, "Load recording", "Copy and paste the recording file into this dialog.", "Load", "Exit");
		return 1;
	}
	return 0;
}

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch(dialogid)
	{
		case LOAD_RECORDING_DIALOGID:
		{
			if(!response) return 1;
			if(LIST::load(player_session[playerid], inputtext)) ShowRecording(playerid, LIST::begin(player_session[playerid]));
			else SendClientMessage(playerid, 0xFF0000FF, "Failed to load session file.");
		}
		case LIST_RECORDING_DIALOGID:
		{
			if(!response)
			{
				LIST::clear(player_session[playerid]);
				MEM::free(session_ptrs_arr[playerid]);
				session_ptrs_arr[playerid] = NULL_PTR;
				listed_events[playerid] = 0;
				SendClientMessage(playerid, 0xFF0000FF, "You have left the dialog.");
				return 1;
			}
		    switch(listitem)
		    {
			    case 0:
			    {
					new ListIt:last_it = ListIt:MEM::get_val(session_ptrs_arr[playerid], listed_events[playerid]-1);
					if(_:last_it == LIST_NULL_ || last_it == LIST::end(player_session[playerid]))
					{
						LIST::clear(player_session[playerid]);
						MEM::free(session_ptrs_arr[playerid]);
						session_ptrs_arr[playerid] = NULL_PTR;
						listed_events[playerid] = 0;
						SendClientMessage(playerid, 0xFF0000FF, "No more results found.");
						return 1;
					}
					ShowRecording(playerid, LIST_IT::next(last_it));
			    }
			    case 1:
			    {
					LIST::clear(player_session[playerid]);
					MEM::free(session_ptrs_arr[playerid]);
					session_ptrs_arr[playerid] = NULL_PTR;
					listed_events[playerid] = 0;
					SendClientMessage(playerid, 0xFF0000FF, "You have left the dialog.");
				}
			    default:
			    {
					if(listitem < listed_events[playerid]+2)
					{
						new buffer[player_info], anim[2][32], title[21], dstr[332];
						MEM::get_arr(LIST_IT::data_ptr(ListIt:MEM::get_val(session_ptrs_arr[playerid], listitem-2)), _, buffer);
						GetAnimationName(buffer[player_info_animation], anim[0], sizeof anim[], anim[1], sizeof anim[]);
						format(dstr, sizeof dstr, "Time after recording: %d\n\nSkin ID: %d\nHolding Weapon ID: %d\nAnimation: %s %s ( ID: %d )", buffer[player_info_time], buffer[player_info_skin_weapon]&0xFFFF, (buffer[player_info_skin_weapon]>>>16)&0xFFFF, anim[0], anim[1], buffer[player_info_animation]);
						if(buffer[player_info_vehicle]&0xFFFF) format(dstr, sizeof dstr, "%s\n\nVehicle Model: %d\nVehicle Seat ID: %d", dstr, buffer[player_info_vehicle]&0xFFFF, (buffer[player_info_vehicle]>>>16)&0xFFFF);
						else strcat(dstr, "\n\nNo Vehicle");
						format(dstr, sizeof dstr, "%s\n\n\nX: %.6f\nY: %.6f\nZ: %.6f\nRotZ: %.6f\n\nVelX: %.6f\nVelY: %.6f\nVelZ: %.6f", dstr, buffer[player_info_pos][0], buffer[player_info_pos][1], buffer[player_info_pos][2], buffer[player_info_pos][3], buffer[player_info_velocity][0], buffer[player_info_velocity][1], buffer[player_info_velocity][2]);
						format(title, sizeof title, "%d ms later", buffer[player_info_time]);
						ShowPlayerDialog(playerid, NO_RESPONSE_DIALOGID, DIALOG_STYLE_MSGBOX, title, dstr, "OK", "");
					}
					LIST::clear(player_session[playerid]);
					MEM::free(session_ptrs_arr[playerid]);
					session_ptrs_arr[playerid] = NULL_PTR;
					listed_events[playerid] = 0;
				}
			}
		}
	}
	return 1;
}