#shader vertex
#version 430 core
layout(location = 0) in vec3 a_Position;

uniform mat4 u_View;
uniform mat4 u_Transform;

void main()
{
    gl_Position = u_View * u_Transform * vec4(a_Position, 1.0);
}

#shader fragment
#version 430 core
layout(location = 0) out vec4 o_Color;

uniform vec4 u_Color;
void main()
{
    o_Color = u_Color;
}
