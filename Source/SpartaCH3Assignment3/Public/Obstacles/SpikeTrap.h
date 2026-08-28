#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "Interfaces/InteractableInterface.h"

#include "SpikeTrap.generated.h"

class UBoxComponent;

UENUM(BlueprintType)
enum class ESpikeState : uint8
{
	Inactive,              // 비활성화
	Active,                // 활성화
	TransitionToActive,    // 비활성화 -> 활성화 이동 중
	TransitionToInactive,  // 활성화 -> 비활성화 이동 중
};

UCLASS()
class SPARTACH3ASSIGNMENT3_API ASpikeTrap : public AActor, public IInteractableInterface
{
	GENERATED_BODY()

  public:
	ASpikeTrap();

  protected:
	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* PlatformMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* SpikeMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* DamageCollision;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* SpikeInactivePoint;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* SpikeActivePoint;

	// Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	FName Type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	int32 Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	ESpikeState SpikeState;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	float SpikeMoveSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	float ActiveDuration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	float InactiveDuration;

	// Timer Handles
	UPROPERTY()
	FTimerHandle SpikeTimerHandle;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// Spike Actions
	UFUNCTION(BlueprintCallable, Category = "Actions")
	void ActivateSpike();
	UFUNCTION(BlueprintCallable, Category = "Actions")
	void DeactivateSpike();

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

  public:
	UFUNCTION(BlueprintPure, Category = "Properties")
	FVector GetSize() const;
};
