#include <gameplay.h>
#include <cmath>
#include <rlgl.h>  // Para rlPushMatrix, rlTranslatef, rlPopMatrix

// Función auxiliar para verificar si todos los efectos han terminado
bool AreAllEffectsFinished(Game* game) {
    // Verificar efectos visuales
    bool visualEffectsFinished = !game->flash.IsActive() && 
                                  !game->screenShake.IsActive() && 
                                  !game->distortionWave.IsActive() &&
                                  game->particleSystem.GetParticleCount() == 0;
    
    // Verificar si los sonidos han terminado de reproducirse
    bool soundsFinished = !IsSoundPlaying(game->wallHitSound) && 
                          !IsSoundPlaying(game->paddleHitSound) && 
                          !IsSoundPlaying(game->explosionSound);
    
    return visualEffectsFinished && soundsFinished;
}

void UpdatePlaying(Game* game) {
    // Verificar si se presiona P para pausar el juego
    if (IsKeyPressed(KEY_P)) {
        game->currentState = PAUSED;
        game->pauseStartTime = GetTime();
    }
    
    // Actualizar sistema de partículas
    game->particleSystem.Update(GetFrameTime());
    
    // Actualizar screen shake
    game->screenShake.Update(GetFrameTime());
    
    // Actualizar flash
    game->flash.Update(GetFrameTime());
    
    // Actualizar distortion wave
    game->distortionWave.Update(GetFrameTime());
    
    // Si no estamos esperando que terminen los efectos, actualizar el juego normalmente
    if (!game->waitingForEffectsToFinish) {
        // Actualizar la bola y los paddles
        game->ball.Update(game->playerScore, game->cpuScore, game->wallHitSound, game->explosionSound);
        game->player.Update();
        game->cpu.Update(game->ball.y);

        double currentTime = GetTime();
        // Ajustar el tiempo considerando las pausas
        if (currentTime - game->lastSpeedIncreaseTime - game->pausedTime >= speedIncreaseInterval) {
            int maxSpeed = game->settings.maxBallSpeed;
            
            // Aumentar velocidad en 0.1 respetando la dirección
            float speedIncrement = 0.1f;
            
            // Aumentar cada componente
            if (game->ball.speedX > 0) {
                game->ball.speedX += speedIncrement;
            } else {
                game->ball.speedX -= speedIncrement;
            }
            
            if (game->ball.speedY > 0) {
                game->ball.speedY += speedIncrement;
            } else {
                game->ball.speedY -= speedIncrement;
            }
            
            // Calcular la velocidad total (magnitud del vector)
            float totalSpeed = sqrt(game->ball.speedX * game->ball.speedX + game->ball.speedY * game->ball.speedY);
            
            // Si la velocidad total excede el máximo, escalar los componentes
            if (totalSpeed > maxSpeed) {
                float scale = maxSpeed / totalSpeed;
                game->ball.speedX *= scale;
                game->ball.speedY *= scale;
            }
            
            game->lastSpeedIncreaseTime = currentTime;
        }

        // Verificar colisiones entre la bola y los paddles
        if (CheckCollisionCircleRec(Vector2{ game->ball.x, game->ball.y }, game->ball.radius, 
                                    Rectangle{ game->player.x, game->player.y, game->player.width, game->player.height })) {
            game->ball.speedX = -game->ball.speedX;
            game->ball.x = game->player.x + game->player.width + game->ball.radius;
            
            // Reproducir sonido con pitch aleatorio
            float randomPitch = 0.7f + (GetRandomValue(0, 60) / 100.0f);
            SetSoundPitch(game->paddleHitSound, randomPitch);
            PlaySound(game->paddleHitSound);
        }

        if (CheckCollisionCircleRec(Vector2{ game->ball.x, game->ball.y }, game->ball.radius, 
                                    Rectangle{ game->cpu.x, game->cpu.y, game->cpu.width, game->cpu.height })) {
            game->ball.speedX = -game->ball.speedX;
            game->ball.x = game->cpu.x - game->ball.radius;
            
            // Reproducir sonido con pitch aleatorio
            float randomPitch = 0.7f + (GetRandomValue(0, 60) / 100.0f);
            SetSoundPitch(game->paddleHitSound, randomPitch);
            PlaySound(game->paddleHitSound);
        }

        // Verificar condición de fin de juego
        int pointsToWin = game->settings.pointsToWin;
        if (game->playerScore >= pointsToWin || game->cpuScore >= pointsToWin) {
            // Marcar que estamos esperando que terminen los efectos
            game->waitingForEffectsToFinish = true;
        }
    }
    
    // Si estamos esperando que terminen los efectos, verificar si ya terminaron
    if (game->waitingForEffectsToFinish) {
        if (AreAllEffectsFinished(game)) {
            // Todos los efectos han terminado, cambiar a game over
            game->currentState = GAME_OVER;
            game->waitingForEffectsToFinish = false;
        }
        // Si no han terminado, continuar actualizando los efectos (ya se hace arriba)
    }
}

void DrawPlaying(Game* game) {
    ClearBackground(DarkGreen);
    
    // Obtener offset del screen shake
    Vector2 shakeOffset = game->screenShake.GetOffset();
    
    // Aplicar offset a todos los elementos dibujados
    rlPushMatrix();
    rlTranslatef(shakeOffset.x, shakeOffset.y, 0);
    
    // Draw scores with target score
    int pointsToWin = game->settings.pointsToWin;
    DrawText(TextFormat("%d / %d", game->playerScore, pointsToWin), screenWidth / 4 - 20, 20, 80, RAYWHITE);
    DrawText(TextFormat("%d / %d", game->cpuScore, pointsToWin), 3 * screenWidth / 4 - 20, 20, 80, RAYWHITE);

    // Dibujar círculo central con distorsión si está activa
    Vector2 centerPos = {(float)screenWidth / 2, (float)screenHeight / 2};
    if (game->distortionWave.IsActive()) {
        Vector2 displacement = game->distortionWave.GetDisplacement(centerPos);
        DrawCircle(centerPos.x + displacement.x, centerPos.y + displacement.y, 70, LightGreen);
    } else {
        DrawCircle(screenWidth / 2, screenHeight / 2, 70, LightGreen);
    }
    
    DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, DARKGRAY);

    // Calcular tiempo transcurrido sin incluir pausas
    double elapsedTime;
    if (game->currentState == PAUSED) {
        // Durante la pausa, mostrar el tiempo hasta que comenzó la pausa
        elapsedTime = game->pauseStartTime - game->startTime - game->pausedTime;
    } else {
        // Durante el juego, mostrar el tiempo actual menos el tiempo en pausa
        elapsedTime = GetTime() - game->startTime - game->pausedTime;
    }
    
    float ballSpeed = sqrt(game->ball.speedX * game->ball.speedX + game->ball.speedY * game->ball.speedY);
    const char* infoText = TextFormat("Press P to Pause | Time: %.1f s | Speed: %.1f", elapsedTime, ballSpeed);
    int textWidth = MeasureText(infoText, 20);
    DrawText(infoText, screenWidth / 2 - textWidth / 2, screenHeight - 40, 20, RAYWHITE);
    
    // Dibujar partículas primero (debajo de todo)
    game->particleSystem.Draw();
    
    game->ball.Draw();
    game->cpu.Draw();
    game->player.Draw();
    
    // Restaurar transformación (quitar el offset del shake)
    rlPopMatrix();
    
    // Dibujar flash encima de todo (sin transformación)
    game->flash.Draw();
}
