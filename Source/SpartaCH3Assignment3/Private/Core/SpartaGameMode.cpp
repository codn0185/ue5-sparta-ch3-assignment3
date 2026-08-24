#include "Core/SpartaGameMode.h"

#include "Characters/SpartaCharacter.h"
#include "Characters/SpartaPlayerController.h"

ASpartaGameMode::ASpartaGameMode()
{
	DefaultPawnClass = ASpartaCharacter::StaticClass();
	PlayerControllerClass = ASpartaPlayerController::StaticClass();
}
