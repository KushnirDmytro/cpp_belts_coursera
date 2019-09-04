//
// Created by dkushn on 14.08.19.
//

#ifndef CPP_BELTS_RECTANGLE_H
#define CPP_BELTS_RECTANGLE_H

class Rectangle {
public:
    Rectangle(int width, int height);

    int GetArea() const;

    int GetPerimeter() const ;
    int GetWidth() const;
    int GetHeight() const;
private:
    int width_, height_;
};

#endif //CPP_BELTS_RECTANGLE_H
