#include "World/SpawnVolumeBase.h"

#include "Components/BoxComponent.h"

ASpawnVolumeBase::ASpawnVolumeBase()
{
	PrimaryActorTick.bCanEverTick = false;

	SpawnBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Spawning Box"));
	SetRootComponent(SpawnBox);
}

AActor* ASpawnVolumeBase::SpawnActor()
{
	return nullptr;
}

FVector ASpawnVolumeBase::GetRandomSpawnLocation() const
{
	if (!SpawnBox)
	{
		return FVector::ZeroVector;
	}

	// 소환 위치 및 범위 확인
	const FVector& BoxOrigin = SpawnBox->GetComponentLocation();
	const FVector& BoxExtent = SpawnBox->GetScaledBoxExtent();

	// 무작위 위치 반환
	return BoxOrigin + FVector(
						   FMath::FRandRange(-BoxExtent.X, BoxExtent.X),
						   FMath::FRandRange(-BoxExtent.Y, BoxExtent.Y),
						   FMath::FRandRange(-BoxExtent.Z, BoxExtent.Z));
}
