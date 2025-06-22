/**
 * @file Singleton.hpp
 * @brief Реализация шаблонного синглтона с ручным управлением временем жизни объекта.
 *
 * Предоставляет контроль над созданием, уничтожением и доступом к единственному экземпляру типа `T`.
 */

#ifndef LIBZM_INC_SINGLETON_HPP_
#define LIBZM_INC_SINGLETON_HPP_

#include <utility>   ///< Для std::forward
#include <cstddef>   ///< Для std::byte и alignas

/**
 * @brief Шаблон класса Singleton для создания одного экземпляра типа `T`.
 *
 * @tparam T Тип, для которого реализуется синглтон.
 */
template<typename T>
class Singleton
{
public:

    /// Упрощённый псевдоним для типа `T`.
    using type = T;

    /**
     * @brief Создаёт экземпляр объекта типа `T` с переданными аргументами.
     *
     * @tparam TArgs Параметры конструктора типа `T`.
     * @param args Аргументы, которые будут переданы в конструктор `T`.
     *
     * @note Если объект уже создан, повторное создание игнорируется.
     */
    template <typename... TArgs>
    static void create(TArgs&&... args)
    {
        Data& data = get_data();

        if (!data.valid)
        {
            // Размещаем объект в заранее выделенном сыром буфере
            T* p = reinterpret_cast<T*>(&data.storage);
            ::new (p) T(std::forward<TArgs>(args)...);  ///< placement new
            data.valid = true;
        }
    }

    /**
     * @brief Уничтожает экземпляр объекта типа `T`, если он был создан.
     */
    static void destroy()
    {
        Data& data = get_data();

        if (data.valid)
        {
            T* p = reinterpret_cast<T*>(&data.storage);
            p->~T();             ///< Явный вызов деструктора
            data.valid = false;  ///< Отмечаем как уничтоженный
        }
    }

    /**
     * @brief Возвращает ссылку на экземпляр объекта типа `T`.
     *
     * @return Ссылка на объект типа `T`.
     *
     * @warning Если объект не был создан, поведение неопределено (в данной реализации бесконечный цикл).
     */
    static T& instance()
    {
        Data& data = get_data();

        if (!data.valid)
        {
            while (true) {}  ///< Простой способ "защититься" от вызова до create()
        }

        return *reinterpret_cast<T*>(&data.storage);
    }

    /**
     * @brief Проверяет, был ли экземпляр объекта создан.
     *
     * @return true если объект создан, иначе false.
     */
    static bool isCreated()
    {
        Data& data = get_data();
        return data.valid;
    }

private:

    /**
     * @brief Вспомогательная структура, хранящая данные синглтона.
     *
     * Содержит выровненный буфер под объект и флаг валидности.
     */
    struct Data
    {
        /// Конструктор инициализирует флаг как false.
        Data() : valid(false) {}

        alignas(T) std::byte storage[sizeof(T)]; ///< Сырой выровненный буфер под объект T
        bool valid;                              ///< Флаг, указывающий, был ли объект создан
    };

    /**
     * @brief Возвращает ссылку на статические данные `Data`.
     *
     * @return Ссылка на статический экземпляр `Data`.
     */
    static Data& get_data()
    {
        static Data data;  ///< Статическая переменная живёт всё время работы программы
        return data;
    }

    /// Удаляем конструктор — нельзя создать экземпляр Singleton напрямую.
    Singleton() = delete;

    /// Удаляем конструктор копирования.
    Singleton(const Singleton&) = delete;

    /// Удаляем оператор присваивания.
    Singleton& operator=(const Singleton&) = delete;
};

#endif /* LIBZM_INC_SINGLETON_HPP_ */
