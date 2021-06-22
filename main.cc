
class A;
class B;
class C;

class Visitor {
public:
	virtual void visit(A &) = 0;
	virtual void visit(B &) = 0;
	virtual void visit(C &) = 0;

	virtual ~Visitor() = default;
};


class Base {
public:
	virtual void accept(Visitor &) = 0;
	virtual ~Base() = default;
};

class A : public Base {
public:
	void accept(Visitor & v) final
	{
		v.visit(*this);
	}
};

class B : public Base {
public:
	void accept(Visitor & v) final
	{
		v.visit(*this);
	}
};

class C : public Base {
public:
	void accept(Visitor & v) final
	{
		v.visit(*this);
	}
};

#include <iostream>
#include <vector>
#include <memory>

class FooVisitor : public Visitor {
public:
	void visit(A &) override
	{
		std::cerr << "A\n";
	}

	void visit(B &) override
	{
		std::cerr << "B\n";
	}

	void visit(C &) override
	{
		std::cerr << "C\n";
	}
};

int main()
{

	std::vector<std::unique_ptr<Base>> v;
	v.emplace_back(new A{});
	v.emplace_back(new A{});
	v.emplace_back(new B{});
	v.emplace_back(new B{});
	v.emplace_back(new C{});
	v.emplace_back(new C{});

	FooVisitor vis;
	for (auto const& b : v) {
		b->accept(vis);
	}

	return 0;
}
