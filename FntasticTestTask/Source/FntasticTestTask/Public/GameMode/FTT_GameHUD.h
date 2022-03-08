// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FTT_GameHUD.generated.h"

/*

*/
UCLASS()
class FNTASTICTESTTASK_API AFTT_GameHUD : public AHUD
{
	GENERATED_BODY()

public:

	AFTT_GameHUD();

public:

	/*
		Primary draw call for the HUD 
	*/
	virtual void DrawHUD() override;

public:

	/*
		Crosshair asset pointer
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InteractComponent")
		class UTexture2D* CrosshairTex;
};
