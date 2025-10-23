#ifndef GLOW_H
#define GLOW_H

#include <raylib.h>

struct GlowEffect {
    float intensity;      // Intensidad del glow (0-1)
    float baseRadius;     // Radio base del objeto
    float glowRadius;     // Radio del glow actual
    Color glowColor;      // Color del resplandor
    bool active;          // Si el glow está activo
    
    GlowEffect();
    
    void SetIntensity(float intensity);
    void Update(float speed, float maxSpeed);  // Actualizar según velocidad
    void Draw(Vector2 position, float radius, Color baseColor);
    void SetActive(bool isActive);
    bool IsActive() const;
};

#endif // GLOW_H
