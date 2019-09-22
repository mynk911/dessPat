#include "gtest/gtest.h"

#include <type_traits>

#include "mcpp.hpp"

TEST(mcpp, OpNewCreatorPolicyTest)
{
    mcpp::WidgetManager<mcpp::OpNewCreator> wm;
    auto res = wm.DoSomething();
    ASSERT_EQ(res->GetX(), 5);
    delete res;
}

TEST(mcpp, MallocCreatorPolicyTest)
{
    mcpp::WidgetManager<mcpp::MallocCreator> wm;
    auto res = wm.DoSomething();
    ASSERT_EQ(res->GetX(), 5);
    res->~Widget();
    std::free(res);
}

TEST(mcpp, PrototypeCreatorPolicyTest)
{
    auto proto = new mcpp::Widget(23);
    mcpp::WidgetManager<mcpp::PrototypeCreator> wm(proto);
    auto res = wm.DoSomething();
    ASSERT_EQ(res->GetX(), 23);
    delete res;
    delete proto;
}

TEST(mcpp, SwitchPrototypeTest)
{
    auto proto = new mcpp::Widget(23);
    mcpp::WidgetManager<mcpp::PrototypeCreator> wm(proto);
    auto proto2 = new mcpp::Widget(27);
    wm.SwitchPrototype(proto2);
    auto res = wm.DoSomething();
    ASSERT_EQ(res->GetX(), 27);
    delete res;
    delete proto2;
}

TEST(mcpp, staticAssert)
{
    void* somePointer = (void *)"test";
    //char c = mcpp::safe_reinterpret_cast<char>(somePointer);
    char* ch = mcpp::safe_reinterpret_cast<char*>(somePointer);
}

class Arg {
public:
    Arg(int a) : value(a) {}
    int value = 0;
};
class caller {
public:
    void Call(Arg x)
    {
        mem = x.value;
    }
    int mem = 0;
};

TEST(mcpp, localClass)
{
    caller c;
    EXPECT_EQ(c.mem, 0);
    Arg a(10);
    EXPECT_EQ(a.value, 10);
    auto inf = mcpp::MakeAdapter(c, a);
    inf->Fun();
    ASSERT_EQ(c.mem, a.value);
}

class polymorph {
public:
    polymorph() {}
    virtual polymorph* clone() { return nullptr; }
protected:
    polymorph(const polymorph&) {}
};

class nonpolymorph {
public:
    nonpolymorph() {}
    nonpolymorph(const nonpolymorph& other) {}
};
TEST(mcpp, ConstantToType)
{
    auto p = new polymorph();
    //Below line should not compile. Compiler should complain about not being
    //able to access polymorph copy constructor
    //mcpp::UnNiftyContainer<polymorph, true> n;
    mcpp::NiftyContainer<polymorph, true> n;
    n.someFunc(p);

    auto np = new nonpolymorph();
    //Below line should not compile. Compiler should complain about not being
    // to find nonpolymorph::clone
    //mcpp::UnNiftyContainer<nonpolymorph, false> n2;
    mcpp::NiftyContainer<nonpolymorph, false> n2;
    n2.someFunc(np);
}

TEST(mcpp, Type2Type)
{
    auto x = mcpp::Create("Hello", mcpp::Type2Type < std::string >());
    mcpp::Widget2* y = mcpp::Create('a', mcpp::Type2Type< mcpp::Widget2 >());
    delete x, y;
}

TEST(mcpp, TypeSelection)
{
    ASSERT_EQ(true, (std::is_same< mcpp::UnNiftyContainer2<int, true>::ValueType, int* >::value));
    ASSERT_EQ(true, (std::is_same< mcpp::UnNiftyContainer2<int, false>::ValueType, int >::value));
    ASSERT_EQ(true, (std::is_same< mcpp::NiftyContainer2<int, true>::ValueType, int* >::value));
    ASSERT_EQ(true, (std::is_same< mcpp::NiftyContainer2<int, false>::ValueType, int >::value));
}

TEST(mcpp, IsConvertible)
{
    ASSERT_EQ(true, (mcpp::Conversion< int, double >::exists));
    ASSERT_EQ(false, (mcpp::Conversion< char, char* >::exists));
    ASSERT_EQ(false, (mcpp::Conversion< size_t, std::vector<int> >::exists));
}

TEST(mcpp, IsSame)
{
    ASSERT_EQ(false, (mcpp::Conversion< int, double >::sameType));
    ASSERT_EQ(true, (mcpp::Conversion< double, double >::sameType));
}

class polymorphderivative : public polymorph {
public:
    polymorphderivative() : polymorph() {}
    virtual polymorphderivative* clone() override { return nullptr; }
    polymorphderivative(const polymorphderivative& other) : polymorph(other) {}
};

TEST(mcpp, InheritsFrom)
{
    ASSERT_EQ(false, SUPERSUBCLASS(polymorph, nonpolymorph));
    ASSERT_EQ(true, SUPERSUBCLASS(polymorph, polymorphderivative));
}

/* TEST(mcpp, TypeInfo)
{
    mcpp::TypeInfo info = typeid(polymorphderivative);
    polymorph *obj = new polymorphderivative();
    ASSERT_EQ(info, typeid(*obj));
} */

TEST(mcpp, TypeTraitsPointerTraits)
{
    ASSERT_EQ(false, mcpp::TypeTraits<std::vector<int>::iterator>::isPointer);
    ASSERT_EQ(false, (std::is_same<std::vector<int>::iterator, int*>::value));
}

TEST(mcpp, TypeTraitsReferenceTraits)
{
    ASSERT_EQ(false, mcpp::TypeTraits<std::vector<int>::iterator>::isReference);
    ASSERT_EQ(false, (std::is_same<std::vector<int>::iterator, int&>::value));
}

/*TEST(mcpp, TypeTraitsPtoMTraits)
{
    // implement after PToM discussion in chapter 5
}*/

/*TEST(mcpp, TypeTraitsFundamental)
{
    // implement after TypeLists discussion in chapter 5
}*/

/*TEST(mcpp, TypeTraitsParameterType)
{
    // implement after TypeLists discussion in chapter 5
}*/

TEST(mcpp, TypeTraitsNonConst)
{
    ASSERT_EQ(true, (std::is_same< mcpp::TypeTraits< const int >::NonConstType, int >::value));
}

// enum class doesn't work without an extra parameter of class name
enum CopyAlgoSelector {Conservative, Fast};

template < typename InIt, typename OutIt >
int CopyImp(InIt first, InIt last, OutIt result, mcpp::Int2Type<Conservative>)
{
    for (; first != last; ++first, ++result)
        *result = *first;
    return 0;
}

template < typename InIt, typename OutIt >
int CopyImp(InIt first, InIt last, OutIt result, mcpp::Int2Type<Fast>)
{
    for (; first != last; ++first, ++result)
        *result = *first;
    return 1;
}

template < typename InIt, typename OutIt >
int Copy(InIt first, InIt last, OutIt result)
{
    typedef mcpp::TypeTraits<InIt>::PointeeType SrcPointee;
    typedef mcpp::TypeTraits<OutIt>::PointeeType DstPointee;
    enum {
        copyAlgo = mcpp::TypeTraits<InIt>::isPointer &&
        mcpp::TypeTraits<OutIt>::isPointer &&
        //mcpp::TypeTraits<SrcPointee>::IsFundamental &&
        //mcpp::TypeTraits<DstPointee>::IsFundamental &&
        //mcpp::SupportsBitwiseCopy<SrcPointee>::result &&
        //mcpp::SupportsBitwiseCopy<DstPointee>::result &&
        sizeof(SrcPointee) == sizeof(DstPointee) ? Fast : Conservative
    };
    return CopyImp(first, last, result, mcpp::Int2Type<copyAlgo>());
}

class POD
{
public:
    int x;
};

class NPOD
{
public:
    int x;
    NPOD() {};
    NPOD(int a) { x = a; }
    virtual ~NPOD() {}
};

template<> struct mcpp::SupportsBitwiseCopy<POD>
{
    enum { result = true };
};

// implement after TypeLists discussion in chapter 5
TEST(mcpp, TypeTraitsUsage)
{
    int arr[10] = { 5 };
    int dst[10] = { 0 };

//    ASSERT_EQ(1, Copy(arr, arr + 10, dst));

    std::vector<int> v(10, 5),d;
//    ASSERT_EQ(0, Copy(v.begin(), v.end(), std::back_inserter(d)));

    POD arr2[10] = { 5 };
    POD dst2[10] = { 0 };

//    ASSERT_EQ(1, Copy(arr2, arr2 + 10, dst2));
    NPOD arr3[10] = { 5 };
    NPOD dst3[10] = { 0 };

//    ASSERT_EQ(1, Copy(arr3, arr3 + 10, dst3));
}
