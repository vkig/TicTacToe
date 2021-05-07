//
// Created by vkig on 2021. 05. 05..
//

#ifndef TICTACTOE_GLABEL_HPP
#define TICTACTOE_GLABEL_HPP

#include "GWidget.hpp"

class GLabel : public GWidget{
    std::string text;
    genv::color textc = genv::color(0, 0, 0);
public:
    GLabel(Application* _parent, int x, int y, int _width, int _height, std::string _text, genv::color _textc = genv::color(255, 255, 255),
           int _bordersize = 0, genv::color _main = genv::color(0,0,0), genv::color _bordercolor = genv::color(0, 0, 0));

    void setText(std::string _text);

    void show() override;

    void action(genv::event& ev) override;
};


#endif //TICTACTOE_GLABEL_HPP
