// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FTT_InteractionComponent.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPotentialForInteractChanged, AActor*, InteractiveActor, bool, WasRemoved);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInteractingObjectChanged, AActor*, InteractiveActor, bool, StoppedInteraction);


/*
	It is attaching to an object that will interact with the InteractiveObjec.
*/
UCLASS( Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent) )
class FNTASTICTESTTASK_API UFTT_InteractionComponent : public UActorComponent
{
	GENERATED_BODY()

//constructor
public:	

	UFTT_InteractionComponent();

//c++ public methods
public:

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


//c++ protected methods
protected:

	virtual void BeginPlay() override;



//c++ protected values
protected:

	TArray<AActor*> PotentialForInteract;

	AActor* MyActor = nullptr;


//..........................................................................................................................................//
//..........................................................................................................................................//


//Blueprint methods
public:

	//...............................................Interacting..............................................................//

	UFUNCTION(BlueprintCallable, Server, Reliable, Category = "InteractComponent|Interacting")
		void InteractWith(AActor* InteractiveObject);
		void InteractWith_Implementation(AActor* InteractiveObject);

		UFUNCTION(BlueprintCallable, Server, Reliable, Category = "InteractComponent|Interacting")
		void InteractWithPotentialForInteract();
		void InteractWithPotentialForInteract_Implementation();

	UFUNCTION(BlueprintCallable, Server, Reliable, Category = "InteractComponent|Interacting")
		void EndInteractWith(AActor* InteractiveObject);
		void EndInteractWith_Implementation(AActor* InteractiveObject);


	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, BlueprintPure, Category = "InteractComponent|Interacting")
		bool GetCanInteractWithActor(AActor* Actor) const;
		virtual bool GetCanInteractWithActor_Implementation(AActor* Actor) const;


	UFUNCTION(BlueprintCallable, Category = "InteractComponent|Interacting")
		bool GetCanTargetedActor(AActor* Actor) const;

	//........................................................................................................................//



	//...........................................PotentialForInteract.........................................................//

	UFUNCTION(BlueprintCallable, Category = "InteractComponent|PotentialForInteract")
		void AddToPotentialInteract(AActor* InteractiveObject);
	UFUNCTION(BlueprintCallable, Category = "InteractComponent|PotentialForInteract")
		void RemoveFromPotentialInteract(AActor* InteractiveObject);

	UFUNCTION(BlueprintCallable, Category = "InteractComponent|PotentialForInteract")
		void RemoveAllFromPotentialInteract();



	UFUNCTION(BlueprintNativeEvent, Category = "InteractiveObjectComponent|PotentialForInteract")
		void OnPotentialForInteractChanged(AActor* InteractiveActor, bool WasRemoved);
		virtual void OnPotentialForInteractChanged_Implementation(AActor* InteractiveActor, bool WasRemoved) {}
	UPROPERTY(BlueprintAssignable, Category = "InteractComponent|EventsForBind")
		FOnPotentialForInteractChanged OnPotentialForInteractChangedBind;

	UFUNCTION(BlueprintNativeEvent, Category = "InteractiveObjectComponent|InteractingObject")
		void OnInteractingObjectChanged(AActor* InteractiveActor,  bool StoppedInteraction);
	virtual void OnInteractingObjectChanged_Implementation(AActor* InteractiveActor, bool StoppedInteraction) {}
	UPROPERTY(BlueprintAssignable, Category = "InteractComponent|EventsForBind")
		FOnInteractingObjectChanged OnInteractingObjectChangedBind;




	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "InteractComponent|PotentialForInteract")
		TArray<AActor*> GetPotentialForInteractObjects() const;

	//........................................................................................................................//




//Blueprint values
public:

	/*
		Can only interact with one object at a time.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InteractComponent")
		bool CanInteractOnlyWithOneActor = true;
	/*
		When trying to add a new potential actor for interaction, it will replace the old one.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InteractComponent")
		bool CanHaveOnlyOneActorToPotentialInteract = true;

	/*
		The maximum distance to the nearest point of the interactive object for interaction.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.0", UIMin = "0.0"), Category = "InteractComponent")
		float MaxDistanceToInteractObject = 450.0f;
};
