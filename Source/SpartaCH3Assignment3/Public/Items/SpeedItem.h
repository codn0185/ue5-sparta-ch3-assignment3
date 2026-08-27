#pragma once

#include "CoreMinimal.h"

#include "Items/BaseItem.h"

#include "SpeedItem.generated.h"

UCLASS()
class SPARTACH3ASSIGNMENT3_API ASpeedItem : public ABaseItem
{
	GENERATED_BODY()

  public:
	ASpeedItem();

  protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties", meta = (ClampMin = "0.1", UIMin = "0.1"))
	float Multiplier;  // 속도 배율
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties", meta = (ClampMin = "0.1", UIMin = "0.1"))
	float Duration;  // 적용 시간

	// "IInteractableInterface" Methods
	virtual void Activate(AActor* Activator) override;
};
