#ifndef VIDEO_MEMORY_H
#define VIDEO_MEMORY_H

#include <cstdint>
#include <kernel/Memory.hpp>
#include <kernel/RenderBuffer.hpp>
#include <SFML/Graphics.hpp>
#include <gif_lib.h>

using namespace std;

class VideoMemory : public Memory {
    // Permite o acesso as fun��e protected
    friend class GPUCommandMemory;
    // Detalhes da mem�ria
    const unsigned int w, h;
    const uint64_t address;
    const uint64_t length;
    // Framebuffer da imagem final
    sf::RenderTexture framebuffer;
    // Textura contendo a imagem que � vis�vel na tela,
    // funciona como mem�ria de v�deo
    sf::RenderTexture gpuRenderTexture;
    // �reas para desenho do framebuffer e combinar os renders
    // em CPU e GPU
    sf::Sprite framebufferSpr, combineSpr;
    // Vertex arrays utilizadas para desenhar informa��o de timing
    RenderBuffer gpuQuadsBuffer;
    RenderBuffer gpuLinesBuffer;
    RenderBuffer gpuTrisBuffer;
    // Textura que permite a leitura e escrita.
    // Mem�ria de v�deo para opera��es n�o aceleradas em hardware
    sf::Texture cpuTexture;
    uint8_t *buffer;
    // Refer�ncia para a janela para que possamos desenhar para ela
    sf::RenderWindow &window;
    // C�digo e o shader utilizado para desenhar mixar texturas
    // e expandir para a tela
    const static string shaderVertex;
    const static string toRGBAShaderFragment;
    const static string combineShaderFragment;
    const static string spriteShaderFragment;
    sf::Shader toRGBAShader, combineShader, spriteShader;
    // Textura utilizada como paleta pelo shader
    sf::Texture paletteTex;
    // Textura contendo sprites
    sf::Texture spriteTex;
    // Arquivo para salvar gifs
    GifFileType *gif;
    // Paleta do gif
    ColorMapObject *colormap;
    // Transformadas da tela (para normalizar mouse)
    double screenScale;
    double screenOffsetX, screenOffsetY;

    const uint8_t *paletteData;

    bool redrawOnSprite;
public:
    const static uint64_t nibblesPerPixel;
    const static uint64_t bytesPerPixel;
    const static uint32_t vertexArrayLength;
public:
    VideoMemory(sf::RenderWindow&,
                const unsigned int,
                const unsigned int,
                const uint64_t);
    ~VideoMemory();

	string name();

    // Ajust escala e aspect ratio para a
    // a janela atual
    void resize();
    void transformMouse(uint16_t&, uint16_t&);

    // Fecha arquivos abertos
    void close();

    void render();
    void draw();

    uint64_t write(const uint64_t, const uint8_t*, const uint64_t);
    uint64_t read(const uint64_t, uint8_t*, const uint64_t);

    uint64_t size();
    uint64_t addr();

    // Chamado por paletteMemory quando o usu�rio troca a paleta
    void updatePalette(const uint8_t*);
    // Chamado por CartidgeMemory quando algum sprite muda
    void updateSpriteSheet(const uint64_t, const uint8_t*, const uint64_t);
protected:
    // Verifica se uma cor � transparente
    bool checkColor(uint8_t);
    uint8_t routeColor1(uint8_t);
    uint8_t routeColor2(uint8_t);
    // Opera��es nas VertexArrays utilizadas para
    // desenho na GPU
    void gpuLine(RenderBuffer &, sf::Color,
                 int16_t, int16_t,
                 int16_t, int16_t);
    void gpuRect(RenderBuffer &, sf::Color,
                 int16_t, int16_t,
                 int16_t, int16_t);
    void gpuTri(RenderBuffer &, sf::Color,
                int16_t, int16_t,
                int16_t, int16_t,
                int16_t, int16_t);
    void gpuQuad(RenderBuffer &, sf::Color,
                 int16_t, int16_t,
                 int16_t, int16_t,
                 int16_t, int16_t,
                 int16_t, int16_t);
    void gpuCircle(RenderBuffer &, sf::Color,
                   int16_t, int16_t, int16_t);
    void gpuFillCircle(RenderBuffer &, sf::Color,
                       int16_t, int16_t, int16_t);
    void gpuFillRect(RenderBuffer &, sf::Color,
                     int16_t, int16_t,
                     int16_t, int16_t);
    void gpuFillTri(RenderBuffer &, sf::Color,
                    int16_t, int16_t,
                    int16_t, int16_t,
                    int16_t, int16_t);
    void gpuFillQuad(RenderBuffer &, sf::Color,
                     int16_t, int16_t,
                     int16_t, int16_t,
                     int16_t, int16_t,
                     int16_t, int16_t);
    void gpuSprite(RenderBuffer &, sf::Color,
                   int16_t, int16_t,
                   int16_t, int16_t,
                   int16_t, int16_t);
    void execGpuCommand(uint8_t*);
private:
    // Helpers para extrair argumentos de um comando
    // da GPU
    int16_t next16Arg(uint8_t*&);
    uint8_t next8Arg(uint8_t*&);
    string nextStrArg(uint8_t*&);
    // Gera cores a partir de indices, paletas ou tempo
    sf::Color time2Color(uint32_t);
    sf::Color spriteTime2Color(uint8_t, uint32_t);
    sf::Color index2Color(uint8_t);
    sf::Color pal2Color(uint8_t);
    // Desenho do timing da CPU
    void drawCpuTiming(uint32_t, uint64_t, uint64_t);
    void clearCpuTiming();
    // GIFs
    bool startCapturing(const string&);
    bool captureFrame();
    bool stopCapturing();
    ColorMapObject* getColorMap();
};

#endif /* VIDEO_MEMORY_H */
