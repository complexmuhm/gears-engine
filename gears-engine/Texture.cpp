#include "Texture.h"
#include <d3d11.h>
#include <dxgi.h>
#include "Exceptions.h"

Texture::Texture(D3DGFX& gfx, const std::string& filename)
	: Bindable(gfx)
{
	HRESULT result;

	// load and decode png file and store it in the out vector 
	std::vector<unsigned char> filebuffer, out;
	loadFile(filebuffer, filename);
	unsigned long width, height;
	int error_code = decodePNG(out, width, height, filebuffer.data(), filebuffer.size());
	if (error_code != 0)
	{
		throw EXCEPTION("Couldn't open texture file \"" + filename + "\".");
	}

	CD3D11_TEXTURE2D_DESC tex2d_desc = {};
	tex2d_desc.Width = width;
	tex2d_desc.Height = height;
	tex2d_desc.MipLevels = 1u; // TODO: check out what this actually means
	tex2d_desc.ArraySize = 1u;
	tex2d_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	tex2d_desc.SampleDesc.Count = 1u;
	tex2d_desc.SampleDesc.Quality = 0u;
	tex2d_desc.Usage = D3D11_USAGE_DEFAULT;
	tex2d_desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	tex2d_desc.CPUAccessFlags = 0u;
	tex2d_desc.MiscFlags = 0u;

	D3D11_SUBRESOURCE_DATA data = {};
	data.pSysMem = out.data();
	data.SysMemPitch = width * sizeof(unsigned char) * 4; //4 chars define one pixel

	wrl::ComPtr<ID3D11Texture2D> texture2d;
	result = get_device()->CreateTexture2D(&tex2d_desc, &data, &texture2d);
	D3D_EXCEPTION(result);

	D3D11_SHADER_RESOURCE_VIEW_DESC srv_desc = {};
	srv_desc.Format = tex2d_desc.Format;
	srv_desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srv_desc.Texture2D.MostDetailedMip = 0u;
	srv_desc.Texture2D.MipLevels = -1;
	result = get_device()->CreateShaderResourceView(texture2d.Get(), &srv_desc, &texture);

}

void Texture::bind()
{
	get_device_context()->PSSetShaderResources(0u, 1u, texture.GetAddressOf());
}
