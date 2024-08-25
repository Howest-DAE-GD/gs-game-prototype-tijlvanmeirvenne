
#include "pch.h"
#include "bottle.h"
#include "utils.h"
#include "Texture.h"
#include <iostream>

bottle::bottle(const std::string& texturePath, Point2f position)
{
	m_Texture = new Texture(texturePath);
	m_MyBounds = Rectf{ position.x, position.y, m_Texture->GetWidth(), m_Texture->GetHeight()};
	m_Decay = 0;
}
bottle::~bottle()
{
	delete m_Texture;
}

void bottle::update()
{
	if (m_Decay >= 1000)
	{
		
	}





	m_Decay++;
}

void bottle::draw()
{
	if (m_MyState == State::Clicked)
	{
		utils::SetColor(Color4f{ 0.f,0.f,1.f,1.f });
		utils::DrawRect(m_MyBounds);

	}
	
	std::vector<Point2f> polygon({
		Point2f{m_MyBounds.left + 12, m_MyBounds.bottom + 4},
		Point2f{m_MyBounds.left + 4, m_MyBounds.bottom + 15},
		Point2f{m_MyBounds.left + 50, m_MyBounds.bottom + 100},
		Point2f{m_MyBounds.left + 158, m_MyBounds.bottom + 100},
		Point2f{m_MyBounds.left + 204, m_MyBounds.bottom + 15},
		Point2f{m_MyBounds.left + 193, m_MyBounds.bottom + 4}
		});
	utils::SetColor(Color4f{(float(m_Decay)/1000), 1.f - float(m_Decay) / 1000, 0.f, 1.f});
	utils::FillPolygon(polygon);
	m_Texture->Draw(m_MyBounds);
}



void bottle::OnMouseUpEvent(const SDL_MouseButtonEvent& e)
{
	if (utils::IsPointInRect(Point2f{ float(e.x), float(e.y) }, m_MyBounds))
	{
		m_MyState = State::Clicked;
	}
}

bool bottle::IsClicked()
{
	return (m_MyState==State::Clicked);
}

void bottle::ResetBottle()
{
	m_Decay = 0;
	m_MyState = State::Normal;
}

bool bottle::IsUnstable()
{
	return (m_Decay >= 1000);
}

int bottle::GetDecay()
{
	return m_Decay;
}