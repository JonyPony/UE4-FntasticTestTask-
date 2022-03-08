// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveObjects/InteractionButton/FTT_InteractionButton.h"


#include "InteractiveObjects/FTT_InteractionComponent.h"


void AFTT_InteractionButton::OnActivatedForInteract_Implementation(AActor* InstigatedBy, UFTT_InteractionComponent* InstigatorInteractionComponent)
{
	if (InstigatorInteractionComponent == nullptr || !IsValid(InterectedObject)) return;

	InstigatorInteractionComponent->InteractWith(InterectedObject);

	InstigatorInteractionComponent->EndInteractWith(this);
}


void AFTT_InteractionButton::OnEndIntaractWith_Implementation(AActor* InteractedActor, UFTT_InteractionComponent* InteractionComponent)
{
}
