//
// Created by vkig on 2021. 04. 20..
//

#ifndef GWIDGET_GBUTTON_HPP
#define GWIDGET_GBUTTON_HPP
#include "GWidget.hpp"
#include <functional>

class GButton : public GWidget {
public:
    enum type{
        UP,
        DOWN,
        LABELED
    };
protected:
    std::function<void()> f;
    genv::color textColor = genv::color(255, 255, 255);
    std::string text;
    type _type;
    bool pressed;
    void press();
    void release();
public:
    GButton();
    GButton(Application* _parent, int x, int y, int _width, int _height, int _bordersize, genv::color _main,
            genv::color _bordercolor, std::function<void()> _f = nullptr, type _t = LABELED, genv::color _textcolor = genv::color(255,255,255), std::string _text = "");
    void action(genv::event& ev) override;
    void show() override;
    void changeType(type _t);
    void setText(std::string _text);
};


#endif //GWIDGET_GBUTTON_HPP
