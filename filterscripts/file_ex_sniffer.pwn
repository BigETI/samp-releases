#include <a_samp>
#include <file_ex_remote>

public OnFileExError(script_id, F_EX_RES::ENUM:result_id, func_name[], File:file_handle, msg[])
{
	switch(result_id)
	{
		case F_EX_RES::OK: printf("OnFileExError(): [ Script ID: %d ] %s(): [ File:%d ] OK \"%s\"", script_id, func_name, _:file_handle, msg);
		case F_EX_RES::INV_FILE_ACCESS: printf("OnFileExError(): [ Script ID: %d ] %s(): [ File:%d ] Invalid file access \"%s\"", script_id, func_name, _:file_handle, msg);
		case F_EX_RES::INV_TEMP_FILE_ACCESS: printf("OnFileExError(): [ Script ID: %d ] %s(): [ File:%d ] Invalid temporary file access \"%s\"", script_id, func_name, _:file_handle, msg);
		case F_EX_RES::INV_FILE_S_PTR: printf("OnFileExError(): [ Script ID: %d ] %s(): [ File:%d ] Invalid file pointer access \"%s\"", script_id, func_name, _:file_handle, msg);
		case F_EX_RES::EOF: printf("OnFileExError(): [ Script ID: %d ] %s(): [ File:%d ] End of file \"%s\"", script_id, func_name, _:file_handle, msg);
	}
}