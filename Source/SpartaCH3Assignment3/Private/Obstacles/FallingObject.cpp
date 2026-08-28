#include "Obstacles/FallingObject.h"

#include "Components/SphereComponent.h"
#include "Items/BaseItem.h"
#include "Kismet/GameplayStatics.h"

AFallingObject::AFallingObject()
{
	PrimaryActorTick.bCanEverTick = false;

	// Initialize Components
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	SetRootComponent(StaticMesh);
	StaticMesh->SetSimulatePhysics(true);
	StaticMesh->SetEnableGravity(true);
	StaticMesh->SetNotifyRigidBodyCollision(true);
	StaticMesh->OnComponentHit.AddDynamic(this, &AFallingObject::OnHit);

	DamageCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Damage Collision"));
	DamageCollision->SetupAttachment(StaticMesh);

	// Initialize Properties
	Type = "FallingObject";
	Damage = 20;
}

void AFallingObject::BeginPlay()
{
	Super::BeginPlay();

	StaticMesh->SetPhysicsLinearVelocity(FVector(0.f, 0.f, -100.f));
}

void AFallingObject::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!IsValid(OtherActor))
	{
		return;
	}

	// 아이템 충돌 - 무시
	if (OtherActor->IsA(ABaseItem::StaticClass()))
	{
		return;
	}

	// 플레이어 충돌 - 데미지
	if (OtherActor->ActorHasTag("Player"))
	{
		Activate(OtherActor);
		return;
	}

	// 기타 구조물 충돌 - 파괴
	Destroy();
}

void AFallingObject::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void AFallingObject::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void AFallingObject::Activate(AActor* Activator)
{
	if (IsValid(Activator) && Activator->ActorHasTag("Player"))
	{
		UGameplayStatics::ApplyDamage(
			Activator,
			Damage,
			nullptr,
			this,
			UDamageType::StaticClass());
		Destroy();
	}
}

FName AFallingObject::GetType() const
{
	return Type;
}
