#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Character.h"

#include "SpartaCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

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

  public:
	ASpartaCharacter();

  protected:
	// Callback Methods
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
