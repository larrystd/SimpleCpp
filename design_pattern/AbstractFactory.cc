#include <iostream>
#include <string>


class AbstractProduct {
public:
    virtual ~AbstractProduct() {};
    virtual std::string UsefulFunction() const  = 0;
};


class ConcreteProductA : public AbstractProduct {
public:
    std::string UsefulFunction() const override {
        return "The result of the product A.";
    }
};

class ConcreteProductB : public AbstractProduct {
  std::string UsefulFunction() const override {
    return "The result of the product B.";
  }
};

class AbstractFactory {
public:
    virtual AbstractProduct* CreateProductA() const = 0;
     virtual AbstractProduct* CreateProductB() const = 0;
};

class ConcreteFactory : public AbstractFactory {
 public:
  AbstractProduct *CreateProductA() const override {
    return new ConcreteProductA();
  }
  AbstractProduct *CreateProductB() const override {
    return new ConcreteProductB();
  }
};


void ClientCode(const AbstractFactory &factory) {
  const AbstractProduct *product_a = factory.CreateProductA();
  const AbstractProduct *product_b = factory.CreateProductB();
  std::cout << product_a->UsefulFunction() << "\n";
  std::cout << product_b->UsefulFunction() << "\n";
  delete product_a;
  delete product_b;
}

int main() {
  std::cout << "Client: Testing client code with the first factory type:\n";
  ConcreteFactory *f = new ConcreteFactory();
  ClientCode(*f);
  delete f;

  return 0;
}