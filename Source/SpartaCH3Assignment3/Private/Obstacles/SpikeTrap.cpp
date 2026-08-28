#include "Obstacles/SpikeTrap.h"

#include "Components/BoxComponent.h"
#include "Kismet/GamePlayStatics.h"

ASpikeTrap::ASpikeTrap()
{
	PrimaryActorTick.bCanEverTick = true;

	// Initialize Components
	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Platform Mesh"));
	SetRootComponent(PlatformMesh);

	SpikeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Spike Mesh"));
	SpikeMesh->SetupAttachment(PlatformMesh);
	SpikeMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	DamageCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Damage Collision"));
	DamageCollision->SetupAttachment(SpikeMesh);
	DamageCollision->OnComponentBeginOverlap.AddDynamic(this, &ASpikeTrap::OnBeginOverlap);
	DamageCollision->OnComponentEndOverlap.AddDynamic(this, &ASpikeTrap::OnEndOverlap);

	SpikeInactivePoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spike Inactive Point"));
	SpikeInactivePoint->SetupAttachment(PlatformMesh);
	SpikeInactivePoint->SetRelativeLocation(FVector(0.f, 0.f, -100.f));

	SpikeActivePoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spike Active Point"));
	SpikeActivePoint->SetupAttachment(PlatformMesh);
	SpikeActivePoint->SetRelativeLocation(FVector(0.f, 0.f, 100.f));

	// Initialize Properties
	Type = "SpikeTrap";
	Damage = 15;
	SpikeState = ESpikeState::Inactive;
	SpikeMoveSpeed = 500.f;
	ActiveDuration = 1.5f;
	InactiveDuration = 3.f;
}

void ASpikeTrap::BeginPlay()
{
	Super::BeginPlay();

	switch (SpikeState)
	{
		case ESpikeState::Inactive:
			DeactivateSpike();
			break;
		case ESpikeState::Active:
			ActivateSpike();
			break;
		case ESpikeState::TransitionToActive:
			if (!GetWorldTimerManager().IsTimerActive(SpikeTimerHandle))
			{
				GetWorldTimerManager().SetTimer(
					SpikeTimerHandle,
					this,
					&ASpikeTrap::DeactivateSpike,
					ActiveDuration,
					false);
			}
			break;
		case ESpikeState::TransitionToInactive:
			if (!GetWorldTimerManager().IsTimerActive(SpikeTimerHandle))
			{
				GetWorldTimerManager().SetTimer(
					SpikeTimerHandle,
					this,
					&ASpikeTrap::ActivateSpike,
					InactiveDuration,
					false);
			}
			break;
	}
}

void ASpikeTrap::Tick(float DeltaTime)
{
	// 전환 상태일 때만 이동
	if (SpikeState == ESpikeState::Inactive || SpikeState == ESpikeState::Active)
	{
		return;
	}

	// SpikeMesh 컴포넌트 이동
	const FVector& TargetLocation = SpikeState == ESpikeState::TransitionToActive
										? SpikeActivePoint->GetRelativeLocation()
										: SpikeInactivePoint->GetRelativeLocation();
	const FVector& NewLocation = FMath::VInterpConstantTo(SpikeMesh->GetRelativeLocation(), TargetLocation, DeltaTime, SpikeMoveSpeed);
	SpikeMesh->SetRelativeLocation(NewLocation);

	// 도착 시 상태 업데이트
	if (NewLocation.Equals(TargetLocation))
	{
		if (SpikeState == ESpikeState::TransitionToActive)
		{
			SpikeState = ESpikeState::Active;
		}
		else
		{
			SpikeState = ESpikeState::Inactive;
		}
	}
}

void ASpikeTrap::ActivateSpike()
{
	// 활성화 상태로 전환
	SpikeState = ESpikeState::TransitionToInactive;

	// 타이머 설정 -  일정 시간 이후 비활성화
	GetWorldTimerManager().SetTimer(
		SpikeTimerHandle,
		this,
		&ASpikeTrap::DeactivateSpike,
		ActiveDuration,
		false);
}

void ASpikeTrap::DeactivateSpike()
{
	// 비활성화 상태로 전환
	SpikeState = ESpikeState::TransitionToActive;

	// 타이머 설정 -  일정 시간 이후 활성화
	GetWorldTimerManager().SetTimer(
		SpikeTimerHandle,
		this,
		&ASpikeTrap::ActivateSpike,
		InactiveDuration,
		false);
}

void ASpikeTrap::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 비활성화 상태에서 충돌 감지 방지
	if (SpikeState == ESpikeState::Inactive)
	{
		return;
	}

	if (IsValid(OtherActor) && OtherActor->ActorHasTag("Player"))
	{
		Activate(OtherActor);
	}
}

void ASpikeTrap::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void ASpikeTrap::Activate(AActor* Activator)
{
	if (IsValid(Activator) && Activator->ActorHasTag("Player"))
	{
		UGameplayStatics::ApplyDamage(
			Activator,
			Damage,
			nullptr,
			this,
			UDamageType::StaticClass());
	}
}

FName ASpikeTrap::GetType() const
{
	return Type;
}
