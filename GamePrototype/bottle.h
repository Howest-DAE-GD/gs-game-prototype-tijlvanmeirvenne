#pragma once
#include "Texture.h"


class bottle
{
public:
	bottle(const std::string& texturePath, Point2f position);
	~bottle();

	void update();
	void draw();
	
	void OnMouseUpEvent(const SDL_MouseButtonEvent& e);
	bool IsClicked();
	void ResetBottle();
	bool IsUnstable();

	int GetDecay();

	enum class State
	{
		Normal, Clicked
	};


private:
	Texture* m_Texture;
	Rectf m_MyBounds{};
	int m_Decay;
	State m_MyState{ State::Normal };
};

