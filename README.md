# Framework2D Terrain — tilemaps que se rompen píxel a píxel (estilo KYORA)

Pintas tu nivel con tiles, como en el editor de tilemaps de Unreal, y en el juego **cada
píxel del dibujo se puede picar, explotar, recoger y volver a colocar**, con colisión
real, como en KYORA.

- **Editor de tiles propio:** atlas completo (clic = un tile, arrastrar = un bloque), pincel,
  borrador, cubo, rectángulo, cuentagotas y **vista previa** de lo que vas a pintar. Ves el
  nivel tal cual quedará mientras pintas.
- **Capas en planos separados**, como los tilemaps de Unreal: fondo, terreno y decoración
  delante o detrás del personaje.
- **Colisión a tu gusto:** por tile o celda a celda con el **pincel de colisión** (bloques,
  mitades, rampas, plataformas, paredes invisibles).
- **Flipbooks** (tiles animados) en su propia lista, sin tocar los tiles del atlas.
- **Varios atlas** en un mismo Tile Set (cueva, bosque, desierto...), cada uno en su pestaña.
- **Generadores de vegetación:** pintas una casilla y aparecen plantas, rocas o setas
  repartidas con variación de posición, escala, tinte y volteo. Se rompen como el terreno.
- **Rotura píxel a píxel:** cada material tiene su dureza, el borde del corte se dibuja solo,
  los agujeros salen irregulares y los escombros vuelan hacia quien pica.
- **Terraformar:** lo que picas va a un inventario y lo puedes colocar en otro sitio.
- **Rápido:** al romper, solo se repintan y se recolisionan los trozos tocados.

> 📘 **Manual completo con capturas:** [Docs/Framework2DTerrain_Manual.pdf](Docs/Framework2DTerrain_Manual.pdf) (19 páginas).

Funciona en **Unreal Engine 5.0 – 5.6**: compila sin avisos y con pruebas automáticas en 5.0.3 y 5.6.1.

| Nivel pintado con el atlas de ejemplo | Después de picar túneles, explosiones, Dig y colocar piedra y madera |
|---|---|
| ![Nivel pintado](Docs/nivel_pintado.png) | ![Nivel roto](Docs/nivel_roto.png) |

*Capturas reales del render del plugin. En los agujeros se ve la capa de fondo (pared de cueva)
y el borde del corte se dibuja solo.*

---

## Índice

1. [Instalación](#1-instalación)
2. [Tu primer nivel en 5 minutos](#2-tu-primer-nivel-en-5-minutos)
3. [El editor de tiles](#3-el-editor-de-tiles)
4. [Materiales: cómo se rompe cada cosa](#4-materiales-cómo-se-rompe-cada-cosa)
5. [Usarlo en tu juego (Blueprint)](#5-usarlo-en-tu-juego-blueprint)
6. [Ajustes del terreno](#6-ajustes-del-terreno)
7. [Consejos para dibujar los tiles](#7-consejos-para-dibujar-los-tiles)
8. [Problemas comunes](#8-problemas-comunes)
9. [Límites y siguientes pasos](#9-límites-y-siguientes-pasos)
10. [Cambios de versión](#10-cambios-de-versión)

---

## 1. Instalación

1. Copia la carpeta `Framework2DTerrain` dentro de la carpeta `Plugins/` de tu proyecto
   (créala si no existe):
   ```
   TuProyecto/
     TuProyecto.uproject
     Plugins/
       Framework2DTerrain/
   ```
2. Tu proyecto tiene que ser **C++**, es decir, tener carpeta `Source/`. Si es solo Blueprint:
   *Tools → New C++ Class → None → Create Class*.
3. Clic derecho en el `.uproject` → **Generate Visual Studio project files** y compila.
   Si al abrir el editor te pregunta si quieres recompilar, pulsa **Sí**.
4. En *Edit → Plugins* comprueba que **Framework2D Terrain** está activo. Activa también
   **Paper2D**: su material de sprites es el que usa el terreno por defecto.

---

## 2. Tu primer nivel en 5 minutos

Con el atlas de ejemplo que trae el plugin (`Framework2DTerrain/Ejemplo/AtlasEjemplo.png`,
16 tiles de 16×16).

### Paso 1 · Importa el atlas
Arrastra `AtlasEjemplo.png` al Content Browser.
*(Opcional, para que la paleta se vea nítida: clic derecho sobre la textura →
**Sprite Actions → Apply Paper2D Texture Settings**.)*

### Paso 2 · Crea el Tile Set
*Content Browser → Add → Miscellaneous → **Data Asset** → `Framework2DTileSet`*. Ábrelo y:
- **Atlas** = `AtlasEjemplo`, **Tile Width / Tile Height** = 16.
  La lista **Tiles** se rellena sola, con una fila por tile del atlas.
- Elige el **material** de cada tile en su desplegable. Para el atlas de ejemplo:

| Tile | Dibujo | Material | Fill Pattern |
|---|---|---|---|
| 0 | tierra con hierba | Dirt | |
| 1 | tierra | Dirt | ✔ |
| 2 | piedra | Stone | ✔ |
| 3 | madera | Wood | ✔ |
| 4 | arena | Sand | ✔ |
| 5 | roca madre | Bedrock | |
| 6 | pared de cueva | None *(úsalo en una capa de fondo)* | |
| 7 | hierba | Decoration | |
| 8, 9 | rampas | Dirt | |
| 10, 11 | esquinas redondeadas | Dirt | |
| 12 | tablón | Wood | |
| 13 | piedra con mineral | Stone | |
| 14 | piedra con musgo | Stone | |
| 15 | columna | Stone | |

*Fill Pattern* indica con qué tile se pinta un material cuando el jugador lo **coloca** (ver §4).

### Paso 3 · Crea el Tile Map
*Add → Miscellaneous → Data Asset → `Framework2DTileMapAsset`*. Ábrelo y pon:
- **Tile Set** = el que acabas de crear.
- **Width / Height**: tamaño del nivel **en tiles** (por ejemplo 64 × 32).

### Paso 4 · Coloca el terreno
En *Place Actors* busca **Framework2D Terrain** y arrástralo al nivel. En *Details*, en
**Tile Map**, pon tu Tile Map. Ya verás el rectángulo del nivel, todavía vacío.

> El terreno vive en el plano **XZ** del actor: X hacia la derecha y Z hacia arriba. Para
> pintar cómodo usa la vista ortográfica **Right** (Alt+Shift+K), o una cámara en +Y mirando hacia
> −Y, como la de la plantilla *2D Side Scroller*. La vista *Front* lo enseña de canto.

### Paso 5 · Pinta
Activa el modo **Framework2D Tiles**: en la barra de herramientas, en el desplegable de modos
(donde pone *Selection Mode*). A la izquierda se abre el panel con la paleta. Elige un tile
y pinta con el clic izquierdo. Ver §3.

### Paso 6 · Juega
Arrastra **Framework2DDemoCharacter** encima del terreno y pulsa **Play**:

| Control | Acción |
|---|---|
| A / D o flechas | moverse |
| Espacio / W | saltar |
| **Clic izquierdo** | picar donde apuntas (lo picado va al inventario) |
| **Clic derecho** | colocar el material seleccionado |
| Rueda / Q / E | cambiar de material |
| Clic central / F | explosión |

El inventario se ve arriba a la izquierda.

---

## 3. El editor de tiles

Modo **Framework2D Tiles**. Pinta sobre el terreno **seleccionado** en el nivel; si no hay
ninguno seleccionado, sobre el primero que encuentre. El panel tiene seis tarjetas: estado,
herramientas, capas, colisión, atlas y flipbooks. Todos los botones explican lo que hacen al
dejar el ratón encima.

> **Mira el terreno con la vista ortográfica _Right_** (o una cámara en +Y mirando hacia −Y,
> como la plantilla *2D Side Scroller*). Así la X va a la derecha y las capas de delante quedan
> más cerca de ti. Desde el otro lado el nivel se ve en espejo.

### Herramientas

| Herramienta | Atajo | Qué hace |
|---|---|---|
| **Brush** | B | Pinta el tile, el bloque o el flipbook elegido. Arrastrando pinta en línea. |
| **Eraser** | E | Borra tiles de la capa activa. |
| **Bucket** | G | Rellena la zona contigua de tiles iguales. |
| **Rectangle** | R | Arrastra para rellenar un rectángulo. |
| **Eyedropper** | I | Toma el tile o flipbook bajo el cursor (y su capa) y vuelve al pincel. |
| **Collision** | C | Pinta formas de colisión celda a celda (ver *Colisión*, más abajo). |

- **Vista previa:** antes de hacer clic ves, semitransparente bajo el ratón, lo que vas a pintar:
  el tile, el bloque entero, el flipbook animado o la forma de colisión. El borrador se ve en
  rojo. Se activa y desactiva con el interruptor **Preview**.
- **Grid** y **Show collision** son los otros dos interruptores. *Ver colisión* dibuja en verde
  lo que choca, y en naranja los tiles con colisión pintada a mano.
- **Ctrl+Z / Ctrl+Y** deshacen y rehacen. Cada trazo cuenta como un solo paso.
- Cámara: clic derecho o rueda, como siempre. El clic izquierdo solo pinta **dentro** del
  mapa; fuera de él, el editor se comporta normal.
- **Ctrl+S** con el Tile Map abierto guarda lo pintado. También se guarda con *Save All*.
- Abajo a la izquierda del viewport, una pastilla te recuerda qué herramienta, pincel y capa
  tienes.

### Capas

Cada capa se dibuja en **su propio plano**, separada de las demás en profundidad, como en los
tilemaps de Unreal.

- La lista va de **delante** (arriba) a **detrás** (abajo). Clic en una fila = **capa activa**
  (donde pintas). Doble clic en el nombre = renombrar.
- Botones **+ / − / ↑ / ↓**: añadir, quitar y mover la capa activa hacia delante o hacia atrás.
- La capa marcada como **base** (la primera que no es de fondo) queda en el plano del actor,
  que es donde viven la colisión y los personajes. Las de detrás se alejan y las de delante se
  acercan a la cámara.
- **Layer separation** (cm): distancia entre planos. 0 = todas en el mismo plano.
  También está en el actor, como *Layer Separation*.
- Iconos de cada capa:
  - **Ojo:** visible. Las capas ocultas no se ven en el juego ni colisionan.
  - **Colisiona:** si está apagado, la capa nunca choca. Sirve para decoración delante o
    detrás del personaje.
  - **Se rompe:** si está apagado, picar y explotar no la tocan.
  - **Fondo:** pared trasera. Se ve oscurecida, no colisiona ni se pica. Es lo que hace que una
    cueva parezca una cueva.
- Al **picar** se rompe la capa de más delante que tenga algo en ese píxel (rompes lo que ves).
  **Dig** y las **explosiones** atraviesan todas las capas que se rompen.

### Atlas y propiedades de los tiles

- **Varios atlas:** cada pestaña encima del atlas es una imagen distinta del mismo Tile Set
  (por ejemplo *Principal*, *Cueva*, *Vegetación*). Con **+** añades otra; debajo eliges su
  **Image**, le cambias el **Name** o la quitas (papelera). Todas las imágenes deben tener
  tiles del mismo tamaño que el atlas principal. Los tiles de un atlas nuevo nacen como
  *Decoration*: dale su material a los que sean terreno.
- **Clic** en el atlas = un tile. **Arrastrar** = un bloque, que se estampa entero y se repite
  al arrastrar, con el cubo y con el rectángulo. **− / +** cambian el zoom.
- Debajo, **Selection properties**: el **Material** y la **Collision** de los tiles
  elegidos. Se guardan en el Tile Set, así que valen en todos los mapas que lo usan. Con un
  bloque seleccionado, cambias todos sus tiles de una vez.

### Colisión

Hay dos niveles de control. Cuando ambos dicen algo distinto, **gana lo pintado**:

1. **Por tile** (en el Tile Set, desde *Propiedades de la selección* o en *Tiles → Collision*):
   vale en todos los mapas.
2. **Celda a celda** con el **pincel de colisión** (tecla **C**): elige una forma en la tarjeta
   *Colisión* y pinta. **Automatic** borra lo pintado.

| Forma | Qué choca |
|---|---|
| **Automatic** | Lo de siempre: los píxeles del dibujo cuyo material colisiona. |
| **No collision** | Nada de ese tile. |
| **Drawing pixels** | Todos los píxeles dibujados, aunque el material no colisione (p. ej. *Decoration*). |
| **Full block** | El tile entero, tenga dibujo o no: **pared invisible**. |
| **Mitad de arriba / abajo / izquierda / derecha** | Esa mitad del tile. |
| **Rampa que sube / que baja** | Un triángulo, para rampas lisas. |
| **Thin platform** | Una franja arriba del tile (un cuarto del alto). |

Las formas son **a medida**: no dependen del dibujo. Si el jugador pica un píxel que tenía forma,
ese píxel deja de chocar (lo roto no choca). Las paredes invisibles no se pueden picar.

### Flipbooks (tiles animados)

Los flipbooks viven **aparte** de los tiles del atlas, en su propia tarjeta. Crear uno **no
cambia ningún tile**.

1. En el atlas, **arrastra** sobre los fotogramas (se leen de izquierda a derecha y de arriba
   abajo).
2. En la tarjeta **Flipbooks**, pulsa **New from selection**.
3. Haz **clic en el flipbook** de la lista para pintar con él. Se anima en el editor y en el juego.

En cada flipbook puedes cambiar los **FPS**, renombrarlo con doble clic, **reemplazar sus
fotogramas** con la selección actual o **borrarlo**. Al borrarlo se vacían las celdas del mapa
que lo usaban; Ctrl+Z lo recupera. Su material y su colisión se cambian igual que los de un
tile: con el flipbook elegido, en *Propiedades de la selección*. Para agua, hierba y cosas que no
deben bloquear al jugador, usa el material **Decoration**.

> Si hiciste flipbooks con la v2.0, al abrir el Tile Set se pasan solos a la lista *Flipbooks*
> y el tile del atlas vuelve a ser normal. Las celdas que ya estaban pintadas muestran el tile
> estático: vuelve a pintarlas con el flipbook.

### Generadores de vegetación

Un generador es una "semilla" que pintas en una casilla, en cualquier capa, como si fuera un
tile. Al hornear, reparte por esa casilla sprites de tus atlas: hierba, juncos, setas, rocas...
Lo generado son píxeles de terreno de esa capa: se ve en el editor al momento, siempre sale
igual (tiene semilla) y el jugador lo rompe como lo demás.

1. Selecciona en el atlas los tiles que quieres que salgan (por ejemplo cinco variantes de
   hierba) y pulsa **New from selection** en la tarjeta **Generators**. Cada tile se
   convierte en un sprite.
2. Haz clic en el generador de la lista para pintar con él. Píntalo con el pincel, el
   rectángulo o el cubo en las casillas donde quieras vegetación (justo encima del suelo).
   En el viewport, las casillas generador de la capa activa llevan un rombo.
3. Ajústalo abajo, en **Ajustes de «...»**. Cada cambio se ve en el nivel al soltar el valor:

| Ajuste | Qué hace |
|---|---|
| **Density** | Sprites por casilla (media). 0,5 = uno cada dos casillas. |
| **Variación X / Y** | Cuánto se mueve cada sprite al azar, en píxeles. |
| **Hundir en el suelo** | Desplazamiento fijo hacia abajo; 1–2 px hacen que parezcan plantados. |
| **Escala mínima / máxima** | Tamaño al azar entre las dos (con pixel art, mejor 1). |
| **Tinte A / B** | Cada sprite se tiñe con un color al azar entre los dos. Blanco = sin tinte. |
| **Brightness variation** | Más claro u oscuro al azar. |
| **Rest on the ground** | Cada sprite baja hasta el primer suelo que choca. Si no hay suelo a menos de **Buscar suelo** casillas, no sale. |
| **Random flip** | Voltea en horizontal la mitad de los sprites. |
| **Seed** | Otra semilla = otro reparto con los mismos ajustes (botón de flechas = una nueva). |

- **+ Each tile** añade los tiles seleccionados como sprites sueltos; **+ Bloque como un
  sprite** añade el bloque entero como uno solo (un arbusto de 2×2, un árbol...).
- El **material** de lo generado se elige con el generador como pincel, en *Propiedades del
  generador*. Por defecto es *Decoration* (no choca); pon *Stone* a unas rocas y chocarán.
- Lo generado no pisa los tiles de su capa: para vegetación delante del terreno, usa una capa
  aparte (por ejemplo *Vegetación*, con **Colisiona** apagado).
- Con el **cuentagotas** sobre una casilla generador eliges ese generador.

### Generación procedural de mapas (pestaña «Generate»)
Arriba del panel tienes dos pestañas: **Paint** (lo de siempre) y **Generate**. En *Generar* le
das al plugin las piezas de tu tileset y él construye el nivel entero: alturas, rampas, fosos,
lagos, cascadas, plataformas flotantes, fondo y decoración.

![Nivel generado (bosque)](Docs/capturas_v23/escena_bosque.png)

**1. Un bioma = tus piezas.** Un bioma (se guarda en el Tile Set) dice con qué se construye:

| Pieza | ¿Obligatoria? | Qué es |
|---|---|---|
| Terreno 3×3 | Solo el centro | Esquinas, bordes y centro del suelo. Las que falten usan la más parecida. |
| Esquinas interiores | No | Unen el suelo con la pared de un escalón. |
| Variantes del centro | No | Se mezclan con el centro para que no se repita. |
| Rampas (45°) y rampas suaves | No | Sube / Baja; las suaves son dos tiles por cada tile de altura. |
| Plataformas | No | Izquierda, tramo, derecha. Sin ellas, la fila de arriba del 3×3. |
| Fondo 3×3 | No | Pared trasera y colinas; se ve al picar el terreno. |
| Agua y cascada | No | Suelen ser **flipbooks**: superficie y fondo del agua; arriba, caída y espuma. |
| Decoración | No | Generadores de vegetación, flipbooks (antorchas…) o tiles, con peso y sitio (Suelo/Techo). |

Haz clic en un hueco para abrir el **selector** (atlas, flipbooks y generadores) y elige la
pieza; clic derecho o Supr lo vacía. Para el 3×3, **Choose 3×3 block…** y arrastra un bloque
de 3×3 en el atlas, o selecciónalo en la pestaña Pintar y pulsa **Use the atlas selection**.

**Para probar en un minuto:** añade `Ejemplo/AtlasBioma.png` como página del atlas (el «+» de
las pestañas), déjala activa y pulsa **Create example biome** en la pestaña Generar. Crea los
biomas *Bosque* y *Cueva* con sus flipbooks (agua, cascada, antorcha…) y generadores (hierba,
rocas, arbustos). Mira la distribución del atlas en `Docs/atlas_bioma_ampliado.png`.

**2. La receta = cómo es el nivel** (se guarda en el Tile Map): tamaño del mapa, **alturas**
y alto de cada una, suelo base, anchura de los llanos, salto máximo, **% de rampas** (y de
suaves), fosos, **lagos**, **cascadas**, plataformas, **densidad de decoración**, separación,
variantes, fondo y muros en los bordes, y la **semilla**. Misma receta + misma semilla = mismo
nivel. Cada parte tiene su propio azar: cambiar la decoración no mueve el relieve.

**3. Generar.** **Generate map** rellena las capas *Terreno*, *Fondo*, *Agua* y *Decoración*
(las crea si faltan, con sus interruptores puestos) y **reemplaza su contenido**; las demás
capas no se tocan. **New seed** prueba otro nivel. Con **Regenerate on change** encendido,
cada ajuste vuelve a generar al soltarlo. Todo es **un paso de Ctrl+Z**. Después puedes
retocar el nivel a mano con la pestaña Pintar.

**En juego (niveles distintos en cada partida):** el nodo **Generate Procedural Level** del
terreno genera con la receta del mapa sobre una copia (el asset no cambia); Seed −1 = al azar.
Desde Blueprint también tienes **Generate Map** / **Generate Map With Settings** sobre un Tile Map.

![Panel Generar](Docs/capturas_v23/panel_generar.png)

### Exteriores: lomas, islas, puentes, fondos parallax y objetos grandes (v2.4)

![Exterior generado](Docs/capturas_v24/escena_exterior_cerca_2.png)

**Para verlo en un clic:** en la pestaña *Generar*, botón **Outdoor example**. Importa al
proyecto (`/Game/Framework2D_Ejemplo`) las imágenes de `Ejemplo/` y `Ejemplo/Exterior/`, crea el
bioma **Bosque exterior** y genera el mapa (Ctrl+Z lo deshace).

- **Lomas**: en la receta, el chip **Hills (outdoor)** cambia los escalones por un suelo que sube y
  baja casilla a casilla, con rampas de 45° y suaves donde caben. *Lomas: movimiento* = lo movido.
- **Islas flotantes** con base de roca (receta › *Islas y puentes*): se hacen con tu 3×3 y llevan
  bordes, decoración y lo que cuelga debajo.
- **Bridges** (piezas del bioma: extremo izquierdo, tablas, extremo derecho): cruzan fosos, lagos y
  valles estrechos entre dos orillas a la misma altura; el agua queda debajo.
- **Natural edges** (piezas del bioma, suelen ser generadores): *Arriba* va sobre CADA borde de
  arriba del terreno (una franja de hierba hundida unos píxeles tapa la línea recta de los tiles);
  *Abajo*, bajo islas y salientes (rocas o raíces: en su generador activa **Hang from the ceiling**).
  Van en la capa *Bordes*.
- **Parallax backgrounds** (tarjeta *Paisaje*): imágenes sueltas (cielo, montañas, bosque lejano…), de
  atrás a delante, con *Parallax %* (0 = quieto en la pantalla, 100 = se mueve con el nivel),
  altura, escala, repetir y rellenar abajo/arriba. Se ven en el editor y en el juego; se guardan en
  el Tile Map (*Backdrops*), y el terreno tiene *Show Backdrops* y *Backdrop Distance*.
- **Large objects** (tarjeta *Paisaje*): árboles, rocas, setas gigantes… de cualquier tamaño, en
  PNG suelto. Salen donde hay suelo llano para su **apoyo** (*Footprint Tiles* del objeto en el
  Tile Set; el ancho del tronco va bien), con peso, *Hundir*, volteo y **Detrás/Delante** del
  terreno (capa *Detrás*: ni choca ni se rompe). Cuántos: receta › *Objetos grandes*.
- Para tu arte de pixel art: importa los PNG con *Filter = Nearest* y sin mipmaps (botón derecho ›
  *Sprite Actions › Apply Paper2D Texture Settings*). 1 píxel de la imagen = 1 píxel del terreno.

### Terreno 5×5 y tilesets con bordes de dos tiles (v2.5)

Muchos tilesets dibujan el borde del terreno con **dos tiles de grosor**: la hierba ocupa dos filas
(las hojas de arriba y la base), los lados son de roca, etc. Con un 3×3 siempre se pierde la segunda
fila y la hierba «no casa». Para eso está el **Terrain 5×5** del bioma (pestaña *Generar* › piezas):

| Fila del 5×5 | Se usa en |
|---|---|
| 0 | la casilla de arriba del todo (aire encima) |
| 1 | la segunda (aire a dos casillas por encima) |
| 2 | el interior |
| 3 | la de encima del borde de abajo |
| 4 | la de abajo (aire debajo: islas, salientes) |

Las columnas igual, de izquierda a derecha. **Choose 5×5 block…** rellena las 25 piezas de una vez.
Si el 5×5 tiene centro, manda sobre el 3×3. También hay piezas nuevas: **Waves** (lo que asoma por
encima de la superficie del agua) y **postes del puente**, y los **objetos grandes** pueden ser un
trozo del atlas (para tilesets que traen árboles o rocas dentro).

**Plantilla T_Tiles:** si tu atlas tiene la distribución de *T_Tiles* (25 × 25 tiles de 16 px),
déjala como página activa y pulsa **T_Tiles biomes (5×5)**: crea *Bosque (T_Tiles)* y
*Roca (T_Tiles)* con el terreno 5×5, agua con olas, cascada, puente con postes, tablón, flores,
setas, espadañas, copas de árboles y rocas del propio atlas.

![T_Tiles generado](Docs/capturas_v25/ttiles_lomas_cerca_1.png)

### Todo el tileset, sin cortes (v2.6)

En muchos tilesets (T_Tiles entre ellos) la hierba de la fila de arriba del 5×5 empieza unos
píxeles por debajo del borde del tile. El generador lo tiene en cuenta para que nada quede
cortado en recto ni flote:

- **Pie de pared:** donde un suelo llega a la pared de un escalón, su hierba pasa por delante del
  pie de la pared y se remata con su extremo redondeado (con las piezas de *Pie de pared*, entra en
  la pared y acaba en un matorral). Bajo pilares y bultos estrechos la hierba sigue de corrido.
- **Superficie sin sello repetido:** las dos filas de arriba de un suelo llano alternan las tres
  piezas del medio del 5×5 (casan entre sí), sin repetir la de al lado.
- **Interior profundo:** con el 5×5, lo que va más adentro que sus filas (la franja de rocas bajo
  la hierba) usa esta pieza (por ejemplo, la tierra lisa).
- **Agua, cascadas y puentes a ras de la hierba:** con el 5×5 bajan una fila; la hierba del fondo
  del lago queda delante del agua y detrás de las orillas hay agua (sin rendijas). Los puentes
  llevan su **canto** (borde de las tablas y cuerdas) y sus extremos y postes van sobre las orillas.
  Los lagos no pasan de **Lake: max width** (24 tiles): en un valle más ancho solo se llena lo hondo.
- **Fondo redondeado:** con un 3×3 de fondo de bordes redondeados (el arbusto oscuro de T_Tiles)
  sus colinas salen redondeadas y el fondo es un bosque continuo.
- **Los objetos grandes se apoyan en la hierba de verdad**, sin colgar sobre
  escalones ni lagos; el mismo objeto no se repite pegado.
- **Relieve más natural:** mesetas y valles anchos en vez de almenas.

La plantilla **T_Tiles biomes (5×5)** usa todo esto con las piezas de T_Tiles. Quedan fuera las
ruinas (son trozos de una pared sin bordes propios: sueltas se ven recortadas), las colmenas (traen
pegado un trozo de la rama de la que cuelgan) y los objetos de juego (cofres, pociones, llaves).

![Bosque de T_Tiles (v2.6)](Docs/capturas_v26/ttiles_escalones_cerca_1.png)

### Vista previa del nivel
El terreno se dibuja en el editor tal como saldrá en el juego, con tus sprites. Se actualiza
solo al pintar, al deshacer y al cambiar el Tile Set o el atlas. Si alguna vez no se refresca,
pulsa el botón de **Actualizar vista** (las flechas en círculo) de la tarjeta de herramientas.

---

## 4. Materiales: cómo se rompe cada cosa

Los materiales se definen en el **Tile Set**, en la lista *Materials*. Cada tile elige uno.
Vienen 6 de serie:

| Material | Colisiona | Dureza | Notas |
|---|---|---|---|
| Dirt | sí | 3 | |
| Stone | sí | 8 | |
| Wood | sí | 4 | |
| Sand | sí | 1 | |
| Decoration | **no** | 1 | hierba y plantas: se ven y se rompen, pero no se pisan ni dan material |
| Bedrock | sí | — | **indestructible**: para los bordes del nivel |

Campos de cada material:

| Campo | Para qué sirve |
|---|---|
| **Name** | El nombre que eliges en los tiles y el que usas desde Blueprint. |
| **Color / Color Variance** | Color de los píxeles sin dibujo, es decir, lo colocado cuando el material no tiene *Fill Pattern*. |
| **Collides** | Si el personaje choca con él. |
| **Hardness** | Daño que necesita un píxel para romperse al picar. 0–1 = al primer golpe. |
| **Indestructible** | Nada lo rompe. |
| **Collectable** | Lo picado va al inventario de quien pica. |
| **Draw Edge** | Dibuja el borde oscuro donde toca el aire. |

Puedes añadir los que quieras, por ejemplo `Gold` con dureza 12, y asignarlos a sus tiles.

**Tiles sin material (None):** en una capa normal no ponen terreno. En una capa de **fondo**
se ven igual, así que son ideales para la pared de cueva.

---

## 5. Usarlo en tu juego (Blueprint)

### Personaje base: picar con el clic (`Framework2D Character`)
Un **Paper Character** que deforma el terreno **delante del jugador con el clic izquierdo**, sin
configurar nada. Para usarlo con tu personaje:

1. Abre el Blueprint de tu personaje (el que herede de *Paper Character*).
2. **Class Settings → Parent Class → Framework2D Character**. Compila.
3. Juega y haz clic. Mantener pulsado repite el golpe.

No cambia nada de lo tuyo (movimiento, cámara, sprite, componentes, variables): solo añade el
componente **Terrain Deformer**. Selecciónalo en la lista de componentes para ajustar el golpe en
*Details*. También puedes añadir ese componente a cualquier otro personaje con *Add Component*.

| Ajuste | Qué controla |
|---|---|
| **Use Keys / Keys** | Deforma mientras pulses una de esas teclas (por defecto, clic izquierdo y gatillo derecho). Solo el jugador local que controla al personaje: los enemigos y la IA no pican solos. Con un menú «solo interfaz» abierto (*Set Input Mode UI Only*) o tras *Disable Input* no pica; al volver, hay que pulsar de nuevo. |
| **Repeat While Held / Hits Per Second** | Mantener pulsado repite el golpe, como mucho *Hits Per Second* veces por segundo (4). Un clic durante la espera no se pierde. |
| **Mode** | *Picar*: cada golpe suma *Damage* y cada píxel se rompe al llegar a la dureza de su material (Dirt 3, Stone 8…), con borde irregular y escombros. *Excavar*: círculo exacto al instante. |
| **Radius** | Tamaño del círculo que se rompe (cm). |
| **Damage** | Daño de cada golpe al picar. |
| **Reach** | Hasta dónde llega hacia delante (cm). |
| **Aim At First Solid** | Buscar la pared: golpea el primer terreno sólido delante, dentro del alcance (si no hay ninguno, no hace nada). Desactivado, golpea siempre a *Reach*. |
| **Height Offset / Aim Angle** | Altura desde la que sale el golpe (negativo = hacia los pies) e inclinación (−90 = justo debajo). |
| **Facing Source** | De dónde sale «delante»: el último movimiento (por defecto; vale gires como gires el dibujo), la rotación del actor, la del sprite (girado o con escala X negativa) o el ratón. |
| **Store In Inventory** | Si el personaje lleva la varita (*Framework2D Terraform*), lo roto va a su inventario. |
| **Show Aim** | Dibuja (en desarrollo) el círculo donde caería el golpe: útil para ajustar. |

| Nodo / evento | Para qué |
|---|---|
| **Deform Now** | Un golpe ahora mismo delante (por ejemplo, desde tu animación de ataque). |
| **Deform At** (posición) | Un golpe en cualquier punto, con el modo, radio y daño del componente. |
| **Start Deforming / Stop Deforming** | Para tu propia entrada: desactiva *Use Keys* y llámalos al pulsar y soltar. |
| **Get Aim Point**, **Get Aim Direction**, **Get Facing / Set Facing** | Dónde caería el golpe y hacia dónde mira. |
| Evento **On Terrain Deformed** | En cada golpe que alcanza terreno, aunque la dureza aún no lo rompa (*Cells Hit* cuenta los píxeles dañados o rotos; *Cells Removed*, los rotos): sonido, partículas, animación… |

> Si tu clic izquierdo ya hace otra cosa (por ejemplo, la acción *Attack*), las dos pasan a la vez.
> Para picar con otra tecla, cámbiala en **Keys**; para picar solo desde tu ataque, desactiva
> *Use Keys* y llama a **Deform Now** desde él. El terreno girado (por ejemplo, 180° para verlo
> desde −Y) funciona igual: «delante» se mide en el plano del terreno.
>
> La deformación no se replica en red: cada máquina cambia su copia del terreno (un jugador o
> pantalla partida en el mismo equipo).

### La varita: componente `Framework2D Terraform`
Es la forma más rápida. Añádelo a tu personaje con *Add Component → Framework2D Terraform*.

| Nodo | Cuándo llamarlo |
|---|---|
| **Mine Toward** (Target World, Delta Seconds) | Cada frame con el botón de picar pulsado. Lanza un rayo desde el personaje hacia el objetivo y pica lo **primero** que toca. |
| **Place Toward** (Target World, Delta Seconds) | Cada frame con el botón de colocar pulsado. Gasta inventario. |
| **Select Next Material** (±1) | Cambiar el material que colocas. |
| **Get Amount**, **Get Total Stored**, **Inventory** | Para tu interfaz. Evento **On Inventory Changed**. |

Ajustes de la varita:

| Ajuste | Qué controla |
|---|---|
| **Range** | Alcance. |
| **Mine Radius** | Tamaño de la punta. |
| **Mine Damage Per Second** | Daño por segundo. Con 40 y `Stone` (dureza 8), cada píxel de piedra tarda 0,2 s. |
| **Place Radius / Place Cells Per Second** | Tamaño y ritmo al colocar. |
| **Capacity** | Límite del inventario (0 = sin límite). |
| **Infinite Materials** | Modo creativo: colocar no gasta y puedes elegir cualquier material del Tile Set. |

### Nodos del terreno (`Framework2D Terrain`)

| Nodo | Qué hace |
|---|---|
| **Mine At** (posición, radio, daño, Collector) | Picar con dureza. Devuelve lo roto y lo recogido. |
| **Dig** (posición, radio) | Círculo exacto al instante, sin dureza y sin escombros. Devuelve lo roto y lo recogido. Ideal para scripts. |
| **Explode** (posición, radio, Power) | Explosión: el daño baja con la distancia y los escombros salen en estallido. |
| **Place Material** (posición, radio, material, MaxCells, *Layer*) | Rellena huecos con un material. No coloca encima de personajes. *Layer* (avanzado): capa del Tile Map; −1 = la capa base. |
| **Paint** (posición, radio, material, *Layer*) | Sustituye lo que haya en esa capa (None = borrar). |
| **Trace Terrain** (inicio, fin) | Rayo píxel a píxel: primer píxel de terreno y su material. |
| **Is Solid At World**, **Get Material Name At World** | Consultas puntuales (`None` = aire). El material es el de la capa de más delante. |
| **Get Layer Material Name At World** (posición, capa) | El material de una capa concreta en ese punto. |
| **Count Material In Radius** | Cuántos píxeles de un material hay en un círculo (objetivos de juego). |
| **Reset Terrain** | Vuelve a dejar el nivel como está pintado. |
| **Get Cell Size**, **Get Materials** | Información útil. |
| Evento **On Terrain Mined** | Salta con cada golpe que rompe algo: sonido, vibración de cámara, partículas… |

Ejemplo, un arma que abre agujeros al impactar:
`On Hit → Explode (Impact Point, 80, 255)`.

---

## 6. Ajustes del terreno

En el panel *Details* del actor **Framework2D Terrain**:

| Grupo | Ajuste | Qué hace |
|---|---|---|
| Básico | **Tile Map** | El nivel. |
| | **Tile Size** (64) | Lo que mide un tile en el mundo, en cm. Un píxel mide `Tile Size / ancho del tile`. |
| | **Layer Separation** (10) | Distancia en cm entre los planos de las capas. 0 = todas en el mismo plano. |
| | **Terrain Material** | Por defecto, el de sprites de Paper2D (sin luz y con el aire transparente). |
| Aspecto | **Edge Width / Edge Color / Top Edge Color** | El borde de los cortes. El alfa del color es la fuerza. |
| | **Background Brightness** | Brillo de las capas de fondo. |
| | **Draw Sky / Sky Color** | Pintar el aire de un color en vez de dejarlo transparente. |
| | **Show Damage** | Oscurecer los píxeles que se están picando. |
| Rotura | **Brush Roughness** | Lo irregular del borde de los agujeros. |
| | **Debris Mode / Chance** | Los píxeles que saltan al romper. *Hacia quien pica* = estilo KYORA. |
| Colisión | **Generate Collision / Collision Depth / Collision Profile** | La física del terreno. |

Si usas **tu propio material**, ponle un parámetro de textura llamado `TerrainTexture`. Para
que el aire sea transparente, usa *Blend Mode = Masked* con el alfa de esa textura en *Opacity Mask*.

---

## 7. Consejos para dibujar los tiles

- **Los píxeles transparentes son aire.** La silueta del dibujo es la colisión real: una
  rampa, una esquina redondeada o la hierba de arriba se pisan tal como están dibujadas.
- **El atlas** es una rejilla de tiles del mismo tamaño, sin márgenes ni separación. Los tiles
  se numeran de izquierda a derecha y de arriba abajo.
- **Tamaño de tile:** 16 px es un buen equilibrio. Cada píxel es una celda, y el nivel no puede
  pasar de 16384 píxeles de lado: con tiles de 16 px, eso son 1024 tiles.
- **Marca un tile de relleno** (*Fill Pattern*) por material, sin hierba ni bordes. Así, lo que
  coloca el jugador parece pintado con el tilemap.
- **Bordes del nivel con `Bedrock`**: así el jugador no puede salirse picando.
- **Cuevas:** pinta una capa de fondo con la pared de cueva debajo del terreno. Al picar se verá
  la pared en vez del cielo.

---

## 8. Problemas comunes

**No veo el terreno.** Comprueba en orden:
1. El actor tiene **Tile Map**.
2. El Tile Map tiene **Tile Set**.
3. El Tile Set tiene **Atlas** y sus tiles tienen material.
4. Paper2D está activo (o tienes un *Terrain Material* propio).
5. Miras el plano XZ desde +Y (vista *Right*). Desde *Front* se ve de canto.

El panel del modo Framework2D Tiles te dice qué falta.

**El personaje atraviesa el suelo.** Activa **Show collision** en el panel: lo verde es lo que
choca. Si ese tile no está en verde, mira su material (*Collides*), la colisión del tile
(*Propiedades de la selección*), si la capa tiene **Colisiona** apagado, o si el terreno tiene
*Generate Collision* desactivado.

**Una capa tapa al personaje (o queda detrás).** Las capas de delante se acercan a la cámara.
Mueve la capa con ↑ / ↓, baja la *Separación entre capas* o mueve el personaje en Y.

**Mi flipbook de la v2.0 ya no se anima.** Se ha pasado a la lista *Flipbooks* del Tile Set y
el tile del atlas vuelve a ser normal. Elige el flipbook en la paleta y vuelve a pintar esas
celdas.

**En el juego empaquetado el terreno sale con colores planos.** Abre el Tile Set y guárdalo
(Ctrl+S): al guardar se copia el atlas para el juego empaquetado.

**Los colores salen más claros o lavados que en el PNG.** Es la exposición automática de Unreal.
Pon un *Post Process Volume* con *Infinite Extent* y en *Exposure* fija *Min/Max EV100* = 0,
o desactiva *Auto Exposure* en *Project Settings → Rendering*. Es lo habitual en juegos 2D.

**La paleta se ve borrosa.** Pon el *Filter* de la textura del atlas en *Nearest* (o usa
*Apply Paper2D Texture Settings*).

**"El plugin está hecho para otra versión" / "¿recompilar módulos?".** Es normal: el plugin se
entrega como código. Pulsa **Sí**. Si falla, necesitas Visual Studio con "Game development with
C++". Pásame el error exacto del Output Log.

---

## 9. Límites y siguientes pasos

- **Una textura por capa** (máx. 16384×16384 píxeles). Para mundos más grandes, usa
  varios actores de terreno o divide el render en varias texturas (pendiente).
- **Sin red ni guardado** del terreno roto todavía. La rotura ya es reproducible (el ruido de
  cada golpe sale de la posición), que es la base para replicarla como KYORA: enviar solo
  "golpe en (x, y)" y que cada cliente lo aplique.
- **Lo que queda flotando no cae** (como en Terraria o KYORA, no como en Noita).
- **Rotura procedural al empezar la partida** (erosión, cuevas por ruido): idea para la
  siguiente fase.

---

## 10. Cambios de versión

### v2.7
- **Personaje base `Framework2D Character`** (Paper Character): ponlo como padre de tu personaje y el
  clic izquierdo deforma el terreno delante de él. Sus ajustes, en el componente **Terrain Deformer**
  (también se puede añadir suelto a cualquier personaje).
- **Dig** devuelve lo roto y lo recogido, como *Mine At*; el resultado de un golpe trae también
  **Cells Hit** (píxeles dañados o rotos).
- Fuera la tarjeta **Bloques y árboles** de la pestaña Generar y lo que hacía en el generador
  (bloques de superficie e interior, árboles gigantes y copas del fondo), con sus ajustes de la
  receta. Los biomas que los tuvieran los pierden al abrirse; lo demás no cambia.

### v2.6
- Sin cortes bruscos con tilesets de bordes de dos tiles: pie de pared, interior profundo, agua,
  cascadas y puentes a ras de la hierba, canto de plataformas y puentes, islas y plataformas 5×5
  sin la hierba cortada.
- Bloques de superficie e interior, árboles gigantes con copa variada, copas del fondo, objetos
  apoyados en el suelo y fondo 3×3 redondeado. Tarjeta **Bloques y árboles** en la pestaña Generar.
- Lagos con ancho máximo, relieve con inercia y mesetas, fosos con margen, puentes espaciados.
- Superficie con las piezas del medio del 5×5 alternadas; árboles vecinos siempre distintos.
- Rendimiento igual o mejor que la v2.4.1 (800×200 tiles: generar ~15 ms, regenerar ~0,7 s).

### v2.5
- **Terrain 5×5** en los biomas (bordes de dos tiles de grosor), con selector de bloque 5×5.
- Piezas nuevas: **olas** sobre el agua y **postes del puente**. Objetos grandes recortados **del atlas**.
- Plantilla **T_Tiles biomes (5×5)**.

### v2.4.1 (rendimiento con mapas grandes)
- La mitad de memoria por capa: el color final ya no se guarda (se calcula al subir cada trozo) y el daño solo existe en juego.
- Regenerar reutiliza la memoria de la vez anterior; hornear, calcular colores y la colisión van en paralelo (todos los núcleos).
- Los flipbooks (agua, cascadas...) solo repintan su tile en su capa al cambiar de fotograma: sin tirones con lagos grandes.
- La colisión solo crea componentes donde hay algo que choca (el cielo no cuesta nada).
- Medido con un mapa de 800×200 tiles: regenerar 6,4 s → 0,8 s; peor frame con flipbooks 27 ms → 0,5 ms.

### v2.4
- **Exteriores**: relieve en **lomas**, **islas flotantes** con base de roca, **puentes**, **bordes naturales** (remates de hierba y rocas colgantes), **fondos parallax** con imágenes sueltas y **objetos grandes** (árboles, rocas…) delante o detrás del terreno.
- Generadores con **Hang from the ceiling**.
- Botón **Outdoor example** (importa el arte de ejemplo y genera un bosque exterior) y arte nuevo en `Ejemplo/Exterior/`.

### v2.3
- **Generación procedural de mapas** (pestaña *Generar*): biomas con terreno 3×3, esquinas interiores, variantes, rampas de 45° y suaves, plataformas, fondo, agua, cascadas y decoración; receta con alturas, rampas, fosos, lagos, cascadas, plataformas, densidad de decoración y semilla. Un paso de deshacer.
- Atlas de ejemplo `Ejemplo/AtlasBioma.png` (bosque y cueva) y botón **Create example biome**.
- Blueprint: **Generate Procedural Level** (en juego, nivel nuevo cada partida), **Generate Map** y **Resize** del Tile Map.

### v2.2
- **Varios atlas** por Tile Set, con pestañas en la paleta. Los mapas de antes siguen igual (son la página 0).
- **Generadores de vegetación** con densidad, variación de posición, escala, tinte, brillo, volteo, apoyo en el suelo y semilla.
- Las miniaturas del panel salen con su fondo a cuadros (antes, en blanco).

### v2.1
- **Capas en planos separados** (*Layer Separation*), con interruptores **Colisiona** y **Se rompe** por capa, renombrar y reordenar.
- **Preview** semitransparente de lo que vas a pintar.
- **Colisión por tile** y **pincel de colisión** con formas a medida (bloque, mitades, rampas, plataforma, sin colisión, píxeles del dibujo).
- **Flipbooks en su propia lista**: ya no pisan el tile del atlas. Los de la v2.0 se migran solos.
- **Selection properties** (material y colisión) desde el panel, para uno o muchos tiles a la vez.
- **Panel rediseñado:** iconos, tarjetas, contraste alto y ayuda en cada botón.
- **Orientación corregida:** el terreno se mira desde +Y (vista *Right*). La cámara del personaje de demo estaba en el lado contrario y veía el nivel en espejo, con A/D invertidos.
- *Place Material* y *Paint* aceptan la capa; nuevo nodo *Get Layer Material Name At World*.

### v2.0 (respecto a la v1)

La v2 se centra en el tilemap destructible y quita todo lo demás:

- **Eliminado:** la simulación de arena y líquidos, las reacciones, el mundo de demo, la autoría
  por PNG, la ruta de tilemaps de Paper2D y los botones provisionales del Tile Map.
- **Los materiales pasan al Tile Set.** Ya no hace falta tocar el actor para definirlos.
- **Propiedades del actor renombradas:** *Source Framework2D Tile Map* → **Tile Map** y
  *Terrain Material Template* → **Terrain Material**. En niveles de la v1, vuelve a asignarlas.
- **Ya no hace falta crear un material**: viene uno por defecto.
- **El tamaño se fija con Tile Size** (cm por tile). *Cell Size* y *Cells Per Tile* desaparecen:
  ahora siempre es un píxel del tile por celda.
- **Get Material Name At World** devuelve **None** en el aire (antes `Empty`).
- **Dig** vuelve a ser un círculo exacto y silencioso. Para picar con dureza, usa **Mine At** o la varita.
