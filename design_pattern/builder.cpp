#include <iostream>
#include <vector>

class Product{
public:
    std::vector<std::string> parts_;
    void ListParts() const{
        std::cout << "Product parts: ";
        for (size_t i = 0; i < parts_.size(); i++){
            if (parts_[i] == parts_.back()){
                std::cout << parts_[i];
            }else{
                std::cout << parts_[i] << ", ";
            }
        }
        std::cout<< "\n\n";
    }
};

class Builder{
    public:
    virtual ~Builder(){}
    virtual void ProducePartA() const =0;
    virtual void ProducePartB() const =0;
    virtual void ProducePartC() const =0;
};

class ConcreteBuilder : public Builder {
private:
    Product* product;
public:
    ConcreteBuilder(){
        this->Reset();
    }
    ~ConcreteBuilder(){
        delete product;
    }

    void Reset(){
        this->product = new Product();
    }
    void ProducePartA()const override{
        this->product->parts_.push_back("PartA");
    }

    void ProducePartB()const override{
        this->product->parts_.push_back("PartB");
    }

    void ProducePartC()const override{
        this->product->parts_.push_back("PartC");
    }
    Product* GetProduct() {
        Product* result= this->product;
        this->Reset();
        return result;
    }
};

class Director{
private:
    Builder* builder;
public:
    void set_builder(Builder* builder){
        this->builder = builder;
    }
    void BuildMinimalViableProduct(){
        this->builder->ProducePartA();
    }
    
    void BuildFullFeaturedProduct(){
        this->builder->ProducePartA();
        this->builder->ProducePartB();
        this->builder->ProducePartC();
    }
};

void ClientCode(Director& director)
{
    ConcreteBuilder* builder = new ConcreteBuilder();
    director.set_builder(builder);
    std::cout << "Standard basic product:\n"; 
    director.BuildMinimalViableProduct();
    
    Product* p= builder->GetProduct();
    p->ListParts();
    delete p;

    std::cout << "Standard full featured product:\n"; 
    director.BuildFullFeaturedProduct();

    p= builder->GetProduct();
    p->ListParts();
    delete p;

    // Remember, the Builder pattern can be used without a Director class.
    std::cout << "Custom product:\n";
    builder->ProducePartA();
    builder->ProducePartC();
    p=builder->GetProduct();
    p->ListParts();
    delete p;

    delete builder;
}

int main(){
    Director* director= new Director();
    ClientCode(*director);
    delete director;
    return 0;    
}

https://refactoringguru.cn/design-patterns/cpp