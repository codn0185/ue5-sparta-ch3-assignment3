#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Character.h"

#include "SpartaCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UWidgetComponent;

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

  protected:
	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components|Camera")
	USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components|Camera")
	UCameraComponent* Camera;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components|UI")
	UWidgetComponent* OverheadWidget;

	// Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|Health")
	int32 MaxHealth;  // 최대 체력
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|Health")
	int32 Health;  // 현재 체력

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|Movement", meta = (ClampMin = "0", UIMin = "0"))
	float MinMovementSpeed;  // 최소 속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|Movement", meta = (ClampMin = "100", UIMin = "100"))
	float MaxMovementSpeed;  // 최대 속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|Movement")
	EMovementSpeedState MovementSpeedState;  // 현재 이동 속도 상태
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|Movement")
	TMap<EMovementSpeedState, float> MovementSpeedMap;  // 이동 상태 별 속도 값

	// Effects
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects|Speed")
	TArray<FSpeedEffect> SpeedEffects;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects|ReverseContol")
	bool bIsReversingControl;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects|ReverseContol")
	FTimerHandle ReverseControlTimerHandle;

  public:
	ASpartaCharacter();

	// Properties
	UFUNCTION(BlueprintCallable, Category = "Properties|Health")
	void AddHealth(int32 Amount);  // 체력 회복
	UFUNCTION(BlueprintPure, Category = "Properties|Health")
	bool IsDead() const;  // 사망 여부 반환
	UFUNCTION(BlueprintPure, Category = "Properties|Health")
	int32 GetMaxHealth() const;  // 최대 체력 반환
	UFUNCTION(BlueprintPure, Category = "Properties|Health")
	int32 GetHealth() const;  // 현재 체력 반환

	void UpdateOverheadWidgetHealth();

	// Effects
	UFUNCTION(BlueprintCallable, Category = "Effects|Speed")
	void ApplySpeedEffect(float Multiplier, float Duration);
	UFUNCTION(BlueprintCallable, Category = "Effects|ReverseContol")
	void ApplyReverseControl(float Duration);

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
	UFUNCTION(BlueprintCallable, Category = "Effects|ReverseContol")
	void UpdateReverseControl();

	// Etc.
	UFUNCTION()
	void EnableRagdoll();
};
