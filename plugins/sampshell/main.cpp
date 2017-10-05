#include "main.h"

typedef void(*logprintf_t)(char* format, ...);
logprintf_t logprintf;
extern void *pAMXFunctions;

static CTR<CallbackInfo *> callbacks;
static std::mutex mtx;
static std::list<CMDRet *> cmd_rets;
static CTR<ShellThread *> shell_threads;
static std::map<AMX *, CallbackInfo *> cb_map;

void command_thread(ShellThread *shell_thread)
{
#ifdef PLUGIN_DEBUG
	logprintf("command_thread() call");
#endif
	shell_thread->ThreadedCall();
#ifdef PLUGIN_DEBUG
	logprintf("command_thread() end");
#endif
}

template <class _T> void CTR<_T>::Add(_T ptr)
{
#ifdef PLUGIN_DEBUG
	logprintf("CTR<_T>::Add() call");
#endif
	static typename std::list<_T>::iterator value;
	if (_map.find(ptr) == _map.end())
	{
		try
		{
			_list.push_back(ptr);
		}
		catch (...)
		{
			throw EXCEPTION::OUT_OF_MEMORY;
		}
		value = _list.end();
		try
		{
			_map[ptr] = (--value);
		}
		catch (...)
		{
			_list.pop_back();
			throw EXCEPTION::OUT_OF_MEMORY;
		}
	}
#ifdef PLUGIN_DEBUG
	logprintf("CTR<_T>::Add() end");
#endif
}

template <class _T> typename std::list<_T>::iterator CTR<_T>::Delete(_T ptr)
{
#ifdef PLUGIN_DEBUG
	logprintf("CTR<_T>::Delete() call");
#endif
	static typename std::list<_T>::iterator ret = _list.end();
	static typename std::list<_T>::iterator *value;
	try
	{
		ret = _list.erase(*(value = &(_map.at(ptr))));
		(*value) = _list.end();
	}
	catch (...) {}
#ifdef PLUGIN_DEBUG
	logprintf("CTR<_T>::Delete() end");
#endif
	return ret;
}

template <class _T> bool CTR<_T>::Exists(_T ptr)
{
#ifdef PLUGIN_DEBUG
	logprintf("CTR<_T>::Exists() call and end");
#endif
	return _map.find(ptr) == _map.end() ? false : (_map[ptr] != _list.end());
}

template <class _T> void CTR<_T>::Clear()
{
#ifdef PLUGIN_DEBUG
	logprintf("CTR<_T>::Clear() call");
#endif
	_map.clear();
	_list.clear();
#ifdef PLUGIN_DEBUG
	logprintf("CTR<_T>::Clear() end");
#endif
}

template <class _T> void CTR<_T>::CleanUp()
{
#ifdef PLUGIN_DEBUG
	logprintf("CTR<_T>::CleanUp() call");
#endif
	typedef typename std::list<_T>::iterator listit;
	static typename std::map<_T, listit>::iterator _it;
	for (_it = _map.begin(); _it != _map.end(); ++_it)
	{
		map_foreach_begin:
		if (_it->second == _list.end())
		{
			_map.erase(_it);
			if ((_it = _map.begin()) == _map.end()) break;
			goto map_foreach_begin;
		}
	}
#ifdef PLUGIN_DEBUG
	logprintf("CTR<_T>::CleanUp() end");
#endif
}

template <class _T> void CTR<_T>::Destruct()
{
#ifdef PLUGIN_DEBUG
	logprintf("CTR<_T>::Destruct() call");
#endif
	static typename std::list<_T>::iterator _it;
	while ((_it = _list.begin()) != _list.end()) delete (*_it);
#ifdef PLUGIN_DEBUG
	logprintf("CTR<_T>::Destruct() end");
#endif
}

ShellThread::ShellThread(std::string *exec_str) : joinable(false), quit_it(false)
{
#ifdef PLUGIN_DEBUG
	logprintf("ShellThread::ShellThread() call");
#endif
	if (pipe_handle = ETI_popen((*exec_str).c_str(), "r"))
	{
		try
		{
			thread = new std::thread(command_thread, this);
		}
		catch (...)
		{
			throw EXCEPTION::OUT_OF_MEMORY;
		}
	}
	else
	{
		throw EXCEPTION::PIPE_OPEN_FAILED;
	}
#ifdef PLUGIN_DEBUG
	logprintf("ShellThread::ShellThread() end");
#endif
}

ShellThread::~ShellThread()
{
#ifdef PLUGIN_DEBUG
	logprintf("ShellThread::~ShellThread() call");
#endif
	delete thread;
	shell_threads.Delete(this);
#ifdef PLUGIN_DEBUG
	logprintf("ShellThread::~ShellThread() end");
#endif
}

void ShellThread::ThreadedCall()
{
#ifdef PLUGIN_DEBUG
	logprintf("ShellThread::ThreadedCall() call");
#endif
	CMDRet *ret = NULL;
	char buf[BUF_LEN];
	if (pipe_handle)
	{
		while (fgets(buf, BUF_LEN * sizeof(char), pipe_handle))
		{
			try
			{
				ret = new CMDRet;
			}
			catch (...)
			{
				ret = NULL;
			}
			if (ret)
			{
				ret->handle = (cell)this;
				ret->str = buf;
				mtx.lock();
				cmd_rets.push_back(ret);
				mtx.unlock();
			}
			if (quit_it) break;
		}
		ETI_pclose(pipe_handle);
	}
	joinable = true;
#ifdef PLUGIN_DEBUG
	logprintf("ShellThread::ThreadedCall() end");
#endif
}

void ShellThread::CloseHandle()
{
#ifdef PLUGIN_DEBUG
	logprintf("ShellThread::CloseHandle() call");
#endif
	mtx.lock();
	quit_it = true;
	mtx.unlock();
#ifdef PLUGIN_DEBUG
	logprintf("ShellThread::CloseHandle() end");
#endif
}

std::thread *ShellThread::GetThread()
{
#ifdef PLUGIN_DEBUG
	logprintf("ShellThread::GetThread() call");
#endif
	return thread;
#ifdef PLUGIN_DEBUG
	logprintf("ShellThread::GetThread() end");
#endif
}

bool ShellThread::Joinable()
{
#ifdef PLUGIN_DEBUG
	logprintf("ShellThread::Joinable() call");
#endif
	return joinable;
#ifdef PLUGIN_DEBUG
	logprintf("ShellThread::Joinable() end");
#endif
}

static ShellThread *CreateShell(AMX *amx, std::string *exec_str)
{
#ifdef PLUGIN_DEBUG
	logprintf("CreateShell() call");
#endif
	ShellThread *ret = NULL;
	try
	{
		ret = new ShellThread(exec_str);
	}
	catch (...)
	{
		ret = NULL;
	}
	if (ret)
	{
		try
		{
			shell_threads.Add(ret);
		}
		catch (...)
		{
			delete ret;
			ret = NULL;
		}
	}
#ifdef PLUGIN_DEBUG
	logprintf("CreateShell() end");
#endif
	return ret;
}

// native Shell:SHELL_Execute(const cmd[]);
cell AMX_NATIVE_CALL AMX_SHELL_Execute(AMX *amx, cell *params)
{
#ifdef PLUGIN_DEBUG
	logprintf("AMX_SHELL_Execute() call");
#endif
	ShellThread *ret = NULL;
	cell *addr;
	std::string *exec_str = NULL;
	try
	{
		exec_str = new std::string;
	}
	catch (...)
	{
		exec_str = NULL;
	}
	if (exec_str)
	{
		amx_GetAddr(amx, params[1], &addr);
		for (cell *qs = addr; *qs != 0; qs++) (*exec_str) += ((char)(*qs));
		if ((ret = CreateShell(amx, exec_str)) == NULL) delete exec_str;
	}
#ifdef PLUGIN_DEBUG
	logprintf("AMX_SHELL_Execute() end");
#endif
	return (cell)ret;
}

// native SHELL_System(const cmd[]);
cell AMX_NATIVE_CALL AMX_SHELL_System(AMX *amx, cell *params)
{
	std::string exec_str;
	cell *addr;
	amx_GetAddr(amx, params[1], &addr);
	for (cell *qs = addr; *qs != 0; qs++) exec_str += ((char)(*qs));
	return ((cell)(system(exec_str.c_str())));
}

// native SHELL_IsActive(Shell:handle);
cell AMX_NATIVE_CALL AMX_SHELL_IsActive(AMX *amx, cell *params)
{
#ifdef PLUGIN_DEBUG
	logprintf("AMX_SHELL_IsActive() call and end");
#endif
	return (cell)(shell_threads.Exists((ShellThread *)(params[1])));
}

// native SHELL_Release(Shell:handle);
cell AMX_NATIVE_CALL AMX_SHELL_Release(AMX *amx, cell *params)
{
#ifdef PLUGIN_DEBUG
	logprintf("AMX_SHELL_Release() call");
#endif
	if (shell_threads.Exists((ShellThread *)(params[1]))) ((ShellThread *)(params[1]))->CloseHandle();
#ifdef PLUGIN_DEBUG
	logprintf("AMX_SHELL_Release() end");
#endif
	return 1;
}

// native SHELL_ReleaseAll();
cell AMX_NATIVE_CALL AMX_SHELL_ReleaseAll(AMX *amx, cell *params)
{
#ifdef PLUGIN_DEBUG
	logprintf("AMX_SHELL_ReleaseAll() call");
#endif
	list_foreach(ShellThread *, shell_threads._list, shell_threads_it) (*shell_threads_it)->CloseHandle();
#ifdef PLUGIN_DEBUG
	logprintf("AMX_SHELL_ReleaseAll() end");
#endif
	return 1;
}

// native SHELL_MEM_CleanUp();
cell AMX_NATIVE_CALL AMX_SHELL_MEM_CleanUp(AMX *amx, cell *params)
{
#ifdef PLUGIN_DEBUG
	logprintf("AMX_SHELL_CleanUp() call");
#endif
	callbacks.CleanUp();
	shell_threads.CleanUp();
#ifdef PLUGIN_DEBUG
	logprintf("AMX_SHELL_CleanUp() end");
#endif
	return 1;
}
PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports()
{
	return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES | SUPPORTS_PROCESS_TICK;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData)
{
	pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
	logprintf = (logprintf_t)ppData[PLUGIN_DATA_LOGPRINTF];
	logprintf("/====================\\");
	logprintf("| SA:MP Shell Plugin |");
	logprintf("|     Made by BigETI |");
	logprintf("| Loaded!            |");
	logprintf("\\====================/");
	return true;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload()
{
	callbacks.Destruct();
	shell_threads.Destruct();
	logprintf("/====================\\");
	logprintf("| SA:MP Shell Plugin |");
	logprintf("|     Made by BigETI |");
	logprintf("| Unloaded!          |");
	logprintf("\\====================/");
}

AMX_NATIVE_INFO PluginNatives[] =
{
	{ "SHELL_Execute", AMX_SHELL_Execute },
	{ "SHELL_System", AMX_SHELL_System },
	{ "SHELL_IsActive", AMX_SHELL_IsActive },
	{ "SHELL_Release", AMX_SHELL_Release },
	{ "SHELL_ReleaseAll", AMX_SHELL_ReleaseAll },
	{ "SHELL_MEM_CleanUp ", AMX_SHELL_MEM_CleanUp },
	{ 0, 0 }
};

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX *amx)
{
	int ret = 0;
	CallbackInfo *cb_info = NULL;
	try
	{
		cb_info = new CallbackInfo;
	}
	catch (...)
	{
		cb_info = NULL;
	}
	if (cb_info)
	{
		cb_info->amx = amx;
		if (amx_FindPublic(amx, "OnReceiveShellMessage", &(cb_info->orsm_idx))) cb_info->orsm_idx = -1;
		if (amx_FindPublic(amx, "OnReleaseShell", &(cb_info->ors_idx))) cb_info->ors_idx = -1;
		try
		{
			callbacks.Add(cb_info);
		}
		catch (...)
		{
			delete cb_info;
			cb_info = NULL;
		}
		cb_map[amx] = cb_info;
		if (cb_info) ret = amx_Register(amx, PluginNatives, -1);
	}
	return ret;
}

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX *amx)
{
	CallbackInfo *cb_info = cb_map[amx];
	if (cb_info)
	{
		callbacks.Delete(cb_info);
		delete cb_info;
		cb_map.erase(amx);
	}
	callbacks.CleanUp();
	shell_threads.CleanUp();
	return AMX_ERR_NONE;
}

PLUGIN_EXPORT void PLUGIN_CALL ProcessTick()
{
#ifdef PLUGIN_DEBUG
	logprintf("ProcessTick() call");
#endif
	static std::list<CMDRet *>::iterator cmd_rets_it;
	static std::list<CallbackInfo *>::iterator callbacks_it;
	static std::list<ShellThread *>::iterator t_shell_threads_it;
	static cell amx_addr, *phys_addr, retval;
	mtx.lock();
	while ((cmd_rets_it = cmd_rets.begin()) != cmd_rets.end())
	{
		for (callbacks_it = callbacks._list.begin(); callbacks_it != callbacks._list.end(); callbacks_it++)
		{
			if ((*callbacks_it)->orsm_idx != -1)
			{
				amx_PushString((*callbacks_it)->amx, &amx_addr, &phys_addr, (*cmd_rets_it)->str.c_str(), 0, 0);
				amx_Push((*callbacks_it)->amx, (*cmd_rets_it)->handle);
				amx_Exec((*callbacks_it)->amx, &retval, (*callbacks_it)->orsm_idx);
				amx_Release((*callbacks_it)->amx, amx_addr);
			}
		}
		delete (*cmd_rets_it);
		cmd_rets.pop_front();
	}
	mtx.unlock();
	list_foreach(ShellThread *, shell_threads._list, shell_threads_it)
	{
	shell_threads_begin:
		if ((*shell_threads_it)->Joinable())
		{
			(*shell_threads_it)->GetThread()->join();
			for (callbacks_it = callbacks._list.begin(); callbacks_it != callbacks._list.end(); callbacks_it++)
			{
				if ((*callbacks_it)->ors_idx != -1)
				{
					amx_Push((*callbacks_it)->amx, (cell)(*shell_threads_it));
					amx_Exec((*callbacks_it)->amx, &retval, (*callbacks_it)->ors_idx);
				}
			}
			t_shell_threads_it = shell_threads_it;
			t_shell_threads_it++;
			delete (*shell_threads_it);
			shell_threads_it = t_shell_threads_it;
			if (shell_threads_it != shell_threads._list.end()) goto shell_threads_begin;
		}
	}
#ifdef PLUGIN_DEBUG
	logprintf("ProcessTick() end");
#endif
}