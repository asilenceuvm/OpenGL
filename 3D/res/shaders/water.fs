#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D image;
uniform vec3 spriteColor;
uniform float time;
// Maximum number of cells a ripple can cross.
#define MAX_RADIUS 2

// Set to 1 to hash twice. Slower, but less patterns.
#define DOUBLE_HASH 0

#define HASHSCALE1 .1031
#define HASHSCALE3 vec3(.1031, .1030, .0973)

float hash12(vec2 p)
{
	vec3 p3  = fract(vec3(p.xyx) * HASHSCALE1);
    p3 += dot(p3, p3.yzx + 19.19);
    return fract((p3.x + p3.y) * p3.z);
}

vec2 hash22(vec2 p)
{
	vec3 p3 = fract(vec3(p.xyx) * HASHSCALE3);
    p3 += dot(p3, p3.yzx+19.19);
    return fract((p3.xx+p3.yz)*p3.zy);

}
void main() {   
    float resolution = 10. * exp2(1920);
	vec2 uv = TexCoords.xy / 1080 * resolution;
    vec2 p0 = floor(uv);

    float circles = 0.;
    for (int j = -MAX_RADIUS; j <= MAX_RADIUS; ++j)
    {
        for (int i = -MAX_RADIUS; i <= MAX_RADIUS; ++i)
        {
			vec2 pi = p0 + vec2(i, j);
            #if DOUBLE_HASH
            vec2 h = hash22(pi);
            #else
            vec2 h = pi;
            #endif
            vec2 p = pi + hash22(h);

            float t = fract(0.3*time + hash12(h));
            float d = length(p - uv) - (float(MAX_RADIUS) + 1.)*t;

            circles += (1. - t) * (1. - t)
                * mix(sin(31.*d) * 0.5 + 0.5, 1., 0.1)
                * smoothstep(-0.6, -0.3, d)
                * smoothstep(0., -0.3, d);
        }
    }

    float intensity = mix(0.01, 0.15, smoothstep(0.1, 0.6, abs(fract(0.05*time + 0.5)*2.-1.)));
    vec3 n = vec3(dFdx(circles), dFdy(circles), 0.);
    n.z = sqrt(1. - dot(n.xy, n.xy));
    vec3 texcolor = vec3(TexCoords, uv/resolution - intensity*n.xy); 
	// + 5.*pow(clamp(dot(n, normalize(vec3(1., 0.7, 0.5))), 0., 1.), 6.)
	color = vec4(texcolor, 1.0);
}
    //color = vec4(spriteColor, 1.0) * texture(image, TexCoords);