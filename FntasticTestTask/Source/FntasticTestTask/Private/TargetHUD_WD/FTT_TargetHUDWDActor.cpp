// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetHUD_WD/FTT_TargetHUDWDActor.h"

#include "TargetHUD_WD/FTT_TargetHUD_WD.h"
#include "Components/WidgetComponent.h"




AFTT_TargetHUDWDActor::AFTT_TargetHUDWDActor()
{
	PrimaryActorTick.bCanEverTick = true;


	TargetWDComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("TargetWD"));
	TargetWDComponent->CastShadow = false;
}


void AFTT_TargetHUDWDActor::BeginPlay()
{
	Super::BeginPlay();


	SetActorTickEnabled(false);
	SetActorHiddenInGame(true);

	TargetWDComponent->SetManuallyRedraw(true);
	TargetWDComponent->SetWidgetSpace(EWidgetSpace::Screen);
}





void AFTT_TargetHUDWDActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (!IsValid(TargetingActorComponent) || !IsValid(PlayerViewComponent) || !GetCanHUDBeVisibleNow())
	{
		HideTarget();
		return;
	}


	UFTT_TargetHUD_WD* Widget = Cast<UFTT_TargetHUD_WD>(TargetWDComponent->GetWidget());
	if (Widget && Widget->IsNeedRedraw)
	{
		Widget->IsNeedRedraw = false;
		TargetWDComponent->RequestRedraw();
	}

	UpdatePosition();
}







void AFTT_TargetHUDWDActor::ShowTargetByComp(USceneComponent* InTargetingActorComp, USceneComponent* InPlayerViewComponent)
{
	if (!IsValid(TargetWDComponent)) return;
	if (!IsValid(InTargetingActorComp) || !IsValid(InPlayerViewComponent)) return;
	if (TargetingActorComponent == InTargetingActorComp && PlayerViewComponent == InPlayerViewComponent) return;


	TargetingActor = InTargetingActorComp->GetAttachmentRootActor();
	PlayerViewComponent = InPlayerViewComponent;
	TargetingActorComponent = InTargetingActorComp;

	if (UFTT_TargetHUD_WD* LTargetWD = Cast<UFTT_TargetHUD_WD>(TargetWDComponent->GetWidget()))
	{
		LTargetWD->InitializeTargetHUDWD(TargetingActor);
		LTargetWD->SetTargetText(TargetText);

		TargetWDComponent->RequestRedraw();
	}

	if (!GetCanHUDBeVisibleNow()) return;

	SetActorTickEnabled(true);
	SetActorHiddenInGame(false);
}

void AFTT_TargetHUDWDActor::ShowTargetByActor(AActor* InTargetingActor, USceneComponent* InPlayerViewComponent)
{
	if (!IsValid(InTargetingActor)) return;


	ShowTargetByComp(InTargetingActor->GetRootComponent(), InPlayerViewComponent);
}




void AFTT_TargetHUDWDActor::HideTarget()
{
	SetActorTickEnabled(false);
	SetActorHiddenInGame(true);


	TargetingActor = nullptr;
	TargetingActorComponent = nullptr;

	PlayerViewComponent = nullptr;


	OnHideTarget();
}



void AFTT_TargetHUDWDActor::UpdatePosition()
{
	if (!IsValid(TargetingActorComponent) || !IsValid(PlayerViewComponent)) return;

	FVector TargetLocation = TargetingActorComponent->GetComponentLocation();
	TargetLocation.Z = (UseVerticalLocationFromPlayerComponent) ? PlayerViewComponent->GetOwner<AActor>()->GetActorLocation().Z + UpWidgetSpawnOffset : TargetLocation.Z + UpWidgetSpawnOffset;

	const FVector TargetDirection = PlayerViewComponent->GetComponentLocation() - TargetLocation;

	const FVector NewLocation = TargetLocation + TargetDirection * DistanceSplit;
	SetActorLocation(NewLocation);
}


