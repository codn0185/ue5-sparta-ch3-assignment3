#include "UI/MainMenuButtonWidget.h"

#include "Components/Button.h"
#include "Core/SpartaGameInstance.h"

void UMainMenuButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 버튼 이벤트 바인딩
	MainMenuButton->OnClicked.AddDynamic(this, &UMainMenuButtonWidget::OnClicked);
}

void UMainMenuButtonWidget::OnClicked()
{
	// 메인 메뉴 이동
	if (USpartaGameInstance* GameInstance = GetGameInstance<USpartaGameInstance>())
	{
		GameInstance->StartMainMenu();
	}
}
