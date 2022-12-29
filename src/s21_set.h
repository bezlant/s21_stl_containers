/* ************************************************************************** */
/*                                              ############       ####       */
/*                                              ############       ####       */
/*   s21_set.h                                              ####       ####   */
/*                                                          ####       ####   */
/*   By: hubertfu@student.21-school.ru              ########           ####   */
/*                                                  ########           ####   */
/*                                              ####                   ####   */
/*   Created: 2022-10-30                        ####                   ####   */
/*   Updated: 2022-11-22                            ############       ####   */
/*                                                  ############       ####   */
/* ************************************************************************** */

/**
 * @file s21_set.h
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @brief s21::set (множество) - это ассоциативный контейнер, содержащий
 * отсортированный набор уникальных объектов типа Key. Сортировка осуществляется
 * с помощью функции сравнения ключей. Операции поиска, удаления и вставки имеют
 * логарифмическую сложность. Набор реализован в виде красно-черного дерева.
 *
 * @version 1.0
 * @date 2022-11-22
 *
 * @copyright hubertfu (c) 2022
 */

#ifndef S21_CONTAINERS_S21_CONTAINERS_S21_SET_H_
#define S21_CONTAINERS_S21_CONTAINERS_S21_SET_H_

#include <vector>

#include "s21_tree.h"

namespace s21 {
template <class Key>
class set {
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
     * @brief Конструктор по умолчанию, создает пустое множество
     */
    set() : tree_(new tree_type{}) {
    }

    /**
     * @brief Конструктор списка инициализаторов, создает множество,
     * инициализированное с помощью std::initializer_list.
     *
     * @param items Список создаваемых элементов
     */
    set(std::initializer_list<value_type> const &items) : set() {
        for (auto item : items) {
            insert(item);
        }
    }

    /**
     * @brief Конструктор копирования (Copy Constructor). Создает множество
     * путем копирования данных из объекта other.
     *
     * @param other копируемый объект
     */
    set(const set &other) : tree_(new tree_type(*other.tree_)) {
    }

    /**
     * @brief Конструктор переноса (Move Constructor). Создает множество путем
     * передачи владения ресурсами от объекта other.
     *
     * @param other переносимый объект
     */
    set(set &&other) noexcept : tree_(new tree_type(std::move(*other.tree_))) {
    }

    /**
     * @brief Оператор присваивания копированием.
     *
     * @param other Копируемое множество
     * @return list& Созданная копия
     */
    set &operator=(const set &other) {
        *tree_ = *other.tree_;
        return *this;
    }

    /**
     * @brief Оператор присваивания переносом
     *
     * @param other Перемещаемое множество
     * @return list& Результат перемещения
     */
    set &operator=(set &&other) noexcept {
        *tree_ = std::move(*other.tree_);
        return *this;
    }

    /**
     * @brief Деструктор объекта (Destructor)
     */
    ~set() {
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
    void swap(set &other) noexcept {
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
    void merge(set &other) noexcept {
        tree_->MergeUnique(*other.tree_);
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

#endif  // S21_CONTAINERS_S21_CONTAINERS_S21_SET_H_
