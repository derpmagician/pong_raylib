#include <effects/distortion_wave.h>
#include <cmath>

DistortionWave::DistortionWave()
    : amplitude(0.0f), frequency(0.05f), speed(800.0f), time(0.0f), 
      duration(0.0f), elapsed(0.0f), active(false), epicenter({0.0f, 0.0f}) {
}

void DistortionWave::Start(Vector2 center, float waveAmplitude, float waveDuration) {
    epicenter = center;
    amplitude = waveAmplitude;
    duration = waveDuration;
    elapsed = 0.0f;
    time = 0.0f;
    active = true;
}

void DistortionWave::Update(float deltaTime) {
    if (!active) return;
    
    elapsed += deltaTime;
    time += deltaTime;
    
    if (elapsed >= duration) {
        Reset();
        return;
    }
    
    // La amplitud disminuye con el tiempo (decaimiento)
    // amplitude se mantiene constante, pero el cálculo de desplazamiento usa el factor de decaimiento
}

Vector2 DistortionWave::GetDisplacement(Vector2 point) {
    if (!active) return {0.0f, 0.0f};
    
    // Calcular distancia desde el epicentro
    float dx = point.x - epicenter.x;
    float dy = point.y - epicenter.y;
    float distance = std::sqrt(dx * dx + dy * dy);
    
    // Calcular el radio de la onda expandiéndose
    float waveRadius = speed * time;
    
    // Calcular qué tan cerca está el punto de la onda
    float distanceFromWave = std::abs(distance - waveRadius);
    
    // Solo afectar puntos cerca del frente de onda (banda de influencia)
    float influenceBand = 100.0f; // Ancho de la banda de influencia
    if (distanceFromWave > influenceBand) {
        return {0.0f, 0.0f};
    }
    
    // Factor de decaimiento temporal (disminuye con el tiempo)
    float decayFactor = 1.0f - (elapsed / duration);
    
    // Factor de decaimiento espacial (disminuye con la distancia del frente de onda)
    float spatialFactor = 1.0f - (distanceFromWave / influenceBand);
    
    // Calcular la intensidad de la distorsión
    float intensity = amplitude * decayFactor * spatialFactor;
    
    // Calcular el ángulo de oscilación basado en la distancia
    float angle = distance * frequency - time * 10.0f;
    float wave = std::sin(angle);
    
    // Aplicar distorsión perpendicular a la dirección del epicentro
    Vector2 displacement = {0.0f, 0.0f};
    
    if (distance > 0.1f) {
        // Normalizar la dirección
        float dirX = dx / distance;
        float dirY = dy / distance;
        
        // Crear vector perpendicular
        float perpX = -dirY;
        float perpY = dirX;
        
        // Aplicar desplazamiento perpendicular (onda tangencial)
        displacement.x = perpX * wave * intensity;
        displacement.y = perpY * wave * intensity;
        
        // También agregar un pequeño componente radial
        displacement.x += dirX * wave * intensity * 0.3f;
        displacement.y += dirY * wave * intensity * 0.3f;
    }
    
    return displacement;
}

bool DistortionWave::IsActive() const {
    return active;
}

void DistortionWave::Reset() {
    amplitude = 0.0f;
    time = 0.0f;
    elapsed = 0.0f;
    duration = 0.0f;
    active = false;
    epicenter = {0.0f, 0.0f};
}
