//
// Created by admin on 2024/7/11.
//

#pragma once

#include <directx/d3dx12.h>
#include <dxgi1_6.h>
#include <d3dcompiler.h>
#include <dwrite_3.h>

#include <wrl/client.h>

#include "FDirectXResult.hpp"

#define THROW_IF_FAILED(hr) (Whale::FDirectXResult{hr}.ThrowIfFailed(""))

