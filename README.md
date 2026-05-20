# Parcial Final - Dungeon Crawler

## Integrante
- Alessandro De Bonis

## Nota sobre el historial de commits
Profesor tuve un inconveniente, utilice --force, por que estaba teniendo un problema subiendo mis commits hoy en la mañana, por usarlo sin antes investigar bien no sabia que esto sobreescribiria el historial previo de mis commits. (MVP inicial, sistema de habitaciones, enemigos, inventario, integracion de raylib). Los commits actuales reflejan el estado final del proyecto pero no la totalidad del proceso de desarrollo que se llevo a cabo de forma incremental.

## Instrucciones de compilacion

---

### macOS

**Requisitos:** Xcode Command Line Tools y CMake

**Paso 1:** Instalar Xcode Command Line Tools (si no lo tienes)
```
xcode-select --install
```

**Paso 2:** Instalar CMake con Homebrew (si no lo tienes)
```
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
brew install cmake
```

**Paso 3:** Compilar y ejecutar
```
git clone https://github.com/alessdebonis/dungeon.git
cd dungeon
mkdir build
cd build
cmake ..
make
./dungeon
```

---

### Linux (Ubuntu/Debian)

**Paso 1:** Instalar CMake, compilador y librerias necesarias
```
sudo apt update
sudo apt install cmake g++ git libgl1-mesa-dev libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev
```

**Paso 2:** Compilar y ejecutar
```
git clone https://github.com/alessdebonis/dungeon.git
cd dungeon
mkdir build
cd build
cmake ..
make
./dungeon
```

---

### Windows

**Paso 1:** Instalar Git

1. Ir a https://git-scm.com/download/win
2. Descargar el instalador y ejecutarlo
3. Dejar todas las opciones por defecto y darle "Next" hasta terminar
4. Verificar abriendo PowerShell y escribiendo:
```
git --version
```

**Paso 2:** Instalar CMake

1. Ir a https://cmake.org/download/
2. Descargar el archivo "Windows x64 Installer" (.msi)
3. Ejecutar el instalador
4. IMPORTANTE: En la pantalla de opciones, seleccionar "Add CMake to the system PATH for all users"
5. Terminar la instalacion
6. Cerrar y abrir PowerShell, verificar con:
```
cmake --version
```

**Paso 3:** Instalar MinGW (compilador de C++)

1. Ir a https://github.com/niXman/mingw-builds-binaries/releases
2. Descargar el archivo que diga: `x86_64-XX.X.X-release-posix-seh-ucrt-rt_vXX-revX.7z` (la version mas reciente)
3. Extraer el contenido en `C:\mingw64`
4. Agregar MinGW al PATH del sistema:
   - Buscar "Variables de entorno" en el menu de inicio
   - Click en "Variables de entorno"
   - En "Variables del sistema" buscar "Path" y darle "Editar"
   - Click en "Nuevo" y agregar: `C:\mingw64\bin`
   - Darle "Aceptar" a todo
5. Cerrar y abrir PowerShell, verificar con:
```
g++ --version
```

**Paso 4:** Compilar y ejecutar

```
git clone https://github.com/alessdebonis/dungeon.git
cd dungeon
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
cmake --build .
.\dungeon.exe
```

**Nota:** Si el comando `cmake .. -G "MinGW Makefiles"` da error, probar con:
```
cmake .. -G "MinGW Makefiles" -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++
```

**Alternativa para Windows:** Si tienes Visual Studio instalado, puedes usar:
```
cmake ..
cmake --build . --config Release
.\Release\dungeon.exe
```


## Innovaciones implementadas
1. Motor grafico con raylib para ventana grafica en vez de terminal
2. 4 tipos de enemigos con diferentes velocidades y comportamientos, para que el juego sea mas dinamico
3. Sistema de 3 objetos coleccionables con colores diferenciados, para que haya sentido de victoria
4. Barra de informacion con vidas, habitacion, inventario y progreso, para que el jugador sepa el status del juego
5. Pantalla de inicio con instrucciones
6. Pantalla de Game Over y Victoria con opcion de reinicio
7. Paredes internas con diseño unico por habitacion
8. Sistema de respawn al recibir daño, inicias en la sala 0.
9. Efectos de sonido para movimiento, recoleccion y daño causado por los enemigos

## Uso de herramientas
Se utilizo un LLM (Claude) como herramienta de apoyo para los aspectos esteticos del proyecto: integracion de la libreria grafica raylib, configuracion de colores, diseno de las pantallas de inicio y game over, y generacion de efectos de sonido. 

## Innovaciones detalladas

### 1. Motor grafico con raylib
- **Para que:** Para dar al juego una presentacion visual tipo videojuego real en vez de algo blanco y negro en terminal.
- **Por que:** Busque ejemplos de juegos parecidos de la epoca. Usar una ventana grafica mejora la experiencia del jugador.
- **Como:** Se uso la libreria raylib mediante FetchContent de CMake. Se reemplazo std::cout por funciones de raylib como DrawRectangle y DrawText. Cada muñeco se hizo como un cuadrado con ojos y detalles

### 2. Cuatro tipos de enemigos
- **Para que:** Para dar variedad al juego y diferentes niveles de dificultad por habitacion.
- **Por que:** Un solo tipo de enemigo me parecia muy aburrido, quise que el juego fuera un poco mas dinamico.
- **Como:** Se agrego un campo type al struct Enemy. En moveEnemies se usa el type para decidir cada cuantos turnos se mueve (type 0 cada 3, type 1 cada 2, type 2 cada 1) y si se mueve en diagonal (type 3 mueve en x y y al mismo turno).

### 3. Tres objetos coleccionables con colores
- **Para que:** Para que el jugador tenga un objetivo para finalizar el juego y no fuera algo tan facil como recoger solo una llave.
- **Por que:** Tener 3 objetos obliga al jugador a pensar rutas y arriesgarse contra los enemigos.
- **Como:** Se crearon 3 items en el arreglo estatico items[] con simbolos K, G, C. Cada uno tiene un color diferente en drawRoom: dorado, azul, morado. La victoria se calcula contando cuantos objetos estan en la habitacion 5.

### 4. Mecanica de multiples viajes
- **Para que:** Para que el juego no sea simplemente ir de A a B, sino que requiera estrategia.
- **Por que:** Como el inventario es de un solo espacio, el jugador debe hacer 3 viajes separados. Esto aumenta el riesgo y la rejugabilidad.
- **Como:** La funcion handleItem permite recoger y soltar objetos. Al soltar, el item se reactiva en la posicion del jugador. checkVictory cuenta los items en la habitacion 5 y si son 3, el jugador gana.

### 5. Barra de informacion
- **Para que:** Para que el jugador vea su status del juego,
- **Por que:** Me parece un requisito minimo de todo video juego.
- **Como:** Se dibujan rectangulos y texto con raylib en la parte inferior de la ventana. Se muestra vida como cuadrados rojos, nombre de habitacion, slot de inventario con color del objeto, y contador de objetos entregados.

### 6. Pantalla de inicio
- **Para que:** Para que el jugador sepa que hacer antes de empezar
- **Por que:** Sin instrucciones, el jugador no sabria como jugar.
- **Como:** La funcion showIntro dibuja texto con DrawText explicando objetivo, controles, tipos de enemigos y objetos. El jugador debe presionar enter para jugar.

### 7. Pantalla de Game Over y Victoria con reinicio
- **Para que:** Para dar cierre al juego y permitir reiniciar el juegos
- **Por que:** Sin estas pantallas el juego terminaria y el jugador debia hacer todo el proceso para poder jugar otra vez. 
- **Como:** Al terminar el bucle principal, se muestra un mensaje segun si gano o perdio. Si el jugador presiona R, se llama initGame para reiniciar todo y se vuelve a llamar gameLoop.

### 8. Paredes internas unicas
- **Para que:** Para que cada habitacion se sienta diferente.
- **Por que:** Habitaciones vacias son aburridas. Las paredes internas obligan al jugador a buscar caminos y formas de sobrevivir a los enemigos.
- **Como:** En initRooms, despues de crear los bordes, se agregan paredes dentro del mapa usando ciclos for que ponen '#' en ubicaciones exactas dentro del mapa. Cada habitacion tiene paredes diferentes.

### 9. Efectos de sonido
- **Para que:** Para que el jugador conecte mejor con el juego.
- **Por que:** Los sonidos hacen que el juego se sienta mas completo y el jugador sepa cuando algo paso
- **Como:** Se generan sonidos con ondas cuadradas usando arreglos de short. La funcion crearSonido recibe frecuencia y duracion, llena un arreglo con valores alternados y crea un Sound de raylib con LoadSoundFromWave.
un short es como un int, pero mas pequeño, es primera vez que lo uso, se usa para audios.
