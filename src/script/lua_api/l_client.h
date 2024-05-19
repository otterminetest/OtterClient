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

#pragma once

#include "lua_api/l_base.h"
#include "itemdef.h"
#include "tool.h"

class ModApiClient : public ModApiBase
{
private:
	// get_current_modname()
	static int l_get_current_modname(lua_State *L);

	// get_modpath(modname)
	static int l_get_modpath(lua_State *L);

	// print(text)
	static int l_print(lua_State *L);

	// display_chat_message(message)
	static int l_display_chat_message(lua_State *L);

	// send_chat_message(message)
	static int l_send_chat_message(lua_State *L);

	// clear_out_chat_queue()
	static int l_clear_out_chat_queue(lua_State *L);

	// get_player_names()
	static int l_get_player_names(lua_State *L);

	// show_formspec(name, formspec)
	static int l_show_formspec(lua_State *L);

	// send_respawn()
	static int l_send_respawn(lua_State *L);

	// disconnect()
	static int l_disconnect(lua_State *L);

	// gettext(text)
	static int l_gettext(lua_State *L);

	// get_node(pos)
	static int l_get_node_or_nil(lua_State *L);

	// get_language()
	static int l_get_language(lua_State *L);

	// get_wielded_item()
	static int l_get_wielded_item(lua_State *L);

	// get_meta(pos)
	static int l_get_meta(lua_State *L);

	// get_server_info()
	static int l_get_server_info(lua_State *L);

	// get_item_def(itemstring)
	static int l_get_item_def(lua_State *L);

	// get_node_def(nodename)
	static int l_get_node_def(lua_State *L);

	// get_privilege_list()
	static int l_get_privilege_list(lua_State *L);

	// get_builtin_path()
	static int l_get_builtin_path(lua_State *L);

	// get_csm_restrictions()
	static int l_get_csm_restrictions(lua_State *L);

	// send_damage(damage)
	static int l_send_damage(lua_State *L);

	// set_fast_speed(speed)
	static int l_set_fast_speed(lua_State *L);

	// place_node(pos)
	static int l_place_node(lua_State *L);

	// dig_node(pos)
	static int l_dig_node(lua_State *L);

	// interact(action, pointed_thing)
	static int l_interact(lua_State *L);

	// get_inventory(location)
	static int l_get_inventory(lua_State *L);

	// set_keypress(key_setting, pressed)
	static int l_set_keypress(lua_State *L);

	// drop_selected_item()
	static int l_drop_selected_item(lua_State *L);

	// get_objects_inside_radius(pos, radius)
	static int l_get_objects_inside_radius(lua_State *L);

	// get_all_objects(pos)
	static int l_get_all_objects(lua_State *L);

	// make_screenshot()
	static int l_make_screenshot(lua_State *L);

	// all_loaded_nodes()
	static int l_all_loaded_nodes(lua_State *L);

	// nodes_at(pos)
	static int l_nodes_at_block_pos(lua_State *L);

	// file_write(path, content)
	static int l_file_write(lua_State *L);

	// file_append(path, content)
	static int l_file_append(lua_State *L);

	// get_object_or_nil(objId)
	static int l_get_object_or_nil(lua_State *L);

	// get_server_url()
	static int l_get_server_url(lua_State *L);

	// can_attack()
	static int l_can_attack(lua_State *L);

	// get_inv_item_damage(index, object_id)
	static int l_get_inv_item_damage(lua_State *L);

	// get_inv_item_break(index, nodepos)
	static int l_get_inv_item_break(lua_State *L);

public:
	static void Initialize(lua_State *L, int top);
};
