// Copyright Epic Games, Inc. All Rights Reserved.

#include "RealVegetationForPFTCommands.h"

#define LOCTEXT_NAMESPACE "FRealVegetationForPFTModule"

void FRealVegetationForPFTCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "RealVegetationForPFT", "Bring up RealVegetationForPFT window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
