// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class VIrtPirates_181127EditorTarget : TargetRules
{
	public VIrtPirates_181127EditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		ExtraModuleNames.Add("VIrtPirates_181127");
	}
}
