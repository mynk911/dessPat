#include "gtest/gtest.h"

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
    //void* somePointer = (void *)"test";
    //char c = mcpp::safe_reinterpret_cast<char>(somePointer);
    void* somePointer = (void *)"test";
    char* c = mcpp::safe_reinterpret_cast<char*>(somePointer);
}
