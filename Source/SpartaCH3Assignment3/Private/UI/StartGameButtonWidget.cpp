#include "UI/StartGameButtonWidget.h"

#include "Components/Button.h"
#include "Core/SpartaGameInstance.h"

void UStartGameButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 버튼 이벤트 바인딩
	StartGameButton->OnClicked.AddDynamic(this, &UStartGameButtonWidget::OnClicked);
}

void UStartGameButtonWidget::OnClicked()
{
	// 게임 시작
	if (USpartaGameInstance* GameInstance = GetGameInstance<USpartaGameInstance>())
	{
		GameInstance->StartGame();
	}
}
