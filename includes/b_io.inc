/*
	Binary files I/O plugin's include made by BigETI © 2013
*/
#if defined _B_IO_INCLUDED_
	#endinput
#endif
#define _B_IO_INCLUDED_
#define BIO_ENUM_ENUM					enum _:
#define BIO_ENUM_8<%0>					%0
#define BIO_ENUM_8A<%0>[%1]				%0[%1]
#define BIO_ENUM_8T<%0><%1>				%0:%1
#define BIO_ENUM_8TA<%0><%1>[%2]		%0:%1[%2]
#define BIO_ENUM_8AT<%0><%1>[%2]		%0:%1[%2]
#define BIO_ENUM_16<%0>					%0,__%0_U
#define BIO_ENUM_16A<%0>[%1]			%0[%1],__%0_U[%1]
#define BIO_ENUM_16T<%0><%1>			%0:%1,__%1_U
#define BIO_ENUM_16TA<%0><%1>[%2]		%0:%1[%2],__%1_U[%2]
#define BIO_ENUM_16AT<%0><%1>[%2]		%0:%1[%2],__%1_U[%2]
#define BIO_ENUM_24<%0>					%0,__%0_U[2]
#define BIO_ENUM_24A<%0>[%1]			%0[%1],__%0_U[(%1)*2]
#define BIO_ENUM_24T<%0><%1>			%0:%1,__%1_U[2]
#define BIO_ENUM_24TA<%0><%1>[%2]		%0:%1[%2],__%1_U[(%2)*2]
#define BIO_ENUM_24AT<%0><%1>[%2]		%0:%1[%2],__%1_U[(%2)*2]
#define BIO_ENUM_32<%0>					%0,__%0_U[3]
#define BIO_ENUM_32A<%0>[%1]			%0[%1],__%0_U[(%1)*3]
#define BIO_ENUM_32T<%0><%1>			%0:%1,__%1_U[3]
#define BIO_ENUM_32TA<%0><%1>[%2]		%0:%1[%2],__%1_U[(%2)*3]
#define BIO_ENUM_32AT<%0><%1>[%2]		%0:%1[%2],__%1_U[(%2)*3]
#define BIO_ENUM_F<%0>					Float:%0,__%0_U[3]
#define BIO_ENUM_FA<%0>[%1]				Float:%0[%1],__%0_U[(%1)*3]
#define BIO_exist(%0)					fexist(%0)
#define BIO_read_f(%0,%1,%2)			Float:(BIO_read_32(%0,%1,%2))
#define BIO_write_f(%0,%1,%2)			BIO_write_32(%0,Float:(%1),%2)
#define BIO_read_f_arr(%0,%1,%2)		BIO_read_32_arr(%0,Float:%1,%2)
#define BIO_write_f_arr(%0,%1,%2)		BIO_write_32_arr(%0,Float:%1,%2)
#define BIO_INST_read_f(%0,%1)			Float:(BIO_read_INST_32(%0,%1))
#define BIO_INST_write_f(%0,%1)			BIO_write_INST_32(Float:(%0),%1)
#define BIO_INST_read_f_arr(%0,%1)		BIO_read_INST_32_arr(Float:%0,%1)
#define BIO_INST_write_f_arr(%0,%1)		BIO_write_INST_32_arr(Float:%0,%1)
enum b_io_mode
{
	b_io_mode_read,
	b_io_mode_write,
	b_io_mode_append,
	b_io_mode_new,
	b_io_mode_add,
	b_io_mode_update
};
native BFile:BIO_open(const file_name[], b_io_mode:mode = b_io_mode_update);
native BFile:BIO_temp();
native BIO_close(BFile:file_handle);
native BIO_read_8(BFile:file_handle, position = 0, seek_whence:whence = seek_current);
native BIO_read_16(BFile:file_handle, position = 0, seek_whence:whence = seek_current);
native BIO_read_24(BFile:file_handle, position = 0, seek_whence:whence = seek_current);
native BIO_read_32(BFile:file_handle, position = 0, seek_whence:whence = seek_current);
native BIO_write_8(BFile:file_handle, value, position = 0, seek_whence:whence = seek_current);
native BIO_write_16(BFile:file_handle, value, position = 0, seek_whence:whence = seek_current);
native BIO_write_24(BFile:file_handle, value, position = 0, seek_whence:whence = seek_current);
native BIO_write_32(BFile:file_handle, value, position = 0, seek_whence:whence = seek_current);
native BIO_read_8_arr(BFile:file_handle, bin_array[], bin_array_len = sizeof bin_array, position = 0, seek_whence:whence = seek_current);
native BIO_read_16_arr(BFile:file_handle, bin_array[], bin_array_len = sizeof bin_array, position = 0, seek_whence:whence = seek_current);
native BIO_read_24_arr(BFile:file_handle, bin_array[], bin_array_len = sizeof bin_array, position = 0, seek_whence:whence = seek_current);
native BIO_read_32_arr(BFile:file_handle, bin_array[], bin_array_len = sizeof bin_array, position = 0, seek_whence:whence = seek_current);
native BIO_write_8_arr(BFile:file_handle, const bin_array[], bin_array_len = sizeof bin_array, position = 0, seek_whence:whence = seek_current);
native BIO_write_16_arr(BFile:file_handle, const bin_array[], bin_array_len = sizeof bin_array, position = 0, seek_whence:whence = seek_current);
native BIO_write_24_arr(BFile:file_handle, const bin_array[], bin_array_len = sizeof bin_array, position = 0, seek_whence:whence = seek_current);
native BIO_write_32_arr(BFile:file_handle, const bin_array[], bin_array_len = sizeof bin_array, position = 0, seek_whence:whence = seek_current);
native bool:BIO_eof(BFile:file_handle);
native bool:BIO_INST_open(const file_name[], b_io_mode:mode = b_io_mode_update);
native bool:BIO_INST_temp();
native bool:BIO_INST_close();
native BIO_INST_read_8(position = 0, seek_whence:whence = seek_current);
native BIO_INST_read_16(position = 0, seek_whence:whence = seek_current);
native BIO_INST_read_24(position = 0, seek_whence:whence = seek_current);
native BIO_INST_read_32(position = 0, seek_whence:whence = seek_current);
native BIO_INST_write_8(value, position = 0, seek_whence:whence = seek_current);
native BIO_INST_write_16(value, position = 0, seek_whence:whence = seek_current);
native BIO_INST_write_24(value, position = 0, seek_whence:whence = seek_current);
native BIO_INST_write_32(value, position = 0, seek_whence:whence = seek_current);
native BIO_INST_read_8_arr(bin_array[], bin_array_len = sizeof bin_array, position = 0, seek_whence:whence = seek_current);
native BIO_INST_read_16_arr(bin_array[], bin_array_len = sizeof bin_array, position = 0, seek_whence:whence = seek_current);
native BIO_INST_read_24_arr(bin_array[], bin_array_len = sizeof bin_array, position = 0, seek_whence:whence = seek_current);
native BIO_INST_read_32_arr(bin_array[], bin_array_len = sizeof bin_array, position = 0, seek_whence:whence = seek_current);
native BIO_INST_write_8_arr(const bin_array[], bin_array_len = sizeof bin_array, position = 0, seek_whence:whence = seek_current);
native BIO_INST_write_16_arr(const bin_array[], bin_array_len = sizeof bin_array, position = 0, seek_whence:whence = seek_current);
native BIO_INST_write_24_arr(const bin_array[], bin_array_len = sizeof bin_array, position = 0, seek_whence:whence = seek_current);
native BIO_INST_write_32_arr(const bin_array[], bin_array_len = sizeof bin_array, position = 0, seek_whence:whence = seek_current);
native bool:BIO_INST_eof();
#define BIO::			BIO_
#define BIO_I::			BIO_INST_
#define BIO_INST::		BIO_INST_
#define BIO_INSTANT::	BIO_INST_
#define BIO_E::			BIO_ENUM_
#define BIO_ENUM::		BIO_ENUM_