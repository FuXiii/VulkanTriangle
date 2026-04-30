#version 450 core
layout(push_constant) uniform PushConstantData
{
    float scale;
}
myData;

layout(location = 0) out vec3 color;
void main()
{
    float scale = myData.scale;
    vec2 vertex_pos = vec2(0, 0);

    if (gl_VertexIndex == 0)
    {
        vertex_pos = vec2(0.0, -0.5);
        color = vec3(1, 0, 0);
    }
    else if (gl_VertexIndex == 1)
    {
        vertex_pos = vec2(0.5, 0.5);
        color = vec3(0, 1, 0);
    }
    else if (gl_VertexIndex == 2)
    {
        vertex_pos = vec2(-0.5, 0.5);
        color = vec3(0, 0, 1);
    }

    gl_Position = vec4(vertex_pos * scale, 0.0f, 1.0f);
}