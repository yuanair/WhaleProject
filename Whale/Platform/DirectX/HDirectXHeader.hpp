//
// Created by admin on 2024/7/11.
//

#pragma once

#include <directx/d3dx12.h>
#include <dxgi1_6.h>
#include <d3dcompiler.h>
#include <dwrite_3.h>
#include <initguid.h>

#include <wrl/client.h>

#include "Whale/Platform/Win32/FResult.hpp"

#define THROW_IF_FAILED(hr) (Whale::Win32::FResult{hr}.ThrowIfFailed(""))

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "d3dCompiler.lib")


namespace Whale::DirectX
{
	constexpr const CharA TagA[] = "Whale::DirectX";
	constexpr const CharW TagW[] = L"Whale::DirectX";
	
}
