#version 330 core

in vec4 worldPosition;
in vec3 worldNormal;

out vec4 out_Color;

void main(void){

    vec3 lightPosition = vec3(0.0,0.0,0.0); //Point Light position

    vec3 lightToVector = normalize(lightPosition - worldPosition.xyz);
    vec3 normal = normalize(worldNormal);

    float dotProduct = max(dot(lightToVector, normal), 0.0);
    vec4 diffuse = dotProduct * vec4(0.385, 0.647, 0.812, 1.0);

    vec3 viewDir = normalize(-worldPosition.xyz); 
    vec3 reflectDir = reflect(-lightToVector, normal);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 4.0); 
    vec4 specular = spec * vec4(1.0, 1.0, 1.0, 1.0);

    vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);

    vec4 objectColor = vec4(0.385, 0.647, 0.812, 1.0);
    
    //out_Color = ambient + diffuse;
    out_Color = ambient + (diffuse * objectColor) + specular;
}