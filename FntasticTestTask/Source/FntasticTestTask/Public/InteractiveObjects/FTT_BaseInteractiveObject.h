// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "InteractiveObjects/FTT_InteractiveObjectInterface.h"

#include "FTT_BaseInteractiveObject.generated.h"

class UFTT_InteractionComponent;

UCLASS()
class FNTASTICTESTTASK_API AFTT_BaseInteractiveObject : public AActor,
														public IFTT_InteractiveObjectInterface
{
	GENERATED_BODY()
	
//constructors
public:

	AFTT_BaseInteractiveObject();

//c++ protected methods
protected:
	
	virtual void BeginPlay() override;


	//~ Begin IFTT_InteractiveObjectInterface
	virtual bool GetCanBeInteractedNow_Implementation() const override { return false; }
	virtual bool GetCanBeTargetedNow_Implementation() const override { return false; }
	virtual void TargetInteractiveObject_Implementation(bool EnableTarget) override {}
	//~End IFTT_InteractiveObjectInterface



//>>............................................................................................................<<//



//Blueprint methods
public:

	UFUNCTION(BlueprintNativeEvent, Category = "BaseInteractiveObject")
		void OnActivatedForInteract(AActor* InstigatedBy, UFTT_InteractionComponent* InstigatorInteractionComponent);
		virtual void OnActivatedForInteract_Implementation(AActor* InstigatedBy, UFTT_InteractionComponent* InstigatorInteractionComponent) {}

	UFUNCTION(BlueprintNativeEvent, Category = "BaseInteractiveObject")
		void OnEndIntaractWith(AActor* InteractedActor, UFTT_InteractionComponent* InteractionComponent);
		virtual void OnEndIntaractWith_Implementation(AActor* InteractedActor, UFTT_InteractionComponent* InteractionComponent) {}



};
