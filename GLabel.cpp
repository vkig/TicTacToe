//
// Created by vkig on 2021. 05. 05..
//

#include "GLabel.hpp"

GLabel::GLabel(Application *_parent, int x, int y, int _width, int _height, std::string _text, genv::color _textc, int _bordersize,
               genv::color _main, genv::color _bordercolor) : GWidget(_parent, x, y, _width, _height, _bordersize, _main, _bordercolor){
    text = _text;
    textc = _textc;
}

void GLabel::setText(std::string _text){
    text = _text;
    show();
}

void GLabel::show(){
    GWidget::show();
//    graphicRepr<<genv::color(255, 255, 255);
//    graphicRepr<<genv::move_to(width/2-graphicRepr.twidth(text)/2,height/2-(graphicRepr.cascent()+graphicRepr.cdescent())/2)<<genv::text(text);
//    graphicRepr<<genv::move_to(0, 0)<<genv::box(10, 10);
//    genv::gout<<genv::stamp(graphicRepr, posx, posy);
}

void GLabel::action(genv::event &ev) {

}
