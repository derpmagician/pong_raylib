#include <gameover.h>

void UpdateGameOver(Game* game) {
    if (IsKeyPressed(KEY_ENTER)) {
        game->currentState = PLAYING;
        ResetGame(game);
    }
    
    if (IsKeyPressed(KEY_R)) {
        game->currentState = MENU;
    }
}

void DrawGameOver(Game* game) {
    ClearBackground(DarkGreen);
    
    const char* winnerText = (game->playerScore > game->cpuScore) ? "PLAYER WINS!" : "CPU WINS!";
    Color winnerColor = Yellow;
    
    DrawText("GAME OVER", screenWidth/2 - MeasureText("GAME OVER", 80)/2, 150, 80, Yellow);
    DrawText(winnerText, screenWidth/2 - MeasureText(winnerText, 60)/2, 300, 60, winnerColor);
    
    DrawText(TextFormat("Final Score - Player: %d  CPU: %d", game->playerScore, game->cpuScore), 
             screenWidth/2 - MeasureText(TextFormat("Final Score - Player: %d  CPU: %d", game->playerScore, game->cpuScore), 30)/2, 
             400, 30, RAYWHITE);
    
    DrawText("PRESS ENTER TO PLAY AGAIN", screenWidth/2 - MeasureText("PRESS ENTER TO PLAY AGAIN", 30)/2, 500, 30, LightGreen);
    DrawText("PRESS R TO RETURN TO MENU", screenWidth/2 - MeasureText("PRESS R TO RETURN TO MENU", 20)/2, 550, 20, LightGreen);
}
