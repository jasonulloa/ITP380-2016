#include "HUD.h"
#include "Game.h"

IMPL_ACTOR(HUD, Actor);

HUD::HUD(Game& game) : Actor(game) {
	mScoreFontComponent = FontComponent::Create(*this);
	mTimerFontComponent = FontComponent::Create(*this);
	mMessageFontComponent = FontComponent::Create(*this);
	AssetCache& texture = game.GetAssetCache();
	mFont = texture.Load<Font>("Fonts/Carlito-Regular.ttf");
	mScoreFontComponent->SetFont(mFont);
	mTimerFontComponent->SetFont(mFont);
	mMessageFontComponent->SetFont(mFont);
}

void HUD::UpdateScoreText() {
	std::string points = "Score: " + std::to_string(mPoints);
	mScoreFontComponent->SetText(points, Color::White, 26);
}

void HUD::UpdateTimerText() {
	std::string count = "Time: " + std::to_string(mTimer);
	mTimerFontComponent->SetText(count, Color::Green, 26);
}

void HUD::PrintHUDMessage() {
	mMessageFontComponent->SetText(mMessage, Color::Red, 36);
}