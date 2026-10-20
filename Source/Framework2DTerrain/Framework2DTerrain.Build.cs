// Copyright Chema Luque. Plugin Framework2DTerrain.

using UnrealBuildTool;

public class Framework2DTerrain : ModuleRules
{
	public Framework2DTerrain(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"ProceduralMeshComponent", // el quad donde se dibuja el terreno (aparece en la cabecera publica)
			"Paper2D"                  // AFramework2DCharacter hereda de APaperCharacter
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"InputCore",               // teclas del personaje de demo
			"RHI",                     // subida parcial de la textura del terreno
			"RenderCore",
			"PhysicsCore"              // cajas de colision sin cocinado
		});
	}
}
