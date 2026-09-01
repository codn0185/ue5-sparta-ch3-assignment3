#pragma once

#include "CoreMinimal.h"

#include "Items/BaseItem.h"

#include "MineItem.generated.h"

class USphereComponent;

UCLASS()
class SPARTACH3ASSIGNMENT3_API AMineItem : public ABaseItem
{
	GENERATED_BODY()

  public:
	AMineItem();

  protected:
	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* ExplosionCollsion;

	// VFX & SFX
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FX")
	UParticleSystem* ExplosionParticle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FX")
	USoundBase* ExplosionSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FX")
	float ExplosionParticleDuration;

	// Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	float ExplosionDelay;  // 폭발 딜레이
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	int32 ExplosionDamage;  // 폭발 데미지
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	bool bIsTriggered;

	// Timer Handle
	UPROPERTY()
	FTimerHandle ExplosionTimerHandle;

	// "IInteractableInterface" Methods
	virtual void Activate(AActor* Activator) override;

	// Methods
	UFUNCTION(BlueprintCallable, Category = "Actions")
	void Explode();  // 폭발
};
