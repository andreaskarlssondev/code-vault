#pragma once

#include <string>
#include <unordered_map>
#include <assert.h>


class Layer
{
	public:
        Layer(const std::string& aLayerName);

        // Gives back mask value 
        static uint32_t CreateLayer(const std::string& aLayerName, uint32_t aLayerId)
        {
            auto it = LayerTable.find(aLayerName);
            if (it != LayerTable.end()) {
                return it->second;
            }

            // Assign a new bit position if the name is not found
            size_t newPosition = LayerTable.size();
            if (newPosition >= 32) {
                assert(false && L"Can not create more then 32 layers, same as unity");
            }

            LayerNameTable[aLayerId] = aLayerName;
            LayerTable[aLayerName] = aLayerId;
            return (1 << aLayerId);
        }

        static uint32_t NameToLayer(const std::string& aName)
        {
            if (!HasName(aName))
            {
                assert(false && "Layer does not exist");
                return 0;
            }

            return GetBitPosition(aName);
        }

        static bool HasName(const std::string& aName) {
            auto it = LayerTable.find(aName);
            return it != LayerTable.end();
        }

        static std::string LayerToName(uint32_t aLayer)
        {
            auto it = LayerNameTable.find(aLayer);
            if (it != LayerNameTable.end()) {
                return it->second;
            }

            assert(false && "Layer does not exist");
            return "Unknown Layer";
        }

        static uint32_t GetLayerMask(const std::string& aLayerName)
        {
            return (1 << GetBitPosition(aLayerName));
        }
        
        static uint32_t GetLayerMasks(std::initializer_list<std::string> someLayerNames)
        {
            uint32_t mask = 0;

            for (auto& layerName : someLayerNames)
            {
                mask |= GetLayerMask(layerName);
            }

            return mask;
        }

        uint32_t GetBit()
        {
            return myBit;
        }

	private:
        uint32_t myBit;

		static std::unordered_map<std::string, uint32_t> LayerTable;
        static std::unordered_map<uint32_t, std::string> LayerNameTable;

        static uint32_t GetBitPosition(const std::string& name) {
            auto it = LayerTable.find(name);
            if (it != LayerTable.end()) {
                return it->second;
            }

            assert(false && "Layer does not exist");
            return 0;
        }

};
