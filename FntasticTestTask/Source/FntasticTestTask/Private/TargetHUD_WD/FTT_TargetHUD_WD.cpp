// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetHUD_WD/FTT_TargetHUD_WD.h"


//...............Subwidgets/Elements................//

#include "Components/TextBlock.h"

//..................................................//

UFTT_TargetHUD_WD::UFTT_TargetHUD_WD(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UFTT_TargetHUD_WD::SetTargetText(const FText& Text)
{
	if (!TargetText) return;

	IsNeedRedraw = true;
	TargetText->SetText(Text);
}
