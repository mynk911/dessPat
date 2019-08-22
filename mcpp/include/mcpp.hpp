#ifndef MCPP_MCPP_H_
#define MCPP_MCPP_H_

#include <cstdlib>
#include <utility>

/// main namespace for mcpp
namespace mcpp {

/// \group CreationPolicy
/// Simple Policy Example - Creation Policy.
/// These classes implement Creation Policy. Creation Policy specifies that
/// implementations should expose a member Create which returns a pointer to
/// created object
/// \{

/*! operator new as cretion policy.
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


}
#endif // MCPP_MCPP_H_
