/** Copyright (c) 2017 Lazu Ioan-Bogdan */

#include <stdio.h>
#include <SDL.h>

#include "Platform\PlatformVideo.h"

void InitializeVideo(SDL_Window **window, SDL_GLContext *context)
{
	SDL_LogSetPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO);

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to initialize SDL: %s\n", SDL_GetError());
	}

	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 8);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	*window = SDL_CreateWindow("",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		1000, 1000, // Resolution from config
		SDL_WINDOW_OPENGL); // Add if FULLSCREEN

	*context = SDL_GL_CreateContext(*window);

	SDL_GL_MakeCurrent(*window, *context);

	// TODO: set swap interval to 0 if we wish for instant updates
	SDL_GL_SetSwapInterval(0);	

	if (!*window) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to create OpenGL window: %s\n", SDL_GetError());
		SDL_Quit();
	}

	if (!SDL_GL_CreateContext(*window)) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to create OpenGL context: %s\n", SDL_GetError());
		SDL_Quit();
	}
}

#include "Engine\Object\Object.h"

#include "Engine\Engine.h"
#include "Engine\Object\GameObject.h"
#include "Engine\Camera.h"

#include "Engine\Asset\ShaderBlueprint.h"
#include "Engine\Asset\TextureBlueprint.h"
#include "Engine\Asset\Material.h"
#include "Engine\Asset\MeshBlueprint.h"

USING_NS_TRITRANIUM;

PEngine engine;
YCamera *camera;
PShaderProgram *prog;
PTexture *tex;

void init()
{

	engine.SetViewData(PWindowView{ 1000, 1000 });

	// Camera
	camera = (YCamera *)YCamera::NewObject();
	camera->Init(&engine);

	engine.PreTick();	
}

PTexture *GetTexture(PEngine *engine, PString name, PString path)
{
	PTextureBlueprint *textureBlueprint = new PTextureBlueprint(engine, name, path);
	textureBlueprint->AsyncLoad();
	textureBlueprint->VidInit();

	PTexture *tex = textureBlueprint->Build();
	delete textureBlueprint;

	return tex;
}

#include "Engine\Asset\AssetManager.h"

int main(int argc, char* argv[])
{	
	

	// TODO: global them
	SDL_Window *window;
	SDL_GLContext context;	
	
	Tritranium::YClass::StaticInit();
	
	InitializeVideo(&window, &context);

	InitializeRendererVideo();

	// TODO: put it in camera
	glViewport(0, 0, (GLsizei)(1000), (GLsizei)(1000));

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glClearColor(0, 0.3, 0.3, 1);

	init();

	PShaderBlueprint *blue = new PShaderBlueprint(&engine, "test",
		"G:/Workspace/C++/Tritranium/media/Shaders/textured1.glsl.vs",
		"G:/Workspace/C++/Tritranium/media/Shaders/textured1.glsl.fs");
	blue->AsyncLoad();
	blue->VidInit();

	PShaderProgram *prog = blue->Build();
	delete blue;

	PMaterial *material = new PMaterial(&engine, prog);

	PMeshBlueprint *meshBlueprint = new PMeshBlueprint(&engine, "mesh", "G:/Workspace/C++/Tritranium/media/Models/shuttle.obj");
	meshBlueprint->AsyncLoad();
	meshBlueprint->VidInit();

	PMesh *mesh = meshBlueprint->Build();
	delete meshBlueprint;

	PMat4x4 uni;
	uni.Identity();

	YCamera *camera = (YCamera *)YCamera::NewObject();
	camera->Init(&engine);

	material->SetMat4("uni_proj", camera->GetMtxProjection());

	material->SetMat4("uni_mv", uni);

	
	material->SetTexture("tex_diff", GetTexture(&engine, "texture", "G:/Workspace/C++/Tritranium/media/Textures/shuttle.png"));
	// material->SetTexture("tex_ao", GetTexture(&engine, "texture", "G:/Workspace/C++/Tritranium/media/Textures/Sphere/sphere_Ambient_Occlusion.png"));
	// material->SetTexture("tex_env", GetTexture(&engine, "texture", "G:/Workspace/C++/Tritranium/media/Textures/Env1.png"));

	material->SetVec3("light_pos", PVec3(0, 10, 0));

	camera->transform.position = PVec3(0, 0, -4);
	camera->transform.rotation = PVec3(0, 0, 0);

	engine.PreTick();

	PVidCommands *vid = engine.GetVidCommands();
	
	while (1)
	{
		// Camera defined
		glClearColor(0, 0, 0, 1);

		camera->Step();

		static float rot = 0.0f;
		rot += 35.0f * engine.GetTime().DeltaTime();

		
		camera->transform.position = PMath::Rotation(rot, PVec3(0, 1, 0)) * PVec3(0, 0, -1.5);
		camera->transform.rotation.y = rot;

		material->SetMat4("uni_mv", camera->GetMtxCamera());

		// Camera defined
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Try draw this		
		vid->DrawMesh(material, mesh);

		// Let's see the tick and the render tick
		engine.Tick();

		camera->DispatchTick();

		SDL_GL_SwapWindow(window);

		{
			SDL_Event event;
			while (SDL_PollEvent(&event))
			{
				switch (event.type) {
				case SDL_QUIT:
					SDL_Quit();
					exit(0);
					break;
				}
			}
		}

		// TODO: do not delay
		// SDL_Delay(16);
	}

	return 0;
}