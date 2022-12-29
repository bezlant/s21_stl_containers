/* ************************************************************************** */
/*                                              ############       ####       */
/*                                              ############       ####       */
/*   s21_map.h                                              ####       ####   */
/*                                                          ####       ####   */
/*   By: hubertfu@student.21-school.ru              ########           ####   */
/*                                                  ########           ####   */
/*                                              ####                   ####   */
/*   Created: 2022-10-24                        ####                   ####   */
/*   Updated: 2022-11-22                            ############       ####   */
/*                                                  ############       ####   */
/* ************************************************************************** */

/**
 * @file s21_map.h
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @brief s21::map (словарь) — это отсортированный ассоциативный контейнер,
 * содержащий пары ключ-значение с уникальными ключами. Ключи сортируются с
 * помощью структуры MapValueComparator. Операции поиска, удаления и вставки
 * имеют логарифмическую сложность.
 *
 * Набор реализован в виде красно-черного дерева.
 *
 * Словарь реализован путем хранения std::pair<Key, Type> в бинарном дереве.
 * Т.к. уникальность элементов в дереве отслеживается только по Key, то мы
 * определяем собственный компаратор MapValueComparator, который меняет
 * стандартные правила сравнения значений для std::pair.
 *
 * @version 1.0
 * @date 2022-11-22
 *
 * @copyright hubertfu (c) 2022
 */
#ifndef S21_CONTAINERS_S21_CONTAINERS_S21_MAP_H_
#define S21_CONTAINERS_S21_CONTAINERS_S21_MAP_H_

#include <stdexcept>

#include "s21_tree.h"

namespace s21 {
template <class Key, class Type>
class map {
  public:
    // Тип ключа элемента (Key — параметр шаблона)
    using key_type = Key;
    // Тип значения элемента (Type — параметр шаблона)
    using mapped_type = Type;
    // Тип данных для пары ключ-значение
    using value_type = std::pair<const key_type, mapped_type>;
    // Тип ссылки на элемент
    using reference = value_type &;
    // Тип константной ссылки на элемент
    using const_reference = const value_type &;

    // Компаратор. Для словаря у нас элементы дерева будут считаться равными,
    // если у них равны ключи, значение пары ключ-значение при этом ни на что не
    // влияет.
    struct MapValueComparator {
        bool operator()(const_reference value1,
                        const_reference value2) const noexcept {
            return value1.first < value2.first;
        }
    };

    // Внутренний класс для дерева
    using tree_type = RedBlackTree<value_type, MapValueComparator>;
    // Внутренний класс для итератора
    using iterator = typename tree_type::iterator;
    // Внутренний класс для константного итератора
    using const_iterator = typename tree_type::const_iterator;
    // Тип для размера контейнера
    using size_type = std::size_t;

    /**
     * @brief Конструктор по умолчанию, создает пустой словарь
     */
    map() : tree_(new tree_type{}) {
    }

    /**
     * @brief Конструктор списка инициализаторов, создает словарь,
     * инициализированный с помощью std::initializer_list.
     *
     * @param items Список создаваемых элементов
     */
    map(std::initializer_list<value_type> const &items) : map() {
        for (auto item : items) {
            insert(item);
        }
    }

    /**
     * @brief Конструктор копирования (Copy Constructor). Создает словарь путем
     * копирования данных из объекта other.
     *
     * @param other копируемый объект
     */
    map(const map &other) : tree_(new tree_type(*other.tree_)) {
    }

    /**
     * @brief Конструктор переноса (Move Constructor). Создает словарь путем
     * передачи владения ресурсами от объекта other.
     *
     * @param other переносимый объект
     */
    map(map &&other) noexcept : tree_(new tree_type(std::move(*other.tree_))) {
    }

    /**
     * @brief Оператор присваивания копированием.
     *
     * @param other Копируемый словарь
     * @return list& Созданная копия
     */
    map &operator=(const map &other) {
        *tree_ = *other.tree_;
        return *this;
    }

    /**
     * @brief Оператор присваивания переносом
     *
     * @param other Перемещаемый словарь
     * @return list& Результат перемещения
     */
    map &operator=(map &&other) noexcept {
        *tree_ = std::move(*other.tree_);
        return *this;
    }

    /**
     * @brief Деструктор объекта (Destructor)
     */
    ~map() {
        delete tree_;
        // Для избежания сбоев при повторном освобождении указателей и повторном
        // использовании указателей
        tree_ = nullptr;
    }

    /**
     * @brief Доступ к указанному элементу с проверкой границ. Возвращает ссылку
     * на сопоставленное значение элемента с ключом, эквивалентным ключу. Если
     * такого элемента не существует, создается исключение типа
     * std::out_of_range.
     *
     * @param key
     * @return mapped_type&
     */
    mapped_type &at(const key_type &key) {
        value_type search_pair(key, mapped_type{});
        iterator it_search = tree_->Find(search_pair);

        if (it_search == end()) {
            throw std::out_of_range(
                "s21::map::at: No element exists with key equivalent to key");
        } else {
            return (*it_search).second;
        }
    }

    /**
     * @brief Версия at() для const-объектов
     *
     * @param key
     * @return const mapped_type&
     */
    const mapped_type &at(const key_type &key) const {
        return const_cast<map<Key, Type> *>(this)->at(key);
    }

    /**
     * @brief Возвращает ссылку на значение, сопоставленное с ключом key. Если
     * такого элемента нет, то выполняется вставка нового элемента
     * value_type(key, mapped_type{}).
     *
     * @details If an exception is thrown by any operation, the insertion has no
     * effect
     *
     * @param key
     * @return mapped_type& Ссылка на значение нового элемента, если не
     * существует элемента с ключевым ключом. В противном случае ссылка на
     * сопоставленное значение существующего элемента, ключ которого
     * эквивалентен ключу.
     */
    mapped_type &operator[](const key_type &key) {
        value_type search_pair(key, mapped_type{});
        iterator it_search = tree_->Find(search_pair);

        if (it_search == end()) {
            std::pair<iterator, bool> result = tree_->InsertUnique(search_pair);
            return (*result.first).second;
        } else {
            return (*it_search).second;
        }
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
     * @brief Вставляет элемент со значением value в контейнер, если контейнер
     * еще не содержит элемент с эквивалентным ключом.
     *
     * @param value Значение элемента для вставки
     * @return std::pair<iterator, bool> - Пара, состоящая из итератора для
     * вставленного элемента (или для элемента, который предотвратил вставку) и
     * логического значения, установленного в true, если вставка произошла
     * (false, если вставка не произошла
     */
    std::pair<iterator, bool> insert(const value_type &value) {
        return tree_->InsertUnique(value);
    }

    /**
     * @brief Вставляет элемент c ключом key и со значением obj в контейнер,
     * если контейнер еще не содержит элемент с эквивалентным ключом.
     *
     * @param key Значение ключа для вставки
     * @param obj Значение элемента для вставки
     * @return std::pair<iterator, bool> - Пара, состоящая из итератора для
     * вставленного элемента (или для элемента, который предотвратил вставку) и
     * логического значения, установленного в true, если вставка произошла
     * (false, если вставка не произошла
     */
    std::pair<iterator, bool> insert(const key_type &key,
                                     const mapped_type &obj) {
        return tree_->InsertUnique(value_type{key, obj});
    }

    /**
     * @brief Если ключ, эквивалентный key, уже существует в контейнере,
     * присваивает obj элементу, соответствующему ключу key. Если ключ не
     * существует, вставляет новое значение value_type(key, obj)
     *
     * @todo Работает медленнее оригинала с -O3 для 200000 элементов:
     * std: 31.847 ms
     * s21: 48.19 ms
     * Вероятно, необходимо избавится от лишнего прохода по дереву (Find -
     * первый проход, InsertUnique - второй)
     * @param key
     * @param obj
     * @return std::pair<iterator, bool>
     */
    std::pair<iterator, bool> insert_or_assign(const key_type &key,
                                               const mapped_type &obj) {
        iterator result = tree_->Find(value_type{key, obj});

        if (result == end()) {
            return tree_->InsertUnique(value_type{key, obj});
        }

        (*result).second = obj;

        return {result, false};
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
    void swap(map &other) noexcept {
        tree_->Swap(*other.tree_);
    }

    /**
     * @brief Пытается извлечь элементы из other и вставить их в this. Если в
     * *this есть элемент с ключом, эквивалентным ключу элемента из other,
     * то этот элемент не извлекается из other.
     * @details Детали реализации описаны в методе MergeUnique() реализации
     * дерева.
     *
     * @param other
     */
    void merge(map &other) noexcept {
        tree_->MergeUnique(*other.tree_);
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
        value_type search_pair(key, mapped_type{});
        iterator it_search = tree_->Find(search_pair);
        return !(it_search == end());
    }

    /**
     * @brief Размещает новые элементы args в контейнер, если контейнер ещё не
     * содержит элемент с эквивалентным ключом.
     *
     * @details Детали реализации описаны в методе EmplaceUnique() реализации
     * дерева
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
        return tree_->EmplaceUnique(std::forward<Args>(args)...);
    }

  private:
    // Указатель на объект созданного дерева, используемого в контейнере
    tree_type *tree_;
};

}  // namespace s21

#endif  // S21_CONTAINERS_S21_CONTAINERS_S21_MAP_H_
