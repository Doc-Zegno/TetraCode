#include "Encoder.h"

#include <vector>
#include <algorithm>


namespace TetraCode {
	Encoder::Encoder(coord_t maxSide, coord_t minSide, coord_t pivotSide, const Palette* palette)
		: _maxSide(maxSide), _minSide(minSide), _pivotSide(pivotSide), _palette(palette)
	{
	}


	std::pair<std::unique_ptr<Pixel[]>, int> Encoder::sequence2image(const byte_t* sequence, size_t length) const
	{
		TetraTree root(0U, 0U, _maxSide, 0U, 0U, 0);

		std::vector<TetraTree*> stack = { &root };
		auto numNodes = length;
		for (auto i = 0U; i < numNodes; i++) {
			auto tree = stack[i];
			tree->spawnChildren();
			tree->calculateChildrenColors(CodeBits(sequence[i]));

			for (auto& child : tree->children()) {
				if (child->color().isActive()) {
					stack.push_back(child.get());
				}
			}
		}

		auto optimalSide = std::max(_minSide, (1 << root.calculateHeight()) * _pivotSide * 2);
		auto compression = _maxSide / optimalSide;

		Pixel* image = new Pixel[optimalSide * optimalSide];
		fillImage(root, image, optimalSide, compression);

		return std::make_pair(std::unique_ptr<Pixel[]>(image), optimalSide);
	}

	void Encoder::fillImage(const TetraTree& tree, Pixel* image, coord_t optimalSide, coord_t compression) const
	{
		auto side = tree.side() / compression;
		auto xMin = tree.xMin() / compression;
		auto yMin = tree.yMin() / compression;
		auto xMax = xMin + side;
		auto yMax = yMin + side;
		auto pixel = _palette->color2pixel(tree.color());

		if (!tree.children().empty()) {
			for (auto& child : tree.children()) {
				fillImage(*child, image, optimalSide, compression);
			}

			if (tree.xPivot() == 1U) {
				xMin = xMax - _pivotSide;
			} else {
				xMax = xMin + _pivotSide;
			}

			if (tree.yPivot() == 1U) {
				yMin = yMax - _pivotSide;
			} else {
				yMax = yMin + _pivotSide;
			}
		}

		for (auto x = xMin; x < xMax; x++) {
			for (auto y = yMin; y < yMax; y++) {
				image[y * optimalSide + x] = pixel;
			}
		}
	}
}