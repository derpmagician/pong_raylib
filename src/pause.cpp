#include <pause.h>
#include <gameplay.h>

void UpdatePause(Game* game) {
    if (IsKeyPressed(KEY_P)) {
        game->currentState = PLAYING;
        game->pausedTime += GetTime() - game->pauseStartTime;
    }
    if (IsKeyPressed(KEY_R)) {
        game->currentState = MENU;
        game->pausedTime = 0.0;
    }
}

void DrawPause(Game* game) {
    // Dibujar el estado de juego actual como fondo
    DrawPlaying(game);
    
    // Overlay semi-transparente
    DrawRectangle(0, 0, screenWidth, screenHeight, OverlayColor);
    
    DrawText("PAUSED", screenWidth/2 - MeasureText("PAUSED", 60)/2, screenHeight/2 - 30, 60, Yellow);
    DrawText("PRESS P TO RESUME", screenWidth/2 - MeasureText("PRESS P TO RESUME", 30)/2, screenHeight/2 + 50, 30, RAYWHITE);
    DrawText("PRESS R TO RETURN TO MENU", screenWidth/2 - MeasureText("PRESS R TO RETURN TO MENU", 20)/2, screenHeight/2 + 100, 20, LightGreen);
}
