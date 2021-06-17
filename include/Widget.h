#ifndef WIDGET_H
#define WIDGET_H

/*
 * John O'Grady, Peter Daly
 * Widget class to handle all the UI elements 
 * 18/10/17
 */

#include "Controller.h"
#include "ResourceManager.h"



class Widget
{
public:
	Widget();	// Constructor for the widget object.
	~Widget();	// Deconstructor for the widget object.

	/// <summary>
	/// Update method that will be passed to all classes that inherit the widget class,
	/// This must be overwritten as it is pure virtual.
	/// </summary>
	virtual void update() = 0;

	/// <summary>
	/// Render method that will be passed to all classes that inherit the widget class,
	/// This must be overwritten as it is pure virtual.
	/// Takes the address of the game window as a argument.
	/// </summary>
	/// <param name="window"></param>
	virtual void render(sf::RenderWindow& window) = 0;

	// Function to select a widget
	virtual void select();

	// FUnction to de-select a widget
	virtual void deSelect();

private:
	bool selected;
};
#endif // !WIDGET_H

#ifndef BOX_H
#define BOX_H

class Box : public Widget
{
public:
	Box(sf::Vector2u pos);
	~Box();

	virtual void update() override;
	virtual void render(sf::RenderWindow& window) override;

private:
	sf::Texture m_image;
	sf::Sprite m_sprite;
};
#endif // !BOX_H

#ifndef BUTTON_H
#define BUTTON_H

class Button : public Widget
{
public:
	Button(sf::Vector2f pos, std::string text);
	~Button();

	virtual void update() override;
	virtual void render(sf::RenderWindow& window) override;

	void focus();
	void defocus();
private:
	sf::Texture m_image, m_textImage;
	sf::Sprite m_sprite, m_textSprite;
	sf::Color color;
	sf::Text m_text;
	sf::Font m_font;
};


#endif // !BUTTON_H

#ifndef RADIOBUTTON_H
#define RADIOBUTTON_H

class RadioButton : public Widget
{
public:
	RadioButton();	// Default constructor for the RadioButton object.
					/// <summary>
					/// Overloaded constructor for the RadioButton object.
					/// Takes a texture used to represent the RadioButton and a vector of two floats that is used to represent its on-screen position.
					/// </summary>
					/// <param name="texture"></param>
					/// <param name="position"></param>
	RadioButton(sf::Texture *texture, sf::Vector2f *position);
	~RadioButton();	// Deconstructor for the RadioButton object.

	virtual void update() override;	// "update" method for the RadioButton object, Overrides the "update" method in the widget.
									/// <summary>
									/// "render" method for the RadioButton object, Overrides the "render" method in the widget.
									/// Takes the address of the game window as a argument.
									/// </summary>
									/// <param name="window"></param>
	virtual void render(sf::RenderWindow& window) override;

	virtual void getFocus();	// Gives the RadioButton focus. Doesn't need to override the method in the widget class as they are the same.
	virtual void loseFocus();	// Takes focus from the RadioButton. Doesn't need to override the method in the widget class as they are the same.

	void moveRight();	// Moves the RadioButton to the right, This is used in screen transitions.
	void moveLeft();	// Moves the RadioButton to the left, This is used in screen transitions.

	sf::Vector2f m_position;	// Stores the postion of the RadioButton.
	sf::Sprite m_sprite;	// Uses the texture and positon to represent the RadioButton on the screen to the player.

	bool m_filled = false; // If the radio button is filled or not

private:
	sf::Texture m_texture;	// Stores the texture of the RadioButton.
	bool m_hasFocus;	// Used to determine whether or not the RadioButton hasFocus.
	sf::FloatRect m_spriteRectangle;	// Rectangle used to find the centre of the texture so that the sprite can be placed easier on screen.
};
#endif // !RADIOBUTTON_H

#ifndef SLIDER_H
#define SLIDER_H

class Slider : public Widget
{
public:
	Slider();	// Default constructor for the Slider object.
				/// <summary>
				/// Overloaded constructor for the Slider object.
				/// Takes a vector of two floats to represent the objects position 
				/// and an integer used to determine how many segments the slider is made up of as its arguments.
				/// </summary>
				/// <param name="position"></param>
				/// <param name="numOfSegments"></param>
	Slider(sf::Vector2f *position, int numOfSegments);
	~Slider();	// Deconstructor for the Slider object.

	virtual void update() override;	// "update" method for the Slider object, Overrides the "update" method in the widget.
									/// <summary>
									/// "render" method for the Slider object, Overrides the "render" method in the widget.
									/// Takes the address of the game window as a argument.
									/// </summary>
									/// <param name="window"></param>
	virtual void render(sf::RenderWindow& window) override;

	virtual void select() override;	// Method that sets hasFocus to "True" as well as changing the colour of the Slider to show that it hasFocus.
	virtual void deSelect() override;	// Method that sets hasFocus to "False" as well as changing the colour of the Slider to show it no longer hasFocus.

	void moveRight();	// Moves the Slider object to the right, This is called for transitioning between screens.
	void moveLeft();	// Moves the Slider object to the left, This is called for transitioning between screens.

	int incrementSlider();	// Increments the Slider by one segment.
	int decrementSlider();	// Decrements the Slider by one segment.
	void setCurrentSegment(int segmentValue);

	sf::Vector2f m_position;	// Stores the positon of the Slider object.

	sf::RectangleShape m_slider;	// Used to represent the Slider on-screen.

private:
	bool m_hasFocus;	// Determines whether or not the Slider hasFocus.

	int m_numOfSegments;	// Stores the number of different segments the Slider is broken up into.
	int m_currentSegment;	// Stores the number of the segment the Slider is currently on.

	float m_circleSize;	// Stores the value of the size of m_circle.
	sf::Vector2f m_rectangleSize;	// Stores the value of the size of m_slider and m_sliderBackground.

	sf::CircleShape m_circle;	// Placed at the end of the Slider rectangle to give the player a easy point to follow.
	sf::RectangleShape m_sliderBackground;	// What the rest of the Slider sits upon to seperate it from the background image.
};
#endif // !SLIDER_H