/*
	Binary files I/O plugin made by BigETI © 2013
*/

#include <string>
#include <algorithm>
#include <vector>
#include <ctime>
#include "SDK\amx\amx.h"
#include "SDK\plugincommon.h"

#define vector_foreach(type,vect,var)	for(vector<type>::iterator (var)=(vect).begin();(var)!=(vect).end();++(var))

typedef void (*logprintf_t)(char* format, ...);
logprintf_t logprintf;
extern void *pAMXFunctions;

using namespace std;

struct B_IO_AMX_STRUCT
{
	AMX *amx_ptr;
	FILE *current_file_handle;
};

typedef vector<B_IO_AMX_STRUCT> B_IO_AMX_STRUCT_VECTOR;

enum B_IO_MODE_ENUM
{
	B_IO_MODE_READ,
	B_IO_MODE_WRITE,
	B_IO_MODE_APPEND,
	B_IO_MODE_NEW,
	B_IO_MODE_ADD,
	B_IO_MODE_UPDATE
};

B_IO_AMX_STRUCT_VECTOR b_io_amx_vect;

FILE *amx_fopen(AMX *amx, cell *file_name, B_IO_MODE_ENUM mode)
{
	int str_len;
	cell *addr = NULL;
	amx_GetAddr(amx, *file_name, &addr);
	amx_StrLen(addr, &str_len);
	if(str_len)
	{
		char *var_c_str = new char[++str_len];
		if(var_c_str == NULL)
		{
			logprintf("[BIO ERROR] Out of memory!");
			exit(0);
		}
		amx_GetString(var_c_str, addr, 0, str_len);
		char *t_c_str = var_c_str;
		while(*t_c_str != '\0')
		{
			switch(*t_c_str)
			{
				case '\\': case ':': case '*': case '?': case '\"': case '<': case '>': case '|':
					logprintf("[BIO ERROR] Attempted to open file \"%s\"", var_c_str);
					return NULL;
				case '.':
					t_c_str++;
					if(*t_c_str == '.')
					{
						logprintf("[BIO ERROR] Attempted to open file \"%s\"", var_c_str);
						return NULL;
					}
					break;
			}
			t_c_str++;
		}
		char *final_file_name = new char[str_len += 12];
		if(final_file_name == NULL)
		{
			delete[] var_c_str;
			logprintf("[BIO ERROR] Out of memory!");
			exit(0);
		}
		strcpy_s(final_file_name, str_len, "scriptfiles/");
		strcat_s(final_file_name, str_len, var_c_str);
		FILE *ret;
		switch(mode)
		{
			case B_IO_MODE_READ:
				fopen_s(&ret, final_file_name, "rb");
				break;
			case B_IO_MODE_WRITE:
				fopen_s(&ret, final_file_name, "wb");
				break;
			case B_IO_MODE_APPEND:
				fopen_s(&ret, final_file_name, "ab");
				break;
			case B_IO_MODE_NEW:
				fopen_s(&ret, final_file_name, "wb+");
				break;
			case B_IO_MODE_ADD:
				fopen_s(&ret, final_file_name, "ab+");
				break;
			case B_IO_MODE_UPDATE:
				fopen_s(&ret, final_file_name, "rb+");
				break;
			default:
				logprintf("[BIO ERROR] Attempted to set file stream mode to ID:%d for \"%s\"", mode, var_c_str);
				delete[] var_c_str;
				delete[] final_file_name;
				return NULL;
		}
		delete[] var_c_str;
		delete[] final_file_name;
		return ret;
	}
	logprintf("[BIO ERROR] Null string detected!");
	return NULL;
}

// native BFile:BIO_open(const file_name[], b_io_mode:mode = b_io_mode_update);
cell AMX_NATIVE_CALL AMX_BIO_open(AMX *amx, cell *params)
{
	return (cell)amx_fopen(amx, &params[1], (B_IO_MODE_ENUM)params[2]);
}

// native BFile:BIO_temp();
cell AMX_NATIVE_CALL AMX_BIO_temp(AMX *amx, cell *params)
{
	FILE *ret;
	tmpfile_s(&ret);
	return (cell)ret;
}

// native BIO_close(BFile:file_handle);
cell AMX_NATIVE_CALL AMX_BIO_close(AMX *amx, cell *params)
{
	return (cell)fclose((FILE *)params[1]);
}

// native BIO_read_8(BFile:file_handle, position = 0, seek_whence:whence = seek_current);
cell AMX_NATIVE_CALL AMX_BIO_read_8(AMX *amx, cell *params)
{
	fseek((FILE *)params[1], (long)params[2], (int)params[3]);
	return (cell)fgetc((FILE *)params[1]);
}

// native BIO_read_16(BFile:file_handle, position = 0, seek_whence:whence = seek_current);
cell AMX_NATIVE_CALL AMX_BIO_read_16(AMX *amx, cell *params)
{
	fseek((FILE *)params[1], (long)params[2], (int)params[3]);
	cell ret = NULL;
	fread(&ret, 2, 1, (FILE *)params[1]);
	return ret;
}

// native BIO_read_24(BFile:file_handle, position = 0, seek_whence:whence = seek_current);
cell AMX_NATIVE_CALL AMX_BIO_read_24(AMX *amx, cell *params)
{
	fseek((FILE *)params[1], (long)params[2], (int)params[3]);
	cell ret = NULL;
	fread(&ret, 3, 1, (FILE *)params[1]);
	return ret;
}

// native BIO_read_32(BFile:file_handle, position = 0, seek_whence:whence = seek_current);
cell AMX_NATIVE_CALL AMX_BIO_read_32(AMX *amx, cell *params)
{
	fseek((FILE *)params[1], (long)params[2], (int)params[3]);
	cell ret = NULL;
	fread(&ret, 4, 1, (FILE *)params[1]);
	return ret;
}

// native BIO_write_8(BFile:file_handle, value, position = 0, seek_whence:whence = seek_current);
cell AMX_NATIVE_CALL AMX_BIO_write_8(AMX *amx, cell *params)
{
	fseek((FILE *)params[1], (long)params[3], (int)params[4]);
	return (cell)fputc((int)(params[2]&0xFF), (FILE *)params[1]);
}

// native BIO_write_16(BFile:file_handle, value, position = 0, seek_whence:whence = seek_current);
cell AMX_NATIVE_CALL AMX_BIO_write_16(AMX *amx, cell *params)
{
	fseek((FILE *)params[1], (long)params[3], (int)params[4]);
	return (cell)fwrite(&params[2], 2, 1, (FILE *)params[1]);
}

// native BIO_write_24(BFile:file_handle, value, position = 0, seek_whence:whence = seek_current);
cell AMX_NATIVE_CALL AMX_BIO_write_24(AMX *amx, cell *params)
{
	fseek((FILE *)params[1], (long)params[3], (int)params[4]);
	return (cell)fwrite(&params[2], 3, 1, (FILE *)params[1]);
}

// native BIO_write_32(BFile:file_handle, value, position = 0, seek_whence:whence = seek_current);
cell AMX_NATIVE_CALL AMX_BIO_write_32(AMX *amx, cell *params)
{
	fseek((FILE *)params[1], (long)params[3], (int)params[4]);
	return (cell)fwrite(&params[2], 4, 1, (FILE *)params[1]);
}

// native BIO_read_8_arr(BFile:file_handle, bin_array[], bin_array_len = sizeof bin_array, position = 0, seek_whence:whence = seek_current);
cell AMX_NATIVE_CALL AMX_BIO_read_8_arr(AMX *amx, cell *params)
{
	if(params[3] <= 0) return 0;
	fseek((FILE *)params[1], (long)params[4], (int)params[5]);
	cell *addr, count_write = 0;
	amx_GetAddr(amx, params[2], &addr);
	for(int i = 0; i < params[3]; i++) if((addr[i] = fgetc((FILE *)params[1])) != EOF) count_write++;
	return count_write;
}

// native BIO_read_16_arr(BFile:file_handle, bin_array[], bin_array_len = sizeof bin_array, position = 0, seek_whence:whence = seek_current);
cell AMX_NATIVE_CALL AMX_BIO_read_16_arr(AMX *amx, cell *params)
{
	if(params[3] <= 0) return 0;
	fseek((FILE *)params[1], (long)params[4], (int)params[5]);
	cell *addr, count_write = 0;
	amx_GetAddr(amx, params[2], &addr);
	for(int i = 0; i < params[3]; i++) count_write += fread(&addr[i], 2, 1, (FILE *)params[1]);
	return count_write;
}

// native BIO_read_24_arr(BFile:file_handle, bin_array[], bin_array_len = sizeof bin_array, position = 0, seek_whence:whence = seek_current);
cell AMX_NATIVE_CALL AMX_BIO_read_24_arr(AMX *amx, cell *params)
{
	if(params[3] <= 0) return 0;
	fseek((FILE *)params[1], (long)params[4], (int)params[5]);
	cell *addr, count_write = 0;
	amx_GetAddr(amx, params[2], &addr);
	for(int i = 0; i < params[3]; i++) count_write += fread(&addr[i], 3, 1, (FILE *)params[1]);
	return count_write;
}

// native BIO_read_32_arr(BFile:file_handle, bin_array[], bin_array_len = sizeof bin_array, position = 0, seek_whence:whence = seek_current);
cell AMX_NATIVE_CALL AMX_BIO_read_32_arr(AMX *amx, cell *params)
{
	if(params[3] <= 0) return 0;
	fseek((FILE *)params[1], (long)params[4], (int)params[5]);
	cell *addr;
	amx_GetAddr(amx, params[2], &addr);
	return fread(addr, 4, params[3], (FILE *)params[1]);
}

// native BIO_write_8_arr(BFile:file_handle, const bin_array[], bin_array_len = sizeof bin_array, position = 0, seek_whence:seek_current);
cell AMX_NATIVE_CALL AMX_BIO_write_8_arr(AMX *amx, cell *params)
{
	if(params[3] <= 0) return 0;
	fseek((FILE *)params[1], (long)params[4], (int)params[5]);
	cell *addr, count_write = 0;
	amx_GetAddr(amx, params[2], &addr);
	for(int i = 0; i < params[3]; i++) count_write += fputc(addr[i], (FILE *)params[1]);
	return count_write;
}

// native BIO_write_16_arr(BFile:file_handle, const bin_array[], bin_array_len = sizeof bin_array, position = 0, seek_whence:whence = seek_current);
cell AMX_NATIVE_CALL AMX_BIO_write_16_arr(AMX *amx, cell *params)
{
	if(params[3] <= 0) return 0;
	fseek((FILE *)params[1], (long)params[4], (int)params[5]);
	cell *addr, count_write = 0;
	amx_GetAddr(amx, params[2], &addr);
	for(int i = 0; i < params[3]; i++) count_write += fwrite(&addr[i], 2, 1, (FILE *)params[1]);
	return count_write;
}

// native BIO_write_24_arr(BFile:file_handle, const bin_array[], bin_array_len = sizeof bin_array, position = 0, seek_whence:whence = seek_current);
cell AMX_NATIVE_CALL AMX_BIO_write_24_arr(AMX *amx, cell *params)
{
	if(params[3] <= 0) return 0;
	fseek((FILE *)params[1], (long)params[4], (int)params[5]);
	cell *addr, count_write = 0;
	amx_GetAddr(amx, params[2], &addr);
	for(int i = 0; i < params[3]; i++) count_write += fwrite(&addr[i], 3, 1, (FILE *)params[1]);
	return count_write;
}

// native BIO_write_32_arr(BFile:file_handle, const bin_array[], bin_array_len = sizeof bin_array, position = 0, seek_whence:whence = seek_current);
cell AMX_NATIVE_CALL AMX_BIO_write_32_arr(AMX *amx, cell *params)
{
	if(params[3] <= 0) return 0;
	fseek((FILE *)params[1], (long)params[4], (int)params[5]);
	cell *addr;
	amx_GetAddr(amx, params[2], &addr);
	return fwrite(addr, 4, params[3], (FILE *)params[1]);
}

// native bool:BIO_eof(BFile:file_handle);
cell AMX_NATIVE_CALL AMX_BIO_eof(AMX *amx, cell *params)
{
	return (cell)feof((FILE *)params[1]);
}

// native bool:BIO_INST_open(const file_name[], b_io_mode:mode = b_io_mode_update);
cell AMX_NATIVE_CALL AMX_BIO_INST_open(AMX *amx, cell *params)
{
	vector_foreach(B_IO_AMX_STRUCT, b_io_amx_vect, amx_it)
	{
		if(amx_it->amx_ptr != amx) continue;
		if(amx_it->current_file_handle) fclose(amx_it->current_file_handle);
		return (amx_it->current_file_handle = amx_fopen(amx, &params[1], (B_IO_MODE_ENUM)params[2])) != NULL;
	}
	return 0;
}

// native bool:BIO_INST_temp();
cell AMX_NATIVE_CALL AMX_BIO_INST_temp(AMX *amx, cell *params)
{
	vector_foreach(B_IO_AMX_STRUCT, b_io_amx_vect, amx_it)
	{
		if(amx_it->amx_ptr != amx) continue;
		if(amx_it->current_file_handle) fclose(amx_it->current_file_handle);
		tmpfile_s(&(amx_it->current_file_handle));
		return (amx_it->current_file_handle != NULL);
	}
	return 0;
}

// native bool:BIO_INST_close();
cell AMX_NATIVE_CALL AMX_INST_close(AMX *amx, cell *params)
{
	vector_foreach(B_IO_AMX_STRUCT, b_io_amx_vect, amx_it)
	{
		if(amx_it->amx_ptr != amx) continue;
		if(!amx_it->current_file_handle) return 0;
		fclose(amx_it->current_file_handle);
		amx_it->current_file_handle = NULL;
		return 1;
	}
	return 0;
}

// native BIO_INST_read_8(position = 0, seek_whence:whence = seek_current);
cell AMX_NATIVE_CALL AMX_BIO_INST_read_8(AMX *amx, cell *params)
{
	vector_foreach(B_IO_AMX_STRUCT, b_io_amx_vect, amx_it)
	{
		if(amx_it->amx_ptr != amx) continue;
		if(amx_it->current_file_handle == NULL)
		{
			logprintf("[BIO WARNING] Not initialized instant file handle!");
			return 0;
		}
		fseek(amx_it->current_file_handle, (long)params[1], (int)params[2]);
		return fgetc(amx_it->current_file_handle);
	}
	return 0;
}

// native BIO_INST_read_16(position = 0, seek_whence:whence = seek_current);
cell AMX_NATIVE_CALL AMX_BIO_INST_read_16(AMX *amx, cell *params)
{
	vector_foreach(B_IO_AMX_STRUCT, b_io_amx_vect, amx_it)
	{
		if(amx_it->amx_ptr != amx) continue;
		if(amx_it->current_file_handle == NULL)
		{
			logprintf("[BIO WARNING] Not initialized instant file handle!");
			return 0;
		}
		fseek(amx_it->current_file_handle, (long)params[1], (int)params[2]);
		cell ret = NULL;
		fread(&ret, 2, 1, amx_it->current_file_handle);
		return ret;
	}
	return 0;
}

// native BIO_INST_read_24(position = 0, seek_whence:whence = seek_current);
cell AMX_NATIVE_CALL AMX_BIO_INST_read_24(AMX *amx, cell *params)
{
	vector_foreach(B_IO_AMX_STRUCT, b_io_amx_vect, amx_it)
	{
		if(amx_it->amx_ptr != amx) continue;
		if(amx_it->current_file_handle == NULL)
		{
			logprintf("[BIO WARNING] Not initialized instant file handle!");
			return 0;
		}
		fseek(amx_it->current_file_handle, (long)params[1], (int)params[2]);
		cell ret = NULL;
		fread(&ret, 3, 1, amx_it->current_file_handle);
		return ret;
	}
	return 0;
}

// native BIO_INST_read_32(position = 0, seek_whence:whence = seek_current);
cell AMX_NATIVE_CALL AMX_BIO_INST_read_32(AMX *amx, cell *params)
{
	vector_foreach(B_IO_AMX_STRUCT, b_io_amx_vect, amx_it)
	{
		if(amx_it->amx_ptr != amx) continue;
		if(amx_it->current_file_handle == NULL)
		{
			logprintf("[BIO WARNING] Not initialized instant file handle!");
			return 0;
		}
		fseek(amx_it->current_file_handle, (long)params[1], (int)params[2]);
		cell ret = NULL;
		fread(&ret, 4, 1, amx_it->current_file_handle);
		return ret;
	}
	return 0;
}

// native BIO_INST_write_8(value, position = 0, seek_whence:whence = seek_current);
cell AMX_NATIVE_CALL AMX_BIO_INST_write_8(AMX *amx, cell *params)
{
	vector_foreach(B_IO_AMX_STRUCT, b_io_amx_vect, amx_it)
	{
		if(amx_it->amx_ptr != amx) continue;
		if(amx_it->current_file_handle == NULL)
		{
			logprintf("[BIO WARNING] Not initialized instant file handle!");
			return 0;
		}
		fseek(amx_it->current_file_handle, (long)params[2], (int)params[3]);
		return fputc((int)(params[1]&0xFF), amx_it->current_file_handle);
	}
	return 0;
}

// native BIO_INST_write_16(value, position = 0, seek_whence:whence = seek_current);
cell AMX_NATIVE_CALL AMX_BIO_INST_write_16(AMX *amx, cell *params)
{
	vector_foreach(B_IO_AMX_STRUCT, b_io_amx_vect, amx_it)
	{
		if(amx_it->amx_ptr != amx) continue;
		if(amx_it->current_file_handle == NULL)
		{
			logprintf("[BIO WARNING] Not initialized instant file handle!");
			return 0;
		}
		fseek(amx_it->current_file_handle, (long)params[2], (int)params[3]);
		return fwrite(&params[1], 2, 1, amx_it->current_file_handle);
	}
	return 0;
}

// native BIO_INST_write_24(value, position = 0, seek_whence:whence = seek_current);
cell AMX_NATIVE_CALL AMX_BIO_INST_write_24(AMX *amx, cell *params)
{
	vector_foreach(B_IO_AMX_STRUCT, b_io_amx_vect, amx_it)
	{
		if(amx_it->amx_ptr != amx) continue;
		if(amx_it->current_file_handle == NULL)
		{
			logprintf("[BIO WARNING] Not initialized instant file handle!");
			return 0;
		}
		fseek(amx_it->current_file_handle, (long)params[2], (int)params[3]);
		return fwrite(&params[1], 3, 1, amx_it->current_file_handle);
	}
	return 0;
}

// native BIO_INST_write_32(value, position = 0, seek_whence:whence = seek_current);
cell AMX_NATIVE_CALL AMX_BIO_INST_write_32(AMX *amx, cell *params)
{
	vector_foreach(B_IO_AMX_STRUCT, b_io_amx_vect, amx_it)
	{
		if(amx_it->amx_ptr != amx) continue;
		if(amx_it->current_file_handle == NULL)
		{
			logprintf("[BIO WARNING] Not initialized instant file handle!");
			return 0;
		}
		fseek(amx_it->current_file_handle, (long)params[2], (int)params[3]);
		return fwrite(&params[1], 4, 1, amx_it->current_file_handle);
	}
	return 0;
}

// native BIO_INST_read_8_arr(bin_array[], bin_array_len = sizeof bin_array, position = 0, seek_whence:whence = seek_current);
cell AMX_NATIVE_CALL AMX_BIO_INST_read_8_arr(AMX *amx, cell *params)
{
	vector_foreach(B_IO_AMX_STRUCT, b_io_amx_vect, amx_it)
	{
		if(amx_it->amx_ptr != amx) continue;
		if(amx_it->current_file_handle == NULL)
		{
			logprintf("[BIO WARNING] Not initialized instant file handle!");
			return 0;
		}
		fseek(amx_it->current_file_handle, (long)params[3], (int)params[4]);
		cell *addr;
		amx_GetAddr(amx, params[1], (cell **)&addr);
		for(int i = 0; i < params[2]; i++) addr[i] = fgetc(amx_it->current_file_handle);
		return 1;
	}
	return 0;
}

// native BIO_INST_read_16_arr(bin_array[], bin_array_len = sizeof bin_array, position = 0, seek_whence:whence = seek_current);
cell AMX_NATIVE_CALL AMX_BIO_INST_read_16_arr(AMX *amx, cell *params)
{
	vector_foreach(B_IO_AMX_STRUCT, b_io_amx_vect, amx_it)
	{
		if(amx_it->amx_ptr != amx) continue;
		if(amx_it->current_file_handle == NULL)
		{
			logprintf("[BIO WARNING] Not initialized instant file handle!");
			return 0;
		}
		fseek(amx_it->current_file_handle, (long)params[3], (int)params[4]);
		cell *addr;
		amx_GetAddr(amx, params[1], &addr);
		for(int i = 0; i < params[2]; i++) fread(addr+i, 2, 1, amx_it->current_file_handle);
		return 1;
	}
	return 0;
}

// native BIO_INST_read_24_arr(bin_array[], bin_array_len = sizeof bin_array, position = 0, seek_whence:whence = seek_current);
cell AMX_NATIVE_CALL AMX_BIO_INST_read_24_arr(AMX *amx, cell *params)
{
	vector_foreach(B_IO_AMX_STRUCT, b_io_amx_vect, amx_it)
	{
		if(amx_it->amx_ptr != amx) continue;
		if(amx_it->current_file_handle == NULL)
		{
			logprintf("[BIO WARNING] Not initialized instant file handle!");
			return 0;
		}
		fseek(amx_it->current_file_handle, (long)params[3], (int)params[4]);
		cell *addr;
		amx_GetAddr(amx, params[1], &addr);
		for(int i = 0; i < params[2]; i++) fread(addr+i, 3, 1, amx_it->current_file_handle);
		return 1;
	}
	return 0;
}

// native BIO_INST_read_32_arr(bin_array[], bin_array_len = sizeof bin_array, position = 0, seek_whence:whence = seek_current);
cell AMX_NATIVE_CALL AMX_BIO_INST_read_32_arr(AMX *amx, cell *params)
{
	vector_foreach(B_IO_AMX_STRUCT, b_io_amx_vect, amx_it)
	{
		if(amx_it->amx_ptr != amx) continue;
		if(amx_it->current_file_handle == NULL)
		{
			logprintf("[BIO WARNING] Not initialized instant file handle!");
			return 0;
		}
		fseek(amx_it->current_file_handle, (long)params[3], (int)params[4]);
		cell *addr;
		amx_GetAddr(amx, params[1], &addr);
		fread(addr, 4, params[2], amx_it->current_file_handle);
		return 1;
	}
	return 0;
}

// native BIO_INST_write_8_arr(const bin_array[], bin_array_len = sizeof bin_array, position = 0, seek_whence:whence = seek_current);
cell AMX_NATIVE_CALL AMX_BIO_INST_write_8_arr(AMX *amx, cell *params)
{
	vector_foreach(B_IO_AMX_STRUCT, b_io_amx_vect, amx_it)
	{
		if(amx_it->amx_ptr != amx) continue;
		if(amx_it->current_file_handle == NULL)
		{
			logprintf("[BIO WARNING] Not initialized instant file handle!");
			return 0;
		}
		fseek(amx_it->current_file_handle, (long)params[3], (int)params[4]);
		cell *addr, count_write = 0;
		amx_GetAddr(amx, params[1], &addr);
		for(int i = 0; i < params[2]; i++) count_write += fputc(addr[i], amx_it->current_file_handle);
		return count_write;
	}
	return 0;
}

// native BIO_INST_write_16_arr(const bin_array[], bin_array_len = sizeof bin_array, position = 0, seek_whence:whence = seek_current);
cell AMX_NATIVE_CALL AMX_BIO_INST_write_16_arr(AMX *amx, cell *params)
{
	vector_foreach(B_IO_AMX_STRUCT, b_io_amx_vect, amx_it)
	{
		if(amx_it->amx_ptr != amx) continue;
		if(amx_it->current_file_handle == NULL)
		{
			logprintf("[BIO WARNING] Not initialized instant file handle!");
			return 0;
		}
		fseek(amx_it->current_file_handle, (long)params[3], (int)params[4]);
		cell *addr, count_write = 0;
		amx_GetAddr(amx, params[1], &addr);
		for(int i = 0; i < params[2]; i++) count_write += fwrite(addr+i, 2, 1, amx_it->current_file_handle);
		return count_write;
	}
	return 0;
}

// native BIO_INST_write_24_arr(const bin_array[], bin_array_len = sizeof bin_array, position = 0, seek_whence:whence = seek_current);
cell AMX_NATIVE_CALL AMX_BIO_INST_write_24_arr(AMX *amx, cell *params)
{
	vector_foreach(B_IO_AMX_STRUCT, b_io_amx_vect, amx_it)
	{
		if(amx_it->amx_ptr != amx) continue;
		if(amx_it->current_file_handle == NULL)
		{
			logprintf("[BIO WARNING] Not initialized instant file handle!");
			return 0;
		}
		fseek(amx_it->current_file_handle, (long)params[3], (int)params[4]);
		cell *addr, count_write = 0;
		amx_GetAddr(amx, params[1], &addr);
		for(int i = 0; i < params[2]; i++) count_write += fwrite(addr+i, 3, 1, amx_it->current_file_handle);
		return count_write;
	}
	return 0;
}

// native BIO_INST_write_32_arr(const bin_array[], bin_array_len = sizeof bin_array, position = 0, seek_whence:whence = seek_current);
cell AMX_NATIVE_CALL AMX_BIO_INST_write_32_arr(AMX *amx, cell *params)
{
	vector_foreach(B_IO_AMX_STRUCT, b_io_amx_vect, amx_it)
	{
		if(amx_it->amx_ptr != amx) continue;
		if(amx_it->current_file_handle == NULL)
		{
			logprintf("[BIO WARNING] Not initialized instant file handle!");
			return 0;
		}
		fseek(amx_it->current_file_handle, (long)params[3], (int)params[4]);
		cell *addr;
		amx_GetAddr(amx, params[1], &addr);
		return fwrite(addr, 4, params[2], amx_it->current_file_handle);
	}
	return 0;
}

// native bool:BIO_INST_eof();
cell AMX_NATIVE_CALL AMX_BIO_INST_eof(AMX *amx, cell *params)
{
	vector_foreach(B_IO_AMX_STRUCT, b_io_amx_vect, amx_it)
	{
		if(amx_it->amx_ptr != amx) continue;
		if(amx_it->current_file_handle == NULL)
		{
			logprintf("[BIO WARNING] Not initialized instant file handle!");
			return 0;
		}
		return (cell)feof(amx_it->current_file_handle);
	}
	return 0;
}

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports()
{
	return SUPPORTS_VERSION|SUPPORTS_AMX_NATIVES|SUPPORTS_PROCESS_TICK;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData)
{
	pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
	logprintf = (logprintf_t)ppData[PLUGIN_DATA_LOGPRINTF];
	logprintf("===========================");
	logprintf("= Binary files I/O plugin =");
	logprintf("=          Made by BigETI =");
	logprintf("= Loaded!                 =");
	logprintf("===========================");
	return true;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload()
{
	logprintf("===========================");
	logprintf("= Binary files I/O plugin =");
	logprintf("=          Made by BigETI =");
	logprintf("= Unloaded!               =");
	logprintf("===========================");
}

AMX_NATIVE_INFO PluginNatives[] =
{
	{"BIO_open", AMX_BIO_open},
	{"BIO_temp", AMX_BIO_temp},
	{"BIO_close", AMX_BIO_close},
	{"BIO_read_8", AMX_BIO_read_8},
	{"BIO_read_16", AMX_BIO_read_16},
	{"BIO_read_24", AMX_BIO_read_24},
	{"BIO_read_32", AMX_BIO_read_32},
	{"BIO_write_8", AMX_BIO_write_8},
	{"BIO_write_16", AMX_BIO_write_16},
	{"BIO_write_24", AMX_BIO_write_24},
	{"BIO_write_32", AMX_BIO_write_32},
	{"BIO_read_8_arr", AMX_BIO_read_8_arr},
	{"BIO_read_16_arr", AMX_BIO_read_16_arr},
	{"BIO_read_24_arr", AMX_BIO_read_24_arr},
	{"BIO_read_32_arr", AMX_BIO_read_32_arr},
	{"BIO_write_8_arr", AMX_BIO_write_8_arr},
	{"BIO_write_16_arr", AMX_BIO_write_16_arr},
	{"BIO_write_24_arr", AMX_BIO_write_24_arr},
	{"BIO_write_32_arr", AMX_BIO_write_32_arr},
	{"BIO_eof", AMX_BIO_eof},
	{"BIO_INST_open", AMX_BIO_INST_open},
	{"BIO_INST_temp", AMX_BIO_INST_temp},
	{"BIO_INST_read_8", AMX_BIO_INST_read_8},
	{"BIO_INST_read_16", AMX_BIO_INST_read_16},
	{"BIO_INST_read_24", AMX_BIO_INST_read_24},
	{"BIO_INST_read_32", AMX_BIO_INST_read_32},
	{"BIO_INST_write_8", AMX_BIO_INST_write_8},
	{"BIO_INST_write_16", AMX_BIO_INST_write_16},
	{"BIO_INST_write_24", AMX_BIO_INST_write_24},
	{"BIO_INST_write_32", AMX_BIO_INST_write_32},
	{"BIO_INST_read_8_arr", AMX_BIO_INST_read_8_arr},
	{"BIO_INST_read_16_arr", AMX_BIO_INST_read_16_arr},
	{"BIO_INST_read_24_arr", AMX_BIO_INST_read_24_arr},
	{"BIO_INST_read_32_arr", AMX_BIO_INST_read_32_arr},
	{"BIO_INST_write_8_arr", AMX_BIO_INST_write_8_arr},
	{"BIO_INST_write_16_arr", AMX_BIO_INST_write_16_arr},
	{"BIO_INST_write_24_arr", AMX_BIO_INST_write_24_arr},
	{"BIO_INST_write_32_arr", AMX_BIO_INST_write_32_arr},
	{"BIO_INST_eof", AMX_BIO_INST_eof},
	{0, 0}
};

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX *amx)
{
	B_IO_AMX_STRUCT t_b_io_amx_vect;
	t_b_io_amx_vect.amx_ptr = amx;
	t_b_io_amx_vect.current_file_handle = NULL;
	b_io_amx_vect.push_back(t_b_io_amx_vect);
	return amx_Register(amx, PluginNatives, -1);
}

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX *amx)
{
	vector_foreach(B_IO_AMX_STRUCT, b_io_amx_vect, amx_it)
	{
		if(amx_it->amx_ptr != amx) continue;
		b_io_amx_vect.erase(amx_it);
		break;
	}
	return AMX_ERR_NONE;
}

PLUGIN_EXPORT void PLUGIN_CALL ProcessTick()
{
	vector_foreach(B_IO_AMX_STRUCT, b_io_amx_vect, amx_it)
	{
		if(amx_it->current_file_handle)
		{
			fclose(amx_it->current_file_handle);
			amx_it->current_file_handle = NULL;
		}
	}
}