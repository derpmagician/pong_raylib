#ifndef SETTINGS_H
#define SETTINGS_H

// Estructura para guardar la configuración del juego
typedef struct {
    int pointsToWin;      // Puntos necesarios para ganar
    int maxBallSpeed;     // Velocidad máxima de la pelota
} GameSettings;

// Valores por defecto
extern const int DEFAULT_POINTS_TO_WIN;
extern const int DEFAULT_MAX_BALL_SPEED;
extern const char* SETTINGS_FILE_PATH;

// Funciones para manejar la configuración
void InitSettings(GameSettings* settings);
void LoadSettings(GameSettings* settings);
void SaveSettings(const GameSettings* settings);
void ResetToDefaults(GameSettings* settings);

#endif
