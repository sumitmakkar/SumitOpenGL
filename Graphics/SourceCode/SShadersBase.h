#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <SumitOGLMaths.h>

class SShadersBase
{
	private:
		GLuint									m_ShaderProgramID;
		std::vector<std::string>				m_UniformVariableNamesVector;
		std::unordered_map<std::string, GLuint> m_UniformLocationsMap;

	public:
		SShadersBase();
		SShadersBase(std::string vertexShaderFileName, std::string fragmentShaderFileName, std::vector<std::string> uniformNamesVector = std::vector<std::string>());
		~SShadersBase();
		void UseShader();	//Step 9
		GLuint GetUniformVariableLocation(std::string uniformVariableName);

	private:
		void LoadShaderWithFileNames(std::string vertexShaderFileName, std::string fragmentShaderFileName);//Step 1 to Step 9
		std::string ReadShaderFile(std::string fileName);	//Step3: Read files
		void AddShader(const char* shaderText, GLenum shaderType);	//Step 2 to Step 6
		void LoadShaderSourceInShaderObjectHandle(const GLuint& shaderObjectHandleID, const char* shaderText);	//Step 4
		void CompileShader(const GLuint& shaderObjectHandleID, GLenum shaderType);	//Step 5
		void LinkProgram();	//Step 7
		void PopulateUniformLocations();
		void ValidateShaderProgram();	//Step 8
		void InitializeUniformVariableNamesVector(std::vector<std::string> uniformNamesVector);
};