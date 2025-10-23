#ifndef SCREEN_SHAKE_H
#define SCREEN_SHAKE_H

#include <raylib.h>

struct ScreenShake {
    float intensity;      // Intensidad actual del shake
    float duration;       // Duración total del shake
    float elapsed;        // Tiempo transcurrido
    Vector2 offset;       // Offset actual de la cámara
    bool active;          // Si el shake está activo
    
    ScreenShake();
    
    void Start(float intensity, float duration);
    void Update(float deltaTime);
    Vector2 GetOffset() const;
    bool IsActive() const;
    void Reset();
};

#endif // SCREEN_SHAKE_H
