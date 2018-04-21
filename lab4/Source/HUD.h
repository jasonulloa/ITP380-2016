#pragma once
#include "Actor.h"
#include "FontComponent.h"
#include <string>

class HUD : public Actor {
	DECL_ACTOR(HUD, Actor);
public:
	HUD(Game& game);

	void UpdateScoreText();
	void UpdateTimerText();
	void PrintHUDMessage();
	void SetPoints(int points) { mPoints = points; }
	void SetTimerText(int count) { mTimer = count; }
	void SetMessage(std::string words) { mMessage = words; }
private:
	FontComponentPtr mScoreFontComponent;
	FontComponentPtr mTimerFontComponent;
	FontComponentPtr mMessageFontComponent;
	FontPtr mFont;
	int mPoints;
	int mTimer;
	std::string mMessage;
};

DECL_PTR(HUD);