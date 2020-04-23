#version 330 core

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shine;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

out vec4 FragColor;
  
in vec3 Normal;
in vec3 FragPos;

uniform Material material;
uniform Light light;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main() {
    //ambient
    vec3 ambient = light.ambient * material.ambient;

    //diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * (diff * material.diffuse);

    //specular
    vec3 viewDir = normalize(viewPos- FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shine);
    vec3 specular = light.specular * material.specular * spec;

    //total
    vec3 final = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(final, 1.0);
}