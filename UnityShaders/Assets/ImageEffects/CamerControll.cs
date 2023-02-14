using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[ExecuteInEditMode]
public class CamerControll : MonoBehaviour
{
    public EImageEffectType mu_type;
    public Texture mu_overlayTex;
    public Vector4 mu_tester;
    //public string mu_ShaderName;
    Material mi_blitMaterial;
    int mi_testerID;
    Dictionary<EImageEffectType, string> mi_typeToShaderName = new Dictionary<EImageEffectType, string>()
    {
        { EImageEffectType.SIMPLE, "Hidden/SimpleImageEffect"},
        { EImageEffectType.SIN_CITY, "Hidden/SinCity"}
	};

    public enum EImageEffectType
    {
        SIMPLE,
        SIN_CITY,
	}

    // Start is called before the first frame update
    void Start()
    {
        mi_testerID = Shader.PropertyToID("_Tester");
	}

    // Update is called once per frame
    void Update()
    {
        mi_blitMaterial.SetVector(mi_testerID, mu_tester);   
    }

    void OnRenderImage(RenderTexture _src, RenderTexture _dst)
    {
        if (!mi_blitMaterial)
        {
            mi_blitMaterial = new Material(Shader.Find(mi_typeToShaderName[mu_type]));
            mi_blitMaterial.SetTexture(Shader.PropertyToID("_AdditionalTex"), mu_overlayTex);
        }
        else
        { 
            Graphics.Blit(_src, _dst, mi_blitMaterial);
        }
    }
}
