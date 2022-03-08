// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveObjects/FTT_BaseInteractiveObject.h"
#include "FTT_TurtleSpawner.generated.h"

class AFTT_Turtle;

/*

*/
UCLASS()
class FNTASTICTESTTASK_API AFTT_TurtleSpawner : public AFTT_BaseInteractiveObject
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
		TSubclassOf<AFTT_Turtle> TurtleClass = nullptr;


	/*
		Can only interact with one object at a time.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InteractComponent")
		AActor* TurtleEndPoint = nullptr;
	
};
