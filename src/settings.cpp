#include <settings.h>
#include <stdio.h>
#include <stdlib.h>

// Valores por defecto
const int DEFAULT_POINTS_TO_WIN = 5;
const int DEFAULT_MAX_BALL_SPEED = 20;
const char* SETTINGS_FILE_PATH = "settings.txt";

void InitSettings(GameSettings* settings) {
    // Intentar cargar configuración desde el archivo
    LoadSettings(settings);
}

void LoadSettings(GameSettings* settings) {
    FILE* file = fopen(SETTINGS_FILE_PATH, "r");
    
    if (file == NULL) {
        // Si no existe el archivo, usar valores por defecto
        ResetToDefaults(settings);
        SaveSettings(settings);  // Crear el archivo con valores por defecto
        return;
    }
    
    // Leer configuración del archivo
    int pointsRead = 0, speedRead = 0;
    int result = fscanf(file, "pointsToWin=%d\nmaxBallSpeed=%d", &pointsRead, &speedRead);
    
    if (result == 2) {
        // Validar los valores leídos
        settings->pointsToWin = (pointsRead >= 1 && pointsRead <= 20) ? pointsRead : DEFAULT_POINTS_TO_WIN;
        settings->maxBallSpeed = (speedRead >= 11 && speedRead <= 50) ? speedRead : DEFAULT_MAX_BALL_SPEED;
    } else {
        // Si hay error al leer, usar valores por defecto
        ResetToDefaults(settings);
    }
    
    fclose(file);
}

void SaveSettings(const GameSettings* settings) {
    FILE* file = fopen(SETTINGS_FILE_PATH, "w");
    
    if (file == NULL) {
        // Error al abrir el archivo
        return;
    }
    
    // Guardar configuración en el archivo
    fprintf(file, "pointsToWin=%d\n", settings->pointsToWin);
    fprintf(file, "maxBallSpeed=%d\n", settings->maxBallSpeed);
    
    fclose(file);
}

void ResetToDefaults(GameSettings* settings) {
    settings->pointsToWin = DEFAULT_POINTS_TO_WIN;
    settings->maxBallSpeed = DEFAULT_MAX_BALL_SPEED;
}
