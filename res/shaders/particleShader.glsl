#shader vertex
#version 330 core
layout(location = 0) in vec3 a_Position;

uniform mat4 u_ViewProj;
uniform mat4 u_Transform;

void main()
{
    gl_Position = vec4(a_Position, 1.0);
}

#shader fragment
#version 330 core
layout(location = 0) out vec4 o_Color;

void main()
{
    o_Color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}
