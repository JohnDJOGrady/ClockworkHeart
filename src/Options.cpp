#include "Options.h"

Options::Options(GameState *gameState, sf::Sound &music) 

{
	m_backgroundTex = ResourceManager::instance().m_holder["MenuBG"];
	m_backgroundSprite.setTexture(m_backgroundTex);
	m_backgroundSprite.setOrigin(m_backgroundTex.getSize().x / 2, m_backgroundTex.getSize().y / 2);
	m_backgroundSprite.setPosition(1920 / 2, 1080 / 2);

	//m_radioTex = ResourceManager::instance().m_holder["Radio"];	// initialises the radio texture to be Radio from the yaml file

	m_gameState = gameState;	// initialising the gamestate object

	m_volDif = 25;	// initialised the slider difference variable
	m_volume = music.getVolume();	// initialises volume to get the current musics volume (defaulted to 100)

	m_exitString = "Exit";

	createUI(sf::Vector2u(1920, 1080));

	m_buttonSelected = new optionsSelection(optionsSelection::Option1);
}

Options::~Options()
{
}

void Options::update(GamePadState m_state, Controller & m_controller, sf::Sound &music)
{
	if (m_state.dpadDown && !m_controller.m_previousState.dpadDown)
	{
		m_buttons[m_currentBtn]->defocus();
		m_currentBtn++;
		if (m_currentBtn >= m_buttons.size())
		{
			m_currentBtn = 0;
		}
		*m_buttonSelected = optionsSelection(m_currentBtn);
		m_buttons[m_currentBtn]->focus();
	}

	if (m_state.dpadUp && !m_controller.m_previousState.dpadUp)
	{
		m_buttons[m_currentBtn]->defocus();
		m_currentBtn--;
		if (m_currentBtn < 0)
		{
			m_currentBtn = m_buttons.size() - 1;
		}
		*m_buttonSelected = optionsSelection(m_currentBtn);
		m_buttons[m_currentBtn]->focus();
	}

	if (m_state.A && !m_controller.m_previousState.A)
	{
		if (*m_buttonSelected == optionsSelection::Option4)
		{
			*m_gameState = GameState::MENU_STATE;
		}
	}
}

void Options::render(sf::RenderWindow & window)
{
	window.clear(sf::Color(0, 0, 0));	// sets the window to our preferred colour, royal blue
	window.draw(m_backgroundSprite);
	// rendering each widget object
	for (Widget* widget : m_guiElements)
	{
		widget->render(window);
	}

}

void Options::createUI(sf::Vector2u window_size)
{
	m_guiElements.push_back(new Box(window_size));

	m_buttons.push_back(new Button(sf::Vector2f(1920, 400), "Option1"));
	m_buttons.push_back(new Button(sf::Vector2f(1920, 484), "Option2"));
	m_buttons.push_back(new Button(sf::Vector2f(1920, 568), "Option3"));
	m_buttons.push_back(new Button(sf::Vector2f(1920, 652), "Exit"));
	m_buttons[m_currentBtn]->focus();

	for (Button* button : m_buttons)
	{
		m_guiElements.push_back(button);
	}
}
