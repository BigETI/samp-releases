/*
//////////////////////////////////////////////////////
//==================================================//
//== Text Processor include made by BigETI © 2011 ==//
//==================================================//
//== You are not allowed to edit this include ======//
//== and/or release it without my permissions! =====//
//==================================================//
//== File name: btxt.inc ===========================//
//== Autor: Ethem Kurt © ===========================//
//== Release Date: 21.11.2011 ======================//
//== Version: V1 ===================================//
//== Lines: 108 ====================================//
//== File size: 4,21 KB ============================//
//==================================================//
//////////////////////////////////////////////////////

||=================================================================================================================||
||	IMPORTANT: Define FILTERSCRIPT on top of your script to verify if you are using a filterscript or a gamemode!  ||
||=================================================================================================================||
*/
#if defined _TXT_INCLUDE
	#endinput
#endif
#define _TXT_INCLUDE
#include <a_samp>
#define TEXT:%0(%1)	forward txt_%0(%1);\
	public txt_%0(%1)
#define TXT:%0(%1) TEXT:%0(%1)
new bool:TXT_OPT;
#if defined FILTERSCRIPT
public OnFilterScriptInit
#else
public OnGameModeInit()
#endif
{
	TXT_OPT = (funcidx("TXT_OnPlayerText") != -1);
#if defined FILTERSCRIPT
	return (funcidx("TXT_OnFilterScriptInit") != -1 ? CallLocalFunction("TXT_OnFilterScriptInit", "") : 1);
#else
	return (funcidx("TXT_OnGameModeInit") != -1 ? CallLocalFunction("TXT_OnGameModeInit", "") : 1);
}
#if defined FILTERSCRIPT
	#if defined _ALS_OnFilterScriptInit
		#undef OnFilterScriptInit
	#else
		#define _ALS_OnFilterScriptInit
	#endif
	#define OnFilterScriptInit TXT_OnFilterScriptInit
forward TXT_OnFilterScriptInit();
#else
	#if defined _ALS_OnGameModeInit
		#undef OnGameModeInit
	#else
		#define _ALS_OnGameModeInit
	#endif
	#define OnGameModeInit TXT_OnGameModeInit
forward TXT_OnGameModeInit();
#endif
public OnPlayerText(playerid, text[])
{
	if((!(text[0])) || (((text[0]) == '\1') && (!(text[1])))) return (TXT_OPT ? CallLocalFunction("TXT_OnPlayerText", "ds", playerid, "\1") : 1);
	new funcstr[24], text2[20], textlen = strlen(text), pos = -1;
	if(textlen > 1)
	{
		for(new i = 0; i < textlen; i++)
		{
			if(text[i] == ' ')
			{
				if(i+1 < textlen)
				{
					pos = i;
					strmid(text2, text, 0, pos);
					for(new j = 0; j < strlen(text2); j++) text2[j] = tolower(text2[j]);
					format(funcstr, 24, "txt_%s", text2);
				}
				else text[i] = '\0';
				break;
			}
		}
	}
	if(pos == -1)
	{
		for(new i = 0; i < 20 && i < textlen; i++) text2[i] = tolower(text[i]);
		format(funcstr, 24, "txt_%s", text2);
		return (funcidx(funcstr) != -1 ? (CallLocalFunction(funcstr, "ds", playerid, "\1") != 0 ? (TXT_OPT ? CallLocalFunction("TXT_OnPlayerText", "ds", playerid, text) : 1) : 0) : (TXT_OPT ? CallLocalFunction("TXT_OnPlayerText", "ds", playerid, text) : 1));
	}
	return (funcidx(funcstr) != -1 ? (CallLocalFunction(funcstr, "ds", playerid, text[pos+1]) != 0 ? (TXT_OPT ? CallLocalFunction("TXT_OnPlayerText", "ds", playerid, text) : 1) : 0) : (TXT_OPT ? CallLocalFunction("TXT_OnPlayerText", "ds", playerid, text) : 1));
}
#if defined _ALS_OnPlayerText
	#undef OnPlayerText
#else
	#define _ALS_OnPlayerText
#endif
#define OnPlayerText TXT_OnPlayerText
forward TXT_OnPlayerText(playerid, text[]);

/*
ETIETIETIETI  	ETI		    ETIETIETIETI	BigBigBigBig	BigBigBigBigBig		Big
ETI       ETI 	ETI		  ETI           	Big         	      Big      		Big
ETI        ETI	ETI		 ETI            	Big         	      Big      		Big
ETI       ETI 	ETI		ETI             	Big         	      Big      		Big
ETIETIETIETI  	ETI		ETI    ETIETIETI	BigBigBig   	      Big      		Big
ETI       ETI 	ETI		ETI          ETI	Big         	      Big      		Big
ETI        ETI	ETI		 ETI         ETI	Big         	      Big      		Big
ETI       ETI 	ETI		  ETI        ETI	Big         	      Big      		Big
ETIETIETIETI  	ETI		    ETIETIETIETI	BigBigBigBig	      Big      		Big
*/
