/*
Dragonfire
Copyright (C) 2020 Elias Fleckenstein <eliasfleckenstein@web.de>

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

#include "cpp_api/s_cheats.h"
#include "cpp_api/s_base.h"
#include "cpp_api/s_internal.h"
#include "settings.h"

#include <iostream>

ScriptApiCheatsCheat::ScriptApiCheatsCheat(
		const std::string &name, const std::string &setting) :
		m_name(name),
		m_setting(setting), m_function_ref(0)
{
}

ScriptApiCheatsCheat::ScriptApiCheatsCheat(const std::string &name, const int &function) :
		m_name(name), m_setting(""), m_function_ref(function)
{
}

void ScriptApiCheatsCheat::set_info_text(std::string infoText) {
	m_info_text = infoText;
}

std::string ScriptApiCheatsCheat::get_info_text() {
	return m_info_text;
}

bool ScriptApiCheatsCheat::is_enabled()
{
	try {
		return !m_function_ref && g_settings->getBool(m_setting);
	} catch (SettingNotFoundException &) {
		return false;
	}
}

void ScriptApiCheatsCheat::toggle(lua_State *L, int error_handler)
{
	if (m_function_ref) {
		lua_rawgeti(L, LUA_REGISTRYINDEX, m_function_ref);
		lua_pcall(L, 0, 0, error_handler);
	} else
		g_settings->setBool(m_setting, !is_enabled());
}

ScriptApiCheatsCategory::ScriptApiCheatsCategory(const std::string &name) : m_name(name)
{
}

ScriptApiCheatsCategory::~ScriptApiCheatsCategory()
{
	for (auto i = m_cheats.begin(); i != m_cheats.end(); i++)
		delete *i;
}

void ScriptApiCheatsCategory::read_cheats(lua_State *L)
{
	std::vector<std::pair<std::string, ScriptApiCheatsCheat*>> cheat_pairs;

	lua_pushnil(L);
	while (lua_next(L, -2)) {
		ScriptApiCheatsCheat *cheat = nullptr;
		std::string name = lua_tostring(L, -2);
		if (lua_isstring(L, -1))
			cheat = new ScriptApiCheatsCheat(name, lua_tostring(L, -1));
		else if (lua_isfunction(L, -1)) {
			cheat = new ScriptApiCheatsCheat(
					name, luaL_ref(L, LUA_REGISTRYINDEX));
			lua_pushnil(L);
		}
		if (cheat)
			cheat_pairs.emplace_back(name, cheat);
		lua_pop(L, 1);
	}

	// Sorting cheats
	std::sort(cheat_pairs.begin(), cheat_pairs.end());

	// Assigning sorted cheats to m_cheats
	for (const auto &pair : cheat_pairs) {
		m_cheats.push_back(pair.second);
	}
}

ScriptApiCheatsCheat* ScriptApiCheatsCategory::get_cheat(const std::string &name) {
	for (auto& cheat : m_cheats) {
		if (cheat->m_name == name) 
			return cheat;
	}
	return nullptr;
}

ScriptApiCheats::~ScriptApiCheats()
{
	for (auto i = m_cheat_categories.begin(); i != m_cheat_categories.end(); i++)
		delete *i;
}

void ScriptApiCheats::init_cheats()
{
    SCRIPTAPI_PRECHECKHEADER

    lua_getglobal(L, "core");
    lua_getfield(L, -1, "cheats");
    if (!lua_istable(L, -1)) {
        lua_pop(L, 2);
        return;
    }
	
    // Collecting keys in a vector
    std::vector<std::string> keys;
    lua_pushnil(L);  // First key
    while (lua_next(L, -2) != 0) {
        if (lua_isstring(L, -2)) {
            keys.push_back(lua_tostring(L, -2));
        }
        lua_pop(L, 1);
    }

    // Sorting keys
    std::sort(keys.begin(), keys.end());

    // Iterate over sorted keys
    for (const auto &key : keys) {
        lua_pushstring(L, key.c_str());
        lua_gettable(L, -2);
        if (lua_istable(L, -1)) {
            ScriptApiCheatsCategory *category = new ScriptApiCheatsCategory(key.substr(2).c_str());
            category->read_cheats(L);
            m_cheat_categories.push_back(category);
        }
        lua_pop(L, 1);
    }

    lua_pop(L, 2);
    m_cheats_loaded = true;
}

void ScriptApiCheats::toggle_cheat(ScriptApiCheatsCheat *cheat)
{
	SCRIPTAPI_PRECHECKHEADER

	PUSH_ERROR_HANDLER(L);
	int error_handler = lua_gettop(L) - 1;
	lua_insert(L, error_handler);

	cheat->toggle(L, error_handler);
}

ScriptApiCheatsCategory* ScriptApiCheats::get_category(const std::string &name) {
    for (auto& category : m_cheat_categories) {
        if (category->m_name == name) 
            return category;
    }
    return nullptr;
}
