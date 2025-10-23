#include <effects/screen_shake.h>
#include <cmath>

ScreenShake::ScreenShake() 
    : intensity(0.0f), duration(0.0f), elapsed(0.0f), offset({0.0f, 0.0f}), active(false) {
}

void ScreenShake::Start(float newIntensity, float newDuration) {
    intensity = newIntensity;
    duration = newDuration;
    elapsed = 0.0f;
    active = true;
}

void ScreenShake::Update(float deltaTime) {
    if (!active) return;
    
    elapsed += deltaTime;
    
    if (elapsed >= duration) {
        // Shake terminado
        Reset();
        return;
    }
    
    // Calcular factor de decaimiento (disminuye con el tiempo)
    float decayFactor = 1.0f - (elapsed / duration);
    
    // Generar offset aleatorio con decaimiento
    float currentIntensity = intensity * decayFactor;
    offset.x = ((GetRandomValue(0, 200) - 100) / 100.0f) * currentIntensity;
    offset.y = ((GetRandomValue(0, 200) - 100) / 100.0f) * currentIntensity;
}

Vector2 ScreenShake::GetOffset() const {
    return offset;
}

bool ScreenShake::IsActive() const {
    return active;
}

void ScreenShake::Reset() {
    intensity = 0.0f;
    duration = 0.0f;
    elapsed = 0.0f;
    offset = {0.0f, 0.0f};
    active = false;
}
