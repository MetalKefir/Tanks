/*******************************************
	Данные классы реализуют делигаты.

	Дабы понять все это читайте:
		1. http://habrahabr.ru/post/78299/
		2. https://ru.wikipedia.org/wiki/%D0%94%D0%B5%D0%BB%D0%B5%D0%B3%D0%B0%D1%82_(%D0%BF%D1%80%D0%BE%D0%B3%D1%80%D0%B0%D0%BC%D0%BC%D0%B8%D1%80%D0%BE%D0%B2%D0%B0%D0%BD%D0%B8%D0%B5)
********************************************/

#include <assert.h>

//  Контейнер для хранения до 2-х аргументов.
struct NIL {};
class IArguments { public: virtual ~IArguments() {} };
template< class T1 = NIL, class T2 = NIL >
class Arguments : public IArguments
{
public: Arguments() {}
};

//  Контейнер для хранения указателя на метод.
class IContainer { public: virtual void Call(IArguments*) = 0; };
template< class T, class M > class Container : public IContainer {};

//  Специализация для метода без аргументов.
template< class T >
class Container< T, void (T::*)(void) > : public IContainer
{
	typedef void (T::*M)(void);
public: Container(T* c, M m) : m_class(c), m_method(m) {}
private: T* m_class; M m_method;

public: void Call(IArguments* i_args)
{
	(m_class->*m_method)();
}
};

//  Специализация для метода с одним аргументом.
template< class T, class A1 >
class Container< T, void (T::*)(A1) > : public IContainer
{
	typedef void (T::*M)(A1);
	typedef Arguments<A1> A;
public: Container(T* c, M m) : m_class(c), m_method(m) {}
private: T* m_class; M m_method;
public: void Call(IArguments* i_args)
{
	A* a = dynamic_cast< A* >(i_args);
	assert(a);
	if (a) (m_class->*m_method)(a->arg1);
}
};

//  Специализация для метода с двумя аргументами
template< class T, class A1, class A2 >
class Container< T, void (T::*)(A1, A2) > : public IContainer
{
	typedef void (T::*M)(A1, A2);
	typedef Arguments<A1, A2> A;
public: Container(T* c, M m) : m_class(c), m_method(m) {}
private: T* m_class; M m_method;
public: void Call(IArguments* i_args)
{
	A* a = dynamic_cast< A* >(i_args);
	assert(a);
	if (a) (m_class->*m_method)(a->arg1, a->arg2);
}
};


//  Собственно делегат.
class Delegate
{
public:

	Delegate() : m_container(0) {}
	//~Delegate() { if (m_container) delete m_container; }

	template< class T, class U > void Connect(T *i_class, U i_method)
	{
		if (m_container) delete m_container;
		m_container = new Container< T, U >(i_class, i_method);
	}

	void operator()()
	{
		m_container->Call(&Arguments<>());
	}

private:
	IContainer* m_container;
};
