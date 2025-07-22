
//new commit push
#include <cstdlib>  // Add this line for malloc
#include <cstring>  // Add this line for memcpy
#include "raylib.h"
#include "rlgl.h" 
#include "raygui.h"
#include <cstdio>
#include <cmath>


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



    // Load compute shader
    char *computeShaderCode = LoadFileText("/home/honey_hiccups/Documents/Voxel_Bot/src/shaders/TestingComputeShader.comp");
    unsigned int computeShaderId = rlCompileShader(computeShaderCode, RL_COMPUTE_SHADER);

    // 2. Create the compute shader program

    unsigned int computeProgram = rlLoadComputeShaderProgram(computeShaderId);
    UnloadFileText(computeShaderCode);

    Shader computeShader = { computeProgram };

    printf ("\e[35mGl Version is %i\e[0m \n ", rlGetVersion());


    //Image outputImg = GenImageColor(800, 600, BLANK);
    float *pixels = (float *)RL_CALLOC(800*600*4, sizeof(float));  // 4 channels × float
    Image outputImg = {
    .data = pixels,
    .width = 800,
    .height = 600,
    .format = PIXELFORMAT_UNCOMPRESSED_R32G32B32A32,  // 32-bit float
    };

    Texture2D outputTex = LoadTextureFromImage(outputImg);
    UnloadImage(outputImg);

    // Bind texture to image unit 0 (matches layout(binding=0) in shader)
    rlBindImageTexture(outputTex.id, 0, PIXELFORMAT_UNCOMPRESSED_R32G32B32A32, false);
    





    BeginDrawing();
    ClearBackground(BLACK);
	EndDrawing();



	while (!WindowShouldClose())
	{

        ScreenSize = {float(GetScreenWidth()),float(GetScreenHeight())};

        ClearBackground(BLACK);

        BeginDrawing();


        //BeginShaderMode(computeShader);      // ?causes segfault
		//rlSetShader(computeShader.id, NULL); // ?causes segfault
        rlComputeShaderDispatch((int)ceil(800.0f / 16.0f),(int)ceil(600.0f / 16.0f),1); //dose not causes segfault


        //shadder img draw
        DrawTexture(outputTex, 0, 0, WHITE); 

        EndShaderMode();

        DrawFPS(0 ,20);
		EndDrawing();

	}


	CloseWindow();
	return 0;
}



/*
///////////////////// test shader
// main.cpp
#include "raylib.h"

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "shader");
    SetTargetFPS(300);

    Shader shader = LoadShader(0, TextFormat("/home/honey_hiccups/Documents/Voxel_Bot/src/shaders/testshader.fs"));

    Rectangle screenRect = { 0, 0, (float)screenWidth, (float)screenHeight };

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginShaderMode(shader);
        DrawRectangleRec(screenRect, WHITE);
        EndShaderMode();

		DrawFPS(0,20);
        EndDrawing();
    }

    UnloadShader(shader);
    CloseWindow();

    return 0;
}

/*
#include "raylib.h"


#define GLSL_VERSION            430

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "raylib [shaders] example - raymarching shapes");

    Camera camera = { 0 };
    camera.position = (Vector3){ 2.5f, 2.5f, 3.0f };    // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.7f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 65.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

    // Load raymarching shader
    // NOTE: Defining 0 (NULL) for vertex shader forces usage of internal default vertex shader

    Shader shader = LoadShader(0, TextFormat("/home/honey_hiccups/Documents/Voxel_Bot/src/shaders/raymarcher.fs", GLSL_VERSION));

	//Shader shader = LoadShader(0, TextFormat("raymarcher.fs", GLSL_VERSION));
    // Get shader locations for required uniforms
    int viewEyeLoc = GetShaderLocation(shader, "viewEye");
    int viewCenterLoc = GetShaderLocation(shader, "viewCenter");
    int runTimeLoc = GetShaderLocation(shader, "runTime");
    int resolutionLoc = GetShaderLocation(shader, "resolution");

    float resolution[2] = { (float)screenWidth, (float)screenHeight };
    SetShaderValue(shader, resolutionLoc, resolution, SHADER_UNIFORM_VEC2);

    float runTime = 0.0f;

    DisableCursor();                    // Limit cursor to relative movement inside the window
    SetTargetFPS(250);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(&camera, CAMERA_FIRST_PERSON);

        float cameraPos[3] = { camera.position.x, camera.position.y, camera.position.z };
        float cameraTarget[3] = { camera.target.x, camera.target.y, camera.target.z };

		camera.position = Vector3{ camera.position.x, camera.position.y + GetFrameTime()*(float(IsKeyDown(KEY_SPACE)) - float(IsKeyDown(KEY_LEFT_CONTROL))), camera.position.z };
		camera.target = Vector3{ camera.target.x, camera.target.y+ GetFrameTime()*(float(IsKeyDown(KEY_SPACE)) - float(IsKeyDown(KEY_LEFT_CONTROL))), camera.target.z };

        float deltaTime = GetFrameTime();
        runTime += deltaTime;

        // Set shader required uniform values
        SetShaderValue(shader, viewEyeLoc, cameraPos, SHADER_UNIFORM_VEC3);
        SetShaderValue(shader, viewCenterLoc, cameraTarget, SHADER_UNIFORM_VEC3);
        SetShaderValue(shader, runTimeLoc, &runTime, SHADER_UNIFORM_FLOAT);

        // Check if screen is resized
        if (IsWindowResized())
        {
            resolution[0] = (float)GetScreenWidth();
            resolution[1] = (float)GetScreenHeight();
            SetShaderValue(shader, resolutionLoc, resolution, SHADER_UNIFORM_VEC2);
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            // We only draw a white full-screen rectangle,
            // frame is generated in shader using raymarching
            BeginShaderMode(shader);
                DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), WHITE);
            EndShaderMode();

            DrawText("(c) Raymarching shader by Iñigo Quilez. MIT License.", GetScreenWidth() - 280, GetScreenHeight() - 20, 10, BLACK);


			DrawFPS(0, 20);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadShader(shader);           // Unload shader

    CloseWindow();                  // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

*/