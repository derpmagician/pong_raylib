#ifndef PARTICLE_H
#define PARTICLE_H

#include <raylib.h>
#include <vector>

struct Particle {
    Vector2 position;
    Vector2 velocity;
    float lifetime;
    float maxLifetime;
    float size;
    Color color;
    
    Particle(Vector2 pos, Vector2 vel, float life, float sz, Color col);
    void Update(float deltaTime);
    void Draw();
    bool IsAlive() const;
};

class ParticleSystem {
private:
    std::vector<Particle> particles;
    int maxParticles;

public:
    ParticleSystem(int maxParticles = 100);
    
    void AddParticle(Vector2 position, Vector2 velocity, float lifetime, float size, Color color);
    void Update(float deltaTime);
    void Draw();
    void Clear();
    int GetParticleCount() const;
};

#endif // PARTICLE_H
