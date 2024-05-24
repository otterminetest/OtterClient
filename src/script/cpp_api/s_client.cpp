/*
Minetest
Copyright (C) 2013 celeron55, Perttu Ahola <celeron55@gmail.com>
Copyright (C) 2017 nerzhul, Loic Blot <loic.blot@unix-experience.fr>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#include <iostream>
#include "s_client.h"
#include "s_internal.h"
#include "client/client.h"
#include "common/c_converter.h"
#include "common/c_content.h"
#include "lua_api/l_item.h"
#include "itemdef.h"
#include "s_item.h"

void ScriptApiClient::on_mods_loaded()
{
	SCRIPTAPI_PRECHECKHEADER

	// Get registered shutdown hooks
	lua_getglobal(L, "core");
	lua_getfield(L, -1, "registered_on_mods_loaded");
	// Call callbacks
	try {
		runCallbacks(0, RUN_CALLBACKS_MODE_FIRST);
	} catch (LuaError &e) {
		getClient()->setFatalError(e);
	}
}

void ScriptApiClient::on_shutdown()
{
	SCRIPTAPI_PRECHECKHEADER

	// Get registered shutdown hooks
	lua_getglobal(L, "core");
	lua_getfield(L, -1, "registered_on_shutdown");
	// Call callbacks
	try {
		runCallbacks(0, RUN_CALLBACKS_MODE_FIRST);
	} catch (LuaError &e) {
		getClient()->setFatalError(e);
	}
}

bool ScriptApiClient::on_sending_message(const std::string &message)
{
	SCRIPTAPI_PRECHECKHEADER

	// Get core.registered_on_chat_messages
	lua_getglobal(L, "core");
	lua_getfield(L, -1, "registered_on_sending_chat_message");
	// Call callbacks
	lua_pushstring(L, message.c_str());
	try {
		runCallbacks(1, RUN_CALLBACKS_MODE_OR_SC);
	} catch (LuaError &e) {
		getClient()->setFatalError(e);
		return true;
	}
	return readParam<bool>(L, -1);
}

bool ScriptApiClient::on_receiving_message(const std::string &message)
{
	SCRIPTAPI_PRECHECKHEADER

	// Get core.registered_on_chat_messages
	lua_getglobal(L, "core");
	lua_getfield(L, -1, "registered_on_receiving_chat_message");
	// Call callbacks
	lua_pushstring(L, message.c_str());
	try {
		runCallbacks(1, RUN_CALLBACKS_MODE_OR_SC);
	} catch (LuaError &e) {
		getClient()->setFatalError(e);
		return true;
	}
	return readParam<bool>(L, -1);
}

void ScriptApiClient::on_damage_taken(int32_t damage_amount)
{
	SCRIPTAPI_PRECHECKHEADER

	// Get core.registered_on_chat_messages
	lua_getglobal(L, "core");
	lua_getfield(L, -1, "registered_on_damage_taken");
	// Call callbacks
	lua_pushinteger(L, damage_amount);
	try {
		runCallbacks(1, RUN_CALLBACKS_MODE_OR_SC);
	} catch (LuaError &e) {
		getClient()->setFatalError(e);
	}
}

void ScriptApiClient::on_hp_modification(int32_t newhp)
{
	SCRIPTAPI_PRECHECKHEADER

	// Get core.registered_on_chat_messages
	lua_getglobal(L, "core");
	lua_getfield(L, -1, "registered_on_hp_modification");
	// Call callbacks
	lua_pushinteger(L, newhp);
	try {
		runCallbacks(1, RUN_CALLBACKS_MODE_OR_SC);
	} catch (LuaError &e) {
		getClient()->setFatalError(e);
	}
}

void ScriptApiClient::on_death()
{
	SCRIPTAPI_PRECHECKHEADER

	// Get registered shutdown hooks
	lua_getglobal(L, "core");
	lua_getfield(L, -1, "registered_on_death");
	// Call callbacks
	try {
		runCallbacks(0, RUN_CALLBACKS_MODE_FIRST);
	} catch (LuaError &e) {
		getClient()->setFatalError(e);
	}
}

void ScriptApiClient::environment_step(float dtime)
{
	SCRIPTAPI_PRECHECKHEADER

	// Get core.registered_globalsteps
	lua_getglobal(L, "core");
	lua_getfield(L, -1, "registered_globalsteps");
	// Call callbacks
	lua_pushnumber(L, dtime);
	try {
		runCallbacks(1, RUN_CALLBACKS_MODE_FIRST);
	} catch (LuaError &e) {
		getClient()->setFatalError(e);
	}
}

void ScriptApiClient::on_formspec_input(const std::string &formname,
	const StringMap &fields)
{
	SCRIPTAPI_PRECHECKHEADER

	// Get core.registered_on_chat_messages
	lua_getglobal(L, "core");
	lua_getfield(L, -1, "registered_on_formspec_input");
	// Call callbacks
	// param 1
	lua_pushstring(L, formname.c_str());
	// param 2
	lua_newtable(L);
	StringMap::const_iterator it;
	for (it = fields.begin(); it != fields.end(); ++it) {
		const std::string &name = it->first;
		const std::string &value = it->second;
		lua_pushstring(L, name.c_str());
		lua_pushlstring(L, value.c_str(), value.size());
		lua_settable(L, -3);
	}
	try {
		runCallbacks(2, RUN_CALLBACKS_MODE_OR_SC);
	} catch (LuaError &e) {
		getClient()->setFatalError(e);
	}
}

bool ScriptApiClient::on_dignode(v3s16 p, MapNode node)
{
	SCRIPTAPI_PRECHECKHEADER

	// Get core.registered_on_dignode
	lua_getglobal(L, "core");
	lua_getfield(L, -1, "registered_on_dignode");

	// Push data
	push_v3s16(L, p);
	pushnode(L, node);

	// Call functions
	try {
		runCallbacks(2, RUN_CALLBACKS_MODE_OR);
	} catch (LuaError &e) {
		getClient()->setFatalError(e);
		return true;
	}
	return lua_toboolean(L, -1);
}

bool ScriptApiClient::on_punchnode(v3s16 p, MapNode node)
{
	SCRIPTAPI_PRECHECKHEADER

	// Get core.registered_on_punchgnode
	lua_getglobal(L, "core");
	lua_getfield(L, -1, "registered_on_punchnode");

	// Push data
	push_v3s16(L, p);
	pushnode(L, node);

	// Call functions
	try {
		runCallbacks(2, RUN_CALLBACKS_MODE_OR);
	} catch (LuaError &e) {
		getClient()->setFatalError(e);
		return true;
	}
	return readParam<bool>(L, -1);
}

bool ScriptApiClient::on_placenode(const PointedThing &pointed, const ItemDefinition &item)
{
	SCRIPTAPI_PRECHECKHEADER

	// Get core.registered_on_placenode
	lua_getglobal(L, "core");
	lua_getfield(L, -1, "registered_on_placenode");

	// Push data
	push_pointed_thing(L, pointed, true);
	push_item_definition(L, item);

	// Call functions
	try {
		runCallbacks(2, RUN_CALLBACKS_MODE_OR);
	} catch (LuaError &e) {
		getClient()->setFatalError(e);
		return true;
	}
	return readParam<bool>(L, -1);
}

bool ScriptApiClient::on_item_use(const ItemStack &item, const PointedThing &pointed)
{
	SCRIPTAPI_PRECHECKHEADER

	// Get core.registered_on_item_use
	lua_getglobal(L, "core");
	lua_getfield(L, -1, "registered_on_item_use");

	// Push data
	LuaItemStack::create(L, item);
	push_pointed_thing(L, pointed, true);

	// Call functions
	try {
		runCallbacks(2, RUN_CALLBACKS_MODE_OR);
	} catch (LuaError &e) {
		getClient()->setFatalError(e);
		return true;
	}
	return readParam<bool>(L, -1);
}

bool ScriptApiClient::on_inventory_open(Inventory *inventory)
{
	SCRIPTAPI_PRECHECKHEADER

	lua_getglobal(L, "core");
	lua_getfield(L, -1, "registered_on_inventory_open");

	push_inventory_lists(L, *inventory);

	try {
		runCallbacks(1, RUN_CALLBACKS_MODE_OR);
	} catch (LuaError &e) {
		getClient()->setFatalError(e);
		return true;
	}
	return readParam<bool>(L, -1);
}

bool ScriptApiClient::on_block_data(v3s16 pos)
{
	SCRIPTAPI_PRECHECKHEADER

	//std::cout << "ScriptAPIClient: " << pos.X << ", " << pos.Y << ", " << pos.Z << "\n";

	lua_getglobal(L, "core");
	lua_getfield(L, -1, "registered_on_block_data");

	// Push data
	push_v3s16(L, pos);

	// Call functions
	try {
		runCallbacks(1, RUN_CALLBACKS_MODE_OR_SC);
		return true;
	} catch (LuaError &e) {
		getClient()->setFatalError(e);
		return false;
	}
}

bool ScriptApiClient::on_player_join(std::string name)
{
	SCRIPTAPI_PRECHECKHEADER

	lua_getglobal(L, "core");
	lua_getfield(L, -1, "registered_on_player_join");

	lua_pushstring(L, name.c_str());
	try {
		runCallbacks(1, RUN_CALLBACKS_MODE_OR_SC);
	} catch (LuaError &e) {
		getClient()->setFatalError(e);
		return true;
	}
	return readParam<bool>(L, -1);
}

bool ScriptApiClient::on_player_leave(std::string name)
{
	SCRIPTAPI_PRECHECKHEADER

	lua_getglobal(L, "core");
	lua_getfield(L, -1, "registered_on_player_leave");

	lua_pushstring(L, name.c_str());
	try {
		runCallbacks(1, RUN_CALLBACKS_MODE_OR_SC);
	} catch (LuaError &e) {
		getClient()->setFatalError(e);
		return true;
	}
	return readParam<bool>(L, -1);
}

bool ScriptApiClient::on_add_active_object(u16 id, u8 type)
{
	SCRIPTAPI_PRECHECKHEADER

	lua_getglobal(L, "core");
	lua_getfield(L, -1, "registered_on_add_active_object");

	lua_newtable(L);
	lua_pushinteger(L, id);
	lua_setfield(L, -2, "id");
	lua_pushinteger(L, type);
	lua_setfield(L, -2, "type");

	try {
		runCallbacks(1, RUN_CALLBACKS_MODE_OR_SC);
	} catch (LuaError &e) {
		getClient()->setFatalError(e);
		return true;
	}
	return readParam<bool>(L, -1);
}

bool ScriptApiClient::on_remove_active_object(u16 id)
{
	SCRIPTAPI_PRECHECKHEADER

	lua_getglobal(L, "core");
	lua_getfield(L, -1, "registered_on_remove_active_object");

	lua_pushinteger(L, id);

	try {
		runCallbacks(1, RUN_CALLBACKS_MODE_OR_SC);
	} catch (LuaError &e) {
		getClient()->setFatalError(e);
		return true;
	}
	return readParam<bool>(L, -1);
}

bool ScriptApiClient::on_active_object_update_position(GenericCAO *gcao)
{
	SCRIPTAPI_PRECHECKHEADER

	lua_getglobal(L, "core");
	lua_getfield(L, -1, "registered_on_active_object_update_position");

	//push_generic_cao
	lua_newtable(L);
	lua_pushnumber(L, gcao->getId());
	lua_setfield(L, -2, "id");
	lua_pushboolean(L, gcao->isPlayer());
	lua_setfield(L, -2, "is_player");
	lua_pushboolean(L, gcao->isLocalPlayer());
	lua_setfield(L, -2, "is_local_player");
	lua_pushboolean(L, gcao->isVisible());
	lua_setfield(L, -2, "is_visible");
	lua_pushstring(L, gcao->getName().c_str());
	lua_setfield(L, -2, "name");
	push_v3f(L, gcao->getPosition() / BS);
	lua_setfield(L, -2, "position");
	push_v3f(L, gcao->getVelocity() / BS);
	lua_setfield(L, -2, "velocity");
	push_v3f(L, gcao->getAcceleration());
	lua_setfield(L, -2, "acceleration");
	push_v3f(L, gcao->getRotation());
	lua_setfield(L, -2, "rotation");
	lua_pushnumber(L, gcao->getHp());
	lua_setfield(L, -2, "hp");
	lua_pushboolean(L, gcao->isImmortal());
	lua_setfield(L, -2, "is_immortal");
	lua_pushboolean(L, gcao->collideWithObjects());
	lua_setfield(L, -2, "collide_with_objects");
	push_object_properties(L, &gcao->getProperties());
	lua_setfield(L, -2, "props");

	try {
		runCallbacks(1, RUN_CALLBACKS_MODE_OR_SC);
	} catch (LuaError &e) {
		getClient()->setFatalError(e);
		return true;
	}
	return readParam<bool>(L, -1);
}

bool ScriptApiClient::on_active_object_step(float dtime, GenericCAO *gcao)
{
	SCRIPTAPI_PRECHECKHEADER

	lua_getglobal(L, "core");
	lua_getfield(L, -1, "registered_on_active_object_step");

	//push_generic_cao, but with dtime
	lua_newtable(L);
	lua_pushnumber(L, dtime);
	lua_setfield(L, -2, "dtime");
	lua_pushnumber(L, gcao->getId());
	lua_setfield(L, -2, "id");
	lua_pushboolean(L, gcao->isPlayer());
	lua_setfield(L, -2, "is_player");
	lua_pushboolean(L, gcao->isLocalPlayer());
	lua_setfield(L, -2, "is_local_player");
	lua_pushboolean(L, gcao->isVisible());
	lua_setfield(L, -2, "is_visible");
	lua_pushstring(L, gcao->getName().c_str());
	lua_setfield(L, -2, "name");
	push_v3f(L, gcao->getPosition() / BS);
	lua_setfield(L, -2, "position");
	push_v3f(L, gcao->getVelocity() / BS);
	lua_setfield(L, -2, "velocity");
	push_v3f(L, gcao->getAcceleration());
	lua_setfield(L, -2, "acceleration");
	push_v3f(L, gcao->getRotation());
	lua_setfield(L, -2, "rotation");
	lua_pushnumber(L, gcao->getHp());
	lua_setfield(L, -2, "hp");
	lua_pushboolean(L, gcao->isImmortal());
	lua_setfield(L, -2, "is_immortal");
	lua_pushboolean(L, gcao->collideWithObjects());
	lua_setfield(L, -2, "collide_with_objects");
	push_object_properties(L, &gcao->getProperties());
	lua_setfield(L, -2, "props");


	try {
		runCallbacks(1, RUN_CALLBACKS_MODE_OR_SC);
	} catch (LuaError &e) {
		getClient()->setFatalError(e);
		return true;
	}
	return readParam<bool>(L, -1);
}

bool ScriptApiClient::on_active_object_update_bones(float dtime, GenericCAO *gcao)
{
	SCRIPTAPI_PRECHECKHEADER

	lua_getglobal(L, "core");
	lua_getfield(L, -1, "registered_on_active_object_step");

	//push_generic_cao, but with dtime
	lua_newtable(L);
	lua_pushnumber(L, dtime);
	lua_setfield(L, -2, "dtime");
	lua_pushnumber(L, gcao->getId());
	lua_setfield(L, -2, "id");
	lua_pushboolean(L, gcao->isPlayer());
	lua_setfield(L, -2, "is_player");
	lua_pushboolean(L, gcao->isLocalPlayer());
	lua_setfield(L, -2, "is_local_player");
	lua_pushboolean(L, gcao->isVisible());
	lua_setfield(L, -2, "is_visible");
	lua_pushstring(L, gcao->getName().c_str());
	lua_setfield(L, -2, "name");
	push_v3f(L, gcao->getPosition() / BS);
	lua_setfield(L, -2, "position");
	push_v3f(L, gcao->getVelocity() / BS);
	lua_setfield(L, -2, "velocity");
	push_v3f(L, gcao->getAcceleration());
	lua_setfield(L, -2, "acceleration");
	push_v3f(L, gcao->getRotation());
	lua_setfield(L, -2, "rotation");
	lua_pushnumber(L, gcao->getHp());
	lua_setfield(L, -2, "hp");
	lua_pushboolean(L, gcao->isImmortal());
	lua_setfield(L, -2, "is_immortal");
	lua_pushboolean(L, gcao->collideWithObjects());
	lua_setfield(L, -2, "collide_with_objects");
	push_object_properties(L, &gcao->getProperties());
	lua_setfield(L, -2, "props");


	try {
		runCallbacks(1, RUN_CALLBACKS_MODE_OR_SC);
	} catch (LuaError &e) {
		getClient()->setFatalError(e);
		return true;
	}
	return readParam<bool>(L, -1);
}


v3f ScriptApiClient::get_send_speed(v3f speed)
{
	SCRIPTAPI_PRECHECKHEADER

	PUSH_ERROR_HANDLER(L);
	int error_handler = lua_gettop(L) - 1;
	lua_insert(L, error_handler);

	lua_getglobal(L, "core");
	lua_getfield(L, -1, "get_send_speed");
	if (lua_isfunction(L, -1)) {
		speed /= BS;
		push_v3f(L, speed);
		lua_pcall(L, 1, 1, error_handler);
		speed = read_v3f(L, -1);
		speed *= BS;
	}

	return speed;
}

void ScriptApiClient::setEnv(ClientEnvironment *env)
{
	ScriptApiBase::setEnv(env);
}