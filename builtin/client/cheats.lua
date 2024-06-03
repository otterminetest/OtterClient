core.cheats = {
	["1.Combat"] = {
		["AntiKnockback"] = "antiknockback",
		["AttachmentFloat"] = "float_above_parent",
	},
	["2.Movement"] = {
		["Freecam"] = "freecam",
		["AutoForward"] = "continuous_forward",
		["PitchMove"] = "pitch_move",
		--["AutoJump"] = "autojump",
		["Flight"] = "free_move",
		["Noclip"] = "noclip",
		["FastMove"] = "fast_move",
		["Jesus"] = "jesus",
		["NoSlow"] = "no_slow",
		["JetPack"] = "jetpack",
		--["AntiSlip"] = "antislip",
		["AirJump"] = "airjump",
		["Spider"] = "spider",
		["AutoSneak"] = "autosneak",
	},
	["3.Render"] = {
		["Xray"] = "xray",
		["Fullbright"] = "fullbright",
		["HUDBypass"] = "hud_flags_bypass",
		--["NoHurtCam"] = "no_hurt_cam",
		["Coords"] = "coords",
		["CheatHUD"] = "cheat_hud",
		["EntityESP"] = "enable_entity_esp",
		["EntityTracers"] = "enable_entity_tracers",
		["PlayerESP"] = "enable_player_esp",
		["PlayerTracers"] = "enable_player_tracers",
		["NodeESP"] = "enable_node_esp",
		["NodeTracers"] = "enable_node_tracers",
		["TunnelESP"] = "enable_tunnel_esp",
		["TunnelTracers"] = "enable_tunnel_tracers",
		["NoRender"] = "norender.particles",
	},
	["4.Interact"] = {
		["FastDig"] = "fastdig",
		["FastPlace"] = "fastplace",
		["AutoDig"] = "autodig",
		["AutoPlace"] = "autoplace",
		["InstantBreak"] = "instant_break",
		["FastHit"] = "spamclick",
		["AutoHit"] = "autohit",
		["AutoTool"] = "autotool",
	},
	["5.Player"] = {
		["NoFallDamage"] = "prevent_natural_damage",
		--["NoForceRotate"] = "no_force_rotate",
		["Reach"] = "reach",
		--["PointLiquids"] = "point_liquids",
		["AutoRespawn"] = "autorespawn",
		--["ThroughWalls"] = "dont_point_nodes",
	},
	["6.Misc"] = {
		["Silence"] = "silence",
	}
}

function core.register_cheat(cheatname, category, func)
	core.cheats[category] = core.cheats[category] or {}
	core.cheats[category][cheatname] = func
end
