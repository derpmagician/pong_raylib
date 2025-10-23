#include <ball.h>
#include <effects/screen_shake.h>
#include <effects/flash.h>
#include <effects/glow.h>
#include <effects/distortion_wave.h>
#include <cmath>

void Ball::Draw() {
    // Dibujar glow primero (debajo de la bola)
    if (glow != nullptr) {
        Vector2 pos = {x, y};
        glow->Draw(pos, (float)radius, color);
    }
    
    // Dibujar la bola encima
    DrawCircle(x, y, radius, color);
}

void Ball::EmitTrailParticles() {
    if (particleSystem == nullptr) return;
    
    // Calcular la dirección opuesta al movimiento
    float speed = std::sqrt(speedX * speedX + speedY * speedY);
    if (speed < 0.1f) return; // No emitir si está casi parado
    
    // Dirección normalizada del movimiento
    float dirX = speedX / speed;
    float dirY = speedY / speed;
    
    // Emitir partículas en dirección opuesta al movimiento
    int numParticles = 2; // Emitir 2 partículas por frame
    
    for (int i = 0; i < numParticles; i++) {
        // Posición de emisión ligeramente atrás de la bola
        Vector2 emitPos = {
            x - dirX * radius,
            y - dirY * radius
        };
        
        // Velocidad de las partículas: opuesta a la dirección de movimiento con variación aleatoria
        float spreadAngle = 0.3f; // Ángulo de dispersión
        float randomAngle = ((GetRandomValue(0, 100) / 100.0f) - 0.5f) * spreadAngle;
        
        float particleSpeed = speed * 0.3f; // Las partículas van más lentas que la bola
        Vector2 particleVel = {
            (-dirX * particleSpeed + randomAngle * dirY * 20.0f),
            (-dirY * particleSpeed - randomAngle * dirX * 20.0f)
        };
        
        // Variación en el tamaño de las partículas
        float particleSize = radius * (0.3f + GetRandomValue(0, 40) / 100.0f);
        
        // Color con un ligero tono amarillo/naranja para efecto de cometa
        Color particleColor = color;
        // Mezclar con amarillo/naranja para efecto de estela caliente
        particleColor.r = (unsigned char)((particleColor.r + 255) / 2);
        particleColor.g = (unsigned char)((particleColor.g + 200) / 2);
        particleColor.b = (unsigned char)(particleColor.b / 2);
        
        // Tiempo de vida aleatorio para más variedad (aumentado para cola más larga)
        float lifetime = 0.8f + GetRandomValue(0, 50) / 100.0f;  // 0.8-1.3 segundos (antes era 0.3-0.6)
        
        particleSystem->AddParticle(emitPos, particleVel, lifetime, particleSize, particleColor);
    }
}

void Ball::Update(int& playerScore, int& cpuScore, Sound wallHitSound, Sound explosionSound) {
    // Emitir partículas de estela antes de actualizar la posición
    EmitTrailParticles();
    
    // Actualizar glow según velocidad
    if (glow != nullptr) {
        float speed = std::sqrt(speedX * speedX + speedY * speedY);
        float maxSpeed = 20.0f;  // Velocidad máxima esperada
        glow->Update(speed, maxSpeed);
    }
    
    x += speedX;
    y += speedY;

    // Rebote en paredes superior e inferior
    if (y - radius <= 0 || y + radius >= GetScreenHeight()) {
        speedY = -speedY;
        // Establecer pitch aleatorio entre 0.7 (30% menos) y 1.3 (30% más) de 0% a 60% + 70%
        float randomPitch = 0.7f + (GetRandomValue(0, 60) / 100.0f);
        SetSoundPitch(wallHitSound, randomPitch);
        PlaySound(wallHitSound);  // Reproducir sonido al chocar con la pared
    }
    // Puntaje y reinicio si la bola sale por los lados
    if (x + radius >= GetScreenWidth()) {
        playerScore++;
        // Activar efectos al anotar
        if (screenShake != nullptr) {
            screenShake->Start(10.0f, 0.3f);
        }
        if (flash != nullptr) {
            Color flashColor = { 20, 160, 133, 255 };  // DarkGreen
            flash->Start(flashColor, 0.2f);
        }
        if (distortionWave != nullptr) {
            distortionWave->Start(Vector2{x, y}, 15.0f, 1.0f);  // Onda desde el punto de impacto
        }
        // Reproducir sonido de explosión
        PlaySound(explosionSound);
        ResetBall();
    }

    if (x - radius <= 0) {
        cpuScore++;
        // Activar efectos al anotar
        if (screenShake != nullptr) {
            screenShake->Start(10.0f, 0.3f);
        }
        if (flash != nullptr) {
            Color flashColor = { 20, 160, 133, 255 };  // DarkGreen
            flash->Start(flashColor, 0.2f);
        }
        if (distortionWave != nullptr) {
            distortionWave->Start(Vector2{x, y}, 15.0f, 1.0f);  // Onda desde el punto de impacto
        }
        // Reproducir sonido de explosión
        PlaySound(explosionSound);
        ResetBall();
    }
}

void Ball::ResetBall() {
    x = GetScreenWidth() / 2;
    y = GetScreenHeight() / 2;

    // Reiniciar velocidades a valores iniciales
    speedX = 7.0f;
    speedY = 7.0f;

    int speedChoices[2] = { -1, 1 };
    // Dirección aleatoria
    speedX *= speedChoices[GetRandomValue(0, 1)];
    speedY *= speedChoices[GetRandomValue(0, 1)];
}