#include "UI/ExitGameButtonWidget.h"

#include "Components/Button.h"
#include "Core/SpartaGameInstance.h"

void UExitGameButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 버튼 이벤트 바인딩
	ExitGameButton->OnClicked.AddDynamic(this, &UExitGameButtonWidget::OnClicked);
}

void UExitGameButtonWidget::OnClicked()
{
	// 게임 종료
	if (USpartaGameInstance* GameInstance = GetGameInstance<USpartaGameInstance>())
	{
		GameInstance->ExitGame();
	}
}
