/*
	FileEx (Extended file functions controlling and debugging script) made by BigETI © 2013
	
	file_ex.inc allows you to control and debug your scripts which uses file functions from file.inc
	Also by defining FILE_EX_ENABLE_REMOTE you allow your main script to send error messages to other scripts.



	- Links:
	==================================================
		- file_ex.inc:				http://pastebin.com/w3S4YYv2
		- file_ex_remote_def.inc:	http://pastebin.com/KNjpZkmP
		- file_ex_remote.inc		http://pastebin.com/Vsf3Wd8j
	==================================================



	- Documentation:

	==================================================

		- Callbacks:

			- public OnFileExError(script_id, F_EX_RES::ENUM:result_id, func_name[], File:file_handle, msg[])

				- Description:
					- Gets called, if an error occurs at another script, which uses file.inc.
					- Only usable, if the reporting script has remote error report enabled. ( FILE_EX_ENABLE_REMOTE )

				- Usage:
					public OnFileExError(script_id, F_EX_RES::ENUM:result_id, func_name[], File:file_handle, msg[])
					{
						// ...
					}

	==================================================
*/
#if defined _FILE_EX_REMOTE_INCLUDED_
	#endinput
#endif
#define _FILE_EX_REMOTE_INCLUDED_
#include <file>
#include <file_ex_remote_def>
forward FILE_EX_RES_CB_NAME(script_id, F_EX_RES::ENUM:result_id, func_name[], File:file_handle, msg[]);