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
*/
#if defined _FILE_EX_REMOTE_DEF_INCLUDED_
	#endinput
#endif
#define _FILE_EX_REMOTE_DEF_INCLUDED_
#if defined _FILE_EX_INCLUDED_
	#if !defined FILE_EX_SCRIPT_ID
		#error	Please define "FILE_EX_SCRIPT_ID" with an unique ID to be indetified properly from all scripts.
	#endif
#endif
#if !defined FILE_EX_RES_CB_NAME
	#define FILE_EX_RES_CB_NAME	OnFileExError
#endif
#if !defined FILE_EX_RES_CB_NAME_STR
	#define FILE_EX_RES_CB_NAME_STR	"OnFileExError"
#endif
#if !defined _FILE_EX_INCLUDED_
enum f_ex_res_ENUM
{
	f_ex_res_OK,
	f_ex_res_INV_FILE_ACCESS,
	f_ex_res_INV_TEMP_FILE_ACCESS,
	f_ex_res_INV_FILE_S_PTR,
	f_ex_res_EOF
}
	#define F_EX_RES::	f_ex_res_
#endif