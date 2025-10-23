#include <game_state.h>
#include "../resources/sounds/wallhit.h"
#include "../resources/sounds/paddlehit.h"
#include "../resources/sounds/explosion.h"

// Colores
Color Purple = { 128, 0, 128, 255 };
Color DarkGreen = { 20, 160, 133, 255 };
Color LightGreen = { 129, 204, 184, 255 };
Color Yellow = { 243, 213, 91, 255 };
Color OverlayColor = { 0, 0, 0, 128 };

// Constantes
const int screenWidth = 1280;
const int screenHeight = 800;
const double speedIncreaseInterval = 3.0;

void InitGame(Game* game, int paddleHeight, int paddleWidth) {
    game->currentState = MENU;
    game->playerScore = 0;
    game->cpuScore = 0;
    game->startTime = GetTime();
    game->pausedTime = 0.0;
    game->pauseStartTime = 0.0;
    game->lastSpeedIncreaseTime = GetTime();
    game->waitingForEffectsToFinish = false;
    
    // Inicializar configuración
    InitSettings(&game->settings);
    
    // Inicializar sistema de partículas (aumentado para cola más larga)
    game->particleSystem = ParticleSystem(400);  // Antes era 200
    
    // Inicializar bola
    game->ball.radius = 15;
    game->ball.x = screenWidth / 2;
    game->ball.y = screenHeight / 2;
    
    // Calcular velocidad inicial como 70% de la velocidad máxima
    // Distribuida equitativamente entre X e Y
    float initialSpeed = game->settings.maxBallSpeed * 0.7f;
    float componentSpeed = initialSpeed / 1.414f; // dividir por √2 para distribuir entre X e Y
    
    game->ball.speedX = componentSpeed;
    game->ball.speedY = componentSpeed;
    game->ball.color = Yellow;
    game->ball.particleSystem = &game->particleSystem;
    game->ball.screenShake = &game->screenShake;
    game->ball.flash = &game->flash;
    game->ball.glow = &game->glow;
    game->ball.distortionWave = &game->distortionWave;
    
    // Incializar paddle del jugador
    game->player.x = 10;
    game->player.y = screenHeight / 2 - paddleHeight / 2;
    game->player.width = paddleWidth;
    game->player.height = paddleHeight;
    game->player.speedY = 6;
    game->player.color = LightGreen;
    game->player.useTexture = false;
    game->player.flipHorizontal = false;
    
    // Inicializar paddle de la CPU
    game->cpu.x = screenWidth - 35;
    game->cpu.y = screenHeight / 2 - paddleHeight / 2;
    game->cpu.width = paddleWidth;
    game->cpu.height = paddleHeight;
    game->cpu.speedY = 6;
    game->cpu.color = LightGreen;
    game->cpu.useTexture = false;
    game->cpu.flipHorizontal = false;
}

void ResetGame(Game* game) {
    game->playerScore = 0;
    game->cpuScore = 0;
    game->startTime = GetTime();
    game->pausedTime = 0.0;
    game->lastSpeedIncreaseTime = GetTime();
    game->waitingForEffectsToFinish = false;
    
    // Limpiar partículas
    game->particleSystem.Clear();
    
    game->ball.x = screenWidth / 2;
    game->ball.y = screenHeight / 2;
    
    // Calcular velocidad inicial como 70% de la velocidad máxima
    // Distribuida equitativamente entre X e Y
    float initialSpeed = game->settings.maxBallSpeed * 0.7f;
    float componentSpeed = initialSpeed / 1.414f; // dividir por √2 para distribuir entre X e Y
    
    game->ball.speedX = componentSpeed;
    game->ball.speedY = componentSpeed;
    
    game->player.y = screenHeight / 2 - 60;
    game->cpu.y = screenHeight / 2 - 60;
}

void LoadGameSounds(Game* game) {
    // Cargar sonido de colisión con la pared desde el array de bytes embebido
    Wave wallCollisionWave;
    wallCollisionWave.frameCount = WALLHIT_FRAME_COUNT;
    wallCollisionWave.sampleRate = WALLHIT_SAMPLE_RATE;
    wallCollisionWave.sampleSize = WALLHIT_SAMPLE_SIZE;
    wallCollisionWave.channels = WALLHIT_CHANNELS;
    wallCollisionWave.data = WALLHIT_DATA;
    game->wallHitSound = LoadSoundFromWave(wallCollisionWave);
    
    // Cargar sonido de colisión con la paleta desde el array de bytes embebido
    Wave paddleCollisionWave;
    paddleCollisionWave.frameCount = PADDLEHIT_FRAME_COUNT;
    paddleCollisionWave.sampleRate = PADDLEHIT_SAMPLE_RATE;
    paddleCollisionWave.sampleSize = PADDLEHIT_SAMPLE_SIZE;
    paddleCollisionWave.channels = PADDLEHIT_CHANNELS;
    paddleCollisionWave.data = PADDLEHIT_DATA;
    game->paddleHitSound = LoadSoundFromWave(paddleCollisionWave);
    
    // Cargar sonido de explosión desde el array de bytes embebido
    Wave explosionWave;
    explosionWave.frameCount = EXPLOSSION_FRAME_COUNT;
    explosionWave.sampleRate = EXPLOSSION_SAMPLE_RATE;
    explosionWave.sampleSize = EXPLOSSION_SAMPLE_SIZE;
    explosionWave.channels = EXPLOSSION_CHANNELS;
    explosionWave.data = EXPLOSION_DATA;
    game->explosionSound = LoadSoundFromWave(explosionWave);
}

void UnloadGameSounds(Game* game) {
    UnloadSound(game->wallHitSound);
    UnloadSound(game->paddleHitSound);
    UnloadSound(game->explosionSound);
}
