#include <effects/particle.h>
#include <algorithm>
#include <cmath>

// Implementación de Particle
Particle::Particle(Vector2 pos, Vector2 vel, float life, float sz, Color col)
    : position(pos), velocity(vel), lifetime(life), maxLifetime(life), size(sz), color(col) {
}

void Particle::Update(float deltaTime) {
    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;
    
    // Reducir velocidad gradualmente (fricción)
    velocity.x *= 0.98f;
    velocity.y *= 0.98f;
    
    lifetime -= deltaTime;
}

void Particle::Draw() {
    if (lifetime > 0) {
        // Calcular alpha basado en el tiempo de vida restante
        float alpha = (lifetime / maxLifetime);
        Color particleColor = color;
        particleColor.a = (unsigned char)(255 * alpha);
        
        // Calcular tamaño basado en el tiempo de vida
        float currentSize = size * (0.5f + 0.5f * alpha);
        
        DrawCircleV(position, currentSize, particleColor);
    }
}

bool Particle::IsAlive() const {
    return lifetime > 0;
}

// Implementación de ParticleSystem
ParticleSystem::ParticleSystem(int maxParticlesCount)
    : maxParticles(maxParticlesCount) {
    particles.reserve(maxParticlesCount);
}

void ParticleSystem::AddParticle(Vector2 position, Vector2 velocity, float lifetime, float size, Color color) {
    if (particles.size() < static_cast<size_t>(maxParticles)) {
        particles.emplace_back(position, velocity, lifetime, size, color);
    } else {
        // Si alcanzamos el máximo, eliminar la partícula más vieja y agregar la nueva
        particles.erase(particles.begin());
        particles.emplace_back(position, velocity, lifetime, size, color);
    }
}

void ParticleSystem::Update(float deltaTime) {
    // Actualizar todas las partículas
    for (auto& particle : particles) {
        particle.Update(deltaTime);
    }
    
    // Eliminar partículas muertas
    particles.erase(
        std::remove_if(particles.begin(), particles.end(),
            [](const Particle& p) { return !p.IsAlive(); }),
        particles.end()
    );
}

void ParticleSystem::Draw() {
    // Dibujar partículas de atrás hacia adelante para efecto de profundidad
    for (auto& particle : particles) {
        particle.Draw();
    }
}

void ParticleSystem::Clear() {
    particles.clear();
}

int ParticleSystem::GetParticleCount() const {
    return static_cast<int>(particles.size());
}
