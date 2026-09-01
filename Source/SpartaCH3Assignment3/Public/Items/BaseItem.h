#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "Interfaces/InteractableInterface.h"

#include "BaseItem.generated.h"

class USphereComponent;

UCLASS()
class SPARTACH3ASSIGNMENT3_API ABaseItem : public AActor, public IInteractableInterface
{
	GENERATED_BODY()

  public:
	ABaseItem();

  protected:
	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* RootCollision;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* StaticMesh;

	// VFX & SFX
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FX")
	UParticleSystem* PickupParticle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FX")
	USoundBase* PickupSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FX")
	float PickupParticleDuration;

	// Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	FName Type;

	// Implement "IInteractableInterface" Methods
	virtual void OnBeginOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult) override;
	virtual void OnEndOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex) override;
	virtual void Activate(AActor* Activator) override;
	virtual FName GetType() const override;
};
