#ifndef DISTORTION_WAVE_H
#define DISTORTION_WAVE_H

#include <raylib.h>

struct DistortionWave {
    float amplitude;      // Amplitud de la onda (intensidad de la distorsión)
    float frequency;      // Frecuencia de la onda
    float speed;          // Velocidad de propagación
    float time;           // Tiempo acumulado
    float duration;       // Duración del efecto
    float elapsed;        // Tiempo transcurrido
    bool active;          // Si el efecto está activo
    Vector2 epicenter;    // Punto de origen de la onda

    DistortionWave();
    
    // Iniciar onda de distorsión desde un punto
    void Start(Vector2 center, float waveAmplitude, float waveDuration);
    
    // Actualizar el efecto
    void Update(float deltaTime);
    
    // Obtener el desplazamiento para un punto dado
    Vector2 GetDisplacement(Vector2 point);
    
    // Verificar si está activo
    bool IsActive() const;
    
    // Reiniciar el efecto
    void Reset();
};

#endif // DISTORTION_WAVE_H
