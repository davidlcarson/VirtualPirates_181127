// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/SplineComponent.h"

#include "CPC_Spline_Provider.generated.h"

//-------------------------------------------------------------+
UCLASS() 
class VIRTPIRATES_181127_API ACPC_Spline_Provider : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPC_Spline_Provider();

protected:

	//our spline component;
	//181111: Added UPROPERTY. I think it helps make
	//..the spline editable in the Editor...
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USplineComponent* OurSpline;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//dc
	//Get our spline component
	UFUNCTION(BlueprintCallable)
	USplineComponent* GetOurSpline() { return OurSpline; }
};



