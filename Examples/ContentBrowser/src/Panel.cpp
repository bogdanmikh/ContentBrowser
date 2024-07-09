
#include "Panel.hpp"

#include <imgui.h>

Panel::~Panel() {
    delete m_defaultFileIcon;
    delete m_directoryIcon;
    for (const auto &icon : m_fileIcons) {
        delete icon.second;
    }
}

static std::string getString(const char8_t *ptr) {
    return (const char *)ptr;
}

void Panel::start() {
    m_baseDirectory = std::filesystem::current_path();
    m_currentDirectory = std::filesystem::current_path();
    m_defaultFileIcon = new Texture("Icons/FileIcon.png");
    m_directoryIcon = new Texture("Icons/DirectoryIcon.png");
    m_fileIcons.emplace(".cpp", new Texture("Icons/Cpp.png"));
}
void Panel::onImGuiRender() {
    ImGui::Begin("Content Browser");
    if (m_currentDirectory != std::filesystem::path(m_baseDirectory)) {
        if (ImGui::Button(getString(ICON_ARROW_LEFT).c_str())) {
            m_currentDirectory = m_currentDirectory.parent_path();
        }
    }
    static float padding = 16.0f;
    static float thumbnailSize = 128.0f;
    float cellSize = thumbnailSize + padding;

    float panelWidth = ImGui::GetContentRegionAvail().x;
    int columnCount = (int)(panelWidth / cellSize);
    columnCount = std::max(columnCount, 1);

    ImGui::Columns(columnCount, 0, false);

    for (auto &directoryEntry : std::filesystem::directory_iterator(m_currentDirectory)) {
        const auto &path = directoryEntry.path();
        std::string filenameString = path.filename().string();

        ImGui::PushID(filenameString.c_str());
        Texture *icon;
        if (directoryEntry.is_directory()) {
            icon = m_directoryIcon;
        } else {
            if (m_fileIcons.find(path.extension().string()) != m_fileIcons.end()) {
                icon = m_fileIcons[path.extension().string()];
            } else {
                icon = m_defaultFileIcon;
            }
        }
        icon->bind();
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
        ImGui::ImageButton(
            (ImTextureID)icon->getRendererId(), {thumbnailSize, thumbnailSize}, {0, 1}, {1, 0}
        );
        icon->unbind();
        ImGui::PopStyleColor();
        if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left)) {
            if (directoryEntry.is_directory()) {
                m_currentDirectory /= path.filename();
            }
        }
        ImGui::TextWrapped(filenameString.c_str());
        ImGui::NextColumn();
        ImGui::PopID();
    }
    ImGui::Columns(1);
    ImGui::SliderFloat("Thumbnail Size", &thumbnailSize, 16, 512);
    ImGui::SliderFloat("Padding", &padding, 0, 32);
    // TODO: status bar
    ImGui::End();
}
