//
// Created by vkig on 2021. 04. 20..
//

#ifndef GWIDGET_GSELECT_HPP
#define GWIDGET_GSELECT_HPP
#include "GButton.hpp"
#include <vector>

class GSelect : public GWidget{
    int selectedItem{}, scrollHeight{}, itemHeight{}, basicHeight{}, dx{}, dy{}, topItem{}, itemsOnScroll{};
    bool expanded{}, sliderDragged{};
    GButton buttonDown, slider;
    std::vector<std::string> items;
    genv::canvas itemsGraphRepr;
    void dragSlider(int ex, int ey);
    void dropSlider();
    void expand();
    void scrollUp();
    void scrollDown();
    void selectItem(int ey);
public:
    GSelect();
    GSelect(Application* _parent, int x, int y, int _width, int _height, int _borderSize, int _scrollHeight, std::vector<std::string> _items,
            genv::color _main = genv::color(255, 255, 255), genv::color _borderColor = genv::color(255, 0, 0));
    void show() override;
    bool isOnScroll(int ex, int ey);
    void addItem(const std::string& item);
    void deselect() override;
    void removeItem(const std::string& item);
    void action(genv::event& ev) override;
    void resize(int _width, int _height) override;
    void changePosition(int x, int y) override;
    void showScroll(bool init = false);
    [[nodiscard]] std::string getSelected() const;
};


#endif //GWIDGET_GSELECT_HPP
