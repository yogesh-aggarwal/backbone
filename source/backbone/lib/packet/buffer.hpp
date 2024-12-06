#pragma once

#include <backbone/lib/buffer/basic.tcc>

/* ------------------------------------------------------------------------------------------------------- */

class PacketBuffer : public BasicBuffer<Byte, 512> {
public:
   PacketBuffer();
   ~PacketBuffer() = default;
};

/* ------------------------------------------------------------------------------------------------------- */
