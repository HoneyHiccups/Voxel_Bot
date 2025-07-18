#version 330

out vec4 finalColor;

void main()
{
    
    vec2 uv = gl_FragCoord.xy / vec2(800.0, 450.0); 
    finalColor = vec4(uv.x, uv.y, 0.5, 1.0);
}