-- Minetest: builtin/client/chatcommands.lua

core.register_on_sending_chat_message(function(message)
	if message:sub(1,2) == ".." then
		return false
	end

	local first_char = message:sub(1,1)
	if first_char == "/" or first_char == "." then
		core.display_chat_message(core.gettext("Issued command: ") .. message)
	end

	if first_char ~= "." then
		return false
	end

	local cmd, param = string.match(message, "^%.([^ ]+) *(.*)")
	param = param or ""

	if not cmd then
		core.display_chat_message("-!- " .. core.gettext("Empty command."))
		return true
	end

	-- Run core.registered_on_chatcommand callbacks.
	if core.run_callbacks(core.registered_on_chatcommand, 5, cmd, param) then
		return true
	end

	local cmd_def = core.registered_chatcommands[cmd]
	if cmd_def then
		core.set_last_run_mod(cmd_def.mod_origin)
		local _, result = cmd_def.func(param)
		if result then
			core.display_chat_message(result)
		end
	else
		core.display_chat_message("-!- " .. core.gettext("Invalid command: ") .. cmd)
	end

	return true
end)

core.register_chatcommand("say", {
	description = "Send raw text",
	func = function(text)
		core.send_chat_message(text)
		return true
	end,
})

core.register_chatcommand("tp", {
	params = "<X> <Y> <Z>",
	description = "Teleport to coordinates.",
	func = function(param)
		local success, pos = core.parse_pos(param)
		if success then
			core.localplayer:set_pos(pos)
			return true, "Teleporting to " .. core.pos_to_string(pos)
		end
		return false, pos
	end,
})

core.register_chatcommand("wielded", {
	description = "Print itemstring of wielded item",
	func = function()
		return true, core.localplayer:get_wielded_item():to_string()
	end
})

core.register_chatcommand("players", {
	description = core.gettext("List online players"),
	func = function(param)
		local player_names = core.get_player_names()
		if not player_names then
			return false, core.gettext("This command is disabled by server.")
		end

		local players = table.concat(player_names, ", ")
		return true, core.gettext("Online players: ") .. players
	end
})

core.register_chatcommand("kill", {
	description = "Kill yourself",
	func = function()
		core.send_damage(10000)
	end,
})

core.register_chatcommand("sneak", {
	description = "Toggle autosneak on/off",
	func = function()
		local autosneak = minetest.settings:get_bool("autosneak")
		minetest.settings:set_bool("autosneak", not autosneak)
	end,
})

core.register_chatcommand("speed", {
	params = "<speed>",
	description = "Set speed.",
	func = function(param)
		local success, newspeed = core.parse_num(param)
		if success then
			core.set_fast_speed(newspeed)
			return true, "Speed set to " .. newspeed
		end
		return false, "Invalid speed input (" .. param .. ")"
	end,
})

core.register_chatcommand("place", {
	params = "<X> <Y> <Z>",
	description = "Place wielded item",
	func = function(param)
		if param == "" then
			local myPos = core.localplayer:get_pos()
			myPos.y = myPos.y - 1;
			core.place_node(myPos)
			return true, "Node placed at " .. core.pos_to_string(myPos)
		end

		local success, pos = core.parse_pos(param)
		if success then
			core.place_node(pos)
			return true, "Node placed at " .. core.pos_to_string(pos)
		end

		return false, "Invalid position"
	end,
})

core.register_chatcommand("dig", {
	params = "<X>,<Y>,<Z>",
	description = "Dig node",
	func = function(param)
		local success, pos = core.parse_pos(param)
		if success then
			core.dig_node(pos)
			return true, "Node at " .. core.pos_to_string(pos) .. " dug"
		end
		return false, pos
	end,
})

core.register_chatcommand("break", {
	description = "Toggle instant break on/off",
	func = function()
		local instant_break = minetest.settings:get_bool("instant_break")
		minetest.settings:set_bool("instant_break", not instant_break)
	end,
})


core.register_chatcommand("disconnect", {
	description = core.gettext("Exit to main menu"),
	func = function(param)
		core.disconnect()
	end,
})

core.register_chatcommand("clear_chat_queue", {
	description = core.gettext("Clear the out chat queue"),
	func = function(param)
		core.clear_out_chat_queue()
		return true, core.gettext("The out chat queue is now empty.")
	end,
})

core.register_chatcommand("setyaw", {
	params = "<yaw>",
	description = "Set your yaw",
	func = function(param)
		local yaw = tonumber(param)
		if yaw then
			core.localplayer:set_yaw(yaw)
			return true
		else
			return false, "Invalid usage (See .help setyaw)"
		end
	end
})

core.register_chatcommand("setpitch", {
	params = "<pitch>",
	description = "Set your pitch",
	func = function(param)
		local pitch = tonumber(param)
		if pitch then
			core.localplayer:set_pitch(pitch)
			return true
		else
			return false, "Invalid usage (See .help setpitch)"
		end
	end
})

function core.run_server_chatcommand(cmd, param)
	core.send_chat_message("/" .. cmd .. " " .. param)
end

core.register_list_command("xray", "Configure X-Ray", "xray_nodes")
core.register_list_command("search", "Configure NodeESP", "node_esp_nodes")
core.register_player_list_command("friend", "Configure Friends.", "friends")
core.register_server_list_command("ctf", "Configure CTF servers.", "ctf_servers")
