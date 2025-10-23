#include <raylib.h>
#include <resource_dir.h>
#include <game_state.h>
#include <menu.h>
#include <gameplay.h>
#include <pause.h>
#include <gameover.h>

int main()
{
	const int currentFps = 60, paddleHeight = 120, paddleWidth = 30;
	bool shouldExit = false;
	
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(screenWidth, screenHeight, "Pong Game");
	
	// Inicializar sistema de audio
	InitAudioDevice();
	
	SetTargetFPS(currentFps);               // Set our game to run at 60 frames-per-second
	SetExitKey(KEY_NULL);                   // Desactivar ESC para cerrar la ventana

	// Inicializar datos del juego
	Game game;
	InitGame(&game, paddleHeight, paddleWidth);

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	// Cargar sonidos del juego
	LoadGameSounds(&game);
	
	// Cargar sonidos del menú
	LoadMenuSounds();
	
	// Opción 1: Usar la misma textura pero voltear la del CPU horizontalmente
	Texture2D paddleTexture = LoadTexture("graphics/paddle_texture.png");
	game.player.SetTexture(paddleTexture, false);  // Normal
	game.cpu.SetTexture(paddleTexture, true);      // Volteada horizontalmente
	
	
	// game loop
	while (!WindowShouldClose()  && !shouldExit)		// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		// drawing
		BeginDrawing();

		// Manejar diferentes estados del juego
		switch(game.currentState) {
			case MENU:
				// Verificar si se presiona ESC en el menú
                if (IsKeyPressed(KEY_ESCAPE)) {
                    shouldExit = true;  // Marcar para salir del loop
                }
				UpdateMenu(&game, &shouldExit);
				DrawMenu();
				break;
			
			case SETTINGS:
				UpdateSettings(&game);
				DrawSettings(&game);
				break;
				
			case PLAYING:
				UpdatePlaying(&game);
				DrawPlaying(&game);
				break;
				
			case PAUSED:
				UpdatePause(&game);
				DrawPause(&game);
				break;
				
			case GAME_OVER:
				UpdateGameOver(&game);
				DrawGameOver(&game);
				break;
		}
		
		// Terminar el dibujo del frame y prepararse para el siguiente (mostrar frame, sondear entrada, etc...)
		EndDrawing();
	}

	// cleanup
	// Descargar texturas
	UnloadTexture(paddleTexture);
	
	// Descargar sonidos del menú
	UnloadMenuSounds();
	
	// Descargar sonidos
	UnloadGameSounds(&game);
	
	// Cerrar sistema de audio
	CloseAudioDevice();

	// Destruyer la ventana y limpiar el contexto OpenGL
	CloseWindow();
	return 0;
}