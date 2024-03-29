#include "Shader.h"
#include "OpenGLIncludes.h"
#include <assert.h>


//-----------------------------------------------------------------------------
// Constructor & destructor.
//-----------------------------------------------------------------------------

Shader::Shader()
	: m_isLinked(false)
{
	m_glProgram = glCreateProgram();
	for (int i = 0; i < MAX_SHADER_STAGES; ++i)
		m_glShaderStages[i] = 0;
}

Shader::~Shader()
{
	if (m_isLinked)
	{
		//delete [] m_params;
	}

	glDeleteProgram(m_glProgram);
		
	// Delete the shader stages.
	for (int i = 0; i < MAX_SHADER_STAGES; ++i)
	{
		if (m_glShaderStages != 0)
			glDeleteShader(m_glShaderStages[i]);
	}
}

	

//-----------------------------------------------------------------------------
// Accessors.
//-----------------------------------------------------------------------------

bool Shader::IsLinked() const
{
	return m_isLinked;
}

unsigned int Shader::GetNumUniforms() const
{
	return m_uniforms.size();
}

const Uniform& Shader::GetUniform(unsigned int index) const
{
	return m_uniforms[index];
}

const Uniform* Shader::GetUniform(const std::string& name) const
{
	for (unsigned int i = 0; i < m_uniforms.size(); ++i)
	{
		if (m_uniforms[i].m_name == name)
			return &m_uniforms[i];
	}
	return nullptr;
}

	
//-----------------------------------------------------------------------------
// Compiling and Linking
//-----------------------------------------------------------------------------

bool Shader::AddStage(const std::string& code, ShaderType::value_type type)
{
	GLuint shaderGL = 0;

	// Create the correct shader object.
	if (type == ShaderType::VERTEX_SHADER)
		shaderGL = glCreateShader(GL_VERTEX_SHADER);
	else if (type == ShaderType::FRAGMENT_SHADER)
		shaderGL = glCreateShader(GL_FRAGMENT_SHADER);
	else if (type == ShaderType::GEOMETRY_SHADER)
		shaderGL = glCreateShader(GL_GEOMETRY_SHADER);
	else if (type == ShaderType::COMPUTE_SHADER)
		shaderGL = glCreateShader(GL_COMPUTE_SHADER);
	else
	{
		assert(false);
		//CMG_ASSERT_FALSE("Invalid shader stage type.");
		return false;
	}

	// Set the shader's source code.
	const GLchar* str[1] = { code.c_str() };
	GLint lengths[1] = { (GLint) code.length() };
	glShaderSource(shaderGL, 1, str, lengths);
		
	// Attach the shader stage to the shader program.
	glAttachShader(m_glProgram, shaderGL);
	m_glShaderStages[(int) type] = shaderGL;
	m_isLinked = false;
	return true;
}
	
bool Shader::CompileAndLink()
{
	GLint  isStatusOK;
	GLuint shaderGL;
	GLchar errorMsg[1024] = { 0 };

	// Compile all shader stages.
	for (int i = 0; i < MAX_SHADER_STAGES; ++i)
	{
		shaderGL = m_glShaderStages[i];

		if (shaderGL != 0)
		{
			// Compile the shader.
			glCompileShader(shaderGL);
			glGetShaderiv(shaderGL, GL_COMPILE_STATUS, &isStatusOK);
			if (isStatusOK == GL_FALSE)
			{
				glGetShaderInfoLog(shaderGL, sizeof(errorMsg), NULL, errorMsg);
				fprintf(stderr, "Error compiling shader:\n%s\n", errorMsg);
				return false;
			}
		}
	}

	// Link the program.
	glLinkProgram(m_glProgram);
	glGetProgramiv(m_glProgram, GL_LINK_STATUS, &isStatusOK);
	if (isStatusOK == GL_FALSE)
	{
		glGetProgramInfoLog(m_glProgram, sizeof(errorMsg), NULL, errorMsg);
		fprintf(stderr, "Error linking shader:\n%s\n", errorMsg);
		return false;
	}

	// Validate the program.
	glValidateProgram(m_glProgram);
	glGetProgramiv(m_glProgram, GL_VALIDATE_STATUS, &isStatusOK);
	if (isStatusOK == GL_FALSE)
	{
		glGetProgramInfoLog(m_glProgram, sizeof(errorMsg), NULL, errorMsg);
		fprintf(stderr, "Shader validation failed:\n%s\n", errorMsg);
		return false;
	}

	m_isLinked = true;
	GenerateUniforms();
	return true;
}


//-----------------------------------------------------------------------------
// Private methods.
//-----------------------------------------------------------------------------
	
void Shader::GenerateUniforms()
{
	// Find the number of uniforms and the max uniform name length.
	int maxNameLength;
	int numUniforms;
	glGetProgramiv(m_glProgram, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxNameLength);
	glGetProgramiv(m_glProgram, GL_ACTIVE_UNIFORMS, &numUniforms);
	m_uniforms.resize(numUniforms);
	GLchar* uniformName = new char[maxNameLength];

	int samplerSlot = 0;
		
	// Create a list of all shader parameters.
	for (int i = 0; i < numUniforms; ++i)
	{
		Uniform& uniform = m_uniforms[i];
		uniform.m_location = i;
		uniform.m_name = new char[maxNameLength];

		GLint size;
		GLenum type;
		glGetActiveUniform(m_glProgram, (GLuint) i,
			maxNameLength, NULL, &size, &type, uniformName);

		uniform.m_name = uniformName;

		switch (type)
		{
		case GL_BOOL:
			uniform.m_type = UniformType::BOOLEAN;
			break;
		case GL_INT:
			uniform.m_type = UniformType::INTEGER;
			break;
		case GL_FLOAT:
			uniform.m_type = UniformType::FLOAT;
			break;
		case GL_FLOAT_VEC2:
			uniform.m_type = UniformType::VEC2;
			break;
		case GL_FLOAT_VEC3:
			uniform.m_type = UniformType::VEC3;
			break;
		case GL_FLOAT_VEC4:
			uniform.m_type = UniformType::VEC4;
			break;
		case GL_FLOAT_MAT4:
			uniform.m_type = UniformType::MATRIX;
			break;
		case GL_SAMPLER_2D:
		case GL_SAMPLER_3D:
		case GL_SAMPLER_CUBE:
			uniform.m_type = UniformType::TEXTURE;
			uniform.m_samplerSlot = samplerSlot++;
			break;
		default:
			fprintf(stderr, "Warning: unsupported GLSL uniform type for '%s'\n", uniformName);
			//CMG_ASSERT_FALSE("Unsupported uniform type");
			assert(false);
			break;
		}
	}

	delete [] uniformName;
}

