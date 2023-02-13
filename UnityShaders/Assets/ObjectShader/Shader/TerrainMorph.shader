Shader "Custom/TerrainMorph"
{
    Properties
    {
        _Color ("Color", Color) = (1,1,1,1)
        _MainTex ("Albedo (RGB)", 2D) = "white" {}
        _Glossiness ("Smoothness", Range(0,1)) = 0.5
        _Metallic ("Metallic", Range(0,1)) = 0.0
        _HeightMap ("Height Map(R)", 2D) = "black" {}
        _Extrusion("Height Map effect", Range(-10,10)) = 1
        _Tess("Tesselation Level", Range(1,20)) = 0
    }
    SubShader
    {
        Tags { "RenderType"="Opaque" }
        LOD 200

        CGPROGRAM
        // Physically based Standard lighting model, and enable shadows on all light types
        //#pragma surface surf Standard fullforwardshadows vertex:vert tessellate:tess
        //#pragma surface surf Standard fullforwardshadows vertex:vert tessellate:tessDistance
        #pragma surface surf Standard fullforwardshadows vertex:vert tessellate:tessEdge

        // Use shader model 3.0 target, to get nicer looking lighting
        #pragma target 4.6
        #include "Tessellation.cginc"


        struct Input
        {
            float2 uv_MainTex;
        };

        sampler2D _MainTex;
        sampler2D _HeightMap;
        half _Glossiness;
        half _Metallic;
        fixed4 _Color;
        float _Extrusion;
        float _Tess;

        // Add instancing support for this shader. You need to check 'Enable Instancing' on materials that use the shader.
        // See https://docs.unity3d.com/Manual/GPUInstancing.html for more information about instancing.
        // #pragma instancing_options assumeuniformscaling
        UNITY_INSTANCING_BUFFER_START(Props)
            // put more per-instance properties here
        UNITY_INSTANCING_BUFFER_END(Props)


        void vert(inout appdata_full v) 
        {
            v.vertex.y =  v.vertex.y + _Extrusion * tex2Dlod(_HeightMap, float4(v.texcoord.xy, 0,0));
        }

        float4 tess()
        {
            return _Tess;
        }

        float4 tessDistance(appdata_full v0, appdata_full v1, appdata_full v2) {
            float minDist = 0.5;
            float maxDist = 5.0;
            return UnityDistanceBasedTess(v0.vertex, v1.vertex, v2.vertex, minDist, maxDist, _Tess);
        }

        float4 tessEdge(appdata_full v0, appdata_full v1, appdata_full v2)
        {
            return UnityEdgeLengthBasedTess(v0.vertex, v1.vertex, v2.vertex, _Tess);
        }

        void surf (Input IN, inout SurfaceOutputStandard o)
        {
            // Albedo comes from a texture tinted by color
            fixed4 c = tex2D (_MainTex, IN.uv_MainTex) * _Color;
            o.Albedo = c.rgb;
            // Metallic and smoothness come from slider variables
            o.Metallic = _Metallic;
            o.Smoothness = _Glossiness;
            o.Alpha = c.a;
        }
        ENDCG
    }
    FallBack "Diffuse"
}
