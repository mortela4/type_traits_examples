//============================================================================
// Name        : type_mix_ex1.cpp
// Author      : ml
// Version     :
// Copyright   : 
// Description : Mixing types - using a function which may return different types,
//               depending on input.
//============================================================================

#include <iostream>
#include <string>
#include <variant>
#include <type_traits>


using namespace std;


struct Foo { class CA {}; class CB {}; class CC {}; CA a; CB b; CC c; };
enum Base { A, B, C, };
enum Func { X, Y, };

template<Base> struct GetBaseTraits;
template<> struct GetBaseTraits<Base::A> { using type = Foo::CA; };
template<> struct GetBaseTraits<Base::B> { using type = Foo::CB; };
template<> struct GetBaseTraits<Base::C> { using type = Foo::CC; };

template<Base b>
typename GetBaseTraits<b>::type getBase(Foo f);

template<> typename GetBaseTraits<A>::type getBase<A>(Foo f) { return f.a; }
template<> typename GetBaseTraits<B>::type getBase<B>(Foo f) { return f.b; }
template<> typename GetBaseTraits<C>::type getBase<C>(Foo f) { return f.c; }

int main()
{
    Foo f{};
    Foo::CA ca = getBase<A>(f);
    Foo::CB cb = getBase<B>(f);
    Foo::CC cc = getBase<C>(f);
}


//template<typename Tin, typename Tout>
//Tout MixType(Tin input)
//{
//	Tout someType;
//	const string errMsg = "Jeez ...";
//
//	if (is_same<Tin,float>::value)
//	{
//		cout << "Got FLOAT input = " << input << endl;
//		someType = 5.5F;
//	}
//	else if (is_same<Tin,int>::value)
//	{
//		cout << "Got INT input = " << input << endl;
//		someType = -7;
//	}
//	else
//	{
//		someType = errMsg;
//	}
//
//	return someType;
//}
//
//
//int main()
//{
//	variant<string,int,float> multiTypedVar;
//
//	/* Expect INTeger ... (NOTE: always smart to enclose in try-catch ;-) */
//	int tst1 = MixType(123);
//	multiTypedVar = tst3;
//
//	cout << "..." << endl; // prints ...
//
//	return 0;
//}
