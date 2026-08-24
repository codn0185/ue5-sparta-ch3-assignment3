#include "Core/SpartaGameMode.h"

#include "Characters/SpartaCharacter.h"
#include "Characters/SpartaPlayerController.h"
#include "Core/SpartaGameState.h"

ASpartaGameMode::ASpartaGameMode()
{
	DefaultPawnClass = ASpartaCharacter::StaticClass();
	PlayerControllerClass = ASpartaPlayerController::StaticClass();
	GameStateClass = ASpartaGameState::StaticClass();
}
