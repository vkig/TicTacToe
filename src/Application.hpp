//
// Created by vkig on 2021. 04. 29..
//

#ifndef GWIDGET_APPLICATION_HPP
#define GWIDGET_APPLICATION_HPP

#include "GWidget.hpp"
#include "../graphics.hpp"
#include <vector>

class Application {
protected:
    int XX{}, YY{};
    std::vector<GWidget*> widgets;
public:
    Application();
    virtual ~Application() = default;
    void eventManager();
    void addWidget(GWidget*);
};


#endif //GWIDGET_APPLICATION_HPP
