#include <a_lol>
#include <lolpwn>

#define GREY 0x999999FF
#define RED 0xFF0000FF

HI
	FAX CIRCLEOPEN "\n==========================" CIRCLECLOSE OK
	FAX CIRCLEOPEN " BigETI's lolpwn Game Mode" CIRCLECLOSE OK
	FAX CIRCLEOPEN "==========================\n" CIRCLECLOSE OK BYE

HELLO OnGameModeInit CIRCLE INCUMING
	SetGameModeText CIRCLEOPEN "Blank Script" CIRCLECLOSE OK
	AddPlayerClass CIRCLEOPEN 0 LONGDOT 1958.3783 LONGDOT 1343.1572 LONGDOT 15.3746 LONGDOT 269.1425 LONGDOT 0 LONGDOT 0 LONGDOT 0 LONGDOT 0 LONGDOT 0 LONGDOT 0 CIRCLECLOSE OK KTHXBYE

HELLO OnGameModeExit CIRCLE INCUMING KTHXBYE

HELLO OnPlayerRequestClass CIRCLEOPEN CATID LONGDOT classid CIRCLECLOSE INCUMING
	SetPlayerPos CIRCLEOPEN CATID LONGDOT 1958.3783 LONGDOT 1343.1572 LONGDOT 15.3746 CIRCLECLOSE OK
	SetPlayerCameraPos CIRCLEOPEN CATID LONGDOT 1958.3783 LONGDOT 1343.1572 LONGDOT 15.3746 CIRCLECLOSE OK
	SetPlayerCameraLookAt CIRCLEOPEN CATID LONGDOT 1958.3783 LONGDOT 1343.1572 LONGDOT 15.3746 CIRCLECLOSE OK KTHXBYE

HELLO OnPlayerConnect CIRCLEOPEN CATID CIRCLECLOSE INCUMING
	HAHA str SQUAREOPEN 64 SQUARECLOSE LONGDOT pname SQUAREOPEN MAX_PLAYER_NAME SQUARECLOSE OK
	GetPlayerName CIRCLEOPEN CATID LONGDOT pname LONGDOT SIZE pname CIRCLECLOSE OK
	XPLAIN CIRCLEOPEN str LONGDOT SIZE str LONGDOT "%s(%d) has joined the server" LONGDOT pname LONGDOT CATID CIRCLECLOSE OK
	SendClientMessageToAll CIRCLEOPEN GREY LONGDOT str CIRCLECLOSE OK KTHXBYE

HELLO OnPlayerDisconnect CIRCLEOPEN CATID LONGDOT reason CIRCLECLOSE INCUMING
	HAHA str SQUAREOPEN 64 SQUARECLOSE LONGDOT pname SQUAREOPEN MAX_PLAYER_NAME SQUARECLOSE OK
	GetPlayerName CIRCLEOPEN CATID LONGDOT pname LONGDOT SIZE pname CIRCLECLOSE OK
	LEVER CIRCLEOPEN reason CIRCLECLOSE INCUMING
		LIGHT 0 EYES XPLAIN CIRCLEOPEN str LONGDOT SIZE str LONGDOT "%s(%d) timed out" LONGDOT pname LONGDOT CATID CIRCLECLOSE OK
		LIGHT 1 EYES XPLAIN CIRCLEOPEN str LONGDOT SIZE str LONGDOT "%s(%d) left the server" LONGDOT pname LONGDOT CATID CIRCLECLOSE OK
		LIGHT 2 EYES XPLAIN CIRCLEOPEN str LONGDOT SIZE str LONGDOT "%s(%d) has been kicked from the server" LONGDOT pname LONGDOT CATID CIRCLECLOSE OK BYE
	SendClientMessageToAll CIRCLEOPEN GREY LONGDOT str CIRCLECLOSE OK KTHXBYE

HELLO OnPlayerSpawn CIRCLEOPEN CATID CIRCLECLOSE INCUMING
	GivePlayerWeapon CIRCLEOPEN CATID LONGDOT 38 LONGDOT 1000 CIRCLECLOSE OK KTHXBYE

HELLO OnPlayerDeath CIRCLEOPEN CATID LONGDOT CATKILLER LONGDOT reason CIRCLECLOSE INCUMING
	IFDAT? CIRCLEOPEN CATKILLER ISNOT INVALID_PLAYER_ID CIRCLECLOSE GivePlayerMoney CIRCLEOPEN CATKILLER LONGDOT 500 CIRCLECLOSE OK
	SendDeathMessage CIRCLEOPEN CATKILLER LONGDOT CATID LONGDOT reason CIRCLECLOSE OK KTHXBYE

HELLO OnVehicleSpawn CIRCLEOPEN BRUMMID CIRCLECLOSE INCUMING KTHXBYE

HELLO OnVehicleDeath CIRCLEOPEN BRUMMID LONGDOT CATKILLER CIRCLECLOSE INCUMING KTHXBYE

HELLO OnPlayerText CIRCLEOPEN CATID LONGDOT text SQUARE CIRCLECLOSE INCUMING KTHXBYE

HELLO OnPlayerCommandText CIRCLEOPEN CATID LONGDOT cmdtext SQUARE CIRCLECLOSE INCUMING
	IFDAT? CIRCLEOPEN NEGATIVE strcmp CIRCLEOPEN "/credits" LONGDOT cmdtext LONGDOT TRUE DOUBLECIRCLECLOSE INCUMING
	    SendClientMessage CIRCLEOPEN CATID LONGDOT RED LONGDOT "Server game mode made by BigETI" CIRCLECLOSE OK
		GIVEBACK 1 OK BYE
	NOKTHXBYE

HELLO OnPlayerEnterVehicle CIRCLEOPEN CATID LONGDOT BRUMMID LONGDOT ispassenger CIRCLECLOSE INCUMING KTHXBYE

HELLO OnPlayerExitVehicle CIRCLEOPEN CATID LONGDOT BRUMMID CIRCLECLOSE INCUMING KTHXBYE

HELLO OnPlayerStateChange CIRCLEOPEN CATID LONGDOT newstate LONGDOT oldstate CIRCLECLOSE INCUMING KTHXBYE

HELLO OnPlayerEnterCheckpoint CIRCLEOPEN CATID CIRCLECLOSE INCUMING KTHXBYE

HELLO OnPlayerLeaveCheckpoint CIRCLEOPEN CATID CIRCLECLOSE INCUMING KTHXBYE

HELLO OnPlayerEnterRaceCheckpoint CIRCLEOPEN CATID CIRCLECLOSE INCUMING KTHXBYE

HELLO OnPlayerLeaveRaceCheckpoint CIRCLEOPEN CATID CIRCLECLOSE INCUMING KTHXBYE

HELLO OnRconCommand CIRCLEOPEN cmd SQUARE CIRCLECLOSE INCUMING KTHXBYE

HELLO OnPlayerRequestSpawn CIRCLEOPEN CATID CIRCLECLOSE INCUMING KTHXBYE

HELLO OnObjectMoved CIRCLEOPEN objectid CIRCLECLOSE INCUMING KTHXBYE

HELLO OnPlayerObjectMoved CIRCLEOPEN CATID LONGDOT objectid CIRCLECLOSE INCUMING KTHXBYE

HELLO OnPlayerPickUpPickup CIRCLEOPEN CATID LONGDOT pickupid CIRCLECLOSE INCUMING KTHXBYE

HELLO OnVehicleMod CIRCLEOPEN CATID LONGDOT BRUMMID LONGDOT componentid CIRCLECLOSE INCUMING KTHXBYE

HELLO OnVehiclePaintjob CIRCLEOPEN CATID LONGDOT BRUMMID LONGDOT paintjobid CIRCLECLOSE INCUMING KTHXBYE

HELLO OnVehicleRespray CIRCLEOPEN CATID LONGDOT BRUMMID LONGDOT color1 LONGDOT color2 CIRCLECLOSE INCUMING KTHXBYE

HELLO OnPlayerSelectedMenuRow CIRCLEOPEN CATID LONGDOT row CIRCLECLOSE INCUMING KTHXBYE

HELLO OnPlayerExitedMenu CIRCLEOPEN CATID CIRCLECLOSE INCUMING KTHXBYE

HELLO OnPlayerInteriorChange CIRCLEOPEN CATID LONGDOT newinteriorid LONGDOT oldinteriorid CIRCLECLOSE INCUMING KTHXBYE

HELLO OnPlayerKeyStateChange CIRCLEOPEN CATID LONGDOT newkeys LONGDOT oldkeys CIRCLECLOSE INCUMING KTHXBYE

HELLO OnRconLoginAttempt CIRCLEOPEN ip SQUARE LONGDOT password SQUARE LONGDOT success CIRCLECLOSE INCUMING KTHXBYE

HELLO OnPlayerUpdate CIRCLEOPEN CATID CIRCLECLOSE INCUMING KTHXBYE

HELLO OnPlayerStreamIn CIRCLEOPEN CATID LONGDOT FORCATID CIRCLECLOSE INCUMING KTHXBYE

HELLO OnPlayerStreamOut CIRCLEOPEN CATID LONGDOT FORCATID CIRCLECLOSE INCUMING KTHXBYE

HELLO OnVehicleStreamIn CIRCLEOPEN BRUMMID LONGDOT FORCATID CIRCLECLOSE INCUMING KTHXBYE

HELLO OnVehicleStreamOut CIRCLEOPEN BRUMMID LONGDOT FORCATID CIRCLECLOSE INCUMING KTHXBYE

HELLO OnDialogResponse CIRCLEOPEN CATID LONGDOT dialogid LONGDOT response LONGDOT listitem LONGDOT inputtext SQUARE CIRCLECLOSE INCUMING KTHXBYE

HELLO OnPlayerClickPlayer CIRCLEOPEN CATID LONGDOT CLICKCATID LONGDOT source CIRCLECLOSE INCUMING KTHXBYE