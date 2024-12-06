#pragma once

#include "buffer.hpp"

/* ------------------------------------------------------------------------------------------------------- */

class PacketRecord {
public:
   static Result<PacketRecord>
   from_buffer(Ref<PacketBuffer> buffer);
};

/* ------------------------------------------------------------------------------------------------------- */
