// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "FTT_InteractiveObjectInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(BlueprintType, MinimalAPI)
class UFTT_InteractiveObjectInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class FNTASTICTESTTASK_API IFTT_InteractiveObjectInterface 
{
	GENERATED_IINTERFACE_BODY()


public:

	/*
		@return true if interface owner can be interacted in general.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "InteractiveObject")
		bool GetCanBeInteractedNow() const;
	/*
		@return true if interface owner can be targeted in general.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "InteractiveObject")
		bool GetCanBeTargetedNow() const;
	/*
		Set target effect enabled for interface owner.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "InteractiveObject")
		void TargetInteractiveObject(bool EnableTarget);
};
