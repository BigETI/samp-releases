#define FILTERSCRIPT
#include <a_samp>
#define MAX_MINUTES 60
#define MAX_HOURS	24
new Text:Clock, gTime[2];
stock UpdateTime()
{
	new tstr[10];
	format(tstr, 10, "%02d:%02d", gTime[0], gTime[1]);
	TextDrawSetString(Clock, tstr);
	for(new playerid = 0; playerid < MAX_PLAYERS; playerid++) if(IsPlayerConnected(playerid)) SetPlayerTime(playerid, gTime[0], gTime[1]);
}
forward Tick();
public OnFilterScriptInit()
{
	Clock = TextDrawCreate(547.0, 24.0, "--:--");
	TextDrawLetterSize(Clock, 0.6, 2.0);
	TextDrawFont(Clock, 3);
	TextDrawSetOutline(Clock, 2);
	gTime[0] = random(MAX_HOURS);
	gTime[1] = random(MAX_MINUTES);
	UpdateTime();
	TextDrawShowForAll(Clock);
	SetTimer("Tick", 1000, true);
	return 1;
}
public OnFilterScriptExit()
{
	TextDrawDestroy(Clock);
	return 1;
}
public OnPlayerConnect(playerid)
{
	TextDrawShowForPlayer(playerid, Clock);
	return 1;
}
public Tick()
{
	new tTime[2];
	tTime[0] = gTime[0];
	tTime[1] = gTime[1]+1;
	if(tTime[1] >= MAX_MINUTES)
	{
		tTime[1] = 0;
		tTime[0]++;
	}
	if(tTime[0] >= MAX_HOURS) tTime[0] = 0;
	gTime[0] = tTime[0];
	gTime[1] = tTime[1];
	UpdateTime();
}
