#include "Game.h"

// Updates per milliseconds
static sf::Int32 MS_PER_UPDATE = 10.0;;

Game::Game() :	
	m_window(sf::VideoMode(1920, 1080, 32), "A Clockwork Heart")	
{
	sf::Vector2u window_size = m_window.getSize();

	int currentLevel = 1;
	if (!LevelLoader::load(currentLevel, m_level))
	{
		std::cout << "Level not loaded" << std::endl;
	}
	
	ResourceManager::instance().loadData(m_level);

	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile("smack.wav"))
	{
		std::cout << "Failed to load sound file" << std::endl;
	}

	
	m_sound.setBuffer(buffer);
	m_sound.play();
	m_sound.setLoop(true);

	// Initialising the game state object
	m_currentGameState = new GameState(GameState::PLAY_STATE);
	m_splashScreen = new Splash(m_currentGameState);
	m_menuScreen = new Menu(m_currentGameState, window_size);
	m_playScreen = new Play(m_currentGameState, currentLevel, &m_level);
	m_optionsScreen = new Options(m_currentGameState, m_sound);
	m_endScreen = new EndScreen(m_currentGameState, window_size);
}

Game::~Game()
{
}

void Game::run()
{
	m_window.setFramerateLimit(1000);
	sf::Clock clock;
	sf::Int32 lag = 0;
	sf::Event event;

	while (m_window.isOpen())
	{

		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				m_window.close();
			}
		}

		sf::Time dt = clock.restart();

		lag += dt.asMilliseconds();

		while (lag > MS_PER_UPDATE)
		{
			update(dt);
			lag -= MS_PER_UPDATE;
		}
		update(dt);
		render(m_window);
	}
}

void Game::update(sf::Time deltaTime)
{		
	m_controller.update();	// updates the controller object

	// A switch statement for changing the current gamestate and hence, game screen
	switch (*m_currentGameState)
	{
	case GameState::SPLASH_STATE:
		m_splashScreen->update(&m_controller, deltaTime);	// updating splash screen
		break;
	case GameState::MENU_STATE:
		m_menuScreen->update(&m_controller, deltaTime);
		break;
	case GameState::PLAY_STATE:
		m_playScreen->update(&m_controller, deltaTime);
		break;
	case GameState::UPGRADE_STATE:
		
		break;
	case GameState::OPTIONS_STATE:
		m_optionsScreen->update(m_controller.m_currentState, m_controller, m_sound);
		break;
	case GameState::CREDITS_STATE:
		
		break;
	case GameState::END_STATE:
		m_endScreen->update(&m_controller, deltaTime);
		break;
	default:
		break;
	}
}

void Game::render(sf::RenderWindow &window)
{
	window.clear(sf::Color(30, 50, 90));	// clears the window to our preferred colour, a royal blue

	// switch statement for rendering each screen object
	switch (*m_currentGameState)
	{
	case GameState::SPLASH_STATE:
		m_splashScreen->render(window);
		break;
	case GameState::MENU_STATE:
		m_menuScreen->render(window);
		break;
	case GameState::PLAY_STATE:
		m_playScreen->render(window);
		break;
	case GameState::UPGRADE_STATE:
		
		break;
	case GameState::OPTIONS_STATE:
		m_optionsScreen->render(window);
		break;
	case GameState::CREDITS_STATE:
		
		break;
	case GameState::END_STATE:
		m_endScreen->render(window);
		break;
	default:
		break;
	}
	window.display();
}