// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveObjects/FTT_BaseInteractiveObject.h"
#include "FTT_TurtleSpawner.generated.h"

class AFTT_Turtle;


UCLASS()
class FNTASTICTESTTASK_API AFTT_TurtleSpawner : public AFTT_BaseInteractiveObject
{
	GENERATED_BODY()


//c++ protected methods
protected:

	//~ Begin IFTT_InteractiveObjectInterface
	virtual bool GetCanBeInteractedNow_Implementation() const override { return true; }
	//~End IFTT_InteractiveObjectInterface



//Blueprint methods
public:

	virtual void OnActivatedForInteract_Implementation(AActor* InstigatedBy, UFTT_InteractionComponent* InstigatorInteractionComponent);


//Blueprint values
public:

	/*
		Class of Turtle.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TurtleSpawner")
		TSubclassOf<AFTT_Turtle> TurtleClass = nullptr;

	/*
		Actor defining final point of turtle movement.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TurtleSpawner")
		AActor* TurtleEndPoint = nullptr;
	
};
