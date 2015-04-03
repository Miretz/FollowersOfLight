#include "ShaderLoader.h"

ShaderLoader::ShadersMap ShaderLoader::myShaders;

sf::Shader* ShaderLoader::getShader(const std::string& path)
{
    ShadersMap::iterator it = myShaders.find(path);

    if(it != myShaders.end())
        return it->second.getShader();

    if(!myShaders[path].loadShaderFromFile(path))
        std::cout << "An error occured while loading the following shader:" << path << std::endl;

    return myShaders[path].getShader();
}

ShaderLoader::ShaderObject::ShaderObject()
{
    myShader = NULL;
}

ShaderLoader::ShaderObject::~ShaderObject()
{
    if(myShader)
        delete myShader;
}

sf::Shader* ShaderLoader::ShaderObject::getShader() const
{
    return myShader;
};

bool ShaderLoader::ShaderObject::loadShaderFromFile(const std::string& path)
{
    if(!myShader)
        myShader=new sf::Shader;

    return myShader->loadFromFile(path, sf::Shader::Fragment);
}
