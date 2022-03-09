// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveObjects/FTT_BaseInteractiveObject.h"
#include "FTT_InteractionButton.generated.h"

class AFTT_BaseInteractiveObject;

UCLASS()
class FNTASTICTESTTASK_API AFTT_InteractionButton : public AFTT_BaseInteractiveObject
{
	GENERATED_BODY()


//c++ protected methods
protected:

	//~ Begin IFTT_InteractiveObjectInterface
	virtual bool GetCanBeInteractedNow_Implementation() const override { return true; }
	virtual bool GetCanBeTargetedNow_Implementation() const override { return true; }
	//~End IFTT_InteractiveObjectInterface


//Blueprint methods
public:


	virtual void OnActivatedForInteract_Implementation(AActor* InstigatedBy, UFTT_InteractionComponent* InstigatorInteractionComponent);


//Blueprint values
public:

	/*
		Object with which to interact.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InteractionButton")
		AFTT_BaseInteractiveObject* InterectedObject = nullptr;

	
};
