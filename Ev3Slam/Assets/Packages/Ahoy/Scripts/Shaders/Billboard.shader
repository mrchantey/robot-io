Shader "Ahoy/Billboard"
{
  Properties{
 
    _Radius ("Radius",Range(0,1)) = 0.1
    _Color ("Color",Color) = (1,1,1,1)
  }
  SubShader{
    Tags{"Queue"="Transparent+1"} 
    ZWrite Off

    Blend SrcAlpha OneMinusSrcAlpha

    Pass
    {
      CGPROGRAM

      #pragma vertex vert
      #pragma geometry geom
      #pragma fragment frag

      #include "UnityCG.cginc"
      #include "Utility.cginc"

      struct appdata{
        float4 pos: POSITION;
        // float4 color: TANGENT;
      };

      struct v2g{
        float4 pos: SV_POSITION;
      };

      struct g2f{
        float4 pos: SV_POSITION;
        float2 uv: TEXCOORD0;
      };

      v2g vert (appdata v){ 
        v2g o;
        o.pos = v.pos;
        // o.color = v.color;
        return o;
      }

      float _Radius;


      [maxvertexcount(4)]
      void geom(point v2g IN[1], inout TriangleStream<g2f> triStream){

          float screenScale = GetScreenScale(IN[0].pos,_Radius);          
          float scale = screenScale;

          float4 verts[4];
          WorldPoint2ClipBillboard(IN[0].pos, scale, verts);

          g2f OUT;
          // OUT.color = IN[0].color;
          OUT.pos = verts[0];
          OUT.uv = float2(0,1);
          triStream.Append(OUT);

          OUT.pos = verts[1];
          OUT.uv = float2(1,1);
          triStream.Append(OUT);
          
          OUT.pos = verts[2];
          OUT.uv = float2(0,0);
          triStream.Append(OUT);
          
          OUT.pos = verts[3];
          OUT.uv = float2(1,0);
          triStream.Append(OUT);
      }

    fixed4 _Color;

      fixed4 frag(g2f i): SV_TARGET{
          return _Color;
          // return fixed4(i.color.rgb,a);
      }

      ENDCG

    }



  }




}