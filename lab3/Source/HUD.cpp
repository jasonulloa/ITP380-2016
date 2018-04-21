#include "HUD.h"
#include "Game.h"

IMPL_ACTOR(HUD, Actor);

HUD::HUD(Game& game) : Actor(game) {
	mHealthFontComponent = FontComponent::Create(*this);
	mMoneyFontComponent = FontComponent::Create(*this);
	mMessageFontComponent = FontComponent::Create(*this);
	AssetCache& texture = game.GetAssetCache();
	mFont = texture.Load<Font>("Fonts/Carlito-Regular.ttf");
	mHealthFontComponent->SetFont(mFont);
	mMoneyFontComponent->SetFont(mFont);
	mMessageFontComponent->SetFont(mFont);
}

void HUD::UpdateHPText() {
	std::string health = "Base Health: " + std::to_string(mHP);
	mHealthFontComponent->SetText(health, Color::White, 26);
}

void HUD::UpdateMoneyText() {
	std::string money = "Money: $" + std::to_string(mCash);
	mMoneyFontComponent->SetText(money, Color::Green, 26);
}

void HUD::PrintHUDMessage() {
	mMessageFontComponent->SetText(mMessage, Color::Red, 36);
}