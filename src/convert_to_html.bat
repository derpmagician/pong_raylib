@echo off
if "%1"=="" (
    echo Usage: %0 ^<output_name^>
    exit /b 1
)
setlocal enabledelayedexpansion
set "files="
for %%f in (*.cpp) do set "files=!files! %%f"
for %%f in (effects\*.cpp) do set "files=!files! %%f"
emcc -o %1.html %files% -Wall -std=c++14 -D_DEFAULT_SOURCE -Wno-missing-braces -Wunused-result -Os -I. -I ../include -I C:/raylib/raylib/src -I C:/raylib/raylib/src/external -L. -L C:/raylib/raylib/src -s USE_GLFW=3 -s ASYNCIFY -s TOTAL_MEMORY=67108864 -s FORCE_FILESYSTEM=1 --preload-file ../resources --shell-file C:/raylib/raylib/src/shell.html C:/raylib/raylib/src/web/libraylib.a -DPLATFORM_WEB -s "EXPORTED_FUNCTIONS=[\"_free\",\"_malloc\",\"_main\"]" -s "EXPORTED_RUNTIME_METHODS=[\"cwrap\",\"ccall\",\"HEAPF32\"]"