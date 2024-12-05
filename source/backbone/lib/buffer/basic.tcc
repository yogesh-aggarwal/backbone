#pragma once

#include "buffer.hpp"

#include <array>

/* ------------------------------------------------------------------------------------------------------- */

template<typename T, size_t MAX_SIZE>
class BasicBuffer : public IBuffer<T, MAX_SIZE>
{
private:
   T                       m_DefaultValue;
   std::array<T, MAX_SIZE> buffer;

   size_t m_ReadIndex;
   size_t m_WriteIndex;

public:
   BasicBuffer(T defaultValue) : m_ReadIndex(0), m_WriteIndex(0), m_DefaultValue(std::move(defaultValue))
   {
      buffer.fill(m_DefaultValue);
   }

   size_t
   GetCapacity() override
   {
      return MAX_SIZE;
   }

   T
   Get() override
   {
      return buffer[m_ReadIndex];
   }

   Result<T>
   GetAt(size_t index) override
   {
      if (index >= MAX_SIZE)
      {
         return { m_DefaultValue, new Error({ OUT_OF_BOUNDS, "Index out of bounds" }) };
      }

      return { buffer[index] };
   }

   Result<std::vector<T>>
   GetRange(size_t start, size_t end) override
   {
      if (start >= MAX_SIZE || end >= MAX_SIZE || start > end)
      {
         return { {}, new Error({ OUT_OF_BOUNDS, "Range out of bounds" }) };
      }

      std::vector<T> range(buffer.begin() + start, buffer.begin() + end + 1);
      return { range };
   }

   Result<T>
   Read() override
   {
      if (m_ReadIndex >= MAX_SIZE)
      {
         return { m_DefaultValue, new Error({ OUT_OF_BOUNDS, "Read index out of bounds" }) };
      }

      return { buffer[m_ReadIndex++] };
   }

   Result<T>
   ReadAt(size_t index) override
   {
      if (index >= MAX_SIZE)
      {
         return { m_DefaultValue, new Error({ OUT_OF_BOUNDS, "Index out of bounds" }) };
      }

      return { buffer[index] };
   }

   Result<std::vector<T>>
   ReadRange(size_t start, size_t end) override
   {
      if (start >= MAX_SIZE || end >= MAX_SIZE || start > end)
      {
         return { {}, new Error({ OUT_OF_BOUNDS, "Range out of bounds" }) };
      }

      std::vector<T> range(buffer.begin() + start, buffer.begin() + end + 1);
      m_ReadIndex = end + 1;
      return { range };
   }

   size_t
   GetReadIndex() override
   {
      return m_ReadIndex;
   }

   size_t
   GetReadRemaining() override
   {
      return MAX_SIZE - m_ReadIndex;
   }

   Result<bool>
   SeekRead(size_t index) override
   {
      if (index >= MAX_SIZE) { return { false, new Error({ OUT_OF_BOUNDS, "Index out of bounds" }) }; }

      m_ReadIndex = index;
      return { true };
   }

   Result<uint16_t>
   ReadUInt16() override
   {
      if (m_ReadIndex + 1 >= MAX_SIZE)
      {
         return { m_DefaultValue, new Error({ OUT_OF_BOUNDS, "Read index out of bounds" }) };
      }

      uint16_t value = (buffer[m_ReadIndex] << 8) | buffer[m_ReadIndex + 1];
      m_ReadIndex += 2;
      return { value };
   }

   Result<uint32_t>
   ReadUInt32() override
   {
      if (m_ReadIndex + 3 >= MAX_SIZE)
      {
         return { m_DefaultValue, new Error({ OUT_OF_BOUNDS, "Read index out of bounds" }) };
      }

      uint32_t value = (buffer[m_ReadIndex] << 24) | (buffer[m_ReadIndex + 1] << 16) |
                       (buffer[m_ReadIndex + 2] << 8) | buffer[m_ReadIndex + 3];
      m_ReadIndex += 4;
      return { value };
   }

   Result<bool>
   Write(T value) override
   {
      if (m_WriteIndex >= MAX_SIZE)
      {
         return { false, new Error({ OUT_OF_BOUNDS, "Write index out of bounds" }) };
      }

      buffer[m_WriteIndex++] = value;
      return { true };
   }

   Result<bool>
   WriteAt(size_t index, T value) override
   {
      if (index >= MAX_SIZE) { return { false, new Error({ OUT_OF_BOUNDS, "Index out of bounds" }) }; }

      buffer[index] = value;
      return { true };
   }

   Result<bool>
   WriteRange(size_t start, size_t end, std::vector<T> values) override
   {
      if (start >= MAX_SIZE || end >= MAX_SIZE || start > end || values.size() != (end - start + 1))
      {
         return { false, new Error({ OUT_OF_BOUNDS, "Range out of bounds or size mismatch" }) };
      }

      std::copy(values.begin(), values.end(), buffer.begin() + start);
      m_WriteIndex = end + 1;
      return { true };
   }

   size_t
   GetWriteIndex() override
   {
      return m_WriteIndex;
   }

   size_t
   GetWriteRemaining() override
   {
      return MAX_SIZE - m_WriteIndex;
   }

   Result<bool>
   SeekWrite(size_t index) override
   {
      if (index >= MAX_SIZE) { return { false, new Error({ OUT_OF_BOUNDS, "Index out of bounds" }) }; }

      m_WriteIndex = index;
      return { true };
   }

   Result<bool>
   WriteUInt16(uint16_t value) override
   {
      if (m_WriteIndex + 1 >= MAX_SIZE)
      {
         return { false, new Error({ OUT_OF_BOUNDS, "Write index out of bounds" }) };
      }

      buffer[m_WriteIndex++] = (value >> 8) & 0xFF;
      buffer[m_WriteIndex++] = value & 0xFF;
      return { true };
   }

   Result<bool>
   WriteUInt32(uint32_t value) override
   {
      if (m_WriteIndex + 3 >= MAX_SIZE)
      {
         return { false, new Error({ OUT_OF_BOUNDS, "Write index out of bounds" }) };
      }

      buffer[m_WriteIndex++] = (value >> 24) & 0xFF;
      buffer[m_WriteIndex++] = (value >> 16) & 0xFF;
      buffer[m_WriteIndex++] = (value >> 8) & 0xFF;
      buffer[m_WriteIndex++] = value & 0xFF;
      return { true };
   }

   Result<std::vector<T>>
   Serialize() override
   {
      std::vector<T> data(buffer.begin(), buffer.begin() + m_WriteIndex);
      return { data };
   }

   Result<bool>
   Deserialize(std::vector<T> data) override
   {
      if (data.size() > MAX_SIZE)
      {
         return { false, new Error({ OUT_OF_BOUNDS, "Data size exceeds buffer capacity" }) };
      }

      std::copy(data.begin(), data.end(), buffer.begin());
      m_WriteIndex = data.size();
      return { true };
   }
};

/* ------------------------------------------------------------------------------------------------------- */
