#pragma once

#include <memory>
#include <vector>

#include "Scrambler.h"


namespace Handmada::TetraCode::Sequence {
    /// <summary>
    /// Provides a convenient functionality for dealing with a sequence
    /// of scramblers
    /// </summary>
    class ScramblingPipeline : public Scrambler {
    private:
        std::vector<std::unique_ptr<Scrambler>>& _scramblers;

    public:
        ScramblingPipeline(std::vector<std::unique_ptr<Scrambler>>& scramblers);

        virtual ByteIteratorPtr encodingIterator(ByteIteratorPtr&& iterator) override;
        virtual ByteIteratorPtr decodingIterator(ByteIteratorPtr&& iterator) override;
    };
}
