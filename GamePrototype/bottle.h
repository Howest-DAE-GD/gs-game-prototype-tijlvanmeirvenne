#pragma once
#include "Texture.h"


class bottle
{
public:
	bottle(const std::string& texturePath, const std::string& flamePath, Point2f position);
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
	Texture* m_FlameTexture;
	Rectf m_MyBounds{};
	float m_Decay;
	State m_MyState{ State::Normal };
	float m_DecayRate;
};

