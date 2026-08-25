#include "Items/HealItem.h"

#include "Characters/SpartaCharacter.h"

AHealItem::AHealItem()
{
	HealAmount = 20;
	Type = "Heal";
}

void AHealItem::Activate(AActor* Activator)
{
	if (IsValid(Activator) && Activator->ActorHasTag("Player"))
	{
		if (ASpartaCharacter* Player = Cast<ASpartaCharacter>(Activator))
		{
			Player->AddHealth(HealAmount);
			Destroy();
		}
	}
}
