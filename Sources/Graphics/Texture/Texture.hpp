#pragma once
#include "glad/glad.h"
#include <string>


namespace D3EGraphics
{
    class Texture
    {
    private:
        int width;
        int height;
        int numberOfColorChannels;

        unsigned char* LoadedData;
        unsigned int texture_id;

        std::string type;
    public:
        Texture(const char* fn, std::string type);
        virtual ~Texture();

        void bind(int unit) const;
        void unbind(int unit) const;

        unsigned int get_id() const;
        std::string getType() { return type; }
    };

}
