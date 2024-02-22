//
// Created by vkig on 2021. 05. 05..
//

#ifndef TICTACTOE_GLABEL_HPP
#define TICTACTOE_GLABEL_HPP

#include "GWidget.hpp"

class GLabel : public GWidget{
    std::string text;
    genv::color textColor = genv::color(0, 0, 0);
public:
    GLabel(Application* _parent, int x, int y, int _width, int _height, std::string _text, genv::color _textColor = genv::color(255, 255, 255),
           int _borderSize = 0, genv::color _mainColor = genv::color(0, 0, 0), genv::color _borderColor = genv::color(0, 0, 0));

    void setText(std::string _text);

    void show() override;

    void action(genv::event& ev) override;
};


#endif //TICTACTOE_GLABEL_HPP
