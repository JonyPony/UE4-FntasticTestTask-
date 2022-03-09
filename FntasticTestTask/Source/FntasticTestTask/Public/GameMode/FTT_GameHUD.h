// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FTT_GameHUD.generated.h"

/*
	GameHUD
*/
UCLASS()
class FNTASTICTESTTASK_API AFTT_GameHUD : public AHUD
{
	GENERATED_BODY()

//constructor
public:

	AFTT_GameHUD();


//c++ public methods
public:

	/*
		Primary draw call for the HUD 
	*/
	virtual void DrawHUD() override;


//........................................................................................................................//



//Blueprint values
public:

	/*
		Crosshair asset pointer
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GameHUD")
		class UTexture2D* CrosshairTex;
};
