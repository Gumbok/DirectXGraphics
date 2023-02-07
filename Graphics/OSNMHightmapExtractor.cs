using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;
using UnityEditor.PackageManager.UI;
using System.IO;

public class OSNMHightmapExtractor : EditorWindow
{
	Texture2D m_sourceTex;
	Texture2D mi_destinationTex;
	float m_multiplier = 5;

	[MenuItem("Window/Window OSNM Extractor")]
	public static void ShowWindow()
	{
		OSNMHightmapExtractor window = EditorWindow.GetWindow<OSNMHightmapExtractor>();
		window.Show();
	}

	private void OnGUI()
	{
		m_sourceTex = (Texture2D)EditorGUILayout.ObjectField("Source Tex",m_sourceTex, typeof(Texture2D), false);
		m_multiplier = EditorGUILayout.FloatField("multiplier", m_multiplier);
		if (m_sourceTex != null)
		{
			if (GUILayout.Button("fire"))
			{
				mi_destinationTex = CreateOSNMFromHeight(m_sourceTex);
			}
			if (mi_destinationTex != null && GUILayout.Button("Save Normalmap"))
			{
				string path = EditorUtility.SaveFilePanel("save osnmnormal map", ".", "normalmap.png", "png");
				if (!string.IsNullOrEmpty(path))
				{
					byte[] data = mi_destinationTex.EncodeToPNG();
					File.WriteAllBytes(path, data);
				}
			}

			GUILayout.Box(mi_destinationTex);
		}

		
	}

	private Texture2D CreateOSNMFromHeight(Texture2D _source)
	{
		Texture2D t = new Texture2D(_source.width, _source.height);

		Vector3 dir;
		float up, left, down, right, current;
		for (int y = 0; y < _source.height; y++)
		{
			for (int x = 0; x < _source.width; x++)
			{
				up = left = down = right = current = _source.GetPixel(x, y).r;
				if (y < _source.height - 1)
					up = _source.GetPixel(x, y + 1).r;
				if (x > 0)
					left = _source.GetPixel(x - 1, y).r;
				if (y > 0)
					down = _source.GetPixel(x, y - 1).r;
				if (x > _source.width - 1)
					right = _source.GetPixel(x + 1, y).r;

				dir = new Vector3(0, 1, 0);
				dir.x = (right - left) * m_multiplier;
				dir.z = (down - up) * m_multiplier;
				dir = dir.normalized;

				t.SetPixel(x, y, new Color((dir.x + 1) / 2, (dir.y + 1) / 2, (dir.z + 1) / 2));
			}
		}

		t.Apply();
		return t;
	}
}
