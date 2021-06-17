#include "Menu.h"

Menu::Menu(GameState *gameState, sf::Vector2u window_size)
{
	m_backgroundTex = ResourceManager::instance().m_holder["MenuBG"];
	m_backgroundSprite.setTexture(m_backgroundTex);
	m_backgroundSprite.setOrigin(m_backgroundTex.getSize().x / 2, m_backgroundTex.getSize().y / 2);
	m_backgroundSprite.setPosition(window_size.x / 2, window_size.y / 2);
	m_currentButton = 0;
	createUI(window_size);
	m_state = gameState;
	m_buttonState = new ButtonState(ButtonState::NEW_GAME);

	// Loads in the background shader
	if (!m_platShader.loadFromFile("platShader.txt", sf::Shader::Fragment))
		std::cout << "Shader not loaded";

	// Sets up the shader
	m_platShader.setUniform("resolution", sf::Vector2f(1920, 1080));
	m_platShader.setUniform("time", 0.0f);
}

Menu::~Menu()
{

}

void Menu::update(Controller * controller, sf::Time dt)
{
	m_controller = controller;
	m_time += (dt.asMicroseconds() / 300);
	m_platShader.setUniform("time", m_time);	// Sets the time of the shader
	if (m_controller->m_currentState.dpadDown && !m_controller->m_previousState.dpadDown)
	{
		m_buttons[m_currentButton]->defocus();
		m_currentButton++;
		if (m_currentButton >= m_buttons.size())
		{
			m_currentButton = 0;
		}
		*m_buttonState = ButtonState(m_currentButton);
		m_buttons[m_currentButton]->focus(); 
	}

	if (m_controller->m_currentState.dpadUp && !m_controller->m_previousState.dpadUp)
	{
		m_buttons[m_currentButton]->defocus();
		m_currentButton--; 
		if (m_currentButton < 0)
		{
			m_currentButton = m_buttons.size() -1;
		}
		*m_buttonState = ButtonState(m_currentButton);
		m_buttons[m_currentButton]->focus();
	}

	if (m_controller->m_currentState.A && !m_controller->m_previousState.A)
	{
		if (*m_buttonState == ButtonState::NEW_GAME)
		{
			*m_state = GameState::PLAY_STATE;
		}

		if (*m_buttonState == ButtonState::OPTIONS_STATE)
		{
			*m_state = GameState::OPTIONS_STATE;
		}

		if (*m_buttonState == ButtonState::END_STATE)
		{
			exit(1);
		}
	}
}

void Menu::render(sf::RenderWindow & window)
{
	window.clear(sf::Color::Black);
	window.draw(m_backgroundSprite, &m_platShader);
	for (Widget* widget : m_guiElements)
	{
		widget->render(window);
	}
}

void Menu::createUI(sf::Vector2u window_size)
{
	m_guiElements.push_back(new Box(window_size));

	m_buttons.push_back(new Button(sf::Vector2f(1920, 400), "New Game"));
	m_buttons.push_back(new Button(sf::Vector2f(1920, 484), "Load Game"));
	m_buttons.push_back(new Button(sf::Vector2f(1920, 568), "Settings"));
	m_buttons.push_back(new Button(sf::Vector2f(1920, 652), "Exit"));
	m_buttons[m_currentButton]->focus();

	for (Button* button : m_buttons)
	{
		m_guiElements.push_back(button);
	}
}