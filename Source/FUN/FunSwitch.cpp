// Fill out your copyright notice in the Description page of Project Settings.


#include "FunSwitch.h"

// Sets default values
AFunSwitch::AFunSwitch()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Root->SetupAttachment(RootComponent);
	SetRootComponent(Root);
	
	Pivot = CreateDefaultSubobject<USceneComponent>(TEXT("Pivot"));
	Pivot->SetupAttachment(Root);
	

}

void AFunSwitch::Toggle() {
	bIsOn = !bIsOn;
	
	Pivot->SetRelativeRotation(bIsOn ? PivotRotationOn : PivotRotationOff);
}

// Called when the game starts or when spawned
void AFunSwitch::BeginPlay()
{
	Super::BeginPlay();
	Pivot->SetRelativeRotation(PivotRotationOff);
	
}

// Called every frame
void AFunSwitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

