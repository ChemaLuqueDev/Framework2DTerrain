// Copyright Chema Luque. Plugin Framework2DTerrain.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Framework2DDemoCharacter.generated.h"

class UCameraComponent;
class AFramework2DTerrainWorld;
class UFramework2DTerraformComponent;

/**
 * AFramework2DDemoCharacter
 * =================================================================
 * Personaje de DEMO para probar la rotura estilo KYORA sin montar nada.
 *   - A / D  (o flechas)  -> moverse izquierda / derecha
 *   - Espacio / W         -> saltar
 *   - Clic IZQUIERDO      -> picar donde apunta el raton (lo picado va al inventario)
 *   - Clic DERECHO        -> colocar el material seleccionado (gasta inventario)
 *   - Rueda / Q / E       -> cambiar de material
 *   - Clic CENTRAL / F    -> explosion en el raton
 *
 * Se auto-posee (Player 0) y busca solo el AFramework2DTerrainWorld del nivel.
 * Movimiento bloqueado al plano XZ (2D), gravedad -Z estandar de Unreal.
 * El inventario se muestra arriba a la izquierda (mensajes de depuracion).
 *
 * COMO USARLO:
 *   Opcion A (rapida): arrastra este actor al nivel, cerca del terreno, y Play.
 *   Opcion B (recomendada): clic derecho sobre la clase -> Create Blueprint class,
 *     abre el Blueprint, asigna una Skeletal/Static Mesh al componente Mesh si
 *     quieres verlo, y coloca ESE Blueprint en el nivel.
 *
 * No usa Enhanced Input a proposito: sondea las teclas en Tick para que funcione
 * sin configurar Input Mappings en Project Settings.
 */
UCLASS()
class FRAMEWORK2DTERRAIN_API AFramework2DDemoCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AFramework2DDemoCharacter();

	/** Multiplicador de velocidad de movimiento. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D Demo")
	float MoveInputScale = 1.0f;

	/** Radio (cm) de la explosion de prueba (clic central / F). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D Demo")
	float ExplosionRadius = 90.0f;

	/** Distancia de la camara al personaje (en el eje +Y, mirando hacia -Y). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D Demo")
	float CameraDistance = 1200.0f;

	/** Muestra el inventario en pantalla. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D Demo")
	bool bShowInventory = true;

	/** La varita: picar, recoger y colocar. Ajusta aqui alcance, dano, radios... */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Framework2D Demo")
	TObjectPtr<UFramework2DTerraformComponent> Terraform;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

private:
	UPROPERTY() TObjectPtr<UCameraComponent> Camera;
	UPROPERTY() TObjectPtr<AFramework2DTerrainWorld> Terrain;

	// Proyecta la posicion del raton sobre el plano del terreno (Y = cte).
	bool MouseToTerrainPlane(FVector& OutHit) const;
	void DrawInventory() const;
};
