#include "SShadersBase.h"
#include <Glew\glew.h>
#include <FreeGlut\glut.h>
#include <SOGLUtility.h>

#pragma region Public Methods
SShadersBase::SShadersBase()
{
}

SShadersBase::SShadersBase(std::string vertexShaderFileName, std::string fragmentShaderFileName, std::vector<std::string> uniformNamesVector)
{
	InitializeUniformVariableNamesVector(uniformNamesVector);
	LoadShaderWithFileNames(vertexShaderFileName, fragmentShaderFileName);
}

SShadersBase::~SShadersBase()
{
	if (!m_ShaderProgramID)
	{
		glDeleteProgram(m_ShaderProgramID);
		m_ShaderProgramID = 0;
	}
}

void SShadersBase::UseShader()
{
	glUseProgram(m_ShaderProgramID);
}

GLuint SShadersBase::GetUniformVariableLocation(std::string uniformVariableName)
{
	if (m_UniformLocationsMap.find(uniformVariableName) == m_UniformLocationsMap.end())
	{
		printf("Can't find any uniform variable with name '%s' in the shader file\n", uniformVariableName.c_str());
		exit(1);
	}
	return m_UniformLocationsMap[uniformVariableName];

}

#pragma endregion

#pragma region Private Methods

void SShadersBase::LoadShaderWithFileNames(std::string vertexShaderFileName, std::string fragmentShaderFileName)
{
#pragma region Step 1: Create a handle for program.
	m_ShaderProgramID = glCreateProgram();
	//Checking if we are getting a non zero handle;
	if (m_ShaderProgramID == 0)
	{
		fprintf(stderr, "Error creating a shader program! \n");
		exit(1);
	}
#pragma endregion

#pragma region Step 3: Read Files
	std::string vertexShaderText = ReadShaderFile(vertexShaderFileName);
	std::string fragmentShaderText = ReadShaderFile(fragmentShaderFileName);
#pragma endregion

#pragma region Add Shaders to the shader program
	AddShader(vertexShaderText.c_str(), GL_VERTEX_SHADER);
	AddShader(fragmentShaderText.c_str(), GL_FRAGMENT_SHADER);
#pragma endregion

#pragma region Step 7: Link the program
	LinkProgram();
#pragma endregion

#pragma region Populate Uniform Locations, If any
	PopulateUniformLocations();
#pragma endregion

#pragma region Validate Shader Program
	ValidateShaderProgram();
#pragma endregion

#pragma region Step 9: Use/Enable the program
	UseShader();
#pragma endregion
}

std::string SShadersBase::ReadShaderFile(std::string fileName)
{
	std::string fileText;
	if (!ReadFile(fileName.c_str(), fileText)) { exit(1); }
	return fileText;
}

void SShadersBase::AddShader(const char* shaderText, GLenum shaderType)
{
#pragma region Step 2: Allocate Shader Handle
	GLuint shaderObjectHandleID = glCreateShader(shaderType);
	//Checking if shader handle is not zero.
	if (shaderObjectHandleID == 0)
	{
		fprintf(stderr, "Error Creating Shader Type %d\n", shaderType);
		exit(0);
	}
#pragma endregion

#pragma region Step 4: Load shader source into shader handle
	LoadShaderSourceInShaderObjectHandle(shaderObjectHandleID, shaderText);
#pragma endregion

#pragma region Step 5: Compile the shader
	CompileShader(shaderObjectHandleID, shaderType);
#pragma endregion

#pragma region Step 6: Attach the compiled shader to the program.
	glAttachShader(m_ShaderProgramID, shaderObjectHandleID);
#pragma endregion
}

void SShadersBase::LoadShaderSourceInShaderObjectHandle(const GLuint& shaderObjectHandleID, const char* shaderText)
{
	const GLchar* shaderTextPointer[1];
	GLint		  shaderTextLengthPointer[1];
	shaderTextPointer[0] = shaderText;
	shaderTextLengthPointer[0] = (GLint)strlen(shaderText);
	glShaderSource(shaderObjectHandleID, 1, shaderTextPointer, shaderTextLengthPointer);
}

void SShadersBase::CompileShader(const GLuint& shaderObjectHandleID, GLenum shaderType)
{
	glCompileShader(shaderObjectHandleID);
	//Checking for compilation errors, if any
	GLint success;
	glGetShaderiv(shaderObjectHandleID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[1024];
		glGetShaderInfoLog(shaderObjectHandleID, 1024, NULL, infoLog);
		fprintf(stderr, "Error compiling shader type %d: %s\n", shaderType, infoLog);
		exit(1);
	}
}

void SShadersBase::LinkProgram()
{
	GLint success;
	GLchar errorLog[1024] = { 0 };
	glLinkProgram(m_ShaderProgramID);
	//Check for link errors, if any
	glGetProgramiv(m_ShaderProgramID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(m_ShaderProgramID, 1024, NULL, errorLog);
		fprintf(stderr, "Error in linking the shader program: '%s'\n", errorLog);
		exit(1);
	}
}

void SShadersBase::PopulateUniformLocations()
{
	for (std::string uniformVariableName : m_UniformVariableNamesVector)
	{
		GLuint uniformVariableLocation = glGetUniformLocation(m_ShaderProgramID, uniformVariableName.c_str());
		if (uniformVariableLocation == -1)
		{
			printf("Error in getting the uniform location of '%s'\n", uniformVariableName.c_str());
			exit(1);
		}
		m_UniformLocationsMap[uniformVariableName] = uniformVariableLocation;
	}
}

void SShadersBase::ValidateShaderProgram()
{
	GLint  success;
	GLchar errorLog[1024] = { 0 };
	glValidateProgram(m_ShaderProgramID);
	//Check validation error, if any
	glGetProgramiv(m_ShaderProgramID, GL_VALIDATE_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(m_ShaderProgramID, 1024, NULL, errorLog);
		fprintf(stderr, "Error in validating the program: '%s'\n", errorLog);
		exit(1);
	}
}

void SShadersBase::InitializeUniformVariableNamesVector(std::vector<std::string> uniformNamesVector)
{
	m_UniformVariableNamesVector = uniformNamesVector;
}

#pragma endregion