

struct LightColor
{
    float4 diffuse;
    float4 specular;
    float4 ambient;
};

struct LightAttribute
{
    LightColor color;
    float4 position;
    float4 direction;
    
    int type;
    float radius;
    float angle;
    int padding;
};

//Vector4 diffuse;
//Vector4 specular;
//Vector4 ambient;
//Vector4 position;
//Vector4 direction;

//enums::eLightType type;
//float radius;
//float angle;
//int padding;

