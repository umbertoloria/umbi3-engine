#version 330 core

struct Light {
    vec3 ambient, diffuse, specular;
};

struct Attenuation {
    float constant, linear, quadratic;
};

struct DirectionalLight {
    Light light;
    vec3 direction;
};

struct PointLight {
    Light light;
    vec3 position;
    Attenuation attenuation;
};

struct CalculatedLight {
    vec3 ambient, diffuse, specular;
};

CalculatedLight calculateDirectionalLight(DirectionalLight dirLight, vec3 norm, vec3 fragPos, vec3 viewPos, float shininess) {
    CalculatedLight result;
    float diff = max(dot(-dirLight.direction, norm), 0);
    vec3 reflectDir = reflect(dirLight.direction, norm);
    vec3 viewDir = normalize(viewPos - fragPos);
    float spec = pow(max(dot(viewDir, reflectDir), 0), shininess);
    // float attenuation= dirLight.attenuation.constant + dirLight.attenuation.linear * distance + dirLight.attenuation.quadratic * distance * distance;
    result.ambient = dirLight.light.ambient;
    result.diffuse = dirLight.light.diffuse * diff;
    result.specular = dirLight.light.specular * spec;
    return result;
}

CalculatedLight calculatePointLight(PointLight pointLight, vec3 norm, vec3 fragPos, vec3 viewPos, float shininess) {
    CalculatedLight result;
    vec3 lightDir = normalize(fragPos - pointLight.position);
    float diff = max(dot(-lightDir, norm), 0);
    vec3 reflectDir = reflect(lightDir, norm);
    vec3 viewDir = normalize(viewPos - fragPos);
    float spec = pow(max(dot(viewDir, reflectDir), 0), shininess);
    // float attenuation= dirLight.attenuation.constant + dirLight.attenuation.linear * distance + dirLight.attenuation.quadratic * distance * distance;
    result.ambient = pointLight.light.ambient;
    result.diffuse = pointLight.light.diffuse * diff;
    result.specular = pointLight.light.specular * spec;
    return result;
}

in vec3 oColor;
in vec3 oNormal;
in vec3 oViewPosition;
in vec3 oFragPosition;

uniform DirectionalLight dirLight;
uniform bool enableDirLight;
uniform PointLight pointLight;
uniform bool enablePointLight;

out vec4 fragColor;

void main () {
    vec3 norm = normalize(oNormal);
    vec3 ambientChannel = vec3(0.0);
    vec3 diffuseChannel = vec3(0.0);
    vec3 specularChannel = vec3(0.0);

    if (enableDirLight) {
        CalculatedLight dirCL = calculateDirectionalLight(dirLight, norm, oFragPosition, oViewPosition, 128);
        ambientChannel += dirCL.ambient;
        diffuseChannel += dirCL.diffuse;
        specularChannel += dirCL.specular;
    }
    if (enablePointLight) {
        CalculatedLight pointCL = calculatePointLight(pointLight, norm, oFragPosition, oViewPosition, 128);
        ambientChannel += pointCL.ambient;
        diffuseChannel += pointCL.diffuse;
        specularChannel += pointCL.specular;
    }
    ambientChannel *= oColor;
    diffuseChannel *= oColor;
    specularChannel *= oColor;

    fragColor = vec4(ambientChannel + diffuseChannel + specularChannel, 1.0);
}