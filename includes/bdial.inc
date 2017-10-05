/*
/////////////////////////////////////////////////////////////////
//=============================================================//
//== Dialog Response Processor include made by BigETI © 2011 ==//
//=============================================================//
//== You are not allowed to edit this include =================//
//== and/or release it without my permissions! ================//
//=============================================================//
//== File name: bdial.inc =====================================//
//== Autor: Ethem Kurt © ======================================//
//== Release Date: 04.11.2011 =================================//
//== Version: V1.0.2 ==========================================//
//== Lines: 90 ================================================//
//== File size: 3,93 KB =======================================//
//=============================================================//
/////////////////////////////////////////////////////////////////

||===================================================================================================================||
||	IMPORTANT: Define FILTERSCRIPT on top of your script to verify if you are yousing a filterscript or a gamemode!  ||
||===================================================================================================================||
*/

//Do not edit these things below!
#if defined _BIGETI_DIALOG_RESPONSE
	#endinput
#endif	
#define _BIGETI_DIALOG_RESPONSE
#define DIALOG:%0(%1)\
	forward dial_%0(%1);\
	public dial_%0(%1)
#define DIAL:%0(%1)\
	DIALOG:%0(%1)
new bool:DIAL_ODR;
#if defined FILTERSCRIPT
public OnFilterScriptInit()
#else
public OnGameModeInit()
#endif
{
	DIAL_ODR = (funcidx("Dial_OnDialogResponse") != -1);
#if defined FILTERSCRIPT
	return (funcidx("Dial_OnFilterScriptInit") != -1 ? CallLocalFunction("Dial_OnFilterScriptInit", "") : 1);
#else
	return (funcidx("Dial_OnGameModeInit") != -1 ? CallLocalFunction("Dial_OnGameModeInit", "") : 1);
#endif
}
#if defined FILTERSCRIPT
	#if defined _ALS_OnFilterScriptInit
		#undef OnFilterScriptInit
	#else
		#define _ALS_OnFilterScriptInit
	#endif
	#define OnFilterScriptInit Dial_OnFilterScriptInit
forward Dial_OnFilterScriptInit();
#else
	#if defined _ALS_OnGameModeInit
		#undef OnGameModeInit
	#else
		#define _ALS_OnGameModeInit
	#endif
	#define OnGameModeInit Dial_OnGameModeInit
forward Dial_OnGameModeInit();
#endif

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	new bdialstr[24];
	format(bdialstr, 24, "dial_%d", dialogid);
	if((!(inputtext[0])) || (((inputtext[0]) == '\1') && (!(inputtext[1])))) return (CallLocalFunction(bdialstr, "dlds", playerid, !!response, listitem, "\1") == 0 ? (DIAL_ODR ? CallLocalFunction("Dial_OnDialogResponse", "dddds", playerid, dialogid, response, listitem, "\1") : 0) : 1);
	return (CallLocalFunction(bdialstr, "dlds", playerid, !!response, listitem, inputtext) == 0 ? (DIAL_ODR ? CallLocalFunction("Dial_OnDialogResponse", "dddds", playerid, dialogid, response, listitem, inputtext) : 0) : 1);
}
#if defined _ALS_OnDialogResponse
	#undef OnDialogResponse
#else
	#define _ALS_OnDialogResponse
#endif
#define OnDialogResponse Dial_OnDialogResponse
forward Dial_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);

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
