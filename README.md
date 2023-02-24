# AGRV
A mini console rpg game

It is a console turn based game, user can use skills to buff its stats. Skills lasts a defined quantity of rounds and does have its own cooldown/mana cost. 
Winning player is the one who killed the another one.

The main logic (as well as the game loop) is inside GameManager.cpp.
Skills are managed by SkillStack, member object of every player.
A round passes at the beginning of the player's round.
Skills infos are inside GameSrc/.h.

