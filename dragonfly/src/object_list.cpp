// object_list.cpp — Container wrapping an owned vector of Object pointers with
// scripting syntax

#include "object_list.h"

#include <log_manager.h>

#include <algorithm>

namespace df {

ObjectList::ObjectList() = default;

auto ObjectList::count() const noexcept -> size_t { return m_objects.size(); }

void ObjectList::append(Object* obj) {
    m_objects.push_back(std::unique_ptr<Object>(obj));
}

void ObjectList::append(ObjectList& other) {
    for (auto& obj : other.m_objects) {
        m_objects.push_back(std::move(obj));
    }
    // TODO: Consider memory strat here to avoid manual deletes
    other.m_objects.clear();  // empty source list
}

auto ObjectList::pop() -> std::unique_ptr<Object> {
    if (m_objects.empty()) return nullptr;
    auto obj = std::move(m_objects.back());
    m_objects.pop_back();
    return obj;
}

auto ObjectList::remove(const Object* obj_ptr) -> bool {
    const auto it = std::ranges::find_if(
        m_objects, [&](const auto& o) -> auto { return o.get() == obj_ptr; });
    if (it != m_objects.end()) {
        m_objects.erase(it);
        return true;
    }
    return false;
}

auto ObjectList::contains(const Object* obj_ptr) const -> bool {
    return std::ranges::any_of(
        m_objects, [&](const auto& o) -> auto { return o.get() == obj_ptr; });
}

void ObjectList::insert(const size_t index, Object* obj) {
    if (index > m_objects.size()) {
        LM.writeLog(
            LogLevel::ERROR,
            std::format("ObjectList::insert index {} out of range (size {})",
                        index, m_objects.size()));
        return;
    }

    m_objects.insert(
        m_objects.begin() +
            static_cast<std::vector<std::unique_ptr<Object>>::difference_type>(
                index),
        std::unique_ptr<Object>(obj));
}

auto ObjectList::findById(const int id) const -> Object* {
    for (const auto& obj : m_objects) {
        if (obj->getId() == id) return obj.get();
    }
    return nullptr;
}

auto ObjectList::begin() noexcept -> iterator { return m_objects.begin(); }
auto ObjectList::end() noexcept -> iterator { return m_objects.end(); }
auto ObjectList::begin() const noexcept -> const_iterator {
    return m_objects.begin();
}
auto ObjectList::end() const noexcept -> const_iterator {
    return m_objects.end();
}

auto ObjectList::operator[](const size_t index) const -> Object* {
    return m_objects[index].get();
}

}  // namespace df
