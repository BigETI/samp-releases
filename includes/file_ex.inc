/*
	FileEx (Extended file functions controlling and debugging script) made by BigETI © 2013
	
	This include allows you to control and debug your scripts which uses file functions from file.inc
	Also by defining FILE_EX_ENABLE_REMOTE you allow your main script to send error messages to other scripts.


	
	- Links:
	==================================================
		- file_ex.inc:				http://pastebin.com/w3S4YYv2
		- file_ex_remote_def.inc:	http://pastebin.com/KNjpZkmP
		- file_ex_remote.inc		http://pastebin.com/Vsf3Wd8j
	==================================================



	- Documentation:

	==================================================

		- Definitions ( Those definitions below, if needed have to be defined on top of your script, above #include <file_ex> )

			-------------------------
			- FILE_EX_NO_TRACKING

				- Description:
					- Disables all tracking features of this include.
					- It makes result feedback and debugging useless.

				- Usage:
					- #define FILE_EX_NO_TRACKING

			-------------------------
			- FILE_EX_DEBUG_LEVEL

				- Description:
					- Defines the current debug level your script should debug the file functions.
					- Useless, if defined FILE_EX_NO_TRACKING.

				- Levels:
					- Level 0 (Default):
						- Nothing will be debugged!

					- Level 1:
						- Functions like fopen, ftemp, fclose, fremove will be debugged.

					- Level 2:
						- All other file functions will be debugged, also the ones from level 1.

					- Level 3 and above:
						- Prints fwrite, fread, fputchar, fgetchar, fblockwrite, fblockread, fseek, fexist, and flenght inputs and outputs.
						- Also does the same as level 2 and level 1.

				- Usage:
					- Example: #define FILE_EX_DEBUG_LEVEL	1

			-------------------------
			- FILE_EX_ENABLE_REMOTE

				- Description:
					- Error reports will be send to other scripts.
					- If needed use atleast a script with file_ex_remote.inc included
					- Define FILE_EX_SCRIPT_ID with an unique ID to identify your script from your other scripts!

				- Usage:
					- #define FILE_EX_ENABLE_REMOTE

			-------------------------
			- FILE_EX_SCRIPT_ID

				- Description:
					- Gives your script an unique ID to be indentified from other scripts

				- Usage:
					- Example:
						- #define FILE_EX_SCRIPT_ID	5

			-------------------------
			- FILE_EX_FGETCHAR_FIX

				- Description:
					- Fixes the native fgetchar's arguments.
					- Removes the second useless argument.
					- fgetchar(File:handle, bool:utf8 = true) instead of fgetchar(File:handle, value, bool:utf8 = true)
					- Do not use this, if you get compatiblitiy issues with your script.

				- Usage
					- #define FILE_EX_FGETCHAR_FIX

			-------------------------


		- Macros:
		
			-------------------------
			- F_EX::file_read(const file_name[])<variable_name>
			
				- Description:
					- Handles a file stream safely inside brackets.
					- Read only mode!
					- Much easier to open and close files.
					- It does not require fclose inside, hence DO NOT USE THIS IN THIS CASE!
					- Supports all file stream modes from file.inc
					- "variable_name" defines the variable, which will hold the file stream handle.
					- A variable in "variable_name" will be declared inside this macro, so do not declare a variable for this!

				- Usage:
					- Example:
						F_EX::file_read("example.txt")<example_txt_handle>
						{
							new buffer[128];
							fread(example_txt_handle, buffer);
							print(buffer);
						}


			-------------------------
			- F_EX::file_write(const file_name[])<variable_name>

				- Description:
					- Handles a file stream safely inside brackets.
					- Write only mode!
					- Much easier to open and close files.
					- It does not require fclose inside, hence DO NOT USE THIS IN THIS CASE!
					- Supports all file stream modes from file.inc
					- "variable_name" defines the variable, which will hold the file stream handle.
					- A variable in "variable_name" will be declared inside this macro, so do not declare a variable for this!

				- Usage:
					- Example:
						F_EX::file_write("example.txt")<example_txt_handle>
						{
							fwrite(example_txt_handle, "Hello world!\r\n");
						}
			
			-------------------------
			- F_EX::file_readwrite(const file_name[])<variable_name>

				- Description:
					- Handles a file stream safely inside brackets.
					- Read and write mode.
					- Much easier to open and close files.
					- It does not require fclose inside, hence DO NOT USE THIS IN THIS CASE!
					- Supports all file stream modes from file.inc
					- "variable_name" defines the variable, which will hold the file stream handle.
					- A variable in "variable_name" will be declared inside this macro, so do not declare a variable for this!

				- Usage:
					- Example:
						F_EX::file_readwrite("example.txt")<example_txt_handle>
						{
							fwrite(example_txt_handle, "Hello world!\r\n");
							new buffer[128];
							fread(example_txt_handle, buffer);
							print(buffer);
						}
			
			-------------------------
			- F_EX::file_append(const file_name[])<variable_name>

				- Description:
					- Handles a file stream safely inside brackets.
					- Append only mode!
					- Much easier to open and close files.
					- It does not require fclose inside, hence DO NOT USE THIS IN THIS CASE!
					- Supports all file stream modes from file.inc
					- "variable_name" defines the variable, which will hold the file stream handle.
					- A variable in "variable_name" will be declared inside this macro, so do not declare a variable for this!

				- Usage:
					- Example:
						F_EX::file_append("example.txt")<example_txt_handle>
						{
							fwrite(example_txt_handle, "Hello world!\r\n");
						}
			
			-------------------------
			- F_EX::temp_file<variable_name>

				- Description:
					- Handles a temporary file stream safely inside brackets.
					- Much easier to open and close temporary files.
					- It does not require fclose inside, hence DO NOT USE THIS IN THIS CASE!
					- Supports all file stream modes from file.inc
					- "variable_name" defines the variable, which will hold the file stream handle.
					- A variable in "variable_name" will be declared inside this macro, so do not declare a variable for this!

				- Usage:
					- Example:
						F_EX::temp_file<temp_file_handle>
						{
							new buffer = EOF;
							F:EX::open_read("example.txt", example_txt_handle) while((buffer = fgetchar(example_txt_handle, 0, false)) != EOF) fputchar(temp_file_handle, false);
							fseek(temp_file_handle);
							F:EX::open_write("example2.txt", example2_txt_handle)
							{
								buffer = EOF;
								while((buffer = fgetchar(temp_file_handle, 0, false)) != EOF) fputchar(example2_txt_handle, false);
							}
						}

			-------------------------


		- Enums:

			-------------------------
			- F_EX_RES::ENUM

				- Description:
					- Used to identify specified results as numbers.

				- Items:
					- F_EX_RES::OK
						- Result is okay.

					- F_EX_RES::INV_FILE_ACCESS
						- Result shows an invalid file access.

					- F_EX_RES::INV_TEMP_FILE_ACCESS
						- Result shows an invalid temporary file access.

					- F_EX_RES::INV_FILE_S_PTR
						- Result shows an invalid file pointer access.

					- F_EX_RES::EOF
						- Result shows that the end of a file has been reached.

			-------------------------


		- Stocks:

			-------------------------
			- stock F_EX_RES::ENUM: F_EX::get_result(bool:keep_result = true)

				- Description:
					- Gets the last result ID.
					- If bool:keep_result is true it will not reset the last result.
					- Useless, if defined FILE_EX_NO_TRACKING.

				- Usage:
					- Example:
						F_EX::fopen_read("example.txt", my_file)
						{
							print("Current result: %d", _:F_EX::get_result();
						}
						
			-------------------------
			- stock F_EX::print_result(bool:ignore_ok = true, bool:keep_result = true)

				- Description:
					- Prints the last result properly into the console.
					- Does not print in OK results, if bool:ignore_ok is set to true.
					- If bool:keep_result is true it will not reset the last result.
					- Useless, if defined FILE_EX_NO_TRACKING.

				- Usage:
					- Example:
						F_EX::fopen_read("example.txt", my_file)
						{
							F_EX::print_result(false);
						}

			-------------------------


		- Hooked natives (without defining FILE_EX_NO_TRACKING):

			- native File:fopen(const name[], filemode: mode = io_readwrite);
			- native bool:fclose(File: handle);
			- native File:ftemp();
			- native bool:fremove(const name[]);
			- native fwrite(File: handle, const string[]);
			- native fread(File: handle, string[], size = sizeof string, bool: pack = false);
			- native bool:fputchar(File: handle, value, bool: utf8 = true);
			- native fgetchar(File: handle, value, bool: utf8 = true);
			- native fblockwrite(File: handle, const buffer[], size = sizeof buffer);
			- native fblockread(File: handle, buffer[], size = sizeof buffer);
			- native fseek(File: handle, position = 0, seek_whence: whence = seek_start);
			- native flength(File: handle);
			- native fexist(const pattern[]);

	==================================================
*/

#if defined _FILE_EX_INCLUDED_
	#endinput
#endif
#define _FILE_EX_INCLUDED_
#if defined FILE_EX_NO_TRACKING
	#include <file>
	#define f_ex_inc_file_read%2(%0)%3<%1>		for(new File:%1=fopen(%0,io_read),bool:_%1__=true;_%1__;_%1__=(((%1) == File:0)?false:(fclose(%1)?false:false)))
	#define f_ex_inc_file_write%2(%0)%3<%1>		for(new File:%1=fopen(%0,io_write),bool:_%1__=true;_%1__;_%1__=(((%1) == File:0)?false:(fclose(%1)?false:false)))
	#define f_ex_inc_file_readwrite%2(%0)%3<%1>	for(new File:%1=fopen(%0,io_readwrite),bool:_%1__=true;_%1__;_%1__=(((%1) == File:0)?false:(fclose(%1)?false:false)))
	#define f_ex_inc_file_append%2(%0)%3<%1>	for(new File:%1=fopen(%0,io_append),bool:_%1__=true;_%1__;_%1__=(((%1) == File:0)?false:(fclose(%1)?false:false)))
	#define f_ex_inc_temp_file%1<%0>			for(new File:%0=ftemp(),bool:_%0__=true;_%0__;_%0__=(((%0) == File:0)?false:(fclose(%0)?false:false)))
#else
	#if defined FILE_EX_ENABLE_REMOTE
		#include <a_samp>
		#include <file_ex_remote_def>
	#else
		#include <file>
	#endif
	#if !defined FILE_EX_DEBUG_LEVEL
		#define FILE_EX_DEBUG_LEVEL	0
	#endif
enum f_ex_res_ENUM
{
	f_ex_res_OK,
	f_ex_res_INV_FILE_ACCESS,
	f_ex_res_INV_TEMP_FILE_ACCESS,
	f_ex_res_INV_FILE_S_PTR,
	f_ex_res_EOF
}
new f_ex_res_ENUM:g_f_ex_res = f_ex_res_OK, g_f_ex_res_descr[128] = "";
	#define f_ex_inc_file_read%2(%0)%3<%1>		for(new File:%1=fopen(%0,io_read),bool:_%1__=true;_%1__;_%1__=(fclose(%1)?false:false))
	#define f_ex_inc_file_write%2(%0)%3<%1>		for(new File:%1=fopen(%0,io_write),bool:_%1__=true;_%1__;_%1__=(fclose(%1)?false:false))
	#define f_ex_inc_file_readwrite%2(%0)%3<%1>	for(new File:%1=fopen(%0,io_readwrite),bool:_%1__=true;_%1__;_%1__=(fclose(%1)?false:false))
	#define f_ex_inc_file_append%2(%0)%3<%1>	for(new File:%1=fopen(%0,io_append),bool:_%1__=true;_%1__;_%1__=(fclose(%1)?false:false))
	#define f_ex_inc_temp_file%1<%0>			for(new File:%0=ftemp(),bool:_%0__=true;_%0__;_%0__=(fclose(%0)?false:false))
stock File:f_ex_hook_fopen(const name[], filemode:mode = io_readwrite)
{
	new File:f_ex_debug_var = fopen(name, mode);
	if(f_ex_debug_var)
	{
		g_f_ex_res = f_ex_res_OK;
	#if FILE_EX_DEBUG_LEVEL > 2
		printf(" [DEBUG] <file_ex.inc> fopen() -> Successfully created file stream ( File:%d )", _:f_ex_debug_var);
	#endif
		return f_ex_debug_var;
	}
	format(g_f_ex_res_descr, sizeof(g_f_ex_res_descr), name);
	g_f_ex_res = f_ex_res_INV_FILE_ACCESS;
	#if FILE_EX_DEBUG_LEVEL > 0
	if(mode == io_read) printf("[DEBUG] <file_ex.inc> fopen() -> Failed to open file \"%s\"", name);
	else printf(" [DEBUG] <file_ex.inc> fopen() -> Failed to open or create file \"%s\"", name);
	#endif
	#if defined FILE_EX_ENABLE_REMOTE
	CallRemoteFunction(FILE_EX_RES_CB_NAME_STR, "ddsds", FILE_EX_SCRIPT_ID, _:f_ex_res_INV_FILE_ACCESS, "fopen", 0, name);
	#endif
	return File:0;
}
	#if defined _ALS_fopen
		#undef fopen
	#else
		#define _ALS_fopen
	#endif
	#define fopen	f_ex_hook_fopen
stock bool:f_ex_hook_fclose(File:handle)
{
	if(handle == File:0)
	{
		g_f_ex_res_descr[0] = 0;
		g_f_ex_res = f_ex_res_INV_FILE_S_PTR;
	#if FILE_EX_DEBUG_LEVEL > 0
		print(" [DEBUG] <file_ex.inc> fclose() -> Attempted to destroy a file stream with a NULL pointer ( File:0 )");
	#endif
	#if defined FILE_EX_ENABLE_REMOTE
		CallRemoteFunction(FILE_EX_RES_CB_NAME_STR, "ddsds", FILE_EX_SCRIPT_ID, _:f_ex_res_INV_FILE_S_PTR, "fclose", 0, " ");
	#endif
		return false;
	}
	if(fclose(handle))
	{
		g_f_ex_res = f_ex_res_OK;
		#if FILE_EX_DEBUG_LEVEL > 2
		printf(" [DEBUG] <file_ex.inc> fclose() -> Successfully destroyed file stream ( File:%d )", _:handle);
		#endif
		return true;
	}
	g_f_ex_res_descr[0] = _:handle;
	g_f_ex_res = f_ex_res_INV_FILE_S_PTR;
	#if FILE_EX_DEBUG_LEVEL > 0
	printf(" [DEBUG] <file_ex.inc> fclose() -> Attempted to destroy an invalid file stream ( File:%d )", _:handle);
	#endif
	#if defined FILE_EX_ENABLE_REMOTE
	CallRemoteFunction(FILE_EX_RES_CB_NAME_STR, "ddsds", FILE_EX_SCRIPT_ID, _:f_ex_res_INV_FILE_S_PTR, "fclose", _:handle, " ");
	#endif
	return false;
}
	#if defined _ALS_fclose
		#undef fclose
	#else
		#define _ALS_fclose
	#endif
	#define fclose	f_ex_hook_fclose
stock File:f_ex_hook_ftemp()
{
	new File:f_ex_debug_var = ftemp();
	if(f_ex_debug_var)
	{
		g_f_ex_res = f_ex_res_OK;
	#if FILE_EX_DEBUG_LEVEL > 2
		printf(" [DEBUG] <file_ex.inc> ftemp() -> Successfully created temporary file stream ( File:%d )", _:f_ex_debug_var);
	#endif
		return f_ex_debug_var;
	}
	g_f_ex_res_descr[0] = '\0';
	g_f_ex_res = f_ex_res_INV_TEMP_FILE_ACCESS;
	#if FILE_EX_DEBUG_LEVEL > 0
	print(" [DEBUG] <file_ex.inc> ftemp() -> Failed to create a temporary file stream");
	#endif
	#if defined FILE_EX_ENABLE_REMOTE
	CallRemoteFunction(FILE_EX_RES_CB_NAME_STR, "ddsds", FILE_EX_SCRIPT_ID, _:f_ex_res_INV_TEMP_FILE_ACCESS, "ftemp", 0, "Temporary file");
	#endif
	return File:0;
}
	#if defined _ALS_ftemp
		#undef ftemp
	#else
		#define _ALS_ftemp
	#endif
	#define ftemp	f_ex_hook_ftemp
stock bool:f_ex_hook_fremove(const name[])
{
	if(fremove(name))
	{
		g_f_ex_res = f_ex_res_OK;
	#if FILE_EX_DEBUG_LEVEL > 2
		printf(" [DEBUG] <file_ex.inc> fremove() -> Successfully removed file \"%s\"", name);
	#endif
		return true;
	}
	format(g_f_ex_res_descr, sizeof(g_f_ex_res_descr), name);
	g_f_ex_res = f_ex_res_INV_FILE_ACCESS;
	#if FILE_EX_DEBUG_LEVEL > 0
	printf(" [DEBUG] <file_ex.inc> fremove() -> Failed to remove file \"%s\"", name);
	#endif
	#if defined FILE_EX_ENABLE_REMOTE
	CallRemoteFunction(FILE_EX_RES_CB_NAME_STR, "ddsds", FILE_EX_SCRIPT_ID, _:f_ex_res_INV_FILE_ACCESS, "fremove", 0, name);
	#endif
	return false;
}
	#if defined _ALS_fremove
		#undef fremove
	#else
		#define _ALS_fremove
	#endif
	#define fremove	f_ex_hook_fremove
stock f_ex_hook_fwrite(File:handle, const string[])
{
	if(handle)
	{
	#if FILE_EX_DEBUG_LEVEL > 2
		printf(" [DEBUG] <file_ex.inc> fwrite() -> ( File:%d ) %s", _:handle, string);
	#endif
		return fwrite(handle, string);
	}
	g_f_ex_res_descr[0] = 0;
	g_f_ex_res = f_ex_res_INV_FILE_S_PTR;
	#if FILE_EX_DEBUG_LEVEL > 1
	print(" [DEBUG] <file_ex.inc> fwrite() -> Attempted to write into file stream ( File:0 )");
	#endif
	#if defined FILE_EX_ENABLE_REMOTE
	CallRemoteFunction(FILE_EX_RES_CB_NAME_STR, "ddsds", FILE_EX_SCRIPT_ID, _:f_ex_res_INV_FILE_S_PTR, "fwrite", 0, string);
	#endif
	return 0;
}
	#if defined _ALS_fwrite
		#undef fwrite
	#else
		#define _ALS_fwrite
	#endif
	#define fwrite	f_ex_hook_fwrite
stock f_ex_hook_fread(File:handle, string[], size = sizeof string, bool:pack = false)
{
	if(handle == File:0)
	{
		g_f_ex_res_descr[0] = 0;
		g_f_ex_res = f_ex_res_INV_FILE_S_PTR;
	#if FILE_EX_DEBUG_LEVEL > 1
		print(" [DEBUG] <file_ex.inc> fread() -> Attempted to read from file stream ( File:0 )");
	#endif
	#if defined FILE_EX_ENABLE_REMOTE
		CallRemoteFunction(FILE_EX_RES_CB_NAME_STR, "ddsds", FILE_EX_SCRIPT_ID, _:f_ex_res_INV_FILE_S_PTR, "fread", 0, " ");
	#endif
		return 0;
	}
	new f_ex_num_read = fread(handle, string, size, pack);
	#if FILE_EX_DEBUG_LEVEL > 2
		printf(" [DEBUG] <file_ex.inc> fread() -> ( File:%d | Pack = %d) %s", _:handle, _:pack, string);
	#endif
	if(f_ex_num_read == 0)
	{
		g_f_ex_res_descr[0] = _:handle;
		g_f_ex_res = f_ex_res_EOF;
	#if FILE_EX_DEBUG_LEVEL > 1
		printf(" [DEBUG] <file_ex.inc> fread() -> Reached the end of file ( File:%d )", _:handle);
	#endif
	#if defined FILE_EX_ENABLE_REMOTE
		CallRemoteFunction(FILE_EX_RES_CB_NAME_STR, "ddsds", FILE_EX_SCRIPT_ID, _:f_ex_res_EOF, "fread", _:handle, " ");
	#endif
		return 0;
	}
	return f_ex_num_read;
}
	#if defined _ALS_fread
		#undef fread
	#else
		#define _ALS_fread
	#endif
	#define fread	f_ex_hook_fread
stock bool:f_ex_hook_fputchar(File:handle, value, bool:utf8 = true)
{
	if(handle)
	{
	#if FILE_EX_DEBUG_LEVEL > 2
		printf(" [DEBUG] <file_ex.inc> fputchar() -> ( File:%d | UTF8 = %d )  %c", _:handle, _:utf8, value);
	#endif
		return fputchar(handle, value, utf8);
	}
	g_f_ex_res_descr[0] = 0;
	g_f_ex_res = f_ex_res_INV_FILE_S_PTR;
	#if FILE_EX_DEBUG_LEVEL > 1
	print(" [DEBUG] <file_ex.inc> fputchar() -> Attempted to write into file stream ( File:0 )");
	#endif
	#if defined FILE_EX_ENABLE_REMOTE
	new f_ex_str[2] = {'\0', '\0'};
	f_ex_str[0] = value;
	CallRemoteFunction(FILE_EX_RES_CB_NAME_STR, "ddsds", FILE_EX_SCRIPT_ID, _:f_ex_res_INV_FILE_S_PTR, "fputchar", 0, f_ex_str);
	#endif
	return false;
}
	#if defined _ALS_fputchar
		#undef fputchar
	#else
		#define _ALS_fputchar
	#endif
	#define fputchar	f_ex_hook_fputchar

	#if defined	FILE_EX_FGETCHAR_FIX
stock f_ex_hook_fgetchar(File:handle, bool:utf8 = true)
	#else
stock f_ex_hook_fgetchar(File:handle, value, bool:utf8 = true)
	#endif
{
	if(handle == File:0)
	{
		g_f_ex_res_descr[0] = 0;
		g_f_ex_res = f_ex_res_INV_FILE_S_PTR;
	#if FILE_EX_DEBUG_LEVEL > 1
		print(" [DEBUG] <file_ex.inc> fgetchar() -> Attempted to read from file stream ( File:0 )");
	#endif
	#if defined FILE_EX_ENABLE_REMOTE
		CallRemoteFunction(FILE_EX_RES_CB_NAME_STR, "ddsds", FILE_EX_SCRIPT_ID, _:f_ex_res_INV_FILE_S_PTR, "fgetchar", 0, " ");
	#endif
		return 0;
	}
	#if FILE_EX_DEBUG_LEVEL > 2
	printf(" [DEBUG] <file_ex.inc> fgetchar() -> ( File:%d | UTF8 = %d) %c", _:handle, _:utf8, value);
	#endif
	#if defined	FILE_EX_FGETCHAR_FIX
	new f_ex_getchar = fgetchar(handle, 0, utf8);
	#else
	new f_ex_getchar = fgetchar(handle, value, utf8);
	#endif
	if(f_ex_getchar == EOF)
	{
		g_f_ex_res_descr[0] = _:handle;
		g_f_ex_res = f_ex_res_EOF;
	#if FILE_EX_DEBUG_LEVEL > 1
		printf(" [DEBUG] <file_ex.inc> fgetchar() -> Reached the end of file ( File:%d )", _:handle);
	#endif
	#if defined FILE_EX_ENABLE_REMOTE
		CallRemoteFunction(FILE_EX_RES_CB_NAME_STR, "ddsds", FILE_EX_SCRIPT_ID, _:f_ex_res_EOF, "fgetchar", _:handle, " ");
	#endif
		return EOF;
	}
	return f_ex_getchar;
}
	#if defined _ALS_fgetchar
		#undef fgetchar
	#else
		#define _ALS_fgetchar
	#endif
	#define fgetchar	f_ex_hook_fgetchar
stock f_ex_hook_fblockwrite(File:handle, const buffer[], size = sizeof buffer)
{
	if(handle)
	{
	#if FILE_EX_DEBUG_LEVEL > 2
		printf(" [DEBUG] <file_ex.inc> fblockwrite() -> ( File:%d | size = %d)", _:handle, size);
		for(new f_ex_it_i = 0; f_ex_it_i > size; f_ex_it_i++) {printf(" [DEBUG] <file_ex.inc> fblockwrite() -> ( File:%d | Pos = %d | Value = %x | %d )", _:handle, f_ex_it_i, buffer[f_ex_it_i], buffer[f_ex_it_i]);}
	#endif
		return fblockwrite(handle, buffer, size);
	}
	g_f_ex_res_descr[0] = 0;
	g_f_ex_res = f_ex_res_INV_FILE_S_PTR;
	#if FILE_EX_DEBUG_LEVEL > 1
	print(" [DEBUG] <file_ex.inc> fblockwrite() -> Attempted to write to file stream ( File:0 )");
	#endif
	#if defined FILE_EX_ENABLE_REMOTE
	CallRemoteFunction(FILE_EX_RES_CB_NAME_STR, "ddsds", FILE_EX_SCRIPT_ID, _:f_ex_res_INV_FILE_S_PTR, "fblockwrite", 0, " ");
	#endif
	return 0;
}
	#if defined _ALS_fblockwrite
		#undef fblockwrite
	#else
		#define _ALS_fblockwrite
	#endif
	#define fblockwrite	f_ex_hook_fblockwrite
stock f_ex_hook_fblockread(File:handle, buffer[], size = sizeof buffer)
{
	if(handle == File:0)
	{
		g_f_ex_res_descr[0] = 0;
		g_f_ex_res = f_ex_res_INV_FILE_S_PTR;
	#if FILE_EX_DEBUG_LEVEL > 1
		print(" [DEBUG] <file_ex.inc> fblockread() -> Attempted to read from file stream ( File:0 )");
	#endif
	#if defined FILE_EX_ENABLE_REMOTE
		CallRemoteFunction(FILE_EX_RES_CB_NAME_STR, "ddsds", FILE_EX_SCRIPT_ID, _:f_ex_res_INV_FILE_S_PTR, "fblockread", 0, " ");
	#endif
		return 0;
	}
	new f_ex_num_cells = fblockread(handle, buffer, size);
	#if FILE_EX_DEBUG_LEVEL > 2
	printf(" [DEBUG] <file_ex.inc> fblockread() -> ( File:%d | size = %d)", _:handle, size);
	for(new f_ex_it_i = 0; f_ex_it_i > size; f_ex_it_i++) {printf(" [DEBUG] <file_ex.inc> fblockread() -> ( File:%d | Pos = %d | Value = %x | %d )", _:handle, f_ex_it_i, buffer[f_ex_it_i], buffer[f_ex_it_i]);}
	#endif
	if(f_ex_num_cells == size)
	{
		g_f_ex_res = f_ex_res_OK;
		return f_ex_num_cells;
	}
	#if FILE_EX_DEBUG_LEVEL > 1
		printf(" [DEBUG] <file_ex.inc> fblockread() -> Reached the end of file ( File:%d )", _:handle);
	#endif
	#if defined FILE_EX_ENABLE_REMOTE
		CallRemoteFunction(FILE_EX_RES_CB_NAME_STR, "ddsds", FILE_EX_SCRIPT_ID, _:f_ex_res_EOF, "fblockread", _:handle, " ");
	#endif
	return f_ex_num_cells;
}
	#if defined _ALS_fblockread
		#undef fblockread
	#else
		#define _ALS_fblockread
	#endif
	#define fblockread	f_ex_hook_fblockread
stock f_ex_hook_fseek(File:handle, position = 0, seek_whence:whence = seek_start)
{
	if(handle == File:0)
	{
		g_f_ex_res_descr[0] = 0;
		g_f_ex_res = f_ex_res_INV_FILE_S_PTR;
	#if FILE_EX_DEBUG_LEVEL > 1
		print(" [DEBUG] <file_ex.inc> fseek() -> Attempted to read from file stream ( File:0 )");
	#endif
	#if defined FILE_EX_ENABLE_REMOTE
		CallRemoteFunction(FILE_EX_RES_CB_NAME_STR, "ddsds", FILE_EX_SCRIPT_ID, _:f_ex_res_INV_FILE_S_PTR, "fseek", 0, " ");
	#endif
		return 0;
	}
	#if FILE_EX_DEBUG_LEVEL > 2
	new f_ex_fseek_ret = fseek(handle, position, whence);
	printf(" [DEBUG] <file_ex.inc> fseek() -> ( File:%d | Move to pos = %d | seek_whence:%d | File pos = %d)", _:handle, position, _:whence, f_ex_fseek_ret);
	return f_ex_fseek_ret;
	#else
	return fseek(handle, position, whence);
	#endif
}
	#if defined _ALS_fseek
		#undef fseek
	#else
		#define _ALS_fseek
	#endif
	#define fseek	f_ex_hook_fseek
stock f_ex_hook_flength(File:handle)
{
	if(handle == File:0)
	{
		g_f_ex_res_descr[0] = 0;
		g_f_ex_res = f_ex_res_INV_FILE_S_PTR;
	#if FILE_EX_DEBUG_LEVEL > 1
		print(" [DEBUG] <file_ex.inc> flength() -> Attempted to read from file stream ( File:0 )");
	#endif
	#if defined FILE_EX_ENABLE_REMOTE
		CallRemoteFunction(FILE_EX_RES_CB_NAME_STR, "ddsds", FILE_EX_SCRIPT_ID, _:f_ex_res_INV_FILE_S_PTR, "flength", 0, " ");
	#endif
		return 0;
	}
	#if FILE_EX_DEBUG_LEVEL > 2
	new f_ex_flength_ret = flength(handle);
	printf(" [DEBUG] <file_ex.inc> flength() -> ( File:%d | Size = %d)", _:handle, f_ex_flength_ret);
	return f_ex_flength_ret;
	#else
	return flength(handle);
	#endif
}
	#if defined _ALS_flength
		#undef flength
	#else
		#define _ALS_flength
	#endif
	#define flength	f_ex_hook_flength
stock f_ex_hook_fexist(const pattern[])
{
	if(fexist(pattern))
	{
		g_f_ex_res = f_ex_res_OK;
	#if FILE_EX_DEBUG_LEVEL > 2
		printf(" [DEBUG] <file_ex.inc> fexist() -> File \"%s\" exist", pattern);
	#endif
		return true;
	}
	format(g_f_ex_res_descr, sizeof(g_f_ex_res_descr), pattern);
	g_f_ex_res = f_ex_res_INV_FILE_ACCESS;
	#if FILE_EX_DEBUG_LEVEL > 1
	printf(" [DEBUG] <file_ex.inc> fexist() -> File \"%s\" does not exist", pattern);
	#endif
	#if defined FILE_EX_ENABLE_REMOTE
	CallRemoteFunction(FILE_EX_RES_CB_NAME_STR, "ddsds", FILE_EX_SCRIPT_ID, _:f_ex_res_INV_FILE_ACCESS, "fexist", 0, pattern);
	#endif
	return false;
}
	#if defined _ALS_fexist
		#undef fexist
	#else
		#define _ALS_fexist
	#endif
	#define fexist	f_ex_hook_fexist
stock f_ex_res_ENUM:f_ex_inc_get_result(bool:keep_result = true)
{
	if(keep_result) return g_f_ex_res;
	new f_ex_res_ENUM:ret_g_f_ex_res = g_f_ex_res;
	g_f_ex_res = f_ex_res_OK;
	g_f_ex_res_descr[0] = '\0';
	return ret_g_f_ex_res;
}
stock f_ex_inc_print_result(bool:ignore_ok = true, bool:keep_result = true)
{
	new f_ex_res_ENUM:ret_g_f_ex_res;
	switch(ret_g_f_ex_res = f_ex_inc_get_result(keep_result))
	{
		case f_ex_res_OK:
		{
			if(ignore_ok) return ret_g_f_ex_res;
			print("[FILE EX] No error!");
		}
		case f_ex_res_INV_FILE_ACCESS: printf(" [FILE EX] Invalid file access at \"%s\"", g_f_ex_res_descr);
		case f_ex_res_INV_TEMP_FILE_ACCESS: print(" [FILE EX] Invalid temporary file access");
		case f_ex_res_INV_FILE_S_PTR: printf(" [FILE EX] Invalid file stream pointer ( File:%d )", g_f_ex_res_descr[0]);
		case f_ex_res_EOF: printf(" [FILE EX] End of file ( File:%d ) \"%s\"", g_f_ex_res_descr[0], g_f_ex_res_descr[1]);
	}
	return ret_g_f_ex_res;
}
	#define F_EX_RES::	f_ex_res_
#endif
#define F_EX::		f_ex_inc_