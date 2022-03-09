// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveObjects/FTT_InteractionComponent.h"

#include "InteractiveObjects/FTT_BaseInteractiveObject.h"

#include "InteractiveObjects/FTT_InteractiveObjectInterface.h"



UFTT_InteractionComponent::UFTT_InteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	MyActor = GetOwner();
}


void UFTT_InteractionComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UFTT_InteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}




bool UFTT_InteractionComponent::GetCanInteractWithActor_Implementation(AActor* Actor) const
{
	if (!IsValid(Actor)) return false;

	bool IsActorAllowInteract = true;
	if (Actor->GetClass()->ImplementsInterface(UFTT_InteractiveObjectInterface::StaticClass()))
	{
		IsActorAllowInteract = IFTT_InteractiveObjectInterface::Execute_GetCanBeInteractedNow(Actor);
	}

	return	IsActorAllowInteract;
}


bool UFTT_InteractionComponent::GetCanTargetedActor(AActor* Actor) const
{
	bool IsActorAllowTargeted = false;

	if (Actor->GetClass()->ImplementsInterface(UFTT_InteractiveObjectInterface::StaticClass()))
	{
		IsActorAllowTargeted = IFTT_InteractiveObjectInterface::Execute_GetCanBeTargetedNow(Actor);
	}

	return  IsActorAllowTargeted;
}



void UFTT_InteractionComponent::AddToPotentialInteract(AActor* InteractiveObject)
{
	if (!IsValid(InteractiveObject)) return;

	if (CanHaveOnlyOneActorToPotentialInteract)	RemoveAllFromPotentialInteract();

	PotentialForInteract.AddUnique(InteractiveObject);

	OnPotentialForInteractChanged(InteractiveObject, false);
	OnPotentialForInteractChangedBind.Broadcast(InteractiveObject, false);
}

void UFTT_InteractionComponent::RemoveFromPotentialInteract(AActor* InteractiveObject)
{
	PotentialForInteract.Remove(InteractiveObject);

	OnPotentialForInteractChanged(InteractiveObject, true);
	OnPotentialForInteractChangedBind.Broadcast(InteractiveObject, true);
}

void UFTT_InteractionComponent::RemoveAllFromPotentialInteract()
{
	for (int i = PotentialForInteract.Num() - 1; i >= 0; --i)
	{
		RemoveFromPotentialInteract(PotentialForInteract[i]);
	}

	PotentialForInteract.Empty();
}


TArray<AActor*> UFTT_InteractionComponent::GetPotentialForInteractObjects() const
{
	return PotentialForInteract;
}




void UFTT_InteractionComponent::InteractWith_Implementation(AActor* InteractiveObject)
{
	if (!GetCanInteractWithActor(InteractiveObject)) return;


	if (AFTT_BaseInteractiveObject* LInteractiveObject = Cast<AFTT_BaseInteractiveObject>(InteractiveObject))
	{
		LInteractiveObject->OnActivatedForInteract(InteractiveObject, this);
	}
}

void UFTT_InteractionComponent::InteractWithPotentialForInteract_Implementation()
{
	if (PotentialForInteract.Num() > 0) InteractWith(PotentialForInteract[0]);
}

void UFTT_InteractionComponent::EndInteractWith_Implementation(AActor* InteractiveObject)
{
	if (AFTT_BaseInteractiveObject* LInteractiveObject = Cast<AFTT_BaseInteractiveObject>(InteractiveObject))
	{
		LInteractiveObject->OnEndIntaractWith(InteractiveObject, this);
	}
}