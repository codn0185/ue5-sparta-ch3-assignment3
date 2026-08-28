#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"

#include "SpawnVolumeBase.generated.h"

class UBoxComponent;

UCLASS()
class SPARTACH3ASSIGNMENT3_API ASpawnVolumeBase : public AActor
{
	GENERATED_BODY()

  public:
	ASpawnVolumeBase();

  protected:
	// 소환 영역 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* SpawnBox;

  public:
	// 액터 소환
	UFUNCTION(BlueprintCallable)
	virtual AActor* SpawnActor();

  protected:
	// 소환 영역 내 무작위 위치 반환
	UFUNCTION(BlueprintCallable)
	virtual FVector GetRandomSpawnLocation() const;
};
