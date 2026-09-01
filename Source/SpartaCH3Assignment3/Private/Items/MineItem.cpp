#include "Items/MineItem.h"

#include "Components/SphereComponent.h"
#include "Kismet/GamePlayStatics.h"
#include "Particles/ParticleSystemComponent.h"

AMineItem::AMineItem()
{
	ExplosionCollsion = CreateDefaultSubobject<USphereComponent>(TEXT("Explosion Collsion"));
	ExplosionCollsion->SetupAttachment(RootComponent);
	ExplosionCollsion->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	ExplosionParticle = nullptr;
	ExplosionSound = nullptr;
	ExplosionParticleDuration = 1.f;

	ExplosionDelay = 3.f;
	ExplosionDamage = 30;
	bIsTriggered = false;
	Type = "Mine";
}

void AMineItem::Activate(AActor* Activator)
{
	if (bIsTriggered)
	{
		return;
	}

	bIsTriggered = true;

	Super::Activate(Activator);

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
	// 파티클
	if (ExplosionParticle)
	{
		// 파티클 컴포넌트 생성
		UParticleSystemComponent* ExplosionParticleComp = UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			ExplosionParticle,
			GetActorLocation(),
			GetActorRotation(),
			false);

		// 파티클 제거
		if (ExplosionParticleComp)
		{
			FTimerHandle DestroyParticleTimerHandle;
			GetWorld()->GetTimerManager().SetTimer(
				DestroyParticleTimerHandle,
				[ExplosionParticleComp]()
				{
					ExplosionParticleComp->DestroyComponent();
				},
				ExplosionParticleDuration,
				false);
		}
	}

	// 사운드
	if (ExplosionSound)
	{
		UGameplayStatics::PlaySoundAtLocation(
			GetWorld(),
			ExplosionSound,
			GetActorLocation());
	}

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
