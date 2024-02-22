//
// Created by vkig on 2021. 05. 05..
//

#include "GLabel.hpp"

#include <utility>

GLabel::GLabel(Application *_parent, int x, int y, int _width, int _height, std::string _text, genv::color _textColor, int _borderSize,
               genv::color _mainColor, genv::color _borderColor) : GWidget(_parent, x, y, _width, _height, _borderSize, _mainColor, _borderColor){
    text = std::move(_text);
    textColor = _textColor;
}

void GLabel::setText(std::string _text){
    text = std::move(_text);
    show();
}

void GLabel::show(){
    GWidget::show();
    graphicRepr << textColor;
    graphicRepr<<genv::move_to(width/2-graphicRepr.twidth(text)/2,height/2-(graphicRepr.cascent()+graphicRepr.cdescent())/2)<<genv::text(text);
    genv::gout<<genv::stamp(graphicRepr, posX, posY);
}

void GLabel::action(genv::event &ev) {

}
