#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Character.h"

#include "SpartaCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

struct FInputActionValue;

USTRUCT(BlueprintType)
struct FSpeedEffect
{
	GENERATED_BODY();

  public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Multiplier;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FTimerHandle TimerHandle;
};

UENUM(BlueprintType)
enum class EMovementSpeedState : uint8
{
	Walk,
	Sprint,
};

UCLASS()
class SPARTACH3ASSIGNMENT3_API ASpartaCharacter : public ACharacter
{
	GENERATED_BODY()

  public:
	ASpartaCharacter();

  protected:
	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components|Camera")
	USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components|Camera")
	UCameraComponent* Camera;

	// Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|Health")
	int32 MaxHealth;  // 최대 체력
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|Health")
	int32 Health;  // 현재 체력

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|Movement")
	EMovementSpeedState MovementSpeedState;  // 현재 이동 속도 상태
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|Movement")
	TMap<EMovementSpeedState, float> MovementSpeedMap;  // 이동 상태 별 속도 값

	// Effects
	TArray<FSpeedEffect> SpeedEffects;

  public:
	UFUNCTION(BlueprintCallable, Category = "Properties|Health")
	void AddHealth(int32 Amount);  // 체력 회복
	UFUNCTION(BlueprintPure, Category = "Properties|Health")
	bool IsDead() const;  // 사망 여부 반환
	UFUNCTION(BlueprintPure, Category = "Properties|Health")
	int32 GetMaxHealth() const;  // 최대 체력 반환
	UFUNCTION(BlueprintPure, Category = "Properties|Health")
	int32 GetHealth() const;  // 현재 체력 반환

	// Effects
	UFUNCTION(BlueprintCallable, Category = "Effects|Speed")
	void ApplySpeedEffect(float Multiplier, float Duration);

  protected:
	// Callback Methods
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Input Events
	UFUNCTION()
	virtual void Move(const FInputActionValue& Value);
	UFUNCTION()
	virtual void Look(const FInputActionValue& Value);
	UFUNCTION()
	virtual void StartJump(const FInputActionValue& Value);
	UFUNCTION()
	virtual void StopJump(const FInputActionValue& Value);
	UFUNCTION()
	virtual void StartSprint(const FInputActionValue& Value);
	UFUNCTION()
	virtual void StopSprint(const FInputActionValue& Value);

	// Events
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION()
	void OnDeath();

	// Speed
	UFUNCTION(BlueprintCallable, Category = "Effects|Speed")
	void UpdateSpeed();

	// Etc.
	UFUNCTION()
	void EnableRagdoll();
};
