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

	FVector Origin;
	FVector BoxExtend;
	Actor->GetActorBounds(true, Origin, BoxExtend);

	FVector MyLocation = MyActor->GetActorLocation();

	const float dx = FMath::Max3<float>(Origin.X - BoxExtend.X - MyLocation.X, 0, MyLocation.X - (Origin.X + BoxExtend.X));
	const float dy = FMath::Max3<float>(Origin.Y - BoxExtend.Y - MyLocation.Y, 0, MyLocation.Y - (Origin.Y + BoxExtend.Y));
	const float dz = FMath::Max3<float>(Origin.Z - BoxExtend.Z - MyLocation.Z, 0, MyLocation.Z - (Origin.Z + BoxExtend.Z));



	return	(!CanInteractOnlyWithOneActor ||
		IsActorAllowInteract &&
		FVector(dx, dy, dz).Size() <= MaxDistanceToInteractObject);
}

void UFTT_InteractionComponent::AddToPotentialInteract(AActor* InteractiveObject)
{
	if (!IsValid(InteractiveObject)) return;


	if (CanHaveOnlyOneActorToPotentialInteract)
	{
		RemoveAllFromPotentialInteract();
	}
	//else if (UniqueInteractionNamesInPotentialInteract.Contains(LInteractiveObjectComponent->InteractionName))
	//{
	//	RemoveAllPotentialInteractWithInteractionName(LInteractiveObjectComponent->InteractionName);
	//}



	PotentialForInteract.AddUnique(InteractiveObject);

	OnPotentialForInteractChanged(InteractiveObject, false);
	OnPotentialForInteractChangedBind.Broadcast(InteractiveObject, false);
}

void UFTT_InteractionComponent::RemoveFromPotentialInteract(AActor* InteractiveObject)
{
	PotentialForInteract.Remove(InteractiveObject);
}

void UFTT_InteractionComponent::RemoveAllFromPotentialInteract()
{
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
	if (PotentialForInteract.Num() <= 0) return;

	if (AFTT_BaseInteractiveObject* InteractiveObject = Cast<AFTT_BaseInteractiveObject>(PotentialForInteract[0])) 
	{
		InteractiveObject->OnActivatedForInteract(InteractiveObject, this);
	}
}

void UFTT_InteractionComponent::EndInteractWith_Implementation(AActor* InteractiveObject)
{
	if (AFTT_BaseInteractiveObject* LInteractiveObject = Cast<AFTT_BaseInteractiveObject>(InteractiveObject))
	{
		LInteractiveObject->OnEndIntaractWith(InteractiveObject, this);
	}

}

void UFTT_InteractionComponent::GetInteractingWithObjects(TArray<AActor*>& OutInteractingWithObjects) const
{
}
