#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D textureRGB;
uniform sampler2D textureY;
uniform sampler2D textureU;
uniform sampler2D textureV;

void main()
{
    highp float y = texture2D(textureY, TexCoord).r;
    highp float u = texture2D(textureU, TexCoord).r - 0.5;
    highp float v = texture2D(textureV, TexCoord).r - 0.5;
    highp float r = y +             1.402 * v;
    highp float g = y - 0.344 * u - 0.714 * v;
    highp float b = y + 1.772 * u;

    FragColor = vec4(r,g,b,1.0);
    //FragColor = texture2D(textureY, TexCoord);
}