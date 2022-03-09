// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveObjects/TurtleSpawner/FTT_TurtleSpawner.h"

#include "InteractiveObjects/FTT_InteractionComponent.h"

#include "InteractiveObjects/Turtle/FTT_Turtle.h"



void AFTT_TurtleSpawner::OnActivatedForInteract_Implementation(AActor* InstigatedBy, UFTT_InteractionComponent* InstigatorInteractionComponent)
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	if (TurtleClass != nullptr && TurtleEndPoint != nullptr)
	{
		if (AFTT_Turtle* LTurtle = GetWorld()->SpawnActor<AFTT_Turtle>(TurtleClass, GetTransform(), SpawnInfo)) 
		{
			LTurtle->SetStartEndTransform(GetTransform(), TurtleEndPoint->GetTransform());

			InstigatorInteractionComponent->InteractWith(LTurtle);
		}

	}

	InstigatorInteractionComponent->EndInteractWith(this);
}