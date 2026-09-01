#include "Items/BaseItem.h"

#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

ABaseItem::ABaseItem()
{
	PrimaryActorTick.bCanEverTick = false;

	// Initialize Components
	RootCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Root Collision"));
	SetRootComponent(RootCollision);
	RootCollision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	StaticMesh->SetupAttachment(RootCollision);

	// 오버랩 이벤트 바인딩
	RootCollision->OnComponentBeginOverlap.AddDynamic(this, &ABaseItem::OnBeginOverlap);
	RootCollision->OnComponentEndOverlap.AddDynamic(this, &ABaseItem::OnEndOverlap);

	// VFX & SFX
	PickupParticle = nullptr;
	PickupSound = nullptr;
	PickupParticleDuration = 2.f;
}

void ABaseItem::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsValid(OtherActor) && OtherActor->ActorHasTag("Player"))
	{
		Activate(OtherActor);
	}
}

void ABaseItem::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void ABaseItem::Activate(AActor* Activator)
{
	// 파티클
	if (PickupParticle)
	{
		// 파티클 컴포넌트 생성
		UParticleSystemComponent* PickupParticleComp = UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			PickupParticle,
			GetActorLocation(),
			GetActorRotation(),
			false);

		// 파티클 제거
		if (PickupParticleComp)
		{
			FTimerHandle DestroyParticleTimerHandle;
			GetWorld()->GetTimerManager().SetTimer(
				DestroyParticleTimerHandle,
				[PickupParticleComp]()
				{
					PickupParticleComp->DestroyComponent();
				},
				PickupParticleDuration,
				false);
		}
	}

	// 사운드
	if (PickupSound)
	{
		UGameplayStatics::PlaySoundAtLocation(
			GetWorld(),
			PickupSound,
			GetActorLocation());
	}
}

FName ABaseItem::GetType() const
{
	return Type;
}
