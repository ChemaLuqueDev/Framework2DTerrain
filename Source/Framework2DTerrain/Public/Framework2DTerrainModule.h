// Copyright Chema Luque. Plugin Framework2DTerrain.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

/**
 * Modulo Runtime del plugin. No hace nada especial: solo existe para que
 * Unreal cargue el codigo del plugin. La logica vive en AFramework2DTerrainWorld.
 *
 * Prefijo F = clase/struct C++ "plana" (no es un UObject, no la gestiona el
 * Garbage Collector). Los modulos siempre usan F.
 */
class FFramework2DTerrainModule : public IModuleInterface
{
public:
	virtual void StartupModule() override {}
	virtual void ShutdownModule() override {}
};
