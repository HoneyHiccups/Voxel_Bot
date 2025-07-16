
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

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	//SearchAndSetResourceDir("resources");

	//ExportImgToSource();  // funcstion I use for embeding things :: umath



	Vector2 ScreenSize = {float(GetScreenWidth()),float(GetScreenHeight())};

	SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor())-2);

	//Scene* mainscene = &Scene::Get();

    //printf("%s\n", glGetString(GL_VERSION));


	EndDrawing();

	//mainscene->printfromscene();
	// game loop

	while (!WindowShouldClose())		// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{


		ScreenSize = {float(GetScreenWidth()),float(GetScreenHeight())};

		BeginDrawing();
		ClearBackground(BLUE);
        //DrawText(TextFormat("OpenGL %s", glGetString(GL_VERSION)), 10, 10, 20, GREEN);

		EndDrawing();

	}


	CloseWindow();
	return 0;
}
