#ifndef PLAY_H
#define PLAY_H

/// /// <summary>
/// Author: Peter Daly, John O'Grady
/// Version: 1.0
/// Created: 18/10/2017
/// </summary>

#include <SFML\Graphics.hpp>
#include "GameState.h"
#include <Thor\Resources.hpp>
#include <Thor\Particles.hpp>
#include <Thor\Math.hpp>
#include "ResourceManager.h"
#include "Controller.h"
#include "Screen.h"
#include "Player.h"
#include "Platform.h"
#include "Lever.h"
#include "Door.h"
#include "jumpPad.h"
#include "PressurePlate.h"
#include <math.h>

class Play : public Screen
{
	const sf::Time TIME_PER_UPDATE = sf::microseconds(1000); // Initialising the TIME_PER_UPDATE variable for the splash transition.

public:

	Play(GameState *gameState, int currentLevel, LevelData *level);	// Constructor for the splash object.
	~Play();	// Deconstructor for the splash object.

	virtual void update(Controller * controller, sf::Time dt) override;
	virtual void render(sf::RenderWindow & window) override;
	void checkCollision();
	void checkLever();
	void checkDoor();
	void checkJumpPad(JumpPad * jump);
	void checkPlate();
	void transitionToNext();

private:

	void addEmitter(sf::Vector2f pos, sf::Vector2f halfSize); // Function to add am emitter to the the particle system
	void initialiseObjects();

	void leverPulled(); // Function to change to the next level

	float getMag(sf::Vector2f v);
	GameState *m_state;	// A pointer to the current gamestate

	// Background variables
	sf::Texture m_backgroundTex;
	sf::Sprite m_backgroundSprite;

	Player m_player;	// Pointer to the player object
	NPC* m_testNPC;	// Pointer to the npc object
	std::vector<Platform*> m_levelEntities;	// A vector of pointers to platform objects
	Lever *m_lever;	// Pointer to the lever object
	Door *m_door;	// Pointer to the door object
	JumpPad * m_jumpPad;	// Pointer to the door object
	JumpPad * m_otherjumpPad;	// Pointer to the door object
	PressurePlate *m_pressurePlate; // Pressure Plate for the activating objects;
	Controller * m_controller;	// Pointer to the controller object
	int level;	// Integer to store which level it is
	LevelData *m_level;	// The level data that will be loaded


	std::vector<sf::Vector2f> m_positions = {};	// Player starting level positions
	std::vector<sf::Vector2f> m_doorPositions = {};	// Door starting level positions
	std::vector<sf::Vector2f> m_leverPositions = {};	// Lever starting level positions
	std::vector<sf::Vector2f> m_npcPositions = {};	// NPC starting level positions
	std::vector<sf::Vector2f> m_jumpPadPositions = {};	// jump pad starting level positions
	std::vector<sf::Vector2f> m_jumpPadDirections = {};	// jump pad starting level direction
	std::vector<sf::Vector2f> m_pressurePlatePos = {}; // temp vector contain positions of pressure plates

	int m_firstPlatform = 0;	// Variable to mark the first platform to be drawn
	int m_lastPlatform = 6;		// Variable to mark the last platform to be drawn

	sf::Shader m_shader;	// Shader for the background
	float m_time;	

	thor::ParticleSystem m_system; // Particle Sytem
	sf::Texture m_particleTex; // Texture for the particles
	thor::UniversalEmitter m_emitter;  // An emitter for the particle system

	sf::Clock m_clock;	// A clock object

	bool controlNPC = false; // Bool for whether or not the player is controlling the NPC
};

#endif // !PLAY_H

