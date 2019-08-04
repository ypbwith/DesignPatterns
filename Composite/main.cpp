#include <vector>
#include <iostream> // std::cout
#include <memory> // std::auto_ptr
#include <algorithm> // std::for_each
using namespace std;

class Graphic
{
public:
  virtual void print() const = 0;
  virtual ~Graphic() {}
};

class Ellipse : public Graphic //椭圆
{
public:
  void print() const {
    cout << "Ellipse \n";
  }
};

class CompositeGraphic : public Graphic
{
public:
  void print() const {
    for(Graphic * a: graphicList_) {
      a->print();
    }
  }

  void add(Graphic *aGraphic) {  //添加的是基类指针
    graphicList_.push_back(aGraphic);
  }

private:
  vector<Graphic*>  graphicList_;
};

int main()
{
  // Initialize four ellipses
  const auto_ptr<Ellipse> ellipse1(new Ellipse());
  const auto_ptr<Ellipse> ellipse2(new Ellipse());
  const auto_ptr<Ellipse> ellipse3(new Ellipse());
  const auto_ptr<Ellipse> ellipse4(new Ellipse());

  // Initialize three composite graphics
  const auto_ptr<CompositeGraphic> graphic(new CompositeGraphic());
  const auto_ptr<CompositeGraphic> graphic1(new CompositeGraphic());
  const auto_ptr<CompositeGraphic> graphic2(new CompositeGraphic());

  //得到的是子类的指针，传入函数的是基类指针，子类指针可以调用基类指针
  // Composes the graphics
  graphic1->add(ellipse1.get());
  graphic1->add(ellipse2.get());
  graphic1->add(ellipse3.get());

  graphic2->add(ellipse4.get());

  //传入的就是基类指针，也是本身指针类型，不同的子类同一个基类
  graphic->add(graphic1.get());
  graphic->add(graphic2.get());

  // Prints the complete graphic (four times the string "Ellipse")
  graphic->print();


  return 0;
}
