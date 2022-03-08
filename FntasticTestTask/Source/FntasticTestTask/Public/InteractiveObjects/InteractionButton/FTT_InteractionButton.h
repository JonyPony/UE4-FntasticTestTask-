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



//Blueprint methods
public:


	virtual void OnActivatedForInteract_Implementation(AActor* InstigatedBy, UFTT_InteractionComponent* InstigatorInteractionComponent);

	virtual void OnEndIntaractWith_Implementation(AActor* InteractedActor, UFTT_InteractionComponent* InteractionComponent);

//Blueprint values
public:

	/*
		Can only interact with one object at a time.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InteractComponent")
		AFTT_BaseInteractiveObject* InterectedObject = nullptr;

	
};
