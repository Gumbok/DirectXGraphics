#pragma once

struct SDirectXSettings
{
	// Device Swap Chain	- sorgt für Austausch des Bildes
	ID3D11Device* m_device = nullptr;						// Softwarerepräsentation der Grafikkarte
	ID3D11DeviceContext* m_deviceContext = nullptr;			// Direkter zugriff auf die Grafikkarte
	IDXGISwapChain* m_swapChain = nullptr;

	// Render Target View - hier wird reingezeichnet
	ID3D11RenderTargetView* m_renderTargetView = nullptr;

	// Depth Stencil
	ID3D11Texture2D* m_depthStencilBuffer = nullptr;
	ID3D11DepthStencilView* m_depthStencilView = nullptr;
	ID3D11DepthStencilState* m_depthStencilState = nullptr;
	ID3D11RasterizerState* m_rasterrizerState = nullptr;

	D3D11_VIEWPORT m_viewPort;
};
