#ifndef PADDLE_H
#define PADDLE_H

#include <raylib.h>

class Paddle {
protected:
    void LimitMovement();

public:
    float x, y;
    float width, height;
    int speedY;
    Color color;
    Texture2D texture;
    bool useTexture;
    bool flipHorizontal;  // Para voltear la textura horizontalmente

    void Draw();
    void Update();
    void SetTexture(Texture2D tex, bool flip = false);
};

class CpuPaddle : public Paddle {
public:
    void Update(int ballY);
};

#endif // PADDLE_H