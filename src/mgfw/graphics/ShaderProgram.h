#pragma once

#include <string>
#include <map>

namespace mg
{

template <typename T> struct Vector2;
template <typename T> struct Vector3;
struct Color;

class ShaderProgram
{
public:
    enum Type
    {
        Vertex,
        Fragment
    };

public:
    ShaderProgram();
    ~ShaderProgram();

    bool loadFromFile(const std::string& vertexFile, const std::string& fragmentFile);
    bool loadFromSource(const std::string& vertexSource, const std::string& fragmentSource);

    void use();
    void stopUsing();

    bool isInUse() const;

    void bindAttribute(uint32_t index, const std::string& name);

    void setUniform(const std::string& name, const Vector2<float>& v);
    void setUniform(const std::string& name, const Vector3<float>& v);
    void setUniform(const std::string& name, const Color& c);

    const std::string& getVertexSource() const;
    const std::string& getFragmentSource() const;

private:
    bool setupHandle();
    bool setupShader(ShaderProgram::Type type, const std::string& source);

    bool compile(uint32_t shader);
    int getUniformLoc(const std::string& name);

    void link();

private:
    uint32_t m_handle;
    std::string m_vertexSource;
    std::string m_fragmentSource;

    std::map<std::string, int> m_uniforms;

};

} // namespace mg
