#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "Interfaces/InteractableInterface.h"

#include "FallingObject.generated.h"

class USphereComponent;

UCLASS()
class SPARTACH3ASSIGNMENT3_API AFallingObject : public AActor, public IInteractableInterface
{
	GENERATED_BODY()

  public:
	AFallingObject();

  protected:
	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* StaticMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* DamageCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	FName Type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	int32 Damage;

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHit(
		UPrimitiveComponent* HitComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		FVector NormalImpulse,
		const FHitResult& Hit);

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
