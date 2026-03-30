#include "Shader.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ios>


namespace D3EGraphics
{
    Shader::Shader(const char* vertex_src, const char* frag_src)
    {
    	const char* v_src = read(vertex_src);
    	const char* f_src = read(frag_src);

    	GLuint vertex_id = glCreateShader(GL_VERTEX_SHADER);
    	GLuint frag_id = glCreateShader(GL_FRAGMENT_SHADER);

    	compile_shader(vertex_id, v_src);
    	compile_shader(frag_id, f_src);

    	if(m_ProgramId = glCreateProgram(); m_ProgramId == 0)
    	{
    	    std::cout << "Failed to glCreateProgram()!\n";
    	}

    	glAttachShader(m_ProgramId, vertex_id);
    	glAttachShader(m_ProgramId, frag_id);

    	link_shader();
    }

    char* Shader::read(const char* src)
    {
        std::ifstream file(src, std::ios::binary | std::ios::ate);
        if(!file)
        {
            return nullptr;
        }

        std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);
        char* buffer = new char[size + 1];
        if(!file.read(buffer, size))
        {
            delete[] buffer;
            return nullptr;
        }

        buffer[size] = '\0';
        return buffer;

    }

    void Shader::compile_shader(GLuint id, const char* src)
    {
        GLint result;
        GLint log_len;
        glShaderSource(id, 1, &src, NULL);
        glCompileShader(id);

        glGetShaderiv(id, GL_COMPILE_STATUS, &result);
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &log_len);
        if(log_len > 0)
        {
            GLchar* info_log = nullptr;
            glGetShaderInfoLog(id, log_len, nullptr, info_log);
            std::cout << "Shader Compilation Failed!\n";
        }

    }

    void Shader::link_shader()
    {
        glLinkProgram(m_ProgramId);

        GLint result;
        GLint log_len;
        glGetProgramiv(m_ProgramId, GL_LINK_STATUS, &result);
        glGetProgramiv(m_ProgramId, GL_INFO_LOG_LENGTH, &log_len);
        if(log_len > 0)
        {
            GLchar* info_log = nullptr;
            glGetProgramInfoLog(m_ProgramId, log_len, nullptr, info_log);
            std::cout << "Shader Linking Failed!\n";
        }
    }

    void Shader::bind() const
    {
        glUseProgram(m_ProgramId);
    }

    void Shader::unbind() const
    {
        glUseProgram(0);
    }


    // /*UNIFORMS*/
    GLuint Shader::get_uniform_location(const std::string& name)
    {
        if(m_CachedLocations.find(name) != m_CachedLocations.end())
            return m_CachedLocations[name];

        GLuint loc = glGetUniformLocation(m_ProgramId, name.c_str());
        m_CachedLocations[name] = loc;
        return loc;
    }

    void Shader::vec3_uniform(const std::string& name, glm::vec3 value)
    {
        GLuint loc = get_uniform_location(name);
        glUniform3f(loc, value.x, value.y, value.z);
    }

    void Shader::mat4_uniform(const std::string& name, glm::mat4 value)
    {
        GLuint loc = get_uniform_location(name);
        glUniformMatrix4fv(loc, 1, GL_FALSE, &value[0][0]);
    }
}
// void Shader::SUvec3(const std::string& name, glm::vec3 value) const {
// 	glUniform3f(glGetUniformLocation(program_id, name.c_str()), value.x, value.y, value.z);
// }

// void Shader::SUfloat(const std::string& name, float value) const {
// 	glUniform1f(glGetUniformLocation(program_id, name.c_str()), value);
// }

// void Shader::SUint(const std::string& name, int value) const {
// 	glUniform1i(glGetUniformLocation(program_id, name.c_str()), value);
// }

// void Shader::SUmat4(const std::string& name, glm::mat4 value) const {
// 	glUniformMatrix4fv(glGetUniformLocation(program_id, name.c_str()), 1, GL_FALSE, &value[0][0]);
// }
