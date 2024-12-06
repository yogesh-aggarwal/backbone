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
   RETURN_IF_ERROR(header);

   /* Parse questions */
   std::vector<PacketQuestion> questions;
   for (size_t i = 0; i < header.get_value().question_count; i++) {
      // Parse question
      auto question = PacketQuestion::from_buffer(buffer)
                          //
                          .with_catch({ FAILED_TO_PARSE_QUESTION, "Failed to parse packet question" });
      RETURN_IF_ERROR(question);

      // Add question to the list
      questions.push_back(question.get_value());
   }

   /* Parse answers */

   /* Parse authorities */

   /* Parse additionals */

   return Packet(header.get_value(), {}, {}, {}, {});
}

/* ------------------------------------------------------------------------------------------------------- */
