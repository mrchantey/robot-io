Shader "Ahoy/Wireframe"
{
    Properties
    {
        _Color ("Color",Color) = (0,1,1,0.5)
        _WireSize ("Wire Cutoff",Range(0.5,1)) = 0.9
        _WireSmoothness ("Wire Smoothness",Range(0,0.2)) = 0.001
    }
    SubShader
    {
        Tags { "Queue"="Transparent" "RenderType"="Transparent"}
        ZWrite Off
        Blend SrcAlpha OneMinusSrcAlpha

        Pass
        {
        Cull back
            CGPROGRAM

            #pragma vertex vert
            #pragma fragment frag
            #pragma geometry geom
            #pragma target 4.0

            #include "UnityCG.cginc"

            struct appdata
            {
                float2 uv : TEXCOORD0;
                float3 normal : NORMAL;
                float4 vertex : POSITION;
            };

            struct v2g
            {
                float2 uv : TEXCOORD0;
                float3 normal : NORMAL;
                float4 vertex : SV_POSITION;
            };
            struct g2f
            {
                float2 uv : TEXCOORD0;
                float3 bary : TEXCOORD1;
                float3 normal : NORMAL;
                float4 vertex : SV_POSITION;
            };

            v2g vert (appdata v)
            {
                v2g o;
                // o.vertex = UnityObjectToClipPos(v.vertex);
                o.vertex = v.vertex;
                o.uv = v.uv;
                o.normal = v.normal;
                return o;
            }


            [maxvertexcount(3)]
            void geom(triangle v2g IN[3], inout TriangleStream<g2f> triStream)
            {
                g2f OUT;

                int iA,iB,iC;//iC = hypotenuse vert

                float4 dirAB = IN[1].vertex - IN[0].vertex;
                float4 dirAC = IN[2].vertex - IN[0].vertex;
                float4 dirBC = IN[2].vertex - IN[1].vertex;
                
                float lenAB = length(dirAB.xyz);
                float lenAC = length(dirAC.xyz);
                float lenBC = length(dirBC.xyz);
                
                if(lenAB > lenAC && lenAB > lenBC){
                    iC = 2;
                    iA = 0;
                    iB = 1;
                }else if(lenAC > lenBC){
                    iC = 1;
                    iA = 2;
                    iB = 0;
                }else{
                    iC = 0;
                    iA = 1;
                    iB = 2;
                }
                
                float3 normal = normalize(cross(dirAB.xyz,dirAC.xyz));
                OUT.normal = normal;
                IN[0].vertex = UnityObjectToClipPos(IN[0].vertex);
                IN[1].vertex = UnityObjectToClipPos(IN[1].vertex);
                IN[2].vertex = UnityObjectToClipPos(IN[2].vertex);
                // float3 normal = IN[2].vertex - IN[0].vertex
            
                OUT.uv = IN[iA].uv;
                OUT.bary = float3(1,0,0);
                // OUT.normal = IN[0].normal;
                OUT.vertex = IN[iA].vertex;
                triStream.Append(OUT);
                OUT.uv = IN[iB].uv;
                OUT.bary = float3(0,1,0);
                // OUT.normal = IN[1].normal;
                OUT.vertex = IN[iB].vertex;
                triStream.Append(OUT);
                OUT.uv = IN[iC].uv;
                OUT.bary = float3(1,1,0);
                // OUT.normal = IN[2].normal;
                OUT.vertex = IN[iC].vertex;
                triStream.Append(OUT);
            }


            fixed4 _Color;
            float _WireSize;
            float _WireSmoothness;

            fixed4 frag (g2f i) : SV_Target
            {
                float baryMax = max(max(i.bary.x,i.bary.y),i.bary.z);
                float wireA = smoothstep(_WireSize,_WireSize + _WireSmoothness,baryMax);
                float a = min(wireA,_Color.a);
                fixed4 color = fixed4(_Color.xyz,a);
                return color;
            }
            ENDCG
        }
    }
}
 