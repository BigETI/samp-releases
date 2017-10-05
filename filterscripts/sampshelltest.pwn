#include <a_samp>
#include <sampshell>

new Shell:PlayerShell[MAX_PLAYERS];

main()
{
	print("");
	print("/===========================\\");
	print("| SA:MP Shell Test started! |");
	print("\\===========================/\n");
}

public OnGameModeInit()
{
	SetGameModeText("SA:MP Shell Test");
	AddPlayerClass(0, 1958.3783, 1343.1572, 15.3746, 269.1425, 0, 0, 0, 0, 0, 0);
	return 1;
}

public OnGameModeExit()
{
	SHELL::ReleaseAll();
	return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
	if(PlayerShell[playerid])
	{
		SHELL::Release(PlayerShell[playerid]);
		PlayerShell[playerid] = Shell:0;
	}
}

public OnPlayerRequestClass(playerid, classid)
{
	SetPlayerPos(playerid, 1958.3783, 1343.1572, 15.3746);
	SetPlayerCameraPos(playerid, 1958.3783, 1343.1572, 15.3746);
	SetPlayerCameraLookAt(playerid, 1958.3783, 1343.1572, 15.3746);
	return 1;
}

public OnPlayerText(playerid, text[])
{
	return 1;
}

public OnPlayerCommandText(playerid, cmdtext[])
{
	if(!strcmp(cmdtext, "/shell", true, 6))
	{
		if(SHELL::IsActive(PlayerShell[playerid])) SendClientMessage(playerid, 0xFF0000FF, "Wait for the shell to proceed...");
		else
		{
			if(strlen(cmdtext) > 7)
			{
				PlayerShell[playerid] = SHELL::Execute(cmdtext[7]);
				SendClientMessage(playerid, 0x00FFFFFF, "Shell command executed!");
			}
			else SendClientMessage(playerid, 0xFF0000FF, "Usage: \"/shell <command>\"");
		}
		return 1;
	}
	else if(!strcmp(cmdtext, "/release", true, 5))
	{
		SHELL::Release(PlayerShell[playerid]);
		return 1;
	}
	else if(!strcmp(cmdtext, "/system", true, 7))
	{
		if(strlen(cmdtext) > 8) SHELL::System(cmdtext[8]);
		else SendClientMessage(playerid, 0xFF0000FF, "Usage: \"/system <command>\"");
		return 1;
	}
	return 0;
}

public OnReceiveShellMessage(Shell:handle, msg[])
{
	printf("Shell handle: 0x%x", _:handle);
	print(msg);
	//SendClientMessageToAll(0xFF0000FF, msg);
}

public OnReleaseShell(Shell:handle)
{
	printf("Shell handle 0x%x released!", _:handle);
}