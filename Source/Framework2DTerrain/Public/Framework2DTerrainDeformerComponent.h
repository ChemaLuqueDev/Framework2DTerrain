// Copyright Chema Luque. Plugin Framework2DTerrain.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InputCoreTypes.h"
#include "Framework2DTerrainTypes.h"
#include "Framework2DTerrainDeformerComponent.generated.h"

class AFramework2DTerrainWorld;
class APlayerController;

/** Como cambia el terreno cada golpe. */
UENUM(BlueprintType)
enum class EFramework2DDeformMode : uint8
{
	// Suma Damage a cada pixel del circulo: se rompe al llegar a la dureza (Hardness) de su material.
	// Borde irregular y escombros (hacia el personaje si el terreno los manda a quien pica).
	Mine UMETA(DisplayName = "Picar (con dureza)"),

	// Quita un circulo exacto al instante, sin mirar la dureza (lo indestructible no se toca). Sin escombros.
	Dig  UMETA(DisplayName = "Excavar (al instante)")
};

/** De donde sale "delante" del personaje. */
UENUM(BlueprintType)
enum class EFramework2DFacingSource : uint8
{
	// Hacia donde se movio por ultima vez: vale gires como gires el dibujo (rotacion, escala...).
	Movement       UMETA(DisplayName = "Ultimo movimiento"),

	// Hacia donde mira el actor (si lo giras 180 grados al cambiar de lado).
	ActorRotation  UMETA(DisplayName = "Rotacion del actor"),

	// Hacia donde mira el sprite del Paper Character (girado 180 grados o con escala X negativa).
	SpriteRotation UMETA(DisplayName = "Rotacion del sprite"),

	// Hacia el cursor del raton.
	Mouse          UMETA(DisplayName = "Raton")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFramework2DOnTerrainDeformed, const FFramework2DDigResult&, Result);

/**
 * UFramework2DTerrainDeformerComponent
 * =================================================================
 * Deforma el terreno delante de su dueno. Ponlo en tu personaje (o usa AFramework2DCharacter,
 * que ya lo lleva) y, sin configurar nada mas, el CLIC IZQUIERDO pica delante del jugador:
 *   - "delante" sale de hacia donde se movio por ultima vez (o de su rotacion, el sprite o el raton);
 *   - lanza un rayo hacia delante y golpea el primer terreno solido dentro del alcance;
 *   - mantener pulsado repite el golpe (Hits Per Second).
 * Lo roto puede ir al inventario de la varita (Framework2D Terraform) si el dueno la lleva.
 *
 * Las teclas se leen cada frame del Player Controller que lo controla (sin Input Mappings), solo
 * en el jugador local y solo si la partida recibe la entrada: con un menu "solo interfaz" abierto,
 * en pausa o tras Disable Input no pica, y al volver hace falta pulsar de nuevo. En enemigos o personajes
 * de la IA no hace nada por si solo. Para usar tu propia entrada, desactiva Use Keys y llama a
 * Start/Stop Deforming o a Deform Now.
 *
 * No se replica: cada maquina cambia su propia copia del terreno (un jugador o pantalla partida).
 */
UCLASS(ClassGroup = (Framework2D), meta = (BlueprintSpawnableComponent, DisplayName = "Framework2D Terrain Deformer"))
class FRAMEWORK2DTERRAIN_API UFramework2DTerrainDeformerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFramework2DTerrainDeformerComponent();

	//---------------------- Entrada ----------------------

	/** Deforma mientras pulses una de las Keys (solo el jugador local que controla al dueno y con la entrada de la partida activa). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Deform|Input")
	bool bUseKeys = true;

	/** Teclas que deforman. Por defecto, clic izquierdo y gatillo derecho del mando. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Deform|Input", meta = (EditCondition = "bUseKeys"))
	TArray<FKey> Keys;

	/** Mantener pulsado repite el golpe. Si no, un golpe por pulsacion. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Deform|Input")
	bool bRepeatWhileHeld = true;

	/** Golpes por segundo como mucho (manteniendo pulsado o haciendo clic muy rapido). 0 = sin limite. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Deform|Input", meta = (ClampMin = "0.0", UIMax = "30.0"))
	float HitsPerSecond = 4.0f;

	//---------------------- Golpe ----------------------

	/** Picar (con la dureza de cada material) o excavar al instante. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Deform")
	EFramework2DDeformMode Mode = EFramework2DDeformMode::Mine;

	/** Radio (cm) del circulo que se rompe en cada golpe. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Deform", meta = (ClampMin = "1.0", UIMax = "500.0"))
	float Radius = 40.0f;

	/** Dano de cada golpe al picar. Se compara con la Hardness de cada material (Dirt 3, Stone 8...). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Deform", meta = (ClampMin = "1", ClampMax = "255", EditCondition = "Mode == EFramework2DDeformMode::Mine"))
	int32 Damage = 3;

	/** Hasta donde llega (cm) hacia delante desde el centro del dueno. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Deform", meta = (ClampMin = "0.0", UIMax = "2000.0"))
	float Reach = 120.0f;

	/**
	 * Buscar la pared: lanza un rayo hacia delante y golpea el primer terreno solido que encuentre
	 * dentro del alcance (si no hay ninguno, no hace nada). Desactivado, golpea siempre a Reach.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Deform")
	bool bAimAtFirstSolid = true;

	/** Altura (cm) desde la que sale el golpe, respecto al centro del dueno (negativo = hacia los pies). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Deform", meta = (UIMin = "-300.0", UIMax = "300.0"))
	float HeightOffset = 0.0f;

	/** Inclinacion (grados) del golpe: 0 = recto hacia delante, positivo = hacia arriba, negativo = hacia abajo. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Deform", meta = (ClampMin = "-90.0", ClampMax = "90.0"))
	float AimAngle = 0.0f;

	/** De donde sale "delante". */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Deform")
	EFramework2DFacingSource FacingSource = EFramework2DFacingSource::Movement;

	//---------------------- Otros ----------------------

	/** Terreno sobre el que actua. Vacio = todos los del nivel (golpea el mas cercano). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Deform|Other")
	TObjectPtr<AFramework2DTerrainWorld> Terrain = nullptr;

	/** Si el dueno lleva la varita (Framework2D Terraform), lo que se rompe va a su inventario. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Deform|Other")
	bool bStoreInInventory = true;

	/** Dibuja (en desarrollo) el circulo donde caeria el golpe. Util para ajustar los parametros. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Framework2D|Deform|Other")
	bool bShowAim = false;

	/** Salta en cada golpe que alcanza terreno: el que encuentra la pared o el que dana o rompe algun pixel (aunque la dureza aun no lo rompa). Para sonido, particulas, animacion... */
	UPROPERTY(BlueprintAssignable, Category = "Framework2D|Deform")
	FFramework2DOnTerrainDeformed OnTerrainDeformed;

	//---------------------- Funciones ----------------------

	/** Un golpe ahora mismo delante del dueno (no mira las teclas ni el limite de golpes por segundo). */
	UFUNCTION(BlueprintCallable, Category = "Framework2D|Deform")
	FFramework2DDigResult DeformNow();

	/** Un golpe en un punto del mundo, con el modo, radio y dano de este componente. */
	UFUNCTION(BlueprintCallable, Category = "Framework2D|Deform")
	FFramework2DDigResult DeformAt(FVector WorldPosition);

	/** Empieza a deformar como si se pulsara una de las teclas (para tu propia entrada). */
	UFUNCTION(BlueprintCallable, Category = "Framework2D|Deform")
	void StartDeforming();

	/** Deja de deformar (el contrario de Start Deforming). */
	UFUNCTION(BlueprintCallable, Category = "Framework2D|Deform")
	void StopDeforming();

	/** True mientras se pulsa una de las teclas o tras Start Deforming. */
	UFUNCTION(BlueprintPure, Category = "Framework2D|Deform")
	bool IsDeforming() const { return bHeldByCode || bKeysDown; }

	/** Donde caeria el golpe ahora. False si no hay terreno solido delante (con Buscar la pared). */
	UFUNCTION(BlueprintCallable, Category = "Framework2D|Deform")
	bool GetAimPoint(FVector& OutPoint);

	/** Direccion (unitaria, en el plano del terreno) en la que se golpea. */
	UFUNCTION(BlueprintPure, Category = "Framework2D|Deform")
	FVector GetAimDirection() const;

	/** Hacia donde mira: +1 = derecha del terreno, -1 = izquierda. */
	UFUNCTION(BlueprintPure, Category = "Framework2D|Deform")
	float GetFacing() const { return Facing; }

	/**
	 * Fija hacia donde mira (+1 derecha, -1 izquierda). Con "Ultimo movimiento" dura hasta la siguiente
	 * entrada de movimiento horizontal; con las demas fuentes se vuelve a calcular en cada frame.
	 */
	UFUNCTION(BlueprintCallable, Category = "Framework2D|Deform")
	void SetFacing(float Direction);

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	float Facing = 1.0f;        // +1 derecha del terreno, -1 izquierda
	FVector MouseAim = FVector::ZeroVector; // direccion hacia el raton (en el plano), si FacingSource es Mouse
	bool bHeldByCode = false;   // StartDeforming
	bool bKeysDown = false;     // alguna de las teclas armadas, pulsada
	TArray<FKey, TInlineAllocator<2>> ArmedKeys; // teclas que se vieron pulsar con la entrada activa (una que ya venia pulsada no cuenta)
	bool bPendingPress = false; // pulsacion de tecla que espera al limite de golpes por segundo
	bool bPendingStart = false; // Start Deforming que espera al limite (aunque llegue Stop en el mismo frame)
	float Cooldown = 0.0f;      // segundos hasta el proximo golpe permitido

	// Terrenos del nivel (si Terrain esta vacio): se buscan la primera vez, al golpear, si alguno
	// desaparece y, mientras no haya ninguno, cada medio segundo; no cada frame.
	mutable TArray<TWeakObjectPtr<AFramework2DTerrainWorld>> LevelTerrains;
	mutable bool bTerrainsSearched = false;
	mutable double LastTerrainSearch = 0.0; // sin ninguno, se vuelve a mirar cada medio segundo
	using FTerrainList = TArray<AFramework2DTerrainWorld*, TInlineAllocator<4>>;

	// Terrenos sobre los que actua (Terrain o todos los del nivel). bRefresh vuelve a buscarlos.
	void GatherTerrains(FTerrainList& Out, bool bRefresh = false) const;
	// Ejes del plano del terreno: derecha y arriba (los del primer terreno o los del mundo, X y Z).
	void GetPlaneAxes(FVector& OutRight, FVector& OutUp) const;
	// Recalcula Facing (y MouseAim) segun FacingSource.
	void UpdateFacing(APlayerController* PC);
	// Punto del que sale el golpe.
	FVector GetAimOrigin() const;
	// Centro del golpe y terreno al que le toca (nullptr = todos). False si no hay nada que golpear.
	bool FindTarget(FVector& OutCenter, AFramework2DTerrainWorld*& OutTerrain) const;
	// Olvida las teclas pulsadas: hasta volver a pulsarlas no pican.
	void DisarmKeys();
	// Aplica el golpe en Center (a un terreno o a todos) y avisa.
	FFramework2DDigResult ApplyAt(const FVector& Center, AFramework2DTerrainWorld* Only);
	// El Player Controller local que controla al dueno, o nullptr.
	APlayerController* GetLocalPlayerController() const;
	// True si la entrada de la partida llega a ese jugador (sin menu "solo interfaz" ni Disable Input).
	bool IsGameInputOpen(const APlayerController* PC) const;
};
