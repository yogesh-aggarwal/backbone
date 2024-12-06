#include "record.hpp"

/* ------------------------------------------------------------------------------------------------------- */

Result<PacketRecord>
PacketRecord::from_buffer(Ref<PacketBuffer> buffer) {
   return PacketRecord();
}

/* ------------------------------------------------------------------------------------------------------- */

Result<void>
PacketRecord::write_to_buffer(Ref<PacketBuffer> buffer) const {
   return Result<void>();
}

/* ------------------------------------------------------------------------------------------------------- */
