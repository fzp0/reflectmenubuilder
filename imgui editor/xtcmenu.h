#pragma once
#include <string>
#include <array>
#include <d3d9.h>
#include <d3dx9tex.h>
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "imgui/imgui_impl_dx9.h"
#include "imgui/imgui_impl_win32.h"


namespace pXtcMenu
{

	void Render();
	bool LoadTextureFromMemory(LPDIRECT3DDEVICE9 pDevice, void* data, size_t datasize, PDIRECT3DTEXTURE9* out_texture, int* out_width, int* out_height);
};