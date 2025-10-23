#include <effects/flash.h>

FlashEffect::FlashEffect()
    : color(WHITE), alpha(0.0f), duration(0.0f), elapsed(0.0f), active(false) {
}

void FlashEffect::Start(Color flashColor, float flashDuration) {
    color = flashColor;
    duration = flashDuration;
    elapsed = 0.0f;
    alpha = 1.0f;  // Empezar completamente opaco
    active = true;
}

void FlashEffect::Update(float deltaTime) {
    if (!active) return;
    
    elapsed += deltaTime;
    
    if (elapsed >= duration) {
        Reset();
        return;
    }
    
    // Fade out lineal (de 1.0 a 0.0)
    alpha = 1.0f - (elapsed / duration);
}

void FlashEffect::Draw() {
    if (!active || alpha <= 0.0f) return;
    
    // Dibujar rectángulo semi-transparente sobre toda la pantalla
    Color flashColor = color;
    flashColor.a = (unsigned char)(255 * alpha);
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), flashColor);
}

bool FlashEffect::IsActive() const {
    return active;
}

void FlashEffect::Reset() {
    alpha = 0.0f;
    elapsed = 0.0f;
    duration = 0.0f;
    active = false;
}
