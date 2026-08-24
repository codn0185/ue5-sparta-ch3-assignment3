#pragma once

#include "CoreMinimal.h"

#include "GameFramework/PlayerController.h"

#include "SpartaPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class SPARTACH3ASSIGNMENT3_API ASpartaPlayerController : public APlayerController
{
	GENERATED_BODY()

  public:
	ASpartaPlayerController();

	// InputMappingContext & InputAction
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|Input")
	UInputMappingContext* CharacterInputMappingContext;  // IMC_Character
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|Input")
	UInputAction* MoveAction;  // IA_Move
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|Input")
	UInputAction* LookAction;  // IA_Look
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|Input")
	UInputAction* JumpAction;  // IA_Jump
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|Input")
	UInputAction* SprintAction;  // IA_Sprint

  protected:
	// Callback Methods
	virtual void BeginPlay() override;
};
