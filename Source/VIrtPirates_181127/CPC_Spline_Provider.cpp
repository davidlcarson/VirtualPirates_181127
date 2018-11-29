// Fill out your copyright notice in the Description page of Project Settings.

#include "CPC_Spline_Provider.h"

// Sets default values
/***********************************************/
ACPC_Spline_Provider::ACPC_Spline_Provider()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//UE_LOG(LogTemp, Warning, TEXT("At Spline_Provider Constructor"));

	//dc
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	OurSpline = CreateDefaultSubobject<USplineComponent>(TEXT("OurSpline"));
	OurSpline->SetupAttachment(RootComponent);

	return;
}

// Called when the game starts or when spawned
/***********************************************/
void ACPC_Spline_Provider::BeginPlay()
{
	//UE_LOG(LogTemp, Warning, TEXT("At Spline_Provider BeginPlay"));

	Super::BeginPlay();
	
}

// Called every frame
/***********************************************/
void ACPC_Spline_Provider::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

