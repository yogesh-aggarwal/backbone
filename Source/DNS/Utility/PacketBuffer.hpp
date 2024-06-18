#pragma once

#include <array>
#include <stdint.h>

#include <DNS/Core/Result.tcc>

namespace DNS::Utility
{
   class PacketBuffer
   {
   private:
      std::array<uint8_t, 512> m_Buffer;

      uint16_t m_ReadOffset;
      uint16_t m_WriteOffset;

   public:
      PacketBuffer() = default;

      Result<uint8_t>
      ReadAsU8();

      Result<uint16_t>
      ReadAsU16();

      Result<uint32_t>
      ReadAsU32();
   };
}
