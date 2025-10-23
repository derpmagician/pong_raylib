#include <menu.h>

// Incluir los sonidos del menú
#include "../resources/sounds/selectchange.h"
#include "../resources/sounds/selected.h"

static int selectedOption = MENU_PLAY;
static Sound selectChangeSound;
static Sound selectedSound;

void LoadMenuSounds() {
    Wave selectChangeWave;
    selectChangeWave.frameCount = SELECTCHANGE_FRAME_COUNT;
    selectChangeWave.sampleRate = SELECTCHANGE_SAMPLE_RATE;
    selectChangeWave.sampleSize = SELECTCHANGE_SAMPLE_SIZE;
    selectChangeWave.channels = SELECTCHANGE_CHANNELS;
    selectChangeWave.data = SELECTCHANGE_DATA;
    selectChangeSound = LoadSoundFromWave(selectChangeWave);
    
    Wave selectedWave;
    selectedWave.frameCount = SELECTED_FRAME_COUNT;
    selectedWave.sampleRate = SELECTED_SAMPLE_RATE;
    selectedWave.sampleSize = SELECTED_SAMPLE_SIZE;
    selectedWave.channels = SELECTED_CHANNELS;
    selectedWave.data = SELECTED_DATA;
    selectedSound = LoadSoundFromWave(selectedWave);
}

void UnloadMenuSounds() {
    UnloadSound(selectChangeSound);
    UnloadSound(selectedSound);
}

void UpdateMenu(Game* game, bool* shouldExit) {
    // Navegar hacia arriba
    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) {
        selectedOption--;
        if (selectedOption < 0) {
            selectedOption = MENU_OPTION_COUNT - 1;
        }
        PlaySound(selectChangeSound);
    }
    
    // Navegar hacia abajo
    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) {
        selectedOption++;
        if (selectedOption >= MENU_OPTION_COUNT) {
            selectedOption = 0;
        }
        PlaySound(selectChangeSound);
    }
    
    // Confirmar selección
    if (IsKeyPressed(KEY_ENTER)) {
        PlaySound(selectedSound);
        switch (selectedOption) {
            case MENU_PLAY:
                game->currentState = PLAYING;
                ResetGame(game);
                break;
            case MENU_SETTINGS:
                game->currentState = SETTINGS;
                break;
            case MENU_QUIT:
                *shouldExit = true;
                break;
        }
    }
    
    // ESC como atajo rápido para salir
    if (IsKeyPressed(KEY_ESCAPE)) {
        *shouldExit = true;
    }
}

void DrawMenu() {
    ClearBackground(DarkGreen);
    
    // Título
    DrawText("PONG GAME", screenWidth/2 - MeasureText("PONG GAME", 80)/2, 150, 80, Yellow);
    
    // Opciones del menú
    const char* playText = "PLAY";
    const char* settingsText = "SETTINGS";
    const char* quitText = "QUIT";
    
    int playWidth = MeasureText(playText, 50);
    int settingsWidth = MeasureText(settingsText, 50);
    int quitWidth = MeasureText(quitText, 50);
    
    int menuY = 350;
    int menuSpacing = 80;
    
    // Opción PLAY
    Color playColor = (selectedOption == MENU_PLAY) ? Yellow : RAYWHITE;
    if (selectedOption == MENU_PLAY) {
        DrawText(">", screenWidth/2 - playWidth/2 - 50, menuY, 50, Purple);
        DrawText("<", screenWidth/2 + playWidth/2 + 20, menuY, 50, Purple);
    }
    DrawText(playText, screenWidth/2 - playWidth/2, menuY, 50, playColor);
    
    // Opción SETTINGS
    Color settingsColor = (selectedOption == MENU_SETTINGS) ? Yellow : RAYWHITE;
    if (selectedOption == MENU_SETTINGS) {
        DrawText(">", screenWidth/2 - settingsWidth/2 - 50, menuY + menuSpacing, 50, Purple);
        DrawText("<", screenWidth/2 + settingsWidth/2 + 20, menuY + menuSpacing, 50, Purple);
    }
    DrawText(settingsText, screenWidth/2 - settingsWidth/2, menuY + menuSpacing, 50, settingsColor);
    
    // Opción QUIT
    Color quitColor = (selectedOption == MENU_QUIT) ? Yellow : RAYWHITE;
    if (selectedOption == MENU_QUIT) {
        DrawText(">", screenWidth/2 - quitWidth/2 - 50, menuY + menuSpacing * 2, 50, Purple);
        DrawText("<", screenWidth/2 + quitWidth/2 + 20, menuY + menuSpacing * 2, 50, Purple);
    }
    DrawText(quitText, screenWidth/2 - quitWidth/2, menuY + menuSpacing * 2, 50, quitColor);
    
    // Instrucciones
    DrawText("USE W/S OR ARROW KEYS TO NAVIGATE", screenWidth/2 - MeasureText("USE W/S OR ARROW KEYS TO NAVIGATE", 20)/2, 600, 20, LightGreen);
    DrawText("PRESS ENTER TO SELECT", screenWidth/2 - MeasureText("PRESS ENTER TO SELECT", 20)/2, 630, 20, LightGreen);
    
    // Info de controles de juego
    DrawText("GAME CONTROLS: W/S keys", screenWidth/2 - MeasureText("GAME CONTROLS: W/S keys", 18)/2, 680, 18, DARKGRAY);
}

void UpdateSettings(Game* game) {
    // Regresar al menú (cancelar sin guardar)
    if (IsKeyPressed(KEY_R)) {
        game->currentState = MENU;
        return;
    }
    
    // Ajustar puntos para ganar
    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) {
        if (game->settings.pointsToWin < 20) {
            game->settings.pointsToWin++;
        }
    }
    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) {
        if (game->settings.pointsToWin > 1) {
            game->settings.pointsToWin--;
        }
    }
    
    // Ajustar velocidad máxima
    if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) {
        if (game->settings.maxBallSpeed < 50) {
            game->settings.maxBallSpeed++;
        }
    }
    if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) {
        if (game->settings.maxBallSpeed > 11) {
            game->settings.maxBallSpeed--;
        }
    }
    
    // Guardar configuración
    if (IsKeyPressed(KEY_ENTER)) {
        SaveSettings(&game->settings);
        game->currentState = MENU;
    }
    
    // Restaurar valores por defecto
    if (IsKeyPressed(KEY_BACKSPACE)) {
        ResetToDefaults(&game->settings);
    }
}

void DrawSettings(Game* game) {
    ClearBackground(DarkGreen);
    
    // Título
    DrawText("SETTINGS", screenWidth/2 - MeasureText("SETTINGS", 80)/2, 80, 80, Yellow);
    
    // Configuración de puntos para ganar
    const char* pointsLabel = "POINTS TO WIN:";
    DrawText(pointsLabel, screenWidth/2 - MeasureText(pointsLabel, 30)/2, 220, 30, RAYWHITE);
    
    const char* pointsValue = TextFormat("%d", game->settings.pointsToWin);
    DrawText(pointsValue, screenWidth/2 - MeasureText(pointsValue, 60)/2, 270, 60, Yellow);
    
    DrawText("< W / S >", screenWidth/2 - MeasureText("< W / S >", 25)/2, 340, 25, LightGreen);
    
    // Configuración de velocidad máxima
    const char* speedLabel = "MAX BALL SPEED:";
    DrawText(speedLabel, screenWidth/2 - MeasureText(speedLabel, 30)/2, 420, 30, RAYWHITE);
    
    const char* speedValue = TextFormat("%d", game->settings.maxBallSpeed);
    DrawText(speedValue, screenWidth/2 - MeasureText(speedValue, 60)/2, 470, 60, Yellow);
    
    DrawText("< A / D >", screenWidth/2 - MeasureText("< A / D >", 25)/2, 540, 25, LightGreen);
    
    // Instrucciones
    DrawText("PRESS ENTER TO SAVE", screenWidth/2 - MeasureText("PRESS ENTER TO SAVE", 25)/2, 630, 25, Purple);
    DrawText("PRESS BACKSPACE TO RESTORE DEFAULTS", screenWidth/2 - MeasureText("PRESS BACKSPACE TO RESTORE DEFAULTS", 20)/2, 670, 20, RAYWHITE);
    DrawText("PRESS R TO CANCEL", screenWidth/2 - MeasureText("PRESS R TO CANCEL", 20)/2, 700, 20, RAYWHITE);
}
