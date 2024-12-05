#include "header.hpp"

/* ------------------------------------------------------------------------------------------------------- */

PacketHeader::PacketHeader(uint16_t   id,
                           bool       query_response,
                           uint8_t    op_code,
                           bool       authoritative_answer,
                           bool       truncated_message,
                           bool       recursion_desired,
                           bool       recursion_available,
                           uint8_t    reserved,
                           ResultCode response_code,
                           uint16_t   question_count,
                           uint16_t   answer_count,
                           uint16_t   authority_count,
                           uint16_t   additional_count)
    : id(id), query_response(query_response), op_code(op_code), authoritative_answer(authoritative_answer),
      truncated_message(truncated_message), recursion_desired(recursion_desired),
      recursion_available(recursion_available), reserved(reserved), response_code(response_code),
      question_count(question_count), answer_count(answer_count), authority_count(authority_count),
      additional_count(additional_count)
{
}

/* ------------------------------------------------------------------------------------------------------- */

PacketHeader::PacketHeader(const PacketHeader &other)
    : id(other.id), query_response(other.query_response), op_code(other.op_code),
      authoritative_answer(other.authoritative_answer), truncated_message(other.truncated_message),
      recursion_desired(other.recursion_desired), recursion_available(other.recursion_available),
      reserved(other.reserved), response_code(other.response_code), question_count(other.question_count),
      answer_count(other.answer_count), authority_count(other.authority_count),
      additional_count(other.additional_count)
{
}

/* ------------------------------------------------------------------------------------------------------- */

PacketHeader::PacketHeader(PacketHeader &&other) noexcept
    : id(other.id), query_response(other.query_response), op_code(other.op_code),
      authoritative_answer(other.authoritative_answer), truncated_message(other.truncated_message),
      recursion_desired(other.recursion_desired), recursion_available(other.recursion_available),
      reserved(other.reserved), response_code(other.response_code), question_count(other.question_count),
      answer_count(other.answer_count), authority_count(other.authority_count),
      additional_count(other.additional_count)
{
}

/* ------------------------------------------------------------------------------------------------------- */

PacketHeader &
PacketHeader::operator=(const PacketHeader &other)
{
   if (this != &other)
   {
      id                   = other.id;
      query_response       = other.query_response;
      op_code              = other.op_code;
      authoritative_answer = other.authoritative_answer;
      truncated_message    = other.truncated_message;
      recursion_desired    = other.recursion_desired;
      recursion_available  = other.recursion_available;
      reserved             = other.reserved;
      response_code        = other.response_code;
      question_count       = other.question_count;
      answer_count         = other.answer_count;
      authority_count      = other.authority_count;
      additional_count     = other.additional_count;
   }
   return *this;
}

/* ------------------------------------------------------------------------------------------------------- */

PacketHeader &
PacketHeader::operator=(PacketHeader &&other) noexcept
{
   if (this != &other)
   {
      id                   = other.id;
      query_response       = other.query_response;
      op_code              = other.op_code;
      authoritative_answer = other.authoritative_answer;
      truncated_message    = other.truncated_message;
      recursion_desired    = other.recursion_desired;
      recursion_available  = other.recursion_available;
      reserved             = other.reserved;
      response_code        = other.response_code;
      question_count       = other.question_count;
      answer_count         = other.answer_count;
      authority_count      = other.authority_count;
      additional_count     = other.additional_count;
   }
   return *this;
}

/* ------------------------------------------------------------------------------------------------------- */
