#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Character.h"

#include "SpartaCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

struct FInputActionValue;

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
	float NormalSpeed;  // 기본 속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|Movement")
	float SprintSpeed;  // 달리기 속도

  public:
	UFUNCTION(BlueprintCallable, Category = "Properties|Health")
	void AddHealth(int32 Amount);  // 체력 회복
	UFUNCTION(BlueprintPure, Category = "Properties|Health")
	bool IsDead() const;  // 사망 여부 반환
	UFUNCTION(BlueprintPure, Category = "Properties|Health")
	int32 GetMaxHealth() const;  // 최대 체력 반환
	UFUNCTION(BlueprintPure, Category = "Properties|Health")
	int32 GetHealth() const;  // 현재 체력 반환

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
};
