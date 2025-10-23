#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <raylib.h>
#include <ball.h>
#include <paddle.h>
#include <settings.h>
#include <effects/particle.h>
#include <effects/screen_shake.h>
#include <effects/flash.h>
#include <effects/glow.h>
#include <effects/distortion_wave.h>

// Estados del juego
enum GameState {
    MENU,
    SETTINGS,
    PLAYING,
    PAUSED,
    GAME_OVER
};

// Estructura de datos del juego
typedef struct {
    GameState currentState;
    int playerScore;
    int cpuScore;
    double startTime;
    double pausedTime;
    double pauseStartTime;
    double lastSpeedIncreaseTime;
    bool waitingForEffectsToFinish;  // Bandera para esperar que terminen los efectos antes de game over
    Ball ball;
    Paddle player;
    CpuPaddle cpu;
    GameSettings settings;
    Sound wallHitSound;
    Sound paddleHitSound;
    Sound explosionSound;
    ParticleSystem particleSystem;
    ScreenShake screenShake;
    FlashEffect flash;
    GlowEffect glow;
    DistortionWave distortionWave;
} Game;

// Constantes del juego
extern const int screenWidth;
extern const int screenHeight;
extern const double speedIncreaseInterval;

// Colores
extern Color Purple;
extern Color DarkGreen;
extern Color LightGreen;
extern Color Yellow;
extern Color OverlayColor;

// Inicializar datos del juego
void InitGame(Game* game, int paddleHeight, int paddleWidth);

// Reiniciar juego para una nueva partida
void ResetGame(Game* game);

// Cargar sonidos del juego desde arrays embebidos
void LoadGameSounds(Game* game);

// Descargar sonidos del juego
void UnloadGameSounds(Game* game);

#endif
