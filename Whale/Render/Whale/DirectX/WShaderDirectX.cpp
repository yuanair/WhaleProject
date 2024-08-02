//
// Created by admin on 2024/7/16.
//

#include "WShaderDirectX.hpp"
#include "WRendererDirectX.hpp"

namespace Whale::DirectX
{
	
	Bool WShaderDirectX::CreateFromFile(const Whale::FShaderArg &arg) noexcept
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
			FDebug::Log<CharA>(Error, TagA, "unknown shader type [" + target + "]");
			return false;
		}
		FResult hr = D3DCompileFromFile(
			arg.m_fileName.CStr(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, arg.entryPoint.CStr(), target.CStr(),
			compileFlags, 0,
			m_pShader.ReleaseAndGetAddressOf(), pErrorMsgs.ReleaseAndGetAddressOf()
		);
		hr.SetIsThrowIfFailedAtDestructTime(false);
		if (hr.IsFailed())
		{
			if (!pErrorMsgs) THROW_IF_FAILED(hr);
			auto buffer = reinterpret_cast<const char *>(pErrorMsgs->GetBufferPointer());
			FDebug::Log<CharA>(
				Error,
				TagA, "\n" + target + " shader error: \n" + buffer
			);
			return false;
		}
		
		return true;
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
	
	void WShaderDirectX::OnResourceDestroy() noexcept
	{
		m_pShader.Reset();
	}
	
	
} // Whale