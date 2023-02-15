Shader "Hidden/SinCity"
{
    Properties
    {
        _MainTex ("Texture", 2D) = "white" {}
        _Tester("Tester", Vector) = (0,0,0,0)
        _SaturatationPow("Saturation Power", Int) = 5
        _HueSelection("Hue Selection", Range(0,1)) = 0
        _HueSpread("Hue Spread", Range(0,1)) = 0.1
    }
    SubShader
    {
        // No culling or depth
        Cull Off ZWrite Off ZTest Always

        Pass
        {
            CGPROGRAM
            #pragma vertex vert
            #pragma fragment frag

            #include "UnityCG.cginc"

            struct appdata
            {
                float4 vertex : POSITION;
                float2 uv : TEXCOORD0;
            };

            struct v2f
            {
                float2 uv : TEXCOORD0;
                float4 vertex : SV_POSITION;
            };

            float3 RGBToHSV(float3 c)
            {
                float4 K = float4(0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);
                float4 p = lerp(float4(c.bg, K.wz), float4(c.gb, K.xy), step(c.b, c.g));
                float4 q = lerp(float4(p.xyw, c.r), float4(c.r, p.yzx), step(p.x, c.r));
                float d = q.x - min(q.w, q.y);
                float e = 1.0e-10;
                return float3(abs(q.z + (q.w - q.y) / (6.0 * d + e)), d / (q.x + e), q.x);
            }

            v2f vert (appdata v)
            {
                v2f o;
                o.vertex = UnityObjectToClipPos(v.vertex);
                o.uv = v.uv;
                return o;
            }

            sampler2D _MainTex;
            float4 _Tester;
            int _SaturatationPow;
            float _HueSelection;
            float _HueSpread;

            fixed4 frag (v2f i) : SV_Target
            {
                fixed4 col = tex2D(_MainTex, i.uv);
                float3 hsv = RGBToHSV(col.rgb);
                // just invert the colors
                float c = (col.r + col.g + col.b) / 3;

                float blend = max(hsv.g - _Tester.g, 0.0);

                float hueBlend = max((_HueSelection - (hsv.r - _HueSpread)),0) *
                    max((hsv.r + _HueSpread - _HueSelection),0) * 2;

                blend = blend * hueBlend;

                blend = pow(1-blend, _SaturatationPow);
                blend = 1 - blend;

                return col * (blend) + fixed4(c, c, c, 1) * (1 - blend);
            }
            ENDCG
        }
    }
}
