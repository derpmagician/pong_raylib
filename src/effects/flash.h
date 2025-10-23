#ifndef FLASH_H
#define FLASH_H

#include <raylib.h>

struct FlashEffect {
    Color color;          // Color del flash
    float alpha;          // Transparencia actual (0-1)
    float duration;       // Duración total del flash
    float elapsed;        // Tiempo transcurrido
    bool active;          // Si el flash está activo
    
    FlashEffect();
    
    void Start(Color flashColor, float duration);
    void Update(float deltaTime);
    void Draw();
    bool IsActive() const;
    void Reset();
};

#endif // FLASH_H
