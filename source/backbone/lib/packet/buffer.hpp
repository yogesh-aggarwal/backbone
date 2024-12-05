#pragma once

#include <backbone/lib/buffer/basic.tcc>

/* ------------------------------------------------------------------------------------------------------- */

class PacketBuffer : public BasicBuffer<uint8_t, 512>
{
public:
   PacketBuffer() : BasicBuffer<uint8_t, 512>(0) {}
   PacketBuffer(const PacketBuffer &other) : BasicBuffer<uint8_t, 512>(other) {}
   PacketBuffer(PacketBuffer &&other) : BasicBuffer<uint8_t, 512>(std::move(other)) {}
   ~PacketBuffer() = default;

   PacketBuffer &
   operator=(const PacketBuffer &other)
   {
      BasicBuffer<uint8_t, 512>::operator=(other);
      return *this;
   }

   PacketBuffer &
   operator=(PacketBuffer &&other)
   {
      BasicBuffer<uint8_t, 512>::operator=(std::move(other));
      return *this;
   }
};

/* ------------------------------------------------------------------------------------------------------- */
