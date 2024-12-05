#pragma once

#include <backbone/core/pch>

/* ------------------------------------------------------------------------------------------------------- */

template<typename T, size_t MAX_SIZE>
class IReadableBuffer
{
public:
   virtual T
   Get() = 0;

   virtual Result<T>
   GetAt(size_t index) = 0;

   virtual Result<std::vector<T>>
   GetRange(size_t start, size_t end) = 0;

   virtual Result<T>
   Read() = 0;

   virtual Result<T>
   ReadAt(size_t index) = 0;

   virtual Result<std::vector<T>>
   ReadRange(size_t start, size_t end) = 0;

   virtual size_t
   GetReadIndex() = 0;

   virtual size_t
   GetReadRemaining() = 0;

   virtual Result<bool>
   SeekRead(size_t index) = 0;

   virtual Result<uint16_t>
   ReadUInt16() = 0;

   virtual Result<uint32_t>
   ReadUInt32() = 0;
};

/* ------------------------------------------------------------------------------------------------------- */

template<typename T, size_t MAX_SIZE>
class IWritableBuffer
{
public:
   virtual Result<bool>
   Write(T value) = 0;

   virtual Result<bool>
   WriteAt(size_t index, T value) = 0;

   virtual Result<bool>
   WriteRange(size_t start, size_t end, std::vector<T> values) = 0;

   virtual size_t
   GetWriteIndex() = 0;

   virtual size_t
   GetWriteRemaining() = 0;

   virtual Result<bool>
   SeekWrite(size_t index) = 0;

   virtual Result<bool>
   WriteUInt16(uint16_t value) = 0;

   virtual Result<bool>
   WriteUInt32(uint32_t value) = 0;
};

/* ------------------------------------------------------------------------------------------------------- */

template<typename T, size_t MAX_SIZE>
class ISerializableBuffer
{
public:
   virtual Result<std::vector<T>>
   Serialize() = 0;

   virtual Result<bool>
   Deserialize(std::vector<T> data) = 0;
};

/* ------------------------------------------------------------------------------------------------------- */

template<typename T, size_t MAX_SIZE>
class IBuffer : public IReadableBuffer<T, MAX_SIZE>,
                public IWritableBuffer<T, MAX_SIZE>,
                public ISerializableBuffer<T, MAX_SIZE>
{
public:
   virtual size_t
   GetCapacity() = 0;
};

/* ------------------------------------------------------------------------------------------------------- */
