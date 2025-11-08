#version 330 core
layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 texUV;

out vec2 TexCoordinates;

uniform sampler2D texture0;
uniform mat4 projection;
uniform mat4 model;
uniform vec4 uvRegion;

void main() {
    vec2 atlasSize = vec2(textureSize(texture0, 0));
    vec2 uvMin = uvRegion.xy / atlasSize;
    vec2 uvMax = (uvRegion.xy + uvRegion.zw) / atlasSize;
    TexCoordinates = mix(uvMin, uvMax, texUV);
    gl_Position = projection * model * vec4(aPos, 0.0, 1.0);
}