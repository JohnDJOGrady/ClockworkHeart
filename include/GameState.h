#ifndef GAME_STATE_H
#define GAME_STATE_H

/// <summary>
/// Author: Peter Daly, John O'Grady
/// Version: 1.0
/// Created: 17/10/2017
/// </summary>

enum class GameState
{
	SPLASH_STATE,	// Enum that represents Splash.cpp
	MENU_STATE,		// Enum that represents Menu.cpp
	PLAY_STATE,		// Enum that represents Play.cpp
	UPGRADE_STATE,	// Enum that represents Upgrade.cpp
	OPTIONS_STATE,	// Enum that represents Options.cpp
	CREDITS_STATE,	// Enum that represents Credits.cpp
	END_STATE		// Enum that represents EndScreen.cpp
};
#endif // !GAME_STATE_H
