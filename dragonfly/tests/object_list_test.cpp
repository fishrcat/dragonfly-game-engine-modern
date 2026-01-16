// object_list_test.cpp — Unit tests for df::Manager

#include "object_list.h"

#include "gtest/gtest.h"

using namespace df;

class TestObject : public Object {
    public:
    explicit TestObject(const std::string &type) { setType(type); }
};

TEST(ObjectListTest, AppendAndCount) {
    ObjectList list;
    list.append(new TestObject("A"));
    list.append(new TestObject("B"));
    EXPECT_EQ(list.count(), 2);
}

TEST(ObjectListTest, Pop) {
    ObjectList list;
    list.append(new TestObject("A"));
    const auto obj = list.pop();
    EXPECT_EQ(obj->getType(), "A");
    EXPECT_EQ(list.count(), 0);
}

TEST(ObjectListTest, RemoveAndContains) {
    ObjectList list;
    auto *obj1 = new TestObject("A");
    auto *obj2 = new TestObject("B");
    list.append(obj1);
    list.append(obj2);

    EXPECT_TRUE(list.contains(obj1));
    EXPECT_TRUE(list.remove(obj1));
    EXPECT_FALSE(list.contains(obj1));
    EXPECT_EQ(list.count(), 1);
}

TEST(ObjectListTest, Insert) {
    ObjectList list;
    list.append(new TestObject("A"));
    list.insert(0, new TestObject("B"));
    EXPECT_EQ(list[0]->getType(), "B");
    EXPECT_EQ(list[1]->getType(), "A");
}

TEST(ObjectListTest, FindById) {
    ObjectList list;
    auto *obj1 = new TestObject("A");
    auto *obj2 = new TestObject("B");
    list.append(obj1);
    list.append(obj2);

    EXPECT_EQ(list.findById(obj1->getId()), obj1);
    EXPECT_EQ(list.findById(obj2->getId()), obj2);
    EXPECT_EQ(list.findById(9999), nullptr);
}

TEST(ObjectListTest, GetByTypeTemplate) {
    ObjectList list;
    struct A : TestObject {
        A() : TestObject("A") {}
    };
    struct B : TestObject {
        B() : TestObject("B") {}
    };

    auto *a1 = new A{};
    auto *a2 = new A{};
    auto *b1 = new B{};
    list.append(a1);
    list.append(a2);
    list.append(b1);

    const auto as = list.getByType("A");
    EXPECT_EQ(as.size(), 2);
}

TEST(ObjectListTest, Iterators) {
    ObjectList list;
    list.append(new TestObject("A"));
    list.append(new TestObject("B"));

    int count = 0;
    for (auto &obj : list) {
        EXPECT_TRUE(obj != nullptr);
        count++;
    }
    EXPECT_EQ(count, 2);
}

TEST(ObjectListTest, GetAll) {
    ObjectList list;
    auto *obj1 = new TestObject("A");
    auto *obj2 = new TestObject("B");
    list.append(obj1);
    list.append(obj2);

    const auto all = list.getAll();
    EXPECT_EQ(all.size(), 2);
    EXPECT_EQ(all[0], obj1);
    EXPECT_EQ(all[1], obj2);
}
