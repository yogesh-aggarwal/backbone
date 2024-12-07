#pragma once

/* ------------------------------------------------------------------------------------------------------- */

enum ErrorCode {
   /* Generic Error Codes */

   UNDEFINED = -1,
   UNKNOWN   = 0x0,

   /* Buffer Codes */
   OUT_OF_BOUNDS = 0x1,
   FAILED_TO_READ_QNAME,
   FAILED_TO_READ_LABEL,

   /* Packet Error Codes */
   FAILED_TO_PARSE_HEADER = 0x2,
   FAILED_TO_WRITE_HEADER,
   FAILED_TO_PARSE_QUESTION,
   FAILED_TO_WRITE_QUESTION,
   FAILED_TO_PARSE_RECORD,
   FAILED_TO_WRITE_RECORD,
};

/* ------------------------------------------------------------------------------------------------------- */
