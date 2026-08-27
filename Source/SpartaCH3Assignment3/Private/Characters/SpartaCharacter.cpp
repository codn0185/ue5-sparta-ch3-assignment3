#include "Characters/SpartaCharacter.h"

#include "EnhancedInputComponent.h"

#include "Camera/CameraComponent.h"
#include "Characters/SpartaPlayerController.h"
#include "Components/CapsuleComponent.h"
#include "Core/SpartaGameState.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

ASpartaCharacter::ASpartaCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	// Initialize Components
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bInheritPitch = true;
	SpringArm->bInheritYaw = true;
	SpringArm->bInheritRoll = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;

	// Controller Settings
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Movement Settings
	UCharacterMovementComponent* Movement = GetCharacterMovement();
	Movement->bOrientRotationToMovement = true;
	Movement->bUseControllerDesiredRotation = false;

	// Health
	MaxHealth = 100;
	Health = MaxHealth;

	// Movement
	MovementSpeedState = EMovementSpeedState::Walk;
	MovementSpeedMap.Add(EMovementSpeedState::Walk, 600.f);
	MovementSpeedMap.Add(EMovementSpeedState::Sprint, 1000.f);
}

void ASpartaCharacter::AddHealth(int32 Amount)
{
	Health = FMath::Clamp(Health + Amount, 0, MaxHealth);
}

bool ASpartaCharacter::IsDead() const
{
	return Health <= 0;
}

int32 ASpartaCharacter::GetMaxHealth() const
{
	return MaxHealth;
}

int32 ASpartaCharacter::GetHealth() const
{
	return Health;
}

void ASpartaCharacter::ApplySpeedEffect(float Multiplier, float Duration)
{
	FSpeedEffect& SpeedEffect = SpeedEffects.AddDefaulted_GetRef();  // 기본 값 생성 및 참조
	SpeedEffect.Multiplier = Multiplier;

	GetWorldTimerManager().SetTimer(
		SpeedEffect.TimerHandle,
		this,
		&ASpartaCharacter::UpdateSpeed,
		Duration,
		false);

	UpdateSpeed();
}
void ASpartaCharacter::BeginPlay()
{
	Super::BeginPlay();

	// 속도 설정
	UpdateSpeed();
}

void ASpartaCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (ASpartaPlayerController* PlayerController = Cast<ASpartaPlayerController>(GetController()))
		{
			// IA_Move
			if (PlayerController->MoveAction)
			{
				EnhancedInput->BindAction(
					PlayerController->MoveAction,
					ETriggerEvent::Triggered,
					this,
					&ASpartaCharacter::Move);
			}
			// IA_Look
			if (PlayerController->LookAction)
			{
				EnhancedInput->BindAction(
					PlayerController->LookAction,
					ETriggerEvent::Triggered,
					this,
					&ASpartaCharacter::Look);
			}
			// IA_Jump
			if (PlayerController->JumpAction)
			{
				EnhancedInput->BindAction(
					PlayerController->JumpAction,
					ETriggerEvent::Triggered,
					this,
					&ASpartaCharacter::StartJump);

				EnhancedInput->BindAction(
					PlayerController->JumpAction,
					ETriggerEvent::Completed,
					this,
					&ASpartaCharacter::StopJump);
			}
			// IA_Sprint
			if (PlayerController->SprintAction)
			{
				EnhancedInput->BindAction(
					PlayerController->SprintAction,
					ETriggerEvent::Triggered,
					this,
					&ASpartaCharacter::StartSprint);

				EnhancedInput->BindAction(
					PlayerController->SprintAction,
					ETriggerEvent::Completed,
					this,
					&ASpartaCharacter::StopSprint);
			}
		}
	}
}

void ASpartaCharacter::Move(const FInputActionValue& Value)
{
	if (!Controller)
	{
		return;
	}

	const FVector2D& MoveInput = Value.Get<FVector2D>();

	// 카메라 기준 방향 확인
	const FVector CameraForward = Camera->GetForwardVector();
	const FVector CameraRight = Camera->GetRightVector();

	// Z축 방향 제거
	FVector Forward = FVector(CameraForward.X, CameraForward.Y, 0.0f).GetSafeNormal();
	if (Forward.IsNearlyZero())
	{
		Forward = GetActorForwardVector();
	}
	FVector Right = FVector(CameraRight.X, CameraRight.Y, 0.0f).GetSafeNormal();
	if (Right.IsNearlyZero())
	{
		Right = GetActorRightVector();
	}

	// 이동
	if (!FMath::IsNearlyZero(MoveInput.X))
	{
		AddMovementInput(Forward, MoveInput.X);
	}
	if (!FMath::IsNearlyZero(MoveInput.Y))
	{
		AddMovementInput(Right, MoveInput.Y);
	}
}

void ASpartaCharacter::Look(const FInputActionValue& Value)
{
	if (!Controller)
	{
		return;
	}

	const FVector2D& LookInput = Value.Get<FVector2D>();

	AddControllerYawInput(LookInput.X);
	AddControllerPitchInput(LookInput.Y);
}

void ASpartaCharacter::StartJump(const FInputActionValue& Value)
{
	if (Value.Get<bool>())
	{
		Jump();
	}
}

void ASpartaCharacter::StopJump(const FInputActionValue& Value)
{
	if (!Value.Get<bool>())
	{
		StopJumping();
	}
}

void ASpartaCharacter::StartSprint(const FInputActionValue& Value)
{
	MovementSpeedState = EMovementSpeedState::Sprint;
	UpdateSpeed();
}

void ASpartaCharacter::StopSprint(const FInputActionValue& Value)
{
	MovementSpeedState = EMovementSpeedState::Walk;
	UpdateSpeed();
}

float ASpartaCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	Health = FMath::Clamp(Health - ActualDamage, 0, MaxHealth);
	if (Health <= 0)
	{
		OnDeath();
	}

	return ActualDamage;
}

void ASpartaCharacter::OnDeath()
{
	if (UWorld* World = GetWorld())
	{
		if (ASpartaGameState* GameState = World->GetGameState<ASpartaGameState>())
		{
			GameState->NotifyPlayerDead();
		}
	}

	EnableRagdoll();
}

void ASpartaCharacter::UpdateSpeed()
{
	float Multipier = 1.f;

	for (int32 Index = 0; Index < SpeedEffects.Num(); Index++)
	{
		const FSpeedEffect& SpeedEffect = SpeedEffects[Index];

		// 속도 효과 적용 중
		if (GetWorldTimerManager().IsTimerActive(SpeedEffect.TimerHandle))
		{
			Multipier *= SpeedEffect.Multiplier;
		}
		else  // 속도 효과 종료 -> 제거
		{
			SpeedEffects.RemoveAtSwap(Index--);
		}
	}

	// 속도 적용
	if (GetCharacterMovement())
	{
		if (MovementSpeedMap.Contains(MovementSpeedState))
		{
			GetCharacterMovement()->MaxWalkSpeed = MovementSpeedMap[MovementSpeedState] * Multipier;
		}
	}
}

void ASpartaCharacter::EnableRagdoll()
{
	// 캐릭터 메시 확인
	USkeletalMeshComponent* MeshComponent = GetMesh();
	if (!MeshComponent)
	{
		return;
	}

	// 메시 설정
	MeshComponent->Stop();                                    // 애니메이션 중지
	MeshComponent->SetSimulatePhysics(true);                  //  물리 시뮬레이션 활성화
	MeshComponent->SetCollisionProfileName(TEXT("Ragdoll"));  // 콜리전 프로파일 설정

	// 캡슐 콜리전 비활성화
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// 캐릭터 이동 비활성화
	GetCharacterMovement()->DisableMovement();
}
