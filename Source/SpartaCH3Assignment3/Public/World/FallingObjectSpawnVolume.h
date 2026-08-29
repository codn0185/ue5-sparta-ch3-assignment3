#pragma once

#include "CoreMinimal.h"

#include "World/SpawnVolumeBase.h"

#include "FallingObjectSpawnVolume.generated.h"

UCLASS()
class SPARTACH3ASSIGNMENT3_API AFallingObjectSpawnVolume : public ASpawnVolumeBase
{
	GENERATED_BODY()

  protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
	TSubclassOf<AActor> FallingObjectClass;

  public:
	virtual AActor* SpawnActor() override;

  private:
	FRotator GetRandomYawRotation() const;  //  Z축(Yaw) 기준 무작위 회전 반환
};
