#include "IntegerScalingConverter.h"


namespace Handmada::TetraCode::Matrix {
    IntegerScalingConverter::IntegerScalingConverter(int ratio)
        : _ratio(ratio)
    {
    }


    PixelViewPtr IntegerScalingConverter::directView(PixelViewPtr&& original) const
    {
        throw std::runtime_error("Not implemented");
    }


    PixelViewPtr IntegerScalingConverter::inverseView(PixelViewPtr&& converted) const
    {
        throw std::runtime_error("Not implemented");
    }
}
