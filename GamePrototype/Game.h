#pragma once
#include "BaseGame.h"
#include "vector"

class Button;
class Texture;
class bottle;
class Game : public BaseGame
{
public:
	explicit Game( const Window& window );
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game( Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rh-override
	~Game();

	void Update( float elapsedSec ) override;
	void Draw( ) const override;

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e ) override;
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e ) override;
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e ) override;

	enum class gameState
	{
		title, normal, challenge, normalEnd, challengeEnd
	};

private:

	// FUNCTIONS
	void Initialize();
	void Cleanup( );
	void ClearBackground( ) const;
	void FuseBottles();
	void IsUnstable();

	Point2f m_ClickedBottles;
	std::vector<bottle*> m_bottles;
	int m_Score;
	gameState m_ok;
	Texture* m_Explosion;
	Texture* m_ScoreText;
	Texture* m_GoalText;

	Button* m_StartButton;
	Button* m_ChallengeButton;
	Button* m_BackButton;

	int m_HighScore;
	int m_HighScoreChallenge;
	int m_RandomNumber;
	float m_Timer;
};