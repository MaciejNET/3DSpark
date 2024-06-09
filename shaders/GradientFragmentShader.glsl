#version 410

uniform vec4 color1;
uniform vec4 color2;
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 cameraPos;
uniform bool isLightingEnabled;
uniform bool isShadingEnabled;

out vec4 FragColor;

in vec3 Normal;
in vec3 currentPos;
in float height;

void main()
{
    if (!isLightingEnabled)
    {
        FragColor = mix(color1, color2, height);
        return;
    }

    if (!isShadingEnabled)
    {
        FragColor = mix(color1, color2, height) * lightColor;
        return;
    }

    float ambient = 0.2f;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - currentPos);
    float diff = max(dot(norm, lightDir), 0.0);

    float specularStrength = 0.5f;
    vec3 viewDir = normalize(cameraPos - currentPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    float specular = specularStrength * spec;

    vec4 gradientColor = mix(color1, color2, height);

    FragColor = gradientColor * lightColor * (diff + ambient + specular);
}