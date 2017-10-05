#if defined _FILE_VEHICLES_INCLUDE_
	#endinput
#endif
#define _FILE_VEHICLES_INCLUDE_
#include <a_samp>
#include <list>

MEM::struct v_custom_data_struct
{
	v_custom_data_interior,
	v_custom_data_color[2],
	v_custom_data_paintjob,
	v_custom_data_respawn_delay
}

MEM::struct file_veh_struct
{
	file_veh_model,
	Float:file_veh_pos[3],
	Float:file_veh_rotz,
	Float:file_veh_velocity[3],
	Float:file_veh_health,
	file_veh_virtual_world,
	file_veh_params,
	file_veh_damage,
	file_veh_component[14],
	file_veh_interior,
	file_veh_color[2],
	file_veh_paintjob,
	file_veh_respawn_delay
}

new v_custom_data[MAX_VEHICLES][v_custom_data_struct];

stock FV_AddStaticVehicle(modelid, Float:spawn_x, Float:spawn_y, Float:spawn_z, Float:z_angle, color1, color2)
{
	new vehicleid = AddStaticVehicle(modelid, Float:spawn_x, Float:spawn_y, Float:spawn_z, Float:z_angle, color1, color2);
	if(vehicleid != 0)
	{
		v_custom_data[vehicleid-1][v_custom_data_color][0] = color1;
		v_custom_data[vehicleid-1][v_custom_data_color][1] = color2;
		v_custom_data[vehicleid-1][v_custom_data_respawn_delay] = 0;
	}
	return vehicleid;
}
#if defined _ALS_AddStaticVehicle
	#undef AddStaticVehicle
#else
	#define _ALS_AddStaticVehicle
#endif
#define AddStaticVehicle FV_AddStaticVehicle

stock FV_AddStaticVehicleEx(modelid, Float:spawn_x, Float:spawn_y, Float:spawn_z, Float:z_angle, color1, color2, respawn_delay)
{
	new vehicleid = AddStaticVehicleEx(modelid, Float:spawn_x, Float:spawn_y, Float:spawn_z, Float:z_angle, color1, color2, respawn_delay);
	if(vehicleid != 0)
	{
		v_custom_data[vehicleid-1][v_custom_data_color][0] = color1;
		v_custom_data[vehicleid-1][v_custom_data_color][1] = color2;
		v_custom_data[vehicleid-1][v_custom_data_respawn_delay] = respawn_delay;
	}
	return vehicleid;
}
#if defined _ALS_AddStaticVehicleEx
	#undef AddStaticVehicleEx
#else
	#define _ALS_AddStaticVehicleEx
#endif
#define AddStaticVehicleEx FV_AddStaticVehicleEx

stock FV_CreateVehicle(vehicletype, Float:x, Float:y, Float:z, Float:rotation, color1, color2, respawn_delay)
{
	new vehicleid = CreateVehicle(vehicletype, Float:x, Float:y, Float:z, Float:rotation, color1, color2, respawn_delay);
	if(vehicleid != 0)
	{
		v_custom_data[vehicleid-1][v_custom_data_color][0] = color1;
		v_custom_data[vehicleid-1][v_custom_data_color][1] = color2;
		v_custom_data[vehicleid-1][v_custom_data_respawn_delay] = respawn_delay;
	}
	return vehicleid;
}
#if defined _ALS_CreateVehicle
	#undef CreateVehicle
#else
	#define _ALS_CreateVehicle
#endif
#define CreateVehicle FV_CreateVehicle

stock FV_LinkVehicleToInterior(vehicleid, interiorid)
{
	if(GetVehicleModel(vehicleid) != 0) return 0;
	return LinkVehicleToInterior(vehicleid, v_custom_data[vehicleid-1][v_custom_data_interior] = interiorid);
}
#if defined _ALS_LinkVehicleToInterior
	#undef LinkVehicleToInterior
#else
	#define _ALS_LinkVehicleToInterior
#endif
#define LinkVehicleToInterior FV_LinkVehicleToInterior

stock FV_ChangeVehicleColor(vehicleid, color1, color2)
{
	if(GetVehicleModel(vehicleid) != 0) return 0;
	return ChangeVehicleColor(vehicleid, v_custom_data[vehicleid-1][v_custom_data_color][0] = color1, v_custom_data[vehicleid-1][v_custom_data_color][1] = color2);
}
#if defined _ALS_ChangeVehicleColor
	#undef ChangeVehicleColor
#else
	#define _ALS_ChangeVehicleColor
#endif
#define ChangeVehicleColor FV_ChangeVehicleColor

stock FV_ChangeVehiclePaintjob(vehicleid, paintjobid)
{
	if(GetVehicleModel(vehicleid) != 0) return 0;
	return ChangeVehiclePaintjob(vehicleid, v_custom_data[vehicleid-1][v_custom_data_paintjob] = paintjobid);
}
#if defined _ALS_ChangeVehiclePaintjob
	#undef ChangeVehiclePaintjob
#else
	#define _ALS_ChangeVehiclePaintjob
#endif
#define ChangeVehiclePaintjob FV_ChangeVehiclePaintjob

stock FV_DestroyVehicle(vehicleid)
{
	if(GetVehicleModel(vehicleid) == 0) return 0;
	MEM::zero(MEM::get_addr(v_custom_data[vehicleid-1][v_custom_data_interior]), v_custom_data_struct);
	return DestroyVehicle(vehicleid);
}
#if defined _ALS_DestroyVehicle
	#undef DestroyVehicle
#else
	#define _ALS_DestroyVehicle
#endif
#define DestroyVehicle FV_DestroyVehicle

stock bool:SaveAllVehicles(file_name[])
{
	static i, j, s_vdata[file_veh_struct], s_vparams[7], s_vdamage[4];
	new LIST::init<s_vehicles>;
	for(i = 1; i <= MAX_VEHICLES; i++)
	{
		if((s_vdata[file_veh_model] = GetVehicleModel(i)) == 0) continue;
		GetVehiclePos(i, s_vdata[file_veh_pos][0], s_vdata[file_veh_pos][1], s_vdata[file_veh_pos][2]);
		GetVehicleZAngle(i, s_vdata[file_veh_rotz]);
		GetVehicleVelocity(i, s_vdata[file_veh_velocity][0], s_vdata[file_veh_velocity][1], s_vdata[file_veh_velocity][2]);
		GetVehicleHealth(i, s_vdata[file_veh_health]);
		s_vdata[file_veh_virtual_world] = GetVehicleVirtualWorld(i);
		GetVehicleParamsEx(i, s_vparams[0], s_vparams[1], s_vparams[2], s_vparams[3], s_vparams[4], s_vparams[5], s_vparams[6]);
		s_vdata[file_veh_params] = ((s_vparams[0] == -1)?2:s_vparams[0])|(((s_vparams[1] == -1)?2:s_vparams[1])<<2)|(((s_vparams[2] == -1)?2:s_vparams[2])<<4)|(((s_vparams[3] == -1)?2:s_vparams[3])<<6)|(((s_vparams[4] == -1)?2:s_vparams[4])<<8)|(((s_vparams[5] == -1)?2:s_vparams[5])<<10)|(((s_vparams[6] == -1)?2:s_vparams[6])<<12);
		GetVehicleDamageStatus(i, s_vdamage[0], s_vdamage[1], s_vdamage[2], s_vdamage[3]);
		s_vdata[file_veh_damage] = s_vdamage[0]|(s_vdamage[1]<<4)|(s_vdamage[2]<<8)|(s_vdamage[3]<<12);
		for(j = 0; j < 14; j++) s_vdata[file_veh_component][j] = GetVehicleComponentInSlot(i, j);
		MEM::copy(MEM::get_addr(s_vdata[file_veh_interior]), MEM::get_addr(v_custom_data[i-1][v_custom_data_interior]), v_custom_data_struct);
		LIST::push_back_arr(s_vehicles, s_vdata);
	}
	if(LIST::save(s_vehicles, file_name, true))
	{
		for(i = 1; i <= MAX_VEHICLES; i++)
		{
			if(GetVehicleModel(i) == 0) continue;
			DestroyVehicle(i);
		}
		return true;
	}
	return false;
}

stock bool:LoadVehicles(const file_name[])
{
	static l_vdata[file_veh_struct], l_vid, i;
	new LIST::init<l_vehicles>;
	if(LIST::load(l_vehicles, file_name))
	{
		LIST::foreach<l_vehicles_it>(l_vehicles)
		{
			if(LIST_IT::data_size(l_vehicles_it) != sizeof l_vdata)
			{
				LIST::clear(l_vehicles);
				return false;
			}
			MEM::get_arr(LIST_IT::data_ptr(l_vehicles_it), _, l_vdata);
			if((l_vid = CreateVehicle(l_vdata[file_veh_model], l_vdata[file_veh_pos][0], l_vdata[file_veh_pos][1], l_vdata[file_veh_pos][2], l_vdata[file_veh_rotz], l_vdata[file_veh_color][0], l_vdata[file_veh_color][1], l_vdata[file_veh_respawn_delay])) == 0)
			{
				LIST::clear(l_vehicles);
				for(i = 1; i <= MAX_VEHICLES; i++)
				{
					if(GetVehicleModel(i) == 0) continue;
					DestroyVehicle(i);
				}
				return false;
			}
			LinkVehicleToInterior(l_vid, l_vdata[file_veh_interior]);
			ChangeVehiclePaintjob(l_vid, l_vdata[file_veh_paintjob]);
			for(i = 0; i < 14; i++) AddVehicleComponent(l_vid, l_vdata[file_veh_component][i]);
			SetVehicleHealth(l_vid, l_vdata[file_veh_health]);
			SetVehicleVirtualWorld(l_vid, l_vdata[file_veh_virtual_world]);
			SetVehicleParamsEx(l_vid, l_vdata[file_veh_params]&0x3, (l_vdata[file_veh_params]>>>2)&0x3, (l_vdata[file_veh_params]>>>4)&0x3, (l_vdata[file_veh_params]>>>6)&0x3, (l_vdata[file_veh_params]>>>8)&0x3, (l_vdata[file_veh_params]>>>10)&0x3, (l_vdata[file_veh_params]>>>12)&0x3);
			UpdateVehicleDamageStatus(l_vid, l_vdata[file_veh_damage]&0xF, (l_vdata[file_veh_damage]>>>4)&0xF, (l_vdata[file_veh_damage]>>>8)&0xF, (l_vdata[file_veh_damage]>>>12)&0xF);
			SetVehicleVelocity(l_vid, l_vdata[file_veh_velocity][0], l_vdata[file_veh_velocity][1], l_vdata[file_veh_velocity][2]);
		}
	}
	LIST::clear(l_vehicles);
	return true;
}