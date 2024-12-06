#pragma once

#include <backbone/lib/buffer/basic.tcc>

/* ------------------------------------------------------------------------------------------------------- */

class PacketBuffer : public BasicBuffer<Byte, 512> {
public:
   PacketBuffer();
   PacketBuffer(const PacketBuffer &other);
   PacketBuffer(PacketBuffer &&other);
   ~PacketBuffer() = default;

   PacketBuffer &
   operator=(const PacketBuffer &other);

   PacketBuffer &
   operator=(PacketBuffer &&other);
};

/* ------------------------------------------------------------------------------------------------------- */
