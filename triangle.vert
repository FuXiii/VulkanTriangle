#version 450 core
layout(location = 0) out vec3 color;
void main()
{
    if (gl_VertexIndex == 0)
    {
        gl_Position = vec4(0.0, -0.5, 0.0f, 1.0f);
        color = vec3(1, 0, 0);
    }
    else if (gl_VertexIndex == 1)
    {
        gl_Position = vec4(0.5, 0.5, 0.0f, 1.0f);
        color = vec3(0, 1, 0);
    }
    else if (gl_VertexIndex == 2)
    {
        gl_Position = vec4(-0.5, 0.5, 0.0f, 1.0f);
        color = vec3(0, 0, 1);
    }
}