// #pragma once

// #include <type_traits>
// #include <memory>

// template<typename T>
// class Builder
// {
// public:
//     Builder() : entity(nullptr)
//     {

//     }

//     template<typename... Args>
//     void reset(Args&&... args)
//     {
//         entity = std::make_unique<T>(std::forward<Args>(args)...);
//     }

//     T *getProduct()
//     {
//         return entity.get();
//     }

//     void setPosition(const Vector2 &p)
//     {
//         if(entity != nullptr)
//         {
//             entity->translate(p);
//         }
//     }

//     void setRotation(const Vector2 &r)
//     {
//         if(entity != nullptr)
//         {
//             entity->rotate(r);
//         }
//     }

//     void setScale(const Vector2 &s)
//     {
//         if(entity != nullptr)
//         {
//             entity->scale(s);
//         }
//     }

//     void setState(const State &state)
//     {
//         if(entity != nullptr)
//         {
//             entity->setState(state);
//         }
//     }

//     void setComponent(Component *c)
//     {
//         if(entity != nullptr)
//         {
//             entity->plug(c);
//         }
//     }

// private:
//     std::unique_ptr<T> entity;

//     static_assert(std::is_base_of<GameObject, T>::value, "T must be a GameObject.");
// };