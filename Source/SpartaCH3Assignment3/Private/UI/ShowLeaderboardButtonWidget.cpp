#include "UI/ShowLeaderboardButtonWidget.h"

#include "Components/Button.h"

void UShowLeaderboardButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 버튼 이벤트 바인딩
	ShowLeaderboardButton->OnClicked.AddDynamic(this, &UShowLeaderboardButtonWidget::OnClicked);
}

void UShowLeaderboardButtonWidget::OnClicked()
{
	// TODO: 리더보드 띄우기
}
