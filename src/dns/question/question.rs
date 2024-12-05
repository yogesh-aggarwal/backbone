use crate::{dns::packet::buffer::PacketBufferOps, utility::result::Result};

use super::query_type::DNSQuestionQueryType;

#[derive(Clone, Debug)]
pub struct DNSQuestion {
    /**
     * Label sequence specifying the domain name to be resolved.
     */
    pub name: String,

    /**
     * 2-bytes
     *
     * The record type
     */
    pub question_type: DNSQuestionQueryType,

    /**
     * 2-bytes
     *
     * The class, in practice always set to 1.
     */
    pub class: u16,
}

impl DNSQuestion {
    pub fn new() -> DNSQuestion {
        DNSQuestion {
            name: String::new(),
            question_type: DNSQuestionQueryType::A,
            class: 1,
        }
    }

    pub fn from_buffer<T: PacketBufferOps>(buffer: &mut T) -> Result<DNSQuestion> {
        let mut result = DNSQuestion::new();

        /* Read the domain name */
        buffer
            .read_qname()
            .and_then(|qname| {
                result.name = qname;
                Ok(())
            })
            .expect("Failed to read domain name from buffer.");

        /* Read the question type */
        buffer
            .read_as_u16()
            .and_then(|question_type| {
                result.question_type = DNSQuestionQueryType::from_num(question_type);
                Ok(())
            })
            .expect("Failed to read question type from buffer.");

        /* Read the class */
        buffer
            .read_as_u16()
            .and_then(|class| {
                result.class = class;
                Ok(())
            })
            .expect("Failed to read class from buffer.");

        Ok(result)
    }
}
