#ifndef OPTIONS_H
#define OPTIONS_H

#include <SFML\Graphics.hpp>
#include "GameState.h"
#include "Widget.h"
#include "ResourceManager.h"
#include "SFML\Audio.hpp"
#include "SFML\Audio\SoundSource.hpp"

enum class optionsSelection	// Enum for the buttons
{
	Option1,
	Option2,
	Option3,
	Option4
};

class Options
{
public:

	Options(GameState *gameState, sf::Sound &music);	// Constructor for the options object
	~Options();	// Deconstructor for the options object

				/// <summary>
				/// Update method that updates the options object based on
				/// Current GameState, the controller object, and the music
				/// </summary>
	void update(GamePadState m_state, Controller & m_controller, sf::Sound &music);

	/// <summary>
	/// Render method that renders the options object
	/// Dependent on the current Render Window
	/// </summary>
	void render(sf::RenderWindow & window);

	void createUI(sf::Vector2u window_size);

private:
	GameState *m_gameState;		// A pointer to the current gamestate


	optionsSelection *m_buttonSelected; // The button enum which starts on the first option

																   // Strings for the buttons
	std::string m_exitString;
	std::string m_volString = "Volume:";
	std::string m_muteString = "Mute:";

	sf::Font m_font;	// Stores the font

	sf::Sound vol;	// Stores the volume

	float m_volume;	// A float variable for the volume as a usable value
	int m_volDif;	// The decrementation/incrementation value of the slider

	Widget *widgets[5];	// Array of widgets

	sf::Texture m_radioTex;	// Stores a texture

							// Button and slider variables
	int m_sliderValue;
	int m_currentBtn = 0;
	const int BUTTON_COUNT = 3;

	// Background variables
	sf::Texture m_backgroundTex;
	sf::Sprite m_backgroundSprite;

	std::vector<Widget*> m_guiElements;
	std::vector<Button*> m_buttons;
};
#endif // !OPTIONS_H


