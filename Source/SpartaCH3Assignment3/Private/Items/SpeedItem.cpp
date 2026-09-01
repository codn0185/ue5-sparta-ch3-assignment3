#include "Items/SpeedItem.h"

#include "Characters/SpartaCharacter.h"

ASpeedItem::ASpeedItem()
{
	Multiplier = 1.f;
	Duration = 5.f;
	Type = "Speed";
}

void ASpeedItem::Activate(AActor* Activator)
{
	Super::Activate(Activator);

	if (IsValid(Activator) && Activator->ActorHasTag("Player"))
	{
		if (ASpartaCharacter* Player = Cast<ASpartaCharacter>(Activator))
		{
			Player->ApplySpeedEffect(Multiplier, Duration);
			Destroy();
		}
	}
}
