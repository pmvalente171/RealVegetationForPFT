// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "RealVegetationForPFTStyle.h"

class FRealVegetationForPFTCommands : public TCommands<FRealVegetationForPFTCommands>
{
public:

	FRealVegetationForPFTCommands()
		: TCommands<FRealVegetationForPFTCommands>(TEXT("RealVegetationForPFT"), NSLOCTEXT("Contexts", "RealVegetationForPFT", "RealVegetationForPFT Plugin"), NAME_None, FRealVegetationForPFTStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};