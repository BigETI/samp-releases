/*
	Multiple Commands Makro include made by BigETI © 2012
	Inspired by iPLEOMAX's include http://forum.sa-mp.com/showthread.php?t=323862
*/
#define M_CMDsEx(%0,%1,%2,%3,%4,%5);	if(%1[0]&&((%1[0])!='\1'||%1[1]))for(new %2=0,%3=-1,%4[128],%5=strlen(%1);%2<%5;%2++){if(%1[%2]=='/'&&%2+1<%5){if(%3==-1)%3=%2;else{if(%2-%3>1){strmid(%4,%1,%3,%2);CallLocalFunction("OnPlayerCommandText","is",%0,%4);%3=%2;}}}else if(%2+1==%5&&%3!=-1){strmid(%4,%1,%3,%2+1);CallLocalFunction("OnPlayerCommandText","is",%0,%4);}}
#define M_CMDs(%0)	M_CMDsEx(%0,mcmds1,mcmds2,mcmds3)
#define MultiCommands(%0)	M_CMDs(%0)