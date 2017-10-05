#if defined _SAMPSHELL_INC_
	#endinput
#endif
#define _SAMPSHELL_INC_
native Shell:SHELL_Execute(const cmd[]);
native SHELL_System(const cmd[]);
native bool:SHELL_IsActive(Shell:handle);
native SHELL_Release(Shell:handle);
native SHELL_ReleaseAll();
native SHELL_MEM_CleanUp();
forward OnReceiveShellMessage(Shell:handle, msg[]);
forward OnReleaseShell(Shell:handle);
#define SHELL::	SHELL_