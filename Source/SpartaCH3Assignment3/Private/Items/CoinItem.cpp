#include "Items/CoinItem.h"

#include "Core/SpartaGameState.h"

ACoinItem::ACoinItem()
{
	ScoreValue = 0;
	Type = "Coin";
}

void ACoinItem::Activate(AActor* Activator)
{
	if (IsValid(Activator) && Activator->ActorHasTag("Player"))
	{
		if (UWorld* World = GetWorld())
		{
			if (ASpartaGameState* GameState = World->GetGameState<ASpartaGameState>())
			{
				GameState->NotifyCoinCollected(ScoreValue);
			}
		}

		Destroy();
	}
}
