#include "pch.h"
#include "Button.h"
#include "utils.h"
#include <iostream>

Button::Button(const std::string& texturePath, Point2f position)
{
	m_Texture = new Texture(texturePath);
	m_MyBounds = Rectf{ position.x, position.y, m_Texture->GetWidth(), m_Texture->GetHeight() };
}
Button::~Button()
{
	delete m_Texture;
}

void Button::draw()
{
	m_Texture->Draw(m_MyBounds);
}
bool Button::OnMouseUpEvent(const SDL_MouseButtonEvent& e)
{

	if (utils::IsPointInRect(Point2f{ float(e.x), float(e.y) }, m_MyBounds))
	{
		
		return true;
	}
	return false;
}