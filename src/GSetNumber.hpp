//
// Created by vkig on 2021. 04. 20..
//

#ifndef GWIDGET_GSETNUMBER_HPP
#define GWIDGET_GSETNUMBER_HPP

#include "GButton.hpp"

class GSetNumber : public GWidget {
protected:
    int number, min, max;
    GButton buttonUp;
    GButton buttonDown;
public:
    GSetNumber();
    GSetNumber(Application* parent, int x, int y, int _width, int _height, int _borderSize, int _number = 0, int _min = 0, int _max = 255,
               genv::color _mainColor = genv::color(255, 255, 255), genv::color _borderColor = genv::color(255, 0, 0));
    void show() override;
    void action(genv::event& ev) override;
    void resize(int _width, int _height) override;
    void changePosition(int x, int y) override;
    void deselect() override;
    void increase(int value = 1);
    void decrease(int value = 1);
    [[nodiscard]] int getValue() const;
};


#endif //GWIDGET_GSETNUMBER_HPP
