/* ************************************************************************** */
/*                                              ############       ####       */
/*                                              ############       ####       */
/*   s21_multiset.h                                         ####       ####   */
/*                                                          ####       ####   */
/*   By: hubertfu@student.21-school.ru              ########           ####   */
/*                                                  ########           ####   */
/*                                              ####                   ####   */
/*   Created: 2022-10-30                        ####                   ####   */
/*   Updated: 2022-11-22                            ############       ####   */
/*                                                  ############       ####   */
/* ************************************************************************** */

/**
 * @file s21_multiset.h
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @brief s21::multiset (мультимножество) — это ассоциативный контейнер,
 * содержащий отсортированный набор объектов типа Key. В отличие от set,
 * допускается несколько ключей с эквивалентными значениями. Сортировка
 * осуществляется с помощью функции сравнения ключей Compare. Операции поиска,
 * вставки и удаления имеют логарифмическую сложность.
 *
 * Набор реализован в виде красно-черного дерева.
 *
 * @version 1.0
 * @date 2022-11-22
 *
 * @copyright hubertfu (c) 2022
 */

#ifndef S21_CONTAINERS_S21_CONTAINERS_S21_MULTISET_H_
#define S21_CONTAINERS_S21_CONTAINERS_S21_MULTISET_H_

#include "s21_tree.h"

namespace s21 {
template <class Key>
class multiset {
  public:
    // Тип ключа элемента (Key — параметр шаблона)
    using key_type = Key;
    // Тип значения элемента (само значение является ключом)
    using value_type = key_type;
    // Тип ссылки на элемент
    using reference = value_type &;
    // Тип константной ссылки на элемент
    using const_reference = const value_type &;
    // Внутренний класс для дерева
    using tree_type = RedBlackTree<value_type>;
    // Внутренний класс для итератора
    using iterator = typename tree_type::iterator;
    // Внутренний класс для константного итератора
    using const_iterator = typename tree_type::const_iterator;
    // Тип для размера контейнера
    using size_type = std::size_t;

    /**
     * @brief Конструктор по умолчанию, создает пустое мультимножество
     */
    multiset() : tree_(new tree_type{}) {
    }

    /**
     * @brief Конструктор списка инициализаторов, создает мультимножество,
     * инициализированное с помощью std::initializer_list.
     *
     * @param items Список создаваемых элементов
     */
    multiset(std::initializer_list<value_type> const &items) : multiset() {
        for (auto item : items) {
            insert(item);
        }
    }

    /**
     * @brief Конструктор копирования (Copy Constructor). Создает
     * мультимножество путем копирования данных из объекта other.
     *
     * @param other копируемый объект
     */
    multiset(const multiset &other) : tree_(new tree_type(*other.tree_)) {
    }

    /**
     * @brief Конструктор переноса (Move Constructor). Создает мультимножество
     * путем передачи владения ресурсами от объекта other.
     *
     * @param other переносимый объект
     */
    multiset(multiset &&other) noexcept
        : tree_(new tree_type(std::move(*other.tree_))) {
    }

    /**
     * @brief Оператор присваивания копированием.
     *
     * @param other Копируемое мультимножество
     * @return list& Созданная копия
     */
    multiset &operator=(const multiset &other) {
        *tree_ = *other.tree_;
        return *this;
    }

    /**
     * @brief Оператор присваивания переносом
     *
     * @param other Перемещаемое мультимножество
     * @return list& Результат перемещения
     */
    multiset &operator=(multiset &&other) noexcept {
        *tree_ = std::move(*other.tree_);
        return *this;
    }

    /**
     * @brief Деструктор объекта (Destructor)
     */
    ~multiset() {
        delete tree_;
        // Для избежания сбоев при повторном освобождении указателей и повторном
        // использовании указателей
        tree_ = nullptr;
    }

    /**
     * @brief Возвращает итератор на начало контейнера.
     * @details Для пустого контейнера возвращаемый итератор будет равен end().
     *
     * @return iterator
     */
    iterator begin() noexcept {
        return tree_->Begin();
    }

    /**
     * @brief Версия begin() для const
     *
     * @return const_iterator
     */
    const_iterator begin() const noexcept {
        return tree_->Begin();
    }

    /**
     * @brief Возвращает итератор на конец контейнера (элемент после последнего
     * элемента контейнера).
     * @details Элемент является служебной "заглушкой" и его разыменование - UB
     *
     * @return iterator
     */
    iterator end() noexcept {
        return tree_->End();
    }

    /**
     * @brief Версия end() для const
     *
     * @return const_iterator
     */
    const_iterator end() const noexcept {
        return tree_->End();
    }

    /**
     * @brief Проверяет, является ли контейнер пустым
     *
     * @return true контейнер пустой
     * @return false контейнер непустой
     */
    bool empty() const noexcept {
        return tree_->Empty();
    }

    /**
     * @brief Возвращает количество элементов в контейнере
     *
     * @return size_type
     */
    size_type size() const noexcept {
        return tree_->Size();
    }

    /**
     * @brief Возвращает максимальное количество элементов, которое может
     * содержать контейнер из-за ограничений реализации системы или библиотеки.
     *
     * @warning В реальности значение max_size() никогда не будет достижимо.
     *
     * @details Это число не зависит от состояния ОС или доступной памяти, а
     * определяется только реализацией контейнера. Во время выполнения размер
     * контейнера может быть ограничен значением, меньшим max_size(), чем объем
     * доступной оперативной памяти.
     *
     * В данном контейнере мы храним только дерево, поэтому значение max_size()
     * зависит от max_size() реализации дерева.
     *
     */
    size_type max_size() const noexcept {
        return tree_->MaxSize();
    }

    /**
     * @brief Удаляет содержимое контейнера (все элементы). Контейнер при этом
     * остается консистентным.
     */
    void clear() noexcept {
        tree_->Clear();
    }

    /**
     * @brief Вставляет элемент со значением value в контейнер. Если в
     * контейнере есть элементы с эквивалентным ключом, вставка выполняется по
     * верхней границе этого диапазона.
     *
     * @param value Значение элемента для вставки
     * @return iterator Итератор, указывающий на вставленный элемент
     */
    iterator insert(const value_type &value) {
        return tree_->Insert(value);
    }

    /**
     * @brief Удаляет элемент на позиции pos. Ссылки и итераторы на стертые
     * элементы становятся недействительными. Другие ссылки и итераторы не
     * затрагиваются.
     *
     * @param pos
     */
    void erase(iterator pos) noexcept {
        tree_->Erase(pos);
    }

    /**
     * @brief Обменяет содержимое контейнера на содержимое other
     *
     * @param other
     */
    void swap(multiset &other) noexcept {
        tree_->Swap(*other.tree_);
    }

    /**
     * @brief Извлекает все элементы из other и вставляет их в this.
     * @details Детали реализации описаны в методе Merge() реализации дерева.
     *
     * @param other
     */
    void merge(multiset &other) noexcept {
        tree_->Merge(*other.tree_);
    }

    /**
     * @brief Возвращает количество элементов с ключом, эквивалентным key.
     *
     * @param key
     * @return size_type
     */
    size_type count(const key_type &key) const {
        // Находим первый элемент, который не меньше key
        auto lower_iterator = lower_bound(key);
        if (*lower_iterator != key) {
            // Если этот элемент не равен key, значит количество таких элементов
            // 0
            return 0;
        }

        // Если этот элемент равен key, то двигаем итератор до тех пор, пока не
        // встретим элемент больше key и на каждом шаге увеличиваем счетчик
        // result_count
        auto end_iterator = end();
        size_type result_count = 0;
        while (lower_iterator != end_iterator && *lower_iterator == key) {
            ++result_count;
            ++lower_iterator;
        }

        // возвращаем посчитанное в result_count количество
        return result_count;
    }

    /**
     * @brief Находит элемент с ключом, эквивалентным key.
     *
     * @param key Искомый ключ
     * @return iterator Итератор найденного элемента. Если такой элемент не
     * найден, возвращается end().
     */
    iterator find(const key_type &key) noexcept {
        return tree_->Find(key);
    }

    /**
     * @brief Версия find() для константного объекта
     *
     * @param key Искомый ключ
     * @return const_iterator Итератор найденного элемента. Если такой элемент
     * не найден, возвращается end().
     */
    const_iterator find(const key_type &key) const noexcept {
        return tree_->Find(key);
    }

    /**
     * @brief Проверяет, есть ли в контейнере элемент с ключом, эквивалентным
     * key.
     *
     * @param key
     * @return true Есть
     * @return false Нет
     */
    bool contains(const key_type &key) const noexcept {
        return tree_->Find(key) != tree_->End();
    }

    /**
     * @brief Возвращает диапазон, содержащий все элементы с ключом key.
     * Диапазон определяется двумя итераторами, один из которых указывает на
     * первый элемент, который не меньше ключа, а другой указывает на первый
     * элемент больше, чем ключ.
     *
     * Эквивалентно тому, что первый итератор может быть получен с помощью
     * функции lower_bound(), а второй — с помощью функции upper_bound().
     *
     * @todo вызов lower_bound() и upper_bound() внутри функции очень просто, но
     * не очень эффективно, т.к. делается 2 прохода по дереву. Эффективнее один
     * раз вызвать lower_bound(), а затем уже посчитать второй итератор от
     * результата lower_bound().
     *
     * @param key ключевое значение, с которым сравниваются элементы
     * @return std::pair<iterator, iterator> Пара итераторов, определяющих
     * желаемый диапазон: первый указывает на первый элемент, который не меньше
     * ключа, а второй указывает на первый элемент больше, чем ключ.
     */
    std::pair<iterator, iterator> equal_range(const key_type &key) noexcept {
        iterator first = lower_bound(key);
        iterator second = upper_bound(key);

        return std::pair<iterator, iterator>{first, second};
    }

    /**
     * @brief Версия equal_range() для const-объектов.
     *
     * @param key ключевое значение, с которым сравниваются элементы
     * @return std::pair<const_iterator, const_iterator>
     */
    std::pair<const_iterator, const_iterator>
    equal_range(const key_type &key) const noexcept {
        const_iterator first = lower_bound(key);
        const_iterator second = upper_bound(key);

        return std::pair<const_iterator, const_iterator>{first, second};
    }

    /**
     * @brief Возвращает итератор, указывающий на первый элемент, который не
     * меньше (т.е. больше или равен) key.
     *
     * @param key ключевое значение, с которым сравниваются элементы
     * @return iterator Итератор, указывающий на первый элемент, который не
     * меньше key. Если такой элемент не найден, возвращается итератор End().
     */
    iterator lower_bound(const key_type &key) noexcept {
        return tree_->LowerBound(key);
    }

    /**
     * @brief Версия lower_bound() для const-объектов.
     *
     * @param key ключевое значение, с которым сравниваются элементы
     * @return iterator Итератор, указывающий на первый элемент, который не
     * меньше key. Если такой элемент не найден, возвращается итератор End().
     */
    const_iterator lower_bound(const key_type &key) const {
        return tree_->LowerBound(key);
    }

    /**
     * @brief Возвращает итератор, указывающий на первый элемент, который больше
     * key.
     *
     * @param key ключевое значение, с которым сравниваются элементы
     * @return iterator Итератор, указывающий на первый элемент, который больше
     * key. Если такой элемент не найден, возвращается итератор End().
     */
    iterator upper_bound(const key_type &key) noexcept {
        return tree_->UpperBound(key);
    }

    /**
     * @brief Версия upper_bound() для const-объектов.
     *
     * @param key ключевое значение, с которым сравниваются элементы
     * @return iterator Итератор, указывающий на первый элемент, который больше
     * key. Если такой элемент не найден, возвращается итератор End().
     */
    const_iterator upper_bound(const key_type &key) const noexcept {
        return tree_->UpperBound(key);
    }

    /**
     * @brief Размещает новые элементы args в контейнер. Если в контейнере
     * есть элементы с эквивалентным ключом, вставка выполняется по верхней
     * границе этого диапазона.
     *
     * @details Детали реализации описаны в методе Emplace() реализации дерева.
     *
     * @tparam Args Пакет параметров шаблона (Parameter pack)
     * @param args Уже созданные элементы, которые необходимо вставить в
     * соответствующий контейнер.
     * @return std::vector<std::pair<iterator, bool>> Т.к. функция может
     * вставить несколько элементов, то возвращается вектор, содержащий пары
     * результата вставки для каждого вставляемого элемента. Формат пары
     * идентичен методу insert()
     */
    template <typename... Args>
    std::vector<std::pair<iterator, bool>> emplace(Args &&...args) {
        return tree_->Emplace(std::forward<Args>(args)...);
    }

  private:
    tree_type *tree_;
};

}  // namespace s21

#endif  // S21_CONTAINERS_S21_CONTAINERS_S21_MULTISET_H_
