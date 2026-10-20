// Copyright Chema Luque. Plugin Framework2DTerrain (modulo Editor).

using UnrealBuildTool;

public class Framework2DTerrainEditor : ModuleRules
{
	public Framework2DTerrainEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		// Todo lo de editor vive SOLO aqui: el modulo Runtime nunca depende de este,
		// asi el juego empaquetado compila sin el editor.
		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"Slate",
			"SlateCore",
			"UnrealEd",
			"EditorFramework",
			"Projects",        // IPluginManager: ruta de los iconos SVG del plugin
			"RenderCore",
			"PropertyEditor",  // selector de imagen de cada pagina del atlas
			"AppFramework",    // selector de color de los tintes de los generadores
			"AssetTools",      // importar las imagenes del ejemplo de exteriores
			"Framework2DTerrain"
		});
	}
}
