#include <effects/glow.h>
#include <cmath>

GlowEffect::GlowEffect()
    : intensity(0.0f), baseRadius(0.0f), glowRadius(0.0f), 
      glowColor(YELLOW), active(true) {
}

void GlowEffect::SetIntensity(float newIntensity) {
    intensity = newIntensity;
    if (intensity < 0.0f) intensity = 0.0f;
    if (intensity > 1.0f) intensity = 1.0f;
}

void GlowEffect::Update(float speed, float maxSpeed) {
    if (!active) return;
    
    // Calcular intensidad basada en la velocidad
    // Más rápido = más glow
    float speedRatio = speed / maxSpeed;
    if (speedRatio > 1.0f) speedRatio = 1.0f;
    
    // Intensidad entre 0.3 y 1.0
    intensity = 0.3f + (speedRatio * 0.7f);
}

void GlowEffect::Draw(Vector2 position, float radius, Color baseColor) {
    if (!active || intensity <= 0.0f) return;
    
    // Dibujar múltiples círculos concéntricos con alpha decreciente
    // para simular el efecto de glow/bloom
    
    int glowLayers = 3;  // Número de capas de glow
    float maxGlowRadius = radius * (1.0f + intensity * 1.5f);  // Hasta 2.5x el radio
    
    for (int i = glowLayers; i > 0; i--) {
        float layerRatio = (float)i / (float)glowLayers;
        float currentRadius = radius + (maxGlowRadius - radius) * layerRatio;
        
        // Alpha disminuye hacia afuera
        float alpha = intensity * (0.4f / glowLayers) * ((float)i / glowLayers);
        
        Color layerColor = baseColor;
        layerColor.a = (unsigned char)(255 * alpha);
        
        DrawCircleV(position, currentRadius, layerColor);
    }
}

void GlowEffect::SetActive(bool isActive) {
    active = isActive;
}

bool GlowEffect::IsActive() const {
    return active;
}
