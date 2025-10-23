#ifndef BALL_H
#define BALL_H

#include <raylib.h>
#include <effects/particle.h>

// Forward declaration para evitar dependencias circulares
struct ScreenShake;
struct FlashEffect;
struct GlowEffect;
struct DistortionWave;

class Ball {
public:
    float x, y;
    int radius;
    float speedX, speedY;
    Color color;
    ParticleSystem* particleSystem;
    ScreenShake* screenShake;
    FlashEffect* flash;
    GlowEffect* glow;
    DistortionWave* distortionWave;

    void Draw();
    void Update(int& playerScore, int& cpuScore, Sound wallHitSound, Sound explosionSound);
    void ResetBall();
    void EmitTrailParticles();
};

#endif // BALL_H