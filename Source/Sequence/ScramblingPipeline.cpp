#include "ScramblingPipeline.h"


namespace Handmada::TetraCode::Sequence {
    ScramblingPipeline::ScramblingPipeline(std::vector<std::unique_ptr<Scrambler>>& scramblers)
        : _scramblers(scramblers)
    {
    }


    ByteIteratorPtr ScramblingPipeline::encodingIterator(ByteIteratorPtr&& iterator)
    {
        for (auto& scrambler : _scramblers) {
            iterator = scrambler->encodingIterator(std::move(iterator));
        }
        return std::move(iterator);
    }


    ByteIteratorPtr ScramblingPipeline::decodingIterator(ByteIteratorPtr&& iterator)
    {
        for (auto it = _scramblers.rbegin(); it != _scramblers.rend(); ++it) {
            auto& scrambler = *it;
            iterator = scrambler->decodingIterator(std::move(iterator));
        }
        return std::move(iterator);
    }
}
