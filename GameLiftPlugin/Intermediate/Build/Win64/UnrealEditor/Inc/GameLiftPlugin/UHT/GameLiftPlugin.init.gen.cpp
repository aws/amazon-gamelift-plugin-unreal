// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGameLiftPlugin_init() {}
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_GameLiftPlugin;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_GameLiftPlugin()
	{
		if (!Z_Registration_Info_UPackage__Script_GameLiftPlugin.OuterSingleton)
		{
			static const UECodeGen_Private::FPackageParams PackageParams = {
				"/Script/GameLiftPlugin",
				nullptr,
				0,
				PKG_CompiledIn | 0x00000040,
				0xB0DBD547,
				0x2C5F3374,
				METADATA_PARAMS(nullptr, 0)
			};
			UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_GameLiftPlugin.OuterSingleton, PackageParams);
		}
		return Z_Registration_Info_UPackage__Script_GameLiftPlugin.OuterSingleton;
	}
	static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_GameLiftPlugin(Z_Construct_UPackage__Script_GameLiftPlugin, TEXT("/Script/GameLiftPlugin"), Z_Registration_Info_UPackage__Script_GameLiftPlugin, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0xB0DBD547, 0x2C5F3374));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
