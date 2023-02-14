using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[ExecuteInEditMode]
public class CamerControll : MonoBehaviour
{
    public EImageEffectType mu_type;
    public Texture mu_overlayTex;
    public Vector4 mu_tester;
    public int mu_colorPower = 5;
    [Range(0, 1)]
    public float mu_hue = 0;
    [Range(0,1)]
    public float mu_hueSpread = 0.1f;
    public ComputeShader mu_computeShader;
    //public string mu_ShaderName;
    Material mi_blitMaterial;
    int mi_testerID;
    int mi_colorPowerID;
    int mi_hueSelectionID;
    int mi_hueSpreadID;
    bool mi_useImageEffect = true;
    RenderTexture mi_computeResult;

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
        mi_colorPowerID = Shader.PropertyToID("_SaturatationPow");
        mi_hueSelectionID = Shader.PropertyToID("_HueSelection");
		mi_hueSpreadID = Shader.PropertyToID("_HueSpread");
	}

    // Update is called once per frame
    void Update()
    {
        if (!mi_blitMaterial)
            return;

        mi_blitMaterial.SetVector(mi_testerID, mu_tester);
        mi_blitMaterial.SetInt(mi_colorPowerID, mu_colorPower);
        mi_blitMaterial.SetFloat(mi_hueSelectionID, mu_hue);
        mi_blitMaterial.SetFloat(mi_hueSpreadID, mu_hueSpread);
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

	private void OnGUI()
	{
		if (GUILayout.Button($"{(mi_useImageEffect ? "hide" : "show")} Image Effects"))
        {
            mi_useImageEffect = !mi_useImageEffect;
        }
        if (mi_computeResult)
        {
            GUILayout.Box(mi_computeResult);
        }
        else
        {
            if (GUILayout.Button("Create Texture"))
            {
                mi_computeResult = new RenderTexture(512, 512, 0, RenderTextureFormat.ARGBFloat, RenderTextureReadWrite.Linear);
                mi_computeResult.enableRandomWrite = true;
                mi_computeResult.Create();

                int kernel = mu_computeShader.FindKernel("CSMain");
				mu_computeShader.SetTexture(kernel, "Result", mi_computeResult);

                mu_computeShader.Dispatch(kernel, 512 / 8, 512 / 8, 1);
            }
        }
	}
}
