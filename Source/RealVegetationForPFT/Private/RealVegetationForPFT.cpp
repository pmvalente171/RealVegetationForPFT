// Copyright Epic Games, Inc. All Rights Reserved.

#include "RealVegetationForPFT.h"
#include "RealVegetationForPFTStyle.h"
#include "RealVegetationForPFTCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"

static const FName RealVegetationForPFTTabName("RealVegetationForPFT");

#define LOCTEXT_NAMESPACE "FRealVegetationForPFTModule"

void FRealVegetationForPFTModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FRealVegetationForPFTStyle::Initialize();
	FRealVegetationForPFTStyle::ReloadTextures();

	FRealVegetationForPFTCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FRealVegetationForPFTCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FRealVegetationForPFTModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FRealVegetationForPFTModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(RealVegetationForPFTTabName, FOnSpawnTab::CreateRaw(this, &FRealVegetationForPFTModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FRealVegetationForPFTTabTitle", "RealVegetationForPFT"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FRealVegetationForPFTModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FRealVegetationForPFTStyle::Shutdown();

	FRealVegetationForPFTCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(RealVegetationForPFTTabName);
}

TSharedRef<SDockTab> FRealVegetationForPFTModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FRealVegetationForPFTModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("RealVegetationForPFT.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(WidgetText)
			]
		];
}

void FRealVegetationForPFTModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(RealVegetationForPFTTabName);
}

void FRealVegetationForPFTModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FRealVegetationForPFTCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FRealVegetationForPFTCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FRealVegetationForPFTModule, RealVegetationForPFT)