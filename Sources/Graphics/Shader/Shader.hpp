#pragma once
#include "glad/glad.h"
#include "glm/glm.hpp"
#include <string>

namespace D3EGraphics
{
    class Shader
    {
	public:
		Shader(const char* vertex_src, const char* frag_src);
		~Shader() = default;

		char* read(const char* src);
		void compile_shader(GLuint id, const char* src);
		void link_shader();

		void bind() const;
		void unbind() const;

		GLuint get_uniform_location(const std::string& name);
		void vec3_uniform(const std::string& name, glm::vec3 value);
		void mat4_uniform(const std::string& name, glm::mat4 value);
		// void float_uniform(const std::string& name, float value) const;

		unsigned int get_program() const { return m_ProgramId; }
	private:
		unsigned int m_ProgramId;
		std::unordered_map<std::string, GLuint> m_CachedLocations;
    };
}
// class Shader
// {
// 	public:
// 		Shader(const char*, const char*);
// 		~Shader() {};
// 		unsigned int CACShaders(unsigned int);
// 		void bind() const;
// 		void unbind() const;
// 		unsigned int program_id;
// 		/*UNIFORMS*/
// 		void SUvec3(const std::string& name, glm::vec3 value) const;
// 		void SUfloat(const std::string& name, float value) const;
// 		void SUint(const std::string& name, int value) const;
// 		void SUmat4(const std::string& name, glm::mat4 value) const;

// 		inline void setType(std::string setType) { type = setType; }
// 		std::string getType() { return type; }
// 		GLuint getID() const { return program_id; }
// 	private:
// 		std::string vertexShader;
// 		std::string fragmentShader;
// 		std::string type;
// };
