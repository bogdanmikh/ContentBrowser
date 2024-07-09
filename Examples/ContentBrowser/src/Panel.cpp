
#include "Panel.hpp"

#include <imgui.h>

Panel::~Panel() {
    delete m_defaultFileIcon;
    delete m_directoryIcon;
}

void Panel::start() {
    m_baseDirectory = std::filesystem::current_path();
    m_currentDirectory = std::filesystem::current_path();
//    m_fileIcons.emplace("123", Texture(""));
    m_defaultFileIcon = new Texture("FileIcon.png");
    m_directoryIcon = new Texture("DirectoryIcon.png");
}
void Panel::onImGuiRender() {
    ImGui::Begin("Content Browser");
    if (m_currentDirectory != std::filesystem::path(m_baseDirectory)) {
        if (ImGui::Button("<-")) {
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
        Texture *icon = directoryEntry.is_directory() ? m_directoryIcon : m_defaultFileIcon;
        icon->bind();
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
        ImGui::ImageButton(
            (ImTextureID)icon->getRendererId(), {thumbnailSize, thumbnailSize}, {0, 1}, {1, 0}
        );
        icon->unbind();

        if (ImGui::BeginDragDropTarget()) {
            const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("FileDrop");
            LOG_WARN("Payload");

            if (payload) {
                const char* path = (const char*)payload->Data;

                std::string file_path = std::string(path, payload->DataSize);

                LOG_WARN("Dropped file: {}", file_path.c_str());
            }
            ImGui::EndDragDropTarget();
        }

        ImGui::PopStyleColor();
        if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left)) {
            if (directoryEntry.is_directory())
                m_currentDirectory /= path.filename();
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
