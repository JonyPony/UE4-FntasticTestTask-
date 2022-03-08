// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FTT_TargetHUD_WD.generated.h"


class UTextBlock;

UCLASS(Abstract)
class FNTASTICTESTTASK_API UFTT_TargetHUD_WD : public UUserWidget
{
	GENERATED_BODY()


//constructor
public:

	UFTT_TargetHUD_WD(const FObjectInitializer& ObjectInitializer);



//>>.......................................................................................................................................<<//


//Blueprint methods
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "TargetHUDWD")
		void InitializeTargetHUDWD(AActor* InActor);
		virtual void InitializeTargetHUDWD_Implementation(AActor* InActor) {}

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "TargetHUDWD")
		void DeinitializeTargetHUDWD();
		void DeinitializeTargetHUDWD_Implementation() {}


	UFUNCTION(BlueprintCallable, Category = "TargetWD")
		void SetTargetText(const FText& Text);

//Blueprint values
public:

	/*
		Text block for current target hint text.
	*/
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "TargetWD|Widgets")
		UTextBlock* TargetText = nullptr;

	/*
		Can be used in TargetWDActor for determinate redrawing for performance.
	*/
	UPROPERTY(BlueprintReadWrite)
		bool IsNeedRedraw = true;
};
