#include "World/FallingObjectSpawnVolume.h"

#include "Components/BoxComponent.h"

AActor* AFallingObjectSpawnVolume::SpawnActor()
{
	// FallingObjectClass가 할당되지 않은 경우
	if (!FallingObjectClass)
	{
		return nullptr;
	}

	// 액터 소환
	return GetWorld()->SpawnActor<AActor>(
		FallingObjectClass,
		GetRandomSpawnLocation(),
		GetRandomYawRotation());
}

FRotator AFallingObjectSpawnVolume::GetRandomYawRotation() const
{
	return FRotator(
		0.f,
		FMath::RandRange(0.f, 360.f),
		0.f);
}
