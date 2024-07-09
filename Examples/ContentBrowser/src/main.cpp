#include <Nest.hpp>

#include "ContentBrowser.hpp"

int main() {
    auto* application = Application::getInstance();
    auto *layer = new ContentBrowser();
    layer->start();
    application->setLayer(layer);
    application->loop();
    delete layer;
    delete application;
}