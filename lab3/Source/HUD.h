#pragma once
#include "Actor.h"
#include "FontComponent.h"
#include <string>

class HUD : public Actor {
	DECL_ACTOR(HUD, Actor);
public:
	HUD(Game& game);

	void UpdateHPText();
	void UpdateMoneyText();
	void PrintHUDMessage();
	void SetHP(int HP) { mHP = HP; }
	void SetMoney(int cash) { mCash = cash; }
	void SetMessage(std::string words) { mMessage = words; }
private:
	FontComponentPtr mHealthFontComponent;
	FontComponentPtr mMoneyFontComponent;
	FontComponentPtr mMessageFontComponent;
	FontPtr mFont;
	int mHP;
	int mCash;
	std::string mMessage;
};

DECL_PTR(HUD);