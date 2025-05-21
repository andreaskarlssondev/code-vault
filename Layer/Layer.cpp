#include "Layer.h"

std::unordered_map<std::string, uint32_t> Layer::LayerTable;
std::unordered_map<uint32_t, std::string> Layer::LayerNameTable;

Layer::Layer(const std::string& aLayerName)
{
    uint32_t bitPosition = GetBitPosition(aLayerName);
    myBit |= (1 << bitPosition);
}

