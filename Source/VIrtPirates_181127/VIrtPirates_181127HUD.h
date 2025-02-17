// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "VIrtPirates_181127HUD.generated.h"

UCLASS()
class AVIrtPirates_181127HUD : public AHUD
{
	GENERATED_BODY()

public:
	AVIrtPirates_181127HUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

