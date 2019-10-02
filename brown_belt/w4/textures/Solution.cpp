#include "Common.h"
#include "Textures.h"
using namespace std;

Size operator&(const Size& lhs, const Size &rhs){
    return {
            min(lhs.width, rhs.width),
            min(lhs.height, rhs.height)
    };
}

class SingletonNullTexture : public ITexture {
public:

     Size GetSize() const override {
        static const Size empty_size_{0,0};
        return empty_size_;
    }

    const Image& GetImage() const override {
        static const Image null_image_{};
        return null_image_;
    }
};

class SingletonNullTextureManager {
public:
    static ITexture* GetSingletonNullTexturePtr(){
        static const unique_ptr<SingletonNullTexture> singletonNullTexture =
                make_unique<SingletonNullTexture>();
        return singletonNullTexture.get();
    }
};

class AbstractFigure;
void DrawFigure(const AbstractFigure *fig, Image& canvas_image);


class AbstractFigure : public IShape{
public:
     void SetPosition(Point new_position) final { position_ = new_position; }
     Point GetPosition() const final { return position_; }

     void SetSize(Size new_size) final { size_ = new_size; }
     Size GetSize() const final { return size_; }

     void SetTexture(std::shared_ptr<ITexture> new_texture) final { texture_ = new_texture; }
     ITexture* GetTexture() const final {
         return texture_ ?
                texture_.get() :
                SingletonNullTextureManager::GetSingletonNullTexturePtr();
     }

     tuple<Size, Size, Size> GetOverlapingRegionsWith(const Image& canvas_image) const {
         Size sh_tx_overlap = GetTexture()->GetSize();

         Size canvas_image_size{static_cast<int>(canvas_image[0].size()),
                                static_cast<int>(canvas_image.size())};

         Size im_tx_overlap = sh_tx_overlap & canvas_image_size;
         Size sh_im_overlap = canvas_image_size & size_;
         return {sh_tx_overlap, im_tx_overlap, sh_im_overlap};
     }

    inline bool isTextured(const Point& p) const { // presume that it allways belong to img
        const Size& ts = GetTexture()->GetSize();
        return p.x < ts.width && p.y < ts.height;
    }

     virtual bool isShapeCovered(const Point&) const = 0;
    void Draw(Image& canvas_image) const final {
        DrawFigure(this, canvas_image);
    }
protected:
    Size size_;
    Point position_;
    shared_ptr<ITexture> texture_{nullptr};
};


void DrawFigure(const AbstractFigure *fig, Image& canvas_image){
    Size sh_tx_overlap, im_tx_overlap, sh_im_overlap;
    tie(sh_tx_overlap, im_tx_overlap, sh_im_overlap) =
            fig->GetOverlapingRegionsWith(canvas_image);

    const auto figure_texture = fig->GetTexture();
    const Image &texture_im = figure_texture->GetImage();

    Point shape_origin = fig->GetPosition();

    Point p{0, 0};
    for (; p.y < sh_im_overlap.height; ++p.y,  p.x = 0){
        for (; p.x < sh_im_overlap.width; ++p.x){
            if (fig->isShapeCovered(p))
            canvas_image[p.y + shape_origin.y][p.x + shape_origin.x] = \
                fig->isTextured(p)
                ? texture_im[p.y][p.x] \
                : '.';
        }
    }
}


class Rectangle : public  AbstractFigure{

    inline bool isShapeCovered(const Point&) const override { return true;}

    std::unique_ptr<IShape> Clone() const override {
        return make_unique<Rectangle>(Rectangle(*this));
    }
};

class Ellipse : public AbstractFigure {

    inline bool isShapeCovered(const Point& p) const override{
        return IsPointInEllipse(p, GetSize());
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
        default:
            return nullptr; // make compiler happy
    }
}