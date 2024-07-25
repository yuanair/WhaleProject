//
// Created by admin on 2024/7/16.
//

#include "WShaderDirectX.hpp"
#include "WRendererDirectX.hpp"

namespace Whale::DirectX
{
	
	Bool WShaderDirectX::OnGPUCreate(const Whale::FShaderArg &arg) noexcept
	{
		Microsoft::WRL::ComPtr<ID3DBlob> pErrorMsgs;
#if defined(_DEBUG)
		uint32 compileFlags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#else
		uint32 compileFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#endif
		StringA target;
		if (!GetTarget(target, arg.m_type))
		{
			FDebug::LogError(TagA, "unknown shader type [" + target + "]");
			return false;
		}
		Win32::FResult hr = D3DCompileFromFile(
			arg.m_fileName.CStr(), nullptr, nullptr, arg.entryPoint.CStr(), target.CStr(), compileFlags, 0,
			m_pShader.ReleaseAndGetAddressOf(), pErrorMsgs.ReleaseAndGetAddressOf()
		);
		if (hr.IsFailed())
		{
			if (!pErrorMsgs) THROW_IF_FAILED(hr);
			FDebug::LogError(
				TagA, target + " shader error: " + reinterpret_cast<const char *>(pErrorMsgs->GetBufferPointer()));
			return false;
		}
		
		return true;
	}
	
	void WShaderDirectX::OnGPUDestroy() noexcept
	{
	
	}
	
	void WShaderDirectX::OnEnable() noexcept
	{
	
	}
	
	void WShaderDirectX::OnDisable() noexcept
	{
	
	}
	
	Bool WShaderDirectX::IsGPUResourceCreated() const noexcept
	{
		return m_pRenderer;
	}
	
	
} // Whale