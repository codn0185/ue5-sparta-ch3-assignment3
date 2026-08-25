#include "Items/MineItem.h"

#include "Components/SphereComponent.h"
#include "Kismet/GamePlayStatics.h"

AMineItem::AMineItem()
{
	ExplosionCollsion = CreateDefaultSubobject<USphereComponent>(TEXT("Explosion Collsion"));
	ExplosionCollsion->SetupAttachment(RootComponent);
	ExplosionCollsion->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	ExplosionDelay = 3.f;
	ExplosionDamage = 30;
	Type = "Mine";
}

void AMineItem::Activate(AActor* Activator)
{
	// 이미 타이머 활성화 중이면 무시
	if (ExplosionTimerHandle.IsValid()) return;

	// 타이머 설정 - 일정 시간 후 폭발
	GetWorldTimerManager().SetTimer(
		ExplosionTimerHandle,
		this,
		&AMineItem::Explode,
		ExplosionDelay,
		false);
}

void AMineItem::Explode()
{
	// 범위 내 액터 확인
	TArray<AActor*> OverlappingActors;
	ExplosionCollsion->GetOverlappingActors(OverlappingActors);

	// 플레이어에 데미지 적용
	for (AActor* Actor : OverlappingActors)
	{
		if (IsValid(Actor) && Actor->ActorHasTag("Player"))
		{
			UGameplayStatics::ApplyDamage(
				Actor,
				ExplosionDamage,
				nullptr,
				this,
				UDamageType::StaticClass());
		}
	}

	// 아이템 제거
	Destroy();
}
