// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Pawns/Bird.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef HIGHLANDER_Bird_generated_h
#error "Bird.generated.h already included, missing '#pragma once' in Bird.h"
#endif
#define HIGHLANDER_Bird_generated_h

#define FID_Highlander_Source_Highlander_Public_Pawns_Bird_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesABird(); \
	friend struct Z_Construct_UClass_ABird_Statics; \
public: \
	DECLARE_CLASS(ABird, APawn, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Highlander"), NO_API) \
	DECLARE_SERIALIZER(ABird)


#define FID_Highlander_Source_Highlander_Public_Pawns_Bird_h_15_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	ABird(ABird&&); \
	ABird(const ABird&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ABird); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ABird); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ABird) \
	NO_API virtual ~ABird();


#define FID_Highlander_Source_Highlander_Public_Pawns_Bird_h_12_PROLOG
#define FID_Highlander_Source_Highlander_Public_Pawns_Bird_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Highlander_Source_Highlander_Public_Pawns_Bird_h_15_INCLASS_NO_PURE_DECLS \
	FID_Highlander_Source_Highlander_Public_Pawns_Bird_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> HIGHLANDER_API UClass* StaticClass<class ABird>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Highlander_Source_Highlander_Public_Pawns_Bird_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
