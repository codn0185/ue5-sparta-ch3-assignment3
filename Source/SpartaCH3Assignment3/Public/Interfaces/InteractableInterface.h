#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"

#include "InteractableInterface.generated.h"

UINTERFACE(MinimalAPI)
class UInteractableInterface : public UInterface
{
	GENERATED_BODY()
};

class SPARTACH3ASSIGNMENT3_API IInteractableInterface
{
	GENERATED_BODY()

  public:
	// 플레이어가 범위 안에 들어올 때 호출
	UFUNCTION()
	virtual void OnBeginOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult) = 0;
	// 플레이어가 아이템 범위 밖에 나갈 때 호출
	UFUNCTION()
	virtual void OnEndOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex) = 0;
	// 활성화 시 호출
	UFUNCTION()
	virtual void Activate(AActor* Activator) = 0;
	// 아이템 타입 반환
	UFUNCTION()
	virtual FName GetType() const = 0;
};
