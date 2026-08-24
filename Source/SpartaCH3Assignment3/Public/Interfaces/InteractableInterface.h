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
	// 플레이어가 아이템 범위 안에 들어올 때 호출
	UFUNCTION()
	virtual void OnItemBeginOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult) = 0;
	// 플레이어가 아이템 범위 밖에 나갈 때 호출
	UFUNCTION()
	virtual void OnItemEndOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex) = 0;
	// 아이템 활성화 시 호출
	UFUNCTION()
	virtual void ActivateItem(AActor* Activator) = 0;
	// 아이템 타입 반환
	UFUNCTION()
	virtual FName GetItemType() const = 0;
	// 아이템 제거 시 호출
	UFUNCTION()
	virtual void DestroyItem() = 0;
};
