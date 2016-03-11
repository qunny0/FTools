#version 330

in vec2 TexCoord0;

out vec4 FragColor;

uniform sampler2D gSampler;

void main()
{
    FragColor = texture2D(gSampler, TexCoord0.xy) * vec4(0.4, 0.3, 0.5, 1.0);
}