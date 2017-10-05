/*
//////////////////////////////////////////////////////
//==================================================//
//== Static Dialogs include made by BigETI © 2011 ==//
//==================================================//
//== You are allowed to edit this include ==========//
//== but not release it without my permissions! ====//
//==================================================//
//== File name: sdialog.inc ========================//
//== Autor: Ethem Kurt © ===========================//
//== Release Date: 24.10.2011 ======================//
//== Version: V1 ===================================//
//== Lines: 79 =====================================//
//== File size: 3,52 KB ============================//
//==================================================//
//////////////////////////////////////////////////////
*/
#if defined _BIGETI_STATIC_DIALOGS
	#endinput
#endif
#define _BIGETI_STATIC_DIALOGS
#pragma library					sdialog
#include <a_samp>
#define MAX_STATIC_DIALOGS		128
#define MAX_STATIC_D_CAPTION	32
#define MAX_STATIC_D_INFO		1024
#define MAX_STATIC_D_BUTTON		16
enum S_DialogInfos
{
	bool:S_DialogInUse,
	S_DialogStyle,
	S_DialogCaption[MAX_STATIC_D_CAPTION],
	S_DialogInfo[MAX_STATIC_D_INFO],
	S_DialogButton1[MAX_STATIC_D_BUTTON],
	S_DialogButton2[MAX_STATIC_D_BUTTON],
}
new S_Dialog[MAX_STATIC_DIALOGS][S_DialogInfos];
stock SetStaticDialog(dialogid, style, caption[], info[], button1[], button2[])
{
	if(IsValidStaticDialog(dialogid))
	{
		S_Dialog[dialogid][S_DialogStyle] = style;
		format(S_Dialog[dialogid][S_DialogCaption], MAX_STATIC_D_CAPTION, caption);
		format(S_Dialog[dialogid][S_DialogInfo], MAX_STATIC_D_INFO, info);
		format(S_Dialog[dialogid][S_DialogButton1], MAX_STATIC_D_BUTTON, button1);
		format(S_Dialog[dialogid][S_DialogButton2], MAX_STATIC_D_BUTTON, button2);
		S_Dialog[dialogid][S_DialogInUse] = true;
		return true;
	}
	return false;
}
stock RemoveStaticDialog(dialogid)
{
	if(IsStaticDialog(dialogid))
	{
		S_Dialog[dialogid][S_DialogStyle] = 0;
		format(S_Dialog[dialogid][S_DialogCaption], MAX_STATIC_D_CAPTION, "");
		format(S_Dialog[dialogid][S_DialogInfo], MAX_STATIC_D_INFO, "");
		format(S_Dialog[dialogid][S_DialogButton1], MAX_STATIC_D_BUTTON, "");
		format(S_Dialog[dialogid][S_DialogButton2], MAX_STATIC_D_BUTTON, "");
		S_Dialog[dialogid][S_DialogInUse] = false;
		return true;
	}
	return false;
}
stock ShowPlayerStaticDialog(playerid, dialogid) if(IsStaticDialog(dialogid)) ShowPlayerDialog(playerid, dialogid, S_Dialog[dialogid][S_DialogStyle], S_Dialog[dialogid][S_DialogCaption], S_Dialog[dialogid][S_DialogInfo], S_Dialog[dialogid][S_DialogButton1], S_Dialog[dialogid][S_DialogButton2]);
stock IsStaticDialog(dialogid) return IsValidStaticDialog(dialogid) ? S_Dialog[dialogid][S_DialogInUse] : false;
stock IsValidStaticDialog(dialogid)	return (dialogid >= 0 && dialogid < MAX_STATIC_DIALOGS) ? true : false;
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
