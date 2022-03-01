#include "xtcmenu.h"
#include "images.h"


bool ImGui::Tab(const char* label, bool selected)
{
   
    ImGuiContext& g = *ImGui::GetCurrentContext();
    ImGuiWindow* window = g.CurrentWindow;
        if (window->SkipItems)
            return false;
    const ImGuiStyle& style = g.Style;
    const ImGuiID id = window->GetID(label);
    const ImVec2 label_size = CalcTextSize(label, NULL, true);
    ImVec2 pos = window->DC.CursorPos;
    ImVec2 size = CalcItemSize(ImVec2(75, 60), 50 + style.FramePadding.x, label_size.y + style.FramePadding.y);
    const ImRect bb(pos, ImVec2(pos.x + size.x, pos.y + size.y));
    ItemSize(size, style.FramePadding.y);
    if (!ItemAdd(bb, id))
        return false;
    bool hovered, held;
    bool pressed = ButtonBehavior(bb, id, &hovered, &held);
    if (pressed)
        MarkItemEdited(id);
    auto draw = GetWindowDrawList();
    const ImU32 col = GetColorU32((held && hovered) ? ImGuiCol_ButtonActive : hovered ? ImGuiCol_ButtonHovered : ImGuiCol_Button);
    float t = selected ? 1.0f : 0.0f;
    float ANIM_SPEED = 0.39f; // Bigger = Slower
    if (g.LastActiveId == g.CurrentWindow->GetID(label)) {
        float t_anim = ImSaturate(g.LastActiveIdTimer / ANIM_SPEED);
        t = selected ? (t_anim) : (0);
    }
    int a = int(t * 255);
    auto text_color = ImGui::GetColorU32(ImLerp(ImVec4(180 / 255.f, 180 / 255.f, 180 / 255.f, 180 / 255.f), ImVec4(0 / 255.f, 255 / 255.f, 128 / 255.f, 255.f / 255.f), t));
    draw->AddRectFilled(ImVec2(bb.Min.x, bb.Max.y - 2), bb.Max, ImColor(0, 255, 128, a));
    draw->AddText(ImVec2(pos.x + 75 / 2 - label_size.x / 2, pos.y + 30 - label_size.y / 2), text_color, label);
    IMGUI_TEST_ENGINE_ITEM_INFO(id, label, window->DC.LastItemStatusFlags);
    return pressed;
}

bool ImGui::TabAlt(ImageData image, bool selected, const char* bigid, ImVec2 min_offset, ImVec2 max_offset)
{

    ImGuiContext& g = *ImGui::GetCurrentContext();
    ImGuiWindow* window = g.CurrentWindow;
    if (window->SkipItems)
        return false;
    const ImGuiStyle& style = g.Style;
    const ImGuiID id = window->GetID(bigid);
    const ImVec2 label_size = { 75, 60 };
    ImVec2 pos = window->DC.CursorPos;
    ImVec2 size = CalcItemSize(ImVec2(75, 60), 50 + style.FramePadding.x, label_size.y + style.FramePadding.y);
    const ImRect bb(pos, ImVec2(pos.x + size.x, pos.y + size.y));
    ItemSize(size, style.FramePadding.y);
    if (!ItemAdd(bb, id))
        return false;
    bool hovered, held;
    bool pressed = ButtonBehavior(bb, id, &hovered, &held);
    if (pressed)
        MarkItemEdited(id);
    auto draw = GetWindowDrawList();
    const ImU32 col = GetColorU32((held && hovered) ? ImGuiCol_ButtonActive : hovered ? ImGuiCol_ButtonHovered : ImGuiCol_Button);
    float t = selected ? 1.0f : 0.0f;
    float ANIM_SPEED = 0.39f; // Bigger = Slower
    if (g.LastActiveId == g.CurrentWindow->GetID(bigid)) {
        float t_anim = ImSaturate(g.LastActiveIdTimer / ANIM_SPEED);
        t = selected ? (t_anim) : (0);
    }
    int a = int(t * 255);
    auto text_color = ImGui::GetColorU32(ImLerp(ImVec4(180 / 255.f, 180 / 255.f, 180 / 255.f, 180 / 255.f), ImVec4(0 / 255.f, 255 / 255.f, 128 / 255.f, 255.f / 255.f), t));
    draw->AddRectFilled(ImVec2(bb.Min.x, bb.Max.y - 2), bb.Max, ImColor(0, 255, 128, a));
    draw->AddImage(image.texture, ImVec2{ pos.x + min_offset.x, pos.y + min_offset.y }, {pos.x + 70.f + max_offset.x , pos.y + 60.f + max_offset.y}, { 0,0 }, { 1,1 }, text_color);
    //draw->AddText(ImVec2(pos.x + 75 / 2 - label_size.x / 2, pos.y + 30 - label_size.y / 2), text_color, label);
    IMGUI_TEST_ENGINE_ITEM_INFO(id, label, window->DC.LastItemStatusFlags);
    return pressed;
}


static int curtab = 0;
static float Fortesting = 10.f;
static int CurrentPenisSelection = 0;
static int CurrentVaginaSelection = 0;
static float EpicColor[4] = { 1.f,1.f,1.f,1.f };

void pXtcMenu::Render()
{
    auto& style = ImGui::GetStyle();

    style.WindowRounding = 3.f;
    style.WindowTitleAlign = { 0.5, 0.5 };
    style.WindowBorderSize = 0.f;
    style.FrameBorderSize = 0.f;
    style.WindowPadding = ImVec2{ 0.f,0.f };
    ImVec2 display_size = ImGui::GetIO().DisplaySize;
    ImVec2 window_size;
    if (display_size.x < 1920 && display_size.y < 1080)
    {
        ImGui::SetNextWindowSize({645.f , 720.f / 1080.f * display_size.y });
        window_size = { 645.f , 720.f / 1080.f * display_size.y };
    }
    else
    {
        ImGui::SetNextWindowSize({ 645, 720 });
        window_size = { 645, 720 };
    }
    
    ImGui::SetNextWindowPos({ 100,100 }, ImGuiCond_Once);
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(23.f/255.f, 30.f/255.f, 41.f/255.f, 1.f));
    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.f, 0.f, 0.f, 1.f));
    ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.f, 1.f, 0.5f, 1.f));
    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.1f, 0.1f, 0.1f, 1.f));
    ImGui::PushStyleColor(ImGuiCol_PopupBg, ImVec4(0.05f, 0.05f, 0.05f, 1.f));
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.f, 1.f, 0.5f, 0.f));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.f, 1.f, 0.5f, 0.f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.f, 1.f, 0.5f, 1.f));
    
    
    ImGui::Begin("Hello, world!", nullptr, ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);

    auto window_pos = ImGui::GetWindowPos();
    

    //fade
    ImGui::GetWindowDrawList()->AddRectFilledMultiColor({ window_pos.x, window_pos.y}, { window_pos.x + 75.f,  window_pos.y + 60.f }, ImColor(29.f / 255.f, 88.f / 255.f, 95.f / 255.f, 1.f), ImColor(30.f / 255.f, 41.f / 255.f, 56.f / 255.f, 1.f), ImColor(30.f / 255.f, 41.f / 255.f, 56.f / 255.f, 1.f), ImColor(29.f / 255.f, 88.f / 255.f, 95.f / 255.f, 1.f));


    // two trapezoids :) so we cover the gradient rect with a nice angle :)
    std::array<ImVec2, 4> polypoints = { // lighter colored
        ImVec2{window_pos.x + 75.f, window_pos.y}, // top left
        ImVec2{window_pos.x + window_size.x, window_pos.y}, // top right
        ImVec2{window_pos.x + window_size.x, window_pos.y + 60.f}, // bottom right
        ImVec2{window_pos.x + 60.f, window_pos.y + 60.f} // bottom left
    };

    ImGui::GetWindowDrawList()->AddConvexPolyFilled(polypoints.data(), 4, ImColor(27.f / 255.f, 37.f / 255.f, 51.f / 255.f, 1.f));

    polypoints = { //darker colored
        ImVec2{window_pos.x + 80.f, window_pos.y}, // top left
        ImVec2{window_pos.x + window_size.x, window_pos.y}, // top right
        ImVec2{window_pos.x + window_size.x, window_pos.y + 60.f}, // bottom right
        ImVec2{window_pos.x + 65.f, window_pos.y + 60.f} // bottom left
    };

    ImGui::GetWindowDrawList()->AddConvexPolyFilled(polypoints.data(), 4, ImColor(23.f / 255.f, 30.f / 255.f, 41.f / 255.f, 1.f));

    //logo drawing
    int savedflags = ImGui::GetWindowDrawList()->Flags;
    ImGui::GetWindowDrawList()->Flags |= (ImDrawListFlags_AntiAliasedLinesUseTex | ImDrawListFlags_AntiAliasedFill | ImDrawListFlags_AntiAliasedLines);
    ImGui::GetWindowDrawList()->AddImage(LoadedImages::xtclogo.texture, ImVec2{ window_pos.x - 7.f, window_pos.y - 17.f}, ImVec2{ window_pos.x + 69.f, window_pos.y + 72.f });
    ImGui::GetWindowDrawList()->Flags = savedflags;

    ImGui::SetCursorPosX(70);

    // tabs

    const std::string tabnames[]{ "Legitbot", "Ragebot", "Visuals", "World", "Misc", "Config", "LUA"};

    ImGui::BeginGroup();
    ImGui::PushFont(XtcFonts::tab_names);

    const std::pair<ImVec2, ImVec2> tabimageoffsets[7] = // offsets for the pictures on the tabs so theyre centered
    {
        {{10.f,2.f}, {0.f,-5.f}}, // legitbot
        {{9.f,3.f}, {-4.f,-5.f}}, // ragebot
        {{8.f,3.f}, {-3.f,1.f}}, // visuals
        {{3.f,-1.f}, {3.f,-1.f}}, // world
        {{0.f,-5.f}, {5.f,5.f}}, // misc
        {{8.f,3.f}, {-3.f,-5.f}}, // config
        {{7.f,2.f}, {-2.f,-3.f}}  // lua
    };

    for (int i = 0; i < 7; i++)
    {
        bool selected = (curtab == i);
        if (ImGui::TabAlt(LoadedImages::tabIcons[i], selected, tabnames[i].c_str(), tabimageoffsets[i].first, tabimageoffsets[i].second))
        {
            curtab = i;
        }

        if (i != 6)
            ImGui::SameLine();
    }
    ImGui::PopFont();
    ImGui::EndGroup();

    ImGui::Spacing();
    ImGui::Spacing();

    //local defs
    static std::string Penises[]{ "Black",  "White", "Asian(Small)", "Voidzero Dick ( BIG )", "Tabascofarmer Dick (WTF BIg!!!!!!)"};
    static std::string Vaginas[]{ "Black",  "White", "Asian(Tight)" };
    //tabs

    ImGui::PushFont(XtcFonts::menu_font);

    ImGui::SetCursorPosX(5);
    ImGui::SetCursorPosY(70);
    ImGui::BeginChild("##BIgTab", { window_size.x - 10, window_size.y - 75 }, false, ImGuiWindowFlags_NoScrollbar);
    switch (curtab)
    {
    case 0:
        ImGui::Text("Anal");
        ImGui::SliderFloat("Amount Of Penis", &Fortesting, 0.f, 50.f);


        if (ImGui::ListBoxHeader("Penises to choose"))
        {
            for (int i = 0; i < 5; i++)
            {
                bool select = i == CurrentPenisSelection;
                if (ImGui::Selectable(Penises[i].c_str(), &select))
                    CurrentPenisSelection = i;

            }



            ImGui::ListBoxFooter();
        }

        ImGui::Text("Anal");
        ImGui::SliderFloat("Amount Of Penis", &Fortesting, 0.f, 50.f);
        ImGui::Text("Anal");
        ImGui::SliderFloat("Amount Of Penis", &Fortesting, 0.f, 50.f);
          
        ImGui::SliderFloat("Amount Of Penis", &Fortesting, 0.f, 50.f);

        ImGui::SliderFloat("Amount Of Penis", &Fortesting, 0.f, 50.f);
        ImGui::SliderFloat("Amount Of Penis", &Fortesting, 0.f, 50.f);
        ImGui::SliderFloat("Amount Of Penis", &Fortesting, 0.f, 50.f);
        ImGui::SliderFloat("Amount Of Penis", &Fortesting, 0.f, 50.f);

        ImGui::Text("Anal");
        ImGui::Text("Anal");
        ImGui::Text("Anal");
        ImGui::Text("Anal");
        ImGui::Text("Anal");
        ImGui::Text("Anal");
        ImGui::Text("Anal");
        ImGui::Text("Anal");
        ImGui::Text("Anal");
        ImGui::Text("Anal");
        ImGui::Text("Anal");
        ImGui::Text("Anal");
        ImGui::Text("Anal");
        ImGui::Text("Anal");
        ImGui::Text("Anal");

        break;

    case 1:
        ImGui::Text("Oral");

        if (ImGui::BeginCombo("Vaginas to choose", Vaginas[CurrentVaginaSelection].c_str()))
        {
            for (int i = 0; i < 3; i++)
            {
                bool select = i == CurrentVaginaSelection;
                if (ImGui::Selectable(Vaginas[i].c_str(), &select))
                    CurrentVaginaSelection = i;

            }

            ImGui::EndCombo();
        }

        ImGui::ColorEdit4("Choose Vagina Color", EpicColor, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);

        break;
    }
    ImGui::EndChild();
    ImGui::PopFont();
    
    ImGui::End();
    ImGui::PopStyleColor(8);
}



bool pXtcMenu::LoadTextureFromMemory(LPDIRECT3DDEVICE9 pDevice, void* data, size_t datasize, PDIRECT3DTEXTURE9* out_texture, int* out_width, int* out_height)
{
    // Load texture from disk
    PDIRECT3DTEXTURE9 texture;
    HRESULT hr = D3DXCreateTextureFromFileInMemory(pDevice, data, datasize, &texture);
    if (hr != S_OK)
        return false;

    // Retrieve description of the texture surface so we can access its size
    D3DSURFACE_DESC my_image_desc;
    texture->GetLevelDesc(0, &my_image_desc);
    *out_texture = texture;
    *out_width = (int)my_image_desc.Width;
    *out_height = (int)my_image_desc.Height;
    return true;

}