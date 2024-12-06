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
   std::vector<PacketRecord> answers;
   for (size_t i = 0; i < header.get_value().answer_count; i++) {
      // Parse answer
      auto answer = PacketRecord::from_buffer(buffer)
                        //
                        .with_catch({ FAILED_TO_PARSE_RECORD, "Failed to parse packet answer" });
      RETURN_IF_ERROR(answer);

      // Add answer to the list
      answers.push_back(answer.get_value());
   }

   /* Parse authorities */
   std::vector<PacketRecord> authorities;
   for (size_t i = 0; i < header.get_value().authority_count; i++) {
      // Parse authority
      auto authority = PacketRecord::from_buffer(buffer)
                           //
                           .with_catch({ FAILED_TO_PARSE_RECORD, "Failed to parse packet authority" });
      RETURN_IF_ERROR(authority);

      // Add authority to the list
      authorities.push_back(authority.get_value());
   }

   /* Parse additionals */
   std::vector<PacketRecord> additionals;
   for (size_t i = 0; i < header.get_value().additional_count; i++) {
      // Parse additional
      auto additional = PacketRecord::from_buffer(buffer)
                            //
                            .with_catch({ FAILED_TO_PARSE_RECORD, "Failed to parse packet additional" });
      RETURN_IF_ERROR(additional);

      // Add additional to the list
      additionals.push_back(additional.get_value());
   }

   auto packet = Packet(header.get_value(), questions, answers, authorities, additionals);
   return packet;
}

/* ------------------------------------------------------------------------------------------------------- */
