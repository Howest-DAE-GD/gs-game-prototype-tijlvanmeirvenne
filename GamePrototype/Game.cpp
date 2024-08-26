#include "pch.h"
#include "Game.h"
#include "bottle.h"
#include "utils.h"
#include <iostream>
#include "Texture.h"
#include "Button.h"
#include <cmath>

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
	m_Score = 0;
	m_HighScore = 0;
	m_HighScoreChallenge = 7777;
	m_ok = gameState::title;
	m_Explosion = new Texture("pngwing.com.png");
	m_ScoreText = new Texture("ok", "Arial.ttf",50, Color4f{ 0.f,0.f,0.f,1.f });
	m_RandomNumber = rand() % 7778;
	std::string goaltext = "Target Score   " + std::to_string(m_RandomNumber);
	m_GoalText = new Texture(goaltext, "Arial.ttf", 50, Color4f{ 0.f,0.f,0.f,1.f });

	m_StartButton = new Button("StartButton.png", Point2f{ 400, 460 });
	m_ChallengeButton = new Button("ChallengeButton.png", Point2f{ 400, 390 });
	m_BackButton = new Button("back-button.png", Point2f{ 10, 730 });

	m_Timer = 31.f;
}

void Game::Cleanup( )
{
	for (bottle* bottle : m_bottles)
	{
		delete bottle;
	}
	delete m_StartButton;
	delete m_ChallengeButton;
	delete m_ScoreText;
	delete m_GoalText;
}

void Game::Update( float elapsedSec )
{

	std::string scoretext = "Score   " + std::to_string(m_Score);
	delete m_ScoreText;
	m_ScoreText = new Texture(scoretext, "Arial.ttf", 50, Color4f{ 0.f,0.f,0.f,1.f });


	if (m_ok == gameState::challenge && (m_RandomNumber<=m_Score))
	{
		m_ok = gameState::challengeEnd;
	}

	if (m_ok == gameState::normal || m_ok == gameState::challenge)
	{
		
		m_Timer -= elapsedSec;
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

		if (m_Timer < 0)
		{
			if (m_ok == gameState::normal)
			{
				m_ok = gameState::normalEnd;
				
			}
			else if (m_ok == gameState::challenge)
			{
				m_ok = gameState::challengeEnd; 
				
			}
		}
	}
	if (m_ok == gameState::normalEnd && m_HighScore < m_Score)
	{
		m_HighScore = m_Score;
	}
	if (m_ok == gameState::challengeEnd && m_HighScoreChallenge > abs(m_Score - m_RandomNumber))
	{
		m_HighScoreChallenge = abs(m_Score - m_RandomNumber);
	}
}

void Game::Draw( ) const
{
	
	ClearBackground();
	if (m_ok == gameState::normal)
	{
		std::string hightext = "High Score " + std::to_string(m_HighScore);
		Texture temphightext = Texture(hightext, "Arial.ttf", 30, Color4f{ 0.f,0.f,0.f,1.f });
		temphightext.Draw(Point2f(700, 750));
	}
	if (m_ok == gameState::challenge)
	{
		m_GoalText->Draw(Point2f{ 250, 500 });
		std::string hightext = "Closest Score " + std::to_string(m_HighScoreChallenge);
		Texture temphighchallengetext = Texture(hightext, "Arial.ttf", 30, Color4f{ 0.f,0.f,0.f,1.f });
		temphighchallengetext.Draw(Point2f(700, 750));
	}

	if (m_ok == gameState::normal || m_ok == gameState::challenge)
	{
		std::string timertext = std::to_string(int(m_Timer));
		Texture temptimer = Texture(timertext, "Arial.ttf", 70, Color4f{ 0.f,0.f,0.f,1.f });
		temptimer.Draw(Point2f{ 100.f, 700.f });

		for (bottle* bottle : m_bottles)
		{
			bottle->draw();
		}
		m_ScoreText->Draw(Point2f{ 300,430 });
	}
	else if (m_ok == gameState::normalEnd)
	{
		m_Explosion->Draw();
		m_ScoreText->Draw(Point2f{ 300,430 });
		if (m_HighScore == m_Score)
		{
			Texture newhigh = Texture("New high score!", "Arial.ttf", 40, Color4f{0.f,0.f,0.f,1.f});
			newhigh.Draw(Point2f(310, 330));
		}
		
	}
	else if (m_ok == gameState::challengeEnd)
	{
		if (m_Score != m_RandomNumber)
		{
			m_Explosion->Draw();
			int pointsOff{ abs(m_Score - m_RandomNumber) };
			std::string scoretext = "You were " + std::to_string(pointsOff) + " points off";
			Texture tempText = Texture(scoretext, "Arial.ttf", 45, Color4f{ 0.f,0.f,0.f,1.f });
			tempText.Draw(Point2f(210, 430));
		}
		else
		{
			Texture tempText = Texture("Succes!", "Arial.ttf", 50, Color4f{0.f,0.f,0.f,1.f});
			tempText.Draw(Point2f{ 390,430 });
		}
		if (m_HighScoreChallenge == abs(m_Score - m_RandomNumber))
		{
			Texture newclose = Texture("New closest score!", "Arial.ttf", 40, Color4f{ 0.f,0.f,0.f,1.f });
			newclose.Draw(Point2f(280, 330));
		}
	}
	else if (m_ok == gameState::title)
	{
		m_StartButton->draw();
		m_ChallengeButton->draw();
	}
	if (m_ok != gameState::title)
	{
		m_BackButton->draw();
	}
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	
	/*switch ( e.keysym.sym )
	{
	case SDLK_r:
		for (bottle* bottle : m_bottles)
		{
			bottle->ResetBottle();
		}
		m_Score = 0;
		m_Timer = 31;
		m_RandomNumber = rand() % 7778;
		delete m_GoalText;
		std::string goaltext = "Target Score   " + std::to_string(m_RandomNumber);
		m_GoalText = new Texture(goaltext, "Arial.ttf", 50, Color4f{ 0.f,0.f,0.f,1.f });
		m_ok = gameState::title; 
		break;
	
	}*/
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
	if (m_ok != gameState::title)
	{
		if (m_BackButton->OnMouseUpEvent(e))
		{
			for (bottle* bottle : m_bottles)
			{
				bottle->ResetBottle();
			}
			m_Score = 0;
			m_Timer = 31;
			m_RandomNumber = rand() % 7778;
			delete m_GoalText;
			std::string goaltext = "Target Score   " + std::to_string(m_RandomNumber);
			m_GoalText = new Texture(goaltext, "Arial.ttf", 50, Color4f{ 0.f,0.f,0.f,1.f });
			m_ok = gameState::title;
		}
	}
	if (m_ok == gameState::normal || m_ok == gameState::challenge)
	{
		for (bottle* bottle : m_bottles)
		{
			bottle->OnMouseUpEvent(e);
		}
		
	}
	else if (m_ok == gameState::title)
	{
		if (m_StartButton->OnMouseUpEvent(e))
		{
			m_ok = gameState::normal;
		}
		if (m_ChallengeButton->OnMouseUpEvent(e))
		{
			m_ok = gameState::challenge;
		}
	}
}

void Game::ClearBackground( ) const
{

	if (m_ok == gameState::normalEnd)
	{
		glClearColor(0.0f, 0.0f, 0.f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	else if (m_ok == gameState::challengeEnd)
	{
		if(m_RandomNumber != m_Score)
		{
			glClearColor(0.0f, 0.0f, 0.f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
		}
		else
		{
			glClearColor(1.0f, 1.0f, 1.f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
		}
	}
	else
	{
		glClearColor(1.0f, 1.0f, 1.f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}
}

void Game::FuseBottles()
{
	int tempscore{ abs(int(pow(3 ,((m_bottles[m_ClickedBottles.x]->GetDecay() + m_bottles[m_ClickedBottles.y]->GetDecay()) / 200))) - 2 )};
	if (tempscore > 7777)
	{
		tempscore = 7777;
	}
	m_Score += tempscore;
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
			if (m_ok == gameState::normal)
			{
				m_ok = gameState::normalEnd;
			}
			else if (m_ok == gameState::challenge)
			{
				m_ok = gameState::challengeEnd;
			}
		}
	}
}
