# Pong (raylib) - código fuente

Este directorio contiene la versión fuente del juego Pong compilada con raylib.

Descripción
- Proyecto de ejemplo que usa raylib para crear un pequeño juego tipo Pong en C/C++.
- El código fuente principal está en este directorio (`*.cpp`, `*.h`) y en `effects/`.

Archivos y carpetas importantes
- `*.cpp`, `*.h` — Código fuente del juego.
- `effects/` — Efectos visuales y otros módulos.
- `resources/` — Recursos (gráficos, sonidos) utilizados por el juego.
- `convert_to_html.bat` — Script para compilar con emscripten y generar una versión Web (HTML + JS + Wasm).
- `fullscreenfix.bat`, `build-MinGW-W64.bat`, `build-VisualStudio2022.bat`, `update_makefile.bat` — Scripts de utilidad para construir y arreglar el proyecto en Windows.

Uso de los `.bat`
- `convert_to_html.bat <output_name>`: compila los `*.cpp` con `emcc` y genera `<output_name>.html`, `<output_name>.js` y `<output_name>.data`. Recomendado usarlo en una consola donde `emcc` esté en el PATH.
  - Ejemplo (PowerShell):
    ```powershell
    cd src
    .\convert_to_html.bat pong
    ```
  - Para depuración y obtener salida JS más legible (preservar espacios y generar source maps), se puede exportar la variable `EMCC_DEBUG_FLAG` antes de la invocación. Por ejemplo:
    ```powershell
    $env:EMCC_DEBUG_FLAG = '-gsource-map -g1 --minify 0 --closure 0'
    .\convert_to_html.bat pong
    ```
  - Nota: Generar source maps y salida no minificada es útil en desarrollo, pero aumenta el tamaño de los archivos y puede exponer el código fuente en producción.

- `build-MinGW-W64.bat`, `build-VisualStudio2022.bat`: ayudas para generar archivos de build usando las herramientas indicadas.
- `fullscreenfix.bat`: script de ayuda para ajustar detalles del HTML/JS tras la compilación web (usar si detectas problemas de pantalla completa en el navegador).

Recomendaciones
- Para desarrollo local con emscripten: generar con source maps y sin minificación. Para distribución: compilar con optimizaciones de tamaño (`-Os`) y sin source maps.
- Sirve los archivos resultantes por HTTP (por ejemplo con `python -m http.server`) para que los source maps y la carga de recursos funcionen correctamente.

Agradecimientos
Este proyecto es una copia de: https://github.com/educ8s/Cpp-Pong-Game-Raylib — con varias mejoras y/o cambios que hice para aprender c++ y raylib, gracias por el ejemplo y la inspiración.
