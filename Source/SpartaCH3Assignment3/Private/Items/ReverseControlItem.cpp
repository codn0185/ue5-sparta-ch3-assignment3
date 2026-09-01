#include "Items/ReverseControlItem.h"

#include "Characters/SpartaCharacter.h"

AReverseControlItem::AReverseControlItem()
{
	Duration = 3.f;
	Type = "ReverseControl";
}

void AReverseControlItem::Activate(AActor* Activator)
{
	Super::Activate(Activator);

	if (IsValid(Activator) && Activator->ActorHasTag("Player"))
	{
		if (ASpartaCharacter* Player = Cast<ASpartaCharacter>(Activator))
		{
			Player->ApplyReverseControl(Duration);
			Destroy();
		}
	}
}
