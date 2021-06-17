#include "Play.h"

Play::Play(GameState *gameState,  int currentLevel, LevelData *leveldata) :
	 level(currentLevel), m_level(leveldata)
{
	// Assigns a background texture to a sprite
	m_backgroundTex = ResourceManager::instance().m_holder["MenuBG"];
	m_backgroundSprite.setTexture(m_backgroundTex);

	// Assigns the particle texture to the particle system
	m_particleTex = ResourceManager::instance().m_holder["Particle"];
	m_system.setTexture(m_particleTex);
	
	m_state = gameState;	// Sets up the game state

	// Initialises the base objects within the game
	m_testNPC = new NPC();
	m_lever = new Lever();
	m_door = new Door();
	m_jumpPad = new JumpPad();
	m_otherjumpPad = new JumpPad();
	m_pressurePlate = new PressurePlate();
	
	initialiseObjects();

	// Loads in the background shader
	if (!m_shader.loadFromFile("BGShader.txt", sf::Shader::Fragment))
		std::cout << "Shader not loaded";

	// Sets up the shader
	m_shader.setUniform("resolution", sf::Vector2f(1920, 1080));
	m_shader.setUniform("time", 0.0f);

	m_time = 0;	// Sets the time to 0
	m_otherjumpPad->m_sprite.setRotation(90);
}

// Destructor function
Play::~Play()
{

}

// Function to assign all the level data that has been loaded in
// to all the objects within this game state
void Play::initialiseObjects()
{
	for (PlayerData const &node : m_level->m_player)
	{
		m_positions.push_back(node.m_position);
	}
	for (DoorData const &node : m_level->m_door)
	{
		m_doorPositions.push_back(node.m_position);
	}
	for (JumpData const &node : m_level->m_jump)
	{
		m_jumpPadPositions.push_back(node.m_position);
		m_jumpPadDirections.push_back(node.m_direction);
	}
	for (PressurePlateData const &node : m_level->m_plates)
	{
		m_pressurePlatePos.push_back(node.m_position);
	}

	for (LeverData const &node : m_level->m_lever)
	{
		m_leverPositions.push_back(node.m_position);
	}
	for (NPCData const &node : m_level->m_npc)
	{
		m_npcPositions.push_back(node.m_position);
	}

	for (PlatformData const &node : m_level->m_platforms)
	{
		m_levelEntities.push_back(new Platform(sf::Vector2f(node.m_position.x, node.m_position.y),node.m_rotation));
	}

	m_lever->m_position = m_leverPositions.at(0);
	m_door->m_position = m_doorPositions.at(0);
	m_jumpPad->m_position = m_jumpPadPositions.at(0);
	m_jumpPad->m_direction = m_jumpPadDirections.at(0);
	m_testNPC->m_position = m_npcPositions.at(0);
	m_pressurePlate->m_position = m_pressurePlatePos.at(0);
	m_otherjumpPad->m_position = m_jumpPadPositions.at(0);
	m_otherjumpPad->m_direction = m_jumpPadDirections.at(0);
}

void Play::leverPulled()
{
	if (level == 1)
	{
		addEmitter(m_levelEntities.at(1)->m_position, sf::Vector2f(m_levelEntities.at(1)->dimensions.width / 2, m_levelEntities.at(1)->dimensions.height / 2));
		m_levelEntities.at(1) = new Platform(sf::Vector2f(-1000, -1000), 0);
	}
	if (level == 2)
	{
		addEmitter(m_levelEntities.at(7)->m_position, sf::Vector2f(m_levelEntities.at(7)->dimensions.width / 2, m_levelEntities.at(7)->dimensions.height / 2));
		m_levelEntities.at(7) = new Platform(sf::Vector2f(-1000, -1000), 0);
	}
	if (level == 3)
	{
		addEmitter(m_levelEntities.at(15)->m_position, sf::Vector2f(m_levelEntities.at(15)->dimensions.width / 2, m_levelEntities.at(15)->dimensions.height / 2));
		m_levelEntities.at(15) = new Platform(sf::Vector2f(-1000, -1000), 0);
	}
	m_lever->activate();
}

// Function to update the play screen
void Play::update(Controller * controller, sf::Time dt)
{
	m_system.update(m_clock.restart()); // Updates the particle system
	m_time += dt.asMilliseconds();	// Increments the time
	m_shader.setUniform("time", m_time);	// Sets the time of the shader
	
	m_controller = controller;	// Takes in the controller object
	if (m_controller->m_currentState.LB && !m_controller->m_previousState.LB)
	{
		controlNPC = false;
	}
	if (m_controller->m_currentState.RB && !m_controller->m_previousState.RB)
	{
		controlNPC = true;
	}
	checkCollision();	// Checks collision

	if (!controlNPC)
	{
		m_player.update(m_controller, dt, true);	// Updates player based on controller input
		m_testNPC->update(m_controller, dt, false);	// Updates player based on controller input
	}
	else
	{
		m_player.update(m_controller, dt, false);	// Updates player based on controller input
		m_testNPC->update(m_controller, dt, true);	// Updates the NPC
	}
	
	 
	checkLever();	// Checks if the lever has been pressed
	checkDoor();	// Checks if the door has been pressed
	checkJumpPad(m_jumpPad); // checks if the jump pad has been run over
	checkJumpPad(m_otherjumpPad); // checks if the jump pad has been run over
	if (level == 4 || level == 5)
	{
		checkPlate(); // check if a plate has been stepped on
	}
}


// Function to render all objects in the game screen
void Play::render(sf::RenderWindow & window)
{
	window.clear(sf::Color::Black);	// Clears the game screen
	window.draw(m_backgroundSprite, &m_shader);	// Draws the background sprite
	m_door->render(window);	// Renders the door
	m_jumpPad->render(window);
	m_otherjumpPad->render(window);
	m_pressurePlate->render(window);
	m_player.render(window);	// Draws the player
	m_testNPC->render(window);	// Draws the NPC
	for (int i = m_firstPlatform; i < m_lastPlatform ; i++)
	{	// Draws the platforms specific to that level
		m_levelEntities.at(i)->render(window);	
	}
	m_lever->render(window);	// Draws the lever
	window.draw(m_system);
	
}

// Function to call the collsion checking functions for the player and the NPC
void Play::checkCollision()
{
	for (int i = m_firstPlatform; i < m_lastPlatform; i++)
	{
		m_player.collisions(m_levelEntities.at(i));
		m_testNPC->collisions(m_levelEntities.at(i));
	}
}

void Play::checkLever()
{
	sf::Vector2f distanceBetween = m_player.m_position - m_lever->m_position;
	sf::Vector2f dist = *m_testNPC->getPos() - m_lever->m_position;
	if ((getMag(distanceBetween) < 30 || getMag(dist) < 30) && m_controller->m_currentState.X && !m_controller->m_previousState.X && !m_lever->m_activated)
	{
		leverPulled();
	}
}

void Play::checkDoor()
{
	sf::Vector2f distanceBetween = m_player.m_position - m_door->m_position;
	sf::Vector2f dist = *m_testNPC->getPos() - m_door->m_position;
	if ((getMag(distanceBetween) < 50 || getMag(dist) < 50) && m_controller->m_currentState.X && !m_controller->m_previousState.X && m_door->m_closed == false)
	{
		m_door->activate();
		level++;
		if (level == 4 || level == 5)
		{
			m_door->m_closed = true;
		}
		transitionToNext();
	}
}

void Play::checkJumpPad(JumpPad * jump)
{
	sf::Vector2f distanceBetween = m_player.m_position - jump->m_position;
	sf::Vector2f dist = *m_testNPC->getPos() - jump->m_position;

	if (getMag(distanceBetween) < 140)
	{
		m_player.jump(jump->m_direction);
	}
	if (getMag(dist) < 140)
	{
		m_testNPC->jump(jump->m_direction);
	}
}

void Play::checkPlate()
{
	sf::Vector2f distanceBetween = m_player.m_position - m_pressurePlate->m_position;
	sf::Vector2f dist = *m_testNPC->getPos() - m_pressurePlate->m_position;

	if (getMag(distanceBetween) < 150 || getMag(dist) < 150)
	{
		m_pressurePlate->setActivate(true);
		m_door->m_closed = false;
	}
	else
	{
		m_pressurePlate->setActivate(false);
		m_door->m_closed = true;
	}
}

float Play::getMag(sf::Vector2f v)
{
	float mag = sqrt((v.x * v.x)+ (v.y * v.y));
	return mag;
}

void Play::transitionToNext()
{
	if (level == 7)
	{
		*m_state = GameState::END_STATE;
	}
	else
	{
		m_player.m_position = m_positions.at(level - 1);
		m_lever->m_position = m_leverPositions.at(level - 1);
		m_lever->reset();
		m_testNPC->m_position = m_npcPositions.at(level - 1);
		m_door->m_position = m_doorPositions.at(level - 1);
		m_pressurePlate->setPos(m_pressurePlatePos.at(level - 1));
		m_jumpPad->m_position = m_jumpPadPositions.at(level - 1);
		m_jumpPad->m_direction = m_jumpPadDirections.at(level - 1);

		if (level == 2)
		{
			m_firstPlatform = 6;
			m_lastPlatform = 14;
		}
		if (level == 3)
		{
			m_firstPlatform = 13;
			m_lastPlatform = 23;
		}
		if (level == 4)
		{
			m_firstPlatform = 23;
			m_lastPlatform = 24;
		}
		if (level == 5)
		{
			m_otherjumpPad->m_position = m_jumpPadPositions.at(5);
			m_otherjumpPad->m_direction = m_jumpPadDirections.at(5);
			m_firstPlatform = 24;
			m_lastPlatform = 29;
		}
		if (level == 6)
		{
			m_jumpPad->m_position = m_jumpPadPositions.at(6);
			m_jumpPad->m_direction = m_jumpPadDirections.at(6);
			m_otherjumpPad->m_position = m_jumpPadPositions.at(0);
			m_firstPlatform = 29;
			m_lastPlatform = 38;
		}
	}
}

// Function to add emitters to the particle system
void Play::addEmitter(sf::Vector2f pos, sf::Vector2f halfSize)
{
	m_emitter.setEmissionRate(600);
	m_emitter.setParticleLifetime(sf::seconds(0.5));
	m_emitter.setParticlePosition(thor::Distributions::rect(sf::Vector2f(pos.x + halfSize.x, pos.y + halfSize.y), halfSize));
	m_emitter.setParticleVelocity(thor::Distributions::deflect(sf::Vector2f(300,300), 360.0f));
	m_emitter.setParticleRotation(thor::Distributions::uniform(0.0f, 360.0f));
	m_system.addEmitter(m_emitter, sf::seconds(0.5));
}
