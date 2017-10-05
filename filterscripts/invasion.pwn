#include <a_samp>
#include <streamer_0_3z>
#include <list>

enum invader_type_enum
{
	invader_type_mother,
	invader_type_droid
}

enum ship_part_enum
{
	ship_part_modelid,
	Float:ship_part_x,
	Float:ship_part_y,
	Float:ship_part_z,
	Float:ship_part_rotx,
	Float:ship_part_roty,
	Float:ship_part_rotz
}

MEM::struct invader_struct
{
	Pointer:invader_object_arr,
	Pointer:invader_object_data_arr,
	invader_object_arr_len,
	invader_type,
	Float:invader_health
}

static LIST::init<invader_list>;

static const mother_ship_data[][ship_part_enum] = {
	{18876, 0.0, 0.0, 0.0, 0.0, 270.0, 270.0},
	{2932, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
	{2934, 0.0, -7.15, 0.0, 0.0, 0.0, 0.0},
	{18876, 0.0, -16.0, 0.0, 0.0, 270.0, 270.0},
	{18876, 0.0, -4.0, 0.0, 0.0, 270.0, 270.0},
	{18876, 0.0, -8.0, 0.0, 0.0, 270.0, 270.0},
	{18876, 0.0, -12.0, 0.0, 0.0, 270.0, 270.0},
	{354, -2.55, 6.4, 0.07, 0.0, 0.0, 90.0},
	{354, 2.71, 6.4, 0.07, 0.0, 0.0, 90.0},
	{354, -2.55, -13.0, 0.07, 0.0, 0.0, 90.0},
	{354, 2.71, -13.0, 0.07, 0.0, 0.0, 90.0}
};

static const droid_ship_data[][ship_part_enum] = {
	{2976, 0.0, 0.0, 0.0, 270.0, 0.0, 0.0},
	{18646, 0.0, -0.01, 0.0, 90.0, 0.0, 0.0}
};

stock ListIt:CreateInvader(invader_type_enum:type, Float:health, Float:x, Float:y, Float:z, Float:rotz)
{
	new t_invader_data[invader_struct], i;
	switch(type)
	{
		case invader_type_mother:
		{
			if((t_invader_data[invader_object_arr] = MEM::malloc(t_invader_data[invader_object_arr_len] = sizeof mother_ship_data)) == Pointer:NULL) return ListIt:NULL;
			if((t_invader_data[invader_object_data_arr] = MEM::malloc((sizeof mother_ship_data)*_:ship_part_enum)) == Pointer:NULL)
			{
				MEM::free(t_invader_data[invader_object_arr]);
				return ListIt:NULL;
			}
			for(i = 0; i < sizeof mother_ship_data; i++)
			{
				MEM::set_arr(t_invader_data[invader_object_data_arr], i*_:ship_part_enum, mother_ship_data[i]);
				MEM::set_val(t_invader_data[invader_object_arr], i, CreateDynamicObject(mother_ship_data[i][ship_part_modelid],
					((mother_ship_data[i][ship_part_x]*floatcos(360.0-rotz, degrees))+(mother_ship_data[i][ship_part_y]*floatsin(360.0-rotz, degrees)))+x, (((-mother_ship_data[i][ship_part_x])*floatsin(360.0-rotz, degrees))+(mother_ship_data[i][ship_part_y]*floatcos(360.0-rotz, degrees)))+y, mother_ship_data[i][ship_part_z]+z, mother_ship_data[i][ship_part_rotx], mother_ship_data[i][ship_part_roty], mother_ship_data[i][ship_part_rotz]+rotz));
				//MEM::set_val(t_invader_data[invader_object_arr], i, CreateDynamicObject(mother_ship_data[i][ship_part_modelid], mother_ship_data[i][ship_part_x]+x, mother_ship_data[i][ship_part_y]+y, mother_ship_data[i][ship_part_z]+z, mother_ship_data[i][ship_part_rotx], mother_ship_data[i][ship_part_roty], mother_ship_data[i][ship_part_rotz]));
			}
		}
		case invader_type_droid:
		{
			if((t_invader_data[invader_object_arr] = MEM::malloc(t_invader_data[invader_object_arr_len] = sizeof droid_ship_data)) == Pointer:NULL) return ListIt:NULL;
			if((t_invader_data[invader_object_data_arr] = MEM::malloc((sizeof droid_ship_data)*_:ship_part_enum)) == Pointer:NULL)
			{
				MEM::free(t_invader_data[invader_object_arr]);
				return ListIt:NULL;
			}
			for(i = 0; i < sizeof droid_ship_data; i++)
			{
				MEM::set_arr(t_invader_data[invader_object_data_arr], i*_:ship_part_enum, droid_ship_data[i]);
				MEM::set_val(t_invader_data[invader_object_arr], i, CreateDynamicObject(droid_ship_data[i][ship_part_modelid],
					((droid_ship_data[i][ship_part_x]*floatcos(360.0-rotz, degrees))+(droid_ship_data[i][ship_part_y]*floatsin(360.0-rotz, degrees)))+x, (((-droid_ship_data[i][ship_part_x])*floatsin(360.0-rotz, degrees))+(droid_ship_data[i][ship_part_y]*floatcos(360.0-rotz, degrees)))+y, droid_ship_data[i][ship_part_z]+z, droid_ship_data[i][ship_part_rotx], droid_ship_data[i][ship_part_roty], droid_ship_data[i][ship_part_rotz]+rotz));
			}
		}
		default: return ListIt:NULL;
	}
	t_invader_data[invader_health] = health;
	new ListIt:ret = LIST::push_back_arr(invader_list, t_invader_data);
	if(ret == ListIt:NULL)
	{
		for(i = 0; i < sizeof mother_ship_data; i++) DestroyDynamicObject(MEM::get_val(t_invader_data[invader_object_arr], i));
		MEM::free(t_invader_data[invader_object_arr]);
		MEM::free(t_invader_data[invader_object_data_arr]);
		return ListIt:NULL;
	}
	return ret;
}

stock KillInvader(ListIt:invader_it, bool:explosion = true)
{
	new Pointer:data_ptr = LIST_IT::data_ptr(invader_it), Pointer:objects_ptr = Pointer:MEM::get_val(data_ptr, invader_object_arr);
	for(new i = 0, objects_len = MEM::get_val(data_ptr, invader_object_arr_len), Float:epos[3]; i < objects_len; i++)
	{
		if(explosion)
		{
			GetDynamicObjectPos(MEM::get_val(objects_ptr, i), epos[0], epos[1], epos[2]);
			CreateExplosion(epos[0], epos[1], epos[2], 0, 3.0);
		}
		DestroyDynamicObject(MEM::get_val(objects_ptr, i));
	}
	MEM::free(objects_ptr);
	MEM::free(Pointer:MEM::get_val(data_ptr, invader_object_data_arr));
	LIST::erase(invader_list, invader_it);
}

stock KillAllInvaders(bool:explosion = true)
{
	new Pointer:data_ptr, Pointer:objects_ptr, objects_len, i, Float:epos[3];
	LIST::foreach<invader_it>(invader_list)
	{
		data_ptr = LIST_IT::data_ptr(invader_it);
		for(i = 0, objects_ptr = Pointer:MEM::get_val(data_ptr, invader_object_arr), objects_len = MEM::get_val(data_ptr, invader_object_arr_len); i < objects_len; i++)
		{
			if(explosion)
			{
				GetDynamicObjectPos(MEM::get_val(objects_ptr, i), epos[0], epos[1], epos[2]);
				CreateExplosion(epos[0], epos[1], epos[2], 0, 3.0);
			}
			DestroyDynamicObject(MEM::get_val(objects_ptr, i));
		}
		MEM::free(objects_ptr);
		MEM::free(Pointer:MEM::get_val(data_ptr, invader_object_data_arr));
	}
	LIST::clear(invader_list);
}

stock MoveInvader(ListIt:invader_it, Float:x, Float:y, Float:z, Float:speed)
{
	new Pointer:data_ptr = LIST_IT::data_ptr(invader_it), Pointer:objects_ptr = Pointer:MEM::get_val(data_ptr, invader_object_arr), Pointer:objects_data_ptr = Pointer:MEM::get_val(data_ptr, invader_object_data_arr), object_len = MEM::get_val(data_ptr, invader_object_arr_len), i, Float:objpos[3];
	for(i = 0; i < object_len; i++) StopDynamicObject(MEM::get_val(objects_ptr, i));
	GetDynamicObjectPos(MEM::get_val(objects_ptr, 0), objpos[0], objpos[1], objpos[2]);
	//new Float:rotz = acos((-1.0*(y-objpos[0]))/floatsqroot(floatpower(x-objpos[0], 2.0)+floatpower(y-objpos[1], 2.0))), t_ship_part_data[ship_part_enum];
	new Float:rotz = 180.0+asin((-(x-objpos[0]))/floatsqroot(floatpower(x-objpos[0], 2.0)+floatpower(y-objpos[1], 2.0))), t_ship_part_data[ship_part_enum];
	//if(rotz < 0.0) rotz += 360.0;
	//printf("rotation: %.4f", rotz);
	for(i = 0; i < object_len; i++)
	{
		MEM::get_arr(objects_data_ptr, i*_:ship_part_enum, t_ship_part_data);
		SetDynamicObjectPos(MEM::get_val(objects_ptr, i), (t_ship_part_data[ship_part_x]*floatcos(rotz, degrees))+(t_ship_part_data[ship_part_y]*floatsin(rotz, degrees))+objpos[0], ((-t_ship_part_data[ship_part_x])*floatsin(rotz, degrees))+(t_ship_part_data[ship_part_y]*floatcos(rotz, degrees))+objpos[1], t_ship_part_data[ship_part_z]+objpos[2]);
		//SetDynamicObjectPos(MEM::get_val(objects_ptr, i), (t_ship_part_data[ship_part_x]*floatcos(360.0-rotz, degrees))+(t_ship_part_data[ship_part_y]*floatsin(360.0-rotz, degrees))+objpos[0], ((-t_ship_part_data[ship_part_x])*floatsin(360.0-rotz, degrees))+(t_ship_part_data[ship_part_y]*floatcos(360.0-rotz, degrees))+objpos[1], t_ship_part_data[ship_part_z]+objpos[2]);
		SetDynamicObjectRot(MEM::get_val(objects_ptr, i), t_ship_part_data[ship_part_rotx], t_ship_part_data[ship_part_roty], t_ship_part_data[ship_part_rotz]+(360.0-rotz));
		MoveDynamicObject(MEM::get_val(objects_ptr, i),
			(t_ship_part_data[ship_part_x]*floatcos(rotz, degrees))+(t_ship_part_data[ship_part_y]*floatsin(rotz, degrees))+x,
			((-t_ship_part_data[ship_part_x])*floatsin(rotz, degrees))+(t_ship_part_data[ship_part_y]*floatcos(rotz, degrees))+y,
			t_ship_part_data[ship_part_z]+z,
			speed,
			t_ship_part_data[ship_part_rotx],
			t_ship_part_data[ship_part_roty],
			t_ship_part_data[ship_part_rotz]+(360.0-rotz));
	}
	//print("=====");
}

public OnShootDynamicObject(playerid, weaponid, objectid, Float:fX, Float:fY, Float:fZ)
{
	/*static string[256];
	format(string, sizeof string, "FS: [ PID: %d ] OnShootDynamicObject | WID: %d | OID: %d | fX: %.4f | fY: %.4f | fZ: %.4f", playerid, weaponid, objectid, fX, fY, fZ);
	SendClientMessageToAll(0xFF0000FF, string);*/
	new Pointer:invader_object_ptr, invader_objects, i, Pointer:data_ptr;
	LIST::foreach<invader_it>(invader_list)
	{
		invader_object_ptr = Pointer:MEM::get_val(data_ptr = LIST_IT::data_ptr(invader_it), invader_object_arr);
		invader_objects = MEM::get_val(data_ptr, invader_object_arr_len);
		for(i = 0; i < invader_objects; i++)
		{
			if(MEM::get_val(invader_object_ptr, i) != objectid) continue;
			new Float:spos[3], Float:health = (Float:MEM::get_val(data_ptr, invader_health))-100.0;
			if(health <= 0.0)
			{
				GetPlayerPos(playerid, spos[0], spos[1], spos[2]);
				PlayerPlaySound(playerid, 1139, spos[0], spos[1], spos[2]);
				KillInvader(invader_it);
				return 1;
			}
			GetDynamicObjectPos(objectid, spos[0], spos[1], spos[2]);
			PlayerPlaySound(playerid, 1139, spos[0], spos[1], spos[2]);
			MEM::set_val(data_ptr, invader_health, _:health);
			return 1;
		}
	}
	return 1;
}

public OnFilterScriptInit()
{
	MoveInvader(CreateInvader(invader_type_mother, 1000.0, 0.0, 0.0, 10.0, 0.0), float(random(3000)-random(6000)), float(random(3000)-random(6000)), 100.0, float(random(6))+2.0);
	MoveInvader(CreateInvader(invader_type_mother, 1000.0, 20.0, 0.0, 10.0, 0.0), float(random(3000)-random(6000)), float(random(3000)-random(6000)), 100.0, float(random(6))+2.0);
	MoveInvader(CreateInvader(invader_type_mother, 1000.0, 40.0, 0.0, 10.0, 0.0), float(random(3000)-random(6000)), float(random(3000)-random(6000)), 100.0, float(random(6))+2.0);
	MoveInvader(CreateInvader(invader_type_mother, 1000.0, 60.0, 0.0, 10.0, 0.0), float(random(3000)-random(6000)), float(random(3000)-random(6000)), 100.0, float(random(6))+2.0);
	MoveInvader(CreateInvader(invader_type_mother, 1000.0, 80.0, 0.0, 10.0, 0.0), float(random(3000)-random(6000)), float(random(3000)-random(6000)), 100.0, float(random(6))+2.0);
	MoveInvader(CreateInvader(invader_type_mother, 1000.0, 100.0, 0.0, 10.0, 0.0), float(random(3000)-random(6000)), float(random(3000)-random(6000)), 100.0, float(random(6))+2.0);
	MoveInvader(CreateInvader(invader_type_mother, 1000.0, 120.0, 0.0, 10.0, 0.0), float(random(3000)-random(6000)), float(random(3000)-random(6000)), 100.0, float(random(6))+2.0);
	SetTimer("UpdateMovement", 5000, 1);
	print("\n==============================");
	print("= ERMERGERD, ELEEN ENVESEEN! =");
	print("=       Made by BigETI       =");
	print("==============================\n");
	return 1;
}

public OnFilterScriptExit()
{
	KillAllInvaders();
	return 1;
}

forward UpdateMovement();
public UpdateMovement() LIST::foreach<invader_it>(invader_list) MoveInvader(invader_it, float(random(2000)-random(4000)), float(random(2000)-random(4000)), 10.0, float(random(6))+2.0);