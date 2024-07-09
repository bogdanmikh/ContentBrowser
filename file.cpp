#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

int main() {
    std::string path = "/home/bogdan";

    try {
        if (fs::exists(path) && fs::is_directory(path)) {
            for (const auto& entry : fs::directory_iterator(path)) {
                auto filename = entry.path().filename();
                if (fs::is_regular_file(entry.status())) {
                    if (filename == "dev.sh") {
                        std::string command = ("open " + path + fs::path::preferred_separator + filename.string());
                        std::system(command.c_str());
                    }
                    std::cout << "File: " << filename << '\n';
                } else if (fs::is_directory(entry.status())) {
                    std::cout << "Folder: " << filename << '\n';
                }
            }
        } else {
            std::cout << "Path not found\n";
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << e.what() << '\n';
    }
}