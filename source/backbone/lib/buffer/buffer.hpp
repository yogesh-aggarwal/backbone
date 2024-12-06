#pragma once

#include <backbone/core/pch>

/* ------------------------------------------------------------------------------------------------------- */

template<typename T, size_t MAX_SIZE>
class IReadableBuffer {
public:
   virtual T
   get() = 0;

   virtual Result<T>
   get_at(size_t index) = 0;

   virtual Result<std::vector<T>>
   get_range(size_t start, size_t end) = 0;

   virtual Result<T>
   read() = 0;

   virtual Result<T>
   read_at(size_t index) = 0;

   virtual Result<std::vector<T>>
   read_range(size_t start, size_t end) = 0;

   virtual size_t
   get_read_index() = 0;

   virtual size_t
   get_read_remaining() = 0;

   virtual Result<void>
   seek_read(size_t index) = 0;

   virtual Result<uint16_t>
   read_uint16() = 0;

   virtual Result<uint32_t>
   read_uint32() = 0;
};

/* ------------------------------------------------------------------------------------------------------- */

template<typename T, size_t MAX_SIZE>
class IWritableBuffer {
public:
   virtual Result<void>
   write(T value) = 0;

   virtual Result<void>
   write_at(size_t index, T value) = 0;

   virtual Result<void>
   write_range(size_t start, size_t end, std::vector<T> values) = 0;

   virtual size_t
   get_write_index() = 0;

   virtual size_t
   get_write_remaining() = 0;

   virtual Result<void>
   seek_write(size_t index) = 0;

   virtual Result<void>
   write_uint16(uint16_t value) = 0;

   virtual Result<void>
   write_uint32(uint32_t value) = 0;
};

/* ------------------------------------------------------------------------------------------------------- */

template<typename T, size_t MAX_SIZE>
class ISerializableBuffer {
public:
   virtual Result<std::vector<T>>
   serialize() = 0;

   virtual Result<void>
   deserialize(std::vector<T> data) = 0;
};

/* ------------------------------------------------------------------------------------------------------- */

template<typename T, size_t MAX_SIZE>
class IBuffer : public IReadableBuffer<T, MAX_SIZE>,
                public IWritableBuffer<T, MAX_SIZE>,
                public ISerializableBuffer<T, MAX_SIZE> {
public:
   virtual size_t
   get_capacity() = 0;
};

/* ------------------------------------------------------------------------------------------------------- */
