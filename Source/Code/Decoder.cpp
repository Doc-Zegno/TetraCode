#include "Decoder.h" 

#include <queue>

#include "TetraTree.h"
#include "IteratorExceptionsMacros.h"


namespace Handmada::TetraCode::Code {
    using Visual::Color;
    using Matrix::MatrixView;
    using Sequence::Iterator;


    
    // H e l p e r    c l a s s
    class DecodingIterator : public Iterator<byte_t> {
    private:
        TetraTree _root;
        std::queue<TetraTree*> _worklist;
        byte_t _current;
        bool _isValid;

    public:
        DecodingIterator(TetraTree&& root);

        virtual byte_t current() override;
        virtual bool moveNext() override;
    };


    DecodingIterator::DecodingIterator(TetraTree&& root)
        : _root(std::move(root))
    {
        _worklist.push(&_root);
        _isValid = false;
    }


    byte_t DecodingIterator::current()
    {
        if (!_isValid) {
            throw Sequence::InvalidIteratorException(Sequence::TraceableExceptionPtr());
        }
        return _current;
    }


    bool DecodingIterator::moveNext()
    {
        if (_worklist.empty()) {
            _isValid = false;
        } else {
            _isValid = true;

            auto tree = _worklist.front();
            _worklist.pop();

            auto bits = tree->calculateChildrenCode();
            _current = bits.toByte();

            for (auto& child : tree->children()) {
                if (child->color().isActive() && !child->children().empty()) {
                    _worklist.push(child.get());
                }
            }
        }
        return _isValid;
    }



    // F u n c t i o n s
    void buildDecodingTree(TetraTree* tree, const MatrixView<Visual::Color>& image)
    {
        auto stopped = false;
        if (tree->side() == 2) {
            stopped = true;
        }

        tree->spawnChildren();
        auto hasChildren = false;
        for (auto& child : tree->children()) {
            auto x = child->xMin();
            auto y = child->yMin();
            auto side = child->side();

            if (child->xPivot() == 1) {
                x += side - 1;
            }

            if (child->yPivot() == 1) {
                y += side - 1;
            }

            auto color = image.get(x, y);
            child->setColor(color);
            if (!stopped && child->oddity() == color.huePair()) {
                hasChildren = true;
                buildDecodingTree(child.get(), image);
            }
        }

        if (!hasChildren) {
            tree->removeChildren();
        }
    }


    std::unique_ptr<Iterator<byte_t>> image2sequence(const MatrixView<Visual::Color>& image)
    {
        auto side = image.height();
        auto root = TetraTree(0, 0, side, 0, 0, 0);
        buildDecodingTree(&root, image);
        return std::unique_ptr<Iterator<byte_t>>(new DecodingIterator(std::move(root)));
    }
}