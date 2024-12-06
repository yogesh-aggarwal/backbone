#include "packet.hpp"

/* ------------------------------------------------------------------------------------------------------- */

Packet::Packet(PacketHeader                header,
               std::vector<PacketQuestion> questions,
               std::vector<PacketRecord>   answers,
               std::vector<PacketRecord>   authorities,
               std::vector<PacketRecord>   additionals)
    : header(header), questions(questions), answers(answers), authorities(authorities),
      additionals(additionals) {}

/* ------------------------------------------------------------------------------------------------------- */

Result<Packet>
Packet::from_buffer(Ref<PacketBuffer> buffer) {
   /* Parse header */
   auto header = PacketHeader::from_buffer(buffer)
                     //
                     .with_catch({ FAILED_TO_PARSE_HEADER, "Failed to parse packet header" });
   if (header.is_error()) {
      return header.get_error();
   }

   /* Parse questions */

   /* Parse answers */

   /* Parse authorities */

   /* Parse additionals */

   return Packet(header.get_value(), {}, {}, {}, {});
}

/* ------------------------------------------------------------------------------------------------------- */
