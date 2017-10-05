/*
	BStreamer include made by BigETI © 2012

	Defines:
		- USE_MAP_FILES
		- LIMIT_B_OBJECTS
		- MAX_B_OBJECTS
		- B_OBJECT_STREAM_DISTANCE
		- B_OBJECT_TICK
		- USE_CAMERA_STREAM


	Callbacks:

		- OnBObjectStreamIn(playerid, bobjectid, pobjectid)
		- OnBObjectStreamOut(playerid, bobjectid, pobjectid)
		- OnBObjectMoved(bobjectid)


	Stocks:

		- CreateBObject(modelid, Float:X, Float:Y, Float:Z, Float:rX, Float:rY, Float:rZ, Float:DrawDistance = B_OBJECT_STREAM_DISTANCE, worldid = -1, interiorid = -1, playerid = -1)
		- DestroyBObject(bobjectid)
		- DestroyAllBObjects(single_vworld = -1)
		- SetBObjectPos(bobjectid, Float:X, Float:Y, Float:Z)
		- SetBObjectPosEx(bobjectid, Float:X, Float:Y, Float:Z, Float:rX, Float:rY, Float:rZ)
		- GetBObjectPos(bobjectid, &Float:X, &Float:Y, &Float:Z)
		- GetBObjectPosEx(bobjectid, &Float:X, &Float:Y, &Float:Z, &Float:rX, &Float:rY, &Float:rZ)
		- SetBObjectRot(bobjectid, Float:rX, Float:rY, Float:rZ)
		- GetBObjectRot(bobjectid, &Float:rX, &Float:rY, &Float:rZ)
		- bStream_SetUpdate(updatetime = B_OBJECT_TICK)
		- AssignBObjectForVirtualWorld(bobjectid, worldid = -1)
		- AssignBObjectForInterior(bobjectid, interiorid = -1)
		- AssignBObjectForPlayer(bobjectid, playerid = -1)
		- MoveBObject(bobjectid, Float:X, Float:Y, Float:Z, Float:speed, Float:rX = -1000.0, Float:rY = -1000.0, Float:rZ = -1000.0)
		- StopBObject(bobjectid)
		- AttachCameraToBObject(playerid, bobjectid)
		- SaveBMap(const file_name[], bool:use_vworld = false, vworld = -1)
		- LoadBMap(const file_name[], bool:error_clear = true, bool:use_vworld = false, vworld = -1)
		- SavePWN(const file_name[], bool:use_vworld = false, vworld = -1)
		- LoadPWN(const file_name[], bool:error_clear = true, bool:use_vworld = false, vworld = -1)
		- BMap_To_PWN(bmap_fname[], pwn_fname[], bool:error_clear = true, bool:use_single_vworld = false, single_vworld = -1)
		- PWN_To_BMap(pwn_fname[], bmap_fname[], bool:use_single_vworld = false, single_vworld = -1)
		- CreateBVehicle(vehicletype, Float:x, Float:y, Float:z, Float:rotation, color1, color2, respawn_delay, interior = 0, vworld = 0)
		- DestroyBVehicle(vehicleid)
		- DestroyAllBVehicles(bool:use_vworld = false, vworld = 0)
		- GetBVehicleColors(vehicleid, &color1, &color2)
		- GetBVehicleData(vehicleid, &color1, &color2, &respawn_delay, &interior)
		- IsCameraInRangeOfPoint(playerid, Float:range, Float:X, Float:Y, Float:Z)


	Macros:

		- IsValidBObject(bobjectid)
		- IsBObjectMoving(bobjectid)
		- IsValidBVehicle(vehicleid)
		- GetBVehicleColor1(vehicleid)
		- GetBVehicleColor2(vehicleid)
		- GetBVehicleResDelay(vehicleid)
		- GetBVehicleInterior(vehicleid)

*/
#if !defined LIMIT_B_OBJECTS
	#define LIMIT_B_OBJECTS				(400)
#endif
#if !defined MAX_B_OBJECTS
	#define MAX_B_OBJECTS				(2000)
#endif
#if !defined B_OBJECT_STREAM_DISTANCE
	#define B_OBJECT_STREAM_DISTANCE	(200.0)
#endif
#if !defined B_OBJECT_TICK
	#define B_OBJECT_TICK				(100)
#endif

#if defined B_STREAMER_INCLUDED_
	#endinput
#endif
#define B_STREAMER_INCLUDED_
#include <a_samp>
#include <foreach>
#if defined USE_MAP_FILES
	#tryinclude <sscanf2>
#endif
#define IsValidBObject(%0)	(((%0)>=0&&(%0)<MAX_B_OBJECTS)?bStream[(%0)][bStream_Is]:false)
#define IsBObjectMoving(%0)	(((%0)>=0&&(%0)<MAX_B_OBJECTS)?bStream[(%0)][bStream_Moving]:false)
#define IsValidBVehicle(%0)	(((%0)>0&&(%0)<=MAX_VEHICLES)?bVStream[(%0)-1][bVStream_Is]:false)
#define GetBVehicleColor1(%0) (((%0)>0&&(%0)<=MAX_VEHICLES)?bVStream[(%0)-1][bVStream_Color1]:0)
#define GetBVehicleColor2(%0) (((%0)>0&&(%0)<=MAX_VEHICLES)?bVStream[(%0)-1][bVStream_Color2]:0)
#define GetBVehicleResDelay(%0) (((%0)>0&&(%0)<=MAX_VEHICLES)?bVStream[(%0)-1][btVStream_Respawn]:0)
#define GetBVehicleInterior(%0) (((%0)>0&&(%0)<=MAX_VEHICLES)?bVStream[(%0)-1][bVStream_Interior]:0)

enum bStreamInfos
{
	bool:bStream_Is,
	bStream_Model,
	Float:bStream_X,
	Float:bStream_Y,
	Float:bStream_Z,
	Float:bStream_rX,
	Float:bStream_rY,
	Float:bStream_rZ,
	Float:bStream_DrawDistance,
	bStream_VWorld,
	bStream_Interior,
	bStream_PlayerID,
	bool:bStream_Moving,
	bStream_MoveTick,
	Float:bStream_toX,
	Float:bStream_toY,
	Float:bStream_toZ,
	Float:bStream_toRX,
	Float:bStream_toRY,
	Float:bStream_toRZ,
	Float:bStream_Speed,
	bStream_MoveTime,
	bStream_MoveTimer,
	bStream_pObjectID[MAX_PLAYERS],
	bool:bStream_pTryAttachCam[MAX_PLAYERS]
};

enum btStreamInfos
{
	btStream_Model,
	Float:btStream_X,
	Float:btStream_Y,
	Float:btStream_Z,
	Float:btStream_rX,
	Float:btStream_rY,
	Float:btStream_rZ,
	Float:btStream_DrawDistance,
	btStream_VWorld,
	btStream_Interior,
	btStream_PlayerID,
};

enum bVStreamInfos
{
	bool:bVStream_Is,
	bVStream_Color1,
	bVStream_Color2,
	bVStream_Respawn,
	bVStream_Interior,
}

enum btVStreamInfos
{
	btVStream_Model,
	Float:btVStream_X,
	Float:btVStream_Y,
	Float:btVStream_Z,
	Float:btVStream_rZ,
	btVStream_Color1,
	btVStream_Color2,
	btVStream_Respawn,
	btVStream_Interior,
	btVStream_VWorld,
}

new bStreamTimer, bStream[MAX_B_OBJECTS][bStreamInfos], bStreamCallBacks, Iterator:Iter_BObject<MAX_B_OBJECTS>, Iterator:Iter_BVehicle<MAX_B_OBJECTS>, bStream_Max = 0, bVStream[MAX_VEHICLES][bVStreamInfos];

forward bStream_Update();
forward OnBObjectStreamIn(playerid, bobjectid, pobjectid);
forward OnBObjectStreamOut(playerid, bobjectid, pobjectid);
forward OnBObjectMoved(bobjectid);

stock CreateBObject(modelid, Float:X, Float:Y, Float:Z, Float:rX, Float:rY, Float:rZ, Float:DrawDistance = B_OBJECT_STREAM_DISTANCE, worldid = -1, interiorid = -1, playerid = -1)
{
	for(new i = 0; i < bStream_Max+1; i++)
	{
		if(bStream[i][bStream_Is]) continue;
		bStream[i][bStream_Model] = modelid;
		bStream[i][bStream_X] = X;
		bStream[i][bStream_Y] = Y;
		bStream[i][bStream_Z] = Z;
		bStream[i][bStream_rX] = rX;
		bStream[i][bStream_rY] = rY;
		bStream[i][bStream_rZ] = rZ;
		bStream[i][bStream_DrawDistance] = DrawDistance;
		bStream[i][bStream_VWorld] = worldid;
		bStream[i][bStream_Interior] = interiorid;
		bStream[i][bStream_PlayerID] = playerid;
		bStream[i][bStream_Is] = true;
		if(i >= bStream_Max) bStream_Max = i+1;
		Iter_Add(Iter_BObject, i);
		return i;
	}
	return -1;
}

stock DestroyBObject(bobjectid)
{
	if(bobjectid < 0 || bobjectid >= MAX_B_OBJECTS) return false;
	if(!bStream[bobjectid][bStream_Is]) return false;
	bStream[bobjectid][bStream_Is] = false;
	bStream[bobjectid][bStream_Moving] = false;
	new pobj;
	foreach(Player, playerid)
	{
		if((pobj = bStream[bobjectid][bStream_pObjectID][playerid]) == -1) continue;
		bStream[bobjectid][bStream_pObjectID][playerid] = -1;
		DestroyPlayerObject(playerid, pobj);
	}
	return true;
}

stock DestroyAllBObjects(single_vworld = -1)
{
	if(single_vworld != -1)
	{
		new pobj = -1;
		foreach(Iter_BObject, i)
		{
			if(!bStream[i][bStream_Is]) continue;
			if(bStream[i][bStream_VWorld] != single_vworld) continue;
			bStream[i][bStream_Is] = false;
			bStream[i][bStream_Moving] = false;
			foreach(Player, playerid)
			{
				if((pobj = bStream[i][bStream_pObjectID][playerid]) == -1) continue;
				bStream[i][bStream_pObjectID][playerid] = -1;
				DestroyPlayerObject(playerid, pobj);
			}
		}
	}
	else
	{
		new pobj = -1;
		for(new i = 0; i < MAX_B_OBJECTS; i++)
		{
			if(!bStream[i][bStream_Is]) continue;
			bStream[i][bStream_Is] = false;
			bStream[i][bStream_Moving] = false;
			foreach(Player, playerid)
			{
				if((pobj = bStream[i][bStream_pObjectID][playerid]) == -1) continue;
				bStream[i][bStream_pObjectID][playerid] = -1;
				DestroyPlayerObject(playerid, pobj);
			}
		}
	}
}

stock SetBObjectPos(bobjectid, Float:X, Float:Y, Float:Z)
{
	if(bobjectid < 0 || bobjectid >= MAX_B_OBJECTS) return false;
	if(!bStream[bobjectid][bStream_Is]) return false;
	bStream[bobjectid][bStream_X] = X;
	bStream[bobjectid][bStream_Y] = Y;
	bStream[bobjectid][bStream_Z] = Z;
	foreach(Player, playerid)
	{
		if(bStream[bobjectid][bStream_pObjectID][playerid] == -1) continue;
		SetPlayerObjectPos(playerid, bStream[bobjectid][bStream_pObjectID][playerid], X, Y, Z);
	}
	return true;
}

stock SetBObjectPosEx(bobjectid, Float:X, Float:Y, Float:Z, Float:rX, Float:rY, Float:rZ)
{
	if(bobjectid < 0 || bobjectid >= MAX_B_OBJECTS) return false;
	if(!bStream[bobjectid][bStream_Is]) return false;
	bStream[bobjectid][bStream_X] = X;
	bStream[bobjectid][bStream_Y] = Y;
	bStream[bobjectid][bStream_Z] = Z;
	bStream[bobjectid][bStream_rX] = rX;
	bStream[bobjectid][bStream_rY] = rY;
	bStream[bobjectid][bStream_rZ] = rZ;
	foreach(Player, playerid)
	{
		if(bStream[bobjectid][bStream_pObjectID][playerid] == -1) continue;
		SetPlayerObjectRot(playerid, bStream[bobjectid][bStream_pObjectID][playerid], rX, rY, rZ);
		SetPlayerObjectPos(playerid, bStream[bobjectid][bStream_pObjectID][playerid], X, Y, Z);
	}
	return true;
}

stock GetBObjectPos(bobjectid, &Float:X, &Float:Y, &Float:Z)
{
	if(bobjectid < 0 || bobjectid >= MAX_B_OBJECTS) return;
	if(!bStream[bobjectid][bStream_Is]) return;
	if(bStream[bobjectid][bStream_Moving])
	{
		new tick = GetTickCount()-bStream[bobjectid][bStream_MoveTick];
		X = bStream[bobjectid][bStream_X]+floatmul(floatdiv(bStream[bobjectid][bStream_toX]-bStream[bobjectid][bStream_X], bStream[bobjectid][bStream_MoveTime]), tick);
		Y = bStream[bobjectid][bStream_Y]+floatmul(floatdiv(bStream[bobjectid][bStream_toY]-bStream[bobjectid][bStream_Y], bStream[bobjectid][bStream_MoveTime]), tick);
		Z = bStream[bobjectid][bStream_Z]+floatmul(floatdiv(bStream[bobjectid][bStream_toZ]-bStream[bobjectid][bStream_Z], bStream[bobjectid][bStream_MoveTime]), tick);
	}
	else
	{
		X = bStream[bobjectid][bStream_X];
		Y = bStream[bobjectid][bStream_Y];
		Z = bStream[bobjectid][bStream_Z];
	}
}

stock GetBObjectPosEx(bobjectid, &Float:X, &Float:Y, &Float:Z, &Float:rX, &Float:rY, &Float:rZ)
{
	if(bobjectid < 0 || bobjectid >= MAX_B_OBJECTS) return;
	if(!bStream[bobjectid][bStream_Is]) return;
	new tick = GetTickCount()-bStream[bobjectid][bStream_MoveTick];
	if(bStream[bobjectid][bStream_Moving] && tick < bStream[bobjectid][bStream_MoveTime])
	{
		X = bStream[bobjectid][bStream_X]+floatmul(floatdiv(bStream[bobjectid][bStream_toX]-bStream[bobjectid][bStream_X], bStream[bobjectid][bStream_MoveTime]), tick);
		Y = bStream[bobjectid][bStream_Y]+floatmul(floatdiv(bStream[bobjectid][bStream_toY]-bStream[bobjectid][bStream_Y], bStream[bobjectid][bStream_MoveTime]), tick);
		Z = bStream[bobjectid][bStream_Z]+floatmul(floatdiv(bStream[bobjectid][bStream_toZ]-bStream[bobjectid][bStream_Z], bStream[bobjectid][bStream_MoveTime]), tick);
		rX = bStream[bobjectid][bStream_rX]+floatmul(floatdiv(bStream[bobjectid][bStream_toRX]-bStream[bobjectid][bStream_rX], bStream[bobjectid][bStream_MoveTime]), tick);
		rY = bStream[bobjectid][bStream_rY]+floatmul(floatdiv(bStream[bobjectid][bStream_toRY]-bStream[bobjectid][bStream_rY], bStream[bobjectid][bStream_MoveTime]), tick);
		rZ = bStream[bobjectid][bStream_rZ]+floatmul(floatdiv(bStream[bobjectid][bStream_toRZ]-bStream[bobjectid][bStream_rZ], bStream[bobjectid][bStream_MoveTime]), tick);
	}
	else
	{
		X = bStream[bobjectid][bStream_X];
		Y = bStream[bobjectid][bStream_Y];
		Z = bStream[bobjectid][bStream_Z];
		rX = bStream[bobjectid][bStream_rX];
		rY = bStream[bobjectid][bStream_rY];
		rZ = bStream[bobjectid][bStream_rZ];
	}
}

stock SetBObjectRot(bobjectid, Float:rX, Float:rY, Float:rZ)
{
	if(bobjectid < 0 || bobjectid >= MAX_B_OBJECTS) return false;
	if(!bStream[bobjectid][bStream_Is]) return false;
	bStream[bobjectid][bStream_rX] = rX;
	bStream[bobjectid][bStream_rY] = rY;
	bStream[bobjectid][bStream_rZ] = rZ;
	foreach(Player, playerid)
	{
		if(bStream[bobjectid][bStream_pObjectID][playerid] == -1) continue;
		SetPlayerObjectRot(playerid, bStream[bobjectid][bStream_pObjectID][playerid], rX, rY, rZ);
	}
	return true;
}

stock GetBObjectRot(bobjectid, &Float:rX, &Float:rY, &Float:rZ)
{
	if(bobjectid < 0 || bobjectid >= MAX_B_OBJECTS) return;
	if(!bStream[bobjectid][bStream_Is]) return;
	new tick = GetTickCount()-bStream[bobjectid][bStream_MoveTick];
	if(bStream[bobjectid][bStream_Moving] && tick < bStream[bobjectid][bStream_MoveTime])
	{
		rX = bStream[bobjectid][bStream_rX]+floatmul(floatdiv(bStream[bobjectid][bStream_toRX]-bStream[bobjectid][bStream_rX], bStream[bobjectid][bStream_MoveTime]), tick);
		rY = bStream[bobjectid][bStream_rY]+floatmul(floatdiv(bStream[bobjectid][bStream_toRY]-bStream[bobjectid][bStream_rY], bStream[bobjectid][bStream_MoveTime]), tick);
		rZ = bStream[bobjectid][bStream_rZ]+floatmul(floatdiv(bStream[bobjectid][bStream_toRZ]-bStream[bobjectid][bStream_rZ], bStream[bobjectid][bStream_MoveTime]), tick);
	}
	else
	{
		rX = bStream[bobjectid][bStream_rX];
		rY = bStream[bobjectid][bStream_rY];
		rZ = bStream[bobjectid][bStream_rZ];
	}
}

stock bStream_SetUpdate(updatetime = B_OBJECT_TICK)
{
	if(bStreamTimer != 0) KillTimer(bStreamTimer);
	bStreamTimer = 0;
	bStreamTimer = SetTimer("bStream_Update", updatetime, true);
}

stock AssignBObjectForVirtualWorld(bobjectid, worldid = -1)
{
	if(bobjectid < 0 || bobjectid >= MAX_B_OBJECTS) return false;
	if(!bStream[bobjectid][bStream_Is]) return false;
	bStream[bobjectid][bStream_PlayerID] = worldid;
	return true;
}

stock AssignBObjectForInterior(bobjectid, interiorid = -1)
{
	if(bobjectid < 0 || bobjectid >= MAX_B_OBJECTS) return false;
	if(!bStream[bobjectid][bStream_Is]) return false;
	bStream[bobjectid][bStream_PlayerID] = worldid;
	return true;
}

stock AssignBObjectForPlayer(bobjectid, playerid = -1)
{
	if(bobjectid < 0 || bobjectid >= MAX_B_OBJECTS) return false;
	if(!bStream[bobjectid][bStream_Is]) return false;
	if(!IsPlayerConnected(playerid) && playerid != -1) return false;
	bStream[bobjectid][bStream_PlayerID] = playerid;
	return true;
}

stock MoveBObject(bobjectid, Float:X, Float:Y, Float:Z, Float:speed, Float:rX = -1000.0, Float:rY = -1000.0, Float:rZ = -1000.0)
{
	if(bobjectid < 0 || bobjectid >= MAX_B_OBJECTS) return false;
	if(!bStream[bobjectid][bStream_Is]) return false;
	if(bStream[bobjectid][bStream_Moving])
	{
		if(bStream[bobjectid][bStream_MoveTimer] != 0)
		{
			KillTimer(bStream[bobjectid][bStream_MoveTimer]);
			bStream[bobjectid][bStream_MoveTimer] = 0;
		}
		foreach(Player, playerid) {if(bStream[bobjectid][bStream_pObjectID][playerid] != -1) StopPlayerObject(playerid, bStream[bobjectid][bStream_pObjectID][playerid]);}
		new Float:bObjPos[6];
		GetBObjectPosEx(bobjectid, bObjPos[0], bObjPos[1], bObjPos[2], bObjPos[3], bObjPos[4], bObjPos[5]);
		SetBObjectPosEx(bobjectid, bObjPos[0], bObjPos[1], bObjPos[2], bObjPos[3], bObjPos[4], bObjPos[5]);
		bStream[bobjectid][bStream_Moving] = false;
	}
	bStream[bobjectid][bStream_MoveTick] = GetTickCount();
	bStream[bobjectid][bStream_toX] = X;
	bStream[bobjectid][bStream_toY] = Y;
	bStream[bobjectid][bStream_toZ] = Z;
	bStream[bobjectid][bStream_toRX] = rX;
	bStream[bobjectid][bStream_toRY] = rY;
	bStream[bobjectid][bStream_toRZ] = rZ;
	bStream[bobjectid][bStream_Speed] = speed;
	bStream[bobjectid][bStream_MoveTime] = floatround(floatdiv(floatsqroot((X-bStream[bobjectid][bStream_X])*(X-bStream[bobjectid][bStream_X])+(Y-bStream[bobjectid][bStream_Y])*(Y-bStream[bobjectid][bStream_Y])+(Z-bStream[bobjectid][bStream_Z])*(Z-bStream[bobjectid][bStream_Z])), speed)*1000);
	bStream[bobjectid][bStream_Moving] = true;
	bStream[bobjectid][bStream_MoveTimer] = SetTimerEx("bStream_ObjectMoved", bStream[bobjectid][bStream_MoveTime], false, "iffffff", bobjectid, X, Y, Z, rX, rY, rZ);
	foreach(Player, playerid) {if(bStream[bobjectid][bStream_pObjectID][playerid] != -1) MovePlayerObject(playerid, bStream[bobjectid][bStream_pObjectID][playerid], X, Y, Z, speed, rX, rY, rZ);}
	return true;
}

forward bStream_ObjectMoved(bobjectid, Float:X, Float:Y, Float:Z, Float:rX, Float:rY, Float:rZ);
public bStream_ObjectMoved(bobjectid, Float:X, Float:Y, Float:Z, Float:rX, Float:rY, Float:rZ)
{
	bStream[bobjectid][bStream_MoveTimer] = 0;
	bStream[bobjectid][bStream_Moving] = false;
	foreach(Player, playerid) {if(bStream[bobjectid][bStream_pObjectID][playerid] != -1) StopPlayerObject(playerid, bStream[bobjectid][bStream_pObjectID][playerid]);}
	SetBObjectPosEx(bobjectid, X, Y, Z, rX, rY, rZ);
	return (bStreamCallBacks&0x4 != 0 ? CallLocalFunction("OnBObjectMoved", "d", bobjectid) : 1);
}

stock StopBObject(bobjectid)
{
	if(bobjectid < 0 || bobjectid >= MAX_B_OBJECTS) return false;
	if(!bStream[bobjectid][bStream_Is]) return false;
	if(!bStream[bobjectid][bStream_Moving]) return false;
	if(bStream[bobjectid][bStream_MoveTimer] != 0)
	{
		KillTimer(bStream[bobjectid][bStream_MoveTimer]);
		bStream[bobjectid][bStream_MoveTimer] = 0;
	}
	foreach(Player, playerid) {if(bStream[bobjectid][bStream_pObjectID][playerid] != -1) StopPlayerObject(playerid, bStream[bobjectid][bStream_pObjectID][playerid]);}
	new Float:bObjPos[6];
	GetBObjectPosEx(bobjectid, bObjPos[0], bObjPos[1], bObjPos[2], bObjPos[3], bObjPos[4], bObjPos[5]);
	SetBObjectPosEx(bobjectid, bObjPos[0], bObjPos[1], bObjPos[2], bObjPos[3], bObjPos[4], bObjPos[5]);
	bStream[bobjectid][bStream_Moving] = false;
}

stock AttachCameraToBObject(playerid, bobjectid)
{
	if(!IsPlayerConnected(playerid)) return false;
	if(bobjectid < 0 || bobjectid >= MAX_B_OBJECTS) return false;
	if(bStream[bobjectid][bStream_pObjectID][playerid] != -1) AttachCameraToPlayerObject(playerid, bStream[bobjectid][bStream_pObjectID][playerid]);
	else
	{
		SetPlayerCameraPos(playerid, bStream[bobjectid][bStream_X], bStream[bobjectid][bStream_Y], bStream[bobjectid][bStream_Z]);
		bStream[bobjectid][bStream_pTryAttachCam][playerid] = true;
	}
	return true;
}
#if defined USE_MAP_FILES
stock SaveBMap(const file_name[], bool:use_vworld = false, vworld = -1)
{
	new File:bmapfile = fopen(file_name, io_write);
	if(!bmapfile)
	{
		printf("Couldn't open file \"%s\".", file_name);
		return 0;
	}
	new countobjects = 0, countvehicles = 0;
	foreach(Iter_BObject, i)
	{
		if(!bStream[i][bStream_Is]) continue;
		fputchar(bmapfile, 1, false);
		for(new j = 0; j < 4; j++) fputchar(bmapfile, (bStream[i][bStream_Model]>>>(j*8))&0xFF, false);
		for(new j = 0; j < 4; j++) fputchar(bmapfile, (_:bStream[i][bStream_X]>>>(j*8))&0xFF, false);
		for(new j = 0; j < 4; j++) fputchar(bmapfile, (_:bStream[i][bStream_Y]>>>(j*8))&0xFF, false);
		for(new j = 0; j < 4; j++) fputchar(bmapfile, (_:bStream[i][bStream_Z]>>>(j*8))&0xFF, false);
		for(new j = 0; j < 4; j++) fputchar(bmapfile, (_:bStream[i][bStream_rX]>>>(j*8))&0xFF, false);
		for(new j = 0; j < 4; j++) fputchar(bmapfile, (_:bStream[i][bStream_rY]>>>(j*8))&0xFF, false);
		for(new j = 0; j < 4; j++) fputchar(bmapfile, (_:bStream[i][bStream_rZ]>>>(j*8))&0xFF, false);
		for(new j = 0; j < 4; j++) fputchar(bmapfile, (_:bStream[i][bStream_DrawDistance]>>>(j*8))&0xFF, false);
		if(use_vworld) for(new j = 0; j < 4; j++) fputchar(bmapfile, (vworld>>>(j*8))&0xFF, false);
		else for(new j = 0; j < 4; j++) fputchar(bmapfile, (bStream[i][bStream_VWorld]>>>(j*8))&0xFF, false);
		for(new j = 0; j < 4; j++) fputchar(bmapfile, (bStream[i][bStream_Interior]>>>(j*8))&0xFF, false);
		for(new j = 0; j < 4; j++) fputchar(bmapfile, (bStream[i][bStream_PlayerID]>>>(j*8))&0xFF, false);
		countobjects++;
	}
	new BVehInfo[btVStreamInfos];
	foreach(Iter_BVehicle, i)
	{
		fputchar(bmapfile, 2, false);
		BVehInfo[btVStream_Model] = GetVehicleModel(i);
		for(new j = 0; j < 4; j++) fputchar(bmapfile, (BVehInfo[btVStream_Model]>>>(j*8))&0xFF, false);
		GetVehiclePos(i, BVehInfo[btVStream_X], BVehInfo[btVStream_Y], BVehInfo[btVStream_Z]);
		for(new j = 0; j < 4; j++) fputchar(bmapfile, (_:BVehInfo[btVStream_X]>>>(j*8))&0xFF, false);
		for(new j = 0; j < 4; j++) fputchar(bmapfile, (_:BVehInfo[btVStream_Y]>>>(j*8))&0xFF, false);
		for(new j = 0; j < 4; j++) fputchar(bmapfile, (_:BVehInfo[btVStream_Z]>>>(j*8))&0xFF, false);
		GetVehicleZAngle(i, BVehInfo[btVStream_rZ]);
		for(new j = 0; j < 4; j++) fputchar(bmapfile, (_:BVehInfo[btVStream_rZ]>>>(j*8))&0xFF, false);
		for(new j = 0; j < 4; j++) fputchar(bmapfile, (bVStream[i-1][bVStream_Color1]>>>(j*8))&0xFF, false);
		for(new j = 0; j < 4; j++) fputchar(bmapfile, (bVStream[i-1][bVStream_Color2]>>>(j*8))&0xFF, false);
		for(new j = 0; j < 4; j++) fputchar(bmapfile, (bVStream[i-1][bVStream_Respawn]>>>(j*8))&0xFF, false);
		for(new j = 0; j < 4; j++) fputchar(bmapfile, (bVStream[i-1][bVStream_Interior]>>>(j*8))&0xFF, false);
		if(use_vworld) for(new j = 0; j < 4; j++) fputchar(bmapfile, (vworld>>>(j*8))&0xFF, false);
		else
		{
			BVehInfo[btVStream_VWorld] = GetVehicleVirtualWorld(i);
			for(new j = 0; j < 4; j++) fputchar(bmapfile, (BVehInfo[btVStream_VWorld]>>>(j*8))&0xFF, false);
		}
		countvehicles++;
	}
	fclose(bmapfile);
	printf("\"%s\" %d objects and %d vehicles have been saved!", file_name, countobjects, countvehicles);
	return 1;
}

stock LoadBMap(const file_name[], bool:error_clear = true, bool:use_vworld = false, vworld = -1)
{
	if(!fexist(file_name))
	{
		printf("File \"%s\" does not exist!", file_name);
		return 0;
	}
	new File:bmapfile = fopen(file_name, io_read);
	if(!bmapfile)
	{
		printf("Couldn't open file \"%s\".", file_name);
		return 0;
	}
	new funcid, buffer, objpos = 0, vehpos = 0, BMapInfo[btStreamInfos], BVehInfo[btVStreamInfos], testval = -1;
	while((funcid = fgetchar(bmapfile, 0, false)) != -1)
	{
		switch(funcid)
		{
			case 1:
			{
				for(new argpos = 0; argpos < 11; argpos++)
				{
					for(new i = 0; i < 4; i++)
					{
						testval = fgetchar(bmapfile, 0, false);
						if(testval == -1)
						{
							if(error_clear)
							{
								DestroyAllBObjects(vworld);
								DestroyAllBVehicles(use_vworld, vworld);
							}
							fclose(bmapfile);
							printf("Map \"%s\" is broken.", file_name);
							return 0;
						}
						buffer |= testval<<(i*8);
					}
					switch(argpos)
					{
						case 0: BMapInfo[btStream_Model] = buffer;
						case 1: BMapInfo[btStream_X] = Float:buffer;
						case 2: BMapInfo[btStream_Y] = Float:buffer;
						case 3: BMapInfo[btStream_Z] = Float:buffer;
						case 4: BMapInfo[btStream_rX] = Float:buffer;
						case 5: BMapInfo[btStream_rY] = Float:buffer;
						case 6: BMapInfo[btStream_rZ] = Float:buffer;
						case 7:
						{
							BMapInfo[btStream_DrawDistance] = Float:buffer;
							if(use_vworld)
							{
								fseek(bmapfile, 4, seek_current);
								argpos++;
								BMapInfo[btStream_VWorld] = vworld;
							}
						}
						case 8: BMapInfo[btStream_VWorld] = buffer;
						case 9: BMapInfo[btStream_Interior] = buffer;
						case 10:
						{
							BMapInfo[btStream_PlayerID] = buffer;
							if(CreateBObject(BMapInfo[btStream_Model], BMapInfo[btStream_X], BMapInfo[btStream_Y], BMapInfo[btStream_Z], BMapInfo[btStream_rX], BMapInfo[btStream_rY], BMapInfo[btStream_rZ], BMapInfo[btStream_DrawDistance], BMapInfo[btStream_VWorld], BMapInfo[btStream_Interior], BMapInfo[btStream_PlayerID]) == -1)
							{
								if(error_clear)
								{
									DestroyAllBObjects(vworld);
									DestroyAllBVehicles(use_vworld, vworld);
								}
								fclose(bmapfile);
								printf("Map \"%s\" overflow. Server can't load more than %d objects!", file_name, MAX_B_OBJECTS);
								return 0;
							}
							objpos++;
						}
					}
					buffer = 0;
				}
			}
			case 2:
			{
				for(new argpos = 0; argpos < 10; argpos++)
				{
					for(new i = 0; i < 4; i++)
					{
						testval = fgetchar(bmapfile, 0, false);
						if(testval == -1)
						{
							if(error_clear)
							{
								DestroyAllBObjects(vworld);
								DestroyAllBVehicles(use_vworld, vworld);
							}
							fclose(bmapfile);
							printf("Map \"%s\" is broken.", file_name);
							return 0;
						}
						buffer |= testval<<(i*8);
					}
					switch(argpos)
					{
						case 0: BVehInfo[btVStream_Model] = buffer;
						case 1: BVehInfo[btVStream_X] = Float:buffer;
						case 2: BVehInfo[btVStream_Y] = Float:buffer;
						case 3: BVehInfo[btVStream_Z] = Float:buffer;
						case 4: BVehInfo[btVStream_rZ] = Float:buffer;
						case 5: BVehInfo[btVStream_Color1] = buffer;
						case 6: BVehInfo[btVStream_Color2] = buffer;
						case 7: BVehInfo[btVStream_Respawn] = buffer;
						case 8:
						{
							BVehInfo[btVStream_Interior] = buffer;
							if(use_vworld)
							{
								fseek(bmapfile, 4, seek_current);
								argpos++;
								BVehInfo[btVStream_VWorld] = vworld;
								if(CreateBVehicle(BVehInfo[btVStream_Model], BVehInfo[btVStream_X], BVehInfo[btVStream_Y], BVehInfo[btVStream_Z], BVehInfo[btVStream_rZ], BVehInfo[btVStream_Color1], BVehInfo[btVStream_Color2], BVehInfo[btVStream_Respawn], BVehInfo[btVStream_Interior], BVehInfo[btVStream_VWorld]) == 0)
								{
									if(error_clear)
									{
										DestroyAllBObjects(vworld);
										DestroyAllBVehicles(use_vworld, vworld);
									}
									fclose(bmapfile);
									printf("Map \"%s\" overflow. Server can't load more than %d vehicles!", file_name, MAX_VEHICLES);
									return 0;
								}
								vehpos++;
							}
						}
						case 9:
						{
							BVehInfo[btVStream_VWorld] = buffer;
							if(CreateBVehicle(BVehInfo[btVStream_Model], BVehInfo[btVStream_X], BVehInfo[btVStream_Y], BVehInfo[btVStream_Z], BVehInfo[btVStream_rZ], BVehInfo[btVStream_Color1], BVehInfo[btVStream_Color2], BVehInfo[btVStream_Respawn], BVehInfo[btVStream_Interior], BVehInfo[btVStream_VWorld]) == 0)
							{
								if(error_clear)
								{
									DestroyAllBObjects(vworld);
									DestroyAllBVehicles(use_vworld, vworld);
								}
								fclose(bmapfile);
								printf("Map \"%s\" overflow. Server can't load more than %d vehicles!", file_name, MAX_VEHICLES);
								return 0;
							}
							vehpos++;
						}
					}
					buffer = 0;
				}
			}
			default:
			{
				if(error_clear)
				{
					DestroyAllBObjects(vworld);
					DestroyAllBVehicles(use_vworld, vworld);
				}
				fclose(bmapfile);
				printf("Map \"%s\" unknown function ID: %d", file_name, funcid);
				return 0;
			}
		}
	}
	printf("Map \"%s\" %d objects and %d vehicles loaded.", file_name, objpos, vehpos);
	fclose(bmapfile);
	return 1;
}

stock SavePWN(const file_name[], bool:use_vworld = false, vworld = -1)
{
	new File:pwnfile = fopen(file_name, io_write);
	if(!pwnfile)
	{
		printf("Couldn't open file \"%s\".", file_name);
		return 0;
	}
	new countobjects = 0, countvehicles = 0, writestr[256], Float:vehdata[4], bool:nline = false;
	foreach(Iter_BObject, i)
	{
		if(!bStream[i][bStream_Is]) continue;
		if(nline) format(writestr, sizeof writestr, "\r\nCreateBObject(%d, %0.8f, %0.8f, %0.8f, %0.8f, %0.8f, %0.8f, %0.8f, %d, %d, %d);"
			, bStream[i][bStream_Model], bStream[i][bStream_X], bStream[i][bStream_Y], bStream[i][bStream_Z]
			, bStream[i][bStream_rX], bStream[i][bStream_rY], bStream[i][bStream_rZ]
			, bStream[i][bStream_DrawDistance]
			, (use_vworld?vworld:bStream[i][bStream_VWorld]), bStream[i][bStream_Interior], bStream[i][bStream_PlayerID]
		);
		else
		{
			nline = true;
			format(writestr, sizeof writestr, "CreateBObject(%d, %0.8f, %0.8f, %0.8f, %0.8f, %0.8f, %0.8f, %0.8f, %d, %d, %d);"
				, bStream[i][bStream_Model], bStream[i][bStream_X], bStream[i][bStream_Y], bStream[i][bStream_Z]
				, bStream[i][bStream_rX], bStream[i][bStream_rY], bStream[i][bStream_rZ]
				, bStream[i][bStream_DrawDistance]
				, (use_vworld?vworld:bStream[i][bStream_VWorld]), bStream[i][bStream_Interior], bStream[i][bStream_PlayerID]
			);
		}
		fwrite(pwnfile, writestr);
		countobjects++;
	}
	foreach(Iter_BVehicle, i)
	{
		GetVehiclePos(i, vehdata[0], vehdata[1], vehdata[2]);
		GetVehicleZAngle(i, vehdata[3]);
		if(nline) format(writestr, sizeof writestr, "\r\nCreateBVehicle(%d, %0.8f, %0.8f, %0.8f, %0.8f, %d, %d, %d, %d, %d);"
			, GetVehicleModel(i)
			, vehdata[0], vehdata[1], vehdata[2], vehdata[3]
			, bVStream[i-1][bVStream_Color1], bVStream[i-1][bVStream_Color2]
			, bVStream[i-1][bVStream_Respawn], bVStream[i-1][bVStream_Interior], (use_vworld?vworld:GetVehicleVirtualWorld(i))
		);
		else
		{
			nline = true;
			format(writestr, sizeof writestr, "CreateBVehicle(%d, %0.8f, %0.8f, %0.8f, %0.8f, %d, %d, %d, %d, %d);"
				, GetVehicleModel(i)
				, vehdata[0], vehdata[1], vehdata[2], vehdata[3]
				, bVStream[i-1][bVStream_Color1], bVStream[i-1][bVStream_Color2]
				, bVStream[i-1][bVStream_Respawn], bVStream[i-1][bVStream_Interior], (use_vworld?vworld:GetVehicleVirtualWorld(i))
			);
		}
		fwrite(pwnfile, writestr);
		countvehicles++;
	}
	fclose(pwnfile);
	printf("\"%s\" %d objects and %d vehicles have been saved!", file_name, countobjects, countvehicles);
	return 1;
}

stock LoadPWN(const file_name[], bool:error_clear = true, bool:use_vworld = false, vworld = -1)
{
	if(!fexist(file_name))
	{
		printf("File \"%s\" does not found!", file_name);
		return 0;
	}
	new File:pwnfile = fopen(file_name, io_read);
	if(!pwnfile)
	{
		printf("Couldn't open file \"%s\".", file_name);
		return 0;
	}
	new buffer[256], bufferlen, objpos = 0, vehpos = 0, bool:incomment = false, pos = -1, BMapInfo[btStreamInfos], BVehInfo[btVStreamInfos], line = 0, formatstr[64], bool:commentjmp;
	while(fread(pwnfile, buffer))
	{
		bufferlen = strlen(buffer);
		for(new i = bufferlen-1; i >= 0; i--)
		{
			if(buffer[i] == '\r' || buffer[i] == '\n')
			{
				buffer[i] = EOS;
				bufferlen = i;
			}
			else if(buffer[i] == '\t') buffer[i] = ' ';
		}
		if(incomment)
		{
			for(new i = 0; i < bufferlen-1; i++)
			{
				if(buffer[i] == '*')
				{
					if(buffer[i+1] == '/')
					{
						incomment = false;
						for(new j = i+1; j >= 0; j--) buffer[j] = ' ';
						goto bstreamer_nocomment;
					}
				}
			}
		}
		else
		{
			bstreamer_nocomment:
			for(new i = bufferlen-2; i >= 0; i--)
			{
				if(buffer[i] == '/')
				{
					if(buffer[i+1] == '/')
					{
						for(new j = i; j < bufferlen; j++) buffer[j] = EOS;
						bufferlen = i;
					}
					else if(buffer[i+1] == '*')
					{
						incomment = true;
						for(new j = i+2; j < bufferlen-1; j++)
						{
							if(buffer[j] == '*')
							{
								if(buffer[j+1] == '/')
								{
									incomment = false;
									for(new k = j+1; k >= i+1; k--) buffer[k] = ' ';
								}
							}
						}
						if(incomment)
						{
							for(new j = bufferlen-1; j >= i; j--) buffer[j] = EOS;
							bufferlen = i;
							commentjmp = true;
							goto bstreamer_comment;
						}
					}
				}
			}
			bstreamer_comment:
			if(commentjmp)
			{
				commentjmp = false;
				line++;
				continue;
			}
			pos = strfind(buffer, "CreateBObject(", true);
			if(pos != -1)
			{
				for(new i = bufferlen-1; i >= 0; i--)
				{
					switch(buffer[i])
					{
						case '0'..'9', '.', '-':{}
						default: buffer[i] = ' ';
					}
				}
				format(formatstr, sizeof formatstr, "dffffffF(%.4f)D(-1)D(-1)D(-1)", B_OBJECT_STREAM_DISTANCE);
				if(!sscanf(buffer, formatstr
					, BMapInfo[btStream_Model]
					, BMapInfo[btStream_X]
					, BMapInfo[btStream_Y]
					, BMapInfo[btStream_Z]
					, BMapInfo[btStream_rX]
					, BMapInfo[btStream_rY]
					, BMapInfo[btStream_rZ]
					, BMapInfo[btStream_DrawDistance]
					, BMapInfo[btStream_VWorld]
					, BMapInfo[btStream_Interior]
					, BMapInfo[btStream_PlayerID]))
				{
					if(CreateBObject(BMapInfo[btStream_Model], BMapInfo[btStream_X], BMapInfo[btStream_Y], BMapInfo[btStream_Z], BMapInfo[btStream_rX], BMapInfo[btStream_rY], BMapInfo[btStream_rZ], BMapInfo[btStream_DrawDistance], (use_vworld?vworld:BMapInfo[btStream_VWorld]), BMapInfo[btStream_Interior], BMapInfo[btStream_PlayerID]) == -1)
					{
						if(error_clear)
						{
							DestroyAllBObjects(vworld);
							DestroyAllBVehicles(use_vworld, vworld);
						}
						fclose(pwnfile);
						printf("Map \"%s\" overflow. Server can't load more than %d objects!", file_name, MAX_B_OBJECTS);
						return 0;
					}
					objpos++;
				}
				else printf("Line %d (CreateBObject) invalid amount of arguments.", line+1);
				pos = -1;
				line++;
				continue;
			}
			pos = strfind(buffer, "CreateBVehicle(", true);
			if(pos != -1)
			{
				for(new i = bufferlen-1; i >= 0; i--)
				{
					switch(buffer[i])
					{
						case '0'..'9', '.', '-':{}
						default: buffer[i] = ' ';
					}
				}
				if(!sscanf(buffer, "dffffdddD(0)D(0)"
					, BVehInfo[btVStream_Model]
					, BVehInfo[btVStream_X]
					, BVehInfo[btVStream_Y]
					, BVehInfo[btVStream_Z]
					, BVehInfo[btVStream_rZ]
					, BVehInfo[btVStream_Color1]
					, BVehInfo[btVStream_Color2]
					, BVehInfo[btVStream_Respawn]
					, BVehInfo[btVStream_Interior]
					, BVehInfo[btVStream_VWorld]))
				{
					if(CreateBVehicle(BVehInfo[btVStream_Model], BVehInfo[btVStream_X], BVehInfo[btVStream_Y], BVehInfo[btVStream_Z], BVehInfo[btVStream_rZ], BVehInfo[btVStream_Color1], BVehInfo[btVStream_Color2], BVehInfo[btVStream_Respawn], BVehInfo[btVStream_Interior], BVehInfo[btVStream_VWorld]) == 0)
					{
						if(error_clear)
						{
							DestroyAllBObjects(vworld);
							DestroyAllBVehicles(use_vworld, vworld);
						}
						fclose(pwnfile);
						printf("Map \"%s\" overflow. Server can't load more than %d vehicles!", file_name, MAX_VEHICLES);
						return 0;
					}
					objpos++;
					vehpos++;
				}
				else printf("Line %d (CreateBVehicle) invalid amount of arguments.", line+1);
				pos = -1;
				line++;
				continue;
			}
		}
		line++;
	}
	fclose(pwnfile);
	printf("Map \"%s\" %d objects and %d vehicles have been loaded!", file_name, objpos, vehpos);
	return 1;
}

stock BMap_To_PWN(bmap_fname[], pwn_fname[], bool:error_clear = true, bool:use_single_vworld = false, single_vworld = -1)
{
	if(!fexist(bmap_fname))
	{
		printf("File \"%s\" does not exist!", bmap_fname);
		return 0;
	}
	new File:bmapfile = fopen(bmap_fname, io_read);
	if(!bmapfile)
	{
		printf("Couldn't open file \"%s\".", bmap_fname);
		return 0;
	}
	new File:pwnfile = fopen(pwn_fname, io_write);
	if(!pwnfile)
	{
		printf("Couldn't open file \"%s\".", pwn_fname);
		return 0;
	}
	new funcid, buffer = 0, funcpos = 0, objpos = 0, vehpos = 0, writestr[256], testval;
	while((funcid = fgetchar(bmapfile, 0, false)) != -1)
	{
		switch(funcid)
		{
			case 1:
			{
				for(new argpos = 0; argpos < 11; argpos++)
				{
					for(new i = 0; i < 4; i++)
					{
						testval = fgetchar(bmapfile, 0, false);
						if(testval == -1)
						{
							fclose(bmapfile);
							fclose(pwnfile);
							if(error_clear) fremove(pwn_fname);
							printf("Map \"%s\" is broken.", bmap_fname);
							return 0;
						}
						buffer |= testval<<(i*8);
					}
					switch(argpos)
					{
						case 0:
						{
							if(funcpos == 0) format(writestr, sizeof writestr, "CreateBObject(%d, ", buffer);
							else format(writestr, sizeof writestr, "\r\nCreateBObject(%d, ", buffer);
						}
						case 1..6: format(writestr, sizeof writestr, "%s%0.8f, ", writestr, Float:buffer);
						case 7:
						{
							format(writestr, sizeof writestr, "%s%0.8f, ", writestr, Float:buffer);
							if(use_single_vworld)
							{
								fseek(bmapfile, 4, seek_current);
								argpos++;
								format(writestr, sizeof writestr, "%s%d, ", writestr, single_vworld);
							}
						}
						case 8,9: format(writestr, sizeof writestr, "%s%d, ", writestr, buffer);
						case 10:
						{
							format(writestr, sizeof writestr, "%s%d);", writestr, buffer);
							fwrite(pwnfile, writestr);
							objpos++;
							funcpos++;
						}
					}
					buffer = 0;
				}
			}
			case 2:
			{
				for(new argpos = 0; argpos < 10; argpos++)
				{
					for(new i = 0; i < 4; i++)
					{
						testval = fgetchar(bmapfile, 0, false);
						if(testval == -1)
						{
							fclose(bmapfile);
							fclose(pwnfile);
							if(error_clear) fremove(pwn_fname);
							printf("Map \"%s\" is broken.", bmap_fname);
							return 0;
						}
						buffer |= testval<<(i*8);
					}
					switch(argpos)
					{
						case 0:
						{
							if(funcpos == 0) format(writestr, sizeof writestr, "CreateBVehicle(%d, ", buffer);
							else format(writestr, sizeof writestr, "\r\nCreateBVehicle(%d, ", buffer);
						}
						case 1..4: format(writestr, sizeof writestr, "%s%0.8f, ", writestr, Float:buffer);
						case 5..7: format(writestr, sizeof writestr, "%s%d, ", writestr, buffer);
						case 8:
						{
							format(writestr, sizeof writestr, "%s%d, ", writestr, buffer);
							if(use_single_vworld)
							{
								fseek(bmapfile, 4, seek_current);
								argpos++;
								format(writestr, sizeof writestr, "%s%d);", writestr, single_vworld);
								fwrite(pwnfile, writestr);
								vehpos++;
								funcpos++;
							}
						}
						case 9:
						{
							format(writestr, sizeof writestr, "%s%d);", writestr, buffer);
							fwrite(pwnfile, writestr);
							vehpos++;
							funcpos++;
						}
					}
					buffer = 0;
				}
			}
			default:
			{
				fclose(bmapfile);
				fclose(pwnfile);
				if(error_clear) fremove(pwn_fname);
				printf("Map \"%s\" unknown function ID: %d", bmap_fname, funcid);
				return 0;
			}
		}
	}
	printf("Map \"%s\" -> \"%s\" %d objects and %d vehicles converted.", bmap_fname, pwn_fname, objpos, vehpos);
	fclose(bmapfile);
	fclose(pwnfile);
	return 1;
}

stock PWN_To_BMap(pwn_fname[], bmap_fname[], bool:use_single_vworld = false, single_vworld = -1)
{
	if(!fexist(pwn_fname))
	{
		printf("File \"%s\" does not found!", pwn_fname);
		return 0;
	}
	new File:pwnfile = fopen(pwn_fname, io_read);
	if(!pwnfile)
	{
		printf("Couldn't open file \"%s\".", pwn_fname);
		return 0;
	}
	new File:bmapfile = fopen(bmap_fname, io_write);
	if(!bmapfile)
	{
		printf("Couldn't open file \"%s\".", bmap_fname);
		return 0;
	}
	new buffer[256], bufferlen, objpos = 0, vehpos = 0, bool:incomment = false, pos = -1, BMapInfo[btStreamInfos], BVehInfo[btVStreamInfos], line = 0, formatstr[64], bool:commentjmp;
	while(fread(pwnfile, buffer))
	{
		bufferlen = strlen(buffer);
		for(new i = bufferlen-1; i >= 0; i--)
		{
			if(buffer[i] == '\r' || buffer[i] == '\n')
			{
				buffer[i] = EOS;
				bufferlen = i;
			}
			else if(buffer[i] == '\t') buffer[i] = ' ';
		}
		if(incomment)
		{
			for(new i = 0; i < bufferlen-1; i++)
			{
				if(buffer[i] == '*')
				{
					if(buffer[i+1] == '/')
					{
						incomment = false;
						for(new j = i+1; j >= 0; j--) buffer[j] = ' ';
						goto bstreamer_nocomment;
					}
				}
			}
		}
		else
		{
			bstreamer_nocomment:
			for(new i = bufferlen-2; i >= 0; i--)
			{
				if(buffer[i] == '/')
				{
					if(buffer[i+1] == '/')
					{
						for(new j = i; j < bufferlen; j++) buffer[j] = EOS;
						bufferlen = i;
					}
					else if(buffer[i+1] == '*')
					{
						incomment = true;
						for(new j = i+2; j < bufferlen-1; j++)
						{
							if(buffer[j] == '*')
							{
								if(buffer[j+1] == '/')
								{
									incomment = false;
									for(new k = j+1; k >= i+1; k--) buffer[k] = ' ';
								}
							}
						}
						if(incomment)
						{
							for(new j = bufferlen-1; j >= i; j--) buffer[j] = EOS;
							bufferlen = i;
							commentjmp = true;
							goto bstreamer_comment;
						}
					}
				}
			}
			bstreamer_comment:
			if(commentjmp)
			{
				commentjmp = false;
				line++;
				continue;
			}
			pos = strfind(buffer, "CreateBObject(", true);
			if(pos != -1)
			{
				for(new i = bufferlen-1; i >= 0; i--)
				{
					switch(buffer[i])
					{
						case '0'..'9', '.', '-':{}
						default: buffer[i] = ' ';
					}
				}
				format(formatstr, sizeof formatstr, "dffffffF(%.4f)D(-1)D(-1)D(-1)", B_OBJECT_STREAM_DISTANCE);
				if(!sscanf(buffer, formatstr
					, BMapInfo[btStream_Model]
					, BMapInfo[btStream_X]
					, BMapInfo[btStream_Y]
					, BMapInfo[btStream_Z]
					, BMapInfo[btStream_rX]
					, BMapInfo[btStream_rY]
					, BMapInfo[btStream_rZ]
					, BMapInfo[btStream_DrawDistance]
					, BMapInfo[btStream_VWorld]
					, BMapInfo[btStream_Interior]
					, BMapInfo[btStream_PlayerID]))
				{
					fputchar(bmapfile, 1, false);
					for(new j = 0; j < 4; j++) fputchar(bmapfile, (BMapInfo[btStream_Model]>>>(j*8))&0xFF, false);
					for(new j = 0; j < 4; j++) fputchar(bmapfile, (_:BMapInfo[btStream_X]>>>(j*8))&0xFF, false);
					for(new j = 0; j < 4; j++) fputchar(bmapfile, (_:BMapInfo[btStream_Y]>>>(j*8))&0xFF, false);
					for(new j = 0; j < 4; j++) fputchar(bmapfile, (_:BMapInfo[btStream_Z]>>>(j*8))&0xFF, false);
					for(new j = 0; j < 4; j++) fputchar(bmapfile, (_:BMapInfo[btStream_rX]>>>(j*8))&0xFF, false);
					for(new j = 0; j < 4; j++) fputchar(bmapfile, (_:BMapInfo[btStream_rY]>>>(j*8))&0xFF, false);
					for(new j = 0; j < 4; j++) fputchar(bmapfile, (_:BMapInfo[btStream_rZ]>>>(j*8))&0xFF, false);
					for(new j = 0; j < 4; j++) fputchar(bmapfile, (_:BMapInfo[btStream_DrawDistance]>>>(j*8))&0xFF, false);
					if(use_single_vworld) for(new j = 0; j < 4; j++) fputchar(bmapfile, (single_vworld>>>(j*8))&0xFF, false);
					else for(new j = 0; j < 4; j++) fputchar(bmapfile, (BMapInfo[btStream_VWorld]>>>(j*8))&0xFF, false);
					for(new j = 0; j < 4; j++) fputchar(bmapfile, (BMapInfo[btStream_Interior]>>>(j*8))&0xFF, false);
					for(new j = 0; j < 4; j++) fputchar(bmapfile, (BMapInfo[btStream_PlayerID]>>>(j*8))&0xFF, false);
					objpos++;
				}
				else printf("Line %d (CreateBObject) invalid amount of arguments.", line+1);
				pos = -1;
				line++;
				continue;
			}
			pos = strfind(buffer, "CreateBVehicle(", true);
			if(pos != -1)
			{
				for(new i = bufferlen-1; i >= 0; i--)
				{
					switch(buffer[i])
					{
						case '0'..'9', '.', '-':{}
						default: buffer[i] = ' ';
					}
				}
				if(!sscanf(buffer, "dffffdddD(0)D(0)"
					, BVehInfo[btVStream_Model]
					, BVehInfo[btVStream_X]
					, BVehInfo[btVStream_Y]
					, BVehInfo[btVStream_Z]
					, BVehInfo[btVStream_rZ]
					, BVehInfo[btVStream_Color1]
					, BVehInfo[btVStream_Color2]
					, BVehInfo[btVStream_Respawn]
					, BVehInfo[btVStream_Interior]
					, BVehInfo[btVStream_VWorld]))
				{
					fputchar(bmapfile, 2, false);
					for(new j = 0; j < 4; j++) fputchar(bmapfile, (BVehInfo[btVStream_Model]>>>(j*8))&0xFF, false);
					for(new j = 0; j < 4; j++) fputchar(bmapfile, (_:BVehInfo[btVStream_X]>>>(j*8))&0xFF, false);
					for(new j = 0; j < 4; j++) fputchar(bmapfile, (_:BVehInfo[btVStream_Y]>>>(j*8))&0xFF, false);
					for(new j = 0; j < 4; j++) fputchar(bmapfile, (_:BVehInfo[btVStream_Z]>>>(j*8))&0xFF, false);
					for(new j = 0; j < 4; j++) fputchar(bmapfile, (_:BVehInfo[btVStream_rZ]>>>(j*8))&0xFF, false);
					for(new j = 0; j < 4; j++) fputchar(bmapfile, (BVehInfo[btVStream_Color1]>>>(j*8))&0xFF, false);
					for(new j = 0; j < 4; j++) fputchar(bmapfile, (BVehInfo[btVStream_Color2]>>>(j*8))&0xFF, false);
					for(new j = 0; j < 4; j++) fputchar(bmapfile, (BVehInfo[btVStream_Respawn]>>>(j*8))&0xFF, false);
					for(new j = 0; j < 4; j++) fputchar(bmapfile, (BVehInfo[btVStream_Interior]>>>(j*8))&0xFF, false);
					if(use_single_vworld) for(new j = 0; j < 4; j++) fputchar(bmapfile, (single_vworld>>>(j*8))&0xFF, false);
					else for(new j = 0; j < 4; j++) fputchar(bmapfile, (BVehInfo[btVStream_VWorld]>>>(j*8))&0xFF, false);
					vehpos++;
				}
				else printf("Line %d (CreateBVehicle) invalid amount of arguments.", line+1);
				pos = -1;
				line++;
				continue;
			}
		}
		line++;
	}
	fclose(pwnfile);
	fclose(bmapfile);
	printf("\"%s\" -> \"%s\" %d objects and %d vehicles have been converted!", pwn_fname, bmap_fname, objpos, vehpos);
	return 1;
}
#endif

stock CreateBVehicle(vehicletype, Float:x, Float:y, Float:z, Float:rotation, color1, color2, respawn_delay, interior = 0, vworld = 0)
{
	new vehicleid = CreateVehicle(vehicletype, x, y, z, rotation, color1, color2, respawn_delay);
	if(vehicleid == 0) return 0;
	if(interior != 0) LinkVehicleToInterior(vehicleid, interior);
	if(vworld != 0) SetVehicleVirtualWorld(vehicleid, vworld);
	bVStream[vehicleid-1][bVStream_Interior] = interior;
	bVStream[vehicleid-1][bVStream_Color1] = color1;
	bVStream[vehicleid-1][bVStream_Color2] = color2;
	bVStream[vehicleid-1][bVStream_Is] = true;
	Iter_Add(Iter_BVehicle, vehicleid);
	return vehicleid;
}

stock DestroyBVehicle(vehicleid)
{
	if(vehicleid < 1 || vehicleid > MAX_VEHICLES) return false;
	if(!bVStream[vehicleid-1][bVStream_Is]) return false;
	bVStream[vehicleid-1][bVStream_Is] = false;
	DestroyVehicle(vehicleid);
	Iter_Remove(Iter_BVehicle, vehicleid);
	return true;
}

stock DestroyAllBVehicles(bool:use_vworld = false, vworld = 0)
{
	if(use_vworld)
	{
		foreach(Iter_BVehicle, i)
		{
			if(!bVStream[i-1][bVStream_Is]) continue;
			if(use_vworld) if(vworld != GetVehicleVirtualWorld(i)) continue;
			bVStream[i-1][bVStream_Is] = false;
			DestroyVehicle(i);
			new ni;
			Iter_SafeRemove(Iter_BVehicle, i, ni);
			i = ni;
		}
		Iter_Clear(Iter_BVehicle);
	}
	else
	{
		foreach(Iter_BVehicle, i)
		{
			if(!bVStream[i-1][bVStream_Is]) continue;
			if(use_vworld) if(vworld != GetVehicleVirtualWorld(i)) continue;
			bVStream[i-1][bVStream_Is] = false;
			DestroyVehicle(i);
		}
		Iter_Clear(Iter_BVehicle);
	}
}

stock GetBVehicleColors(vehicleid, &color1, &color2)
{
	if(vehicleid <= 0 || vehicleid > MAX_VEHICLES) return;
	color1 = bVStream[vehicleid-1][bVStream_Color1];
	color2 = bVStream[vehicleid-1][bVStream_Color2];
}

stock GetBVehicleData(vehicleid, &color1, &color2, &respawn_delay, &interior)
{
	if(vehicleid <= 0 || vehicleid > MAX_VEHICLES) return;
	color1 = bVStream[vehicleid-1][bVStream_Color1];
	color2 = bVStream[vehicleid-1][bVStream_Color2];
	respawn_delay = bVStream[vehicleid-1][bVStream_Respawn];
	interior = bVStream[vehicleid-1][bVStream_Interior];
}

stock IsCameraInRangeOfPoint(playerid, Float:range, Float:X, Float:Y, Float:Z)
{
	new Float:pCamPos[3];
	GetPlayerCameraPos(playerid, pCamPos[0], pCamPos[1], pCamPos[2]);
	if(floatsqroot((X-pCamPos[0])*(X-pCamPos[0])+(Y-pCamPos[1])*(Y-pCamPos[1])+(Z-pCamPos[2])*(Z-pCamPos[2])) <= range) return true;
	return false;
}

#if defined FILTERSCRIPT
public OnFilterScriptInit()
#else
public OnGameModeInit()
#endif
{
	bStreamCallBacks = ((funcidx("OnBObjectStreamIn") != -1 ? 0x1 : 0x0)|(funcidx("OnBObjectStreamOut") != -1 ? 0x2 : 0x0)|(funcidx("OnBObjectMoved") != -1 ? 0x4: 0x0));
	for(new i = 0; i < MAX_B_OBJECTS; i++) for(new j = 0; j < MAX_PLAYERS; j++) bStream[i][bStream_pObjectID][j] = -1;
	bStreamTimer = SetTimer("bStream_Update", B_OBJECT_TICK, true);
#if defined FILTERSCRIPT
	return CallLocalFunction("bStream_OnFilterScriptInit", "");
#else
	return CallLocalFunction("bStream_OnGameModeInit", "");
#endif
}
#if defined FILTERSCRIPT
	#if defined _ALS_OnFilterScriptInit
		#undef OnFilterScriptInit
	#else
		#define _ALS_OnFilterScriptInit
	#endif
	#define OnFilterScriptInit bStream_OnFilterScriptInit
forward bStream_OnFilterScriptInit();
#else
	#if defined _ALS_OnGameModeInit
		#undef OnGameModeInit
	#else
		#define _ALS_OnGameModeInit
	#endif
	#define OnGameModeInit bStream_OnGameModeInit
forward bStream_OnGameModeInit();
#endif

public bStream_Update()
{
	foreach(Player, playerid)
	{
		new bstreamcount = 0;
		foreach(Iter_BObject, i)
		{	
			if(bstreamcount >= LIMIT_B_OBJECTS)
			{
				if(bStream[i][bStream_pObjectID][playerid] != -1)
				{
					if(bStreamCallBacks&2?CallLocalFunction("OnBObjectStreamOut", "ddd", playerid, i, bStream[i][bStream_pObjectID][playerid]):1)
					{
						DestroyPlayerObject(playerid, bStream[i][bStream_pObjectID][playerid]);
						bStream[i][bStream_pObjectID][playerid] = -1;
					}
				}
			}
			else
			{
				if(bStream[i][bStream_Is])
				{
					if(bStream[i][bStream_Moving])
					{
						new Float:bObjPos[3];
						GetBObjectPos(i, bObjPos[0], bObjPos[1], bObjPos[2]);
#if defined USE_CAMERA_STREAM
						if(IsCameraInRangeOfPoint(playerid, bStream[i][bStream_DrawDistance], bObjPos[0], bObjPos[1], bObjPos[2]) && (bStream[i][bStream_VWorld] == -1 || bStream[i][bStream_VWorld] == GetPlayerVirtualWorld(playerid)) && (bStream[i][bStream_Interior] == -1 || bStream[i][bStream_Interior] == GetPlayerInterior(playerid)) && (bStream[i][bStream_PlayerID] == -1 || bStream[i][bStream_PlayerID] == playerid))
#else
						if(IsPlayerInRangeOfPoint(playerid, bStream[i][bStream_DrawDistance], bObjPos[0], bObjPos[1], bObjPos[2]) && (bStream[i][bStream_VWorld] == -1 || bStream[i][bStream_VWorld] == GetPlayerVirtualWorld(playerid)) && (bStream[i][bStream_Interior] == -1 || bStream[i][bStream_Interior] == GetPlayerInterior(playerid)) && (bStream[i][bStream_PlayerID] == -1 || bStream[i][bStream_PlayerID] == playerid))
#endif
						{
							if(bStream[i][bStream_pObjectID][playerid] == -1)
							{
								bStream[i][bStream_pObjectID][playerid] = CreatePlayerObject(playerid, bStream[i][bStream_Model], bStream[i][bStream_X], bStream[i][bStream_Y], bStream[i][bStream_Z], bStream[i][bStream_rX], bStream[i][bStream_rY], bStream[i][bStream_rZ], bStream[i][bStream_DrawDistance]);
								if(bStream[i][bStream_pTryAttachCam][playerid]) AttachCameraToPlayerObject(playerid, bStream[i][bStream_pObjectID][playerid]);
								MovePlayerObject(playerid, bStream[i][bStream_pObjectID][playerid], bStream[i][bStream_toX], bStream[i][bStream_toY], bStream[i][bStream_toZ], bStream[i][bStream_Speed], bStream[i][bStream_toRX], bStream[i][bStream_toRY], bStream[i][bStream_toRZ]);
								if(bStreamCallBacks&1) CallLocalFunction("OnBObjectStreamIn", "ddd", playerid, i, bStream[i][bStream_pObjectID][playerid]);
							}
							bstreamcount++;
						}
						else if(bStream[i][bStream_pObjectID][playerid] != -1)
						{
							if((bStreamCallBacks&2?CallLocalFunction("OnBObjectStreamOut", "ddd", playerid, i, bStream[i][bStream_pObjectID][playerid]):1))
							{
								DestroyPlayerObject(playerid, bStream[i][bStream_pObjectID][playerid]);
								bStream[i][bStream_pObjectID][playerid] = -1;
							}
						}
					}
					else
					{
#if defined USE_CAMERA_STREAM
						if(IsCameraInRangeOfPoint(playerid, bStream[i][bStream_DrawDistance], bStream[i][bStream_X], bStream[i][bStream_Y], bStream[i][bStream_Z]) && (bStream[i][bStream_VWorld] == -1 || bStream[i][bStream_VWorld] == GetPlayerVirtualWorld(playerid)) && (bStream[i][bStream_Interior] == -1 || bStream[i][bStream_Interior] == GetPlayerInterior(playerid)) && (bStream[i][bStream_PlayerID] == -1 || bStream[i][bStream_PlayerID] == playerid))
#else
						if(IsPlayerInRangeOfPoint(playerid, bStream[i][bStream_DrawDistance], bStream[i][bStream_X], bStream[i][bStream_Y], bStream[i][bStream_Z]) && (bStream[i][bStream_VWorld] == -1 || bStream[i][bStream_VWorld] == GetPlayerVirtualWorld(playerid)) && (bStream[i][bStream_Interior] == -1 || bStream[i][bStream_Interior] == GetPlayerInterior(playerid)) && (bStream[i][bStream_PlayerID] == -1 || bStream[i][bStream_PlayerID] == playerid))
#endif
						{
							if(bStream[i][bStream_pObjectID][playerid] == -1)
							{
								bStream[i][bStream_pObjectID][playerid] = CreatePlayerObject(playerid, bStream[i][bStream_Model], bStream[i][bStream_X], bStream[i][bStream_Y], bStream[i][bStream_Z], bStream[i][bStream_rX], bStream[i][bStream_rY], bStream[i][bStream_rZ], bStream[i][bStream_DrawDistance]);
								if(bStream[i][bStream_pTryAttachCam][playerid]) AttachCameraToPlayerObject(playerid, bStream[i][bStream_pObjectID][playerid]);
								if(bStreamCallBacks&1) CallLocalFunction("OnBObjectStreamIn", "ddd", playerid, i, bStream[i][bStream_pObjectID][playerid]);
							}
							bstreamcount++;
						}
						else if(bStream[i][bStream_pObjectID][playerid] != -1)
						{
							if((bStreamCallBacks&2?CallLocalFunction("OnBObjectStreamOut", "ddd", playerid, i, bStream[i][bStream_pObjectID][playerid]):1))
							{
								DestroyPlayerObject(playerid, bStream[i][bStream_pObjectID][playerid]);
								bStream[i][bStream_pObjectID][playerid] = -1;
							}
						}
					}
				}
				else
				{
					if(bStream[i][bStream_pObjectID][playerid] != -1)
					{
						if(bStreamCallBacks&2?CallLocalFunction("OnBObjectStreamOut", "ddd", playerid, i, bStream[i][bStream_pObjectID][playerid]):1)
						{
							DestroyPlayerObject(playerid, bStream[i][bStream_pObjectID][playerid]);
							bStream[i][bStream_pObjectID][playerid] = -1;
						}
					}
					if(playerid == Iter_Last(Player))
					{
						new next;
						Iter_SafeRemove(Iter_BObject, i, next);
						i = next;
					}
				}
			}
		}
	}
}