/* ************************************************************************** */
/*                                              ############       ####       */
/*                                              ############       ####       */
/*   s21_tree.h                                             ####       ####   */
/*                                                          ####       ####   */
/*   By: hubertfu@student.21-school.ru              ########           ####   */
/*                                                  ########           ####   */
/*                                              ####                   ####   */
/*   Created: 2022-10-24                        ####                   ####   */
/*   Updated: 2022-11-22                            ############       ####   */
/*                                                  ############       ####   */
/* ************************************************************************** */

/**
 * @file s21_tree.h
 * @author Hubert Furr (hubertfu@student.21-school.ru)
 * @brief Реализация красно-черного дерева
 * @details
 * Красно-черное дерево - это бинарное дерево со следующими свойствами:
 * 1) Узел может быть либо красным, либо чёрным и имеет двух потомков.
 * 2) Корень — всегда чёрный.
 * 3) Все листья, не содержащие данных — чёрные (ниже такие элементы будут
 * называться NIL-элементы).
 * 4) Оба потомка каждого красного узла — чёрные.
 * 5) Любой простой путь от узла-предка до листового узла-потомка содержит
 * одинаковое число чёрных узлов.
 *
 * В нашей реализации есть еще шестое правило:
 * 6) Голова дерева (служебный узел, на который указывает End()) — всегда
 * красный. Зачем - см. описание оператора RedBlackTreeNode::NextNode().
 *
 * Подробное описание организации обхода дерева и структуры (включая служебный
 * узел) - см. описание класса итератора.
 *
 *
 * @version 2.0
 * @date 2022-11-22
 *
 * @copyright hubertfu (c) 2022
 */

#ifndef S21_CONTAINERS_S21_CONTAINERS_S21_TREE_H_
#define S21_CONTAINERS_S21_CONTAINERS_S21_TREE_H_

#include <functional>
#include <limits>
#include <vector>

namespace s21 {
// Цвета для узлов дерева
enum RedBlackTreeColor {
    kBlack,
    kRed
};

template <typename Key, typename Comparator = std::less<Key>>
class RedBlackTree {
  private:
    struct RedBlackTreeNode;
    struct RedBlackTreeIterator;
    struct RedBlackTreeIteratorConst;
#if defined(S21_CONTAINERS_TREE_TEST_HELPER)
    template <typename U>
    friend class RedBlackTreeTestHelper;
#endif
  public:
    // Тип элемента (Key — параметр шаблона)
    using key_type = Key;
    // Тип указателя на элемент
    using reference = key_type &;
    // Тип константной ссылки на элемент
    using const_reference = const key_type &;
    // Внутренний класс для итератора
    using iterator = RedBlackTreeIterator;
    // Внутренний класс для константного итератора
    using const_iterator = RedBlackTreeIteratorConst;
    // Тип для размера контейнера
    using size_type = std::size_t;

    // Внутренний класс для дерева
    using tree_type = RedBlackTree;
    // Внутренний класс узла дерева
    using tree_node = RedBlackTreeNode;
    // Внутренний тип для цвета дерева
    using tree_color = RedBlackTreeColor;

    /**
     * @brief Конструктор по умолчанию, создает пустое дерево
     */
    RedBlackTree() : head_(new tree_node), size_(0U) {
    }

    /**
     * @brief Конструктор копирования (Copy Constructor). Создает дерево путем
     * копирования данных из объекта other.
     *
     * @param other копируемый объект
     */
    RedBlackTree(const tree_type &other) : RedBlackTree() {
        if (other.Size() > 0) {
            CopyTreeFromOther(other);
        }
    }

    /**
     * @brief Конструктор переноса (Move Constructor). Создает дерево путем
     * передачи владения ресурсами от объекта other. Фактически просто
     * обмениваемся ресурсами с other.
     *
     * @param other переносимый объект
     */
    RedBlackTree(tree_type &&other) noexcept : RedBlackTree() {
        Swap(other);
    }

    /**
     * @brief Оператор присваивания копированием.
     *
     * @param other Копируемый список
     * @return list& Созданная копия
     */
    tree_type &operator=(const tree_type &other) {
        if (this != &other) {
            if (other.Size() > 0) {
                CopyTreeFromOther(other);
            } else {
                Clear();
            }
        }

        return *this;
    }

    /**
     * @brief Оператор присваивания переносом
     *
     * @param other Перемещаемый список
     * @return list& Результат перемещения
     */
    tree_type &operator=(tree_type &&other) noexcept {
        Clear();
        Swap(other);
        return *this;
    }

    /**
     * @brief Деструктор объекта (Destructor)
     */
    ~RedBlackTree() {
        Clear();
        delete head_;
        // Для избежания сбоев при повторном освобождении указателей и повторном
        // использовании указателей
        head_ = nullptr;
    }

    /**
     * @brief Удаляет содержимое контейнера (все элементы). Контейнер при этом
     * остается консистентным.
     */
    void Clear() noexcept {
        Destroy(Root());
        InitializeHead();
        // Размер пустого дерева всегда 0
        size_ = 0;
    }

    /**
     * @brief Возвращает количество элементов в контейнере
     *
     * @return size_type
     */
    size_type Size() const noexcept {
        return size_;
    }

    /**
     * @brief Проверяет, является ли контейнер пустым
     *
     * @return true контейнер пустой
     * @return false контейнер непустой
     */
    bool Empty() const noexcept {
        return size_ == 0;
    }

    /**
     * @brief Возвращает максимальное количество элементов, которое может
     * содержать дерево из-за ограничений реализации системы или библиотеки.
     *
     * @warning В реальности значение max_size() никогда не будет достижимо.
     *
     * @details Это число не зависит от состояния ОС или доступной памяти, а
     * определяется только реализацией контейнера. Во время выполнения размер
     * контейнера может быть ограничен значением, меньшим max_size(), чем объем
     * доступной оперативной памяти.
     *
     * Для расчета используются следующие вводные:
     * 1) Размер size_t должен совпадать с размером указателя для любой
     * платформы. Указатель должен быть в состоянии адресовать любой байт в
     * памяти, а size_t хранить размер любого (в т.ч. занимающего всю память)
     * объекта. Таким образом максимальное значение size_t - это максимальное
     * количество байт памяти. Это значение мы получаем при помощи
     * std::numeric_limits<size_t>::max();
     *
     * 2) GCC ограничивает объекты размером в половину адресного пространства.
     * Поэтому полученное в п.1 число делим на 2.
     *
     * Почему так происходит - см. описание s21::list::max_size()
     *
     * 3) В дереве хранится указатель на голову (служебный узел) -
     * sizeof(head_), компаратор - sizeof(cmp_), количество созданных элементов
     * - sizeof(size_), всё вместе - sizeof(tree_type). Кроме этого выделяется
     * память на один служебный узел, который есть даже у пустого дерева -
     * sizeof(tree_node). Всё это вычитаем из памяти, полученной в п.2. Таким
     * образом получаем максимальное количество памяти, доступной для создания
     * узлов дерева.
     *
     * 4) Чтобы определить максимальное количество элементов в контейнере, делим
     * число, полученное в п.3, на размер одного узла, т.е. sizeof(tree_node)
     *
     */
    size_type MaxSize() const noexcept {
        return ((std::numeric_limits<size_type>::max() / 2) -
                sizeof(tree_type) - sizeof(tree_node)) /
               sizeof(tree_node);
    }

    /**
     * @brief Возвращает итератор на начало контейнера.
     * @details Для пустого контейнера возвращаемый итератор будет равен end().
     * Все нюансы реализации итераторов описаны в классе итератора.
     *
     * @return iterator
     */
    iterator Begin() noexcept {
        return iterator(MostLeft());
    }

    /**
     * @brief Версия begin() для const
     *
     * @return const_iterator
     */
    const_iterator Begin() const noexcept {
        return const_iterator(MostLeft());
    }

    /**
     * @brief Возвращает итератор на конец контейнера (элемент после последнего
     * элемента контейнера).
     * @details Элемент является служебной "заглушкой" и его разыменование - UB
     *
     * @return iterator
     */
    iterator End() noexcept {
        return iterator(head_);
    }

    /**
     * @brief Версия end() для const
     *
     * @return const_iterator
     */
    const_iterator End() const noexcept {
        return const_iterator(head_);
    }

    /**
     * @brief Извлекает все элементы из other и вставляет их в this.
     * @details Никакие элементы не копируются и не перемещаются,
     * переназначаются только внутренние указатели узлов контейнера. Все
     * указатели и ссылки на переданные элементы остаются действительными, но
     * теперь ссылаются на *this, а не на other.
     *
     * В данной функции мы переносим все элементы, даже если такие уже есть в
     * текущем дереве. Поэтому мы не используем функцию ExtractNode(), т.к. она
     * вызывает перебалансировку дерева other после изъятия узла, что лишняя
     * ненужная операция, т.к. все равно будут перенесены все без исключения
     * элементы other. Поэтому мы проходимся по порядку по всем элементам other,
     * изымаем их и вставляем в текущее дерево.
     *
     * Т.к. мы не создаем копии узлов, то это экономит много времени.
     *
     * @param other
     */
    void Merge(tree_type &other) {
        if (this != &other) {
            iterator other_begin = other.Begin();

            // Пока элементы есть в other, извлекаем их
            while (other.size_ > 0) {
                tree_node *moving_node = other_begin.node_;
                ++other_begin;

                // Отцепляем узел от других узлов в other

                if (moving_node->left_ != nullptr) {
                    // Т.к. у нас обход слева направо, то left_ всегда будет
                    // nullptr Однако оставим эту проверку на случай
                    // изменения/доработки алгоритма
                    moving_node->left_->parent_ = moving_node->parent_;
                }

                if (moving_node->right_ != nullptr) {
                    moving_node->right_->parent_ = moving_node->parent_;
                }

                if (moving_node->parent_->left_ == moving_node) {
                    moving_node->parent_->left_ = nullptr;
                }

                if (moving_node->parent_->right_ == moving_node) {
                    moving_node->parent_->right_ = nullptr;
                }

                // Приводим узел к виду по умолчанию
                moving_node->ToDefault();

                --other.size_;

                Insert(Root(), moving_node, false);
            }

            // Приводим head дерева other в корректное состояние для пустого
            // контейнера, чтобы other остался консистентным.
            other.InitializeHead();
        }
    }

    /**
     * @brief Пытается извлечь элементы из other и вставить их в this. Если в
     * *this есть элемент с ключом, эквивалентным ключу элемента из other,
     * то этот элемент не извлекается из other.
     *
     * @details Никакие элементы не копируются и не перемещаются,
     * переназначаются только внутренние указатели узлов контейнера. Все
     * указатели и ссылки на переданные элементы остаются действительными, но
     * теперь ссылаются на *this, а не на other.
     *
     * Т.к. other может остаться непустым после операции, то для извлечения
     * узлов из other мы используем ExtractNode(), т.к. она вызывает
     * перебалансировку, а мы должны сохранить other корректным красно-чёрным
     * деревом.
     *
     * @param other
     */
    void MergeUnique(tree_type &other) {
        if (this != &other) {
            iterator other_begin = other.Begin();
            iterator other_end = other.End();

            while (other_begin != other_end) {
                iterator result_it = Find(other_begin.node_->key_);
                if (result_it == End()) {
                    iterator tmp = other_begin;
                    ++other_begin;
                    tree_node *moving_node = other.ExtractNode(tmp);
                    Insert(Root(), moving_node, false);
                } else {
                    ++other_begin;
                }
            }
        }
    }

    /**
     * @brief Вставляет элемент со значением key в контейнер. Если в контейнере
     * есть элементы с эквивалентным ключом, вставка выполняется по верхней
     * границе этого диапазона.
     *
     * @param key Значение элемента для вставки
     * @return iterator Итератор, указывающий на вставленный элемент
     */
    iterator Insert(const key_type &key) {
        tree_node *new_node = new tree_node{key};
        return Insert(Root(), new_node, false).first;
    }

    /**
     * @brief Вставляет элемент со значением key в контейнер, если контейнер еще
     * не содержит элемент с эквивалентным ключом.
     *
     * @param key Значение элемента для вставки
     * @return std::pair<iterator, bool> - Пара, состоящая из итератора для
     * вставленного элемента (или для элемента, который предотвратил вставку) и
     * логического значения, установленного в true, если вставка произошла
     * (false, если вставка не произошла
     */
    std::pair<iterator, bool> InsertUnique(const key_type &key) {
        tree_node *new_node = new tree_node{key};
        std::pair<iterator, bool> result = Insert(Root(), new_node, true);
        if (result.second == false) {
            // Если вставка не произошла, то удаляем созданный узел
            delete new_node;
        }

        return result;
    }

    /**
     * @brief Размещает новые элементы args в контейнер. Если в контейнере
     * есть элементы с эквивалентным ключом, вставка выполняется по верхней
     * границе этого диапазона.
     *
     * @tparam Args Пакет параметров шаблона (Parameter pack)
     * @param args Уже созданные элементы, которые необходимо вставить в
     * соответствующий контейнер.
     * @details Модифицированная версия метода emplace, которая отличается от
     * реализации в std, т.к. получает в качестве аргументов args уже созданные
     * объекты для размещения в контейнере (а не параметры для конструирования
     * объектов)
     *
     * Однако при реализации мы должны сохранить основную идею Emplace:
     * Основное отличие от insert - избежать ненужных копирований объекта,
     * единожды созданный временный объект будет передаваться по функциям без
     * копирования и встроится в дерево.
     *
     * @return std::vector<std::pair<iterator, bool>> Т.к. функция может
     * вставить несколько элементов, то возвращается вектор, содержащий пары
     * результата вставки для каждого вставляемого элемента. Формат пары
     * идентичен методу InsertUnique()
     */
    template <typename... Args>
    std::vector<std::pair<iterator, bool>> Emplace(Args &&...args) {
        std::vector<std::pair<iterator, bool>> result;
        // Т.к. args может быть большим, но это число нам сразу известно, то
        // выделяем нужное количество памяти на вектор, чтобы избежать ненужных
        // повторных выделений памяти в процессе
        result.reserve(sizeof...(args));

        // Обязательно используем std::forward, чтобы избежать лишних
        // копирований в item
        for (auto item : {std::forward<Args>(args)...}) {
            // И используем std::move, чтобы опять избежать лишних копирований
            tree_node *new_node = new tree_node(std::move(item));
            std::pair<iterator, bool> result_insert =
                Insert(Root(), new_node, false);
            result.push_back(result_insert);
        }
        return result;
    }

    /**
     * @brief Размещает новые элементы args в контейнер, если контейнер ещё не
     * содержит элемент с эквивалентным ключом.
     *
     * @details В остальном работает идентично Emplace().
     *
     * @tparam Args Пакет параметров шаблона (Parameter pack)
     * @param args Уже созданные элементы, которые необходимо вставить в
     * соответствующий контейнер.
     * @return std::vector<std::pair<iterator, bool>> Т.к. функция может
     * вставить несколько элементов, то возвращается вектор, содержащий пары
     * результата вставки для каждого вставляемого элемента. Формат пары
     * идентичен методу InsertUnique()
     */
    template <typename... Args>
    std::vector<std::pair<iterator, bool>> EmplaceUnique(Args &&...args) {
        std::vector<std::pair<iterator, bool>> result;
        result.reserve(sizeof...(args));

        for (auto item : {std::forward<Args>(args)...}) {
            tree_node *new_node = new tree_node(std::move(item));
            std::pair<iterator, bool> result_insert =
                Insert(Root(), new_node, true);
            if (result_insert.second == false) {
                delete new_node;
            }
            result.push_back(result_insert);
        }
        return result;
    }

    /**
     * @brief Находит элемент с ключом, эквивалентным key. Стандарт не
     * регулирует, какой именно элемент будет найден, если их несколько, но в
     * gcc находится элемент из lower_bound(), поэтому делаем аналогично
     *
     * @param key Искомый ключ
     * @return iterator Итератор найденного элемента. Если такой элемент не
     * найден, возвращается end().
     */
    iterator Find(const_reference key) {
        iterator result = LowerBound(key);

        if (result == End() || cmp_(key, *result)) {
            // Если LowerBound() ничего не нашел или нашел элемент > key
            return End();
        }

        // В остальных случаях возвращаем результат LowerBound()
        return result;
    }

    /**
     * @brief Возвращает итератор, указывающий на первый элемент, который не
     * меньше (т.е. больше или равен) key.
     *
     * @details Алгоритм расписан по ходу функции. Пример поиска тут:
     * Дерево (с повторами):
     *  /-6----\
     * /4\  /--8\
     * 2 6 /6\  10
     *     6 6\
     *        6
     *
     * Ищем элемент не меньше 5:
     * 1я строка: 6 не меньше 5 == true, запоминаем 6 и идем искать влево от 6
     * 2я строка: 4 не меньше 5 == false, идем искать вправо от 4
     * 3я строка: 6 не меньше 5 == true, запоминаем 6 и идем искать влево от 6
     * 4я строка: nullptr, поиск завершен. Последний запомненный результат - 6
     * из 3й строки
     *
     * Ищем элемент не меньше 6:
     * Идентично поискам 5
     *
     * Ищем элемент не меньше 7:
     * 1я строка: 6 не меньше 7 == false, идем искать вправо
     * 2я строка: 8 не меньше 7 == true, запоминаем 8 и идем искать влево от 8
     * 3я строка: 6 не меньше 7 == false, идем искать вправо
     * 4я строка: 6 не меньше 7 == false, идем искать вправо
     * 5я строка: 6 не меньше 7 == false, идем искать вправо
     * 6я строка: nullptr, поиск завершен. Последний запомненный результат - 8
     *
     * Ищем элемент не меньше 8:
     * Идентично поискам 7
     *
     * Ищем элемент не меньше 888:
     * 1я строка: 6 не меньше 888 == false, идем искать вправо
     * 2я строка: 8 не меньше 888 == false, идем искать вправо
     * 3я строка: 10 не меньше 888 == false, идем искать вправо
     * 4я строка: nullptr, поиск завершен. Т.к. ничего не запомнили, то
     * возвращаем End()
     *
     * @param key ключевое значение, с которым сравниваются элементы
     * @return iterator Итератор, указывающий на первый элемент, который не
     * меньше key. Если такой элемент не найден, возвращается итератор End().
     */
    iterator LowerBound(const_reference key) {
        // Начинаем от корня
        tree_node *start = Root();
        // Результат по умолчанию End(), он и будет использован, если в ходе
        // поисков мы ничего не найдем
        tree_node *result = End().node_;

        // Ищем в цикле нужный элемент, пока не упрёмся в nullptr
        // для пустого дерева даже не зайдем в цикл и вернем End()
        while (start != nullptr) {
            if (!cmp_(start->key_, key)) {
                // Если найден элемент не меньше key, то запоминаем его как
                // предварительный результат поисков (т.е. как минимум один
                // элемент уже найден), далее в цикле будем обновлять этот
                // указатель, если ниже по дереву найдем еще один элемент не
                // меньше key
                result = start;
                // Сдвигаем указатель на левый узел найденного узла, т.к. слева
                // располагаются элементы меньше текущего и они могут быть ближе
                // к искомому значению
                start = start->left_;
            } else {
                // Если текущий узел меньше искомого, то идем вправо, т.к. там
                // находятся элементы больше текущего
                start = start->right_;
            }
        }

        return iterator(result);
    }

    /**
     * @brief Возвращает итератор, указывающий на первый элемент, который больше
     * key.
     *
     * @details Алгоритм в целом аналогичен LowerBound, но типа наоборот (см.
     * отличия в комментариях по ходу функции).
     *
     * @param key ключевое значение, с которым сравниваются элементы
     * @return iterator Итератор, указывающий на первый элемент, который больше
     * key. Если такой элемент не найден, возвращается итератор End().
     */
    iterator UpperBound(const_reference key) {
        tree_node *start = Root();
        tree_node *result = End().node_;

        while (start != nullptr) {
            if (cmp_(key, start->key_)) {
                // Если искомое значение меньше значения узла, то запоминаем
                // текущий узел, т.к. он больше искомого
                result = start;
                // Продолжаем поиски в левой ветви, т.к. там могут быть значения
                // меньше текущего узла, а нам надо найти самый маленький (т.е.
                // ближайший к key) узел
                start = start->left_;
            } else
                // В противном случае ищем узлы в правой ветви
                start = start->right_;
        }

        return iterator(result);
    }

    /**
     * @brief Удаляет элемент на позиции pos. Ссылки и итераторы на стертые
     * элементы становятся недействительными. Другие ссылки и итераторы не
     * затрагиваются.
     *
     * @param pos
     */
    void Erase(iterator pos) noexcept {
        tree_node *result = ExtractNode(pos);
        delete result;
    }

    /**
     * @brief Обменяет содержимое контейнера на содержимое other
     * @details Не вызывает никаких операций перемещения, копирования или замены
     * отдельных элементов. Все итераторы и ссылки остаются действительными.
     * Итератор End() становится недействительным.
     *
     * Проверка на самосвап бессмысленна, т.к. дерево это переживает, а лишняя
     * проверка будет всегда вызываться, а реально будет редко нужна.
     *
     * @param other
     */
    void Swap(tree_type &other) noexcept {
        std::swap(head_, other.head_);
        std::swap(size_, other.size_);
        std::swap(cmp_, other.cmp_);
    }

    /**
     * @brief Метод для тестирования красно-черного дерева на корректность.
     * @details Проверяет все правила, которые должны соблюдаться для дерева
     * (см. описание в начале файла). Пояснения написаны по ходу метода.
     *
     * @return true Дерево корректно
     * @return false Дерево некорректно
     */
    bool CheckTree() const noexcept {
        // head дерева должен быть красный.
        if (head_->color_ == kBlack) {
            return false;
        }

        // Пустое дерево корректно всегда
        if (Root() == nullptr) {
            return true;
        }

        // Корень дерева должен быть чёрный.
        if (Root()->color_ == kRed) {
            return false;
        }

        // Оба потомка каждого красного узла — чёрные.
        if (checkRedNodes(Root()) == false) {
            return false;
        }

        // Любой простой путь от узла-предка до листового узла-потомка содержит
        // одинаковое число чёрных узлов.
        if (ComputeBlackHeight(Root()) == -1) {
            return false;
        }

        // Если всё ок, то возвращаем true
        return true;
    }

  private:
    /**
     * @brief Приватный метод для копирования дерева other в this.
     *
     * @todo В части кейсов копирование осуществляется медленнее, чем в std.
     * Связано это с тем, что наша версия Clear() медленнее оригинала, само
     * копирование сопоставимо по скорости.
     * @param other Копируемое дерево
     */
    void CopyTreeFromOther(const tree_type &other) {
        tree_node *other_copy_root = CopyTree(other.Root(), nullptr);
        // Важно, что мы сначала создаем полную копию, а только потом вызываем
        // очистку текущего дерева. Это необходимо для того, чтобы текущее
        // дерево не было уничтожено, если при копировании вылетит исключение
        // (см. тесты "CopyLeaks").
        Clear();
        Root() = other_copy_root;
        Root()->parent_ = head_;
        MostLeft() = SearchMinimum(Root());
        MostRight() = SearchMaximum(Root());
        size_ = other.size_;
        cmp_ = other.cmp_;
    }

    /**
     * @brief Приватный метод для рекурсивного создания копий узлов и связей
     * между ними
     *
     * @param node копируемый узел.
     * @param parent копия родителя копируемого узла.
     * @return tree_node* указатель на созданную копию узла.
     */
    [[nodiscard]] tree_node *CopyTree(const tree_node *node,
                                      tree_node *parent) {
        // Если вылетит исключение при создании самого первого узла, то ничего
        // страшного, ничего создано не будет
        tree_node *copy = new tree_node{node->key_, node->color_};
        // А вот все рекурсивные вызовы оборачиваем в try/catch, чтобы в случае
        // возникновения исключения удалить все уже скопированные узлы (иначе
        // будет утечка)
        try {
            if (node->left_) {
                copy->left_ = CopyTree(node->left_, copy);
            }

            if (node->right_) {
                copy->right_ = CopyTree(node->right_, copy);
            }
        } catch (...) {
            Destroy(copy);
            throw;
        }

        copy->parent_ = parent;
        return copy;
    }

    /**
     * @brief Рекурсивно удаляет все узлы дерева и освобождает память, кроме
     * служебного узла head.
     *
     * @todo map - 199054 элементов: std: 38.626 ms; s21: 65.842 ms;
     * Отказаться от двойной рекурсии? Или это из-за неудачного механизма
     * компаратора? set/multiset показывают лучшие результаты, чем map
     * @param node
     */
    void Destroy(tree_node *node) noexcept {
        if (node == nullptr)
            return;
        Destroy(node->left_);
        Destroy(node->right_);
        delete node;
    }

    /**
     * @brief Приватный метод, который выставляет значения служебного узла head
     * в значения, необходимые для пустого дерева
     */
    void InitializeHead() noexcept {
        // У пустого дерева корня нет
        Root() = nullptr;
        // Т.к. элементов нет, то самый маленький (самый левый) элемент будет
        // указывать на голову
        MostLeft() = head_;
        // Т.к. элементов нет, то самый большой (самый правый) элемент будет
        // указывать на голову
        MostRight() = head_;
    }

    /**
     * @brief Возвращает ссылку на корень дерева
     *
     * @return tree_node*&
     */
    tree_node *&Root() {
        return head_->parent_;
    }

    /**
     * @brief Возвращает ссылку на корень дерева для const-объектов
     *
     * @return const tree_node*
     */
    const tree_node *Root() const {
        return head_->parent_;
    }

    /**
     * @brief Возвращает ссылку на самый маленький (самый левый) элемент дерева
     *
     * @return tree_node*&
     */
    tree_node *&MostLeft() {
        return head_->left_;
    }

    /**
     * @brief Возвращает ссылку на самый маленький (самый левый) элемент дерева
     * для const-объектов
     *
     * @return tree_node*&
     */
    const tree_node *MostLeft() const {
        return head_->left_;
    }

    /**
     * @brief Возвращает ссылку на самый большой (самый правый) элемент дерева
     * @details Версию для const-объектов не реализуем, т.к. в наших функциях
     * эта версия просто негде вызывать
     *
     * @return tree_node*&
     */
    tree_node *&MostRight() {
        return head_->right_;
    }

    /**
     * @brief Встраивает узел new_node в дерево ниже узла root.
     * @details Алгоритм стандартен для любого бинарного дерева: если
     * вставляемый узел меньше текущего, то ищем место для вставки в левой ветви
     * дерева, если больше (или равен), то ищем место для вставки в правой ветви
     * дерева, пока не дойдем до пустого узла (nullptr) - в это место и
     * вставляем.
     *
     * Если вставка повторяющихся элементов запрещена (см. параметр
     * unique_only), то поиск останавливается, если нашли элемент с
     * эквивалентным ключом.
     *
     * @param root Узел, от которого мы начинаем искать место, куда встроить
     * новый узел
     * @param new_node Встраиваемый узел
     * @param unique_only Режим вставки:
     * true - вставка только уникальных узлов, вставка осуществляется только,
     * если контейнер ещё не содержит элемент с эквивалентным ключом. false -
     * вставка любого узла, в т.ч., если контейнер уже содержит элемент с
     * эквивалентным ключом.
     * @todo Insert можно ускорить, если сделать разные версии для обычной
     * вставки и unique, так сейсчас при обычной вставке мы делаем лишние
     * проверки, которые можно и не делать
     * @todo подозрительно быстро (особенно с оптимизацией) делается вставка
     * 200000 одинаковых элементов в set
     * @return std::pair<iterator, bool> - Пара, состоящая из итератора для
     * вставленного элемента (или для элемента, который предотвратил вставку) и
     * логического значения, установленного в true, если вставка произошла
     * (false, если вставка не произошла
     */
    std::pair<iterator, bool> Insert(tree_node *root, tree_node *new_node,
                                     bool unique_only) {
        tree_node *node = root;
        tree_node *parent = nullptr;

        // Ищем место для вставки, пока не дойдем до пустого узла
        while (node != nullptr) {
            parent = node;
            if (cmp_(new_node->key_, node->key_)) {
                // Если new_node < node
                node = node->left_;
            } else {
                // Иначе (т.е. node >= new_node)
                if (unique_only == false) {
                    // Если вставка неуникальных элементов разрешена, то всегда
                    // продолжаем искать дальше в правой ветви (т.к. нам не
                    // важно, равно ли значение текущего узла вставляемому)
                    node = node->right_;
                } else {
                    // Если вставка неуникальных элементов не разрешена, то
                    // выясняем node > new_node или node == new_node
                    if (cmp_(node->key_, new_node->key_)) {
                        // Если node > new_node, то продолжаем поиски в правой
                        // ветви
                        node = node->right_;
                    } else {
                        // Если node == new_node то возвращаем результат о
                        // невозможности вставки элемента
                        return {iterator(node), false};
                    }
                }
            }
        }

        // После окончания цикла parent буден указывать на узел, потомком
        // которого станет new_node. При этом parent может быть равен nullptr,
        // если в дереве не окажется узлов (пустое дерево), если мы даже не
        // зашли в цикл выше

        if (parent != nullptr) {
            // Если дерево не пустое
            // То родителем нового узла указываем найденный parent
            new_node->parent_ = parent;
            if (cmp_(new_node->key_, parent->key_)) {
                parent->left_ = new_node;
            } else {
                parent->right_ = new_node;
            }
        } else {
            // Если дерево пустое, то new_node становится корнем дерева
            new_node->color_ = kBlack;
            new_node->parent_ = head_;
            Root() = new_node;
        }

        ++size_;

        // Обновляем указатель на самый маленький элемент дерева, если
        // необходимо
        if (MostLeft() == head_ || MostLeft()->left_ != nullptr) {
            MostLeft() = new_node;
        }

        // Обновляем указатель на самый большой элемент дерева, если необходимо
        if (MostRight() == head_ || MostRight()->right_ != nullptr) {
            MostRight() = new_node;
        }

        // Вызываем балансировку после вставки нового узла
        BalancingInsert(new_node);

        return {iterator(new_node), true};
    }

    /**
     * @brief Балансировка дерева, после вставки нового элемента.
     * @details Основной алгоритм расписан по ходу функции, используемая
     * терминология:
     * node — добавленный элемент (сын), который нарушает 3 пункт правил (Оба
     * потомка каждого красного узла — чёрные). Хотя на самом деле может и не
     * нарушает, мы всегда вызываем балансировку. Но если условия не нарушены,
     * то мы не зайдем в цикл while
     *
     * parent — папа элемента node
     *
     * gparent — дедушка элемента node, папа элемента parent
     *
     * uncle — дядя элемента node, брат элемента parent, второй сын элемента
     * gparent
     *
     * При перебалансировке возможны 6 различных случаев:
     * 1) 3 случая, когда дядя справа у деда
     * 2) 3 случая, когда дядя слева у деда
     *
     * Походу функции подробно описаны первые 3 случая. Вторые 3 случая
     * зеркально отражают первые 3 случая (это очень наглядно будет видно по
     * коду).
     *
     * P.S. Можно посмотреть картинки, примеры и почитать дополнительные
     * описания тут: https://habr.com/ru/company/otus/blog/472040/
     *
     * @param node добавленный элемент
     */
    void BalancingInsert(tree_node *node) {
        // Папа
        tree_node *parent = node->parent_;

        while (node != Root() && parent->color_ == kRed) {
            // Дед
            tree_node *gparent = parent->parent_;

            if (gparent->left_ == parent) {
                // Обрабатываем ситуацию, когда дядя справа у деда
                tree_node *uncle = gparent->right_;

                if (uncle != nullptr && uncle->color_ == kRed) {
                    // Случай первый — красный дядя

                    // Если и отец, и дядя красного цвета, то мы можем
                    // «спустить» чёрный цвет с уровня деда на уровень отца и
                    // перекрасить узлы. В этом случае «чёрная высота» останется
                    // прежней, однако возможно нарушение 3 правила для элемента
                    // gparent, поэтому необходимо рекурсивно вызвать дальнейшую
                    // балансировку для этого узла (следующая итерация цикла
                    // while).
                    parent->color_ = kBlack;
                    uncle->color_ = kBlack;
                    gparent->color_ = kRed;
                    // Меняем указатели для следующей итерации цикла while
                    node = gparent;
                    parent = node->parent_;
                } else {
                    // Случай второй — чёрный дядя — папа и дед в разных
                    // сторонах.

                    // Эту структуру необходимо привести к третьему случаю,
                    // когда папа и дед идут в одну сторону. Для этого нужно
                    // выполнить малый поворот от сына node к его отцу и далее
                    // будет вызван 3 случай для элемента node.
                    if (parent->right_ == node) {
                        // Выполняем поворот
                        RotateLeft(parent);
                        // Меняем местами указатели на отца и сына, т.к. в
                        // третьем случае сын снизу должен быть, а после
                        // поворота node встала сверху от parent
                        std::swap(parent, node);
                    }
                    // Случай третий — чёрный дядя — папа и дед в одной стороне

                    // В этом случае мы уже можем совершить большой поворот от
                    // отца через деда к чёрному дяде и перекрасить parent в
                    // чёрный, а gparent в красный.
                    RotateRight(gparent);
                    gparent->color_ = kRed;
                    parent->color_ = kBlack;
                    break;
                }
            } else {
                // Обрабатываем ситуацию, когда дядя слева у деда
                tree_node *uncle = gparent->left_;

                if (uncle != nullptr && uncle->color_ == kRed) {
                    // Случай первый — красный дядя
                    // Аналогично ситуации, когда дядя справа у деда
                    parent->color_ = kBlack;
                    uncle->color_ = kBlack;
                    gparent->color_ = kRed;

                    node = gparent;
                    parent = node->parent_;
                } else {
                    // Случай второй — чёрный дядя — папа и дед в разных
                    // сторонах. Аналогично ситуации, когда дядя справа у деда
                    if (parent->left_ == node) {
                        RotateRight(parent);
                        std::swap(parent, node);
                    }
                    // Случай третий — чёрный дядя — папа и дед в одной стороне
                    // Аналогично ситуации, когда дядя справа у деда
                    RotateLeft(gparent);
                    gparent->color_ = kRed;
                    parent->color_ = kBlack;
                    break;
                }
            }
        }

        // Корень всегда должен быть черным после наших поворотов
        Root()->color_ = kBlack;
    }

    /**
     * @brief Вращаем дерево вправо относительно node
     *
     * @param node
     */
    void RotateRight(tree_node *node) noexcept {
        // Выбираем левый узел в качестве опорного
        tree_node *const pivot = node->left_;

        pivot->parent_ = node->parent_;

        if (node == Root()) {
            // Опорный элемент становится корнем дерева, если node было корнем
            Root() = pivot;
        } else if (node->parent_->left_ == node) {
            // Если узел был слева у родителя, то опорный элемент становится
            // слева
            node->parent_->left_ = pivot;
        } else {
            // Если узел была справа у родителя, то опорный элемент становится
            // справа
            node->parent_->right_ = pivot;
        }

        node->left_ = pivot->right_;
        if (pivot->right_ != nullptr) {
            pivot->right_->parent_ = node;
        }

        node->parent_ = pivot;
        pivot->right_ = node;
    }

    /**
     * @brief Вращаем дерево влево относительно node.
     * @details В целом аналогично повороту вправо, только в другую сторону
     *
     * @param node
     */
    void RotateLeft(tree_node *node) noexcept {
        tree_node *const pivot = node->right_;

        pivot->parent_ = node->parent_;

        if (node == Root()) {
            Root() = pivot;
        } else if (node->parent_->left_ == node) {
            node->parent_->left_ = pivot;
        } else {
            node->parent_->right_ = pivot;
        }

        node->right_ = pivot->left_;
        if (pivot->left_ != nullptr) {
            pivot->left_->parent_ = node;
        }

        node->parent_ = pivot;
        pivot->left_ = node;
    }

    /**
     * @brief Изымает узел в позиции pos из дерева, при необходимости
     * осуществляется ребалансировка дерева.
     *
     * @details Чтобы удалить узел из красно-черного дерева, мы следуем обычному
     * процессу удаления BST, который гарантирует, что удаляемый узел является
     * либо конечным узлом (т.е. не содержит дочерних узлов), либо имеет только
     * один дочерний узел. Возможные варианты удаляемых узлов:
     *
     * 1) К2 — красный узел с двумя детьми.
     * Задача удаления узла с двумя дочерними элементами сводится к задаче
     * удаления узла с одним или нулём дочерних элементов. Для этого необходимо
     * найти ближайший элемент, который меньше или больше удаляемого и поменять
     * их местами.
     *
     * ВАЖНО: Наиболее удобно при обмене элементов местами изменять только
     * значения в узлах, а цвет оставлять прежним, чтобы не нарушать структуру
     * дерева и не изменять чёрную высоту. Обычно это быстро, т.к. происходит
     * обмен только одного поля (значения), даже для сложных классов (если класс
     * поддерживает move). И это проще реализовать, т.к. не надо делать
     * фактический обмен узлов с перепривязкой всех указателей на узлы. Однако в
     * этом случае мы фактический удаляем другой узел, хоть и содержащую нужное
     * значение. Соответственно в этом случае мы не можем гарантировать, что
     * указатели/итераторы на другие узлы дерева останутся валидными. Т.к.
     * оригинальная реализация дерева в STL требует от нас сохранять указатели и
     * итераторы валидными (References and iterators to the erased elements are
     * invalidated. Other references and iterators are not affected.), то мы
     * будем наоборот обменивать узлы целиком, оставляя значение на старом
     * месте.
     *
     * После обмена нужно удалить узел из его нового места. Это будет либо
     * самый правый элемент в левой ветке (максимальный слева), либо самый левый
     * в правой (минимальный справа) (см ниже пояснение с *), в любом случае у
     * него не будет одного дочернего узла слева или справа.
     *
     * Таким образом, задача удаления узла с 2 детьми сводится к задаче удаления
     * элемента с 1 или 0 детьми.
     *
     * *) При поиске ближайшего элемента в идеале необходимо просматривать и
     * левое и правое поддеревья, чтобы выбрать ближайшее значение к удаляемому.
     * Но мы будем всегда искать справа (если правое поддерево есть, конечно),
     * т.к. это проще и не оказывает существенного влияния на работу дерева.
     *
     * 2) Ч2 — чёрный узел с двумя детьми.
     * Аналогично предыдущему случаю К2, задача удаления узла с 2 детьми
     * сводится к задаче удаления элемента с 1 или 0 детьми.
     *
     * 3) К1 — красный узел с одним ребёнком.
     * Если у красного узла одного ребёнка нет, значит, вместо него находится
     * чёрный NIL-элемент и чёрная высота красного узла равна 1. Следовательно,
     * с другой стороны чёрная высота также должны быть равна 1. Но так как у
     * красного узла дочерний элемент не может быть красного цвета, то другой
     * его ребёнок должен быть чёрного цвета. Так как чёрная высота должна быть
     * равна 1, то это может быть только чёрный NIL-элемент, так как в случае
     * обычного чёрного элемента высота будет выше.
     *
     * Таким образом, К1 случай не имеет места быть.
     *
     * 4) Ч1 — чёрный узел с одним ребёнком.
     * Если у чёрного элемента нет одного ребёнка, значит, вместо него находится
     * чёрный NIL-элемент с чёрной высотой 1. Следовательно, с другой стороны
     * должен быть красный узел без детей. Для удаления такого элемента обменять
     * значения красного и чёрного узлов и удалить красный узел (аналогично
     * случаю К2 вместо обмена значений мы будем делать обмен узлов), чёрная
     * высота при этом сохранится.
     *
     * Таким образом, К1 сводится к задаче удаления красного узла без детей (К0)
     *
     * 5) К0 — красный узел без детей.
     * Просто удаляем элемент, чёрная высота при этом сохранится.
     *
     * 6) Ч0 — чёрный узел без детей. Просто удаляем узел, но при этом чёрная
     * высота изменится. Соответственно необходимо запустить перебалансировку.
     *
     *
     * P.S. Можно посмотреть картинки, примеры и почитать дополнительные
     * описания тут: https://habr.com/ru/company/otus/blog/521034/
     *
     * @param pos Итератор, указывающий на извлекаемый узел.
     * @return tree_node* Извлеченный узел дерева.
     */
    tree_node *ExtractNode(iterator pos) noexcept {
        if (pos == End()) {
            // Запрещаем удалять служебный узел (head_), чтобы сохранить
            // консистентность нашего класса.
            return nullptr;
        }

        tree_node *deleted_node = pos.node_;

        // Обработка К2 и Ч2
        if (deleted_node->left_ != nullptr && deleted_node->right_ != nullptr) {
            // Находим самый левый узел в правой ветке (минимальный справа)
            tree_node *replace = SearchMinimum(deleted_node->right_);
            // Обмениваем местами удаляемый узел и найденный узел
            SwapNodesForErase(deleted_node, replace);
        }

        // Обработка К1 — не требуется, т.к. такой случай невозможен

        // Обработка Ч1
        if (deleted_node->color_ == kBlack &&
            ((deleted_node->left_ == nullptr &&
              deleted_node->right_ != nullptr) ||
             (deleted_node->left_ != nullptr &&
              deleted_node->right_ == nullptr))) {
            // Находим красный узел без детей (К0) для обмена значений с ним
            tree_node *replace;
            if (deleted_node->left_ != nullptr) {
                replace = deleted_node->left_;
            } else {
                replace = deleted_node->right_;
            }
            // Обмениваем местами удаляемый узел и найденный узел
            SwapNodesForErase(deleted_node, replace);
        }

        // Обработка К0
        // Дополнительных действий не требуется узел будет просто удален в конце
        // функции. При таком случае все необходимые переменные для удаления уже
        // заполнены корректно

        // Обработка Ч0
        // Самый сложный и интересный случай, нам необходимо перед удалением
        // перебаласировать дерево таким образом, чтобы черная высота не
        // нарушилась после удаления узла
        if (deleted_node->color_ == kBlack && deleted_node->left_ == nullptr &&
            deleted_node->right_ == nullptr) {
            EraseBalancing(deleted_node);
        }

        // Теперь собственно изымаем из дерева узел, который мы удаляем.
        if (deleted_node == Root()) {
            // Отдельно обрабатываем случай, когда удаляем корень дерева
            // Удаление именно корня возможно только в том случае, если он
            // единственный элемент дерева (в остальных случаях мы сведем задачу
            // к удалению другого узла). Поэтому в даном случае приводим
            // состояние служебного узла head_ в соответствие с изначальными
            // данными для пустого дерева.
            InitializeHead();
        } else {
            // В остальных случаях отцепляем ссылки родителя на нашу удаляемый
            // узел
            if (deleted_node == deleted_node->parent_->left_) {
                deleted_node->parent_->left_ = nullptr;
            } else {
                deleted_node->parent_->right_ = nullptr;
            }

            // Ищем новый минимум для служебного узла, если мы удаляем старый
            // минимум
            if (MostLeft() == deleted_node) {
                MostLeft() = SearchMinimum(Root());
            }

            // Ищем новый максимум для служебного узла, если мы удаляем старый
            // максимум
            if (MostRight() == deleted_node) {
                MostRight() = SearchMaximum(Root());
            }
        }
        // И уменьшаем количество элементов дерева, т.к. мы изъяли из него один
        // узел
        --size_;

        // Приводим узел к виду по умолчанию
        deleted_node->ToDefault();

        return deleted_node;
    }

    /**
     * @brief Меняет местами узлы node и other с целью последующего удаления
     * узла node - это важный момент, т.е. это не универсальный свап узлов, а
     * только частный случай (универсальный более сложен, но нам не нужны эти
     * лишние действия)
     *
     * Необходимость обмена именно узлов, а не их значений описана в функции
     * ExtractNode()
     *
     * @param node
     * @param other
     */
    void SwapNodesForErase(tree_node *node, tree_node *other) noexcept {
        // Меняем ссылку на узел other у родителя other
        if (other->parent_->left_ == other) {
            other->parent_->left_ = node;
        } else {
            other->parent_->right_ = node;
        }

        if (node == Root()) {
            // Если node является корнем дерева, то меняем ссылку на новый
            // корень
            Root() = other;
        } else {
            // Если node не является корнем, то меняем ссылку на узел node у
            // родителя node
            if (node->parent_->left_ == node) {
                node->parent_->left_ = other;
            } else {
                node->parent_->right_ = other;
            }
        }

        // Свапаем всё, кроме key_, т.к. ключи должны остаться на своем месте в
        // дереве, а все остальное должно обменяться (см. описание алгоритма
        // удаления)
        std::swap(node->parent_, other->parent_);
        std::swap(node->left_, other->left_);
        std::swap(node->right_, other->right_);
        std::swap(node->color_, other->color_);

        // Меняем родителей у потомков свапаемых узлов

        if (node->left_) {
            // При текущем алгоритме удаления у нас не может быть left_
            // заполнен, но в универсальном варианте надо проверять
            node->left_->parent_ = node;
        }

        if (node->right_) {
            node->right_->parent_ = node;
        }

        if (other->left_) {
            other->left_->parent_ = other;
        }

        if (other->right_) {
            other->right_->parent_ = other;
        }
    }

    /**
     * @brief Функция для перебалансировки дерева перед удалением узла
     * deleted_node, чтобы черная высота не нарушилась после удаления узла.
     *
     * @details Перебалансировка выполняется в том случае, если удаляется черный
     * узел без детей, т.к. в этом случае гарантированно нарушается свойство 5
     * красно-чёрного дерева (свойства описаны в начале файла).
     *
     * При перебалансировке возможны 8 различных случаев:
     * 1) 4 случая, если удаляемый элемент находится слева от родителя (левый
     * сын).
     * 2) 4 случая, если удаляемый элемент находится справа от родителя
     * (правый сын).
     *
     * Мы рассмотрим только 4 случая для левого сына. Вторые 4 случая (для
     * правого сына) зеркально отражают первые четыре случая (это очень наглядно
     * будет видно по коду).
     *
     * Терминология далее:
     * check_node - элемент, для которого мы хотим восстановить высоту (на
     * первой итерации является удаляемым элементом) parent - Родитель
     * check_node sibling - Брат или сестра check_node (второй ребенок parent)
     *
     * Возможные случаи для для левого сына:
     * 6.1) sibling красного цвета.
     *
     * В этом случае мы меняем местами цвета sibling и parent, а затем выполняем
     * поворот налево через parent (при этом изменятся parent и sibling в
     * текущей итерации алгоритма). Это сводит случай 6.1 к случаям 6.2, 6.3
     * или 6.4.
     *
     * 6.2) sibling черного цвета и оба ребенка sibling черного цвета.
     *
     * В этом случае мы меняем цвет sibling на красный.
     * Если цвет parent красный, то мы меняем его цвет на черный и останавливаем
     * балансировку (дерево будет сбалансировано).
     * Если цвет parent черный, мы устанавливаем check_node равной parent и
     * переходим к следующей итерации балансировки (т.е. начинаем проверять
     * случаи для нового check_node, начиная с 6.1). Это обусловлено тем, что в
     * данном случае мы изменили цвет sibling на красный - в результате чёрная
     * высота всей нашей структуры уменьшилась на 1 и мы должны рекурсивно
     * вызывать балансировку для parent.
     *
     * 6.3) sibling черного цвета, левый ребенок sibling красный, правый ребенок
     * sibling черный.
     *
     * В этом случае мы меняем местами цвета sibling и левого ребенка sibling, а
     * затем выполняем поворот направо через sibling (при этом изменится sibling
     * в текущей итерации алгоритма). Это сводит случай 6.3 к случаю 6.4.
     *
     * 6.4) sibling черного цвета, правый ребенок sibling красный.
     *
     * В этом случае мы меняем цвет правого ребенка sibling на черный, меняем
     * цвет sibling на цвет parent, меняем цвет parent на черный, а затем
     * выполняем поворот налево через sibling. После этого дерево будет
     * сбалансировано, останавливаем балансировку
     *
     * P.S. Можно посмотреть картинки, примеры и почитать дополнительные
     * описания тут:
     * https://algorithmtutor.com/Data-Structures/Tree/Red-Black-Trees/
     *
     * @param deleted_node Удаляемый узел
     */
    void EraseBalancing(tree_node *deleted_node) noexcept {
        tree_node *check_node = deleted_node;
        tree_node *parent = deleted_node->parent_;

        // Проверку осуществляем в цикле, пока проверяемый узел черный
        // (необходимость зацикливания указана в описании случая 6.2)). Ну или
        // пока дерево не кончится
        while (check_node != Root() && check_node->color_ == kBlack) {
            if (check_node == parent->left_) {
                // Удаляемый элемент находится слева от родителя
                tree_node *sibling = parent->right_;

                // Случай 6.1
                if (sibling->color_ == kRed) {
                    std::swap(sibling->color_, parent->color_);
                    RotateLeft(parent);
                    parent = check_node->parent_;
                    sibling = parent->right_;
                }

                // Случай 6.2
                if (sibling->color_ == kBlack &&
                    (sibling->left_ == nullptr ||
                     sibling->left_->color_ == kBlack) &&
                    (sibling->right_ == nullptr ||
                     sibling->right_->color_ == kBlack)) {
                    sibling->color_ = kRed;
                    if (parent->color_ == kRed) {
                        parent->color_ = kBlack;
                        // Балансировка завершена
                        break;
                    }
                    // Идем балансировать parent
                    check_node = parent;
                    parent = check_node->parent_;
                } else {
                    if (sibling->left_ != nullptr &&
                        sibling->left_->color_ == kRed &&
                        (sibling->right_ == nullptr ||
                         sibling->right_->color_ == kBlack)) {
                        // Случай 6.3
                        std::swap(sibling->color_, sibling->left_->color_);
                        RotateRight(sibling);
                        sibling = parent->right_;
                    }

                    // Случай 6.4
                    sibling->right_->color_ = kBlack;
                    sibling->color_ = parent->color_;
                    parent->color_ = kBlack;
                    RotateLeft(parent);
                    // Балансировка завершена
                    break;
                }
            } else {
                // Удаляемый элемент находится справа от родителя
                tree_node *sibling = parent->left_;

                // Случай 6.1
                if (sibling->color_ == kRed) {
                    std::swap(sibling->color_, parent->color_);
                    RotateRight(parent);
                    parent = check_node->parent_;
                    sibling = parent->left_;
                }

                // Случай 6.2
                if (sibling->color_ == kBlack &&
                    (sibling->left_ == nullptr ||
                     sibling->left_->color_ == kBlack) &&
                    (sibling->right_ == nullptr ||
                     sibling->right_->color_ == kBlack)) {
                    sibling->color_ = kRed;
                    if (parent->color_ == kRed) {
                        parent->color_ = kBlack;
                        // Балансировка завершена
                        break;
                    }
                    // Идем балансировать parent
                    check_node = parent;
                    parent = check_node->parent_;
                } else {
                    if (sibling->right_ != nullptr &&
                        sibling->right_->color_ == kRed &&
                        (sibling->left_ == nullptr ||
                         sibling->left_->color_ == kBlack)) {
                        // Случай 6.3
                        std::swap(sibling->color_, sibling->right_->color_);
                        RotateLeft(sibling);
                        sibling = parent->left_;
                    }
                    // Случай 6.4
                    sibling->left_->color_ = kBlack;
                    sibling->color_ = parent->color_;
                    parent->color_ = kBlack;
                    RotateRight(parent);
                    // Балансировка завершена
                    break;
                }
            }
        }
    }

    /**
     * @brief Находит среди потомков node самый маленький (самый левый) элемент
     * дерева и возвращает указатель на него.
     *
     * @param node
     * @return tree_node*
     */
    tree_node *SearchMinimum(tree_node *node) const noexcept {
        while (node->left_ != nullptr) {
            node = node->left_;
        };
        return node;
    }

    /**
     * @brief Находит среди потомков node самый большой (самый правый) элемент
     * дерева и возвращает указатель на него.
     *
     * @param node
     * @return tree_node*
     */
    tree_node *SearchMaximum(tree_node *node) const noexcept {
        while (node->right_ != nullptr) {
            node = node->right_;
        };
        return node;
    }

    /**
     * @brief Рассчитывает высоту дерева. Должно соблюдаться правило, что любой
     * простой путь от узла-предка до листового узла-потомка содержит одинаковое
     * число чёрных узлов.
     *
     * @param node Указатель на узел, с которого начинается проверка.
     * @return int Высота дерева. Если дерево не сбалансировано по высоте, то
     * будет возвращено -1
     */
    int ComputeBlackHeight(const tree_node *node) const noexcept {
        // Для пустого поддерева ответ очевиден
        if (node == nullptr) {
            return 0;
        }

        // Рекурсивно вычисляет высоту для левого и правого дочерних элементов
        int left_height = ComputeBlackHeight(node->left_);
        int right_height = ComputeBlackHeight(node->right_);
        int add = node->color_ == kBlack ? 1 : 0;
        // Возвращает -1, если дерево не является корректным:
        // 1) Если левое поддерево не является корректным
        // 2) Если правое поддерево не является корректным
        // 3) Если черная высота левого поддерева не равна высоте правого
        if (left_height == -1 || right_height == -1 ||
            left_height != right_height) {
            return -1;
        } else {
            return left_height + add;
        }
    }

    /**
     * @brief Рекурсивно проверяет, что оба потомка каждого красного узла —
     * чёрные. В красно-черном дереве не может быть двух красных узлов подряд.
     *
     * @param Node Указатель на узел, с которого начинается проверка.
     * @return true Нет двух красных узлов подряд
     * @return false Есть два красных узла подряд
     */
    bool checkRedNodes(const tree_node *Node) const noexcept {
        if (Node->color_ == kRed) {
            if (Node->left_ != nullptr && Node->left_->color_ == kRed) {
                return false;
            }
            if (Node->right_ != nullptr && Node->right_->color_ == kRed) {
                return false;
            }
        }

        if (Node->left_ != nullptr) {
            if (checkRedNodes(Node->left_) == false) {
                return false;
            }
        }

        if (Node->right_ != nullptr) {
            if (checkRedNodes(Node->right_) == false) {
                return false;
            }
        }

        return true;
    }

    /**
     * @brief Класс, реализующий узел красно-чёрного дерева
     *
     */
    struct RedBlackTreeNode {
        /**
         * @brief Конструктор по умолчанию для создания пустого узла дерева, с
         * дефолтной инициализацией значения узла
         * @details left_ и right_ указывают на this, т.к. этот конструктор
         * используется для создания головы дерева
         */
        RedBlackTreeNode()
            : parent_(nullptr), left_(this), right_(this), key_(key_type{}),
              color_(kRed) {
        }

        /**
         * @brief Конструктор, создающий узел дерева, инициализированный
         * значением key
         *
         * @param key значение для инициализации узла
         */
        RedBlackTreeNode(const key_type &key)
            : parent_(nullptr), left_(nullptr), right_(nullptr), key_(key),
              color_(kRed) {
        }

        /**
         * @brief Конструктор, создающий узел дерева, инициализированный
         * значением key, используя move-семантику. Очень актуально для тех
         * случаев, когда для создания узла используется временный уже
         * сконструированный объект, например, в emplace()
         *
         * @param key значение для инициализации узла
         */
        RedBlackTreeNode(key_type &&key)
            : parent_(nullptr), left_(nullptr), right_(nullptr),
              key_(std::move(key)), color_(kRed) {
        }

        /**
         * @brief Конструктор, создающий узел дерева, инициализированный
         * значением key и цветом color
         *
         * @param key значение для инициализации узла
         * @param color значение для цвета узла
         */
        RedBlackTreeNode(key_type key, tree_color color)
            : parent_(nullptr), left_(nullptr), right_(nullptr), key_(key),
              color_(color) {
        }

        /**
         * @brief Приводим узел к виду по умолчанию. Т.е. все указатели узла
         * делаем nullptr, а цвет красным. Именно в таком виде вставляются новые
         * узлы в дерево
         */
        void ToDefault() noexcept {
            left_ = nullptr;
            right_ = nullptr;
            parent_ = nullptr;
            color_ = kRed;
        }

        /**
         * @brief Возвращает следующий относительно this узел дерева.
         * @details Реализация описана по ходу функции. В реализации учитывается
         * наличие служебного узла (головы), через которую реализуется
         * зацикливание при обходе элементов.
         *
         * @return tree_node*
         */
        tree_node *NextNode() const noexcept {
            // Мы не меняем текущий узел в этой функции, поэтому со спокойной
            // совестью делаем const_cast
            tree_node *node = const_cast<tree_node *>(this);
            if (node->color_ == kRed &&
                (node->parent_ == nullptr || node->parent_->parent_ == node)) {
                // Если мы находимся в End(), то сдвигаем итератор в left, чтобы
                // оказаться на самом маленьком элементе дерева (указатель на
                // который и хранится в left в End()) Критерии, что текущий узел
                // является End(): 1) Цвет текущего узла красный (Т.к. корень
                // всегда черный, а End() всегда красный). AND 2) Родитель
                // текущего узла равен nullptr - только у End() parent может
                // быть nullptr для пустого дерева (и это надо проверять, чтобы
                // не словить segmentation fault для пустого дерева). OR 3)
                // Родитель родителя текущего узла равен текущему узлу. Это
                // выполняется и для корня дерева и для End(), поэтому нужно еще
                // первое условие с проверкой цвета.
                node = node->left_;
            } else if (node->right_ != nullptr) {
                // Если мы находимся не в End() и правая ветвь непустая, то в
                // первую очередь идем в неё, т.к. ближайший больший элемента
                // будет именно в правой ветви
                node = node->right_;

                // Далее сдвигаемся полностью влево (while left_ != nullptr), до
                // самого маленького элемента в левых ветвях, он и будет самым
                // маленьким следующим элементом. Если левых ветвей вообще не
                // будет, то самым маленьким останется правая ветвь, в которую
                // мы зашли в начале блока
                while (node->left_ != nullptr) {
                    node = node->left_;
                }
            } else {
                // В остальных случаях сдвигаемся к родительскому элементу до
                // тех пор, пока правая ветвь родителя будет содержать узел,
                // отличный от текущего
                tree_node *parent = node->parent_;

                while (node == parent->right_) {
                    node = parent;
                    parent = parent->parent_;
                }
                // Если в дереве у корня нет правого элемента, то при инкременте
                // мы будем каждый раз попадать на него: Указатель находится  на
                // корне. Т.к. right пустой, то идем в parent (который является
                // служебным узлом End(). У parent-right указывает на самый
                // большой элемент дерева, т.е. на нашу единственный узел,
                // поэтому мы опять поднимаемся в parent, который указывает на
                // нашу единственный узел (parent у End() указывает на корень
                // дерева). Чтобы этого не происходило, добавляем проверку
                // node->right_ != parent, т.е. находясь в End(), мы не будем
                // уходить в parent
                if (node->right_ != parent) {
                    node = parent;
                }
            }

            return node;
        }

        /**
         * @brief Возвращает предыдущий относительно this узел дерева.
         * @details Работает идентично NextNode, только двигаемся в обратную
         * сторону, поэтому всё наоборот.
         *
         * @return tree_node*
         */
        tree_node *PrevNode() const noexcept {
            tree_node *node = const_cast<tree_node *>(this);

            if (node->color_ == kRed &&
                (node->parent_ == nullptr || node->parent_->parent_ == node)) {
                node = node->right_;
            } else if (node->left_ != nullptr) {
                node = node->left_;
                while (node->right_ != nullptr) {
                    node = node->right_;
                }
            } else {
                tree_node *parent = node->parent_;
                while (node == parent->left_) {
                    node = parent;
                    parent = parent->parent_;
                }
                if (node->left_ != parent) {
                    node = parent;
                }
            }

            return node;
        }
        // Указатель на родителя узла дерева
        tree_node *parent_;
        // Указатель на левого потомка узла дерева
        tree_node *left_;
        // Указатель на правого потомка узла дерева
        tree_node *right_;
        // Значение узла дерева
        key_type key_;
        // Цвет узла дерева
        tree_color color_;
    };

    /**
     * @brief Класс итератора для дерева
     *
     * @details У нас реализован классический обход дерева от минимального
     * элемента к максимальному, как в любом бинарном дереве, это и делает
     * дерево сразу отсортированным списком. Необходимо только определить
     * минимальный элемент дерева (это будет первым элементом списка) и
     * максимальный элемент дерева (это будет последний элемент списка).
     *
     * Для удобной организации обхода и быстрого определения Begin(), End() и
     * корня в дереве хранится служебный узел (голова - head):
     * End() указывает на head
     * head->left указывает на минимальный узел дерева (он же является Begin())
     * head->right указывает на максимальный узел дерева, --End() осуществляет
     * переход на head->right
     * head->parent указывает на корень дерева
     *
     * В пустом дереве head всё равно есть, при этом:
     * head->left указывает на head
     * head->right указывает на head
     * head->parent является nullptr
     *
     * При такой реализации обход дерева в обе стороны у нас зацикливается:
     * ++: предпоследний -> последний -> End() -> первый
     * --: первый -> End() -> последний -> предпоследний
     */
    struct RedBlackTreeIterator {
        // C++ ожидает от итератора некоторых свойств, их наличие позволяет
        // использовать с итераторами функции из других библиотек и
        // оптимизировать алгоритмы, работающие с ними. Например, мы теперь
        // можем использовать std::next с нашим итератором. Вот эти пять свойств
        // нужны:
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = tree_type::key_type;
        using pointer = value_type *;
        using reference = value_type &;

        /**
         * @brief Дефолтный конструктор запрещен, т.к. пустой итератор нам не
         * нужен
         */
        RedBlackTreeIterator() = delete;

        /**
         * @brief Основной конструктор. Помечаем основной конструктор как
         * explicit, чтобы избежать сюрпризов из-за неявных преобразований - мы
         * всегда должны четко указывать, что хотим при создании итератора
         *
         * @param node указатель на узел, на который будет указывать итератор
         */
        explicit RedBlackTreeIterator(tree_node *node) : node_(node) {
        }

        /**
         * @brief Получение указателя на значение узла, на который указывает
         * итератор.
         *
         * @return reference
         */
        reference operator*() const noexcept {
            return node_->key_;
        }

        /**
         * @brief Префиксное перемещение итератора вперед для обращения к
         * следующему элементу.
         *
         * @return iterator& ссылка на новый элемент
         */
        iterator &operator++() noexcept {
            node_ = node_->NextNode();
            return *this;
        }

        /**
         * @brief Постфиксное перемещение итератора вперед для обращения к
         * следующему элементу.
         *
         * @return iterator значение до перемещения
         */
        iterator operator++(int) noexcept {
            iterator tmp{node_};
            ++(*this);
            return tmp;
        }

        /**
         * @brief Префиксное перемещение итератора назад для обращения к
         * предыдущему элементу.
         *
         * @return iterator& ссылка на новый элемент
         */
        iterator &operator--() noexcept {
            node_ = node_->PrevNode();
            return *this;
        }

        /**
         * @brief Постфиксное перемещение итератора вперед для обращения к
         * следующему элементу.
         *
         * @return iterator значение до перемещения
         */
        iterator operator--(int) noexcept {
            iterator tmp{node_};
            --(*this);
            return tmp;
        }

        /**
         * @brief Два итератора равны, если они указывают на один и тот же
         * элемент.
         *
         * @param other
         * @return true  - равны
         * @return false - неравны
         */
        bool operator==(const iterator &other) const noexcept {
            return node_ == other.node_;
        }

        /**
         * @brief Два итератора не равны, если они указывают на разные элементы.
         *
         * @param other
         * @return true  - неравны
         * @return false - равны
         */
        bool operator!=(const iterator &other) const noexcept {
            return node_ != other.node_;
        }

        // Указатель на узел, на который указывает итератор
        tree_node *node_;
    };

    /**
     * @brief Класс константного итератора для списка. Используется в тех
     * случаях, когда итератор не должен позволят менять элементы списка,
     * например, для const объектов
     *
     * @details В целом идентичен обычному итератору, но имеет следующие
     * отличия:
     * - pointer и reference объявлены как const
     * - поле node_ класса объявлено как const
     * - имеет дополнительный конструктор для конструирования объекта из
     * обычного итератора (нужен для неявного преобразования iterator в
     * const_iterator)
     * - операторы == и != перегружены как дружественные, чтобы при сравнении
     * неconst и const происходило неявное преобразование неconst в const
     */
    struct RedBlackTreeIteratorConst {
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = tree_type::key_type;
        using pointer = const value_type *;
        using reference = const value_type &;

        RedBlackTreeIteratorConst() = delete;

        explicit RedBlackTreeIteratorConst(const tree_node *node)
            : node_(node) {
        }

        RedBlackTreeIteratorConst(const iterator &it) : node_(it.node_) {
        }

        reference operator*() const noexcept {
            return node_->key_;
        }

        const_iterator &operator++() noexcept {
            node_ = node_->NextNode();
            return *this;
        }

        const_iterator operator++(int) noexcept {
            const_iterator tmp{node_};
            ++(*this);
            return tmp;
        }

        const_iterator &operator--() noexcept {
            node_ = node_->PrevNode();
            return *this;
        }

        const_iterator operator--(int) noexcept {
            const_iterator tmp{node_};
            --(*this);
            return tmp;
        }

        friend bool operator==(const const_iterator &it1,
                               const const_iterator &it2) noexcept {
            return it1.node_ == it2.node_;
        }

        friend bool operator!=(const const_iterator &it1,
                               const const_iterator &it2) noexcept {
            return it1.node_ != it2.node_;
        }

        const tree_node *node_;
    };

    // Указатель на голову дерева
    tree_node *head_;
    // Количество элементов в дереве
    size_type size_;
    // Компаратор дерева (класс для сравнения значений узлов)
    Comparator cmp_;
};

#if defined(S21_CONTAINERS_TREE_TEST_HELPER)
#include "s21_tree_test_helper.inc"
#endif

}  // namespace s21

#endif  // S21_CONTAINERS_S21_CONTAINERS_S21_TREE_H_
