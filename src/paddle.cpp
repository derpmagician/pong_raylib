#include <paddle.h>

void Paddle::LimitMovement() {
    if (y <= 0) y = 0;
    if (y + height >= GetScreenHeight()) y = GetScreenHeight() - height;
}

void Paddle::Draw() {
    if (useTexture && texture.id > 0) {
        // Configurar el rectángulo de origen (source)
        // Si flipHorizontal es true, invertir el ancho
        Rectangle source = { 
            0, 
            0, 
            flipHorizontal ? -(float)texture.width : (float)texture.width,
            (float)texture.height 
        };
        
        // Dibujar con textura escalada al tamaño del paddle
        DrawTexturePro(
            texture,
            source,
            Rectangle{ x, y, width, height },
            Vector2{ 0, 0 },
            0.0f,
            WHITE
        );
    } else {
        // Dibujar rectángulo con color si no hay textura
        DrawRectangleRounded(Rectangle{ x, y, width, height }, 0.8, 0, color);
    }
}

void Paddle::SetTexture(Texture2D tex, bool flip) {
    texture = tex;
    useTexture = true;
    flipHorizontal = flip;
}

void Paddle::Update() {
    if (IsKeyDown(KEY_UP)) y -= speedY;
    if (IsKeyDown(KEY_DOWN)) y += speedY;
    LimitMovement();
}

void CpuPaddle::Update(int ballY) {
    if (y + height / 2 < ballY) y += speedY;
    else if (y + height / 2 > ballY) y -= speedY;
    LimitMovement();
}