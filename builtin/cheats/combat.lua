--[[
KillAura
--]]

local function get_punch_interval(player)
	local interval_str = core.settings:get("punch_interval")
	local interval
	if interval_str == "auto" then
		interval = player:get_wielded_item():get_tool_capabilities().full_punch_interval + 0.1
	else
		interval = tonumber(interval_str) or 0.1
	end

	if (interval <= 0) then
		interval = 0.1
	end

	if (core.settings:get_bool("spamclick")) then
		local multiplier = tonumber(core.settings:get("spamclick_multiplier")) or 6
		interval = interval / multiplier
	end

	return interval
end

core.register_on_active_object_step(function(gcao)
	if (not core.settings:get_bool("killaura.mobs") and not gcao.is_player) then return end
	if (not core.settings:get_bool("killaura.players") and gcao.is_player) then return end

	if (gcao.is_local_player) then return end

	if (not core.can_attack(gcao.id)) then return end

    local player = core.localplayer
    if (player:get_hp() <= 0) then return end

    local interval = get_punch_interval(player)

    if (player:get_time_from_last_punch() < interval) then return end

	if (gcao.hp <= 0) then return end

	local is_enemy = not player:is_player_friendly(gcao.id)
	if (not is_enemy) then return end

    local myPos = player:get_pos()
    local enemyPos = gcao.position;
	local range = player:get_wielded_item_range()^2
	local dist = (myPos.x - enemyPos.x)^2 + (myPos.y - enemyPos.y)^2 + (myPos.z - enemyPos.z)^2
	local is_close = dist <= range
	if not is_close then return end

	if (core.settings:get_bool("killaura.assist")) then
		local wield_index = player:get_wield_index() + 1
		local dmg = core.get_inv_item_damage(wield_index, gcao.id)
		if (dmg and gcao.hp - dmg.damage <= 1) then
			return
		end
	end

    player:punch(gcao.id)

    return true
end)

core.register_cheat("PlayerAura ", "Combat", "killaura.players")
core.register_cheat("MobAura", "Combat", "killaura.mobs")
core.register_cheat("AssistAura", "Combat", "killaura.assist")

core.register_chatcommand("fasthit", {
	params = "<multiplier>",
	description = "Set fasthit multiplier. Used for killaura ONLY when fasthit/spamclick is on.",
	func = function(param)
		local multiplierNum = tonumber(param)
		if multiplierNum then
			if multiplierNum > 0 then
				core.settings:set("spamclick_multiplier", tostring(multiplierNum))
				return true, "Fasthit multiplier has been set to: " .. tostring(multiplierNum) .. "."
			else
				return false, "Error: Input must be greater than 0."
			end
		else
			return false, "Error: Input must be a number."
		end
	end,
})