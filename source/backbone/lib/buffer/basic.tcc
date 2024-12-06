#pragma once

#include "buffer.hpp"

#include <array>

/* ------------------------------------------------------------------------------------------------------- */

template<typename T, size_t MAX_SIZE>
class BasicBuffer : public IBuffer<T, MAX_SIZE> {
private:
   T                       m_DefaultValue;
   std::array<T, MAX_SIZE> buffer;

   size_t m_ReadIndex;
   size_t m_WriteIndex;

public:
   BasicBuffer(T defaultValue) : m_ReadIndex(0), m_WriteIndex(0), m_DefaultValue(std::move(defaultValue)) {
      buffer.fill(m_DefaultValue);
   }

   size_t
   get_capacity() override {
      return MAX_SIZE;
   }

   T
   get() override {
      return buffer[m_ReadIndex];
   }

   Result<T>
   get_at(size_t index) override {
      if (index >= MAX_SIZE) {
         return Error({ OUT_OF_BOUNDS, "Index out of bounds" });
      }

      return buffer[index];
   }

   Result<std::vector<T>>
   get_range(size_t start, size_t end) override {
      if (start >= MAX_SIZE || end >= MAX_SIZE || start > end) {
         return Error({ OUT_OF_BOUNDS, "Range out of bounds" });
      }

      std::vector<T> range(buffer.begin() + start, buffer.begin() + end);

      return range;
   }

   Result<T>
   read() override {
      if (m_ReadIndex >= MAX_SIZE) {
         return Error({ OUT_OF_BOUNDS, "Read index out of bounds" });
      }

      return buffer[m_ReadIndex++];
   }

   Result<T>
   read_at(size_t index) override {
      if (index >= MAX_SIZE) {
         return Error({ OUT_OF_BOUNDS, "Index out of bounds" });
      }

      return buffer[index];
   }

   Result<std::vector<T>>
   read_range(size_t start, size_t end) override {
      if (start >= MAX_SIZE || end >= MAX_SIZE || start > end) {
         return Error({ OUT_OF_BOUNDS, "Range out of bounds" });
      }

      std::vector<T> range(buffer.begin() + start, buffer.begin() + end + 1);
      m_ReadIndex = end + 1;

      return range;
   }

   size_t
   get_read_index() override {
      return m_ReadIndex;
   }

   size_t
   get_read_remaining() override {
      return MAX_SIZE - m_ReadIndex;
   }

   Result<void>
   seek_read(size_t index) override {
      if (index >= MAX_SIZE) {
         return Error({ OUT_OF_BOUNDS, "Index out of bounds" });
      }

      m_ReadIndex = index;

      return Result<void>::ok();
   }

   Result<uint16_t>
   read_uint16() override {
      if (m_ReadIndex + 1 >= MAX_SIZE) {
         return Error({ OUT_OF_BOUNDS, "Read index out of bounds" });
      }

      uint16_t value = (buffer[m_ReadIndex] << 8) | buffer[m_ReadIndex + 1];
      m_ReadIndex += 2;

      return value;
   }

   Result<uint32_t>
   read_uint32() override {
      if (m_ReadIndex + 3 >= MAX_SIZE) {
         return Error({ OUT_OF_BOUNDS, "Read index out of bounds" });
      }

      uint32_t value = (buffer[m_ReadIndex] << 24) | (buffer[m_ReadIndex + 1] << 16) |
                       (buffer[m_ReadIndex + 2] << 8) | buffer[m_ReadIndex + 3];
      m_ReadIndex += 4;

      return value;
   }

   Result<void>
   write(T value) override {
      if (m_WriteIndex >= MAX_SIZE) {
         return Error({ OUT_OF_BOUNDS, "Write index out of bounds" });
      }

      buffer[m_WriteIndex++] = value;

      return Result<void>::ok();
   }

   Result<void>
   write_at(size_t index, T value) override {
      if (index > MAX_SIZE) {
         return Error({ OUT_OF_BOUNDS, "Index out of bounds" });
      }

      buffer[index] = value;

      return Result<void>::ok();
   }

   Result<void>
   write_range(size_t start, size_t end, std::vector<T> values) override {
      if (start >= MAX_SIZE || end >= MAX_SIZE || start > end || values.size() != (end - start + 1)) {
         return Error({ OUT_OF_BOUNDS, "Range out of bounds or size mismatch" });
      }

      std::copy(values.begin(), values.end(), buffer.begin() + start);
      m_WriteIndex = end + 1;

      return Result<void>::ok();
   }

   size_t
   get_write_index() override {
      return m_WriteIndex;
   }

   size_t
   get_write_remaining() override {
      return MAX_SIZE - m_WriteIndex;
   }

   Result<void>
   seek_write(size_t index) override {
      if (index >= MAX_SIZE) {
         return Error({ OUT_OF_BOUNDS, "Index out of bounds" });
      }

      m_WriteIndex = index;

      return Result<void>::ok();
   }

   Result<void>
   write_uint16(uint16_t value) override {
      if (m_WriteIndex + 1 >= MAX_SIZE) {
         return Error({ OUT_OF_BOUNDS, "Write index out of bounds" });
      }

      buffer[m_WriteIndex++] = (value >> 8) & 0xFF;
      buffer[m_WriteIndex++] = value & 0xFF;

      return Result<void>::ok();
   }

   Result<void>
   write_uint32(uint32_t value) override {
      if (m_WriteIndex + 3 >= MAX_SIZE) {
         return Error({ OUT_OF_BOUNDS, "Write index out of bounds" });
      }

      buffer[m_WriteIndex++] = (value >> 24) & 0xFF;
      buffer[m_WriteIndex++] = (value >> 16) & 0xFF;
      buffer[m_WriteIndex++] = (value >> 8) & 0xFF;
      buffer[m_WriteIndex++] = value & 0xFF;

      return Result<void>::ok();
   }

   Result<std::vector<T>>
   serialize() override {
      std::vector<T> data(buffer.begin(), buffer.begin() + m_WriteIndex);

      return data;
   }

   Result<void>
   deserialize(std::vector<T> data) override {
      if (data.size() > MAX_SIZE) {
         return Error({ OUT_OF_BOUNDS, "Data size exceeds buffer capacity" });
      }

      std::copy(data.begin(), data.end(), buffer.begin());
      m_WriteIndex = data.size();

      return Result<void>::ok();
   }
};

/* ------------------------------------------------------------------------------------------------------- */
