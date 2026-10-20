// Copyright Chema Luque. Plugin Framework2DTerrain (modulo Editor).

#include "Modules/ModuleManager.h"
#include "EditorModeRegistry.h"
#include "Editor.h"
#include "EngineUtils.h"
#include "Engine/Texture2D.h"
#include "Textures/SlateIcon.h"
#include "Framework2DEditorStyle.h"
#include "Framework2DTilePaintMode.h"
#include "Framework2DTerrainWorld.h"
#include "Framework2DTileMapAsset.h"
#include "Framework2DTileSet.h"

#define LOCTEXT_NAMESPACE "Framework2DTerrainEditor"

/**
 * Modulo de EDITOR (solo se carga en el editor). Registra el modo "Framework2D Tiles" y
 * mantiene al dia la vista previa de los terrenos: al deshacer/rehacer y al editar el
 * tilemap, el tileset o el atlas desde sus propios paneles.
 */
class FFramework2DTerrainEditorModule : public IModuleInterface
{
public:
	virtual void StartupModule() override
	{
		// El estilo (iconos SVG, botones) va antes que el modo: el icono del modo sale de ahi.
		FFramework2DEditorStyle::Initialize();

		// RegisterMode<T> esta marcado como obsoleto en UE5 (la ruta nueva es UEdMode) pero funciona.
		PRAGMA_DISABLE_DEPRECATION_WARNINGS
		FEditorModeRegistry::Get().RegisterMode<FFramework2DTilePaintMode>(
			FFramework2DTilePaintMode::ModeId,
			LOCTEXT("ModeName", "Framework2D Tiles"),
			FSlateIcon(FFramework2DEditorStyle::GetStyleSetName(), "F2D.Mode", "F2D.Mode.Small"),
			/*bVisible*/ true,
			/*PriorityOrder*/ 500);
		PRAGMA_ENABLE_DEPRECATION_WARNINGS

		PropertyChangedHandle = FCoreUObjectDelegates::OnObjectPropertyChanged.AddRaw(this, &FFramework2DTerrainEditorModule::OnObjectPropertyChanged);
		UndoRedoHandle = FEditorDelegates::PostUndoRedo.AddRaw(this, &FFramework2DTerrainEditorModule::OnUndoRedo);
	}

	virtual void ShutdownModule() override
	{
		FCoreUObjectDelegates::OnObjectPropertyChanged.Remove(PropertyChangedHandle);
		FEditorDelegates::PostUndoRedo.Remove(UndoRedoHandle);

		PRAGMA_DISABLE_DEPRECATION_WARNINGS
		FEditorModeRegistry::Get().UnregisterMode(FFramework2DTilePaintMode::ModeId);
		PRAGMA_ENABLE_DEPRECATION_WARNINGS

		// El ultimo: el modo (y su panel) ya no usan el estilo.
		FFramework2DEditorStyle::Shutdown();
	}

private:
	FDelegateHandle PropertyChangedHandle;
	FDelegateHandle UndoRedoHandle;

	template <typename FilterFunc>
	static void ForEachEditorTerrain(FilterFunc&& Filter)
	{
		// OJO: no usar GEditor->GetEditorWorldContext(): durante el arranque del editor ya
		// llegan cambios de propiedades (texturas) y ese contexto aun no existe (assert).
		if (!GEngine) { return; }
		for (const FWorldContext& Context : GEngine->GetWorldContexts())
		{
			UWorld* World = Context.World();
			if (Context.WorldType != EWorldType::Editor || !World) { continue; }
			for (TActorIterator<AFramework2DTerrainWorld> It(World); It; ++It)
			{
				if (Filter(*It)) { It->RebuildPreview(); }
			}
		}
	}

	void OnObjectPropertyChanged(UObject* Object, FPropertyChangedEvent& Event)
	{
		if (!Object) { return; }
		if (Object->IsA<UFramework2DTileMapAsset>() || Object->IsA<UFramework2DTileSet>() || Object->IsA<UTexture2D>())
		{
			ForEachEditorTerrain([Object](AFramework2DTerrainWorld* Terrain) { return Terrain->UsesAsset(Object); });
		}
	}

	void OnUndoRedo()
	{
		ForEachEditorTerrain([](AFramework2DTerrainWorld*) { return true; });
	}
};

IMPLEMENT_MODULE(FFramework2DTerrainEditorModule, Framework2DTerrainEditor)

#undef LOCTEXT_NAMESPACE
