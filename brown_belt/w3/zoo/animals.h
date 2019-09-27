#include <string>

class Animal {
public:
  virtual std::string Voice() const {
    return "Not implemented yet";
  }
  virtual ~Animal() {
  }
};


class Tiger: public Animal {
  std::string Voice() const override {
      static const std::string voice_sound = "Rrrr";
    return voice_sound;
  }
};


class Wolf: public Animal {
  std::string Voice() const override {
    return "Wooo";
  }
};


class Fox: public Animal {
  std::string Voice() const override {
    return "Tyaf";
  }
};

