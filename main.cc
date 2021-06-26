
template <typename ...Types> class Visitor;

// class Visitor<T4> {};
// class Visitor<T3, T4> : public Visitor<T4> {};
// class Visitor<T2, T3, T4> : public Visitor<T3, T4> {};
// class Visitor<T1, T2, T3, T4> : public Visitor<T2, T3, T4> {};

template <typename T>
class Visitor<T> {
public:
	virtual void visit(T &) = 0;
	virtual ~Visitor() = default; // End of recursion, this is the base class
};

template <typename T, typename ...Types>
class Visitor<T, Types...>  : public Visitor<Types...> {
public:
	using Visitor<Types...>::visit; // ... makes visit from base classes available for overload resolution
	virtual void visit(T &) = 0;
};

template <typename Derived, typename Base>
class Visitable : public Base {
public:
	void accept(typename Base::VisitorType & v) final
	{
		v.visit(static_cast<Derived &>(*this));
	}
};

class ABC {
public:
	using VisitorType = Visitor<class A, class B, class C>; // using "class" here is a forward declaration

	virtual void accept(VisitorType &) = 0;
	virtual ~ABC() = default;
};

class A : public Visitable<A, ABC> {
public:
};

class B : public Visitable<B, ABC> {
public:
};

class C : public Visitable<C, ABC> {
public:
};

#include <iostream>
#include <vector>
#include <memory>

class FooVisitor : public ABC::VisitorType {
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

	std::vector<std::unique_ptr<ABC>> v;
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
