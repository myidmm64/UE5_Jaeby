// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "UE5_Jaeby/UE5_JaebyGameMode.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeUE5_JaebyGameMode() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UE5_JAEBY_API UClass* Z_Construct_UClass_AUE5_JaebyGameMode();
	UE5_JAEBY_API UClass* Z_Construct_UClass_AUE5_JaebyGameMode_NoRegister();
	UPackage* Z_Construct_UPackage__Script_UE5_Jaeby();
// End Cross Module References
	void AUE5_JaebyGameMode::StaticRegisterNativesAUE5_JaebyGameMode()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AUE5_JaebyGameMode);
	UClass* Z_Construct_UClass_AUE5_JaebyGameMode_NoRegister()
	{
		return AUE5_JaebyGameMode::StaticClass();
	}
	struct Z_Construct_UClass_AUE5_JaebyGameMode_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AUE5_JaebyGameMode_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_UE5_Jaeby,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AUE5_JaebyGameMode_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "UE5_JaebyGameMode.h" },
		{ "ModuleRelativePath", "UE5_JaebyGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AUE5_JaebyGameMode_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AUE5_JaebyGameMode>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AUE5_JaebyGameMode_Statics::ClassParams = {
		&AUE5_JaebyGameMode::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x008802ACu,
		METADATA_PARAMS(Z_Construct_UClass_AUE5_JaebyGameMode_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AUE5_JaebyGameMode_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AUE5_JaebyGameMode()
	{
		if (!Z_Registration_Info_UClass_AUE5_JaebyGameMode.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AUE5_JaebyGameMode.OuterSingleton, Z_Construct_UClass_AUE5_JaebyGameMode_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AUE5_JaebyGameMode.OuterSingleton;
	}
	template<> UE5_JAEBY_API UClass* StaticClass<AUE5_JaebyGameMode>()
	{
		return AUE5_JaebyGameMode::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AUE5_JaebyGameMode);
	AUE5_JaebyGameMode::~AUE5_JaebyGameMode() {}
	struct Z_CompiledInDeferFile_FID_UE5_Jaeby_Source_UE5_Jaeby_UE5_JaebyGameMode_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UE5_Jaeby_Source_UE5_Jaeby_UE5_JaebyGameMode_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AUE5_JaebyGameMode, AUE5_JaebyGameMode::StaticClass, TEXT("AUE5_JaebyGameMode"), &Z_Registration_Info_UClass_AUE5_JaebyGameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AUE5_JaebyGameMode), 2541807222U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UE5_Jaeby_Source_UE5_Jaeby_UE5_JaebyGameMode_h_1783977392(TEXT("/Script/UE5_Jaeby"),
		Z_CompiledInDeferFile_FID_UE5_Jaeby_Source_UE5_Jaeby_UE5_JaebyGameMode_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_UE5_Jaeby_Source_UE5_Jaeby_UE5_JaebyGameMode_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
