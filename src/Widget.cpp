#include "Widget.h"

Widget::Widget()
{
	
}

Widget::~Widget() {}

void Widget::select()
{
	selected = true;
}

void Widget::deSelect()
{
	selected = false;
}

#pragma region Box
Box::Box(sf::Vector2u pos)
{

	m_image = ResourceManager::instance().m_holder["BoxTexture"];
	m_sprite.setTexture(m_image);
	m_sprite.setOrigin(m_image.getSize().x / 2, m_image.getSize().y / 2);
	m_sprite.setPosition(pos.x / 2, pos.y / 2);

}

Box::~Box()
{
	delete this;
}

void Box::update()
{

}

void Box::render(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}
#pragma endregion Box

#pragma region Button
Button::Button(sf::Vector2f pos, std::string text)
{
	if (!m_font.loadFromFile("./resources/font/clockwork.ttf"))
	{
		std::cout << "couldnt load font";
	}

	m_image = ResourceManager::instance().m_holder["ButtonBG"];
	m_sprite.setTexture(m_image);
	m_sprite.setOrigin(m_image.getSize().x / 2, m_image.getSize().y / 2);
	m_sprite.setPosition(pos.x / 2, pos.y);
	color = m_sprite.getColor();
	defocus();

	/*
	m_textImage = ResourceManager::instance().m_holder[text];
	m_textSprite.setTexture(m_textImage);
	m_textSprite.setOrigin(m_textImage.getSize().x / 2, m_textImage.getSize().y / 2);
	m_textSprite.setPosition(pos.x / 2, pos.y);
	*/

	m_text.setFont(m_font);
	m_text.setString(text);
	m_text.setStyle(sf::Text::Bold);
	m_text.setOrigin(m_text.getLocalBounds().width / 2, m_text.getLocalBounds().height);
	m_text.setPosition(m_sprite.getPosition());
	
}

Button::~Button()
{
	delete this;
}

void Button::update()
{
}

void Button::focus()
{
	select();
	m_sprite.setColor(sf::Color(color.r, color.g, color.b, 125));
}

void Button::defocus()
{
	deSelect();
	m_sprite.setColor(sf::Color(color.r, color.g, color.b, 0));
}

void Button::render(sf::RenderWindow & window)
{
	window.draw(m_sprite);
	//window.draw(m_textSprite);
	window.draw(m_text);
}
#pragma endregion Button

#pragma region RadioButtonRegion

RadioButton::RadioButton()
{
}

RadioButton::RadioButton(sf::Texture * texture, sf::Vector2f * position) :
	m_position(*position),	// Sets m_position to the de-referenced value of the position argument.
	m_texture(*texture)	// Sets m_texture to the de-referenced value of the texture argument.
{

	m_sprite.setTexture(*texture);	// Sets the texture of the sprite to be that of the de-referenced texture.

	m_spriteRectangle = m_sprite.getLocalBounds();	// Gets the dimensions of the rectangle that contains the text.
	m_sprite.setOrigin(m_spriteRectangle.left + m_spriteRectangle.width / 2.0f, m_spriteRectangle.top + m_spriteRectangle.height / 2.0f);	// Centres the origin of the text.
	m_sprite.setPosition(m_position);	// Sets the position of the sprite to m_position with its centre as its origin.
}

RadioButton::~RadioButton()
{
}

void RadioButton::update()
{
}

void RadioButton::render(sf::RenderWindow & window)
{
	window.draw(m_sprite);	// Draws the sprite to the screen.
}

void RadioButton::getFocus()
{
	m_hasFocus = true;	// Gives focus to the RadioButton.
}

void RadioButton::loseFocus()
{
	m_hasFocus = false;	// Takes focus from the RadioButton.
}

void RadioButton::moveRight()
{
	m_sprite.setPosition(m_sprite.getPosition().x + 1, m_sprite.getPosition().y);	// Moves the sprite by positive one along the x-axis, while leaving the y-axis the same.
}

void RadioButton::moveLeft()
{
	m_sprite.setPosition(m_sprite.getPosition().x - 1, m_sprite.getPosition().y);	// Moves the sprite by negative one along the x-axis, while leaving the y-axis the same.
}

#pragma endregion

#pragma region SliderRegion


Slider::Slider()
{

}

Slider::Slider(sf::Vector2f * position, int numOfSegments) :
	m_position(*position),	// Sets m_position to the de-referenced value of position.
	m_numOfSegments(numOfSegments - 1)	// One is taken from numOfSegments to allow for using zero based numbering.
{
	m_rectangleSize = sf::Vector2f(350.f, 15.0f);	// Values used in both rectangle slider components.

	m_sliderBackground.setPosition(m_position);	// Sets the pos]ition of the slider background using the top left corner as the origin.
	m_slider.setPosition(m_position);	// Sets the position of the slider using the top left corner as the origin.

	m_sliderBackground.setFillColor(sf::Color::Green);	// Sets the colour of the slider background to blue.
	m_slider.setFillColor(sf::Color::Yellow);	// Sets the colour of the slider to black.

	m_sliderBackground.setSize(m_rectangleSize);	// Sets the size of the slider background to the values in m_rectangleSize.
	m_slider.setSize(m_rectangleSize);	// Sets the size of the slider background to the values in m_rectangleSize.

	m_currentSegment = 0;	// sets m_currentSegment to the maximum possible value.
	m_slider.setSize(sf::Vector2f((m_sliderBackground.getSize().x / m_numOfSegments) * m_currentSegment, m_slider.getSize().y));
}

Slider::~Slider()
{
}

void Slider::update()
{
}

void Slider::render(sf::RenderWindow & window)
{
	window.draw(m_sliderBackground);	// Draws the slider background on the screen.
	window.draw(m_slider);	// Draws the slider on top of the slider background.
}

void Slider::select()
{
	m_slider.setFillColor(sf::Color::Yellow);	// Sets the colour of the slider to sea blue.
	m_sliderBackground.setFillColor(sf::Color::Green);
	m_hasFocus = true;	// Gives the slider focus.
}

void Slider::deSelect()
{
	m_slider.setFillColor(sf::Color(0, 0, 0));	// Sets the colour of the slider to black.
	m_sliderBackground.setFillColor(sf::Color::Green);
	m_hasFocus = false;	// takes focus from the slider
}

void Slider::moveRight()
{
	m_sliderBackground.setPosition(m_slider.getPosition().x + 1, m_slider.getPosition().y);	// Moves the slider background by positive one along the x-axis, the y-axis remains unchanged.
	m_slider.setPosition(m_slider.getPosition().x + 1, m_slider.getPosition().y);	// Moves the slider by positive one along the x-axis, the y-axis remains unchanged.
}

void Slider::moveLeft()
{
	m_sliderBackground.setPosition(m_sliderBackground.getPosition().x - 1, m_sliderBackground.getPosition().y);// Moves the slider background by positive one along the x-axis, the y-axis remains unchanged.
	m_slider.setPosition(m_slider.getPosition().x - 1, m_slider.getPosition().y);	// Moves the slider by positive one along the x - axis, the y - axis remains unchanged.
}

int Slider::incrementSlider()
{
	if (m_currentSegment < m_numOfSegments)	// Checks that m_currentSegment is less the value stored in m_numOfSegments.
	{
		m_currentSegment++;	// Increments the value in m_currentSegment.
		m_slider.setSize(sf::Vector2f((m_sliderBackground.getSize().x / m_numOfSegments) * m_currentSegment, m_slider.getSize().y));	// Sets the length of the slider to be that of the total maximum length divided by the total number of segments multiplied by the number of the current segment.
	}

	return m_currentSegment;	// Returns the current segment.
}

int Slider::decrementSlider()
{
	if (m_currentSegment > 0)	// Checks that m_currentSegment is greater that 0.
	{
		m_currentSegment--;	// Decrements the value in m_currentSegment.
		m_slider.setSize(sf::Vector2f((m_sliderBackground.getSize().x / m_numOfSegments) * m_currentSegment, m_slider.getSize().y));	// Sets the length of the slider to be that of the total maximum length divided by the total number of segments multiplied by the number of the current segment.
	}

	return m_currentSegment;	// Returns the current segment.
}

void Slider::setCurrentSegment(int segmentValue)
{
	m_currentSegment = segmentValue;
	m_slider.setSize(sf::Vector2f((m_sliderBackground.getSize().x / m_numOfSegments) * m_currentSegment, m_slider.getSize().y));
}

#pragma endregion
