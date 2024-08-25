#include "pch.h"
#include "Game.h"
#include "bottle.h"
#include "utils.h"
#include <iostream>
#include"Texture.h"

Game::Game( const Window& window ) 
	:BaseGame{ window }
{
	Initialize();
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	m_bottles.push_back(new bottle("pngegg.png", Point2f{0,0}));
	m_bottles.push_back(new bottle("pngegg.png", Point2f{ 1000/4,0 }));
	m_bottles.push_back(new bottle("pngegg.png", Point2f{ (1000 / 4)*2,0 }));
	m_bottles.push_back(new bottle("pngegg.png", Point2f{ (1000 / 4)*3,0 }));
	m_ClickedBottles = Point2f{ 4,4 };
	m_Score = 0.f;
	m_ok = true;
	m_Explosion = new Texture("pngwing.com.png");
	m_ScoreText = new Texture("ok", "Minercraftory.ttf",50, Color4f{ 0.f,0.f,0.f,1.f });
}

void Game::Cleanup( )
{

	for (bottle* bottle : m_bottles)
	{

		delete bottle;
	}
}

void Game::Update( float elapsedSec )
{

	std::string scoretext = "Score   " + std::to_string(m_Score);
	delete m_ScoreText;
	m_ScoreText = new Texture(scoretext, "Minercraftory.ttf", 50, Color4f{ 0.f,0.f,0.f,1.f });

	if (m_ok)
	{
		this->IsUnstable();
		for (int counter{}; counter < 4; counter++)
		{
			if (m_bottles[counter]->IsClicked())
			{
				if (m_ClickedBottles.x == 4)
				{
					m_ClickedBottles.x = counter;

				}
				else if (m_ClickedBottles.x != counter)
				{
					m_ClickedBottles.y = counter;
					this->FuseBottles();
				}

			}
		}

		for (bottle* bottle : m_bottles)
		{
			bottle->update();
		}
	}
	
}

void Game::Draw( ) const
{
	
	ClearBackground();
	if (m_ok)
	{
		for (bottle* bottle : m_bottles)
		{
			bottle->draw();
		}
	}
	else
	{
		m_Explosion->Draw();
	}
	m_ScoreText->Draw(Point2f{ 300,430 });
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	
	switch ( e.keysym.sym )
	{
	case SDLK_r:
		
		break;
	
	}
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
	
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONUP event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}

	if (m_ok)
	{
		for (bottle* bottle : m_bottles)
		{
			bottle->OnMouseUpEvent(e);
		}
	}
}

void Game::ClearBackground( ) const
{
	if (m_ok)
	{
		glClearColor(1.0f, 1.0f, 1.f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	else
	{
		glClearColor(0.0f, 0.0f, 0.f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}
}

void Game::FuseBottles()
{
	m_Score += int(pow(3 ,((m_bottles[m_ClickedBottles.x]->GetDecay() +m_bottles[m_ClickedBottles.y]->GetDecay()) / 200)));
	
	m_bottles[m_ClickedBottles.x]->ResetBottle();
	m_bottles[m_ClickedBottles.y]->ResetBottle();
	m_ClickedBottles = Point2f{ 4,4 };
}

void Game::IsUnstable()
{
	for (bottle* bottle : m_bottles)
	{
		if (bottle->IsUnstable())
		{
			m_ok = false;
		}
	}
}