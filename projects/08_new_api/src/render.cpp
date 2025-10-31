#include "sys.hpp"


namespace render {

    uint32_t _create_shader(GLenum type, std::string path);
    uint32_t _create_program(std::vector<uint32_t> shaders);
    void _delete_program(uint32_t id, std::vector<uint32_t> shaders);
    uint32_t _create_texture2D(std::string path);

    // Vertex Buffer
    void VertexBuffer::clear() {
        list.clear();
    }

    void VertexBuffer::add1(float x) {
        list.push_back(x);
    }

    void VertexBuffer::add2(float x, float y) {
        list.push_back(x);
        list.push_back(y);
    }

    void VertexBuffer::add2(const glm::vec2& v) {
        add2(v.x, v.y);
    }

    void VertexBuffer::add3(float x, float y, float z) {
        list.push_back(x);
        list.push_back(y);
        list.push_back(z);
    }

    void VertexBuffer::add3(const glm::vec3& v) {
        add3(v.x, v.y, v.z);
    }

    void VertexBuffer::add4(float x, float y, float z, float w) {
        list.push_back(x);
        list.push_back(y);
        list.push_back(z);
        list.push_back(w);
    }

    void VertexBuffer::add4(const glm::vec4& v) {
        add4(v.x, v.y, v.z, v.w);
    }

    void VertexBuffer::add1List(std::vector<float>& l) {
        std::for_each(l.begin(), l.end(), [&](float x) {
            this->add1(x);
        });
    }

    void VertexBuffer::add2List(std::vector<glm::vec2>& l) {
        std::for_each(l.begin(), l.end(), [&](glm::vec2& v) {
            this->add2(v.x, v.y);
        });
    }

    void VertexBuffer::add3List(std::vector<glm::vec3>& l) {
        std::for_each(l.begin(), l.end(), [&](glm::vec3& v) {
            this->add3(v.x, v.y, v.z);
        });
    }

    void VertexBuffer::add4List(std::vector<glm::vec4>& l) {
        std::for_each(l.begin(), l.end(), [&](glm::vec4& v) {
            this->add4(v.x, v.y, v.z, v.w);
        });
    }


    void VertexBuffer::init() {
        glGenBuffers(1, &id);
    }

    void VertexBuffer::release() {
        this->clear();
        glDeleteBuffers(1, &id);
    }

    void VertexBuffer::update() {
        this->bind();
        glBufferData(GL_ARRAY_BUFFER, this->dataSize(), list.data(), GL_DYNAMIC_DRAW);
        this->unbind();
    }

    void VertexBuffer::bind() {
        glBindBuffer(GL_ARRAY_BUFFER, id);
    }

    void VertexBuffer::unbind() {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }


    size_t VertexBuffer::typeSize() {
        return sizeof(float);
    }

    size_t VertexBuffer::dataSize() {
        return list.size() * typeSize();
    }

    
    size_t VertexBuffer::elementCount(BufferSize bs) {
        if(bs == BufferSize::BUFFER_SIZE_1) {
            return list.size();
        } else if(bs == BufferSize::BUFFER_SIZE_2) {
            return list.size() / 2;
        } else if(bs == BufferSize::BUFFER_SIZE_3) {
            return list.size() / 3;
        } else if(bs == BufferSize::BUFFER_SIZE_4) {
            return list.size() / 4;
        } else {
            return list.size();
        }
    }

    // Index Buffer
    void IndexBuffer::clear() {
        list.clear();
    }

    void IndexBuffer::add1(uint32_t x) {
        list.push_back(x);
    }

    void IndexBuffer::add2(uint32_t x, uint32_t y) {
        list.push_back(x);
        list.push_back(y);
    }

    void IndexBuffer::add2(const glm::ivec2& v) {
        add2(v.x, v.y);
    }

    void IndexBuffer::add3(uint32_t x, uint32_t y, uint32_t z) {
        list.push_back(x);
        list.push_back(y);
        list.push_back(z);
    }

    void IndexBuffer::add3(const glm::ivec3& v) {
        add3(v.x, v.y, v.z);
    }

    void IndexBuffer::add4(uint32_t x, uint32_t y, uint32_t z, uint32_t w) {
        list.push_back(x);
        list.push_back(y);
        list.push_back(z);
        list.push_back(w);
    }

    void IndexBuffer::add4(const glm::ivec4& v) {
        add4(v.x, v.y, v.x, v.w);
    }

    void IndexBuffer::add1List(std::vector<uint32_t>& l) {
        std::for_each(l.begin(), l.end(), [&](uint32_t x) {
            add1(x);
        });
    }

    void IndexBuffer::add2List(std::vector<glm::ivec2>& l) {
        std::for_each(l.begin(), l.end(), [&](glm::ivec2& x) {
            add2(x.x, x.y);
        });
    }

    void IndexBuffer::add3List(std::vector<glm::ivec3>& l) {
        std::for_each(l.begin(), l.end(), [&](glm::ivec3& l) {
            add3(l.x, l.y, l.z);
        });
    }

    void IndexBuffer::add4List(std::vector<glm::ivec4>& l) {
        std::for_each(l.begin(), l.end(), [&](glm::ivec4& l) {
            add4(l.x, l.y, l.z, l.w);
        });
    }

    void IndexBuffer::init() {
        glGenBuffers(1, &id);
    }

    void IndexBuffer::release() {
        clear();
        glDeleteBuffers(1, &id);
    }

    void IndexBuffer::update() {
        this->bind();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->dataSize(), list.data(), GL_DYNAMIC_DRAW);
        this->unbind();
    }

    void IndexBuffer::bind() {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    }

    void IndexBuffer::unbind() {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }


    size_t IndexBuffer::typeSize() {
        return sizeof(uint32_t);
    }

    size_t IndexBuffer::dataSize() {
        return list.size() * typeSize();
    }

    
    size_t IndexBuffer::elementCount(BufferSize bs) {
        if(bs == BufferSize::BUFFER_SIZE_1) {
            return list.size();
        } else if(bs == BufferSize::BUFFER_SIZE_2) {
            return list.size() / 2;
        } else if(bs == BufferSize::BUFFER_SIZE_3) {
            return list.size() / 3;
        } else if(bs == BufferSize::BUFFER_SIZE_4) {
            return list.size() / 4;
        } else {
            return list.size();
        }
    }


    // Main Shader
    void MainShader::init() {
        vs = _create_shader(GL_VERTEX_SHADER, "main.vs.glsl");
        fs = _create_shader(GL_FRAGMENT_SHADER, "main.fs.glsl");

        prog = _create_program({vs, fs});

        glGenVertexArrays(1, &va);

        glUseProgram(prog);
        // Uniforms
        u_proj = glGetUniformLocation(prog, "proj");
        u_view = glGetUniformLocation(prog, "view");
        u_model = glGetUniformLocation(prog, "model");
        u_tex0 = glGetUniformLocation(prog, "tex0");
        glUniform1i(u_tex0, 0);

        // Setup Vertex Arrays
        glBindVertexArray(va);
        glEnableVertexAttribArray(A_VERTICES);
        //glEnableVertexAttribArray(MAIN_A_COLORS);
        glEnableVertexAttribArray(A_TEXCOORDS);
        glBindVertexArray(0);
        glUseProgram(0);
    }

    void MainShader::release() {
        glDeleteVertexArrays(1, &va);
        _delete_program(prog, {vs, fs});
        glDeleteShader(vs);
        glDeleteShader(fs);
    }

    void MainShader::bind() {
        glUseProgram(prog);
    }

    void MainShader::unbind() {
        glUseProgram(0);
    }

    void MainShader::setProjection(const glm::mat4& m) {
        glUniformMatrix4fv(u_proj, 1, GL_FALSE, &m[0][0]);
    }

    void MainShader::setView(const glm::mat4& m) {
        glUniformMatrix4fv(u_view, 1, GL_FALSE, &m[0][0]);
    }

    void MainShader::setModel(const glm::mat4& m) {
        glUniformMatrix4fv(u_model, 1, GL_FALSE, &m[0][0]);
    }

    // I'll need to add in
    // vertices ~ VertexBuffer
    // texCoords ~ VertexBuffer
    // indexBuffer ~ IndexBuffer
    void MainShader::draw(
        VertexBuffer& vertices,
        VertexBuffer& texCoords,
        IndexBuffer& indencies
    ) {
        glBindVertexArray(this->va);
        vertices.bind();
        glVertexAttribPointer(A_VERTICES, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        texCoords.bind();
        glVertexAttribPointer(A_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
        texCoords.unbind();

        indencies.bind();
        glDrawElements(GL_TRIANGLES, indencies.elementCount(BufferSize::BUFFER_SIZE_1), GL_UNSIGNED_INT, nullptr);
        indencies.unbind();

        glBindVertexArray(0);
    }

    // Global Functions
    static MainShader mainShader;
    static std::map<std::string, uint32_t> textures;

    void init() {
        glEnable(GL_DEPTH_TEST);
        mainShader.init();
    }

    void release() {

        for(std::map<std::string, uint32_t>::iterator it = textures.begin(); it != textures.end(); it++) {
            glDeleteTextures(1, &it->second);
        }
        textures.clear();

        mainShader.release();
    }

    void clear(const glm::vec4& color) {
        glClearColor(color.r, color.g, color.b, color.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    MainShader* getMainShader() {
        return &mainShader;
    }

    void addTexture(std::string name, std::string path) {
        textures[name] = _create_texture2D(path);
    }

    void bindTexture(std::string name, GLenum active) {
        glActiveTexture(active);
        glBindTexture(GL_TEXTURE_2D, textures.at(name));
    }

    void unbindTextre(GLenum active) {
        glActiveTexture(active);
        glBindTexture(GL_TEXTURE_2D, 0);
    }


    uint32_t _create_shader(GLenum type, std::string path) {
        uint32_t temp = glCreateShader(type);

        // Load Source
        std::ifstream in(path);
        in.seekg(0, std::ios::end);
        size_t fsize = in.tellg();
        in.seekg(0, std::ios::beg);
        std::string src;
        src.resize(fsize);
        in.read(src.data(), src.size());
        in.close();

        std::cout << src << "\n";

        const char* c_src = src.c_str();

        glShaderSource(temp, 1, &c_src, nullptr);

        glCompileShader(temp);

        int32_t len = 0;
        glGetShaderiv(temp, GL_INFO_LOG_LENGTH, &len);

        if(len > 0) {
            std::string log;
            log.resize(len);
            glGetShaderInfoLog(temp, log.size(), nullptr, log.data());
            std::cout << log << "\n";
        }
        return temp;
    }

    uint32_t _create_program(std::vector<uint32_t> shaders) {
        uint32_t temp = glCreateProgram();

        std::for_each(shaders.begin(), shaders.end(), [&](uint32_t shader) {
            glAttachShader(temp, shader);
        });
        
        glLinkProgram(temp);

        int32_t len = 0;
        glGetProgramiv(temp, GL_INFO_LOG_LENGTH, &len);

        if(len > 0) {
            std::string log;
            log.resize(len);
            glGetProgramInfoLog(temp, log.size(), nullptr, log.data());
            std::cout << log << "\n";
        }

        return temp;
    }

    void _delete_program(uint32_t id, std::vector<uint32_t> shaders) {
        std::for_each(shaders.begin(), shaders.end(), [&](uint32_t shader) {
            glDetachShader(id, shader);
        });
        glDeleteProgram(id);
    }

    uint32_t _create_texture2D(std::string path) {
        uint32_t temp = 0;

        SDL_Surface* surf = IMG_Load(path.c_str());

        if(surf == nullptr) {
            std::cout << path << " wasn't found\n";
            return 0;
        }

        glGenTextures(1, &temp);

        glBindTexture(GL_TEXTURE_2D, temp);

        glTexImage2D(
            GL_TEXTURE_2D, 
            0, 
            GL_RGBA, 
            surf->w, 
            surf->h, 
            0, 
            GL_RGBA, 
            GL_UNSIGNED_BYTE, 
            surf->pixels);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

        glGenerateMipmap(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, 0);

        SDL_DestroySurface(surf);
        return temp;
    }

}