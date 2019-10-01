#include "Common.h"
#include "Textures.h"
using namespace std;

// Этот файл сдаётся на проверку
// Здесь напишите реализацию необходимых классов-потомков `IShape`

class AbstractFigure : public IShape{
public:
     void SetPosition(Point new_position) override { position_ = new_position; }
     Point GetPosition() const override { return position_; }

     void SetSize(Size new_size) override { size_ = new_size; }
     Size GetSize() const override { return size_; }

     void SetTexture(std::shared_ptr<ITexture> new_texture) { texture_ = new_texture; }
     ITexture* GetTexture() const { return texture_.get(); }

protected:
    Size size_;
    Point position_;
    shared_ptr<ITexture> texture_ = make_shared<ITexture>();
};

Size operator&(const Size& lhs, const Size &rhs){
    return {
        min(lhs.width, rhs.width),
        min(lhs.height, rhs.height)
    };
}


class Rectangle : public  AbstractFigure{
    // Возвращает точную копию фигуры.
    // Если фигура содержит текстуру, то созданная копия содержит ту же самую
    // текстуру. Фигура и её копия совместно владеют этой текстурой.

    void Draw(Image& canvas_image) const {
        Size sh_tx_overlap = texture_->GetSize() & size_;
        Size canvas_image_size{static_cast<int>(canvas_image[0].size()),
                               static_cast<int>(canvas_image.size())};
        Size im_tx_overlap = sh_tx_overlap & canvas_image_size;
        Size sh_im_overlap = canvas_image_size & size_;

        const Image &texture_im = texture_->GetImage();
        for (int h{0}; h < sh_im_overlap.height; ++h){
            for (int w{0}; h < sh_im_overlap.width; ++w){
                canvas_image[h][w] = \
                (w < im_tx_overlap.width && h < im_tx_overlap.height) \
                ? canvas_image[h][w] = texture_im[h][w] \
                : canvas_image[h][w] = '.';
            }
        }
    }


    std::unique_ptr<IShape> Clone() const override {
        return make_unique<Rectangle>(Rectangle(*this));
    }
};

class Ellipse : public AbstractFigure {
    // Возвращает точную копию фигуры.
    // Если фигура содержит текстуру, то созданная копия содержит ту же самую
    // текстуру. Фигура и её копия совместно владеют этой текстурой.
    void Draw(Image& canvas_image) const {

        Size sh_tx_overlap = texture_->GetSize() & size_;
        Size canvas_image_size{static_cast<int>(canvas_image[0].size()),
                               static_cast<int>(canvas_image.size())};
        Size im_tx_overlap = sh_tx_overlap & canvas_image_size;
        Size sh_im_overlap = canvas_image_size & size_;

        const Image &texture_im = texture_->GetImage();
        for (int h{0}; h < sh_im_overlap.height; ++h){
            for (int w{0}; h < sh_im_overlap.width; ++w){
                if (IsPointInEllipse({w, h}, size_))
                canvas_image[h][w] = \
                (w < im_tx_overlap.width && h < im_tx_overlap.height) \
                ? canvas_image[h][w] = texture_im[h][w] \
                : canvas_image[h][w] = '.';
            }
        }
    }


    std::unique_ptr<IShape> Clone() const override {
        return make_unique<Ellipse>(Ellipse(*this));
    }
};


// Напишите реализацию функции
unique_ptr<IShape> MakeShape(ShapeType shape_type) {
    switch (shape_type){
        case ShapeType::Rectangle:
            return make_unique<Rectangle>(Rectangle());
        case ShapeType::Ellipse:
            return make_unique<Ellipse>(Ellipse());
    }
}