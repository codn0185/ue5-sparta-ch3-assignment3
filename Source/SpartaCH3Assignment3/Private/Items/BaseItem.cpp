#include "Items/BaseItem.h"

#include "Components/SphereComponent.h"

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
}

FName ABaseItem::GetType() const
{
	return Type;
}
