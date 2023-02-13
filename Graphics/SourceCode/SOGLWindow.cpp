#include "SOGLWindow.h"

SOGLWindow* selfReference;

SOGLWindow::SOGLWindow(int argc, char* argv[], Vector4f windowBackgroundColour, std::string windowTitleString): m_WindowBackgroundColour(windowBackgroundColour)
{
	m_WindowWidth				= 1920;
	m_WindowHeight				= 1080;
	m_WindowStartingXCoordinate = 0;
	m_WindowStartingYCoordinate = 0;
	m_WindowTitleString			= windowTitleString;
	CreateOpenGLWindow(argc, argv);
}

SOGLWindow::SOGLWindow(int windowWidth, int windowHeight, int windowStartingXCoordinate, int windowStartingYCoordinate, int argc, char* argv[], Vector4f windowBackgroundColour, std::string windowTitleString): m_WindowBackgroundColour(windowBackgroundColour)
{
	m_WindowWidth				= windowWidth;
	m_WindowHeight				= windowHeight;
	m_WindowStartingXCoordinate = windowStartingXCoordinate;
	m_WindowStartingYCoordinate = windowStartingYCoordinate;
	m_WindowTitleString			= windowTitleString;
	CreateOpenGLWindow(argc, argv);
}

SOGLWindow::~SOGLWindow()
{
}


void SOGLWindow::CreateOpenGLWindow(int argc, char* argv[])
{
#ifdef _WIN64
	srand(GetCurrentProcessId());
#else
	srandom(getpid());
#endif
	InitializeWindow(argc, argv);

	char game_mode_string[64];
	// Game mode string example: <Width>x<Height>@<FPS>
	snprintf(game_mode_string, sizeof(game_mode_string), "%dx%d@60", m_WindowWidth, m_WindowHeight);
	glutGameModeString(game_mode_string);
	glutEnterGameMode();

	if (InitializeGlew())
	{
		selfReference = this;
		SetWindowBackgroundColour();
		EnableWindowParameters();
	}
}

void SOGLWindow::InitializeWindow(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	glutInitWindowSize(m_WindowWidth, m_WindowHeight);

	glutInitWindowPosition(m_WindowStartingXCoordinate, m_WindowStartingYCoordinate);

	int win = glutCreateWindow(m_WindowTitleString.c_str());
	printf("Window id %d\n", win);

	//Full Screen Code
	char game_mode_string[64];
	snprintf(game_mode_string, sizeof(game_mode_string), "%dx%d@60", m_WindowWidth, m_WindowHeight);
	glutGameModeString(game_mode_string);
	glutEnterGameMode();
}

bool SOGLWindow::InitializeGlew()
{
	GLenum res = glewInit();
	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	if (res != GLEW_OK)
	{
		fprintf(stderr, "Error: '%s' \n", glewGetErrorString(res));
		return false;
	}
	return true;
}

void SOGLWindow::SetWindowBackgroundColour()
{
	GLclampf Red   = m_WindowBackgroundColour.x;
	GLclampf Green = m_WindowBackgroundColour.y;
	GLclampf Blue  = m_WindowBackgroundColour.z;
	GLclampf Alpha = m_WindowBackgroundColour.w;
	glClearColor(Red, Green, Blue, Alpha);
}

void SOGLWindow::EnableWindowParameters()
{
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
}

void SOGLWindow::UpdateFrame()
{
	glutDisplayFunc(RenderSceneCB);
	glutKeyboardFunc(KeyboardCB);
	glutSpecialFunc(SpecialKeyboardCB);
	glutPassiveMotionFunc(PassiveMouseCB);
	glutMainLoop();
}

void SOGLWindow::UpdateRenderer(SRendererBase* renderer)
{
	m_renderer = renderer;
}

void SOGLWindow::RenderSceneCB()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	selfReference->m_renderer->UpdateScene(0.1f);
	selfReference->m_renderer->RenderScene();

	glutPostRedisplay();	//For calling this function multiple times

	glutSwapBuffers();
}

void SOGLWindow::KeyboardCB(unsigned char key, int mouse_x, int mouse_y)
{
	selfReference->m_renderer->HandleKeyboardEvents(key, mouse_x, mouse_y);
}

void SOGLWindow::SpecialKeyboardCB(int key, int mouse_x, int mouse_y)
{
	selfReference->m_renderer->HandleKeyboardSpecialEvents(key, mouse_x, mouse_y);
}

void SOGLWindow::PassiveMouseCB(int x, int y)
{
	selfReference->m_renderer->HandleMouseEvents(x, y);
}
