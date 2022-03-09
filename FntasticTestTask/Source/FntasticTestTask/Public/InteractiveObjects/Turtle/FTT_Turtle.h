// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveObjects/FTT_BaseInteractiveObject.h"
#include "FTT_Turtle.generated.h"

/*

*/
UCLASS()
class FNTASTICTESTTASK_API AFTT_Turtle : public AFTT_BaseInteractiveObject
{
	GENERATED_BODY()


//c++ protected methods
protected:

	//~ Begin IFTT_InteractiveObjectInterface
	virtual bool GetCanBeInteractedNow_Implementation() const override { return true; }
	//~End IFTT_InteractiveObjectInterface


//Blueprint methods
public:

	UFUNCTION(BlueprintCallable, Category = "Turtle")
		void SetStartEndTransform(const FTransform& StartTransform, const FTransform& EndTransform);


//Blueprint values
public:

	/*
		Transform where the Turtle starts to move.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Turtle")
		FTransform TurtleStartTransform;
	/*
		Transform where the Turtle end to move.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Turtle")
		FTransform TurtleEndTransform;

};
