template <typename Type>
class RedBlackTreeTestHelper {
  public:
    using tree_type = RedBlackTree<Type>;
    using tree_node = typename tree_type::RedBlackTreeNode;
    using tree_color = RedBlackTreeColor;

    static tree_type GetIncorrectTreeType1() {
        tree_type tmp;
        tmp.Insert(1);
        tmp.Insert(2);
        tmp.Insert(3);
        tmp.Insert(4);
        tmp.Insert(5);
        tmp.head_->color_ = kBlack;
        return tmp;
    }

    static tree_type GetIncorrectTreeType2() {
        tree_type tmp;
        tmp.Insert(1);
        tmp.Insert(2);
        tmp.Insert(3);
        tmp.Insert(4);
        tmp.Insert(5);
        tmp.Root()->color_ = kRed;
        return tmp;
    }

    static tree_type GetIncorrectTreeType3() {
        tree_type tmp;
        tmp.Insert(1);
        tmp.Insert(2);
        tmp.Insert(3);
        tmp.Insert(4);
        tmp.Insert(5);

        tmp.Find(1).node_->color_ = kRed;
        return tmp;
    }

    static tree_type GetIncorrectTreeType4() {
        tree_type tmp;
        tmp.Insert(1);
        tmp.Insert(2);
        tmp.Insert(3);
        tmp.Insert(4);
        tmp.Insert(5);
        tmp.Insert(0);
        tmp.Insert(-1);

        tmp.Find(0).node_->color_ = kRed;
        return tmp;
    }

    static tree_type GetIncorrectTreeType5() {
        tree_type tmp;
        tmp.Insert(1);
        tmp.Insert(2);
        tmp.Insert(3);
        tmp.Insert(4);
        tmp.Insert(5);
        tmp.Insert(0);
        tmp.Insert(-1);

        tmp.Find(4).node_->color_ = kRed;
        return tmp;
    }

    static tree_type GetIncorrectTreeType6() {
        tree_type tmp;
        tmp.Insert(1);
        tmp.Insert(2);
        tmp.Insert(3);
        tmp.Insert(4);
        tmp.Insert(5);
        tmp.Insert(0);
        tmp.Insert(-1);

        tmp.Find(0).node_->color_ = kRed;
        tmp.Find(-1).node_->color_ = kBlack;
        return tmp;
    }
};
