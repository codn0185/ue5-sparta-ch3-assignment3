#pragma once

#include "CoreMinimal.h"

#include "Items/BaseItem.h"

#include "CoinItem.generated.h"

UCLASS()
class SPARTACH3ASSIGNMENT3_API ACoinItem : public ABaseItem
{
	GENERATED_BODY()

  public:
	ACoinItem();

  protected:
	// Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	int32 ScoreValue;

	// "IInteractableInterface" Methods
	virtual void Activate(AActor* Activator) override;
};
