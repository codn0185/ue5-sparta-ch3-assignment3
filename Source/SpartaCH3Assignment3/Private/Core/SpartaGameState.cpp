#include "Core/SpartaGameState.h"

ASpartaGameState::ASpartaGameState()
{
	PrimaryActorTick.bCanEverTick = false;

	// Game Data
	Score = 0;
	SpawnedCoinCount = 0;
	CollectedCointCount = 0;
}

void ASpartaGameState::BeginPlay()
{
	Super::BeginPlay();
}

void ASpartaGameState::StartLevel()
{
}

void ASpartaGameState::EndLevel()
{
}

void ASpartaGameState::OnCoinCollected()
{
}

void ASpartaGameState::OnTimeExpired()
{
}

void ASpartaGameState::OnPlayerDead()
{
}

void ASpartaGameState::HandleGameOver()
{
}

void ASpartaGameState::HandleGameCleared()
{
}

void ASpartaGameState::AddScore(int32 amount)
{
}
