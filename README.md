OtterClient
===========

![showcase](doc/showcase1.png)

A minetest cheat client based off of [DragonFire](https://github.com/dragonfireclient/dragonfireclient) but on Minetest version [5.9.0-dev-df4c9e2](https://github.com/minetest/minetest/tree/df4c9e29034ed77c991d25af1891cd63e7518365).
Used code from [WaspSaliva](https://repo.or.cz/waspsaliva.git) for circular cheat menus.

Made by an actual Otter. Here's a selfie:    
<img src="https://avatars.githubusercontent.com/u/168836394" alt="otter" width="30%" />

# Features
### Cheat menu
<details>
  <summary>Combat</summary>

  - AntiKnockback
  - AttachmentFloat: float above parent
  - AutoAssist: don't completely kill your enemies. Turning this on automatically turns on PlayerAura.
  - EntityAura: auto-hit entities
  - PlayerAura: auto-hit enemy players
</details>

<details>
  <summary>Interact</summary>

  - AutoDig: automatically dig pointed block
  - AutoHit: automatically hit pointed entity
  - AutoPlace: automatically place wielded item at pointed block
  - AutoTool: automatically select best tool for digging/hitting
  - FastDig: dig at 10x speed
  - FastHit: hit at 6x speed. Can be modified using the `.fasthit <multiplier>` chat command
  - FastPlace: instant block placing
  - InstantBreak: instant block breaking
</details>

<details>
  <summary>Movement</summary>

  - AirJump: jump while in the air
  - AutoForward
  - AutoSneak: autosneak. This hides your nametag on some servers.
  - FastMove
  - Flight
  - Freecam
  - Jesus
  - JetPack
  - Noclip
  - NoSlow
  - PitchMove
  - Spider: climb walls
</details>

<details>
  <summary>Player</summary>

  - AutoRespawn
  - NoFallDamage
  - Reach: extend interact distance
</details>

<details>
  <summary>Render</summary>

  - CheatHUD: show currently toggled cheats
  - Coords: show coords in bottom left of screen
  - EntityESP: show bounding boxes around entities
  - EntityTracers: show lines to entities
  - Fullbright
  - HUDBypass
  - NodeESP: can be configured using the `.search add <(optional) node_name>` chat command
  - NodeTracers: can be configured using the `.search add <(optional) node_name>` chat command
  - NoRender: skip rendering particles to reduce client lag
  - PlayerESP: show bounding boxes around players. Green = friendly, Red = enemy. Friends can be configured using the `.friend add <(optional) player_name>` chat command.
  - PlayerTracers: show lines to players. Green = friendly, Red = enemy. Friends can be configured using the `.friend add <(optional) player_name>` chat command.
  - Xray: see blocks thru walls. Can be configured using the `.xray add <(optional) node_name>` chat command.
</details>

### Chat commands
- `.fasthit <multiplier>` set fasthit multiplier. FastHit needs to be turned on for this to be used.
- `.say <text>` send raw text
- `.tp <X> <Y> <Z>` teleport
- `.wielded` show itemstring of wielded item
- `.players` list online players
- `.kill` kill your own player
- `.sneak` toggle autosneak
- `.speed <speed>` set speed
- `.place <X> <Y> <Z>` place wielded item
- `.dig <X> <Y> <Z>` dig node
- `.break` toggle instant break
- `.setyaw <yaw>`
- `.setpitch <pitch>`
- `.respawn` respawn while in ghost mode
- `.xray`
    - `add <(optional) node_name>`: add a node to xray configuration (to see thru it). Can either add by node_name or by pointing at a node.
    - `del <(optional) node_name>`: remove a node from xray configuration
    - `list`: list xray nodes
    - `clear`: clear xray nodes
- `.search`
    - `add <(optional) node_name>`: add a node to nodeESP search. Can either add by node_name or by pointing at a node.
    - `del <(optional) node_name>`: remove a node from nodeESP search
    - `list`: list nodeESP nodes
    - `clear`: clear nodeESP nodes
- `.friend`
    - `add <(optional) player_name>`: add a friend. Can either add by player_name or by pointing at a player. Friends are server-specific.
    - `del <(optional) player_name>`: remove a friend
    - `list`: list all friends for the current server
    - `clear`: remove all friends for the current server
- `.ctf`
    - `add`: add current server to ctf servers list
    - `del`: delete current server from ctf servers list
    - `list`: view ctf servers list
    - `clear`: clear ctf servers list

### Misc
- Randomize Version: randomize the version OtterClient tells the server. Can be toggled in the settings tab.

# Compiling
- [Compiling on GNU/Linux](doc/compiling/linux.md)
- [Compiling on Windows](doc/compiling/windows.md)
- [Compiling on MacOS](doc/compiling/macos.md)