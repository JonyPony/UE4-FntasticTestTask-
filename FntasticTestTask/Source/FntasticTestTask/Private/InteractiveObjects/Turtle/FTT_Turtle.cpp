// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveObjects/Turtle/FTT_Turtle.h"



void AFTT_Turtle::SetStartEndTransform(const FTransform& StartTransform, const FTransform& EndTransform)
{
	TurtleStartTransform = StartTransform;
	TurtleEndTransform = EndTransform;
}
