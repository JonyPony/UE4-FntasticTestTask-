// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FTT_TargetHUDWDActor.generated.h"

UCLASS(BlueprintType)
class FNTASTICTESTTASK_API AFTT_TargetHUDWDActor : public AActor
{
	GENERATED_BODY()
	
//constructor
public:

	AFTT_TargetHUDWDActor();

//c++ protected methods
protected:

	virtual void BeginPlay() override;

//c++ public methods
public:

	virtual void Tick(float DeltaTime) override;


//c++ protected values
protected:

	AActor* TargetingActor = nullptr;
	USceneComponent* TargetingActorComponent = nullptr;

	USceneComponent* PlayerViewComponent = nullptr;



//>>....................................................................................................<<//



//Blueprint methods
public:

	UFUNCTION(BlueprintCallable, Category = "TargetHUDWDActor")
		void ShowTargetByComp(USceneComponent* InTargetingActorComp, USceneComponent* InPlayerViewComponent, FName InSocketName = "None");
	UFUNCTION(BlueprintCallable, Category = "TargetWDActor")
		void ShowTargetByActor(AActor* InTargetingActor, USceneComponent* InPlayerViewComponent);

	UFUNCTION(BlueprintCallable, Category = "TargetHUDWDActor")
		void HideTarget();

	UFUNCTION(BlueprintNativeEvent, Category = "TargetHUDWDActor")
		void OnHideTarget();
		virtual void OnHideTarget_Implementation() {}

	UFUNCTION(BlueprintCallable, Category = "TargetHUDWDActor")
		void UpdatePosition();


	UFUNCTION(BlueprintNativeEvent, Category = "TargetHUDWDActor")
		bool GetCanHUDBeVisibleNow();
		virtual bool GetCanHUDBeVisibleNow_Implementation() { return true; }


//Blueprint values
public:

	/*
		Key - type of target.
		Do not use None.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "TargetWDActor")
		 FText TargetText;

	/*
		Percentage of the length of the distance to the character. 0.5 means that the widget will always be centered between the object and the player.
		0 - as close as possible to the object.
		1 - as close as possible to the player.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = "0.0", UIMin = "0.0", ClampMax = "1.0", UIMax = "1.0"), Category = "TargetHUDWDActor")
		float DistanceSplit = 0.0;
	/*
		Vertical offset relative to the position of the character.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "TargetHUDWDActor")
		float UpWidgetSpawnOffset = 0.0f;
	/*
		The Z-axis position will be calculated from the position of the player's component or
		from the position of the object over which the widget is hanging.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "TargetHUDWDActor")
		bool UseVerticalLocationFromPlayerComponent = true;




	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TargetHUDWDActor|Components")
		class UWidgetComponent* TargetWDComponent = nullptr;

};
