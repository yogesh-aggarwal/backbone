#pragma once

#include <array>
#include <stdint.h>

#include <backbone/core/pch>

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

      Result<bool>
      SeekRead(uint16_t offset);

      Result<bool>
      SeekWrite(uint16_t offset);

      Result<bool>
      StepRead(uint16_t offset);

      Result<bool>
      StepWrite(uint16_t offset);

      uint8_t
      Get();

      Result<uint8_t>
      GetAt(uint16_t index);

      Result<std::vector<uint8_t>>
      GetRange(uint16_t start, uint16_t len);

      Result<uint8_t>
      ReadAsU8();

      Result<uint16_t>
      ReadAsU16();

      Result<uint32_t>
      ReadAsU32();

      Result<bool>
      WriteU8(uint8_t value);

      Result<bool>
      WriteU16(uint16_t value);

      Result<bool>
      WriteU32(uint32_t value);
   };
}
