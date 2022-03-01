#include "main.h"
#include "images.h"
#include "project_selection.h"
#include "codeoutput.h"
#include "xtcmenu.h"

int main(int, char**)
{
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, _T("Emilia Imgeui edator"), NULL };
    ::RegisterClassEx(&wc);

    HWND hwnd = ::CreateWindow(wc.lpszClassName, _T("BIGXTCMenu Edater {gone sexyal)"), WS_OVERLAPPEDWINDOW, 100, 100, 1600, 995, NULL, NULL, wc.hInstance, NULL);

    HWND hwd = GetConsoleWindow();
    ShowWindow(hwd, SW_HIDE);

    CreateDirectoryA("C:\\PERS0NA2EDITOR",NULL);

    RefreshConfigs();

//    if (g_Requests->MakeRequest("falconcheats.me", "2", REQUEST_GET) != "0.05")
 //   {
 //       MessageBox(NULL,"Новое обновление найдено, пожалуйста обновите ПО.\nЧенджлог всегда есть на GitHub.",NULL,MB_OK);
//
  //      ShellExecuteW(NULL, L"open", L"https://github.com/pers0na2/imgui-editor/releases", 0, 0, SW_SHOWNORMAL);
//
  //      exit(0);
  //  }

    if (!CreateDeviceD3D(hwnd))
    {
        CleanupDeviceD3D();
        ::UnregisterClass(wc.lpszClassName, wc.hInstance);
        return 1;
    }

    ::ShowWindow(hwnd, SW_SHOWDEFAULT);
    ::UpdateWindow(hwnd);

    //init

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX9_Init(g_pd3dDevice);


    //load pictures and fonts:)
    static const ImWchar ranges[] =
    {
        0x0020, 0x00FF, // Basic Latin + Latin Supplement
        0x0400, 0x044F, // Cyrillic
        0,
    };

    ImFontConfig cfg;
    cfg.OversampleH = 3;
    cfg.OversampleV = 1;

    pXtcMenu::LoadTextureFromMemory(g_pd3dDevice, (void*)xtclogoPNG, sizeof(xtclogoPNG), &LoadedImages::xtclogo.texture, &LoadedImages::xtclogo.w, &LoadedImages::xtclogo.h);
    pXtcMenu::LoadTextureFromMemory(g_pd3dDevice, (void*)penosPNG, sizeof(penosPNG), &LoadedImages::penisTab.texture, &LoadedImages::penisTab.w, &LoadedImages::penisTab.h);
    XtcFonts::tab_names = io.Fonts->AddFontFromMemoryTTF(orbitron, sizeof(orbitron), 15.0f, &cfg, ranges);
    XtcFonts::menu_font = io.Fonts->AddFontFromMemoryTTF(pMenuFont, sizeof(pMenuFont), 13.0f, &cfg, ranges);
    pXtcMenu::LoadTextureFromMemory(g_pd3dDevice, (void*)targetPNG, sizeof(targetPNG), &LoadedImages::tabIcons[0].texture, &LoadedImages::tabIcons[0].w, &LoadedImages::tabIcons[0].h);
    pXtcMenu::LoadTextureFromMemory(g_pd3dDevice, (void*)customerPNG, sizeof(customerPNG), &LoadedImages::tabIcons[1].texture, &LoadedImages::tabIcons[1].w, &LoadedImages::tabIcons[1].h);
    pXtcMenu::LoadTextureFromMemory(g_pd3dDevice, (void*)visionPNG, sizeof(visionPNG), &LoadedImages::tabIcons[2].texture, &LoadedImages::tabIcons[2].w, &LoadedImages::tabIcons[2].h);
    pXtcMenu::LoadTextureFromMemory(g_pd3dDevice, (void*)scanningPNG, sizeof(scanningPNG), &LoadedImages::tabIcons[3].texture, &LoadedImages::tabIcons[3].w, &LoadedImages::tabIcons[3].h);
    pXtcMenu::LoadTextureFromMemory(g_pd3dDevice, (void*)misctabPNG, sizeof(misctabPNG), &LoadedImages::tabIcons[4].texture, &LoadedImages::tabIcons[4].w, &LoadedImages::tabIcons[4].h);
    pXtcMenu::LoadTextureFromMemory(g_pd3dDevice, (void*)settingsPNG, sizeof(settingsPNG), &LoadedImages::tabIcons[5].texture, &LoadedImages::tabIcons[5].w, &LoadedImages::tabIcons[5].h);
    pXtcMenu::LoadTextureFromMemory(g_pd3dDevice, (void*)web_programmingPNG, sizeof(web_programmingPNG), &LoadedImages::tabIcons[6].texture, &LoadedImages::tabIcons[6].w, &LoadedImages::tabIcons[6].h);

    ImVec4 clear_color = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);

    //big Window loop
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));
    while (msg.message != WM_QUIT)
    {
        if (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            continue;
        }

        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        pXtcMenu::Render();

        ImGui::EndFrame();
        g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
        g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
        g_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);
        D3DCOLOR clear_col_dx = D3DCOLOR_RGBA((int)(clear_color.x * 255.0f), (int)(clear_color.y * 255.0f), (int)(clear_color.z * 255.0f), (int)(clear_color.w * 255.0f));
        g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, clear_col_dx, 1.0f, 0);
        if (g_pd3dDevice->BeginScene() >= 0)
        {
            ImGui::Render();
            ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
            g_pd3dDevice->EndScene();
        }
        HRESULT result = g_pd3dDevice->Present(NULL, NULL, NULL, NULL);

        if (result == D3DERR_DEVICELOST && g_pd3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
            ResetDevice();
    }

    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    ::DestroyWindow(hwnd);
    ::UnregisterClass(wc.lpszClassName, wc.hInstance);

    return 0;
}
