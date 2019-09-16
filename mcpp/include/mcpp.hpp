#ifndef MCPP_MCPP_H_
#define MCPP_MCPP_H_

#include <cstdlib>
#include <utility>
#include <typeinfo>

/// main namespace for mcpp
namespace mcpp {

/// \group CreationPolicy
/// Simple Policy Example - Creation Policy.
/// These classes implement Creation Policy. Creation Policy specifies that
/// implementations should expose a member Create which returns a pointer to
/// created object
/// \{

/*! operator new as creation policy.
 */
template<class T>
struct OpNewCreator
{
    static T* Create()
    {
        return new T;
    }
protected:
    // method is protected to prevent user from deleting implementing class
    // using policy pointer
    ~OpNewCreator() {}
};

/*! malloc and placement new as creation policy.
 */
template<class T>
struct MallocCreator
{
    static T* Create()
    {
        void* buf = std::malloc(sizeof(T));
        if(!buf) return 0;
        return new(buf) T;
    }
protected:
    ~MallocCreator() {}
};

/*! prototype as creation policy.
 * provides setter and getters for protype which users of this policy
 * implementation can use
 */
template<class T>
struct PrototypeCreator
{
    PrototypeCreator(T* pObj)
        :pPrototype_(pObj)
    {}
    T* Create()
    {
        return pPrototype_ != nullptr
                ? pPrototype_->Clone()
                : nullptr;
    }
    T* GetPrototype() { return pPrototype_;}
    void SetPrototype(T* pObj) {pPrototype_ = pObj;}
protected:
    ~PrototypeCreator() {}
private:
    T* pPrototype_;
};

/// \}

class Widget
{
public:
    Widget(int val = 5) : x(val){}
    int GetX() {return x;}
    Widget* Clone()
    {
        auto res = new Widget();
        init(res);
        return res;
    }
private:
    void init(Widget* other) {
        other->x = this->x;
    }
    int x;
};

class Gadget
{
public:
    Gadget() {}
    int GetX() {return x;}
private:
    int x = 10;
};

/// Implementing policy classes with template template parameters
template <template <class> class CreationPolicy>
class WidgetManager : public CreationPolicy<Widget>
{
public:
    WidgetManager()
        : CreationPolicy<Widget>()
    {}
    WidgetManager(Widget* wG)
        : CreationPolicy<Widget>(wG)

    {}
    Widget* DoSomething()
    {
        Widget *wG = CreationPolicy<Widget>::Create();
        //Gadget *pW = CreationPolicy<Gadget>().Create();
        return wG;
    }

    /// method only generated for prototype policy.
    void SwitchPrototype(Widget* pNewPrototype)
    {
        CreationPolicy<Widget>& myPolicy = *this;
        delete myPolicy.GetPrototype();
        myPolicy.SetPrototype(pNewPrototype);
    }
};

/// static assertion
template<bool> struct CompileTimeChecker
{
    CompileTimeChecker(...);
};

template<> struct CompileTimeChecker<false> {};

#define STATIC_CHECK(expr, msg) \
{\
    class ERROR_##msg {};\
    (void)sizeof(CompileTimeChecker<(expr) != 0>((ERROR_##msg())));\
}

template <class To, class From>
To safe_reinterpret_cast(From from)
{
    STATIC_CHECK(sizeof(From) <= sizeof(To), Destination_Type_Too_Narrow);
    return reinterpret_cast<To>(from);
}

// a sample local class implementation.
class Interface
{
public:
    Interface();
    virtual ~Interface();
    virtual void Fun() = 0;
};

Interface::Interface()
{
}

Interface::~Interface()
{
}

template <class T, class P>
Interface* MakeAdapter(T& obj, const P& arg)
{
    class Local : public Interface
    {
    public:
        Local(T& obj, const P& arg):
            obj_(obj), arg_(arg) {}
        virtual void Fun()
        {
            obj_.Call(arg_);
        }
    private:
        T& obj_;
        P arg_;
    };
    return new Local(obj, arg);
};

// IntToType demo. IntToType paired with function overlading allows
// template to behave differently for different values of constant
// template argument
template <int v>
struct Int2Type
{
    enum {value = v};
};

template <typename T, bool isPolymorphic>
class UnNiftyContainer
{
public:
    void someFunc(T* pObj)
    {
        if(isPolymorphic) T* pNobj = pObj->clone();
        else T* pNobj = new T(*pObj);
    }
};

template <typename T, bool isPolymorphic>
class NiftyContainer
{
private:
    void someFunc(T* pObj, Int2Type < true > )
    {
        T* pNobj = pObj->clone();
    }

    void someFunc(T* pObj, Int2Type < false > )
    {
        T* pNobj = new T(*pObj);
    }
public:
    void someFunc(T* pObj)
    {
        someFunc(pObj, Int2Type < isPolymorphic >());
    }
};

// Type2Type demo. Partial specialization of functions can be simulated
// using Type2Type paired with function overloading
template < typename T >
struct Type2Type
{
    typedef T originalType;
};

template < typename T, typename U >
T* Create(const U& arg, Type2Type < T > )
{
    return new T(arg);
}

class Widget2
{
public:
    Widget2(char a, int x) {}
};

template < typename U >
Widget2* Create(const U& arg, Type2Type < Widget2 >)
{
    return new Widget2(arg, -1);
}

// Type Selection Demo. Using partial template specialization to select
// types at compile type

// using traits classes
template < typename T, bool isPolymorphic >
struct UnNiftyContainer2ValueTraits
{
    typedef T* ValueType;
};

template < typename T >
struct UnNiftyContainer2ValueTraits<T, false>
{
    typedef T ValueType;
};

template < typename T, bool isPolymorphic >
struct UnNiftyContainer2
{
    typedef UnNiftyContainer2ValueTraits< T, isPolymorphic > Traits;
    typedef typename Traits::ValueType ValueType;
};

// using Loki Select class template
template < bool flag , typename T, typename U >
struct Select
{
    typedef T Result;
};

template < typename T, typename U >
struct Select<false, T, U>
{
    typedef U Result;
};

template < typename T, bool isPolymorphic >
struct NiftyContainer2
{
    typedef typename Select< isPolymorphic, T*, T >::Result ValueType;
};

// Detecting convertibility and inheritence at compile time\

// checks if T is convertible to U and if T is same type as U
template < typename T, typename U >
class Conversion
{
    typedef char Small;
    class Big { char dummy[2]; };
    static Small Test(U);
    static Big Test(...);
    static T MakeT();
public:
    enum {
        exists = sizeof(Test(MakeT())) == sizeof(Small),
        sameType = false
    };
};

template < typename T >
class Conversion < T, T >
{
public:
    enum { exists = true, sameType = true };
};

// uses conversion to check inheritence
#define SUPERSUBCLASS(T, U) \
    (mcpp::Conversion<const U*, const T*>::exists &&\
     !mcpp::Conversion<const T*, const void *>::sameType)

// TypeInfo wrapper aroud type_info
// At this point only declaration in book. Could add definition myself
// but let's wait it out
class TypeInfo
{
public:
    //constructors/destructors
    TypeInfo(); // needed for containers
    TypeInfo(const std::type_info&);
    TypeInfo(const TypeInfo&);
    TypeInfo& operator=(const TypeInfo&);
    // Compatibility functions
    bool before(const TypeInfo&) const;
    const char* name() const;
private:
    const std::type_info* pInfo_;
};

//comparison operators
bool operator==(const TypeInfo&, const TypeInfo&);
bool operator!=(const TypeInfo&, const TypeInfo&);
bool operator<(const TypeInfo&, const TypeInfo&);
bool operator<=(const TypeInfo&, const TypeInfo&);
bool operator>(const TypeInfo&, const TypeInfo&);
bool operator>=(const TypeInfo&, const TypeInfo&);

// NullType and EmptyType

class NullType {};
class EmptyType {};

// TypeTraits facility

template < typename T >
class TypeTraits
{
private:
    template < typename U >
    struct PointerTraits
    {
        enum { result = false };
        typedef NullType PointeeType;
    };

    template < typename U >
    struct PointerTraits<U*>
    {
        enum { result = true };
        typedef U PointeeType;
    };
public:
    enum { isPointer = PointerTraits<T>::result };
    typedef typename PointerTraits<T>::PointeeType PointeeType;
};

}
#endif // MCPP_MCPP_H_