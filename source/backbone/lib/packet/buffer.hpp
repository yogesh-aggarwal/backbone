#pragma once

#include <backbone/lib/buffer/basic.tcc>

/* ------------------------------------------------------------------------------------------------------- */

class PacketBuffer : public BasicBuffer<Byte, 512> {
public:
   PacketBuffer();
   ~PacketBuffer() = default;

   Result<std::string>
   read_qname();

   Result<void>
   write_qname(std::string qname);
};

/* ------------------------------------------------------------------------------------------------------- */
