// object_list.h — Container wrapping an owned vector of Object pointers with
// scripting syntax

#pragma once

#include <cstddef>
#include <memory>
#include <string>
#include <vector>

#include "object.h"

namespace df {

class ObjectList {
    public:
    using iterator = std::vector<std::unique_ptr<Object>>::iterator;
    using const_iterator = std::vector<std::unique_ptr<Object>>::const_iterator;

    ObjectList();
    ~ObjectList() = default;

    auto count() const noexcept -> size_t;

    void append(Object* obj);
    void append(ObjectList& other);
    auto pop() -> std::unique_ptr<Object>;
    auto remove(const Object* obj_ptr) -> bool;
    auto contains(const Object* obj_ptr) const -> bool;
    void insert(size_t index, Object* obj);
    auto getAll() const -> std::vector<Object*>;

    auto findById(int id) const -> Object*;
    [[nodiscard]] auto getByType(std::string_view type) const
        -> std::vector<Object*>;

    auto begin() noexcept -> iterator;
    auto end() noexcept -> iterator;
    auto begin() const noexcept -> const_iterator;
    auto end() const noexcept -> const_iterator;

    auto operator[](size_t index) const
        -> Object*;  // Const pointer to mutable object

    private:
    std::vector<std::unique_ptr<Object>> m_objects;
};

}  // namespace df
