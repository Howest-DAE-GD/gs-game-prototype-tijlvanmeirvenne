#pragma once
#include "Texture.h"


class Button
{
public:
	Button(const std::string& texturePath, Point2f position);
	~Button();

	void draw();
    bool OnMouseUpEvent(const SDL_MouseButtonEvent& e);

private:
	Rectf m_MyBounds;
	Texture* m_Texture;

};

