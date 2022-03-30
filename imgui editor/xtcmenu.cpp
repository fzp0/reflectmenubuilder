#include "xtcmenu.h"
#include <ShlObj_core.h>
#include <algorithm>
#include "project_selection.h"
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

ImVec2 window_size;
ImVec2 window_pos;

void AltBeginChild(ImVec2 min, ImVec2 max, std::string title)
{
    ImGui::GetWindowDrawList()->AddRect({ window_pos.x + min.x , window_pos.y + min.y }, { window_pos.x + max.x, window_pos.y + max.y }, ImColor(30.f / 255.f, 41.f / 255.f, 56.f / 255.f, 1.f), 3.f);
    ImGui::PushFont(XtcFonts::tab_names);
    ImVec2 TitleSize = ImGui::CalcTextSize(title.c_str());
    ImGui::SetCursorPosX((min.x + max.x)/2.f - TitleSize.x/2.f);
    ImGui::SetCursorPosY(min.y + 2);
    ImGui::Text(title.c_str());
    ImGui::PopFont();
    ImGui::GetWindowDrawList()->AddLine({ window_pos.x + min.x , window_pos.y + min.y + TitleSize.y + 5}, { window_pos.x + max.x , window_pos.y + min.y + TitleSize.y + 5 }, ImColor(30.f / 255.f, 41.f / 255.f, 56.f / 255.f, 1.f));
    ImGui::SetCursorPosX(min.x + 5);
    ImGui::SetCursorPosY(min.y + 10 + TitleSize.y);

    ImGui::BeginChild(title.c_str() , {(max.x - min.x) - 5, (max.y - min.y) - 15 - TitleSize.y}, false, ImGuiWindowFlags_NoScrollbar);
    //ImGui::Spacing();

}

void AltEndChild()
{
    ImGui::EndChild();
}



struct player_info
{
    std::string name;
    bool shoot;
    bool is_friend;
};

static bool dummy_bool = false;
static int dummy_int = 0;
static float dummy_float = 0;


static int curtab = 0;
static float Fortesting = 10.f;
static int CurrentPenisSelection = 0;
static int CurrentVaginaSelection = 0;
static float EpicColor[4] = { 1.f,1.f,1.f,1.f };
static bool Init_bool = false;
static int currentConfig = 0;
static bool playerlist_enabled = true;
static bool spectatorlist_enabled = true;
static bool aiaimbut{ 0 };
static bool aiaibut_onkey{ 0 };
static bool aiiambut_team{ 0 };
static bool aauto_pistolering{ 0 };
static bool backterackering{ 0 };
static float bt_length{ 0.2 };
static player_info players[4] =
{
    {"Hossik", false, true},
    {"Rose water", false, true},
    {"Falton", false, true},
    {"Nigger Pug", true, false}
};



void pXtcMenu::Render()
{
    
    if (!Init_bool)
    {
        RefreshConfigs();


        Init_bool = true;
    }

    auto& style = ImGui::GetStyle();

    style.WindowRounding = 3.f;
    style.WindowTitleAlign = { 0.5, 0.5 };
    style.WindowBorderSize = 0.f;
    style.FrameBorderSize = 0.f;
    style.WindowPadding = ImVec2{ 0.f,0.f };
    style.ChildRounding = 3.f;

    ImVec2 display_size = ImGui::GetIO().DisplaySize;
    
    if (display_size.x < 1920 && display_size.y < 1080)
    {
        ImGui::SetNextWindowSize({650.f , 720.f / 1080.f * display_size.y });
        window_size = { 650.f , 720.f / 1080.f * display_size.y };
    }
    else
    {
        ImGui::SetNextWindowSize({ 650.f, 720.f });
        window_size = { 650.f, 720.f };
    }
    
    ImGui::SetNextWindowPos({ 100,100 }, ImGuiCond_Once);
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(23.f/255.f, 30.f/255.f, 41.f/255.f, 1.f));
    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.f, 0.f, 0.f, 1.f));
    ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(23.f / 255.f, 30.f / 255.f, 41.f / 255.f, 1.f));
    ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(23.f / 255.f, 30.f / 255.f, 41.f / 255.f, 1.f));
    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.1f, 0.1f, 0.1f, 1.f));
    ImGui::PushStyleColor(ImGuiCol_PopupBg, ImVec4(0.05f, 0.05f, 0.05f, 1.f));
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(32.f / 255.f, 42.f / 255.f, 56.f / 255.f, 1.f));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(32.f / 255.f, 42.f / 255.f, 56.f / 255.f, 1.f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(55.f / 255.f, 66.f / 255.f, 81.f / 255.f, 1.f));
    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(30.f / 255.f, 41.f / 255.f, 56.f / 255.f, 1.f));
    ImGui::PushStyleColor(ImGuiCol_Separator, ImVec4(30.f / 255.f, 41.f / 255.f, 56.f / 255.f, 1.f));
    ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(32.f / 255.f, 42.f / 255.f, 56.f / 255.f, 1.f));
    ImGui::PushStyleColor(ImGuiCol_CheckMark, ImVec4(0.f, 1.f, 0.5f, 1.f));
    ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(32.f / 255.f, 42.f / 255.f, 56.f / 255.f, 1.f));
    ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(22.f / 255.f, 32.f / 255.f, 46.f / 255.f, 1.f));
    ImGui::PushStyleColor(ImGuiCol_HeaderActive, ImVec4(55.f / 255.f, 66.f / 255.f, 81.f / 255.f, 1.f));
    
    
    ImGui::Begin("Hello, world!", nullptr, ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar);

    window_pos = ImGui::GetWindowPos();
    

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
    ImGui::GetWindowDrawList()->AddImage(LoadedImages::xtclogo.texture, ImVec2{ window_pos.x - 7.f, window_pos.y - 12.f}, ImVec2{ window_pos.x + 69.f, window_pos.y + 72.f });
    ImGui::GetWindowDrawList()->Flags = savedflags;

    ImGui::SetCursorPosX(70);

    // tabs

    const std::string tabnames[]{ "Legitbot", "Ragebot", "Visuals", "World", "Misc", "Config", "LUA"};

    ImGui::BeginGroup();
    ImGui::PushFont(XtcFonts::tab_names);

    const std::pair<ImVec2, ImVec2> tabimageoffsets[7] = // offsets for the pictures on the tabs so theyre centered
    {
        {{13.f,2.f}, {0.f,-5.f}}, // legitbot
        {{12.f,3.f}, {-4.f,-5.f}}, // ragebot
        {{10.f,3.f}, {-4.f,1.f}}, // visuals
        {{5.f,-1.f}, {1.f,-1.f}}, // world
        {{2.f,-6.f}, {3.f,5.f}}, // misc
        {{10.f,3.f}, {-5.f,-5.f}}, // config
        {{8.f,2.f}, {-1.f,-3.f}}  // lua
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
    ImVec2 lgbt_txt_sz = ImGui::CalcTextSize(tabnames[0].c_str());

    style.WindowPadding.x = 5.f;
    style.FramePadding = { 0.f, 2.f };
    style.FrameRounding = 3.f;
    //style.ItemInnerSpacing.x = 10.f;
    //style.SelectableTextAlign = { 0.1f, 0.f };
    
    const int menufont_height = 13;

    switch (curtab)
    {
    case 0: //legit bot
        AltBeginChild({ 5 ,  65 }, {5 + ((window_size.x - 10) / 2), (window_size.y / 2) + 2 }, tabnames[0]);
        
        ImGui::Checkbox("Aimbot", &aiaimbut);
        if (aiaimbut)
        {
            
            ImGui::Checkbox("On Key", &aiaibut_onkey);
            if (aiaibut_onkey)
            {
                ImGui::Text("Keybind Placeholder");
                //ImGui::Dummy(ImVec2(0.0f, 0.0f));
                //ImGui::SameLine();
                //vars.legitbot.key.imgui(crypt_str("Legitbot Key"));
            }
            
            ImGui::Checkbox("Target Teammates", &aiiambut_team);
            //ImGui::Checkbox(crypt_str("RCS Standalone"), &vars.legitbot.rcsstandalone);
        }
        
        ImGui::Checkbox("Auto Pistol", &aauto_pistolering);
        
        ImGui::Checkbox("Backtrack", &backterackering);
        
        if (backterackering)
        {
            ImGui::PushID("polsjdsd");
            ImGui::Text("Backtrack max length");
            ImGui::SetNextItemWidth(270.f);
            ImGui::SliderFloat("Backtrack max lengtheringsexing", &bt_length, 0.f, 0.2f, "%.3fs");
            ImGui::PopID();
        }

        AltEndChild();

        AltBeginChild({ 5, (window_size.x / 2) }, { 5 + ((window_size.x - 10) / 2),  window_size.y - 10 }, "Triggerbot");
        

        AltEndChild();

        AltBeginChild({ 10 + ((window_size.x - 10) / 2), 65 }, { window_size.x - 5, window_size.y - 10 }, "Weapon Configuration");

        ImGui::Text("ImSexing");
        AltEndChild();

        break;

    case 1: // rage bot
        //ImGui::SetCursorPosX(5);
        //ImGui::SetCursorPosY(70);
       // ImGui::BeginChild("RagebotGeneral", { (window_size.x - 10) / 2, window_size.y - 80 }, true, ImGuiWindowFlags_NoScrollbar);
        AltBeginChild({ 5,65 }, { 5 + ((window_size.x - 10) / 2),  window_size.y - 80 }, "Ragebot");


        //this is an example of a proper combobox
        ImGui::Text("Vaginas to choose"); // label above combo
        ImGui::SetNextItemWidth(305.f); // combo width
        if (ImGui::BeginCombo("##Vaginas to choose", Vaginas[CurrentVaginaSelection].c_str())) // combo string id and preview label
        {
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3.f); // this is for fixing the first selectable clipping into preview box
            for (int i = 0; i < 3; i++) // amount of selectables
            {
                bool select = i == CurrentVaginaSelection; // selection handler
                if (ImGui::Selectable(Vaginas[i].c_str(), &select, 0, {305.f, menufont_height + 3})) // set the width to combo width or else it looks like shit
                    CurrentVaginaSelection = i; // selection handler

            }

            ImGui::EndCombo(); // dont forget to end combo !
        }

        ImGui::ColorEdit4("Choose Vagina Color", EpicColor, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs);
        AltEndChild();
        break;
    case 2: // visuals
        ImGui::SetCursorPosX(5);
        ImGui::SetCursorPosY(70);
        ImGui::BeginChild("visualgeneral", { (window_size.x - 10) / 2, window_size.y - 80 }, true, ImGuiWindowFlags_NoScrollbar);

        ImGui::EndChild();
        break;
    case 3: // world visuals
        ImGui::SetCursorPosX(5);
        ImGui::SetCursorPosY(70);
        ImGui::BeginChild("worLdGeneral", { (window_size.x - 10) / 2, window_size.y - 80 }, true, ImGuiWindowFlags_NoScrollbar);

        ImGui::EndChild();
        break;
    case 4: // misc
        ImGui::SetCursorPosX(5);
        ImGui::SetCursorPosY(70);
        ImGui::BeginChild("MiscGneral", { (window_size.x - 10) / 2, window_size.y - 80 }, true, ImGuiWindowFlags_NoScrollbar);

        ImGui::Checkbox("enable player list", &playerlist_enabled);
        ImGui::Checkbox("enable spectator list", &spectatorlist_enabled);
        ImGui::EndChild();
        
        break;
    case 5: // config
        ImGui::SetCursorPosX(5);
        ImGui::SetCursorPosY(70); 
        ImGui::BeginChild("Configors", { (window_size.x - 10) / 2, window_size.y - 80 }, true, ImGuiWindowFlags_NoScrollbar);

        if (ImGui::ListBoxHeader("con gfigs"))
        {
            for (int i = 0; i < ConfigList.size(); i++)
            {
                bool select = i == std::clamp(currentConfig, 0, (int)ConfigList.size() - 1);
                if (ImGui::Selectable(ConfigList.at(i).c_str(), &select))
                    currentConfig = i;

            }



            ImGui::ListBoxFooter();
        }


        if (ImGui::Button("refresh cfg"))
            RefreshConfigs();
        ImGui::EndChild();

        break;
    case 6: // lua
        ImGui::SetCursorPosX(5);
        ImGui::SetCursorPosY(70);
        ImGui::BeginChild("LuaSalacctor", { (window_size.x - 10) / 2, window_size.y - 80 }, true, ImGuiWindowFlags_NoScrollbar);

        ImGui::EndChild();
        break;
    }
    ImGui::PopFont();
    
    ImGui::End();
    
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(23.f / 255.f, 30.f / 255.f, 41.f / 255.f, 0.9f));

    if (playerlist_enabled)
    {
        ImGui::GetStyle().WindowPadding = { 5,3 };
        ImGui::Begin("Player List", (bool*)0, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar);
        if (ImGui::BeginTable("playar list", 3))
        {
            for (int row = 0; row < 4; row++)
            {
                ImGui::PushID(row * 32435);
                ImGui::TableNextRow();
                ImGui::TableNextColumn();      
                ImGui::Text(players[row].name.c_str());
                ImGui::Dummy({ 0, 2 });
                ImGui::Separator();
                
                ImGui::TableNextColumn();         
                ImGui::Checkbox("Im want Shoot", &players[row].shoot);
                ImGui::Separator();
                ImGui::TableNextColumn();
                ImGui::Checkbox("Dis is Freind", &players[row].is_friend);
                if (row != 3)
                {
                    ImGui::Separator();
                }
                else
                {
                    ImGui::Spacing();
                }
                ImGui::PopID();
            }
            ImGui::EndTable();
        }


        ImGui::End();
    }

    

    if (spectatorlist_enabled)
    {
        ImGui::GetStyle().WindowPadding = { 5,3 };
        ImGui::Begin("Spectators", (bool*)0, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar);
        if (ImGui::BeginTable("spactatar list", 1))
        {
            for (int row = 0; row < 4; row++)
            {
                ImGui::PushID(row * 23232);
                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::Text(players[row].name.c_str());
                if (row != 3)
                {
                    ImGui::Dummy({ 0, 2 });
                    ImGui::Separator();
                }
                else
                {
                    ImGui::Spacing();
                }
                
                
                ImGui::PopID();
            }
            ImGui::EndTable();
        }
        ImGui::End();
    }

    ImGui::PopStyleColor(17);

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