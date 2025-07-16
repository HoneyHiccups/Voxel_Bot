
//new commit push
#include <cstdlib>  // Add this line for malloc
#include <cstring>  // Add this line for memcpy
#include "raylib.h"
#include "rlgl.h" 
#include "raygui.h"
#include <cstdio>


int main ()
{

	#define ScreenSizeX_min 800
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_WINDOW_HIGHDPI | FLAG_WINDOW_MAXIMIZED | 0 | 0);

	// Create the window and OpenGL context
	InitWindow(1280, 720, "VOXEL_BOT");
	//SetWindowMinSize(RoundtoInt(float(1280)*.66f),RoundtoInt(float(720)*.66f));               // Set window minimum dimensions (for FLAG_WINDOW_RESIZABLE)



	Vector2 ScreenSize = {float(GetScreenWidth()),float(GetScreenHeight())};

	SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor())-2);


    // Create a texture for compute shader output
    Image outputImg = GenImageColor(800, 600, BLANK);
    Texture2D outputTex = LoadTextureFromImage(outputImg);
    UnloadImage(outputImg);

    // Load compute shader
    Shader compShader = LoadShader(0, TextFormat("testraymarch.comp", 430));




	EndDrawing();



	while (!WindowShouldClose())		// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{

		

		ScreenSize = {float(GetScreenWidth()),float(GetScreenHeight())};

		BeginTextureMode((RenderTexture2D){outputTex.id, 800, 600});
        BeginShaderMode(compShader);


		DrawRectangle(0, 0, 800, 600, WHITE);
		BeginDrawing();
		ClearBackground(BLUE);
        //DrawText(TextFormat("OpenGL %s", glGetString(GL_VERSION)), 10, 10, 20, GREEN);

		EndDrawing();

	}


	CloseWindow();
	return 0;
}
