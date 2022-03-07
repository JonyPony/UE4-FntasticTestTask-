// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FTT_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class FNTASTICTESTTASK_API AFTT_PlayerController : public APlayerController
{
	GENERATED_BODY()

//constructor
public:

	AFTT_PlayerController();
	

//Blueprint public methods
public:

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "PlayerController")
		FVector2D GetViewportHalfSize() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "PlayerController")
		bool GetHitResultAtScreenRadius(const FVector2D& ScreenPosition, float Radius, ECollisionChannel TraceChannel, bool bTraceComplex, FHitResult& HitResult) const;

};
