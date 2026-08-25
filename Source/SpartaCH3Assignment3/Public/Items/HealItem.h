#pragma once

#include "CoreMinimal.h"

#include "Items/BaseItem.h"

#include "HealItem.generated.h"

UCLASS()
class SPARTACH3ASSIGNMENT3_API AHealItem : public ABaseItem
{
	GENERATED_BODY()

  public:
	AHealItem();

  protected:
	virtual void Activate(AActor* Activator) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	int32 HealAmount;
};
