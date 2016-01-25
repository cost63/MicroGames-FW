#include "ShaderProgram.h"

#include <fstream>
#include <GL/glew.h>

#include "../system/ErrorLog.h"
#include "../math/Vector2.h"
#include "../math/Vector3.h"
#include "../graphics/Color.h"

namespace mg
{

// TODO(All) Once File system is finished, use it instead
std::string stringFromFile(const std::string& filename)
{
    std::string output;
    std::string line;

    std::ifstream file;
    file.open( filename.c_str(), std::ios::in );

    if( file.is_open() ) {
        while( std::getline( file, line ) ) {
            output.append( line );
            output.append( "\n" );
        }
    }
    else {
        PRINT_ERROR( "Unable to open file " + filename );
    }

    return output;
}

ShaderProgram::ShaderProgram()
: m_handle(0)
{}

ShaderProgram::~ShaderProgram()
{
    if(m_handle != 0)
    {
        glDeleteProgram(m_handle);
    }
}

bool ShaderProgram::loadFromFile(const std::string& vertexFile, const std::string& fragmentFile)
{
    std::string vertexSource;
    std::string fragmentSource;

    if(!vertexFile.empty())
    {
        vertexSource = stringFromFile(vertexFile);
    }

    if(!fragmentFile.empty())
    {
        fragmentSource = stringFromFile(fragmentFile);
    }

    return loadFromSource(vertexSource, fragmentSource);
}

bool ShaderProgram::loadFromSource(const std::string& vertexSource, const std::string& fragmentSource)
{
    if(vertexSource.empty() && fragmentSource.empty())
    {
        PRINT_ERROR("Unable to load shader. Both vertex and fragment shader sources are empty");
        return false;
    }

    // If the shader program was not created yet
    if(m_handle == 0)
    {
        // If program creation failed
        if(!setupHandle())
        {
            return false;
        }
    }

    if(!vertexSource.empty())
    {
        if(!setupShader(ShaderProgram::Vertex, vertexSource))
        {
            return false;
        }
    }
    if(!fragmentSource.empty())
    {
        if(!setupShader(ShaderProgram::Fragment, fragmentSource))
        {
            return false;
        }
    }

    link();

    return true;
}

void ShaderProgram::use() const
{
    if(!isInUse())
    {
        glUseProgram(m_handle);
    }
}

void ShaderProgram::stopUsing()
{
    if(isInUse())
    {
        glUseProgram(0);
    }
}

bool ShaderProgram::isInUse() const
{
    int currentProgram = 0;
    glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);

    return (currentProgram == (int)m_handle);
}

void ShaderProgram::bindAttribute(uint32_t index, const std::string& name)
{
    glBindAttribLocation(m_handle, index, name.c_str());
}

void ShaderProgram::setUniform(const std::string& name, const Vec2f& v)
{
    use();

    int loc = getUniformLoc(name);

    if(loc != -1) {
        glUniform2fv(loc, 1, v.data);
    }
}

void ShaderProgram::setUniform(const std::string& name, const Vec3f& v)
{
    use();

    int loc = getUniformLoc(name);

    if(loc != -1) {
        glUniform3fv(loc, 1, v.data);
    }
}

void ShaderProgram::setUniform(const std::string& name, const Color& c)
{
    use();

    int loc = getUniformLoc(name);

    if(loc != -1) {
        glUniform4fv(loc, 1, &c.getNormalized()[0]);
    }
}

const std::string& ShaderProgram::getVertexSource() const
{
    return m_vertexSource;
}

const std::string& ShaderProgram::getFragmentSource() const
{
    return m_fragmentSource;
}

/* Private */

bool ShaderProgram::setupHandle()
{
    m_handle = glCreateProgram();

    GLint infoLogLength = 512;
    GLint errorLength = 0;
    GLchar infoLog[512]; // VS doesn't support VLA's (so 512 instead of infoLogLength)

    glGetProgramiv(m_handle, GL_INFO_LOG_LENGTH, &infoLogLength);
    glGetProgramInfoLog(m_handle, infoLogLength, &errorLength, infoLog);

    if(errorLength != 0)
    {
        PRINT_ERROR("Failed to create Shader program with following errors:\n" +
                    std::string(infoLog));

        return false;
    }

    return true;
}

bool ShaderProgram::setupShader(ShaderProgram::Type type, const std::string& source)
{
    uint32_t shader = 0;

    if(type == ShaderProgram::Vertex)
    {
        shader = glCreateShader(GL_VERTEX_SHADER);
    }
    else
    {
        shader = glCreateShader(GL_FRAGMENT_SHADER);
    }

    const char* rawSource = source.c_str();
    glShaderSource(shader, 1, &rawSource, nullptr);

    if(!compile(shader))
    {
        glDeleteShader(shader);
        return false;
    }

    glAttachShader(m_handle, shader);

    if(type == ShaderProgram::Vertex)
    {
        m_vertexSource = source;
    }
    else
    {
        m_fragmentSource = source;
    }

    return true;
}

bool ShaderProgram::compile(uint32_t shader)
{
    glCompileShader(shader);

    int compiled = false; // Has to be int as glGetShaderiv accepts int as param
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

    if(!compiled)
    {
        const int errorLogLength = 512;
        char errorLog[errorLogLength];

        glGetShaderInfoLog(shader, errorLogLength, nullptr, errorLog);

        PRINT_ERROR(std::string(errorLog));

        return false;
    }

    return true;
}

int ShaderProgram::getUniformLoc(const std::string& name)
{
    auto found = m_uniforms.find(name);

    int location = -1;

    if(found != m_uniforms.end())
    {
        location = found->second;
    }
    else
    {
        location = glGetUniformLocation(m_handle, name.c_str());
        m_uniforms[name] = location;
    }

    return location;
}

void ShaderProgram::link()
{
    // Can't link a program that hasn't be created yet
    if(m_handle == 0)
    {
        return;
    }

    glLinkProgram(m_handle);

    int success = false;
    glGetProgramiv(m_handle, GL_LINK_STATUS, &success);

    if(!success)
    {
        int infoLogLength = 512;
        int errorLength = 0;
        char infoLog[512]; // VS doesn't support VLA's (so 512 instead of infoLogLength)

        glGetProgramiv(m_handle, GL_INFO_LOG_LENGTH, &infoLogLength);
        glGetProgramInfoLog(m_handle, infoLogLength, &errorLength, infoLog);

        if(errorLength != 0) {
            PRINT_ERROR("Failed to link Shader program with following errors:\n" +
                        std::string(infoLog));
        }
    }
}

} // namespace mg
